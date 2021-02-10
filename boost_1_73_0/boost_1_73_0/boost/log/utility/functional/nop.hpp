/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   nop.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a function object that does nothing.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_NOP_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_NOP_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that does nothing
struct nop
{
    typedef void result_type;

    void operator() () const BOOST_NOEXCEPT {}

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template< typename... ArgsT >
    void operator() (ArgsT const&...) const BOOST_NOEXCEPT {}
#else
    template< typename T >
    void operator() (T const&) const BOOST_NOEXCEPT {}
    template< typename T1, typename T2 >
    void operator() (T1 const&, T2 const&) const BOOST_NOEXCEPT {}
    template< typename T1, typename T2, typename T3 >
    void operator() (T1 const&, T2 const&, T3 const&) const BOOST_NOEXCEPT {}
#endif
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_NOP_HPP_INCLUDED_

/* nop.hpp
dGHEvo2nA9p6TmYF4H1eoCLzAniaC46s8Xy9y7OOeBaJkiG0tJQiUKjLvJO0LJqIGcYw6v0YBv7CD/zhZNifByPrCGDLOVMb5dFu0KPbSc6tIxQ8puMY8wyZXTGvp2N/PghGzh6tpIJrVlMy2vV9t8vZZPLEJ5dCvOBgstUM579oO9qey3d/MPP3wEyqfdx+UQTitijbiRRThstyRcPgteEXIeqHhx6mSc+fP2pTja215OZ0kdRK1mq2kNkKUuVYv02qxyVV0RwLaECEG5sAp08WfTOefjg2CL/SeQaxK+LFeDo0UNsEcEw17KoLbYdeQvS1eaadrYRCgtLZLelFrHmK61BUrSz1Kc003Y5e0ymJ4DOlpzft+263OzHTdFcNvdkN/cMoa0rjRyfdgAymPj02ZZleTyYuNE39/7ZRqPJVW/PH+gtQSwMECgAAAAgALWdKUhp0SD0cAgAAnAQAABwACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF9zbGVlcC5oVVQFAAG2SCRgrVRha9swEP3uX/FIvrTFi7t+WrcyFtJsDStJSVJKoCAU+xxryJKR5LSB/vie3HRlsJIvPROffL733ukJp69KU1CJq/HwcjwXo9v5tVjOZtdicT0e34irpM9vlaH3G7KTj4sE
*/