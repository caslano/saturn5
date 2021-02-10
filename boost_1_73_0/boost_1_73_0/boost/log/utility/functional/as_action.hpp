/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   as_action.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains function object adapter for compatibility with Boost.Spirit actions interface requirements.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Function object adapter for Boost.Spirit actions
template< typename FunT >
struct as_action_adapter
{
    typedef typename FunT::result_type result_type;

    BOOST_DEFAULTED_FUNCTION(as_action_adapter(), {})
    explicit as_action_adapter(FunT const& fun) : m_fun(fun) {}

    template< typename AttributeT, typename ContextT >
    result_type operator() (AttributeT const& attr, ContextT const& ctx, bool& pass) const
    {
        return m_fun(attr);
    }

private:
    FunT m_fun;
};

template< typename FunT >
BOOST_FORCEINLINE as_action_adapter< FunT > as_action(FunT const& fun)
{
    return as_action_adapter< FunT >(fun);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_

/* as_action.hpp
qdDM1yK0ZaFWqsalVqaN69Ga1YhIVq9FT12JKLYnsyAWEphiufwkiiE8uVl5WvAGpulGRGX8FgivEsFfGMOrYkZ86iKj+Xoi/99DPTXHW/V0BK9nWhsU0NfE6rTe/4jZf8TsP2J2dcxejZ4btM9tzw4wBaMghZNgSU8klwmRofTZURzQREgwbwQFjlovdGZ7IU+CsWzHv3v+xuCYqQDG7r9DE3ZpPYB66Rz8DoYGE6Jx7qzAodt+MP0+jHZnw4BJOimHBmL7+7ImS20mzJ0XEXV+SFCrEmJ3ilqOhUBGefm/JsCS0zyWKFHXEormLLBtExygLro2KjttoI0h65TrQHxg+Q4/wbntr3GUb9HY1szGkeuyJsidIlF0XMwVFPgBQ76qGtf+srXF2MLKDnYIg59mpERKaYR8Zyr10WTXYNtYaysEsMo/qZdm6lta0IwzVOsj5yYbLX/hLOx0CrMlu89PdPIk+KVZB00dv+K3bSmQV2IHtCZq4eeXsOHnkQejxBeR00U+k0KDj62CSSZuEAN4eX27eIHoeFcieobqXkt/FUpErp5EArUolLgpsiFquBpzbH6AURXushktemIFCO/AU6T7QPo/+CgbZMgcQCtfimBZvZWZB0RPvD0QX2Qmj+YEYCW5k4GDy7Bm
*/