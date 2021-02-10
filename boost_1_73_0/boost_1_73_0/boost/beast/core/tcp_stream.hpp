//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_TCP_STREAM_HPP
#define BOOST_BEAST_CORE_TCP_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/basic_stream.hpp>
#include <boost/beast/core/rate_policy.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace boost {
namespace beast {

/** A TCP/IP stream socket with timeouts and a polymorphic executor.

    @see basic_stream
*/
using tcp_stream = basic_stream<
    net::ip::tcp,
    net::executor,
    unlimited_rate_policy>;

} // beast
} // boost

#endif

/* tcp_stream.hpp
mnxrFII0v/Lg6YXAFuisGDB3SdFxfaa53Uk6BkwvT/tebzDpd6fYVT9ahJIa4PqVrBe9eJZy9nlnrT49PFS1J4wnmgEPWRabh6Lj6XF/HYzt7pjWj3ygDH8CXo4STDk8Skq10h7yvrO/B7+1D/LcW7VKEYN9fFdaqHidnQxOT/u9itmDcfSocXsknYtZ3mDb0rv9/IyFuR6qhEvn8YZCfTErzdNgXFWqGG2APewMhiVsAb1BenzybFW87kxlMxeJruNZxq03vhgNx53eauhCP1aaP1TbWRem9m073/t1fpQj6ZEf/+Xxzjr8fECoieWSxHqFCA4+8mZnTbgscCUTWt5ORdctCMKTaC37M6Y5/kgzNCWKyBWJ/Rqz+PtAFQaLEBdaFNN/AVBLAwQKAAAACAAtZ0pSw5axkKUEAABZCgAAIgAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvZnRwZ2V0LmNVVAUAAbZIJGCtVW1P40YQ/u5fMaRqL4lMDHxpaQA1BwmNLkoQCUVISNbaXsfbW3ut3TUhV/jvnVk7CXBXcZXOiNje3ZnnmWdeHHR/3OVBF969Qvcf4oV3Z3Gl1d88tt8+HYZPUP+h1T3e3wMJYGfyFHbgfZMnaDuTsEE5oecwfA/onrjR
*/