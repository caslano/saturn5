/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/permissions.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c permissions keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue permissions to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, permissions)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_

/* permissions.hpp
4OowKzDlwIywTFu2jlSaM0OiM6tokRim1DM5PZ5tlK1to2rPNqr2NrZCLHKOpGob9cs0M4+P0qB+v6o/2m3Yj7LddhLgO94Wpt3GbeGRkE5vTdNefNJxVTqmaU1t5m8c4Vn92Q3ubwQ1OlwIHL/rk/TeR0hp4zNz6xzkyI2CppFdPk87yvPUpM9bfCjTInYdTq05HF52nrTiFjSHIMERSrBXRdhAzQabGfN28FzN7rSG3acWKFq018233aJz66k=
*/