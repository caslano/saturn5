/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_1226)
#define FUSION_END_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::end_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.last;
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
MB4IGgU0PH/XNHOiO9zrbw5cH5NPzDZoVbWQd2MO6aP9Tcp7c96lIS/a9Ns9dw849nxfChWZcdwavz/u0faLMz8RgTh0+y3bvQrSHyWTBShZkhzwDhz43Zw/p701Yc+dvNtWx2m4y32eCW1vPWpXwT5WwZKhLWrajEtTy7CKKNWLHN7ZCd0GlAL9qmhzbZplR/nzLka/qVghkH6E5F+urFZ0zP8o4S+L0Hmne9hz35DVLVnF2HsO8GmNMpzwhCy+Hwu057m08BIG53u047v3OIPAGA+oe+i3NtPCoI7hO1ezBDOaJufrbQzKwTcv5ixm06Bcf6yvGprhhZcz6Ku2JC7VPMEZMvqWHSG0zW04t4RDVuS9fZTSYaAgr7oLoUE7AKeT71MXmvQR0n5EaCbOB9Iu3ZXQzEQa+ShtuO/IXL0boZlwxFhPShvZsgIdz6MpfX8ICKR/9B4uHZ/SRjtwsmEHkjRSZXJo1wYyt3us638IHevShzOUvr9TIdAn/zLdT8/DmCdBGB62QIvWzrnyCsbTPC2zWDJ4fHRbx4ua7Bh3tvHdRJfnjIz0+5gFu9obvZKeuf3dxS3FYRCqzGfGy8ba2x08y+uRN6sDXoJNSNnO7kTsjt3TexjBZp6fpbkn2GbD18N7vNPmjzFtqk+wwOdNn4Z3r+5u7G/3yfv4MxoHYW3G6ybKP36Tzf4q0PQ3NyiLaOJLgGP22FyLjh9l4q9JcNRnB/0o5w0GeqAupHazgAdkSHmaGDPUnLsFl6neBmkYxZk69EYmnje58mAYBJkKRcnAk5RqCc6DTH2wzQGHDY77V8dnAKPbu2purFsyq9ORBauPfptIJ1VH+nvngN7uK2zfhXmkt/rgIXZcOG82D0b7w2F/D9v2+kuaPqyBF4rwEO/kVG2b2jOyl9Dz5rT0VF4ksI4+Z//3w1gU1sMAUydr0VORjTtCZAXMD9OMZ750ZIUFP1ASw3ikrpxnSZ57kZey0Vbv/LnFpQqMutF5qYsVaVymXBYV+PRZDLe6ZPHHCF6vTSMvFhV+6dQi4q2NOuHiCxaB9CzOJLuyCwuL02dOnTp/7lydS2TzYC+l56Nx4HsSzNrVwdX++TPDZ11txPdRLt6PGIwVKeIgYnBxB5YMPaPhp2BWpo/pngUN1oilMiT8XB+wck802Ckv5n2L8IYs90uuoLVzHXbl3MX+3gi49bRQ65HjH4PxG13+wGOlFEHpZyUL9KstO+Pz54xbGwi4CpcdBnDCPD5/agT+N31tLmVr7nublCdlMi/DrDAeQPadu8rMBoEpzQhdeUwKSnym1SXaF2kcQvcJBsWBltm+grLqcoxebPXqZc13xHmiijRmmM/Smn4wtrd3w8pAfdblwgI6bZZanXJlQzcrUMEojkK2ujUAVx7904N5NzzJanphqWouKHL1SqguZ2D7XrmyJAuKJI3SKMchhwVyyuHbMxOXt2Ay9JQXFR4z0OkCsJ1Sq3uknSQTPs9lJHm7/5vdhV0VRFYXiayQ+XmhokRy6C3t1GPbGceR28hmAFqdJO0bgg75mQwK4ZRpr7czggekwSDtrO9u1L5ka71R/5nOO5w/JnJ8pt9USyPpyOHwFMTuaDCuxwi4lPTWt64CSVfP9BO+xf1y6o9WRmmoeOwzWHrByus/1s9p+wD1iMj0WRBGIFId1IHTevK8HSdnX05jRgVhqHQssz48sbG9OwT1O6cdHG0ZkE9RvjRMfSmSghmdBaa9/np/MBwjH/rZunw5yxNPijyKkc/JjKEvnssDqhYVcZgGJdP3gKB2uzvbeI7DbPneStrIYzxSeayDNukIxvr9RpoZvv3/0ZfT2KTGeblg2DevqfDjyH4=
*/