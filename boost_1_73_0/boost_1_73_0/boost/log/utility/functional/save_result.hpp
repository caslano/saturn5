/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   save_result.hpp
 * \author Andrey Semashev
 * \date   19.01.2013
 *
 * This header contains function object adapter that saves the result of the adopted function to an external variable.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_SAVE_RESULT_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_SAVE_RESULT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Function object wrapper for saving the adopted function object result
template< typename FunT, typename AssigneeT >
struct save_result_wrapper
{
    typedef void result_type;

    save_result_wrapper(FunT fun, AssigneeT& assignee) : m_fun(fun), m_assignee(assignee) {}

    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        m_assignee = m_fun(arg);
    }

private:
    FunT m_fun;
    AssigneeT& m_assignee;
};

template< typename FunT, typename AssigneeT >
BOOST_FORCEINLINE save_result_wrapper< FunT, AssigneeT > save_result(FunT const& fun, AssigneeT& assignee)
{
    return save_result_wrapper< FunT, AssigneeT >(fun, assignee);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_SAVE_RESULT_HPP_INCLUDED_

/* save_result.hpp
JzgYovsJDs4d4sbZP5SH/3cL8YSXi1H3nA+JZHiDPIljHIY84aiDiL3KRVwLcUjoPs4Wb1lE3ou45ArDInJkm51TmyrgaHSMz+fnX/AJZ6dnpykupVGksQhk1uQ2KS6KrvKjko+PA0/fU1CA1IM91bJSHt6W4UE6Aq+1ysl4KiA9CvK5U2t+UAahIpRKE0azm9Vk+ivFQ6XyKpLsbAtf2VYXqOSW4CgntX3haKQLsCXDmbxQPjBhG5Q1A9YmBHK1jxxRXmpvIbdSablmIRlQhdD4r1mWt07z9Flhc5/lr9sfVKH+u5MVD1HLHWwTECxaTyliZ4raFqqMmQ3hYtOutfJV+jYNS5kisw6etI5cjFPkX8YmLPb2pLENDU+sQkzeGh+lHipb/9PIPkaWsnWGhdgHbios25yi5U/Kdc3dzl8l9p52Br97NG/zFrCGh0FvuMBk0cNaeuVT3E2WV7PbJe6G8/lwulxh9hPD6SqS/Z5ML/noFYs50GPjyLO4g6obrajYa35cZElfmVy3BaEXrNXCU2ibQdVLkq1V0RGubazwmqg50tZsUPvjb0nSJ8Onhezk3b8VMPkzUEsDBAoAAAAIAC1nSlImtrJlVgIAAB8FAAAdAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xf
*/