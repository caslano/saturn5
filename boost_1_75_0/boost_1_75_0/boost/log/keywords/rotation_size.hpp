/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/rotation_size.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c rotation_size keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ROTATION_SIZE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ROTATION_SIZE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass maximum log file size to the file sink
BOOST_PARAMETER_KEYWORD(tag, rotation_size)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ROTATION_SIZE_HPP_INCLUDED_

/* rotation_size.hpp
vWXFjW3oQLtFJRPX5nlX6JbsBpHKXLH2Q/XDWkWiq45kLw7MXcRvQS5Li+g1PU3ap//trIgN0bezDx2x/XXdy8hGT7T/YWFWe5VlvjHdruIF/kf5ND8Bfz62Ybe8B7pnHgiMLZrIBO5miXPYgKAbvVLOWIMLJJw1vv8jSs8Mcs/j8hLTZzbxbrwyJJ0+fLLtVALYiyng6HEtgApAu6SXA5lDXY1gjgefqSTnjgsvPQfyjouS9jCmkmslSVQvfe7Jq02E6dDsyVdTAZ6mevrsj8+SJFMdDDANsUd5FTaYrikqLnmSesbSxUcbKdsWa2uZx9iujSocVK95alpfr5aVvZHat4Cgt4VgyT/c5zfpEJyXyM93Yar4BFRDKrqk504XjGN1zhZ8o7s/Dz5gmh2zBftbB/eLQlK+Akhc3sU/X8tjgGev5J5qP0HB2E/luAoVzyPwO5t2R8Hqayu3jJVaOZXaaTpdWonH7Z7vu09RvUReANrLD5Pz33kpepqk5iNfr0UAuJg9W/EC+uIGJpHmT0k6Hrizkh7Zyn39QjP0f8rYiHEFRU+ZDT35ofI+i74FwbKAEc9QEp8uWV+IP8qNdqH3DsrFh7wYwCzbEH1W4w3GhZkoGXiIPiT5cVahPsOJMBkigWecct3+KaAHHYTtU44M+xNp6HXLLObMx22dTTc1dmM6FJA+IoDxt0709dEfSamjv4+N/2I5+L5i
*/