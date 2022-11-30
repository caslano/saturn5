/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   contains.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided string contains a substring.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The \c contains functor
struct contains_fun
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        typedef typename T::const_iterator left_iterator;
        typedef typename U::const_iterator right_iterator;

        typename U::size_type const right_size = right.size();
        if (left.size() >= right_size)
        {
            const left_iterator search_end = left.end() - right_size + 1;
            const right_iterator right_end = right.end();
            for (left_iterator it = left.begin(); it != search_end; ++it)
            {
                left_iterator left_it = it;
                right_iterator right_it = right.begin();
                for (; right_it != right_end; ++left_it, ++right_it)
                {
                    if (*left_it != *right_it)
                        break;
                }
                if (right_it == right_end)
                    return true;
            }
        }

        return false;
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_

/* contains.hpp
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
*/