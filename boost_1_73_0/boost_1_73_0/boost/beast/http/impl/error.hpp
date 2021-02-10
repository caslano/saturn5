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
3UWtxtFZgaZfXSRsc9ytqgVqG3Xaw0cFph+BFIDGaGN7b+ooAzx51YR+kSze+V1B8srQ7ORDmjByoUZ+TeE3XcHsJfxqb9Ug6EvZraMaOdPQMpd/lLQo9+JgIS1RqLr6urad4iGXzx70NTg59T57/wFQSwMECgAAAAgALWdKUm2qZynqAwAAFAkAACwACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2h0dHBjdXN0b21oZWFkZXIuY1VUBQABtkgkYK1VbXPiNhD+7l+xR6dTyDg4d596wGVKCW0yl0IGSK+ZyYxH2OtYjSy5khzCNPffu5LtQJp2yIcTA7Kl3efZd6Kjb7cCOIKDK/bfmBbtXuNKqz8xsf8tHcdPUH9I65b2QyQR7FSe4h4cVnmCrleJG5aRe47jQ0S3zjb3EznN29g90gmpOc2JKrea3+UWupMevP/48Uc4hg8nH05COGOSo4ClRblGfRfCKPUnP+Xs8bFv8DQEtMBEv4Fa5dyAUZndMI1Az4InKA2mwAykaBLN1/TCJdgcIeMCYTK/urmY/RrCJudJ7kC2qgKTq0qkkLMHBI0J8ocao2TagspIncBTbiwBVpYr2SduBIu6MA7D0TNhFLAHxgVbExGzkFtbmkEUJZUWZH2UqsRE
*/