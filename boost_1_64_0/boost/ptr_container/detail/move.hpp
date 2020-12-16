// (C) Copyright Daniel Wallin 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// Contains the definitions of the class template move_source and the function
// template move, which together make move pointers moveable.

#ifndef BOOST_MOVE_HPP_INCLUDED
#define BOOST_MOVE_HPP_INCLUDED

namespace boost { namespace ptr_container_detail {

namespace move_ptrs {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)    
#pragma warning(push)    
#pragma warning(disable:4512)  
#endif  
    
template<typename Ptr>
class move_source {
public:
    move_source(Ptr& ptr) : ptr_(ptr) {}
    Ptr& ptr() const { return ptr_; }
private:
    Ptr& ptr_;
    move_source(const Ptr&);
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)    
#pragma warning(pop)    
#endif  

} // End namespace move_ptrs.


template<typename T>
move_ptrs::move_source<T> move(T& x) 
{ return move_ptrs::move_source<T>(x); }

} // namespace 'ptr_container_detail'
} // End namespace boost.

#endif // #ifndef BOOST_MOVE_HPP_INCLUDED

/* move.hpp
ZPvmYLZvHmGPk37+Vf7Zb7Bsfx3M9tcjbGPoFhC3Y50I62OwrQRdjsHyBTbUYBc4EVZgsDw3wiYa7BARd7rBXhdxn6J8t4IdvhOYPZ4QcZ8B+xC6PiEmxxgCe35QOMaIsJcMtpHAXjbYJgJ7FWzg1azPiPK9brDNBfYG2KjL2csc1VeMY8CsccxgUT4xjtHYhG6OQ9rafVensd3fcjMc5zpzfPBvDQHWZljxPzc+6La/KP2+eK8Wtyf1v+4TduUKqlAeIp/wJzt/PzJYaWqs7dzl/K/6jh/9O3Y0MKNVs/5PTKmvAwqwm5gKtdjYTV+3b8LXg28JWJNlO5fyHQuPmvmNNcX/UYNa2NhMtVhTtGxqo7GpLXzZtrIwxlYWxthKMNsugtl2Ecy2OwITNgbMnseKsE+MPZm1XYR9ZrBb+0fYVwZ7S2DfG+zKPLAYewJmz4uB2fYErJvzYr49SS4ys1qLUD5NybZRDWyAyWqHfSPfRsylOhg0Vlb8K38TYfREndaQym6ropi2KoppKzC7rcDstgKz20pgsq3A7LYCs3kLls1bMJu3YGthq0PeYqvrFi0J54MlX4+K+Grd/55IYBJasNENqYWMG/AZVRZfJsf0CTCbz2A2n8Gy+QJm8wXM5oHBxnSTBw0p/odQtCxpTMIBq/4ni/pn12VKTF3A7LqA2f0HLKufRZg3OMCeFHSSr2C2vIHZ8gZmy5vAJF/BbD0AZvMaLFsGwWz+g601/wNZyub/xYL/2XyYGtMmYHabgNltEmH9Da839iLsEeKecK2+1xTM5leEDRwMX6Abq8Cy+QVm8wZsrXnDoRvDnEzeXNulbJbG8KE0hg9gNl/BbPkCs+VLYFK+wGx+gdm8AcuWJTCbX2BrwS+9BqLXl+sWNmTx664uZWlaDA/BbB6C2TwEi6kzmF1nMLt+YGthC3X9tHcihCJLZz/UZT2nx9QTzK4nmF3PCNvW9Jm9domwHQx2sMAkP8BsfoDZ/ABb2/b21x1p7mzd8UyXfCiL4QOYzQcwmw9gMfUDs+sHZtcPbC3a27/jkHuuq+tXNifam7jpiOvIsuv5apf1nBFTTzC7nmB2PcFi6glm1xPMrifYv1FP5g9ibME7GfUsXMu0OfHHgUWW6pPtwWGgLP3w3r+VfgdBIvGYfvmBSD97fmtWzPzWLHt+S2ByfmtWzPwWmD2/BWbPb4GtRV3NBhOC8KHZq+TvizZzPFZdP+9yXPSbGPkDs+UPzJbnCBuDvim9gfM6Csy2VwITPAazeQxm81hgksdgNo/BbB6DxfAYzJ5DBLPnCyNsfEzdJoK1gf1epCfmEMHsOUQwew5RYJNMeitFenJeEcyeVwSz5xXBbH0g6Ipj6jELvlwI1k9gU2LopknMnqcUmNA5GqtYW1k2f8irnMNLnONlu09fKdu2jFXEyFiFLWMCkzIGZssYmC1jYLaMmbiT177uzZyFptpM+7HVvElX2K5vbpf1rYypb6VdX4HJ+lbG1Lcypr6VMfWtXAv7kq5vsnlZpLTseg7tsp5VMfWssuspMFnPqph6gtn1BLPrCfZT6unvtIoqatUzv8t6zo6p52y7ngKT9ZwdU08wu55gdj3BflI9m9rZf1cf308ndFnPOVn1BLPrKTBZTzC7nmB2PcHsepq45Wtbz8Zm/eZJdNY0nM6Ka9+iLus9N6veYHa9BSbrDWbXG8yuN5hdbxF3Bsp7nev9twvAfkqbG0cuvs1ndFn3eTF1B7PrDmbXHSym7mB23cHsuoP9lHqyo75zXTWny3rOj6knmF1PMLueYDH1BLPrCWbXE+yn+JLBxH5gfmP1VaJvV77kgmxfEsz2JSOsCvnLuVkpyME=
*/