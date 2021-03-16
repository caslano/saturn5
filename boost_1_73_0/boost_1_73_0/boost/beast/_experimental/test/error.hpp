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
4HpxrHfSb4LTb9E5F4d5GetLpxiyWx9sK/+Ex6jajH+tq/CmY8LpctNqgA1Mc0hYrgfye03VJ17qw2QwBvAr6lKdeV5oE0YfzenxSG8oSJ09UuAwoa2qp8JfNswNUlJqw/vIAaFKtJfnV2Ik1jav5GjUZSjuW+9GTuFv12WU96zl29Vlwl5vBx5Yz78d68LnzvMre8xgpNP12ip7EulqxsdU1I3xMMrpxNlNv1G4lHq7+FPvpx+vtWyw8/QYTmk=
*/