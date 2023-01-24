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
8fM8QdTCPmjpECdJabWfpzfyEG6h42/SHMqjyC9vWibx13cMtUtFnDGJXwBk3dQ/dhKHyI9puf3tyN45B70jyatYzz7S7II60zxBLuhDOOOlRmeQbym2dubOd4wVPWyLWdFPL21jRelj2juX8pK++zYvKWuOIdeSmL28N0lR9gbZBvlvRls4FA+5VtiQE7uxs0KKAAFu173SRdHmrkqinCCYeIxiAm1BWyhxOINV+Sxa2LuGHLuAzxkoPg1bZTIZOFM83TOhPxRP5KC/C+4sMgEMJoGtXTfJBsHoj75lQXY/vMV8TAkzEl9AQSQVvxB5102yeOOMpiM/y7Fq59mWY5WUymvTL2qBnEX97kvCCZlG7HzGT8ejNbR0+eInaPWw3C5uPOp2jKwiJ2wUTliXcxZCTBZxRvWpo9jotBPVpvPC8R+pHbDyFBOIoVjE3EH0EJIGastFDQpCNLYkSdH2XdgS1X4Sf6LO8OvAn5j6V/Wj3r/XfjT1r+THdvtX/bLoX8MKc//u+9HUv9tO2r9eooZj+eaKTYrAqgK5Dd+srb6n9ZnTRPddl+l0v4hpvqiyXfA0qE099R9tUvxapPgJogPipgfIYasAiAtCsxU8Vdkqj9occz+O1uSR/x9GTmPlUeLWj9DqbBdeutQsEIO+UtDxwXFiXv2OwZh+zw4I6l0bMaGFKBnuzwgJnUpIvyJItV0cQ7Qvp5C9SRYA
*/