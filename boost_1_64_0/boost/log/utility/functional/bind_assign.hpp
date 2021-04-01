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
0CZP3WOgaSxaxCbt2KLrsMdQJFa/qUXyQr8ihOX6hTQ3mkIPKDwmPMVQANftdAkpu/kzrD7aSryMJPxM4YOpYaoAzNq7PdiBQFKHx2izEJ7/RtUeyFn2C2NMK/iAQWhEBZEw1L0ICmHAzlB5h0i00YJD/2snJ7hVC9I1gHKJeUMyNLF25pp3b5ouUMwQzykLyxGRaEXcF5v2ZCg5jlBXor8dO3WvEQsd3DUnqSavO/QavrMHipz06VWyN1lVnQNhs0d3Uhp1pQmAjRl3vzh2uzgDRPlbBgrYpJYk3XVQEKWrmBIHq3vkZKiA3cbhWJDRcoQalQCdF/pKaY8HAXX25B4io/tHtVTe63NeLmG28BnkAdDWOsUx0PkiKV8UKre5/ry7+RdMrgr4jUBZyJBdrGg9p7xaOYekyBGXimH/a+z4HCne+/u7Dg4MJ65lV7lYXW6/lAJqZPFJziy7OKaCPBjQNGeeCyEao3Ev2AXRAGfEy1kPreGcfeU71qRasUdIcF9FgD1p/rk7niOM+Z/PYsbLGm5GZJChMIheyzJfOy+pu4vyUlR/oUrQEA==
*/