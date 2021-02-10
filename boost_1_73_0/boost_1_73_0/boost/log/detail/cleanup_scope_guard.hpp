/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   cleanup_scope_guard.hpp
 * \author Andrey Semashev
 * \date   11.03.2008
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_CLEANUP_SCOPE_GUARD_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_CLEANUP_SCOPE_GUARD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Cleanup scope guard
template< typename T >
struct cleanup_guard
{
    explicit cleanup_guard(T& obj) : m_Obj(obj) {}
    ~cleanup_guard() { m_Obj.clear(); }

    // Copying prohibited
    BOOST_DELETED_FUNCTION(cleanup_guard(cleanup_guard const&))
    BOOST_DELETED_FUNCTION(cleanup_guard& operator= (cleanup_guard const&))

private:
    T& m_Obj;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_CLEANUP_SCOPE_GUARD_HPP_INCLUDED_

/* cleanup_scope_guard.hpp
zJcL/v6xUuRhAXuPesHXZ4d5f86jlEwuYcBjhDqczNme3iuWmmn4RU0JP6cD9STDhZG8K3tLs2CQjVw3ZT5HFlmCtexYs/CufydtxtewyTyTf4AhVt/Hx9mUFWdUNXCPVOmbvI8V/7MS7Flti2XkcnGEy62ZMyee5SAQlZfJSxI9WCfleMsTv+VfVscTnK3aFFtWBvccy/wW3QAyt2T3MpNk9QtwdhCZp374wouribP8RnGOypROfgwNQZ+QhSizJQt5RwqLARmvEDh4Dh08PFsM3xwz5xBR7dN37FB8+Yx7L06F0UXBjNKMhe1p79QXaPNax3xreLD6UB45rvNiJZxMIxniAZNUww6Dtao5pHq0GAyi9Nz/aOwszSPcyIdlNAqavHpZuxVNdLNe1kVCW/yGmW/uzKkr3LScsL1nujumQ54ouv2GvDVwEGYozBez82iO6yaKbWZtDk9bUsGzfvHvzc1NbKc/YtA5Ousc+tUI/053reZUHreVGtWAB8UmMH+yN6e0UuW1E5s2jtWJt1AxyWMzjcA3Qofr7NT7hgV9j2cfzUJq4rIstWovuvLD+250c1BG0fRlOY2Hl/xwhVQaH8oGfzGTR7jIYSG3HzbEDbrlyq7jJNGnLZQX5slLjqC7nBIdqgVdZXrL
*/