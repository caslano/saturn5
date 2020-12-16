// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from http://www.boost.org/more/separate_compilation.html, by
// John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <cstddef>

#if defined(_MSC_VER)
# pragma once
#endif       

//------------------Templated stream support----------------------------------//

// From boost/dynamic_bitset.hpp; thanks to Matthias Troyer for cray patch.
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# if defined(__STL_CONFIG_H) && \
    !defined (__STL_USE_NEW_IOSTREAMS) && !defined(__crayx1) \
    /**/
#  define BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES

//------------------Wide stream support---------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
# if defined(BOOST_IOSTREAMS_NO_STREAM_TEMPLATES) || \
     defined (BOOST_NO_STD_WSTREAMBUF) && \
     ( !defined(__MSL_CPP__) || defined(_MSL_NO_WCHART_CPP_SUPPORT) ) \
     /**/
#  define BOOST_IOSTREAMS_NO_WIDE_STREAMS
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS   

//------------------Locale support--------------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
# if defined(BOOST_NO_STD_LOCALE) && \
     ( !defined(__MSL_CPP__) || defined(_MSL_NO_WCHART_CPP_SUPPORT) ) \
     /**/
#  define BOOST_IOSTREAMS_NO_LOCALE
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_LOCALE

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WIDE_STREAMS_HPP_INCLUDED

/* wide_streams.hpp
azAffgHnwSNwIRyFvJbAi2ARzIGFcBpcCmfBZXA+XA5L4CXwFlgMN8LL4APwcrgTXgGfgyvhO/AqJb+Deu2irIOVfGqK2af04lOCbAf/DvvAw3Al/BreBv8Ft8Jv4BPwW/gl/ALGER5/S358BZvBBsTbEf4b+3nwB5gD/Xb6YBwsgAmwENaAS2AtuBzWhcUwEa6GJ8D7YT34a1gfBmADlb4teg0Z7a+yN8Ssx1jq3AmbHWFt2Ak2g51hW9gFdoddYU84XMmhJ+wHMXKuxTkwH54LC2AaLIbp8Co4CP4WpsJn4HnwZTgAvqrCPQwL9FoknlWZuphp6nlz8eeHM2FjOAueDC+GveFsOBjmwwvgXPU881S+FcD1cAG8FxaqeI+E16jAjUoPWmAOqXh/iTzPgdfDNHg7zITr4Uj4jKoP7oQr4AZ4BbwbXg03wrvgPXCT8v8o3ArL4APwE/gbGIQPQvLceggmwh2wLXwYdoA7YWe4C54LH4MD4eNwKHwC5sKn4CwYgEXwaXg1/B28Bj6j9KTEp9YrqDUaW+CpGHROfq/irw78E6wP34I94btwKHwP5sIyOAO28ofODf8AezH8CK6Ff1Fy+BTug0H4JvyHksNheAR+Af+twvkBfoM9yUf5UuXnO0idKe7d4ff288AfYH9Yw89zwZowC9aGk2FdOAeeAFfAevCX8ER4C0yG61W4d8IGcDNsCHcqf68qfweVvz/BRvAD2BjG+0PXa8DmsKOyd4aHfJQX+DkcrK5nwrexj1B21V6p9+7ovqG9GqnK7RhYF46FDeE42ASOh63gBfBUOFmV04vgcJgNc2GObh/V+2Qw3RDfNTyXD14HG8HrYTd4A+wOb4Y94I0wFd4Ex8HVcApcA/PEn2of49T7OPXudgucb/tTZ43dZucbvB2OhethLtwIZ8B74KVwE7wcDowL1cebsd8Lt8Dt8FdwJ9wKX4bb4afwQXgE7oQ17XIE60DsUt4ehQ3gY7A13A37widgJnwK5sDtcCEkPKmnH4Kr4TlxIT06F94LU+H98Dy4Aw6Aj8CB8GX4NPd9CH8Hg/AZeBg+C+PQi98rfXoe1oIvwHZwH+wFX4Z94CtwJHwVToCvwxnwDXixsufDA3A+PAivhH+Cq+DbcDMsgwH4IXwdfgSD8GOYGEf5hR3gZ7APfB+mwXfgWPg3OBn+HebCf8Dl8DBcCb+C18F/wlJlvwl+DdfCI/A++A18DH4HD8DvYRm0kNu3MB7Wi6e9hKfAGrALrAl7Qzvec+FhOBh+ATNhLdyHw9pwHKwDc+AJcAasBy9W9nxYH86HSXAlbASvgj64FjaGt8Mm8C7YFN4Nm8F74UlwJ2wJ49D3dvAE2B62h6fAjrAjTIWdYDrsAi+EXWE27AanwVPhdNgdLoA9YBHsBVfA3vByeCb8DewLn4JnwZfh2fAg7Af/DFvDv8EU+AVEL8rrhcLo9cJZql44R9UL56p6IVXVC4NUvTBA1QsDVb2QpuqFdJin/B2W8ayaF1fvG7bA1ph41Q4NxV89eD5sDIdD230EPAWOhF3gKNgTFsOh8DI4Bl4O58IrYCFcCYvgOLgCjodr4UT4LrwIBmE2/BLmwBSeZRrsD/NgOpyt6oN8OBvOgdfDeXA7XAhfhIvgO3AxtPykEWbA5TAHXgKnwxUQvzyf/k6FmsdEV1R96fxOxTWqHbhW1fOrYAb8CA6BpXAFXA0fgDfDP8O1MAjXwSPwDmjL+k7YGK6CLeFHsDXcBEfAzXAy3ALz4FZYCO+Hy+GD8Ea4A96i7l8HH4f/hk/DKX7qN/gsfB6i29ZL9n3wNfgVPAAnx1MvwadhGWxL+j+EJ8OP4GF5fjUfB9c=
*/