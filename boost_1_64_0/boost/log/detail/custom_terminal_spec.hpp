/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   custom_terminal_spec.hpp
 * \author Andrey Semashev
 * \date   29.01.2012
 *
 * The header contains Boost.Phoenix custom terminal specialization for Boost.Log terminals.
 */

#ifndef BOOST_LOG_DETAIL_CUSTOM_TERMINAL_SPEC_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_CUSTOM_TERMINAL_SPEC_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/terminal.hpp> // needed for terminal-related part of the grammar
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace phoenix {

template< typename T >
struct is_custom_terminal< T, typename T::_is_boost_log_terminal > :
    public mpl::true_
{
};

template< typename T >
struct custom_terminal< T, typename T::_is_boost_log_terminal >
{
    typedef custom_terminal< T, typename T::_is_boost_log_terminal > this_type;

    template< typename >
    struct result;

    template< typename ThisT, typename TermT, typename ContextT >
    struct result< ThisT(TermT, ContextT) >
    {
        typedef typename remove_cv< typename remove_reference< TermT >::type >::type term;
        typedef typename boost::result_of< const term(ContextT) >::type type;
    };

    template< typename ContextT >
    typename result< const this_type(T const&, ContextT&) >::type operator() (T const& term, ContextT& ctx) const
    {
        return term(ctx);
    }
};

} // namespace phoenix

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_CUSTOM_TERMINAL_SPEC_HPP_INCLUDED_

/* custom_terminal_spec.hpp
DqHs6IFsEDuqxI6FMBougsPgcng1PB9eDy+AN8OL4Gp4E7wHXgqflu1n4LXwY1gPN4j/l3Ax3AKPgj/B46Hb3bQ/BC6CHeFJMAOeAmfAU+FsCTcHng7zZbsAHgtPhcfBZfB4eK7sJ/3EI++QMFrS3xFZIum/VdJ/G9wD3gH3gXfC2fBRye+74TK4Gl4A74GrZP+t8AH4PnxQpQt/SdcjMMq7LfbMMN7D4IFSLqKQiWLPjmJPb9jZ0h+UJuVrABwBB8LRcFcpL2kSf7XxfgOzJP4YS3vfh9LPtA62hx/D3vAT2A9uhDvD9XAg/AymwS/keF/CTAk3BX4ND5ftTSp/5B0BLpPjxyMr5fhPEC4UPgUj4bMwFj4Hk+DzsDt8EfaFa8Sel+Au8GWx51W4F3wNjoXvy3l7Ax4G34R58G24GL4Hj5Fwx8J34cnif4b4m/2UUm9zlf32froD5PxMhFFwEuwID5LzlCn5OEXsnQP7w6lwNzgNDhP/4XC65OdMOA0eJvk5G3oknJxXefYgbs15nSd2ecSuXLErX+wqELsKxa5ysatI7CoWu8rFrvkwU7ZrQwPrJ/zlykj1fcGISfQjIb79hhuh97uM2MmEfUTfjzhjK32JW2DMQcTH74EHBdavuJrfjUifTPYjp+BXAF89M9S1HrmQ7Wq2ffscV0m/4xpofNOxMbO5DzJ5iv9+yGqfvsiV8DGk4ZswV8xZoS36JlPwW8/+qINJO9upMAMx+ip7PKr/BqSafSuQcXuzH+r6L8cRdya/y5Ba5A5krfRnzmbfSriF7db6NZOnESccCDMRo4+zYJrZz0kBxg8x+jvvmGb0eeLvteFRmQP2kNb7PxstfaDxhzb3g86GNUgdYu0TXfsnvjGZgV81sgJZjfjrK92A3ztwJfZHzaAMIRORYuQMn/7TOraNPtSn+L0O8e1Ldc3EZpgKxyPZ0q9aA1cgjfx+7oho1wYkqija1QcZh2QjNUgdcn+R0+fqOMc57r/jttP4//mEbvP3/971/UvTea5V6/+LDaqVzDu6oGl9/2TL9wGp0gcXIWkNR87joaxsvjlm/SAimTp14tb799VYeGm72yDfz3cK4Z1GGEK8jQUqXgwKbt4B9HTzDpht6scUevd3dx8s7fDxbF10hNfvQP0Y4ALt3ARmP81OKr7n3YvcB2na9uz6EXjyFNzUT0lW/PL77793VPofuL37l6j9tHVJ/Ilwi9L/wf2FO1zmRbT2V0iftQrznXu9O6L5OOpb+qY82sxx4prb+iha80utfeaXqfRPcXXmjbudqV9i5plb2fiV+2jXEW6fPFPp2EL84SrM5+481yyVLzfFNsnNXoo0kqCulKl3oVduwG8T/B75ERmc1LR9eGclKmwNYbrBj/Bf0yyqjJG/pott0Q8e3rlO2USCPfPbNP8DfioPI5Sfyldb+/NS6ffk0VDZ8RC8mLCriowyHPzcmej6mzvTbKcdUuIN00VXbtEPfC5Nwvop4/JtgNq/KiQ5JEz1Q8QaOqT4YldUiNk+bYlLV57j4axi7/4t7qNsZbVqqMvS/pxbIn0icqwJSicqxFs2j1Lhy1U6NnJObG3Ylj63R5UdN4Z0CQl3VSPecCc0lev5pZXNY07OVsdaxDV0X0p8uNkPc6HyT3C1M+MvNPunB5VIP5bU4a/VsZaG5ITEWNJUOUTquSo7U1Uafnc3p6FCpWEL+yz5gE5z3R+jdDqHnMt4kXLqVXdXc925yadedU9pqjNHc8J+SrT/HgKlrilZwjb1StWpVdCQHsSRJjrGWBPQah0bWarqWG55+V81X2pndZ6PUn7lanuLuV2hxiP8os4H7Wrp9ntLKgeW6JSLR3Y=
*/