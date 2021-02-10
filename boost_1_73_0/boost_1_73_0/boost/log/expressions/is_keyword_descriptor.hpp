/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_keyword_descriptor.hpp
 * \author Andrey Semashev
 * \date   14.07.2012
 *
 * The header contains attribute keyword descriptor detection trait.
 */

#ifndef BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Base class for keyword descriptors. All keyword descriptors must derive from this class to support the \c is_keyword_descriptor trait.
 */
struct keyword_descriptor
{
#ifndef BOOST_LOG_DOXYGEN_PASS
    typedef void _is_boost_log_keyword_descriptor;
#endif // BOOST_LOG_DOXYGEN_PASS
};

/*!
 * The metafunction detects if the type \c T is a keyword descriptor
 */
template< typename T, typename VoidT = void >
struct is_keyword_descriptor :
    public mpl::false_
{
};

#ifndef BOOST_LOG_DOXYGEN_PASS
template< typename T >
struct is_keyword_descriptor< T, typename T::_is_boost_log_keyword_descriptor > :
    public mpl::true_
{
};
#endif

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_

/* is_keyword_descriptor.hpp
hYUJkrgL25qMzqKcdbB5J8wTcu6cIHRmMOQYWhiT5j8fHLhFFmL1B17i5gdutf3uwkSrnXzCIiLnnpLUkEmoyHWbWLJNUeIFPr/DIRhMi1kY5Iv2ejUwFXsHSUa5DkPWhXmBzu2yNU1K97RZjFKsODD8lidxzqaWiyTaEIQfWYtfZDEMwQ8Q8hK4uU1F7OlMhGXnlYnSp+LgJ0OzXq9HSYzF0H5/QsPJPs2cPMjb9HE4/XB5M6WP/evr/nj6iS7PqD/+xMp+GY5PEfoAxjLSX9NM5zCeURClYaC90ubf9zrYexnEblh4mvZNkoQq16ZIu4v9vfWDt/l9fpAbB3F8x8O+p33sYfzjm5qMcRdOxgIvdYwwruQ+9H8dqMnwfNwfqQ91ncE8BrwfT7iZDNR4MqmJxnlqNa9G0hCujp18YzomB7Gmwbj/fjRQJzfXo9/U1fVwPD3bO2gxzigpMkqWMaVZEBu/0UTkY5cxntOGIxjFXzd9YJ3j+nNGPD/afpLEdzozO554Sb4M4h0Ponye7xhOgFjH7LKROvH9rb7f8eQu2qUpcnbaDYNZEPuJ7O9gjWDmlGTZCfUdeAmx9DoLx70N4jnyMUqyewq1c0smKwc5xfIgAgVkXbrJMcSaOEegP3NEnjW5CQz7mWQe
*/