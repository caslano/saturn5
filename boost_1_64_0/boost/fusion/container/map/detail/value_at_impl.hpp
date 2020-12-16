/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get_val(index()))
                type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
v95kbxR9L/or8+/vs65veOfrabUW+T3xbVK3ifavg5LclPnTls0/+O1OvX7qzqHJsS8uzbd3fWTvusD+deJTg5X54a9MWmzIjd/cocHn09cf+LKz/f6a75jmJ9V74ZepD84b+VyL4W96dKh0pvTXm5NN5VPvwbzQntXv2rE16fOoAwcq0mGmtymf3a/4Ng/5NeX5lf1HeuZXnPm0ves7+9eDl0zXBXL8yXH5KYFVyJMyma9D7sRH8QHeewwHYRwOxXHoyfauH087b3d+VxMWEyztwmHGwrbhFDqte0a66bxp/zUyfzYh4N7C3/ZuE/htTTjM/x4842TavHK6AF7HsEwawdJ+bGDeYt6jHdnUhuxL6E6YxfxMQi4hjNe6BOIhJPO/Dwa2Yn3Wy+B1IK+DyEsO/6cksA7vne9hbl/O4PV6wmHCNUIH5nVPJJ+EEP5PIgSQv8usY8C5vE7jPbfWpM//WfyfTzqzeS9E2qbzCJ5JrEcwEDIoC6Uyw5uQwuu5hED+X4kFrLMX1W3W+bzuw+/sTP7fTvCaSPniZUI26WSxnIF5VeaX4zqFZYg/hdezCSsJnr2IEyOIw5//vSaxPWgkdOf/MMJs/p+GCwg5hMvEy3UNByLbpaxPWMzri+h5hrLj/5r3cS1Emh0wjBDI/O4sH0KYRkhlXgZhAf/n4BmCe2+uYXh9keDL/8nkyT2ZeAgGuTYKSSau3rwm7jBMJVxm/lz0aYe8PyuSY0TZ3mTiInRnfhbvbyd4Pm6+fgrGM0o86N6HbUQ/DCZY2tNXEo+lTb2A4NGXZQjbWbYPxhFmEbIIuYTzzM9jHUu7uns/ylWuuzo8UdiuHsz/i8lf3Bnyyf+ZhEDm56ABz2AaLuD9TNxLOE/wVK7NKJPDrEv7O9dr5Iv/vfi/yhSWY3ndaDedH//7M+8yrz3p3BnC6xBeJ2M6IUXa6NfwfzYeRnV7fS7zvFLM13wdFHkdiimEmoGsi2sIxwl6XuueZBvIlw+G8joQkzE9EPk/C/cGIv9vZ7k853Whc3JOzsk5OSfn5JzKYLq9z/83X/+XxbV/Q+7vPtWc665htIOYmosTk7i8jx2dEJkQG51oev807weEqt8fMzE+ipt2mZT3z/C+cYT6fW6tTRwfryxQm/erIw+m5X0yTTVBbJJ5vSbMn2udnxTDWgZqFrjPnvdlvWmW96WaQVY3va+0u2YUfZ/1x8r7Z8lXmul9awN4eExkYoyOqRnvJ6H3w6r3ZbsfD+fe3NEUjsRzjniyTPEMHTG0yPa1kHjSTe8bxocXZiXRlNfw8exQVkgK1zWRZWdb88zy2mVMdTGvK30xpF17vbTv75B29RzCT8r+eMfavj80pFdIX9Od46UYk+BH4qBtm9fq53/HavoWBEibej+CN6EX4Wcl7eXWtCMNBilYpeuDA+lLm3mxe6C9rfdURybQ9UKTDz+5fz2SRGtjGP5CPjJs5WOSKSMljnMgfTSK5SOmSD6kL4DMY8dKGfoUrltsHABtmUo/EmscRhmX35qO5jkYK2Vbm0rdW0OsWZO23JXWbY2Ki45MMG9tyeVddP/KOBKy//mAM6nTD5D79QMJtQm9CVdYNvdda/qmlOUYL7G+T+6Jlj40jDOv2Xa5l5rPhdIvJn2f8rkw942R/a8Za38fn4VWuA6vkif9ezbzFB4vx2Gyy437B0XwPv2DzGPwu2jzmOYieVT11Ul30fb/kGeKyHoJ0sfH0m8kjrKVY6qwL5B1njdxXW5qXo4U5H59a18j0+sQec16pnUydJZ1EpR1ivQzSrDGnWdZjvRYznR/fp/yzGN71vJe26zCcfwDihy36YXHumm9Wfx/kfAM8yNkPek=
*/