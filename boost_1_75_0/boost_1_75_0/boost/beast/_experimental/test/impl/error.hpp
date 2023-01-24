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
bJje91Pa7/t4a98jo0+2DBvn/8l52PQcz0PkGiqofQ4Yl4NlvaXCHu1/RbPiqLZG8iGyIUMvata9sN+KYEVu6moJPWBlRSaOJJ7jQb6O4+vsUcCazBzFsXVvNOzKdL3m3rOtlqZWveaKee3pNdF715GWeM0dKcofjmnJGPd6XkfUm6EuVvUm6v2W3RBrl6fbwg4+O9b2xGKX17PdLpavXYKq12uBTy9UZwBYBpPQ7uvZjnT0h9T2rGKTbpD6ymPXtzGn6lkn0hWPffZkHUZd8WUd6mNeahu64nuoUya7lixy+zyQrnObQPzz1cP5YD/2TzZtWc0olywkcP2fIX9PuDf8PeEuL3vNEhSzDqMETY6qaxOlsuK8G6JRtGUhR7LJZBHS2+zERgb78KneyNqiff5cfmEkCFA5jBcK18CBTzAs6aLA7gJipOSHXC2Y1By9fHYnYA4IeCE4HccQJFkc9F0ziBYlIXJe+Lo0vnszgTpYTCLsYcfoVcoiMbv2qJ48CUo4yObUBKqk8AGpGIkS+7SpMgXFXP7+ZvYILeS3mnm309vYdjPSY6zV3xyGqI7p4HamYHWIly6by943zXJcRgokqGG2HX6Ou9LALQBrpp1VCKujt7fnaXKj2s8da1L0ju03OvbKyWNuvPS03ZSphFogVgOn7Z546gt952NvKDFDMLneCz92LLcPdSxPVVwXbhI8W2VdXL5gQH6G
*/