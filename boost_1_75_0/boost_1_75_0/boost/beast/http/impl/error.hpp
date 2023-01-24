//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_ERROR_HPP
#define BOOST_BEAST_HTTP_IMPL_ERROR_HPP

#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::http::error>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace http {

BOOST_BEAST_DECL
error_code
make_error_code(error ev);

} // http
} // beast
} // boost

#endif

/* error.hpp
mTkoIoOTNEJEtniqRqounIo3+3NmEFF6OjyV1dPoLXEGZlrocXw6Pg7T4+B0KqPQ6+fwqFcemoZveyhxGz02Tw/ztd1KxpZCMra3fNpZD2xNTcZWRDK2Ii5jm/Vue2Vs931qlLH906azlLiMjX4aZGxPAXs1UK+OCtIhxI+8cQaWDB15v9WII+8em87M4rhzNeHOHyaEy9iEe8jz9OL6kbeaH3njRCbJ2FJsRhkbIgeSsdVqMjYkbH6wchlbNaILt9XYqaQxKzm/YZItrJMF8jygAFDGRpteyNhOqTHK2FbruEmxPR8pYzvYSsZGhLdRxnYwTMZGnEWwX9pEMjasgt2d25CxETFYG13G9pzfIGMTLWuNwlAVUQ3I2NxgdYhz9m4c9eYgl7EdKicZm+bGU3UmVNt1TqVYWZSx4VyUPYO8wqQ3+PROjJOEjM04vYU2qIPO5aTGf/LCX8Rpa0EugucdlIj/Q46QoQsXsPF2LekKAI5kIbvwhlzx4sBT5l9vl2oa45vN7CbKjx62knjfAWLwF0trad5N1STNq1fl2vL3Ss+KlOflQH6ghR0yGyzaWccqxdsTVPrPKJXGVuMFs6t3ZHVYZd9vQKEb1RfA+t5eSfXVhYHboncQ3Nj01LzOp2cNFweDQvw8oKnUFN4sMWxDacjmDm4gXjRga1fgbeit2e8AXzkM1cNbrESX+7RTUSB5mlEgGdsAap0h
*/