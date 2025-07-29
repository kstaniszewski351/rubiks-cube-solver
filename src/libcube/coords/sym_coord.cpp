#include "sym_coord.h"

SymCoord::SymCoord(CoordGenerator* base_gen, Symmetries* syms, int n_conj = 0) 
    : base_gen_(base_gen)
{

    raw_count = base_gen->getMaxCoord();

    if(n_conj == 0)
    {
        //approximate
        n_conj = raw_count / D4H_SYM_COUNT;
    }

    raw_to_sym_.resize(raw_count, -1);
    sym_to_rep_.reserve(n_conj);

    int i = 0;
    CubieCube cube;
    for(int raw = 0; raw < raw_count; raw++)
    {
            if(raw_to_sym_[raw] != -1) {continue;}
            
            raw_to_sym_[raw] = i * D4H_SYM_COUNT;

            sym_to_rep_.push_back(raw);
            
            base_gen->invertCoord(raw, cube);

            for(int sym = 0; sym < D4H_SYM_COUNT; sym++)
            {
                CubieCube sym_cube = syms->getInv(sym);
                sym_cube.multiply(cube);
                sym_cube.multiply(syms->get(sym));

                int s_raw = base_gen->getCoord(sym_cube);
                
                if(raw_to_sym_[s_raw] == -1)
                {
                    raw_to_sym_[s_raw] = i * D4H_SYM_COUNT + sym;
                }
            }
            i++;
    }
    sym_to_rep_.shrink_to_fit();
    coord_count_ = i;
}

int SymCoord::getCoord(const CubieCube& cube) const
{
    int raw = base_gen_->getCoord(cube);

    return raw_to_sym_[raw] / D4H_SYM_COUNT;
}

int SymCoord::get(int raw_coord) const
{
    return raw_to_sym_[raw_coord] / D4H_SYM_COUNT;
}

int SymCoord::getSym(const CubieCube& cube) const
{
    int raw = base_gen_->getCoord(cube);

    return raw_to_sym_[raw] % D4H_SYM_COUNT;
}

int SymCoord::getSym(int raw_coord) const
{
    return raw_to_sym_[raw_coord] % D4H_SYM_COUNT;
}

void SymCoord::invertCoord(int coord, CubieCube& cube) const
{
    int raw = sym_to_rep_[coord];
    base_gen_->invertCoord(raw, cube);
}

int SymCoord::getRep(int sym_coord) const
{
    return sym_to_rep_[sym_coord];
}

int SymCoord::getMaxCoord() const
{
    return coord_count_;
}