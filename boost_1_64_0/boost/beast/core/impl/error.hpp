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
RWzfAsjfrFze4Qgbr3u5B6W9Y+/iz9xLhsFR4X+1heMwCfMzvwdr/a3IEt9Ie+wNs0uZwFQnSZJi+OVtSzsYGovYEXgwfHfjuhBQq3srTRli52EThmym5pzxlr6QIq926ixWEitu++S2WOs2PEczeFngjy6YvaThIEkEvY1LFezh8+pBDCqbOmDyLiI9SwMmcCLqE+c4Fdey9sdDM9AZxYJkJY89GGprrnxDah9rBz4V0fpWfOuoqTPv9e8XUXV1L1mMBgxHBG+hJIuR+0kdYs8LZSDpix4CQRUe+wFT3TV7Hnmpa0wOjZTEXnJHmFDrCzsRk9CG6EEmMh23xX7iWUiy43Y8UNNtjXWe+DiB6GXhaMmcA0MVuKv8Rp8rGf9jrBcH2ExRQ7KhsHfdPrzNT+EeVKMwfSLci29KQpvsiDYEurputUMxukXmCwLp2QbCDF/s4L8Lq/G0uxbwxDEQaEUaPL0IcJcWWSkWIItibz/WSSM0V/yvDsKDAEFbmRYE088B2LBWAenx5Y6KW+hngJhWWaokao5sRti2hEErQoB70UOwrPE3niL8Yw==
*/