///////////////////////////////////////////////////////////////////////////////
/// \file static_const.hpp
/// Contains definition of static_const for declaring static constants that 
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012
#define BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        struct static_const
        {
            static T const value;
        };

        template<typename T>
        T const static_const<T>::value = {};
    }
}}

#endif

/* static_const.hpp
46PaSKT14lJ0Ud77rZYlzaQ/84275jzkPaN8hRWaRZbDQ0my/B9kFjQ5m3n9bBBdhFMyId0B8Lg1S877CUmBaOv0WRz0f0y85jBQ+COX1Q08a2FbopSRmzlUijVSza9X2eeL+lsh77bZ54CSgzMkTHdZsYhriIB9hTAS3NxC74WJHVKmt9VFheETAmg6q9y6eZ/55XtaeaNcNvwi+xFuC3yLElIZhuS/K2EMsdL/5ObufuxoaxBKGa1WuvSMKJDWKNEjxiGUifVlEQsDf+llezoaTorATaDEowzFZ68lXQIzKWGN7m01yq6lD0rorzFh0fCBMhLvZSAYgVY6G1Eg+roS+SRYFpD25vwNHHQfVPhp1oythD7XaookEVNZgYIK1ZhpGm+pXyyNj8gabUwtMJZwhg5I3enOx+YimOmafFIlV2oKiHJqmWQDRh05o+66oSR6pAhQoa9lO3ms1+bFUcuCmQe+Il9m5IbXGHNdq6TwHdOzbVlt58hlFlhxAPO9L0L0XtsChrztrZv4nqPXt9HJpTccYY4oV+vk7xGqdZDTVe2IUofGqh28/g==
*/