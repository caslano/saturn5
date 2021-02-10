/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_END_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_END_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, Sequence::next_up::value>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
FoXJrU6tAMDC9MJLYG/hYRZ/Cq9TDCm+ste08BahL+ddmKpgIdQZj4OEichamwCjRGdlnrlmmbEwGtqJt6A5DmYtT3yKfMxgFa7Xj0ThfwSLKUQLOyWxIXBM/PYz1C858Pxgekfo8SP+zqon6khMZiIXc2Hs+DbkRD9MaBnXoWtkCpGsWZXFJUQ1gmrPGa5NaOozI5nODf5U6+Zms/QyZGduXwjm2O3t6V+3ZZdKwGAjJs+Bg0oiZp/cFaHN8GnpeONY4Wd48pS2Krui1OEy4S3srsB1uanxBmXAlN7Ky0E+0KBBlBFMu9JxUGmgDBKQIGpHUSdIEkJNRpIURWnI2JFIvlVMQAaEys9qxvOSGr2kMcuo1C0nm2qUsCJR7+zZYzYize6OWY6s9oQGsb08oPqgwbjkHHsHykSAlaoDUkLWraOdPY28hE3OCY0IC56M3lbH/kmkoLGg66U1ykjXEmWkZ8OaHFlsRfEUGSW9nrsb6/G2liLkEwvuHl3AClmH+IWWT+iZL+D3F7gYsuUq/BHFm2T+WL32Zapn03n5xF2oQjMLFz8qRqyXnwbN9/XO7qswLUMPQnl5NRpzALAW33d2TR2PTYLop4j5uLRKZVp9ztvnZNREHA/hvX/pHwDKz6Jamo+IPWL76PwI
*/