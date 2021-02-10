// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif             

#include <boost/config.hpp> // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/config/gcc.hpp>

#if !defined(BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION)
# if BOOST_WORKAROUND(__MWERKS__, <= 0x3003) || \
     BOOST_WORKAROUND(__BORLANDC__, < 0x600) \
     /**/
#  define BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* overload_resolution.hpp
fKc8TG2D0+lWbcxjgGWL5NYd0hbmrqboaZJl+6Ixq56l8nPxFWhL565t1UDNElDL/lSk9GPCDdky+2vhc9P5hJq06YrwAR+GjeedphTtkt5O2+Rom8zykzLtzosTpV+dLUi0/wNQSwMECgAAAAgALWdKUnZDIkXqAgAA2QYAACMACQBjdXJsLW1hc3Rlci9zY3JpcHRzL2luc3RhbGxjaGVjay5zaFVUBQABtkgkYK1Ta0/bMBT9nl9xFpgGU9oA+7IHeyD2qiYBKkwbGlPkJje1h2NHtgNl4sfvJmlXhkDVprlqnTr33HPOvddrD9KJMulEeBmtPf5/K1rDypV134wX7y3gyNkflIe7g7PsGv2HQWe8r6BIsURcZ5tYibjGRofI5hy77XOWraA5a4W1P2kLPMvaRz6J1hi3b+srp6YyYGN/E9vPnj3FADtbO1sJ3gqjSOM4kJmQmybYLbqTN1LMZkNPrxJQgNDDLtGJVB7eluFSOAI/a5WT8VRAeBTkc6cm/EcZBEkolSbsHx6djg4+JLiUKufe4so28NI2uoAUFwRHOamLPkUtXIAtGc25C+UD52uCsmbI1IRArvKcoiUX2luIC6G0mDCNCJAh1P55muaN06w8LWzu03xhfShDNXdxygoqcQVbBwSL
*/