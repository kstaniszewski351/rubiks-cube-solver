#pragma once
#include "coord_generator.h"
#include "symmetries.h"
#include <vector>

class SymCoord : public CoordGenerator
{
public:
    SymCoord(CoordGenerator* base_gen, Symmetries* syms, int n_conj);
    int getCoord(const CubieCube& cube) const override;
    void invertCoord(int sym_coord, CubieCube& cube) const override;
    int getMaxCoord() const override;
    int get(int raw_coord) const;
    int getRep(int sym_coord) const;
    int getSym(const CubieCube& cube) const;
    int getSym(int raw_coord) const;
private:
    CoordGenerator* base_gen_;
    int coord_count_;
    int raw_count;
    std::vector<int> raw_to_sym_;
    std::vector<int> sym_to_rep_;
};