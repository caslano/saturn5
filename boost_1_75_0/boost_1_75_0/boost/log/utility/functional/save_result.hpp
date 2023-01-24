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
df3sYvB+AHSxtx0FlDF6IgdW2WTo8wVf0L2nODwjJNqKXS4Vc0kiz9XfDkZMf8gI0xV+cFPWuD4MWrkIiFKQPM0eg2frSQRkph8T03hbuh3VmlhydE2nuyQOYmi0aBi7iaJ0alaaGmqA/SKrml/HMHEUk9iYBJusKV2aaiyO42LSDcAoUMOBVwxkBkJRs+bjsCXQY1o/xtRqmnIZ9tn6UtwbgUAwBVx28dsWru5d0zn+oLqm0gUrXUFP9S13Y2kHiUzKAW9oWA82VxkVRKC7iX6MikpNU5Rsb23rBIY2NnOOqEgMw3UV+a4kgZpLWwsCA6ITvBaw1AT8OTY8WGpPdnj3/Xb5zliXWpIaIOW16JZWbojwGZv1UtxnzPhBqzozRexVFzwid1uuvyRUwgPra0kB+R/VResxY4jiN42ITbOm2WboWL7sczMreixQZiMR4o7VDlCpdFwJ/QEra+x9bCffjgDk6dUWMTGbQZaUHGQAXO60Tf+ItT2qH3iqO9rDLGFn0s1ZRhn4FQ93byH34KS7bbU+GE637oCQZj6qk6OyIrOMmyD4AdgNDFKbs7I0qDY5cG8RuPjd6JIapUKzOIlAu9gd22V37Gw5jclx3t36XwJhTEnvbATqLoIN1GQB8bCQg80l/zbqp71lzgSXs8zjwiyRTQVCURHHRV79K4P3uZHqo0AR0QlL4G/vVPhPEGtGYYYZZR/Rletx
*/