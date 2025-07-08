#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/screen.hpp>
#include <random>
#include <vector>
#include "ui.h"
#include "cube.h"
#include "const.h"

using namespace ftxui;

UI::UI() : screen_(ScreenInteractive::Fullscreen())
{

    std::vector<std::string> menu_entries
    {
        "Moves",
        "2"
    };
    int selected = 0;
    auto menu = Menu({
        .entries = &menu_entries,
        .selected = &selected
    });

    auto cube_input = true;
    auto cube_vis = Cube(face_cube_, 8, cube_input);
    auto cube_view = Renderer(cube_vis, [&] {return cube_vis->Render() | center;});


    std::string input_moves;
    auto move_input_option = InputOption();
    move_input_option.on_enter = [&]
    {
        bool success = true;
        std::vector<Move> moves;

        std::istringstream iss(input_moves);
        std::string move;

        input_moves = "";
        while(iss >> move)
        {
            auto result = std::ranges::find(MOVE_NAMES, move);

            if(result == MOVE_NAMES.end())
            {
                success = false;
                break;
            }

            moves.push_back(static_cast<Move>(std::distance(MOVE_NAMES.begin(), result)));
        }

        if(!success) { return;}
        
        for(Move move : moves)
        {
            scramble_.push_back(move);
            cube_.move(move);
        }

        face_cube_ = FaceCube(cube_);
    };
    auto move_input = Input(&input_moves, move_input_option);

    std::string reset_button_label = "Reset";
    auto reset_button = Button(&reset_button_label, [&]
    {
        scramble_.clear();
        cube_.reset();
    });

    std::string scramble_move_count = "30";
    auto scramble_input_option = InputOption();
    scramble_input_option.multiline = false;
    auto scramble_input = Input(&scramble_move_count, scramble_input_option);

    scramble_input |= CatchEvent([&](Event event) {
        return event.is_character() && !std::isdigit(event.character()[0]);
    });

    std::string scramble_button_label = "Scramble";

    auto scramble_button = Button(&scramble_button_label, [&]
    {   
        if(scramble_move_count.empty()) {return; };
        int move_count = std::stoi(scramble_move_count);
        std::uniform_int_distribution<> distrib(0, MoveCount - 1);
        std::random_device random;
        std::mt19937 rng(random());
        
        int last_move = 0;
        for(int i = 0; i < move_count; i++)
        {
            int generated = distrib(rng);

            while(generated / 3 == last_move / 3)
            {
                generated = distrib(rng);
            }
            last_move = generated;
            
            auto move = static_cast<Move>(generated);

            scramble_.push_back(move);
            cube_.move(move);
        }

        face_cube_ = cube_;
    });

    auto bottom_container = Container::Horizontal({
        move_input,
        Container::Vertical({
            reset_button,
            Container::Horizontal({scramble_input, scramble_button})
        })
    });
    
    auto flexbox_config = FlexboxConfig();
    flexbox_config.SetGap(1, 1);

    auto cubie_cube_renderer = Renderer([&] {
        std::string edge_perm;
        std::string corner_perm;
        std::string edge_ori;
        std::string corner_ori;

        for(Edge i: cube_.edgePerm)
        {
            for(Face c: EDGE_COLORS[i])
            {
                edge_perm += FACE_NAMES[c];
            }
            edge_perm += " ";
        }

        for(Corner i: cube_.cornerPerm)
        {
            for(Face c: CORNER_COLORS[i])
            {
                corner_perm += FACE_NAMES[c];
            }
            corner_perm += " ";
        }

        for(int i: cube_.edgeOri)
        {
            edge_ori += std::to_string(i) + " ";
        }

        for(int i: cube_.cornerOri)
        {
            corner_ori += std::to_string(i) + " ";
        }

        return vbox(
            hbox(text("Edge permutation: "), text(edge_perm)),
            hbox(text("Corner permutation: "), text(corner_perm)),
            hbox(text("Edge orientation: "), text(edge_ori)),
            hbox(text("Corner orientation: "), text(corner_ori))
        );
    });

    auto scramble_renderer = Renderer([&] {
        std::string scramble = "";

        for(Move m : scramble_)
        {
            scramble += MOVE_NAMES[m];
            scramble += " ";
        }

        return window(text("Scramble"), paragraph(scramble));
    });

    auto bottom_view = Renderer(bottom_container, [&] {


        return hbox(
            vbox(
                hbox(text("Apply moves: "), move_input->Render()) | border,
                scramble_renderer->Render()
            ) | border | xflex_grow,
            vbox(
                hbox(reset_button->Render()),
                hbox(hbox(text("Move count: "), scramble_input->Render() | size(WIDTH, EQUAL, 4)) | vcenter, scramble_button->Render()) | border
            ) | border,
            cubie_cube_renderer->Render() | border
        );
    });


    int split_d_size = 10;
    auto splid_d = ResizableSplitBottom(bottom_view, cube_view, &split_d_size);

    int split_l_size = 10;
    auto split_l = ResizableSplitLeft(menu, splid_d, &split_l_size);

    auto main_renderer = Renderer(split_l, [&] {
        return split_l->Render();
    });

    screen_.Loop(main_renderer);
}

void UI::Run()
{
    screen_.Loop(main_component_);
}