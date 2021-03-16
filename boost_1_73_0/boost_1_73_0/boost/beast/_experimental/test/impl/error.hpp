//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_IMPL_ERROR_HPP
#define BOOST_BEAST_TEST_IMPL_ERROR_HPP

#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string.hpp>
#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<
    boost::beast::test::error>
        : std::true_type
{
};
} // system
} // boost

namespace boost {
namespace beast {
namespace test {

BOOST_BEAST_DECL
error_code
make_error_code(error e) noexcept;

} // test
} // beast
} // boost

#endif

/* error.hpp
aAbUJ0UGuSO0PYpJsnBuTUPj3MXGPoc2QLRtYisfqOOOnH+q2qS1Bi8ZkxvcNK0RoJz4qS75P8L1zukYCSTdIcFw32YdrLrVcmcZirT3oQF3ofoSLuzIVdqMCBQz03V8caTEPV2tCs1xxkUmi4Ims0pFoj7QT7W6XhuheEqpTBXMiEC/sUk/zAkqH/8G428U/o4MHrIWZ9V+J6YqnUudw9Ut+FvnnCLqmUFsbWo77t0wdA536trMBj9H87Xgp4k=
*/