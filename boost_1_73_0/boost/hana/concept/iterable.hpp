/*!
@file
Defines `boost::hana::Iterable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ITERABLE_HPP
#define BOOST_HANA_CONCEPT_ITERABLE_HPP

#include <boost/hana/fwd/concept/iterable.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/is_empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename It>
    struct Iterable
        : hana::integral_constant<bool,
            !is_default<at_impl<typename tag_of<It>::type>>::value &&
            !is_default<drop_front_impl<typename tag_of<It>::type>>::value &&
            !is_default<is_empty_impl<typename tag_of<It>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ITERABLE_HPP

/* iterable.hpp
ypFzD5WcvrQkrlcjhDSnMGNI+6DpXrcPPsj/ekZsAr5HxrLwHY5NbAnSKBJ1A5IRNTWV0SJKQ4fYn9Wrwzw8hKtnwlYVzKosxUBRbTslMXHmYv6l79utIz5nhauDI0kaBcdXusPR2PYqX+woxq8qJoV0SzAKaGW6Rc0cJz2ybDNz2a3TVgiyR8aT7JOdzhEge7XfqIgvjArZz9adXs3g38MKuEt+926GnekjkWet32hKF3Oz
*/