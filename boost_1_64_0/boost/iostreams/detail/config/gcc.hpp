// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp> // BOOST_INTEL.

#if defined(__GNUC__) && !defined(BOOST_INTEL)
# define BOOST_IOSTREAMS_GCC (__GNUC__ * 100 + __GNUC_MINOR__)
# define BOOST_IOSTREAMS_GCC_WORKAROUND_GUARD 1
#else
# define BOOST_IOSTREAMS_GCC_WORKAROUND_GUARD 0
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED

/* gcc.hpp
Q1K9rTm7tzrYurOsx+tv7dm9G5K+kfVn0W/Qet3OHuKYeZiNmMcwuzHJd7BPOWbKHQ1r0xp+Db+GX8Ov4dfwa/g1/Bp+Db+GX8Pv2/b7xtb/D5Xl/197/f/ag+z/V8AkZG6Fbz35+JGnDw249h+/5r1bWseE63KQC74uObci2Lrk3Ir63f8vrWPwNVZhYjSilr3/Z5GuM2zpmp932iln5I8ffWb+KZPGTA6UxjM86RGqJY1n1CGNZwRM4xn1nMahOqZxdF3Zz5Pj07iINN5YEb/GVdI54Lr6jQH1d2Md0nZjwLTdWFG/eyzWVX/HaNrmpsan7RzStsqSthYdDpTOVQF1uKoO6VwVMJ2r6jmd66rD0fo3q1H8Xo/DCau6wremRBI5WP1b7UmDRonTFbn63cuykaaBtx68s3HEcyEm+i6nGD3qvNz2fDWLZoJ+Z9Z5ebA1oJ2XB18D6pUtrX0NKLLB17J0Xh58DWjn5cHWgEblOrJWK8fVJdL7SvIxPcRardY5qalJHfgjvYt/jec6XeOZaO3oEgk33ZRjx7eOr7+4T5Xvrtw1Xod6rWhpPax58dZvozLi9XJBb9LkIHqZX1JcGFQ3KwPqZmWcDnGTRGf01EE3K+ugm5V10M3KgLpZ6dHNe9HLm9LrRzf/eRDdvP8Q6mZE58ifQ6ibg5rGtwkndKSsr/DppqXhDaqbhGXycGTrhLqJXP22Edwrbr/j1pnxz3sSz5vnf17T2QjWj8tbEawdzFtRv/sdazsYk6fDNLTeGkgvTD6WCssz+uucoN+DVqwIVt9UrAjeFlasCF7fVKwIXt9UrAhe31SsCFbfVPjycd3XzMdvsl0aFx03No/Xk4VYqgLoids2BdWVqoC6UrUieNtUVQddqaqDrlTVQVeqAupK1SHWlUPZTkR1ZcZh8fXmkI78d5lFVyxtRVBdcS4L1lY4l9VvPcq94s7DG6Rr8P+EORLzqhP5rjU38syFA4vjSgVPn/i71sni73Dbc2uY9u+h54rbFls64M+qr+Y7lO+IezlrwZKt5Qj/fh02a/Lzxe0ua5lSf7V8q2nfX2G3+COn9NvLx8Q+mdiNcHzfd6oMIYhMCe1bst2f/ztPffaXROYoTYuon1PVj/1bz3UiM1j2EujK6tToN9vfq+U7zY/k+23dVzPg95j1+a2l7fvIte5zqF+vTu9xE1TXNoYwp+ueHnkrE+r07NKA/by8lcH29chbGXyOJW9lsDkWT5hWvbtuZe39+HPFfbTTxfKN4vp6+EaxLnka2QO1WeQ7Q92cz10vOwlugfPdNlrza4E7VS/bqdrrnZbwHyJbFrLlGeH422ZTX/1R3Mba8hB//ja1eFFhUZktD5G1t+t8RyTfBP9L3C8ORb+xf0fsXWz5TFj2/iRhybfDqZe77gtDbfUZviP2h512hDIQk0eLFr1PSNwy7P2Aldb+hfmev7v4PY37RPSnhdg/dY7mTclM6o0LMdY+w0prX8TUWR+K+7KQtR+xsvb9C9pIHM4NRfcvuEPsHfkCMc08c1O5dpjErbMn/M4avu27vr2E3Vv8TTJ51FnsmRJON0843SzP6N+v5eRVku4x+7WcLtfSTHlcIuF3IxWbmO/0p6s/aReNPd2x7wsAxX2i01zlJ0iYbUONnLRQor0BckWmayjunqadc2tYx7RzI6grmrn5pvt3fKDf7G9oI9Q2I/L3T7nfD/XvjVy/CkMbIvVK63poN6z9Qi2X0i+09BVzLGON1pb+Y3tL/7GzpR7rlrBtIt10H5FnL49tm4ZoXfdYJ0d+c7VtmoM5H7/Vq3x1HU1S0LmH6lXBxh7Vq4LXZ3Gymp6W+gpZa31lq3OQtdY5tno=
*/