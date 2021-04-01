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
Yk23kaNaYUw5fb34oIfsvpTmYvTtu2Lg/q82PbwEGeuv1J/DJx74/VwIX6LPX7YX/S0L8hlN3QxcruPOBTotVx+RwbJa8pxOqBWNX6ysUf5LY52syfmBYeKj1fFzK2mrj31KmfSdX4nq+UAzpTi77uvbAysxLFUEjSjIYg4XCJZ8Cn5SpWgKd9ru9I9uaRCT5eyRjtphDUycl3mJvjsWneaZ5dy/sfFroinE0vJ0WWigywyBGwnzyFEYbatyVA9ethX21Nrrz0RLjx1QseogYyZYutsCtCGhG+pXxBQVHwhwyVlxGfnosLm2z1fqi8Dj9gwKP4W0dwcw5EA2lnuhThflVESPk3PgTFVHeIY8IuBQGnp5QryBx5aCLowYF3rWWeHxpWV8EwqJ9OY9gCjfP15xDyRP1bpG5W2KowA59vbIo4fwPTfkK4gYb0NB0E6d2+jdOwPUREmct6qeEoH9arC5fpuRGFX/bp9d0R1+ide/jjY5TqS/EoSoQP92bD26EJ+JRNKf0IczASDyMh9YXuFyIFerXRilx02yHqOyf1aohCfu3odvpWzgHg==
*/