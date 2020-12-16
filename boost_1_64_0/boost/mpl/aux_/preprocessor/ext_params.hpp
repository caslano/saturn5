
#ifndef BOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/preprocessor.hpp>

// BOOST_MPL_PP_EXT_PARAMS(2,2,T): <nothing>
// BOOST_MPL_PP_EXT_PARAMS(2,3,T): T2
// BOOST_MPL_PP_EXT_PARAMS(2,4,T): T2, T3
// BOOST_MPL_PP_EXT_PARAMS(2,n,T): T2, T3, .., Tn-1

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/filter_params.hpp>
#   include <boost/mpl/aux_/preprocessor/sub.hpp>

#   define BOOST_MPL_PP_EXT_PARAMS(i,j,p) \
    BOOST_MPL_PP_EXT_PARAMS_DELAY_1(i,BOOST_MPL_PP_SUB(j,i),p) \
    /**/

#   define BOOST_MPL_PP_EXT_PARAMS_DELAY_1(i,n,p) \
    BOOST_MPL_PP_EXT_PARAMS_DELAY_2(i,n,p) \
    /**/

#   define BOOST_MPL_PP_EXT_PARAMS_DELAY_2(i,n,p) \
    BOOST_MPL_PP_EXT_PARAMS_##i(n,p) \
    /**/

#   define BOOST_MPL_PP_EXT_PARAMS_1(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9)
#   define BOOST_MPL_PP_EXT_PARAMS_2(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9,p1)
#   define BOOST_MPL_PP_EXT_PARAMS_3(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##3,p##4,p##5,p##6,p##7,p##8,p##9,p1,p2)
#   define BOOST_MPL_PP_EXT_PARAMS_4(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##4,p##5,p##6,p##7,p##8,p##9,p1,p2,p3)
#   define BOOST_MPL_PP_EXT_PARAMS_5(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##5,p##6,p##7,p##8,p##9,p1,p2,p3,p4)
#   define BOOST_MPL_PP_EXT_PARAMS_6(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##6,p##7,p##8,p##9,p1,p2,p3,p4,p5)
#   define BOOST_MPL_PP_EXT_PARAMS_7(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##7,p##8,p##9,p1,p2,p3,p4,p5,p6)
#   define BOOST_MPL_PP_EXT_PARAMS_8(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##8,p##9,p1,p2,p3,p4,p5,p6,p7)
#   define BOOST_MPL_PP_EXT_PARAMS_9(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##9,p1,p2,p3,p4,p5,p6,p7,p8)

#else

#   include <boost/preprocessor/arithmetic/add.hpp>
#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_EXT_PARAM_FUNC(unused, i, op) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_CAT( \
          BOOST_PP_TUPLE_ELEM(2,1,op) \
        , BOOST_PP_ADD_D(1, i, BOOST_PP_TUPLE_ELEM(2,0,op)) \
        ) \
    /**/

#   define BOOST_MPL_PP_EXT_PARAMS(i, j, param) \
    BOOST_PP_REPEAT( \
          BOOST_PP_SUB_D(1,j,i) \
        , BOOST_MPL_PP_AUX_EXT_PARAM_FUNC \
        , (i,param) \
        ) \
    /**/

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED

/* ext_params.hpp
xoHohkOwLo7FevK5qi/98A1wucTPV6IHrsFGuA4bS/98Eymvp3zemuJJbIZnJL5uQCWeXmV+BY3rA2Lp1nH0tVaxc3Pc3J1lzbCKm/vw2mjSbNLW+fb4uX2yT/bJPv0nJgdS1J/b/p8aFx/5h/v+lbZ/hmrsf4Ccr4agE47C3b78jl80t8PCIiONqza1Maw67W22McJQPSZ5Kkl9z4sYG+1Dc7k8JSbRVMrVCPdQrvTPzeWKjJ6iKpfzHyyXedw3bTGrckm5ZX6CtOUDKY8HZezKfJsvVG15WU6k1T08YqR+6joekzrOJlUmTSNlUkf3bHMdJ8WZt731eHdHG3WkPfe7276huo7W297qmYIbpP25jqQcE8cs5UqIMZbrwW3xomz7++ZtFFOwHGfLyILkGJgpx2bKJXM59AnhJVwO9fbIRf/StsZZF3/cuo12r412csm1Y4s7br244+uLO5698PH1xb/+wMY4H5vXJdwzbv/Dnd49/lRmi+DMQ73KHfvojTYlNy7I1nUPd41tF/lOle/aU6QaxnaaaYqQdsx4rIYTsSbGYEOMxdYYh4E4Wdo18TgK9RiLBpyJCZiOU3ArJuK7mCTtwmkyvns6VsAZWBufwidxpsQDZmEgKu3toTgXR+E8pF60D+U7GZtKvVwlZqVMnVTjk52xG9aS+Ia7xDc8MRC9Jc7hh32xv8Q5RkicYzIOwCSJczwv8Y1NOARfx6HSLh6G53E4fooj8B6ORAfKOAor42h0xTHYAEOwEYZK/dgf8n3MCySlfhVwtNSvkrIcrIo10AXrYA1ledhc6ueF3bENJmBbnIrtpF3cXtaXSDom69sg66uIMbK+/bI9X8NqEhdww0OyvsPYSuICwXgMR0p8wCDxgUQ8gWkSF1hniQtw/Mr3K38/LfuzHn87oDItkPUvkfUvleN0mRyny+U4XYE98DmJd6RKOVZiOKbhRFwl22M1LsQ1uALXShzkRczCdIljbcBr+BLewU0S39iCj1DGl7EebsX6uA0b4nbsgDuwO+7Evvgq9sddOAEzMAn34EzcixnFGCdPm/+/Zqz8/8o4ec2CCho3kh8pmKRbYI+F2Cf7ZJ8e3vQQ2v/6eN0fv/a/AWP799GG8rultHFYKle1J+hCvFu28gmZEhaTQP+OMc9+8mRZ5XmydZsCeVryg5/4VYE8rVr6+BXIc4DlJN4ukKd1S99WBfJkkSfv6wJ5fFq2Lbiug0qeOwXytPH2KVjmMMqTd7dAHj/vtgXX9ZqynO8lj/Qux8WHeLeVXOY893+b50lTFstyND/8Jo+szHSNxJ7qpvuTZZey1faz3eYp3Vh5/fNd33bZs3LTppFfnR06at3Vy7baQsVvq9hoI9loi9pq29hqOxW/bVx4m7Dk2sDFbaMWt818m9eTF9APQ3qTlE26T3JdWEHjQwoi6UgppAzSOVIeyW1RBY0/KZK0kLSTdJaUu6hCkc45cz5x0OSi86cO+eeeC63OOVt+6vCnnXcGs+z8807+TsMUzCSpzz/PMq+cg+ai9XmowwWHQs5F5TzU+hy0GOef+eedLL/Qc0+r886+5LM697Scd1qdc9on+2Sf7JN9sk/2yT7Zp//v6WG0/yfHG0qk/z9T1f/vI6eyLuVNfaxV8XVl8Orf1X3QyqpNfaw+VvW2HlOu+ZT30e0UH5VknA83zfMUjIJ9sNGx0gdr1WddReZ1hY8vl/H5lj7sc5ax84WOP8+Wf2cguHH+vPx7F3P/vMwnyvwNq37/szI/QeZvS/7JMp8r80kyf1Xmw2X+onn9xvm2j+X8w9S3csTX3sf8v9jHPHee8vr2TYdeXqXbd2TjqZib10KP3Xs4fczpZeU=
*/