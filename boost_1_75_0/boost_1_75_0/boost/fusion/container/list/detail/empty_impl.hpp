/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/fusion/container/list/nil.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    struct nil_;

    template <typename Car, typename Cdr>
    struct cons;

    namespace extension
    {
        template <typename Tag>
        struct empty_impl;

        template <>
        struct empty_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
                : boost::is_convertible<Sequence, nil_>
            {};
        };
    }
}}

#endif

/* empty_impl.hpp
14ru6efYME/9UIIwNV6+E4+YuWAQMDPvRFZHOHnXPPQqzP0UwFw2dPFh9PBG/FW1Jg92ReAvyuyGoV05pNdaiK5MtR5Z/pAbIFr1EPRaa4DjfjGnFRBhNmYFAOOVo5px9x/siVle9zHU4884B1mKlCxFSg2ABsttIIieEGw9flsgr9H1KtUVUF3KSgUdpIwdzjp8CGbDOterM6RYAC9GNad7DOnuJqUEfRz/xnl097RS6DSjhHwoAmpcgxxClIvmWMNyJFYqdVUSi6N/Yye62xUGmBQVGdcr8KTQyGg0rqN4cIaExnXF93uuRN5riRyFjKJcZgl7nvy2g1/yAYwXh5FbTXGWvRYfmvXmc+TXQJ/r6e8fcF+P3OvfR5IbFTRj2XPkeyVI6WDeXZ+M/tLRX46UPweOfUfJFPSXgS5hymABvokuCsjPMvKzkvysJT/ryU8h+SkmP2Xkp4L8HCU/Z8iPhfxUk59a8oO/Z5o/R01+tOQnhPyEkp9o8pNEfpLJTzr5gc/e5c8hnyjaUaoP0SCtsf8uO8yf50PuKBvIqqlNF9wD3IituAZZxvWRB3ej8YNk8iCJPzhPHiSRB9H8wT7yIJo8CFceoFvke3wEkHIoL/E+KUE+byeH8AdzyAPyPTpZyx+kkwfk43aymj8YSB6Qr/jJKv7gCfKAfCpWxowmD+4jD8h3TeVq/sCbPCAfnJMt/EFVd/yAfBFX
*/