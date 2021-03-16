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
8BT5vNYJQyDf3NeGLqy+qKoyFKqnTa+pqqqprp1eyYRqOFlTU1lZm6utqvXOzBvVeuMhNPGy82fPOIzQruDz5fCGESScCLF1ImLDqBJmgwESHp2K0MIIh1EJH944ggTyRf4/zIjhQpsaDHI3AHc8YEk+KkvcedHrkt1KT5uJ0JRZ/jFZ2YBLhvuRLz+aZiEmxPlth9gCXPHsdD/yFUzt7MJ+OyDKwH1bwI/8rO/MyxEauJxycX57Id4PzFVXFPY=
*/