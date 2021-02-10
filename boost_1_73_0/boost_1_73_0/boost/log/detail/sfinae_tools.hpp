/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sfinae_tools.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A distinct type that can be used as a fake argument type in constructors filtered by SFINAE
struct sfinae_dummy {};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_

/* sfinae_tools.hpp
b7JkExu5g6sjokMTKEOqzLBxpa7Szg3hYN2sjA4qe3HDUrbMnUcgYxIX4zSFJ9uE+aE9WSpDzY51TFtwNiSpe+U2rwq5j4mlarxlIe4DF5WO25yh4T+U3xfvb/4scejpvsFvjubFbwln2QzagznG8zZWMuiQ4Xa8GE1vFrgdzGaDyWKJ6Q8MJstE9ms8ueDRaxbzoIfaU2BxD72pjabyoPl+K291tC1MUxLa0TkjAsWm7qt2q7V1OnWEY4pM3S2U9OgVMtLa+d3J13/yPKYoyK75GRO6Kfwqu+UJ8O9IaFu552yrQ5aHjbz31kMJbO0PUEsDBAoAAAAIAC1nSlIxmgdTRgYAAJYOAAAeAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfaGVscGVycy5jVVQFAAG2SCRgrVdtc9pGEP7Or9jS6QQ8YJJ8auIkU2wrNhMbURCNM01Gc0gndI24I7qTX6bOf++zJ7DBL3U7E9kg6W7f99m9pbfz464G7dCTV+w/MS7cPceoNH/JxD1MHcfXVP+B6zPuTynp0S3Lddymp1muqeVZ4pWWN/wcx08p+sy28VePOT/H/IgVsDHngVlelWqeO2odtOnFq1e/UpdePn/5vEOHQitZ0MRJPZPlvENvUr/yWy4uL3etfNch
*/