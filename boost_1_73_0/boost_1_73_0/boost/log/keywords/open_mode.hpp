/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/open_mode.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c open_mode keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass log file opening parameters to the rotating file stream methods
BOOST_PARAMETER_KEYWORD(tag, open_mode)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_

/* open_mode.hpp
u7qrUbtINuF6cs39UDr6DE+22ZJRrZYgM1eQONuNH2T3G9RfwcpiP8w1xffQPrXlN11siRVEsRSr9Y6fjVBvf2HPTxx7NHJBKQwes8bxdZ/98osC/N13hSg6Uxh9950tEwCoQheTnwpNxV2aGoEwOw8NkDn8vldUZE45Y0uaUjfDXh49bqFgsULySP1VihO4Cihp7ODAj+5pvkBsHxxskvjTvXxkwsGqU/xaavSTwDhfH8H0l68k/ZQZQpX9YElaSbCXxwVSG06YQ23tX1OF9yq8efUgeVYTzQBic2cVDWCp23jF7wechjcsCdOPaNSFGTkcqG2x+igda/MZli2NwWK/d8Pibkd+LzchQ1wmzL6CD2nMnHV3p77dL/b7jbbOz/FTff/f3EXRY/dEk4K4EuGtwvVo+4fFvaWQXyz/yYviiK72aoiL5uleLy9ranejoT5owqJ8ZluVu+Yb6LqYRdmKSo4BTbG06/zFt3N5AwvTOnFduJJT2kFzt1Cs8iV0VeG0Nw94PujBMS9BRZXQ+I0rN0F2EGYH9/E2oXMsuk/Kz7CjWx982tDK3KVn7JIcVvCRHzJ11nkzDHt+r0yKrkleH5i71tC+xUU8HSXBz6h6M510oCOe4ryrOWvgQgeJY/9lx6HZwgHZghFR
*/