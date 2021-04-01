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
tepN2iNWeTOPWoFRcSYPKfS32LvjGaGp+yYYSRnKfj+2kJcIIOQLKr1I4MnQnUxN+KgNqGQbdvUooL+nFanzLafDnRxaUuGpYhkNF2gGZ5y+qPdSSST27wx+EWqiRednJmuwIkYxDfkFcPRFysScGm30TreM9n3jehwgrluV8v4hhZZzx8v9gRIYQVK8YQYPubVO/iOgX86w9LZf2eS3+dihU74mLuDsYIBG3OqYGHtddXadHaIRpqVQ5AD9TIvw0+JZew97eJhaHYP4tyZ6TyM0Y+e9mi21sd/EPzv5qodNyyOR+tw5l2mDfKNofyd4CCkoWDQJlJ37RlgN1E4BO+g+L2l84pBw1QWx6VBTtrT+XVUQ3iTbhhATrdDq7gjU8BNi951aJ8FOXS0fko7q6v3pxCjYG2hwlhTROJIRPYW6iyvDD3flT9M9Bi4Q5Y63X8h4LfCeS3WDeJT+vSJsGnxczJ/ePynF5fGbhyag8R0ElaFHB1YadF/cwz6wdzH20LDaRYOq2Y69hKrowXpOMruVV0ZtY6lwVuy2pId2K2msQXAcTyL45jFSAA==
*/