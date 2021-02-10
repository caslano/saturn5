//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_GRAY_TO_RGBA_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_GRAY_TO_RGBA_HPP

#include <boost/gil/color_convert.hpp>

namespace boost{ namespace gil {

/// This one is missing in gil ( color_convert.hpp ).
template <>
struct default_color_converter_impl<gray_t,rgba_t>
{
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const
    {
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2, red_t  >::type>(get_color(src,gray_color_t()));
        get_color(dst,green_t())=
            channel_convert<typename color_element_type<P2, green_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,blue_t()) =
            channel_convert<typename color_element_type<P2, blue_t >::type>(get_color(src,gray_color_t()));

        using channel_t = typename channel_type<P2>::type;
        get_color(dst,alpha_t()) = channel_traits< channel_t >::max_value();
    }
};

}} // namespace boost::gil

#endif

/* gray_to_rgba.hpp
Kme+WclnYGLmzlkYSSZDlghYPvZssFk49ib4m8cX8DBKhr4npo2UG5gqGO+FMRPc95EWjPO4UGxz1tPiaWA3FgHHnsRfIgwETnU9DWe5jiBHpDJJ4gAmAjlAp3EIYm6wJBjzmDrTys0UWqYk4IVbk/I7ZmEAzLDNZo+1e5ts6ApPNNindv/d2aDPPjW73Wan/5mdnbBm5zMSe9/uHDcY92CymPGbKOYCJo+ZN4t8j4/NnN2To2d/fX5AW/Oex0Meh4J9fM5qm297veZ5e7POes3eB3bKR1MXFjdT4x7us7ex8YMXjPxkzNkm7rojuEyi3ekmNkxAJSdewMe1Qa/lfII1nX3qOb3eebvOtrZyje9b3Tet7lnveT1D8WekqJRp+io705WbyOke/cSp0gboOnalm39IfIHM+U/P8g2wU4EPkq3oPkt86Q3nkufbBA/GE1rd3jZJ3XeFZLYd9UEY2xryFwwEVCTMZ2E8z1OFZ2M+TC40YfIY2BfX53jCuRDCjTxHJFEUxqBOtXpW5+D/RCit5Veun7hgICB6pQGsltGLOva1VIwSnbuxO+Og3+IF64QBN7oFGxmDxfS7gxbSy+pXlgwbztknLxiH14Lh1iLZvY1hGPorFnEVeuP6xu8b4PN7fHR+edEOJiGD
*/