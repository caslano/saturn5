
#ifndef BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED

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

#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/identity.hpp>
#include <boost/preprocessor/empty.hpp>

// BOOST_MPL_PP_DEF_PARAMS_TAIL(1,T,value): , T1 = value, .., Tn = value
// BOOST_MPL_PP_DEF_PARAMS_TAIL(2,T,value): , T2 = value, .., Tn = value
// BOOST_MPL_PP_DEF_PARAMS_TAIL(n,T,value): <nothing>

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/filter_params.hpp>
#   include <boost/mpl/aux_/preprocessor/sub.hpp>

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, value_func) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_1( \
          i \
        , BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY,i) \
        , param \
        , value_func \
        ) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_1(i, n, param, value_func) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_2(i,n,param,value_func) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_2(i, n, param, value_func) \
    BOOST_PP_COMMA_IF(BOOST_PP_AND(i,n)) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_##i(n,param,value_func) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_0(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##1 v(),p##2 v(),p##3 v(),p##4 v(),p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v())
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_1(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##2 v(),p##3 v(),p##4 v(),p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_2(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##3 v(),p##4 v(),p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1,p2)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_3(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##4 v(),p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1,p2,p3)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_4(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1,p2,p3,p4)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_5(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1,p2,p3,p4,p5)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_6(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##7 v(),p##8 v(),p##9 v(),p1,p2,p3,p4,p5,p6)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_7(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##8 v(),p##9 v(),p1,p2,p3,p4,p5,p6,p7)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_8(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##9 v(),p1,p2,p3,p4,p5,p6,p7,p8)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_9(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p1,p2,p3,p4,p5,p6,p7,p8,p9)

#else

#   include <boost/preprocessor/arithmetic/add.hpp>
#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_TAIL_PARAM_FUNC(unused, i, op) \
    , BOOST_PP_CAT( \
          BOOST_PP_TUPLE_ELEM(3, 1, op) \
        , BOOST_PP_ADD_D(1, i, BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(3, 0, op))) \
        ) BOOST_PP_TUPLE_ELEM(3, 2, op)() \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, value_func) \
    BOOST_PP_REPEAT( \
          BOOST_PP_SUB_D(1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, i) \
        , BOOST_MPL_PP_AUX_TAIL_PARAM_FUNC \
        , (i, param, value_func) \
        ) \
    /**/


#endif // BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES

#define BOOST_MPL_PP_DEF_PARAMS_TAIL(i, param, value) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, BOOST_PP_IDENTITY(=value)) \
    /**/

#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define BOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(i, param, value) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, BOOST_PP_IDENTITY(=value)) \
    /**/
#else
#   define BOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(i, param, value) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, BOOST_PP_EMPTY) \
    /**/
#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED

/* def_params_tail.hpp
rsBmDFJ5DmNxJe7B59GB35QXMBDTcDWuws9xDTbg4oi1aMB1mIUv4s+Yjv14+MMGXI4v4RXciE0YiLMJk3AzHsYtWJnj9mUcjNtwOO7F/O8HfsNtfT9ck+P7OnbCG5j//SDvu1zI90OWfD+8hg3xEM7Ew/gZHsH2vPkorsZjuBGPYwa+iaUpyFs41IHfJdzO8X4Sf+E4P4WD+H44jVs4nt/BXXgGD+Df8BCew1v4DyzF8f0RuuLHGIDnsR9+oiwPL+AG/Ay/xs+xI/X7Ap/FbPwML6GPUl/GG1WZW8H4XIyF7Utr0juU1jgHltWs9S9tHI/kwb8FkgykVFLWXPv4JPtkn+yTfbJP9sk+2ac/Y3IgTfiz+v+5s12UNt5ECd37byttjVYSa3OVvvxoORcfR0oj1pZzy9gH3nVIj5B+3fuFRMVrtUUe8x/C8sOQ+EP+ejJkPd3RCbvgal8NDeoC6xkXHzfVuB7HIq5Hb4iXawtU1xJIPE3nQBtQaygQf4uVcpmvfQiStnWclGuilMv969+UKyQiRhvG+x9K+czbLUvK11Niut1Ia5T9802B8sVqpz44jmteL+Uyrlfdb+sn9xJoLutpQlrLeoLuWK8nRJtYhJix+VmHDUhRMWHj9IWu31JP88L2yfp3k9az/hTL+uO1U7Txeq1p3RWLsP3V15pUVF2Lor5/gT56mtY6RhtNUuJyHdgmFVnGMOZv3bH0l//KpOPvCI0llqusa7Jp38nxVdlYr3Sp13ipVyTpReW4zzHWS6+NCAmLIYBN7YwWJR5f3OPLHAf0LE0bktd4lkbFyF7vD7w9qVmjFxbNSNp+z3a8b7Dx9fsXjzuumjknpecn34dFj2qUTVvX+HqP/hG1rgzP9Sqvc8ue9WTeUWIdjsrrH0z/8PSv95blJi2pV2Nv8ija0CvLKq8fWDb5Oa/krKhLNf65855nfR+Ob43yek7XAW4JnkuTj7h2WFo++5dbGs0OYzlrvTEj+X7D4YcXJPbePf/1XWdo45dWXu/srv3+qdHjmpeZMu7RGTe1H3K/COPrHy+/crqrNvrFOd9NC9/TYBvrHGFczrSqLxw/PrnWkLMbJuzPbjqKh052NJZnb+e+uffbtflw5c1LJyNKRXB/if3GeOi2FzcHzHUo80vXCN/tsZd9+TJ7z5j/drL7mhZvxt6fc3fTwac31XvFGFvjdd3ZSfPv5TQ5/eGKbm5eV/zYDhuM2+etitUOhfj4nOhUtnnbyXW71y5+HLbZXOX1Jd3De34/99fDHw5sMzB28dFDHAhllNc3DH3bwWn+z682yPyogef63p2I5Rm3f8uWm4Ovf/Cz66Dz090GrXc7RQzVuH0m12vqnlkjdfdPSQcWvr/o7iBjLIjXBxzY2v+LX1/pdWf782kVdjRaZ4rnhmrkdwCj5Tu8PAaTlMlLrptqgcrrj+Oj2BKd0RvrYSv0RR8MxjY4Dn3xLt7QyO+A/D5kkGrx90VZTy/+2Qn7YQ3sL8sdgE1wILbCQdgeB+NIDMZwHIITcDjqcQQuxJG4DEfjJhyDu3AsvomheAnD8EsMx/sYgWUoYySWRS1WwiisgeOwDY7HTjgBu+BEqW+ORn5fME7qW5u/r0p9Y6W+8VJfPbqjATtiAnbHKdgPE3E4JuFUnIazcDouwJmYgrNwM87mv534NL6Bc/EMzpP6zkdHyrRA6rUQG+MibIGL8Qlcgn6YLPV7FkNxKY7HFJyIy6XeQRr53cKecjyVwwCpt7vUuyHWRw/Zv42wAzZGf/TEbthUlhuokd8pbC7LfQQ7yHJdZLk1sTrWwtpYGz3QTdZTR5Y3m5Qiy9sny3NCgywvVZb3PFbDF2T/pGE=
*/