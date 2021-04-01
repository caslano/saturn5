//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_FAIL_COUNT_HPP
#define BOOST_BEAST_TEST_FAIL_COUNT_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/_experimental/test/error.hpp>
#include <cstdlib>

namespace boost {
namespace beast {
namespace test {

/** A countdown to simulated failure

    On the Nth operation, the class will fail with the specified
    error code, or the default error code of @ref error::test_failure.

    Instances of this class may be used to build objects which
    are specifically designed to aid in writing unit tests, for
    interfaces which can throw exceptions or return `error_code`
    values representing failure.
*/
class fail_count
{
    std::size_t n_;
    std::size_t i_ = 0;
    error_code ec_;

public:
    fail_count(fail_count&&) = default;

    /** Construct a counter

        @param n The 0-based index of the operation to fail on or after
        @param ev An optional error code to use when generating a simulated failure
    */
    BOOST_BEAST_DECL
    explicit
    fail_count(
        std::size_t n,
        error_code ev = error::test_failure);

    /// Throw an exception on the Nth failure
    BOOST_BEAST_DECL
    void
    fail();

    /// Set an error code on the Nth failure
    BOOST_BEAST_DECL
    bool
    fail(error_code& ec);
};

} // test
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/_experimental/test/impl/fail_count.ipp>
#endif

#endif

/* fail_count.hpp
CCbAukcwvA00oZPJA0Zts8mt0JwRQdq0/hrVQ27JiuEcgtmszI6z/icUAlWO53F6aJ9OiWhN+VlCMd+G97lrNKCvLJCEx6DwEO9wJyBqWxXuLMJ3vKo/wHAMFsl+t9Ywj+nony3lTTdzhtLbJ0rEXkDtEV0XT3iCwmWPurn3RAylo+mYA7oPNU+kjZXutvpl5qCkaeceV3KUf+7Doy9dUhrF5rd/x8q1LWHDif5KDwuapqOLko9IWGL5EC5JNsd5BpbvgIUrxUHAyOVrB6ZCzCdPpq7C9tjp3+c25JY7m33VfB8e/PLH99FbdyG2VL/JCh5yXesLWEcvEZOl9FSassNz8Q0PDPo5U2E3MM7W6Vu/vUdZ23vyooBH52c/IKuo4AfdwpyWYwTfEodflrHmYt6jFkXIWUgAOPq/VYwDnQlV9vCkzaZ+mpltXQq0lZgGf9IBKt9FonocHDCrW9FBj2x/ZL+XurlJ5/0ieJgCfnIt+nMXn8S9xk7qcXKf2+0+a6xCtVdpeNJ+l8rID3MOhjPzgDhSDjlO6AOTG4wKeSFmoFCjAGvQ9HTFQg==
*/