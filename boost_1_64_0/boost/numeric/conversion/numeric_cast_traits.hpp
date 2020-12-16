//
//! Copyright (c) 2011
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NUMERIC_CAST_TRAITS_HPP
#define BOOST_NUMERIC_CAST_TRAITS_HPP

#include <boost/numeric/conversion/converter_policies.hpp>

namespace boost { namespace numeric {

    template <typename Target, typename Source, typename EnableIf = void>
    struct numeric_cast_traits
    {
        typedef def_overflow_handler    overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<Source>           rounding_policy;
    };

}}//namespace boost::numeric;

#if !defined( BOOST_NUMERIC_CONVERSION_RELAX_BUILT_IN_CAST_TRAITS )
#include <boost/cstdint.hpp>
#include <boost/numeric/conversion/detail/numeric_cast_traits.hpp>
#endif//!defined BOOST_NUMERIC_CONVERSION_RELAX_BUILT_IN_CAST_TRAITS

#endif//BOOST_NUMERIC_CAST_TRAITS_HPP

/* numeric_cast_traits.hpp
78zuDPorD+LIVlkMm3Y4fD3acj44DkE7NP71HvTLBVqTWVzUiR4x+I7hIvqTLPSdZj6ykrDQZ62mkb3N7ESPjjeR+yVWpv7cXrJImHbNX4hLFswrmF+wAFkETHt3rNBO62XzMhPIHLDQe2oShbgkstTgGEXRv8/FNz6PHK46VEdl2JPfl+0z7tumHGDafaqCechsMO13mGTRMO23emT1WTu/rnPGeI71DYf6i8W1+umX2yjzpnl9XjKz+vxkAWYNm8chh8At2lcxO//Z/m8xrwMONYdZeAbHXfTLbVqTWQ65Hz4chfp+dKgTLG773pwPYXccahSLq32jaGPk8BONH4tzHm5ivCftXvB+lKBF+w+vQFvu0zUyZuOOX1qDufQQc5BM+06RLBamzSUhLkWI85FFwEK3B79QZkAoUz0yNxfZ3aC9KbvW6+vGu/oe05zPYFjeDvuOYC6lOdQvbxn2bPXrjMjhL7STTPvelywWpn3vK5j1tdEvVv0eEDIbTLt3WYhLJIuGafeACGWmCHE+srww7V5bwax/07EGTPuOVrCkv438cmr5JZM1ZJbtVcVraAvZMIthhTfNdmOe/YvcyUJzD5BFw0Jzpy1ORcK034WQxcK0/RHZ4qDloM/Pi9XdhX6xOFUETBt3MhtMG3eyaJh2zzpZXph2TwZZPEx7/hJrS3atLalkf1oM21Uj4TnmWbhTnWZxi/LtXgXLaF6mh8wG0/YPZNEwbf9AFgnT7kUli4Vp+2LeFn1fLJRpzWReZoJgiYIlkaX/5jUb/XtOvz2XUWYWp2qjDDtRsvQQ5E7W1mJY1XFfVEd9WZ1qIbMqDUaehmVHfmTaPc9ksTDt/hfBfEKZqUJcGtlZZpY2E/tgG8vpxDWrrPS558e+d9AWsoHMWvRpfi9o9DfqM2aduxafhTiy1sxq3W1cAvVFOlULZhl2lDeehUjGy3Q99BnrBNkWZm+tWmk8+y2K5hks9Dg5lSwPs7I1PsmKtkQ7lQumnVuQNQljZbpn5cH8jHOq/IgLPUdwk1Vk9u99a1v0C1lWWOgz7b3ctGfh+8g8zN6O+/wU2mlzqs7MrBvDAogje5tZ4293b0N/kqHPtHfkpJGhLdr7YZXdqeowm39irvGcfLK8FsMeL61f2vgthlO9x+IWDZjaGX3mdKpLvExLgTrYjuJpLWcW/+fu65iDuULHtkzZ/CUQR1ac2ReHD6RgHMji+TjMdNXCXNLiyh5Ino/ccztVArNrUQtrIweycsyqvvjVeGcimY3ZwrLtH2DcyXIwy+/fjrH1k7Vktqn/1HIY9zxONZfZklObc2P8yOoxO1155wH0S16nysmsz5GS47D9kZWEae/hIPMy++5I5afIz+VUo/m2Oec941nj+Wgbsxg2pPC2HRiH/FjPyLR7/chiYdrvOwRLE8q0FjCPSyAzi0sU4pIESxHK9AmWKpSZJpi1oJAfmSeTYct3nrwAK8HitOsFiWT9mH2erTLWswDZ5ODYRtC/xxY8+gdyKOVUTmXY/GVHPkAOZMOYbR91eRT6rLSxLmXRjl+8gvnI7jJ7al/cDm1JcKoRzKqqc8Z7tsrQtgnTjsvJomHacTnZZothx84OnoD6yjlVJxa3vuTrnujP8k6VxOzGyVoN0Z9kZm1RFZxqELMHzX+vhHaS9WeWyXGgF7a/ik6VzOxc5q79sL6QmeUXIMsL084tKpmbmywepp1bCOYli4Rpx5hksTDtGFOIU5XN41yCucn8QXvzx1HrZhrPaaviVCcthr3f87uLyK8a5ieZdu5EZoNp10rIomHatRJepv5MBLJImHbvK1ksTFsnqptbgmCJZGb1JQlxKWSNg32Wmf5dbUE=
*/