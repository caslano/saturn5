/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply
                : mpl::int_
                    <
                        std_array_size
                        <
                            typename remove_const<Sequence>::type
                        >::value
                    >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
S9hePqwL09ibMLr1gCOqmAhaWLf7SK5O9/f2pWO6G8PPUfaTWKvpG3f2l3jb20xiByis5UnsQMbIBZTmQYx5XPtSe7DERe2z9hCJyVpn/FCJ46lDVDylcZjEsdYJO1xiWOuEHSExUbusO1Jh+px9lMI8p4RSfh4lcW4Fsj8fI/GIc+WxkutwrjxO8zwr4WdTEg+cQ0+QeOAceqLGaXbM+pMkLs+hjJ+scWy/srynSLzDufBUxYfPhacZXKvUEHcLK0V+v9bpkqvJlkb4GYSjR2n+w8+dFE73sGXbOMvA0SAez8828OCMStp2jqHxzaq4LZxr8A6PT+f5MNuFp00VWfbzfRxOBhG/gHAxMeTKoPQvZLzdgGxHCLuIsa3w/EzYxRIjV2Gal0hMOpC1lzKO3Z/r4TKBZe3V4N15KXpHQA3u8NG7DS6P5ERbIj9e4ef5lAdDCQ2z9HzI0ATfGXBVgNNviOBnRAHexez5GVGQk0Xja61rg7zHN88C98GuC+jE7StZZ9f7OTGmY9o3+HHRhoOJ0/OioC5g300Bvl0TufOzoiDXKBflOH4LcnivEa7tCLtVYehixG7T2Kg8D92uMP1c6g6FQRHBEMe4N3Wn4uimn/TNXYSvDq/JWA0HK8bvNnDz/s09Bi5KY45r9xqc+dziPhP39Bh6fwC36xU1lj/AXG9PVdx6Qv2DJtZs9jTqlW2l/iHNiedtmO/DfkzEQfyRAF52t6JnQGFcxXkswMErLekZUBhXcZ7wc6Jt0/OfMK7iPBXgqu0Kxnk6jIs42D6fCXBevbKVY2/ZLpapfz/bkcckMN/ngpotm/QsKIxDJOJeCHPqnPJiBCciyrp/yeBFPfYY3MvE9Q9k8Ua8730nr/g533Xvq5qTHQPx1/y4erff62Ecxw2nzM+GiM+lk4OhvN7UnC+vtzTuy+ttwtdfbgl4hAqPXrbCtxdWHWgwyL+jef3IdP3GlvLa5d0wr1PgMr1HmuKwJ4bJrevNMs3/3me8zGPMB+oYRYh9yJhX6hmW918+Igzeg6qxjxkDyJXPpj4xsUZR9eFPFQ63txn7TGGbqXJ/rrCKQymQ9guFVxsua7+UGJ5om0U5bn6FON/1Ze3XBmYbz8a+MXCqVPLTt4xXG1T/3+ExPVnH5RXe1sUGa7+XXIPuJf5Ax2VH+I81PzLmbkVl/Ekdw1ygRHPxnxWGdYHxrLEJazconbHo2NmGj8fGY70+axx5XBd9rdYarVed5rakHZe40RKfy8bDY92Eyl5RTJ1KcnwfX/O6iXGfniCKM9bYTYg8vTKoBvcpWNC9XA8/X4nme3qW5OcrHfilliZ+kmh+iWU5/qTR/FI9fO9wMub16ZvwyRVOcx6P+9wUGm+OlHqW7FpOWtTVsyRrpuykWWbpZWXfncqnWWKpnqVlOkstsTRrpu6k6elaclnWTNNJA59J6mHNtJ00UDKZ13SdNEt3Lyntmr6TZlmoTu7LMyiNHkdmJAw6d8+wHB9mIsz1RCc01oXNrPCaM1pswZhI6c6i8HpZXk/PqrGanDPPJjEqGqY5u8RU6+TnMgF8pAh9Gm/pEz9nBx4SwLzmkjyZitjcCtvOadbJpnkI26IJxSxtoe8pz0t4xaHRFLH5GPM2c0darJvfxLjdLkCYeOoPHtTX3AsiTlObMp+zFvJhcJJ3S1tI/cKKE2MJ6RfxYT04fsh+saiPExS/KzaM60GS/TkmrEHPybQX9/E4HmJ5uvy458IL4+TzvW7F4WWCWnfRo3DpS8KXCOLdVLYlQ7jyE5ZhqSBPNPpwaeTkFIzSW8aHmUMw8cv6eGGr22iKz6BxvSyHvJwmEba8D6NnDSsYWFs+V/Fh/vo=
*/