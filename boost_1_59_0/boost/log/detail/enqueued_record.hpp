/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   enqueued_record.hpp
 * \author Andrey Semashev
 * \date   01.04.2014
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html. In this file
 *         internal configuration macros are defined.
 */

#ifndef BOOST_LOG_DETAIL_ENQUEUED_RECORD_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ENQUEUED_RECORD_HPP_INCLUDED_

#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/timestamp.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

namespace aux {

//! Log record with enqueueing timestamp
class enqueued_record
{
    BOOST_COPYABLE_AND_MOVABLE(enqueued_record)

public:
    //! Ordering predicate
    template< typename OrderT >
    struct order :
        public OrderT
    {
        typedef typename OrderT::result_type result_type;

        order() {}
        order(order const& that) : OrderT(static_cast< OrderT const& >(that)) {}
        order(OrderT const& that) : OrderT(that) {}

        result_type operator() (enqueued_record const& left, enqueued_record const& right) const
        {
            // std::priority_queue requires ordering with semantics of std::greater, so we swap arguments
            return OrderT::operator() (right.m_record, left.m_record);
        }
    };

    boost::log::aux::timestamp m_timestamp;
    record_view m_record;

    enqueued_record(enqueued_record const& that) BOOST_NOEXCEPT : m_timestamp(that.m_timestamp), m_record(that.m_record)
    {
    }
    enqueued_record(BOOST_RV_REF(enqueued_record) that) BOOST_NOEXCEPT :
        m_timestamp(that.m_timestamp),
        m_record(boost::move(that.m_record))
    {
    }
    explicit enqueued_record(record_view const& rec) :
        m_timestamp(boost::log::aux::get_timestamp()),
        m_record(rec)
    {
    }
    enqueued_record& operator= (BOOST_COPY_ASSIGN_REF(enqueued_record) that) BOOST_NOEXCEPT
    {
        m_timestamp = that.m_timestamp;
        m_record = that.m_record;
        return *this;
    }
    enqueued_record& operator= (BOOST_RV_REF(enqueued_record) that) BOOST_NOEXCEPT
    {
        m_timestamp = that.m_timestamp;
        m_record = boost::move(that.m_record);
        return *this;
    }
};

} // namespace aux

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ENQUEUED_RECORD_HPP_INCLUDED_

/* enqueued_record.hpp
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
*/