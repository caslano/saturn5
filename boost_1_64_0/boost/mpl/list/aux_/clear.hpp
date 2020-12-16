
#ifndef BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_end type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
Kdf41FXOi300vzNpL+3YAb2wI5bGTuiLnbEmBmI37IYh2B3HYA98D3vjUnwJ12Jf/AAH4HYMwtNowHMYhhdxMF7GCIn3GIJ5MRLdMQo9MBqL4itYEmOxNMZjPUzAxjgSDTgKw3AMRuNYfANfxamYxH9zcTwuwddwBU7CH3EyXsIpmIe2ehOr4tvoj9MwAJPxRZyBvXEm9sM5OATfwXdwLqbgPHwf5+OHuAAP40I8jovwDL6H6bgYf8IUzOPKPobFcDmWxRX4DK7EqrgKq+FqbIfvYwSuw/G4AV/HVJyMH+AM3ITv4FZchdtwPW7HXbgDv8YP8Q7uRg+lPx+L414sifuwNH6EvrgfK+PHWBMP4XP4KdbBI9gIj2IP/AJ7YRq+jCfQgCcxEU/haGRfkv5K+e6D79rpr/ST4685emMLLIstsQ76YyNshc2wDbbBAByAbTES22EstsfXsAMm4ws4Czuhi/QrLrzw6H7FXbznLIn+xf/pcZXuXMj31PsTC1zM51Sf4uP2J/pSThtSCGkiKYV0kHSedJ/kdYm+Q1IbUj9S4qXsfsTsV/Yr+5X9+m9+/SX9/2js/n/C/n/zMwCuvqPt/2fh0vdfQ/Pb/zbSH1+K5EoqQdqh9P3vV/uplW5Q5edtxr4N/vdKQmhclvqsrftnuc+rlrvLQbkxtuWa7l0HDU4wxBqi4p2IP7BXbn35jtOcVJDkJ/1XyVbl8nMo/Ro7ER8g5eriAfxZSV58J6ZcLIw7KTx9vy4WgWxBMYaIWGNZHpmVRb9G6gHyyjO+i0rZTSsZy64TFGMZayCBZGxDBlvn+lb6ltT31jW/18vqvXVlnW6Z+1plOsPO/X5ZZ7JIH6JlHkXqn6FwWtoiXrZBDGm3H2100NIWSss7239JWWp/xR+sDKug66+gL9m6v0JXr+Bctv2qe5VtZFWv2k+pXhI/YVOPO7nstQ9+bKnHYz1X+wnbJym3/fbxOGRVr9pPp16O2ud0bgexNZZ6GE93WTlHafu2J8tvjEdIfygSE2L6sstyWaIpJERZptxDz7QvNGSfPh7EY5+lb3TvXtvxDbbutY23aLDXdsyDYntt+1Wv7LHtV/1anVdXjSU5bJmnlrvYMk8tY8Ie2ziPoZZ59c3zuuyx7btttMd2bIQKe2z7c/Nb5ql1frDbdmyEY5Z5al22WeapdZlsmaeWMWq3bf/wuV32n/HBBn6sWBTNfqr2C3/kx/JcTP3CZ9lfw91MfSl1duvHNElQlsuJ3/zcC/ZHNc9C8lRT9ktNnnQ5r0bHh4fGyk6uzaP0QSv1u7lHM5aB1CcmVMmif7+Xu+m+LvuZWsZFmzKkH1uWI/N1y2nDcpR7gp/stZR73rpc6fdes0v6uRub+oID9+qnR1hNz9VMa3/jukq+WheWz9T8aIwpO6QeryF8cMdGjzR+pjoXA8da29uWU1nPEMq9wnTaIWkzS6yRrCuZ5f25eG8w6Rumf5D3y+ejdduo7ePyiX79K1pN97Kafk8zrT2f1ZC4gPFyvh4r1zopW9T2IUzIyedqWOLspF3kORlb7G+jDKnDMtlGKbiffB6H1ToMMwwNNW6grMTNFNXXRY5zjlnUXIPo68i7dNuyrqnOdQ9b7YeH7bdjiOw07aQdW0s7+qvtmPVYVcftqI/p6CS/2U+XMs+SDvK+8p9ZypRrpCxcK2b6WateDyaYznFBoIuLYp5pH5dpw3BDRKRhYGSo3X1ZrhGt9o8jn1naVrueiYWkz0H2jzaoXFP4f65fz9pPYT3lWlZdJ7l2dVx3OYYDqZgv9fRiuvARyzH8J68YZf9IGDZsJJqP3ymf6/er1VbTX1pN37SaNhyx31Z95Df9m2U=
*/