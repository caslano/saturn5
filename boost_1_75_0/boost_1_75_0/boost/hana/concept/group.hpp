/*!
@file
Defines `boost::hana::Group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_GROUP_HPP
#define BOOST_HANA_CONCEPT_GROUP_HPP

#include <boost/hana/fwd/concept/group.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/minus.hpp>
#include <boost/hana/negate.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename G>
    struct Group
        : hana::integral_constant<bool,
            !is_default<negate_impl<typename tag_of<G>::type>>::value ||
            !is_default<minus_impl<typename tag_of<G>::type,
                                   typename tag_of<G>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_GROUP_HPP

/* group.hpp
wJpWJtgDXR+iMRP7Kyz4hsthoy9OLbUFZ8HFVYx1aaXosFAFDPOEjrz89dNoNtZfPxR5/el72msAJ00DwWeKi3ZiHngP3Xd0inod2lLiotVzLwXSghksbJLyOYyFUdC+ufzVYqpEME0tIJtmhmfxb3FhTLcX3ijQ9oxG9TaGYfx0bJ2LKHIZn5u+yGCDqtFAwCiDQAza0OEkoW/BlCusghTHbiVzhF7Wy4MUqElLUtpVDyjuegcwz32j3Wp+tqlF3Jmb6C9MNrXBTfzannTTyawPfOPVAmvWtdb1w9WFFtNCa1bLequ8Nz3rA+lzCi2s7g2edrM7h5NqkrpmG47EPQy6SXWag+asNh8Qqfp2j/jnUTA0emYHyhq3C2WNbAHPkMBWQ0WCyezS4bjJwva1gaIxm2YHGlliv8GwXWiEIdtGh8mVQD/A24vwXqIUpgG6T2DD4WXwC0jMzpwBEj0zkXJC09jfKJy2NJ6QQlgrwF0AOtKKErkdlwW+QNotbWTP8fjbVk8PBjGc+A3SJqs5wWNoFp9AAjWwP0EpJV07Jho4vi0GKaEprht5BXsEGDhzTqSKmWcHAOJ1Z+hhOOS7YyKyqa7tAjG6qgVf4CjCWN+ljRQIug8oalCQbmEX8VpcAv09mddk+2lCjSR6BvBxG3/0TZ8dCGbIrWFlJKZSRvbSNUTXAboarsGr+RqMEI3lCYD/0kZvHGsx4yiz
*/