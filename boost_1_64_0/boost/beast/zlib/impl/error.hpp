//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

// This is a derivative work based on Zlib, copyright below:
/*
    Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Jean-loup Gailly        Mark Adler
    jloup@gzip.org          madler@alumni.caltech.edu

    The data format used by the zlib library is described by RFCs (Request for
    Comments) 1950 to 1952 in the files http://tools.ietf.org/html/rfc1950
    (zlib format), rfc1951 (deflate format) and rfc1952 (gzip format).
*/

#ifndef BOOST_BEAST_ZLIB_IMPL_ERROR_HPP
#define BOOST_BEAST_ZLIB_IMPL_ERROR_HPP

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::zlib::error>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace zlib {

BOOST_BEAST_DECL
error_code
make_error_code(error ev);

} // zlib
} // beast
} // boost

#endif

/* error.hpp
NSauPQxGNnaltloxGVn+ogTMb3a0EBBQZOudobIWFDTVYMdkW+b1lJtc7g8lJN9jAKpnlDmfY7ELzQZ6S5yUkXs4WicPzCi8m6Qld/w/ixw6y6t1u4Leif8HrzvaYmxmyrRfMqOsTk2Tl0a2M71JSgLdFWRlJ0QTsswsQQqLubtPXCafMjCTg4/cJf39kcLsVh6Fl5PqyEBtgDEM8ghGWv9cOnno6XfmdPjaAuerD9kx0vX6UQpuV2VNW1L7Nzst2oC9msOVXjIsB9WsI7iNIsqkPJr/eBSP1oH+jF8lQWRCQLdhPO0BMO62D4F6t6W7jBf36fyL7NZi64SOee7Pz6CscNwBq8YZmygIFN8ekkXNwG40hTZlSSabCwYLBIHWbWY9MGDElWQij82Wu0AJnyy3uU2nBIJEszG1sTmKKD9v4DLFDFFFVYD8N75YsmFOQnpOLT+SPdhymMd9gaqRxr05UeyxtCOX0U9kTE4aPTkppNWE7NPru1ToP+hy7iPZpgVaKEXpgYWTtgGUnKDCxUJllYzMOSUdp9A2mfFtbNKOeK8MpD1K3RxICQ==
*/