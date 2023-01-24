
#ifndef BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) /**/

#elif !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
/**/

#else

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
template<> struct trait<int> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
        typedef int type; \
    }; \
}; \
/**/

#endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT


#define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(i, trait) \
    BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
    template<> struct trait<non_sequence_tag> {}; \
/**/

#endif // BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

/* traits_lambda_spec.hpp
I0xWHnQHen1El433IUzJcy37KtfOnmyVJ3l2bTFzVmKbyTbtE/D9WdtKjxj/DU51730Y0i0F+zuN0OEswJIuzeXMTbdhxTsIQqSphi4bxhdEl/zrjB7BHq8ekh6mwCht5AXzwNBtM4kdDT6lJA5JibDQDFxL+RaJX/aYXjOPhEhZgdJpPbwkgwW57IZOOp8WumsocQJWEU/3v2Ct9m+gGDpYWIENKCztY9PZq5AmCeb/qE1HKzJmJfjO/JcURLPqKyNc97FnbsQ3YRosYu1s6lOYLVqSHMibOKYfVehbRWOVOnw6nTncLtP43dMCbtU+sppcHXjcd23w5p+x3otsmxWe8ZzRu0VcIpS2x9cXnkn6Kx2pFKr/bI/3zj8T8ZVYC7DHO4JuE+Sfybu/cRN1rlaDxb12y3VW+glIwZNYK/c1+NkecYWmMAZ+vpBPyDbJ82oVfHf09jxKoLHEVr/wTPne2Fz2A+41WjZwWtfqwwnsR2fvV8qIKZVdZMCKUNsERbct+I61LR3ULvz87TD5s2Vxiu2Qh7MBErm2AC6U1M37l7ajrnRMW85uPdVzHvGlrNxxiUb36RP16NalCsC0YjOwNhx5kASLyK4OeRBZAXsyzVArquu+YcNpkdJYTLKbe4nr0/MuuNtzr1+D0MTzvlzU54jUSqRvutcMXPpzwGFIyPi8zGh75rdMIzTu0MtL+fgFM9+zK3Bk4hx8
*/