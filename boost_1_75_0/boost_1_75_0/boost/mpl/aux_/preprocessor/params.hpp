
#ifndef BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

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

// BOOST_MPL_PP_PARAMS(0,T): <nothing>
// BOOST_MPL_PP_PARAMS(1,T): T1
// BOOST_MPL_PP_PARAMS(2,T): T1, T2
// BOOST_MPL_PP_PARAMS(n,T): T1, T2, .., Tn

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_PARAMS(n,p) \
    BOOST_PP_CAT(BOOST_MPL_PP_PARAMS_,n)(p) \
    /**/

#   define BOOST_MPL_PP_PARAMS_0(p)
#   define BOOST_MPL_PP_PARAMS_1(p) p##1
#   define BOOST_MPL_PP_PARAMS_2(p) p##1,p##2
#   define BOOST_MPL_PP_PARAMS_3(p) p##1,p##2,p##3
#   define BOOST_MPL_PP_PARAMS_4(p) p##1,p##2,p##3,p##4
#   define BOOST_MPL_PP_PARAMS_5(p) p##1,p##2,p##3,p##4,p##5
#   define BOOST_MPL_PP_PARAMS_6(p) p##1,p##2,p##3,p##4,p##5,p##6
#   define BOOST_MPL_PP_PARAMS_7(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7
#   define BOOST_MPL_PP_PARAMS_8(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8
#   define BOOST_MPL_PP_PARAMS_9(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9

#else

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_PARAM_FUNC(unused, i, param) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_CAT(param, BOOST_PP_INC(i)) \
    /**/

#   define BOOST_MPL_PP_PARAMS(n, param) \
    BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_PP_AUX_PARAM_FUNC \
        , param \
        ) \
    /**/

#endif 

#endif // BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

/* params.hpp
S8CHDJEtS91mOsjwZCVunn4xrEhhlpt0UWw2mO7Mc2EGA43eH2TxdvkkRD1g4YG6hBnFWoZr3EQWdKNF04OXoN/sJCMSGu47NVi0H/gT3JO7FCVeVgnT4jvECp1ZtXTZTlLxRymtUho+rwybFkw48Gy+or62KOlJP5U1YmPTu53jLI6IPSVqslUqNNc0/XycSu9dhjuKO5rCr7n7YqZDmSpUAsupuSV+abkE3ACO4IRphpjsZkLqPLvqKrgPiF2KUQRim/TkF4wK9/E2rPS7P/J3ushP5e5F+40/VuwvDKEKwI8ssXCJLkKoEpKFGCJpOYdMWQ04uMDwR+vvBioCG3n0HkEfL2Bhed0aEzE6eI/ZTpvih3SM9VMYL/gHfi2g5bOpq/Ys9507KhxVfy/RdJ7nwqYFisffCLN6BPjB8cpnLQjmWOlCm101+PiwMmp7dgKQ26H64fB4QlWzemt4Kzi+hKrH0YOo5q9HIDH/Vs4L5hfQ5P4/44yAwN+yltVXy3+q5fjuxgoeXVdN9oppHGNpz1RIceUoh6E0jmorxahTfcPqVI96Ggtspvl3PhwSylwGsOg7Twu23q+fzVebVljVLAwNuah6SppkP2IXYSjNNhVzcDgqAlGLpah6pgHMqqP5+ehckJyMVsOxZPbybLRr7rv1O2voRsYTn5f1Gc3R9yn2gCMJ9eoHXlXWVk0ik5EfsyEhgvmaaTio
*/