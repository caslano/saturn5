//
// Copyright 2017-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_DETAIL_TYPE_TRAITS_HPP

#include <boost/config.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

#if defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 50100

template<class T>
struct is_trivially_default_constructible
    : std::integral_constant
    <
        bool,
        std::is_default_constructible<T>::value &&
        std::has_trivial_default_constructor<T>::value
    >
{};

#else

using std::is_trivially_default_constructible;

#endif

using std::is_trivially_destructible;

}}} //namespace boost::gil::detail

#endif

/* type_traits.hpp
Gmi5btQqFaa9ppidyqvrn/R+fd8fHJ/9x/dWrA+RYXW/5zjaiKQyMMsET5q5KjidcNS5dX6mDsbjaos05prZPpr5z+LbJg5Uv97fv8G8Qg7ZjYH+kaEZBwiQbqSPCT5jT4SBtY4m06g7+myODyN8xukNN/Vq7rNQU6QsIZ4ke+hZ0KSf9WTNNiFGWx0sbvrwWCet3Qr7cZUm79kGtK0b9VIsjzRXdqkgBYBorW9cs+UzvKnPhc/4KB1tu9XxwZaI/FCzwsqyfeLp6MJE6Ot739VRTVIHQTlBQyfpa2tMWWcCvaPutOj4U5El4WTaGIN82fsOxMseJTGMMWeA/CD4QW2Xa32MvcMLOvy/xc4T+KOa0FfMBe1+5zVXwIi2t2/IpWcTEXhaEXvz2f7ZGjf/hOGjh7jx4WsONVrx6BxytDOwhx8XDj0nJxVofNRBOBChRwmo7QWZ29qCdjZjbrNNDrPl8/Nn6PDnz1pshEWmO8Aa4vUm02MBAytRsp6kDpho1uVpTmQZrysnnzl93+i9gen0L0FKWmJF1rhAG17Ke8x0NLRRWUN7peSzcFnqfMqG5ismNpJL4LqGKWI6KJgRFRwn9FlOTdSqmU4F4Mk+A8mrD7c+UxwirjoSyMuFVC1PTgfvTi+oRaXw1KeT
*/