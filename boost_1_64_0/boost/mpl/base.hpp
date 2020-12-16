
#ifndef BOOST_MPL_BASE_HPP_INCLUDED
#define BOOST_MPL_BASE_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct base
{
    typedef typename T::base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,base,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, base)

}}

#endif // BOOST_MPL_BASE_HPP_INCLUDED

/* base.hpp
wTmPmIn21PsWDrQOWFKL3glqVM47As5lJaeB+bOx0LmsJNrdqpdh85Dh/yOALsIIOxagToOdcKfRXlJgjhbADhFkTseRinL1k1yzNFeqyUUoK1jHl/imDkaVnd8jOkDKXarlfjUc5XCsRgwsPRNiu/5Y/dam9POY//nLQj2Kc8Ihuk3dI3oiKkB8Cq3j21JH/Gw2hGO2ei6wtgtQYTashidohHT7l52UIt2iowXn6xTeYQJPwt6q82VBV+AAHntq9j8nfOh+f278FxLyPIxtPqmkOPqYGHMUVC+ePZmos+nttMpbttb3COeVZJTlScKCTZwgQzRKICt3VAZiQXIxYhUvny+KqTw1FJsYslPZ2C4+JcH4PcY8nxOiPlmeeXjYWsC984hQ86UTHTGL+wMC/DFQJ7/6Lox7/oMOrbXY1qzZPXipjryy9Fu90dIQz9u0FxbTK3nr7xBD737hT28d/tES6p6AvspAKbbw65nGRx4SQxpVjbq27t+o7Ma/IdnUa2FYV8w1f5teimdnwGO5Ed6+nIwQgA0udrg7VS8TbZg9ULqWkpm3xLiDY6Fqet30Do9mZqDf38GJZ25Kiz+3rvhAzpExvmOw/5XvWV93+gTh3fswI2/Df+rnudk56dAX3rUZzSU0wrZSQzW2xlY6GX0k5l7dHjYsjzj442bX2PnkQTL+mBs+avj/CcZ5KNUcJeN7Q2Bj2FFJz8UZuKO2pmJjGNeANKQW7iBail3kUppPqbwvMw2CYUiER3Kup88S9S6Vctmj5aseFj1C2U8jZahKm1hk9zgpwXT6vINnquJ57/GCJ8feRNtnou0bKbIHXRTax8sy+ZqVelybIWbf3RplnQMGZ+utEeQz59QS1lpGm1pGUC3Y6ycaLBgOO/rJiUDtE8HVw66yUZ0M8IMhAIgb0OP5YrTdRcVtuWhkyyEJIF5PBvGQAXF/wHjfnNlVXTeNIbY2uVCZKTSLCjmdlYrOenQUqC1uWugO56ryhqrQMvLu0QzbKsq3Mfw/J3dHF4GPU8JCmG0wRzvunw8c45rL3k/G79XBxnmMX4HApSWN6am8jmRp9dXshFR6GI0+3kBDgNeBRzjLtPVRMlbzBWp8npiGql10bujrbrJ9nIzOeFOwgL3sSodxbAq+oLlkh5T+qLdrim5MLp2B0lgON4vz1GZynkJfXS9mTCfAxU5qQyfXYaqTrNu47Xj4KL2qmPLIMw83+wh55ubYXeQZtOigebaR0Woknr+MxPW//XP1HxJi7Qv7wz6MFbjaL4bJ0cbCiO9aD0jHX4gtwHFhrTj6AI6HuPc/Uv0Q8nbs3WNEuY52XibwiWfYY7vgCcLe0BYw80Yyd2I/De3tYIbBWNfvADDz4YcrGm/JPr93eIq94iB1kTzc4hTyQ/hIpBXrgRl4rZXXthxyIPhq7ukmSiOfTchSd9DKYEVtWmmrN+Wp/Urv4gvpXXxh1nawNVDb63DWdh6TmXreMSpqnUJUMpvpbOXl/O2d/GM1/zFO/sNAVUXrxjW6194GGia1N/RpNWHZO78PrhbsIyAS478P98k3PaNF2pTHzf7XQNV+vxtM0cMl4bxOpbMYS/Hh7aRIM2Gbf0voKpn6CbGJvus2EDycDFHTFOW+hRNRQJ3aqsSlw0Sy6C4+zohBhMoZaNZCo1JB9V97rI5SvfbwO+OQgklzVQ6ePRcqmm2iTQHA4wKqsH+Y773ybKXUgTs7Soy5wX5dxqTWPfgQF3oY0MMC/SKFHi7WoqsP8kIfq9DpiNJcDVPZHeu0L3QlMndRaBGBFqFQ+Cd6oTWILmgIvQ6E7utO0ZAZTOswmNxiz6CY7I9mx/Kz9Tknlp+jz4RLhj4=
*/