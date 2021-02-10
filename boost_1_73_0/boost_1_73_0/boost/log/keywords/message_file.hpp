/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/message_file.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c message_file keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass the name of the file with event resources to the Windows Event Log backend constructor
BOOST_PARAMETER_KEYWORD(tag, message_file)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

/* message_file.hpp
zLvKzn3hQMruSfKK2Ge2Wd8ELHYNKz9SXOecNbel6BwP1qblpzHRdBNlBykNAxlMnRkRHCzWjMFvtB8t765pGPiV2Oef8zWiS3qxyuQTbSU5C/zwH9JI6p3QT6ZskE65rUvssluqYo/1ulDgyyVVakgToyiJW14cHKB+PMCyUH4SlIgHUqHiE6+4lkSSGn5Euz/OsasdED6v8nWVsBEHuCxpw2WHU0YU8GzxeuNUBW3S/XVSUFYqdmKAQGvBMU7b13IZWTukSJGSlYrPrt4mfxxazxxY46o9al+K/EXs54TfF9B4bE6TKGjeLJzdNT+z6aAm0ZeFS3uLg0EcBQeXfjZbYmWd/ZYNwxyCGaGr+NQWJw9D5Pf93/f3m2cWefZ4O3tYosy8HRQw67YbVHoIP1BqA24Pctecl9TjWWM4fDGWosf+p4whc31hldAu9qXKvCJicodcICPNFWPVQcsT/K7x2NQ9eAkDp6VBY3N2XV9IWltTUEZrpyzP5RfFTzWE1TJWgtrhBqhHVTLSFoMlsuFLLSUTZg1ryS30dAh3X2IFFXi3jKfrCLicRsaU48+/2lbS5tRhL5nY2T3q/FBpN+mdVNpOLg77f81+KuC4e919QbwOcaXJCKP8NT8flZpEk9NmReQsw0q4o3au
*/