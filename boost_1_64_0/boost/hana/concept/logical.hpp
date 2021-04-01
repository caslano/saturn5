/*!
@file
Defines `boost::hana::Logical`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_LOGICAL_HPP
#define BOOST_HANA_CONCEPT_LOGICAL_HPP

#include <boost/hana/fwd/concept/logical.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/eval_if.hpp>
#include <boost/hana/not.hpp>
#include <boost/hana/while.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename L>
    struct Logical
        : hana::integral_constant<bool,
            !is_default<eval_if_impl<typename tag_of<L>::type>>::value &&
            !is_default<not_impl<typename tag_of<L>::type>>::value &&
            !is_default<while_impl<typename tag_of<L>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_LOGICAL_HPP

/* logical.hpp
8f5c+1kxZYQ3gkuV+bi1Soj/p3fAX/v+eQFtLarhyL1qbWqs5cpJZUSygQu6Kgb6PhfNI5gpDhSzQdTerRMkC/PHnvvWIA8EjNb5iZZ2vsl7ib8D8Xd95gtSpmr4CVp7R+axLhmOKR4lrWvb4v53qY/92yPLqPUjhErv+0rgoGZoazYRTJmDvWePDahuLCrqQ6HnCjAc8SuQ+e/wnYLYAE1+Sntl4m6DhLwIi08mWkHWDMuz3MeOvL/A/JFYUETIPLZpy/inCZT0n4GShq8wGngOPzT9xNOxI+6ZaxPqp68Nb0Geac5aVaboYZ4ZpTBqjeB7qOPvK+t4GbLCdYdzyeh5kPjqYKeCpZH8iEAulORb/EkuEY4j3QCQNqAwBd/FsFZGwtcjxHGxQ7zpVsvTDMpbfXfcJeaSzHoqOmw3cK292VN3ZmZerWsdq5y2dzaxCNFb9mq3WUxbJ5WdMjFLYnyL4/TZfN79dhrJHoj4scSQ4N6DHTtLjd/hdlPifJubzaSVQh0PA/4MbxG14gJjD08DQ5iGtu+RII3jxBj2bafrhgH51ZOgdRoGug==
*/