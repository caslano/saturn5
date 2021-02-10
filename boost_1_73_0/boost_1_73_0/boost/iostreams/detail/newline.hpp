// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

namespace boost { namespace iostreams { namespace detail {

template<typename Ch>
struct newline;

template<>
struct newline<char> {
    BOOST_STATIC_CONSTANT(char, value = '\n');
};

template<>
struct newline<wchar_t> {
    BOOST_STATIC_CONSTANT(wchar_t, value = L'\n');
};

} } } // End namespaces detaill, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED

/* newline.hpp
E7OjbXUsk23dCOJbTlwFuEPi7ZWP2y/e82ghZ58yng0zKejmIE5hpsXcNMpnaqNR4DOjMU1XwjDdC+W5yDqwlubbcz1Y2oo9ub6o1iz2LoAsdh7kf+Z+HKyQIlu72QzJZEh0RHyRYjijpc7UykpJohfVhYJm8fIjeWiAmR4L0z5LNyjQMEYdm5jGYR6fqlMDTJPT6t3fw0A5kOQ1eNuwG28NaI7g+B9avXsHdCP3OVrdOVNUYBAtVPRpBLi6jPp5IZAB9TsthDd0wwmj7bJho7/JjS1RuRWhymHI18OcDFjqn5eBZuDzMhTm6cYDplFUIkN0y7Ed6TGGCkiPMNTv6PFmGJcpjGpPrZ9sqRVxLDQtqLVCiMGDFeJesJEcie12okS+lUkTh3uNQCmeamQqwbOOc7xD2KQSzW235Jx8K+Scwr2K8wRPVZwv4VnHuVIbT3My3ZJxdK2QcIz2Kr5jNFXRvYhmHdvaU5uyTaZbso2uFbKN0V7FdoymKrYX0azYcaNHpef33Oj+jQLTxQbKFO1fLk/BvxqNCiG3FWoRVwVqrca1YoHEDqHPNxciMt5WBXKuUgKK9zr+E0SVkb+EaC3zikl80t6Y+8R8W/Zj9yr5jyO+ToEMVWUalKBaUbLSI5znqxY9xA7Sk6UN
*/