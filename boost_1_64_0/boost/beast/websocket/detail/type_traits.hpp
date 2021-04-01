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
/1GiFkeOvIY/oPF06uHinFAItMXHOIKpo97PQdhsHQidj4uPhwxQWmPWFIphZRNR9gMOre+JwMBpZuecViXFJqji80jeEgktnar+RQfIlaUYeyW740zZIX0rb9KPmIYdMeZG0VBf9mqYo70vcagCmUPND5WXiqW/fotWWS5eLdn4fOb8SlfSDJ9W/SR5COQbud8xuJH/RnSKr/6nYYsd+3Xw/3bCahVBexSOn9orW4sotUKlQfRPZu8YnT7mH30qNotEpHvxk9Ksz9UQ/NJfG3OvWwYYfr3KO/9xMlxhWkswbE/bdp/UG5HNrWO+UlPq9s9kY5lHGodZse6V9jZrD5ln/KhqjNhC4UAtEQAOSNToU13FY6EXCNA8nzlkGUue6Fqq3/h8Xxh4GCwEaXbmq1K6vrG8tY98BvJ0OS+O72quhYFkcFNA/iqQW9cXiyfkM9sIdDAXdwrEU2bzolEIQXPXEpHysHkybbZ2HEs9BvGDyONO3ElDqazizebYnEneYMo9GIkvJ4eWqroUUWLzDcWcxEa62feBHaRlq2wEWzggXEcZj2nhqgwaeQ==
*/