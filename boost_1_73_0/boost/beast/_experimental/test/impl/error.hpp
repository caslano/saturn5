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
AF/BvzfOx3yAf68C8/BLgXv4+AbcycKvBLbx8Q24g49vwNex8kgDb2XlsQnYz9rHNuBnyaD6A/Az/Psd+HcM7wE+yOLfD/xR/j0KvIT3B+BKPv++AN8XfL4N7Gbt6Xxgwd7vZcAFDFcCv8THC+CTWftIA7/K7DcC/5jPt4F/wueXwD/l32PAG/h8CriFjQf7gL/K51PAr/D5FPBFrHyOAp/K839hccknGJwGPJv3B+DwOmv8
*/