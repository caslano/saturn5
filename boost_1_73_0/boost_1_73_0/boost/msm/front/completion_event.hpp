// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H
#define BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H

namespace boost { namespace msm { namespace front
{

    struct none
    {
        // make every event convertible to none.
        // to support standard-conform implementation of pseudo exits.
        none(){}
        template <class Event>
        none(Event const&){}

        typedef int completion_event;
    };

}}}

#endif //BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H


/* completion_event.hpp
bAXOR3jgHDNaV9YVzJjcMmmrNGFWIFmR7dFBHTZpnnStj+Q3/euoH1lRfxo+HTE9zz83gSqLQkjNkpNTJW76v/NPpFNiwk+VWn0jlO7U3Va1hk8dN4x7p2LOM51Ec9wgpd50bhiRTEI+eG5Xbxpr26/W7/66Ryu+f2DOygGZ7e9+JsNBLXm8TyfpXRHz1SYeZi+PXrQl7kM5SncpdcdbOlwYe8aGA02Hr9mjN/4RezeZsZs5zrOXcDnexvmqWHkP+6fHqIhd38SI5Dba0Z9iG7oP/tOyvouHi/LJbetw3/BWy1cVLnUZe0kZuu3datkoVr36j9ht5GSZ1Gk+qJFluxzx2htp3zodaHgNWCAfnOQMCE9gSpQyygAXGgilrEAGqxAiCRxyIdFLf5ffuQncaF18cZwT0VX2SvIiY1UqcicnaeYIwx8KfCZg4JxUta62KQrey1LG9Ulweli8K961VK6L9/iuBYEp89hxKDUmB7dag1/OVP8V1ohcmjIVUMF1ykuiU8Ex2DlGB0onKe9apkSIRbK/MBDHPQiw+Bx5OGLj4Sq3k9l8NP3y3hZO2/8Mtm2ibUkLDZLRtDCF/3ZGwJvHWuK3Yjxh8p/mEkwbotuBJNeO/7PLwJ6DjeW9V4WfJ5IO9+WByXS9h4Ro
*/