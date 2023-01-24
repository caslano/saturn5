//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP
#define BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP

#include <boost/beast/core/multi_buffer.hpp>
#include <boost/beast/http/basic_dynamic_body.hpp>

namespace boost {
namespace beast {
namespace http {

/** A dynamic message body represented by a @ref multi_buffer

    Meets the requirements of <em>Body</em>.
*/
using dynamic_body = basic_dynamic_body<multi_buffer>;

} // http
} // beast
} // boost

#endif

/* dynamic_body.hpp
Pue4ySvNv0dxS87kbTYYp63HE9Ap62e7SXAULDebK3eQcta8+i2aC2eyo6ACBh4ZZPMW9HeDcUfllTMZVUOl/vyZ5krcDclpVjpXUN527+jgDIMjuHiweUtavGLZ4yL15QAswlIeZyndMaXUf138TG96qaNgaLxvJJ5HdybHnxP9NXGFFW3L3halSR9TnwamIPOOZ0MBhnNUgflRwK2iz7lAc3aESVh9FHfoczRsj13PhiNZfhDeYMNlgRfYWeLEbRGHILlj4FK9fW96TQT//UZD2NJM1201YiiGyoPeC7iMUq9YbmP9SthkCGXUxQM3IlxZXZf8TTLjzciy++DWCOY6HLtigq5+kTkmfQJ8PdVYYdXkIPcrxnBlN2xVo0cAdX5WUOmyBrPy/m/D/Iaoh7mIw3xCD3NjVSTMEW081Yk2xkW0sYC38YO+DW+sNrSYbazmFsYOVg4jUbZe3oSmo0aWuOE6I54WzqxLAulBqEuWk7GRUNwmAz+R5o08x2HkLuCrvqtmJOfQPs07k/ksn7VX0QlijMjP2uheiyh41c5i5hlhZanD69mM5Msl/fC75YufTESKE29gPrj5gHaayLd5GFKtGnYS7ikb9iRc1Y/vYgnmBIiDMnMLw9JqhqWZPCgt9gHlaoKP9gu7jZ+F71/M9o2X36W7KWLr521qbJQiNeCiufJdFA5KMNiDF7jSQHkTE33pTOnT2xTl
*/