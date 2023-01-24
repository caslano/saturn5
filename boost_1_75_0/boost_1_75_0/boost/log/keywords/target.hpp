/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/target.hpp
 * \author Andrey Semashev
 * \date   21.03.2009
 *
 * The header contains the \c target keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the target address to send log records to
BOOST_PARAMETER_KEYWORD(tag, target)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TARGET_HPP_INCLUDED_

/* target.hpp
PcOxjgaoCLierrwKWBPjIvBzqOAy+95dYXp5ZAdg0P1JwQkUbvI4dX2G9YT7h7/Q/pLfpPDTIwKY4Jnd41CrHAl0aMDxF9gvrUuVhtn3i8UGcj1cCsO9NRjG+/KWLA+En2QjogQCf8Gp4oEM0IAnw3P982cbE8qkKlRQXLUZJfQxOaq6GLrkAYj1lBLsODoLZibahr9GQAHcETCiv3K+wMeZoLj/a27T/ifn/3NYzNb8H5W/DY3p+7sQLPnCp05jkf/ITmbeF42Njo1Ou+l80tNGTIuggx4dPuh2paD/elrT4M0uQb1cGZlM5yhv1uqVJE+cnVGylyGlkdzS35Rs9USTDJsRm4ULBk6kFBXVNt0Xnnjot5b1XmVvvCYMSifNeQnv3Z20HgmBr1wp/S9PoSfxRFuvixepYj9td75oTYeUC1awjeGLWth8mlc9QdPQ0BB/mKffMSeAkU1/cVJ8c62SmDA3RppH9OxDzKe0eUeIGB0kw4Niw1GH7IOti8ry+Op7DXdYojf12uFe+ZjuEaWOWi+5N9f6vWGHo2Ks1jeXuZabZwTaWcGvbfiofgHQzANdxEt/pvdI1ZHGGJtBH0loiBePFrfZHyFPZ7nO4LzlS9JuOJqQOarsY4fGVtHAbhM1j1qmL58cWNlwcIowNtF8Yye0YcR1SYjPsu+7qDbJ2ilyWqECayDstvRW+EhivY3g7e+dK+mWyX40
*/