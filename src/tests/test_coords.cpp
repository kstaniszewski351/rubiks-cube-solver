#include <gtest/gtest.h>
#include <coords/coord_generator.h>
#include <coords/edge_flip_generator.h>
#include <coords/corner_twist_generator.h>
#include <coords/ud_slice_pos_generator.h>
#include <coords/ud_slice_perm_generator.h>
#include <coords/corner_perm_generator.h>
#include <coords/ud_perm_generator.h>
#include <coords/multi_coord.h>
#include <coords/sym_coord.h>
#include <move_table.h>
#include <memory>

auto syms = std::make_unique<Symmetries>();
auto flip_gen = std::make_unique<EdgeFlipGenerator>();
auto twist_gen = std::make_unique<CornerTwistGenerator>();
auto ud_slice_pos_gen = std::make_unique<UDSlicePosGenerator>();
auto ud_perm_gen = std::make_unique<UDPermGenerator>();
auto ud_slice_perm_gen = std::make_unique<UDSlicePermGenerator>();
auto corner_perm_gen = std::make_unique<CornerPermGenerator>();
auto flip_ud_slice_gen = std::unique_ptr<MultiCoord>(new MultiCoord({flip_gen.get(), ud_slice_pos_gen.get()}));
auto sym_flip_ud_slice_gen = std::make_unique<SymCoord>(flip_ud_slice_gen.get(), syms.get(), 0);
const std::vector<CoordGenerator*> generators {flip_gen.get(), ud_slice_pos_gen.get(), twist_gen.get(), corner_perm_gen.get(), ud_slice_perm_gen.get(), ud_perm_gen.get()};

class CoordTest : public testing::TestWithParam<CoordGenerator*>
{

};

TEST_P(CoordTest, AreInversionsEqual)
{
    CoordGenerator* generator = GetParam();

    int count = generator->GetMaxCoord();
    for(int i = 0; i < count; i++)
    {
        CubieCube cube;
        generator->InvertCoord(i, cube);

        int coord = generator->GetCoord(cube);

        EXPECT_EQ(i, coord);
    }
}

TEST_P(CoordTest, IsZeroWhenSolved)
{
    CoordGenerator* generator = GetParam();

    CubieCube cube;

    int coord = generator->GetCoord(cube);

    EXPECT_EQ(coord, 0);
}

TEST_P(CoordTest, AreMoveTablesCorrect)
{
    CoordGenerator* generator = GetParam();

    auto table = MoveTable(generator);

    for(int coord = 0; coord < generator->GetMaxCoord(); coord++)
    {
        for(int move = 0; move < MOVE_COUNT; move++)
        {
            CubieCube cube;
            generator->InvertCoord(coord, cube);
            cube.Move(static_cast<Move>(move));
            
            int gen_coord = generator->GetCoord(cube);
            int table_coord = table.get(coord, move);

            ASSERT_EQ(gen_coord, table_coord);
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    CoordInversion,
    CoordTest,
    testing::ValuesIn(generators)
);

// const std::vector<CoordGenerator*> table_generators {flip_gen.get(), twist_gen.get(), ud_slice_pos_gen.get(), ud_slice_perm_gen.get()};

// class MoveTableTest : public testing::Test
// {
// protected:
//     MoveTableTest()
//     {
//         move_tables_.reserve(table_generators.size());
//         for(auto& generator : table_generators)
//         {
//             move_tables_.push_back(std::make_unique<MoveTable>(generator));
//         }
//     }

//     std::vector<std::unique_ptr<MoveTable>> move_tables_;
// };

// TEST_F(MoveTableTest, AreMovesCorrect)
// {
//     for(int i = 0; i < move_tables_.size(); i++)
//     {
//         auto table = move_tables_[i].get();
//         auto generator = table_generators[i];
//         for(int coord = 0; coord < generator->getMaxCoord(); coord++)
//         {
//             for(int move = 0; move < MOVE_COUNT; move++)
//             {
//                 CubieCube cube;
//                 generator->invertCoord(coord, cube);
//                 cube.move(static_cast<Move>(move));
                
//                 int gen_coord = generator->getCoord(cube);
//                 int table_coord = table->get(coord, move);

//                 ASSERT_EQ(gen_coord, table_coord);
//             }
//         }
//     }
// }

TEST(MultiCoordTest, CheckRaw)
{
    CubieCube m_cube;
    CubieCube r_cube;
    auto raw_buff = std::vector<int>(2);
    for(int i = 0; i < flip_ud_slice_gen->getMaxCoord(); i++)
    {
        flip_ud_slice_gen->invertCoord(i, m_cube);
        flip_ud_slice_gen->getRaw(i, raw_buff.begin());
        flip_gen->invertCoord(raw_buff[0], r_cube);
        ud_slice_pos_gen->invertCoord(raw_buff[1], r_cube);

        EXPECT_EQ(m_cube, r_cube);
    }
}
