/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_assign.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a function object that assigns the received value to the bound object.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that assigns its second operand to the first one
struct assign_fun
{
    typedef void result_type;

    template< typename LeftT, typename RightT >
    void operator() (LeftT& assignee, RightT const& val) const
    {
        assignee = val;
    }
};

template< typename AssigneeT >
BOOST_FORCEINLINE binder1st< assign_fun, AssigneeT& > bind_assign(AssigneeT& assignee)
{
    return binder1st< assign_fun, AssigneeT& >(assign_fun(), assignee);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_

/* bind_assign.hpp
M1FZSp7GUR63ujDjcN3ALY2vyiLQU+kUR0KUgVezFZ2ChKaC0mOX6h/xLeY78dB6/+wykd/8tlIB4JOl2evEBmhnT3HHs+cs8ypK+6lKS2DirNlIIJZZs/N6MftcB6HiEyUObzFGSK2WyMJ6eCoq5eAoaK/LWJRdvP9k3VVdqxptGyV0achCgPUgUUSGrz2vk3Tl35KAjN5F5hqhwAkcaWxS1ez6mMacFmVdcmoe4Css3+sVLBypkH5cvr91WJUVJWOELltpMR7PRRE4TeI4/6EY1eYP5chpmt5oa54WHB+AJHShcvcTpeXqB71tcBrKUtSANH01irjYSn9bheBuEKVJXc/GR+Ja5dPfap3zTxtEAfdht38COd1A1diByj6GHvmEAqPHPmMrdtteT1y775RjvouVvpc3ig3urzul98c31T2egsPV023tAX9pf0hVZuknefouvf9tw7ePfaflx/tNCKr5l4VG2+UpvujavL/hXtvYRdjRAYsKrb0RGuD++UfrUS7FkXLfnclqKsjtbeg9TRopVyd31euaFhx24NJW95Zg14ZaRqcGs7+f9WsjaSMRmK0vqmGE7351k1DLhc0JJSVOWMVamGPRm/v2B40LxPlM35savOHEPNyxmDxgS3DRwEhUrZOSBBRtD75dL1Y5+kup+0ud88dihilZbxjTwWXjeHQJu2rqGmc5hD412SWqk91utGMYoaeU
*/