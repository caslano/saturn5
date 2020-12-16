// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                      // copy.
#include <iosfwd>                         // streamsize.
#include <boost/iostreams/categories.hpp> // tags.
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Mode, typename Ch, typename OutIt>
class output_iterator_adapter {
public:
    BOOST_STATIC_ASSERT((is_convertible<Mode, output>::value));
    typedef Ch        char_type;
    typedef sink_tag  category;
    explicit output_iterator_adapter(OutIt out) : out_(out) { }
    std::streamsize write(const char_type* s, std::streamsize n) 
    { 
        std::copy(s, s + n, out_); 
        return n; 
    }
private:
    OutIt out_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED //-----//

/* output_iterator_adapter.hpp
QeqeLc+Brvfvzs41+uU+lsa+DMM7kJ4jqPc3ppFteI/qqffJ9Vz25+j9jddp0lDXSdfzrLoWVrn6BpBV1w7ncxr71HWDa0lINmz96BJZbG+IKHow4U3iFzyjntHGT644vpBcC5WlsMn1l2PsNa+pTFzTs5H5HUzLOu+zxvnHWrZJ+52mjse77VffTwrV8XSLfw3nhWktZ/NzMPUPtoXsa+e2J/f7BnTqvEHWzz+M4CMcSngendcFdW73F8o7BHlE9s/oe961Sn4seuSaQDC0haTpc7WbsS20bOfwd06dZwZ7HlMyuep9cytysK+VR6O7w0mkv319TsqJfG8UmWpkdrRl4ru43xu1zCJkBqj3xiER742qfaL41sXU76HbTH9bIuunp0WuJ/4B8bOfda6ZT3OMGTpi92FD91CrqEubdGxp7Xz5hkjXI4b1wkk7bL33YVLeLoY1/t9HNrep8upV8K2Y18EP5ZlsWAd/CnnmNZUnq83HoifS0Xb345Ytrzef9+z6rzdPWSLWmydP93rz2j4sw/r679nXxybrzsrzUdabNFznZpNrzyO7/mvPO+rsOh/Iz3VtusFQ31eJXxRW351CzSvPu83Xs2gDzoMy13mwS+g86BpZzmOQrXCVU5v/eth/KK92m0bmNY28ql15YfYx6aXaYffndW7Z7qs3wO7LDHZPnhF2r+9RhjpXkkatu86Ye7T1VXF1H2Xz9l67AfZeZrB38guz935Sz/ndIuu5jELU6XoevGPuzpjQpGAd709tvo51rnI3xFBu0pZyh7fFzM0iy/gIsovDyziteGIVthddOYkb4Yt/hrkttKx+F1zPOnUO6zMkv/+5D/al76t6tTkupeSk5d8s+apiv9wuv5/pfSOzsX4j86P22xXse6mFxYRvHX8zLqK+6zjPUuMf+u9PHPs/dfy9IzIzYC5hgOPv/o6/P87Qf6t3/AaYRtha/k73cU7CGXrcXc0FUMcSCROlzKfL9yTnwu3ku5TBcAEcI9+vFMPL4XRYB2vgNXAevBHWwuvgJfB6iCz7G/1810v+Zxj8fN+GnB/eDdPgvXBruATmwqVwL/gAHAuXwYPgg1Kuh2ApfAROg4/DE+Cz8ET4FJwDn4Y1sn+NSl/G0+BCKVcXwi1SrhelXC/DBPgK7AxfhRnwR5gJV8EsuBpmw9fhtvADmA8/gkfAj6W8n8EK+CWcIemcCL+Bs2ADPB1+C8+G38GL4PfwMpFfA4ssGeOBeVL+9oQDpPybcBPoBNNhV5gJs2A3uB3cDA6EWXBX2AMOglvA3dRvaT+f9PHKmE0DtOPPke+Ruosf9h7wMNhT2qMXnAv7wHPhznA13AV+BXeV74XmQL98/9MB7gYz4FC4E9wd7gFHwEI4Ep4AZzi+9zkdjoZ1cB+4VH4/C/eHP8Cx0KJBD4ZtoP27PTwQdpT9qfAQuCM8DA6GR8JJsAheDsfDpbAUroZlcB2cCNuin8mwPZwEE+R3f1gJd4Mz4HD5PQJOgyNlfwk8GR4Dq/m/Cs6Gp8JT4BlwjrQ/5ZW+D3Qn7d+OMCrU/sjZTBO7TZfzKwNuCjeD3WAm7K19CLJf0r9Bv/ujC0m/M2GhpP+L+ChcB9vD32BHmIzdJMHf5fu7PyQ/i/2bAz/sCeNgbxiAObCN2F9bOAS2gyNhe7gPTID7S/oHwCR4qPxeA7ND79YwXq57Pjmn2bhONsrlRimXF6VcQZRyRQ65Al+43HkOuYoo5aqjlKuNUq7OIVfrqkexQ25xC3LV3vd2rfq9nec78v/17V2gNt7qScgnlBDmEOoIywhvEQLnxVu5hMMJcwh1hBWEesI6Qsb53jd73uZt3uZt67v9nfP/K1o=
*/