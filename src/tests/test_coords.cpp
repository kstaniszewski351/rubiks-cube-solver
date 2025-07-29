#include <gtest/gtest.h>
#include <coords/coord_generator.h>
#include <coords/edge_flip_generator.h>
#include <coords/corner_twist_generator.h>
#include <coords/ud_slice_pos_generator.h>
#include <coords/ud_slice_perm_generator.h>
#include <coords/corner_perm_generator.h>
#include <coords/ud_perm_generator.h>
#include <move_table.h>
#include <memory>

auto flip_gen = std::make_unique<EdgeFlipGenerator>();
auto twist_gen = std::make_unique<CornerTwistGenerator>();
auto ud_slice_pos_gen = std::make_unique<UDSlicePosGenerator>();
auto ud_perm_gen = std::make_unique<UDPermGenerator>();
auto ud_slice_perm_gen = std::make_unique<UDSlicePermGenerator>();
auto corner_perm_gen = std::make_unique<CornerPermGenerator>();
const std::vector<CoordGenerator*> generators {flip_gen.get(), ud_slice_pos_gen.get(), twist_gen.get(), corner_perm_gen.get(), ud_slice_perm_gen.get(), ud_perm_gen.get()};

class CoordTest : public testing::TestWithParam<CoordGenerator*>
{

};

TEST_P(CoordTest, AreInversionsEqual)
{
    CoordGenerator* generator = GetParam();

    int count = generator->getMaxCoord();
    for(int i = 0; i < count; i++)
    {
        CubieCube cube;
        generator->invertCoord(i, cube);

        int coord = generator->getCoord(cube);

        ASSERT_EQ(i, coord);
    }
}

TEST_P(CoordTest, IsZeroWhenSolved)
{
    CoordGenerator* generator = GetParam();

    CubieCube cube;

    int coord = generator->getCoord(cube);

    EXPECT_EQ(coord, 0);
}

TEST_P(CoordTest, AreMoveTablesCorrect)
{
    CoordGenerator* generator = GetParam();

    auto table = MoveTable(generator);

    for(int coord = 0; coord < generator->getMaxCoord(); coord++)
    {
        for(int move = 0; move < MOVE_COUNT; move++)
        {
            CubieCube cube;
            generator->invertCoord(coord, cube);
            cube.move(static_cast<Move>(move));
            
            int gen_coord = generator->getCoord(cube);
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