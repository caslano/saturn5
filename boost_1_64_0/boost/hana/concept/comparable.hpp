/*!
@file
Defines `boost::hana::Comparable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMPARABLE_HPP
#define BOOST_HANA_CONCEPT_COMPARABLE_HPP

#include <boost/hana/fwd/concept/comparable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Comparable
        : hana::integral_constant<bool,
            !is_default<equal_impl<typename tag_of<T>::type,
                                   typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMPARABLE_HPP

/* comparable.hpp
wT313GZJ9wdcw0QcCZQtRxMxoczMMySInX3oo6Eq8bLMzndHht5TEBrg5B+oF6dihhLy6yRxvLKfHk6Fdz+gcERsTg00tPmWcVVjpYbjp6aBTTW0cPsVYWc1dqvcpLxXfRDOrKSrZGQXuovG1TnRW4mJNd/8OmcGQsUQ/o1kxRmyoILt9M9UcvXkGa3TUvfHwwr500+tQz+dtvi0I4NgybVwl1qHkVesy5BRmJuzNyYT6/QjBao4/2MgB1GcjOC2Q93V5xjlE9SQeORKAYFbuVZnK62mGlV2wvPT0VqgFQRZoxu4AREV2G78/qzgv7bigKeJrncW8ygbtrMtA5vt+95ve5fBshymwczYlKfSFGD/jxN63B2GQh9OxQhS3V0Ml7NOVbKjSG+QqzPXglAkHyYrY3zxkCeC6KGVCPCxpiQ0K8mprx+ksGCLPLWTeVgmj4VoRnHqTY98eOOWmEJ5vrktfn6bZiu+vejlbIz5PH3a+qHQiMS+1uoTET5fyVp5bum9L6O+PVCaixhm10/S2eTONFRUxWsXd0hAODXxRJhCNDR+W5lPiWerkA==
*/