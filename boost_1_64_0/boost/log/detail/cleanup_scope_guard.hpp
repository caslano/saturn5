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
nux/ExBFGgyBvtdWiU/dMj+CqYt7RjncsEZoEsgq3y3XN/czZFvcslCdGMo/EeY46s74QXVGGxsy65hwplmVk68VB13tRKso7PE/bt1+QUwtGfYh06AoAioneB0YMoV+unJlk92zYoz5NgFvmz/1vzJepCxrjc2fU+S4l0eI2a2Xwc9TadINtwzm5x0cIKNUw1kjBCXhLPXhi+6gvl7TsWT+ojb+AUeziLMFVL1eTQoBXy7baIJTbBNa1id5MmEmThGU8GbCGTfssIV0nfi+HR/mYTfMRJ1SGS2WUQsp7Piur2KCAPfQoIONHsns565/1VcnQi/SPFNPgprHcMAbhyx+wxeogvfqqUS4A1zUgsbp4HDFShcVuaDdxQmbEqblkR6IJ5IuzM5SAutcP4haU6rBetjPBQGYifDITu50cqOJUt0v/m6EBbvrfemqE2Mer6D9yHN/uFUTmT3pGW1lFPGmd1vSyoA3QU1AGBP1+Vxm8VAwdbrddi6YAHSLzdQUPHwJ8e1CpeKRlfOc3mEhLLPJtsalNLucq8QrFK1ie5zhb8XtYCB2c9Ok3g==
*/