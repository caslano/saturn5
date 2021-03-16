/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/order.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c order keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering predicate to sink frontends
BOOST_PARAMETER_KEYWORD(tag, order)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_

/* order.hpp
ooyQ/ExR/5D8TNG4EJ3W66KT5BqgC0L0vqC7MkRb69yfhOiVOffxEG0cc18I0WkQLswp8RwM90CI3hlz8WCbONB+YdoT6uKHVJcAHS7bhTsxTNsB3Kow2Z3uCtma3JvCdMi+uy5Mrd/9ZZi2zbhvh2kfpPtxmN5wdv8epuP03a/D9Fkh94wIfUDJHRAhV587NUJ+B7cwQp4I9+oI2XhuCdAfY7xA78T4gEJf6z4CdCPQbRHyUrjPRGg2634RoZ4=
*/