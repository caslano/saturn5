// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

#include <boost/config.hpp>                     // BOOST_STATIC_CONSANT.
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename U>
struct forward_impl {
    BOOST_STATIC_CONSTANT(bool, value =
        ( !is_same< U, Device >::value &&
          !is_same< U, reference_wrapper<Device> >::value ));
};

template<typename Device, typename U>
struct forward
    : mpl::bool_<forward_impl<Device, U>::value>
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* forward.hpp
EN28WBN8n/YhE8voTUldRpmWiZ0LThaHUucymuuffZJfafKZkebdDcB0RfEFPxszDZG4VnX5843NxHAhd2QPBObvWEiXhR7q2nsaYdjSLvNDzM1owaA2XK6Ol564cHHAEZNZXSYl11WMsSvf+/hGBZJI5So4+9UM31ySM0Q9l3T61Sy7/Tj0VxeITH0p9FmpzWacvywYL4dPKIvQRMqgn6XgNVdD6/HmhChX7PSvg1qNFmENsQ2sq+7YIJWzYIECPGw8QgNuYXtmWcM+jfXaAMil1Tx/ZG0N7U6wGgvE6Ks1+gT72NM53DyxxLC/wih6fy2wN8/4pHxUhn9s26Dcs8OU1aUNhOAxbImVzOFSjxNPOw74mi9Qi14iNuSPj+jwfn7ohbOnV4xkyY/gidzPYoJoO7bpDlELNiYSlhIMnQ66G2+YLZAajyUccSS4YAew3BCaFYyy+oxcPGGczWs68B6vN/lwnVP3cWekFVoFiGkg0K2VRJ+NCElk/PP8U9JMdir3HSW2Y9nSQBT+/ZUtTIgCT6Klzza5UGc0VCM7YvfSEZwNeIvVHBjFRA==
*/