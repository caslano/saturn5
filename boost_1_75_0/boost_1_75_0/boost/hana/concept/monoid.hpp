/*!
@file
Defines `boost::hana::Monoid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONOID_HPP
#define BOOST_HANA_CONCEPT_MONOID_HPP

#include <boost/hana/fwd/concept/monoid.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monoid
        : hana::integral_constant<bool,
            !is_default<zero_impl<typename tag_of<M>::type>>::value &&
            !is_default<plus_impl<typename tag_of<M>::type,
                                  typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONOID_HPP

/* monoid.hpp
QTqhtTJoQvtOk9whRqLHHZI/qWz4PMFX7n8ujbg/0nc8UjvSrBsJvAxIuzKhHKtQjm0px7aUY5OR+p3l2ORybHI5tg/pG95B+8qxff4d2D7/m3i9VnoW6rYauvbzOFBxJvl/ZRiKT62h/o0wQFKvlf4lf3KxL0NtAErwiepYZZzcbJabzLxFLfInJk7teUuWSv1a9aHfdQrQ24OCv2F62/S3C9W9PNewrWPrxlGuBmb0jUTIMMpgjOVLp0q6uoDLx/Jf4LxWccfiNIt6BBiwGYXAbCDQHwUE+If0+iAemsgpRXxANQzhtn+A2pjVbxojI0D+C3GpOwPlKDCbDoqjE1As/6xn+kEOYuP1elP4z6Ma8pGHVC5B5C/B/liCiF6CiF6CiF6yjqNYJycDUsJbwchcsOHqSJlIYykarpeAgJwKdAXvNnT3N1yMY+AW//1iR+S7Vv/+Bhqzo+oSlgD6+ZN0sr8BzZ0+C5Af9AxSYAjJMlVvAfWvkqAsMcvNINVa+HdgSBwox29Ew6uwAsMLDUKHLDObDtqt81jPv2Aqz7Ooy6z0vLqstOujfw3tnf1c5ExxqaUWd3GTI2wI25sdveQ9cM9Mo0Ex4Zy8yOLfYOPiqNupSCg4sxpcVAFBM3k0iVHoQ3+ftS/HXC7dQEsBNpJKO5VFA3J40Pcj3DizxOg3L1FTqv3majXfDIIfkHOi+gE7DSD+LNQVoCNV
*/