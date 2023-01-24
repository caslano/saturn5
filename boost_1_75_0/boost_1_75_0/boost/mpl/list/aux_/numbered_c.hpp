
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

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

#if defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i BOOST_PP_FRAME_ITERATION(1)

#if i == 1

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i, T C)
    >
struct list1_c
    : l_item<
          long_<1>
        , integral_c<T,C0>
        , l_end
        >
{
    typedef list1_c type;
    typedef T value_type;
};

#else

#   define MPL_AUX_LIST_C_TAIL(list, i, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_PP_DEC(i)),_c)<T, \
      BOOST_PP_ENUM_SHIFTED_PARAMS(i, C) \
    > \
    /**/
    
template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(list,i),_c)
    : l_item<
          long_<i>
        , integral_c<T,C0>
        , MPL_AUX_LIST_C_TAIL(list,i,C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(list,i),_c) type;
    typedef T value_type;
};

#   undef MPL_AUX_LIST_C_TAIL

#endif // i == 1

#undef i

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
5Zw/Jdgjci/4KCRFeP5c55YTyxvJ8rzM+i1riJoJMYie0BYlSGuM06MUG/evS0vN8hsvZP+hJgtweBeYXpeL13R3EvurK83M1hYdvQ9njLnZnTl56yBRtr5wTpw7BgvhSnNLSvz37sB5JQnUbbaX+zL74lkbOVuUjcbpNMxmG8fG+MNzrPlxyhsX4UiW6MqaZCtevVif7xBtAXGcrCU2w9wfpWaWOLlSCez0kb0FxSibUwZNEwrlcnKC5Is1YUyVg3Vzn7Ir9OSULvbpvaCpXnge/flUZXQLSMZiCu2DgDsgAq17yGXYTIBE/DwxgzOuqCxQ6gkk7Y5oNYBFEywuf+TC80bxSky4hvCKH/BLXDnoT06P8vei/ov5ILRrBeMSopP6HRejCPkXAf9hu3tE0YGg+aC57PtiFrMPCfn2CENqXMgEEi6AUTVyeTEF1gQRZVbPl4oElLxll34sxWH1CXfRFsNRaSMKLIqFm0UcCnlZD3IP1VF9tVPvs2aRLV/VihuutUDoHrOdgRlHc94aaXlC6y3312JVDE1RV8VRrQTpxG6+K8hMzMleC49ZpUt840bHb12bGm7tqJQWJS2Tq4e5ZZzITRWyL8tMpHEXLePEhYyNyPxljcvOJFgkF3IknhVdcWYj8Xzqe49hczY5uU0eVfOKr8E3EptBaz13BkSGasJcvDt6Za48f4YlTPruPtm/thz7HKZCYIPv
*/