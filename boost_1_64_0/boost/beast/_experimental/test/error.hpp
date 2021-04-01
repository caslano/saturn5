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
HDOzpZFLCHa+lubNWhMmLjwnCEwl2RGIjTNDvi6p3glIHRQT9iigNHQvv3kdMSms5reeWjFWq+RoeUSH8YbFrL3hwCdcUYjBcTZ8VM29SrQIrJwUu1H5d9t1pefWKCmS4NqjmOOeN/XSdgC14ZuCmKrwgI4k3c8TBUErg8Boz4h/UKff8yiGFYTwVzi5uN2TP1zF/6WCxozYZREwd9UwpsEQSBQcvZTnXRz6S2xxTa6A3MN04AWyS591HcWursOMnJdwcFnTWfbDs7bgxBznNMk6mZeflYQttYK58emwaaDNV0nsQlWjACNZtVvViCPeWTrk/q+eB6WS4WFxPYniwpkWU2gHw9awINuc/s/kKhV/76mpIytfSSY3JYejpMkFgd+R7l7JkBjYF/vZeRq1sVpcUEOivSOVVDI5zlYI7sLrjABsQgjLO/YBqPRZxjI1ECVIUDkd0q6U7mqqGCavfhLmVHWGQUi+PBueec4Wp53ZoBqzyx3FUlWZjGuS8iwEX91bK+nYx/+lnHAar9ctczqfC3aslb+B+kISKaLH4o8GUBf0XVDaYBhA8Q==
*/