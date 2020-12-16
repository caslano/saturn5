/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   embedded_string_type.hpp
 * \author Andrey Semashev
 * \date   16.08.2009
 *
 * This header is the Boost.Log library implementation, see the library documentation
 * at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_EMBEDDED_STRING_TYPE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_EMBEDDED_STRING_TYPE_HPP_INCLUDED_

#include <string>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T, typename ArgT >
struct make_embedded_string_type_impl
{
    typedef ArgT type;
};

template< typename ArgT >
struct make_embedded_string_type_impl< char, ArgT >
{
    typedef std::basic_string< char > type;
};

template< typename ArgT >
struct make_embedded_string_type_impl< const char, ArgT >
{
    typedef std::basic_string< char > type;
};

template< typename ArgT >
struct make_embedded_string_type_impl< wchar_t, ArgT >
{
    typedef std::basic_string< wchar_t > type;
};

template< typename ArgT >
struct make_embedded_string_type_impl< const wchar_t, ArgT >
{
    typedef std::basic_string< wchar_t > type;
};

#if !defined(BOOST_NO_CXX11_CHAR16_T)
template< typename ArgT >
struct make_embedded_string_type_impl< char16_t, ArgT >
{
    typedef std::basic_string< char16_t > type;
};

template< typename ArgT >
struct make_embedded_string_type_impl< const char16_t, ArgT >
{
    typedef std::basic_string< char16_t > type;
};
#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)
template< typename ArgT >
struct make_embedded_string_type_impl< char32_t, ArgT >
{
    typedef std::basic_string< char32_t > type;
};

template< typename ArgT >
struct make_embedded_string_type_impl< const char32_t, ArgT >
{
    typedef std::basic_string< char32_t > type;
};
#endif

//! An auxiliary type translator to store strings by value in function objects and attribute values
template< typename ArgT >
struct make_embedded_string_type :
    public remove_cv< ArgT >
{
};

template< typename ArgT >
struct make_embedded_string_type< ArgT* > :
    public make_embedded_string_type_impl< ArgT, ArgT* >
{
};

template< typename ArgT, unsigned int CountV >
struct make_embedded_string_type< ArgT[CountV] > :
    public make_embedded_string_type_impl< ArgT, ArgT[CountV] >
{
};

template< typename ArgT, unsigned int CountV >
struct make_embedded_string_type< ArgT(&)[CountV] > :
    public make_embedded_string_type_impl< ArgT, ArgT(&)[CountV] >
{
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_EMBEDDED_STRING_TYPE_HPP_INCLUDED_

/* embedded_string_type.hpp
Nc/sLs8cG76LZ/q276oxd0lYF0Q0+KdMXrbZDpf4Os/xu5nmnhEzHpne8d523fsdpc9c+stvi/Yq2ni09Y69nadtPNqMx6+dh1t+23qnxONXi+qL4hmN2oDY13ZfY66FKFs7MDXe2xasa0FbcNK0hrZgLPfzvPfz8haVljAGJTL5uU23D9va2ocTuLe2DScdl3ahjDdY909S2WQ/bcUeTbQVUxzaiqm+bUVt7/2og7VdGBVTgmBuraeXbh5NOMu8yROwL4nzfLuWz/+bIfMvC3rXLf0oqvvX1RMu3BE++M69Ld+X5HjNp2zpfNPjNU/UeT5ly+dHOs8Hbfm8WNl3wRh3hEsc9l3orOufu8B2MBmmwT6wH+wOx8IecBLsBavU/HNYFqx98joWtxEuQBXquHO67gMyGF4Ds2ANHArXwhFwHRwFN8Hx8AU4Ae6EE+EeOAl+As+Bh+C58Ct4Hox0E06YBGfCU+EFcADMh2fA2XAUnAPPgQXwfFgIC2ARXAjnwkvgPHgtLIY3whJYByvgXngJfBtWwa/gpfBruBS6g8iLsAO8Ap4Kr4TZ8Co4Fl4Nx6v+ObAaLobXwlq4Gu6E18Ev9N4VzD2MhjfCTHgLPBvWwnPgbfA8eCecAX8By+FdsBreC38B74OPwwfhi/AhuBs+AvfBrfAAfBT+VfU/hU/AeNLzUzAVPgPHwedgPnwIFsMX4Qq4A94GX4J18FX4HNwN34VvwCNwD2xPftgLe8C34RD4DhwG34Vj4IcwB/4VFsFP4aXwEKyFX8Kt8Gv4EvwGfgRdbuKN/BwEk2EIzIJh8ALohgUwElbBKLgctoOrYTRcA2PgWhgL74bt4YMwDj4D4+Fr8CT4Z5gE34Unw7/AjvBT2Al+BTvD1uSbBNgedoXJsBvsBbvDfrAHHAh7GvsuhGi7WfsIN8KrUT1C9Oxr5CbAAbAYngEvh2fCNXAI/DkcCjfAbCjzjuFv4Ej4OzgKPgdHw51wDNwNx8G34AR4AE6CwW7yJwyFk2FXOBWeAqfDbHg+zIGzYC78ESyAs+HFsBCugvPgdXA+vAkWwzvghXATXAC3whK4HS6Ee2Ep3A8Xw3/CStia/HMx7AgvgV3hEtgXXgqz4DJYAa+GN8KV8Ba4Cm6EP4EvwuvhS/AGuA/eBPfDNdBN/rgVdoE/h8PgnXAU/AU8G66HU+AGeCHMCiLc8H7P+4EPwB/DB+Ev4UPwEfgYfAM+AT+DT8Hv4DMwMoR7mACfh8lwO+wBX4C9VL8v3AknwlfghfA1uAy+DtfAZ+BW+CZ8Be6FH8G34bfwPRhLftoP0+CHcBw8APPhQXgR/Bu8Fn4Kr4efwTXwS1gL/wEfgN/C38Lv4NswJIh8AVvDGPJHG5gKo+FAGAPHwgHwXBgHZ8B4uBwmwWrYGW6FyXA37AY/hT1gG/JRL9gXpsCxMBUuhGlwGUyHm2AG3AIHwJ3wdPgBPBPWwyHwOzgUhpIPz4IxcBjsCIfDbnAETIOj4EA4Go6CY+BseDYshhPgAjgRLoKTYDXMgbXwXHg3nAy3winwcTgVPgfPg3+A0+BuOB2+Bc+HyHjm+h91r47AOoDAOoCjrQNIqeR8ZFRVZWAtQOAKXIErcAWu/83rBM3/pz/0+8//70yf4sOZtN/pdwp2ybbdFRyMV1laIOdqiPlTXWk7drSaL8Zbi0oRkPUD/Xm2Mc+a9phcGRoX/VHr4+hX8a4fGDV5cl7JotmFeeoSfik3996OxIUro1HNPLvlEEx2++sf9N8PWHaDG/1Pbkk7+OA1687pX9cp87QbHujnvz/Rud/QX//d8euPc+5vbXn/oLGPn7wDfTfpKHMfP+1X83A0jIVjYCc=
*/