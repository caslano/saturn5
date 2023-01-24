
#ifndef BOOST_MPL_LIST_C_HPP_INCLUDED
#define BOOST_MPL_LIST_C_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/list.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_LIST_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE),_c).hpp \
    /**/
#else
#   define AUX778076_LIST_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE),_c)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_LIST_C_HEADER)
#   undef AUX778076_LIST_C_HEADER
#   include <climits>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER list_c.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/list.hpp>

#   define AUX778076_SEQUENCE_NAME list_c
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_LIST_SIZE
#   define AUX778076_SEQUENCE_NAME_N(n) BOOST_PP_CAT(BOOST_PP_CAT(list,n),_c)
#   define AUX778076_SEQUENCE_INTEGRAL_WRAPPER
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_LIST_C_HPP_INCLUDED

/* list_c.hpp
bqE4/yn0B/UL32DMEMZfzeTX0pI5YInYh1dXL52pheitJ+UGd29vbnlC4dxXr670X6PJeGS+2uHJjmdUQ1F8jZEFXATkOr/l/wqJeMEw2LOkwWb+0Jur4NDiZT5+NchQOl0yqYA72Gcx4sxxQrtnCuAQJjmQmfIWtZLBjAN6O4x/Z2GhFffkF02lxnq1vZ1UIPIzNhJTU5Fx2j5L0ZMi15LNCUIXT0Bx7ey+RBwfsUMckKuArSk3ZP6J8deZ11CkVr6CQpG/C1RD/BhnKK7HkkN8GhnMM02sFC+ZZilK9okNemqEpH+J+yqJJ3vy1H7hdCmI0niUDsCWFBtXNo1hUfrw+oyQ7n1y2WYw+d/o3L9MMCv2lXWQ8bY3g521/2CpBlvypK80t4YMgYREokwOobrkUoiGuxAp5Xv8b8SK6mexLKncqWQXWol/2+pJGvV6dBeljhuoJF6kUX0jnTQsvX7QUbJj5i3EVvjYG1WrYCulJshBoqImE1s19bsHo+eKWHS9toXj7ltKFOh5OY0OBAtZ3zja6JrftrXLZuwLGnzVPwcm/Uafg01QvENPG5yeTanwpm+EJIM6Ks5rYCef3o5yGBqeTO/IcYwZEEVvddnPVd23CxFszXoGkoHaN+dnVtYuXZrhj9D3HwxW1/CL2+2qJ2vLoxSXF1OUmC0+Ab3ShPEzqJXwmH1sWebPbhLX0y2DphR+xa9eQj2g
*/