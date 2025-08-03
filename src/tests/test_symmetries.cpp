#include <gtest/gtest.h>
#include <symmetries.h>
#include <face_cube.h>

static std::unique_ptr<Symmetries> syms = std::make_unique<Symmetries>();

TEST(SymmetriesTest, AreUnique)
{
    for(int i = 0; i < SYM_COUNT; i++)
    {
        for(int j = 0; j < SYM_COUNT; j++)
        {
            if(j != i)
            {
                EXPECT_FALSE(syms->get(i) == syms->get(j)) << "Syms are the same: " << i << ", " << j;
            }
        }
    }
}

TEST(SymmetriesTest, AreInversionsCorrect)
{
    for(int i = 0; i < SYM_COUNT; i++)
    {
        CubieCube solved_cube;
        CubieCube sym = syms->get(i);
        sym.Multiply(syms->getInv(i));

        EXPECT_EQ(sym, solved_cube);
    }
}

TEST(SymmetriesTest, AreFacesSingleColored)
{
    for(int i = 0; i < SYM_COUNT; i++)
    {
        auto cube = FaceCube(syms->get(i));

        for(int face = 0; face < FaceCount; face++)
        {
            Face fl0 = cube.facelets[face * facelet_count];
            for(int facelet = 0; facelet < facelet_count; facelet++)
            {
                EXPECT_EQ(fl0, cube.facelets[face * facelet_count + facelet]);
            }
        }
    }
}