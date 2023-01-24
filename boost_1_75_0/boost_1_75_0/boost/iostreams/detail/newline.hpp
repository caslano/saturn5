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
J3J55+Cz5BpNqHZ8b+jc4N5c1TOVLryrYJt8+dNMvYJvslh0RwbpuzsTD8Wy/6F10TXTBoZf+VuS8ksmE8IKWMJtM9jycwxrJXCfTylm8d5GKiPnYELQlbuUWPpgPl0aB6vyXa6vgB9LqdQUvndL8WVEQcAOkXIatW9ycWVf6uaakBnWNCb/RiDPpk+DZ2JM2Lv6zyo0vH18Ajg3rdNp3pOrYmUcZlVLeQ878V6afF3WjhrmROXpMZRx6vQSs+2CJ2fAG9XoS88uLi7d12MLhN1tu/2cHIZSLi5LDIHdIiLCqPJHQQ6I02CNP07m2BUt0GdT9HDx8f44U5Od0WpVHSM09OupPLsrFyd/7uTcFOFr/PNVxEpdkcemmK81sceEApBoPUpgFS5mvMdzy3bBp4zwBeaT7ClIKe7DDS17M5x6tlBtGRnQvm8fdKAY2G68uyERmhbm9xNQFDnyiMRLUnrgz/ethSa+1weHA3BqCePfMp9X4U+VV+RZ1O8zz36Qt8uaFFNq73RvfjpH2P7uR3wcIem5AHeWSSPXL2r6J/IT5gzD0vfCbp8WEMonnk7Vr33yx4s/8fGAANogHP9cQZEC8XdnXky5W2qheJUvrNG3rUcSyVXJ/tCukUdtnyii5FJNEIEAbf9H/gswJoBobD2goE9YyWjtTcznh+G6DSnIVNl/oTnXNgfQMJl5qsSsUzojWX6Zytpg8IXI
*/