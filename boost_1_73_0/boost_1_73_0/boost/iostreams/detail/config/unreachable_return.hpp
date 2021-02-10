// (C) Copyright 2010 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>

#if defined(_MSC_VER) || defined(__GNUC__)
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    BOOST_UNREACHABLE_RETURN(x)
#else
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    return x;
#endif

#endif

/* unreachable_return.hpp
bFVUBQABtkgkYK1WUVPiSBB+z6/oQ7YIGoh693CK7C2ltXfu1eHW4t2WJW5qSAYyV8lMamaiUif+9useUAii7MMOBZ10uvvr/qanw85PYWl0OBIy5PIWCq4zb2f3xy1vB7auyH0jXCjJ4bNW//LYbjaOogeYf9BpiHILRAhLj4eoCVs9HsB3HtEC44Suo2gLzJASo5+QHIcRXaLG20G/U1VMtZikFvzTJhwcHf0KLTjcP9wP4IxJwTMYWC5HXE8COEmc5kPK7u/bhr8PgFtgWdsFukyFAaPG9o5pDnidiZhLwxNgBhJuYi1GeCMk2JTDWGQcTi8+X533fw/gLhVxijGmqgSTqjJLIGW3HDSPubidhyiYtqDG6I2xE2EsxiutULKN0Bws17nBEATOMqOA3TKRsRHCMAuptYU5DsO41BlmHiYqNmH8VHo7tfmiiivMIGdTUIUFq6A0PACyCyBXiRiTRCpQWZSjTJg0WKaCQDIJlQbDM2xUchPczFPmMFgwE5AV9XIuLAmjpCGku1TlFUOkEIOMSy0RBilAm0QhwQGUMuHa2bqinxAWbDpqX9mSZa4JKImZQK03gPNBDUbMCBPA1/PLPy7+voSvvS9fev3LK7j4CL3+Fcb687x/hvstEEkDvy80N4isQeRF
*/