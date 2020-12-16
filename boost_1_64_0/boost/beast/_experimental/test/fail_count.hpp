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
cl+6xrGfU1ZQvLh0yZKSnNTjU8p4iNUJ/MxTp9zo6DkVXjr908rcOinne+pYf/4eDK+HTlpaeplbp+ICTx3rz5vo5Kz10Ol7fJlbJ+nnnjrWn38Gy7iHTp800set8wtPHevPe0GdCz10MhQv6ST90lPH+vNhMF4XHazTN1XpLJ29F3vqGH9aobMPndJLgjqVvXUlxZw4Ibv9wXDwIzoqsJi7eUaBaVS2zldcHvK+y8kdPX54HpkYkM7nwTBe4aFDBjk6B4LPuNJDh8g6Ot8Ew3iVh07fNKJRFZ6kDaH1xwbI9Z7a66vTx747NlztoRP6DmLxgodO2Dso/1ofHT3re3Qyr/PU6eu8oyM6U1euD/leKsipabwWrM4mP520Sp3ooD83eOmkZeCP1dnmpyN/6qCTc6OHDi8Bvt/2+7TXRyfXpVOx0Ucnreo9kXmThw7Z5TyrXmee5aVDGUPH1u8NN3vokMzo2Hdr6S0h79YMUw8U572hdv2Nnd5Bpbe67UgtlcmGwTS/7eC2DvnSh3SwOpv8dJQOsUF/bvfSMZ8Gq7PNRyck7+44uI1Cmqtdpbje4eEPOjzL6pRu8vTHtr2aoBO408uf/vhTpbPNT4cwq73IQkCvdl4fhVltgru9dQiPGXe6MTFg9/bK0T77d2v/mtuQbvgR+13dsDGM8F3wA3774MttEzMG0BRze2P+A/szRISPI9i9BE8zOiMCtewYSERgJffMPrV2D6BiOxY00tjF4h4zupnGfDLrf/vaua0btTfaTRpbyDnM3jn57n3yw87FiG5oz6m3+2ytJXL7nHRS0uAybbH5bvimj9z0csfLjpfsN3YdWdMeccT7wPqF+VGFeSFSS33FGwlzyvdhYSa8aTh3wtwl1oTZZLLGp+SmkTFPwjzEmGe642DHjIYbuzFHHH6eR/jN80LG16Ib2b2VzDUR6RCsJ074zZkfwd905cWLqz7JJkzJnUP2NpSbKDsOtt2YB9j9rRv8gNmcwUB8lGflRYuMfxp3kx+dZLZu7J5WMYFFxYuhkw5/MfopMrufkdW4WHO2nzc6dQ6bVscprYiX2UsxHnOs3ZfKhlXp16gy/+O0XpEfxs3gaJiE+xTCYfYAq9zr19TteWVLFuUVFpQXqAy0Meln0lRp6LhrZfdKG2PMD0eN4JkvRzwc4bV332T0bjN6O6LitAcbb8yCsoLK8MZpnPJto5McdXrkCRq7ZKQ3qh73TkXH1CPHndkFrI3GPt8z7tpEFbC36QdI3cgnAl9GRjr7nJpZ13HaI3Sa0e0W3S8QY+LYunOAy0Ta7jP4qtHpGWXMNgyF+OfsEZhjz0lLjgjaFUQ+HNHF9bxSs2fmZfw32fiVGl1lt6LqLCxjFx9dFbelRUWFJmr2XfCG0flFZGJgcmTlew8XJjwxxp8KXH1pdC6KqnoG457OmHIgqLucPSpz7D7x/4g0+1ga9xvRXmjct46uei+bMmHfy+OM/fHRWYE6rjgWGPdm7aqx74R72Wl/xE7KnznGPjG6G67XshL+o4jzAysiWwRmRHUMnIP4jfWT4iaev+Bd3i5gxonZW9HZS8+KuX8SMh3ZlRBqz76t1rwfmSXzHYYhYs8eY29G9mj0FFNH8w/zPquAbUwdVd1h/7WzTBrwntNey3OIm9t8qcxdO7vHp/3Gg4/duK/3+KjfOGv1x02rO368u0nw/vKrkpsNe7vNz25odvE7W7vun+U37u433nzs9j3zHlc+dvvLec8zqP64uN/4+n4zJq32mNp4+5DjkJWI+bY1YG03bAJbw2YwBcbDdJmHypwFm8P5sDUsgQnw1zAR/ga2h2YvHXg9TIa3mfva28Fp/8A+Ck8MMk4=
*/