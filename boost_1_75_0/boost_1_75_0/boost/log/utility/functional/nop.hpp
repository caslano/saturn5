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
xbM5yKyJvuusEm+ZulQ6ahpx6Un/Mx90Y+VutHROdQ+o6RAt8+zqQk/vEnn4ZjEbU7sr7INznQjXoMILnaeLMbNfszJnkXRpFuQAgC8HgdiJ58RioCFkooxWFd/31QehkXZXV9z01+YhzF73QJCPjXJXmysvj5UptJxgKAbB6OI9njs3tobEu6z27Z6a/YQA/mZREbz4zhmsr0hjenI7Ohq6aMwAdtjWxHWoc/ro6rdFclfbawZan77yfz97YHPayaU7EsjLDLzCy9XtClfK02nlpBDkujBYiJau4zR6E3AbIcgFlVacRvdQ8OXKpURir9tJJNol90kNMM+xyRo1UsStm2dFc2hrmFLflct1DLyxz3HdHJf/aCg4wyCMlTIOlHw6Wx8mOhishnCMTjKlfK01Ri0/WN/7NTHqo5KLIpmQxkhNQ7KK1CnJIgcOfwmk9PzmyNA5ISFXt82Bv9LCtNVGpjJG1/pVlsiWPUKBkRi1v9jQ5RMAWC90QozbCJoJdH1FePW2ajC4us7NY0mfigF0KS7TPHztch0nQz8BVptEYNQjU50lv2A2He9u+eMfAqJl4deFMdubL5fh+V2Dp2AXt6J2YSluoqcMkwH2SZe58ZCxiJUIH7cyhVW2ZA3eLNDelEr3BVgj5bdejpi1nJm5nry+q74aBJAbciZF0HvYT81FjoOdMjz/EsrD/2jsK9+mdIRWNSlFDxue
*/