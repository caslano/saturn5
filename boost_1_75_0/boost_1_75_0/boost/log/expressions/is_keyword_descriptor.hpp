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
wRsdSNkkVAne6DudjJeNVy98HkRadJYkcJYka5YkZpa01CxpiVnSKrOk1WUpl1nSwrKktWVJa8qSlpW9Sv0dZ86JOnUe3Ux/TxFMENwgqKS6GyGYIEispTUQ1cc4wTTBTYK7BFVJMw4xP+DsA3rHpKfWk7CXgC3ZBMGtEmX710yQIxiR9TX6B+7SQEeJO+fj8+K1IqsI0Svfy+n7yNqosW3kbFWZieuO7ZQ/tjFHdPpjyR7bZp89WRY9HrBPNOvzt8e/mXsbnDzMC8wHag2EDdnsOi2Po9u4hXiMEkwQXCOoJPrUOtUGqLusVf84/4NdgC0Xay17MMyBVx8Ky+06OSPV46nuYRnH2DB+OCwjk5bcriXe1+vDZ55qHa50lt6Eeq+9NFBfDSxrE/5Yn1yvaeZZMqbDr69BrLV9PvMt+dHB8k/L7LM+zQJLZnSwnNM0132acktOdLA8A80Qzt4e1zQVlszo8G2aThNN3qdZaMmJDn9/D+U6+7ie10qpjUupjUupjUupjUupjUtpHJfSOC6lcVxK47iUxnFp9ha1U4Lq/hIak/I6SnXTTn9PEowTlBPPdoKhx814xLyIefuc1R/Y5rJE2eNiXOa94vP6VFKXxx5b5iwFdeetv/e82bo+PJePEe8bBHXrTZ7bJb+1Tp6aOU+qvu18nPTP8jEGex4y/XTgIWMfceohZasTN/btuO45vemz9lgJjs0B
*/