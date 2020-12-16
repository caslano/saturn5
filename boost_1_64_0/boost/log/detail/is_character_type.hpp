/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_character_type.hpp
 * \author Andrey Semashev
 * \date   25.07.2015
 *
 * The header defines \c is_character_type trait which checks if the type is one of the character types
 */

#ifndef BOOST_LOG_DETAIL_IS_CHARACTER_TYPE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_IS_CHARACTER_TYPE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
struct is_character_type
{
    static BOOST_CONSTEXPR_OR_CONST bool value = false;
};

template< >
struct is_character_type< char >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};

template< >
struct is_character_type< wchar_t >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};

#if !defined(BOOST_NO_CXX11_CHAR16_T)
template< >
struct is_character_type< char16_t >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};
#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)
template< >
struct is_character_type< char32_t >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};
#endif

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_IS_CHARACTER_TYPE_HPP_INCLUDED_

/* is_character_type.hpp
x9ufv0uRJHyv5tP2TOr3dj/mVWvwudqtq3PMiw/VsWx3V5uLOoQdQrUXpOAi8hVnwN7++MHtOFd6SXu6nnad3ucn7XHyWn7SkvSY+vop0dlP3Hfv6W++7z7d3X5mLemX6pwwI0OPA8tBK2oqS6o3yOTQeB1OhoMl/zjz+n1G4LxkLun+6/fFkpYkdbJsFZhLitybfPo5h2McG+/dWbpePUPtGacjD9K+Ckf79N7tnlM4bG1qJO9kts2+uyjLvv9GJ7ru37ZNxnWSZ6AnxuwXLbAM9z1cy7hb8vQ23XvQd9utNsYi7bD1oN1B93TqYbqnEx/6nn5YJ+8b9Xp2HXK/bx7n7m/u6aH7+6e+vOKBN8o8r3OMJ+0ru59fk7QLWYPtZOhnk+56u397DtAxHNi/Rr1Vss8E0v4gacu5VnpN93fVVTstPTYqjPPwfYY5j1FP9zFi23ls9L6v24H3/U293PfVroh3HGNogH2MDPd9p12gL854/6GM9t1/xPZOynNdl7iOBt/7O1LHutY6tuveXzcg/Hu/M6/aoVUyXE3jgrzuecLVZ2meoD5hLfs09u8+z6rj3GOlu/5Wrnf1j/wODeu3Uv2A8H8n17fzGIfzO9k67kvjg20UOvnmBa526ZwozN+B6NrX1nhpm61vtkU5g/bptZM04hz7cbaxobcWgsg6HdKZNjY52+g+72hj8D33e5I/2/zcQ9sQcM7ac4w3JT3W1P5AXcI6jAxbdZ+R9I72mL+rHfdpw1hwXgNkrtI8wJ6ryPZf7G33HHWy/nChSAl9rbnLQLsfS64rDm/enDHw7D/PSksMPke7cpxz7PpVF1fpSRru/D5nYPjnac7A9o3jl4af/jwda/12SQz+7X7VKH6z2W2rqcirLGapP+CZlo6hIsnXTZ9PqZ772yLEhX6eda2kJdrHKz7h9MfrNM+nbHuihnPgc/Ns+dAs99sl9dj8rdzUot92f3DbK83F72/+7/ehafaVGcq35tnzlZnc0xd/36Of/+6Pn1t/amP8gYTzurw7p/0+NM12Wx+Ob03f79TdsA+idjH6fF7ykBbanqZXgD1Nk+r1NOh19/r1YmAP2AOehI3Ws2f4mOr1lv0Q1B7CC8thD1gJB8FqOArWwvFwA5wEN8IZ8Ho4X+2icuFmWAhvhGvgFlgJPwmvgzfBbfBmeCfcCu9We5Rd8FZ4AN5mt1efEcMuhvamanv7ws4wTds703pmCvurXjSSrXp/0P79I4yBJ2Ac/BOUYwTT4dtaj6XWM0A4Uspz+6x7Qsv7lpb3bS3vO1pek5b3XTgEPgnPg0857EdytPwEKd9tP5Ki5feBXWEq7A3TVH+Y9TwMdlP9Do777r2q39Dar1QodL++pfmPQnm3y2lXp3rdDXoXql4W7AbHWfXz6nMefZ60Gw70Hy8J43X8XQIT4ASYArPh+XAiHA1L4Bg4WcfjR+BkOAVOg1PhYjgNroTTYYnqrYEz4fXwSng7nK3jbw68H86FD8IcuAfOg3vhfLgfLoCPw4XwB3ARfB4uhofgEvhTuBy+AT+q7S+A0TSwEPaFRTATFsMhcDUcAUugjl99JkNfGMbvI9pfjTreHtVx9jWYCb8BL4Xf1PIqfKLlzdDyuiNFWt5ftLy/Q/mejdff/++znQb/CQdDD/HDQAc4GnaEE2AUnAQ7w+mqfxI2WL+t4Ubdb5zYP0kQ36Id4PN6XrwAh8MWOAL+EI6CP4IXw2Zt14/hFPgTOAcegjnwp3AhfAXmwcN6PXpNx8MRvR69odejFntc6+9i2M0wrnvruE7Q8y/Rcd7x+zLkefd51fuC8/zR/DGG/STq9SwJdofJ0LZvU704w/XhmO7nN7A=
*/