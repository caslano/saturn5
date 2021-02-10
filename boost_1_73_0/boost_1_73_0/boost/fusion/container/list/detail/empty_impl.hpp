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
FCa41N0yWhU6ghxxlnkWh7AQyAE6+RGIuc2y0OcxdSbO9RJKpiTg2q3J6fVZFAIxbK83YYPJHpu5iUja7PvB9PPoesq+743HveH0Kxuds97wK0723WB4BlsvYLGY8ft1zBNYPGZitQ4E99Waz/dz1Gh8I0IvyHzO9nD3nISn2bqz3LPak8i74enaFTG2N46eaW3kdxQGD2weoahj7vogsdBdoWYmUXALWzvLROAnz8XyETA19/mcnV6PL8b9iTP9PO73zvpnDf3gc+9L3xn2pwP43xkMnc+5GN6FPBXw/5EIO8sPjW94COpaHnf2sTzEn9X07o2veg6tY49w47V7hMtsjnKcL5cTq6uiw/peGIXDABrm0Ow3ryd9xezEuRpNBj+0Gt8wZlFzJZ8iLQhsZtK13BialzFFDw9qpv5+MHz9amPq8ei0P5lsTh1HHqh3aeqc9qZeAWQEptJvsf19s6rjDEdf+hcXzsXg46njtGBRtNk5TO+4vh87aeMb2TdvAatOxAJGsyAKF/ZahtZP/Wnv7Gw8GJ6PkCg1A6jK6OJLf+z0h6PL/iVj/d7AgQ+j8VcURsK39qXf1mrarMDafDd1S7YG3ebFpmWUpKJkkks3WZYGLgF+Sk1pzOM4ioutCNGFhlUWpEKUFkVl
*/