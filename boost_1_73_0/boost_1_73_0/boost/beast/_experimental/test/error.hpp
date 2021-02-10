//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_ERROR_HPP
#define BOOST_BEAST_TEST_ERROR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>

namespace boost {
namespace beast {
namespace test {

/// Error codes returned from unit testing algorithms
enum class error
{
    /** The test stream generated a simulated testing error

        This error is returned by a @ref fail_count object
        when it generates a simulated error.
    */
    test_failure = 1
};

} // test
} // beast
} // boost

#include <boost/beast/_experimental/test/impl/error.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/_experimental/test/impl/error.ipp>
#endif

#endif

/* error.hpp
ntfabZrQb2R7r3sj2WKcszzNSIR2vN7vKMR85HJGVUH5mhxnEMhnI50O3W850PW01WlOH0592NR+QZ+t+RitJbgWz8oH9h9PlNfUvuNaysOpK8UElKzbA08ocES6E8Aa5NvSLqzd5oaNcYTcfitm5eKIE49HLkU0bS9tclXIgzW5DWVWW7YW2zhCbgaTqcNLNOJmdVsvmq9mF8G/X79ddJ86Zb3p4arV9+2yVdnzIL4jBZlSFZbt+GgxV8gSZEjkGmTBjR8fHL9lWDzAixA2TaaH66V7MfZqGtHzmw4zXPvoLVZxt+H3KbCq9D5iQGPniCbj8XjqdwLlYPMpTXqdit9+zxMimRj52DbvWNO2J1YjRlND89d9eHmM2SPUsdis0GjEOPdU7aA30edhu7tdsR0Ey2XcfrFJtt9sXvHN1lCVX/gPxL+9cgUdLP6sgxhnICBFjBYCFcwx0h4p8RgcWEZ9V+NPouGH9Aj8NexVUbqHHZ8OPV6AU5VhyMyOXUQLlpJPQlfcIJDLEpQJzMox0nvJ2R1MhnQn7aiowu7704k9p0mfhsNhb0qWHWHfjtlXKIwF99teMVKP9TKPz/cpTDWazRCHbUc7ySOKxxWrq/SMHT4NBjiBbxKc4ggABtgdRqnemMGgwoLNhl9z
*/