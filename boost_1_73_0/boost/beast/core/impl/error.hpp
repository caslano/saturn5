//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_ERROR_HPP
#define BOOST_BEAST_IMPL_ERROR_HPP

#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // beast
} // boost

#endif

/* error.hpp
W5h72HCfW/kfvwNf48wNrrqHP6fqX/1z/tt/Hk4URhnWuisx6Yi8C+u2lXhh2O7MLi9sdyaGt1Y+GJdJWXF4YVhurxWGlwv3TyUZnhcy75Dcr8wk5W4dXhZTDINf4MwzE5W62BpvBrUiu/JwBhkSffF4Qsp5vH6qa/Ic56kFUPZoi1xXQjurBdcPTEEABEHMjvMstrIlaWnBStmcwaJZAgyAcT5yEqpMSG+g4NSQncP9hHFK
*/