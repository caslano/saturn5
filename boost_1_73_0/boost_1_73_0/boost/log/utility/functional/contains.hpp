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
mmK+jNksSKBuNuDX169/hxfw6uWrlwZck4hRDnZCowmNZwa89fXIXwF5eGhJ+qcBNAHCW5kqJ2ASpJgm9ySmgJ8582gkqQ9Egk+lF7MJ3rAIkoDClHEKpjW66w8/GHAfMC9QSpYiBRmIlPsQkAWFmHqULVY65iROQEwRjsp9JhNUmCZMRC20TSGhcSiVDmWecCmALAjjZIKGSAJBkszlm3bbS2OO3rd94cm2l4ffCpLwMZI7dCIkSxDzBBIBqaQGKEkDQuGzqbpiQnBwnk44k4Gx9gZNRX5bxCAp50oX4hiVK7cp2Fl6DCUGc/SYJeoiRSSVqftAhFuCmEelZZrGERrCPKCQLzDNBqRIqlgL68hzE1lOdYILp2btrw8iQmfgomND376ACZFMGvC57/SsWwc+d8bjztC5A+s9dIZ3StlNf3iNU8/QWAz0YR5TicZjYOGcM+pnNp/vaNcuWeTx1KdwkQjBXUmTdN4KLmq7D6YiDrFIJNUP2zr0j8SLhVRzqEtPYLJJQusNfNauPTaerM+Yva55U18YOPENlebvT8hUU2c2rf+Se4KirvzK5nWFaRQhAAtZpjyBP6C+aFyVEzZDoJUVqFEqvoEAmMSUfC1Xv4H4WS24hfipeMpp/WVDZRc5xsU9BhYKRdAp
*/