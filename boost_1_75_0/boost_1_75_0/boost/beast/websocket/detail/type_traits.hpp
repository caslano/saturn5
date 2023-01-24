//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_TYPE_TRAITS_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_TYPE_TRAITS_HPP

#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

template<class F>
using is_request_decorator =
    typename beast::detail::is_invocable<F,
        void(request_type&)>::type;

template<class F>
using is_response_decorator =
    typename beast::detail::is_invocable<F,
        void(response_type&)>::type;

} // detail
} // websocket
} // beast
} // boost

#endif

/* type_traits.hpp
0gwZacaMVENGqjEjxZCRYsywGTJsxgzJkCEZM1pi9Qz8LTLqeEYGm9IG+N1tlyfwRYvSshA4vG9gdvCNnfTAArK8wlDZCmNliw0Zi40ZlSJDdfa5EkGgkhYnDXRnl74KNJssxWiFzqFCmCLLYE4hqsXfmqGWIaPBmLHTkLHTmFFnyKgzZlQbMqqNGasNGav1jJAMehXK5k/gRNgaYabY9M874oy+m/LAAVi1R056JTVZkj8iFxQ5lqXszX+qCzRlk0rZb+WNZEDjSWWpFDDWDQIuYIe45Y0opd3ndqwCBoYQflXowi/BP+HyqVKUT7nUgUUGl5msmQ6s6qbR9liJ7mMF8n6G46yrE6QYuD2Wf+y3rgaU1pzLunGsczLgOXbNZH3cyT7+gCUoDupjI7gnDrI7ctLeztRbG86MDTEj3d/g3h2H9W2sjTEhlt3Yek6GdDbOSVFnfU7Sob3nkrC9zM5/2Zy8fSqbkxts7ZqTJadGzMk0lqAcTcQ+zj5VzMmMU9uck1bjP/VU4/hTT9XH/5UTxk91H3T+ZeOf4oTxW9s1/judEePPgz4eTcA+ep1i/D2dbY1fo71vvCBeahrxUSveQCrwBsgBlVc2hQaZXGphhs4U0HgCqZwn0GYsY5CAFtiAU5tb4yhbhBfFVJS/AXfSK09gRSbYQFLbwyPfY+ORGM/0BM7XNj+mxOsp3GHJDiX+ZeB+/NtTfsC/
*/