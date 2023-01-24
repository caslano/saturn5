// Boost.Function library - Typeof support
//  Copyright (C) Douglas Gregor 2008
//
//  Use, modification and distribution is subject to the Boost
//  Software License, Version 1.0.  (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_TYPEOF_HPP
#define BOOST_FUNCTION_TYPEOF_HPP
#include <boost/function/function_fwd.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(boost::bad_function_call)

#if !defined(BOOST_FUNCTION_NO_FUNCTION_TYPE_SYNTAX)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function, (typename))
#endif

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function0, (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function1, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function2, (typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function3, 
  (typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function4, 
  (typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function5, 
  (typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function6, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function7, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function8, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function9, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function10, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename)(typename)(typename))
#endif

/* function_typeof.hpp
hb5//RvQfKs89Tg93/6Hng+cgCeTTgbnK7ZPf7Hqcrh0zNI5qiZXNnZZQb4CmDQ0k1WfyarD4LiXEDsHSt/1uVs2Bq6jY2DGhhjOGxVuUE+BBzeQouTaEJ2/qYXBIB0YF541LImQexen//utyLyF4eQ2yW/w54bj9HyG0ZmyxvaYm9FczmBhLt9Jdz3rD9DQR+ryNRrzk2mnTAT2UiMv7GQyfRGE9OsPRUGNBpMEAQ4HiOHEuyF542HsXLE11TNoenWShYnYtDndRbHwqL+j1N/CfdDcVtkRoe5DwmyVaPxRbzVuHrVks3eJtq0+14q899SCeoH+r+CrnAiARZGB7EWUBdhl99TTLgO2/FmN0We77vGBTs6XK7bket1l1ACjcEGy1wMRqGwRwkWNPPLtGBPbH41LBB+u2A7th76WLUESQ9oR7t5EthJ00hSghdIOgGHFEbg/pUOGQusA7tfDComxanw8nH+sA1jjrfLNv7E1/hnXGLbGq/tp/LDGW+Xf/8JDQ7F13I+GFroh+J4WoRTgzH+HF+636hbZUGTajzgKJwOGyxvBd0/auhihXLx2XYxur/jB3aw9hLtlVoG7eb+yee1RcXfdPj3uRv3Fcfeafb64SwhLzfMNeGg3bcDSI7ThujXRM+MoPSPZhlxBRyXsusG8VdaguNvlcok2cN7y89iy5A+R5b18KSR/uPz9XoHLPwG7VmBRtio1
*/