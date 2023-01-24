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
ThuW5wq8TZnSlUyf4r5/V1p33MsSiDSZWPAv51L2V83HCYCoOyfeKdDGnU0EnwuAOuv11QYKC6pTQWSp2Njeze/1ViuWstL8ZEeHRtBcSHjSmqYurnty8CnFUeWkDVs5oZKHhn3sq6M2gXTiSqKYil4U3OLA9TE7C/VL+fy6KVPv4HBpbonVwQoQ9RuU0X8s276HwVkn2H1BLfGrzNO05+fJPIr53VbWkTh5lqiEN4JyhIUM6laytWbvzLG451qUsSMfQHKq2Le0sVrweaQDYA8xzi1pkfVgbelwWufjfGHD8riK6pzc94AAcTC1PRtS5RFRTmJNgufhgVlOcU6YEq5h/nVU9qEZjGmXMyayxDApVNvjx092lMSNBMduJH8n8qtVdFKiO0XJwkzrNTROjkjb6GmTwJZx4rEper504zaRvZ8/VBkL3TKPLrVtkw76iGV11tbRBzVvLhLOuvdUjjGZvZLn8eNAvR0nrzODlfbsTP8O25cLD4nCCN3myKaQNItV/4CyL0pNhDLPEKXEVh8UCc3bxngsywQPdXf0S7YYFVS9ODXmOntuXY8MtC6bAH0tBYFHFrTP1nrYxo0ZcMteLaVTd2dVVNCWiCdpCmP327yT5Njx1NfLEzFKOHDO95bk7rZJMUKp9bPi9snBFUqv/PGgTXdA42lar3mIUpLcxuv7gAlmMq2NaRakBNvYrNDYzjc5hemY3oZb
*/