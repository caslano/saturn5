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

    enqueued_record(enqueued_record const& that) : m_timestamp(that.m_timestamp), m_record(that.m_record)
    {
    }
    enqueued_record(BOOST_RV_REF(enqueued_record) that) :
        m_timestamp(that.m_timestamp),
        m_record(boost::move(that.m_record))
    {
    }
    explicit enqueued_record(record_view const& rec) :
        m_timestamp(boost::log::aux::get_timestamp()),
        m_record(rec)
    {
    }
    enqueued_record& operator= (BOOST_COPY_ASSIGN_REF(enqueued_record) that)
    {
        m_timestamp = that.m_timestamp;
        m_record = that.m_record;
        return *this;
    }
    enqueued_record& operator= (BOOST_RV_REF(enqueued_record) that)
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
OBamwrNhfzgBpuBI3WWRrl0o37q/1vu1zm+v7+9BaR1f6/WN6/QHPMyhLu1TX1+je99laf2cenmjengqyqh/h2gde4W9Xq116sb1aa1HU4e21p3t9WatM2sdGTk/deJcrfvWXxao6wauwBW4AlfgClyBK3AFrsD1v36doPZ/YVGZdAB8r/a/p/0+ALvGOhLm8shVinKjFqIeoS29a1RT6/9dPmv3Hc/tww3HeffMu3Jc64+8v7X7jmv9kT/62n2f9RfYcZxH77DO3+6fmF7i/uySkjmzCxa4HNYQ2+WDvf6Zk8cxe87r/VXe+WxYcXuPmBe5Qvl7TsPcfC6dM6bzGT8UuWmubHpJutG3Eo7epJMYM8dwMyqT910IPerlZp3ZGRqTPtpnDp7Dev8InQvnO58uys96/+gm5sjF2efImfPyiHf0zHjX9Vp6hqEZv99vP8HjdQ7TL6Wf6cHf9Wv7yM2/r9m67cavena9Jef4zR/7oefFBfYZlPmH0n9WbeRP/TbKfieopT7ngqTCNnAIbAfTYALsB5NgBkyBmXA0HAinwNPhdLWXC8+A+XAwLIZZcKGaDzrG/fn+nWPyP9R4/LGOxf8njMOf6DH4uKWB/sjAFbgCV+AKXIHrh7pOUPt/dnlp/+/d/veM73fuwJg4E5ODZHx/yrgxbHpyUV5FhTH+n0LbcYthnsM29DT+zy5akje7ssrVDfOumB9wMDdcSVI38teojHQclHvsi/u9E6lP+5ipXfP5uwzznMo5JcUFxuPl+X88mec3MlcndI7CQOJnoJ4LEBHEH9H3XqGow+1d1OO0j8MaiOKKpuYijPc4mIAfvk2g3SJxULKI1inW9JxvfeZSP8/M1mdaPY7dZj9z0M22Z9rO4R6kfTl9UG7UKagVNDxy9Jn6sucuLiqSvoTv4qSPpXieZW3keSLbw6k/R91xm/M3diWgdG1gE2fSj7fuI+h5Zrw+0+r35Wqhs+Ucimr8XmP3+7yiinTx+8pMu9/bw1qRTXD0O+6YfS1f98Qu5yK41G4sXDPMzxn9znbLrXbXi3krpz4q7DbvzHUjfgiXxk/DPjg8Ez38q3pRph7+MOJR0119iHO622aPR5JO89Nc7U3+01xVaMO8H7dx3jSB32V/XmnRJS4jzXHZ09y7ItuF+xkxQdxvwFfLm5GmrP54VgOchQpCDUbFxuOX4TZ/lJN+/Kb93iLbySn94I5tDwp+LTb3ukgQswza/EEO6cfJbrm5NrqzmKU4ph21p/Fi5LfG8RJlTUvOec1cMxtmOe8+yrwvF5+nGd8RbTaW6DtdgLqcdJnfEJc4WmrpA65YUlbk3Aecb4TB3O+mcF55RUOcF4t5gmO8qV3Lcwqd+4LtstrXjBftfb+mjNkvjGylISsuO+/3qvZ8zopx7AM2ZVs1pHWzn/YKMZuAX9yUkRNjtpNmCwloEmVV8OjWvcOCoqK5dfq+8n4mxcSqnWqETsdOVHS6eZ7O8hivjJFWnuvMe0x2yEPOaUX7a+U96ndH10rr+4q19uvqezDWWRPfRjoz11lXGnoiqXu6OpwBY+TfzDb8kfPFMYfnwuWkufqGNHdx0eLiuaxRbVa6q3dOd07pDFnbuIPK+hl3sMur24STbbusffLuEbJvHPPpImVfgmjTXn9LmnR6thln5p4I08StDx3TZn0L0ma9T37S8QZz/6Y4eU6qeyCxovmIq7BosbrnOcfIkq7NcHUVez3crTQ+qF2K/BHkjXCJO0Za0G9fiNgb4h7PG+tM2s6KpKxp7c0PYaHBV6a0HqmZwjFP+P2Ox4+Ub6rkhwR1d1trzTPtl6+MCo5vlG9iVW4/cmd45DrOMWWuUJkklRk=
*/