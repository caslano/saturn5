/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   c_str.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * This header is the Boost.Log library implementation, see the library documentation
 * at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_

#include <string>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_character_type.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
inline typename boost::enable_if_c< is_character_type< T >::value, const T* >::type c_str(const T* str) BOOST_NOEXCEPT
{
    return str;
}

template< typename T, typename TraitsT, typename AllocatorT >
inline typename boost::enable_if_c< is_character_type< T >::value, const T* >::type c_str(std::basic_string< T, TraitsT, AllocatorT > const& str) BOOST_NOEXCEPT
{
    return str.c_str();
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_

/* c_str.hpp
YiNzvlkv8xiLUFGgmZdFUyfRs49lOzJp6/c6zVwoysbBYuP9YmNHUeogNqaJjTJcIiD70ub/+flZrNezPnJhfZ5ERsLn4PHkbY1pk++cNvp74+kq/EPuSe7pOnuJTzuvje3edL8KswP3phjddY44tHPdmN81fVSm6pDuuoeufu4bue7I/gRb/5vo+F7DzeO9r/afqut3Q9f/nEjJlrDJtrD654Kz1f773Je63ZZ7drl5XTtL7b/TvTOHSXcXm2k6T/mvdvteN7uJ/cvU/gd5PkpwF7p530d8ninM8RhrVd72km2363u1PQx7zPDmt0qrVbwVxDuL8YvN160He3F/QbzXq0ch1yaeB8zrnPrdU65LQ5A1cm2S5wHtmLjYAMp7W+cj8vrFa54nku3PE+r6dLnKF8a+yPVptNSzFTKuoqcY20Pmjqop0tSzrFJW/irMz60I7FpQUxTcnFE1RYHPGVVTFPicUYS1XjN5pvtz18y2nq9/43dpg0534//G6i/rcuLXpSb+8Mb7n5/129n/nr7Z/2pfq/Spyrsv5R6p9+lTHSR9GYNhONwVboIj3PJOKO+69aIzUN6vh0qfx24wEQ6DyXAE7AZHwr5wFBwM94KjYQacA/eFHrgfLIbjYQU8AB4FJ8DT4SR4DpwML4ZTYAOcBt+Gs+C38DAYg21ZcBc4F2bAHHgw9MA8mAePhSVwBZwCH4SV8EVYBdfChfAtWA0b4WL4GTwSboJHwd/gEhgWwjMsjIJjjD4kt7xjyPtWPRyIFEv+fSB9gp/CoXAD3Bt+BafBr2E23Ahz4bdwEdwMT4DfwdPgD/BsuEXy50d4FfwJ3gB/hmvgb/Aj6L1g74QN4XAu7AgXwzh4EuwKL4E94a1wR/gs7ANfgn3hOrgzXA8zoMubbhgBx8IYuA9MgOPgjnBfuDPcDw6CA2AaHAinwF3hVJgGs+AweCQcBWvh3vASGAkvhVHwSriedN0LP4MPqfil/BrPwTBByn2YOgdN7iDCeZkJO8EpMB4ebNFPE/2OGv0DRH8CjIIHwg5woqHvlmcjeT71rT+nSL07DUbCZTANngNHwHPhOHg+HA8vgNPhRXAmvFjKx2VSj66Ci+G18CxYD1fAG+B1cCW8CSI1T8H74LvwAbgZPgjDpe+8D3wC9oNPwqHwWTgBvgiz4MvwCPgKnA9fg9VwLayFb8Lz4Vvwcvg2rIfvwJvhu/AWeCZ8Ep4FnxN/uW7JPZmyqLluHSf5dzzsAU+ABQF+Y1lQHO3MYRfgN5f/5znsTqGcXI00IO8gW5DYkmhXWonTJ+g4xznOcY5znOP+XW479f97O+jb3P/v7d/fwdK/v1zenxYibqQKWZZOW4XH6N9Xx83yyHf/q+Ol/bGk+bvNX1TYPvp+eU9zm+ElcS37sL9R+z2ukcb8YvLt5lXICqQmNvBvRry2JSjb7POv8Vqg3C6SxlTkScLW5NrTmFeem8susdWSTrH1RBW+ty6dEpfb+N4F25EgbOd4NttHi+2bQ+zfZEYiZ3J+Gnxsz8+tTMuaW1aW5ZlbSUHwPVc6m4kjuH4j3/zd0yhDoaZt5liRs7Bxjc7G0rkluQHat6aN9hl5OCKsZR6u5CCNLe3LmleaVTLfk5VbXRaYjY1ttNHIw7UaG2vJw40tbZTOy8Ds27iN7KsOb2nf2djnytPYVzw3v8K3HuntQz84+4hPa19yhD7/YjX2qY7VAMtgbJD26fMPfz/2pbS0T74nD8y+lG1k34zIlvZdy0HSNPZJBQnIvrQ22mfU4V809p1D/mVo7DO+KQ/0HGe00UYjD1dEtbTxXGzM1NhIB1/A9mW20T4jDzOiW9q3HPuytfZJB2SA18E=
*/