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
7Ca4/3dKwRRvtzPX/CeXb3GOsJNt1gARtj+JZvhImy3SuhnMb9bgU4t0hvN9ukbwotSuseelPrrGXgDZPI35nRap8PTBJJ5GKp4a6vbiJwrVrgqVDayxG/zKt5b8Fy/d934rCNmRulbyLH/FQp8/Oz/vEMp7ufl42Y7X06MkCyPQiyINzQiZsz+C/C9j/vJb7kNb01HdrL7dpLibUhhltgroVDb2dm7CLlZNVYnnAocYQ31E
*/