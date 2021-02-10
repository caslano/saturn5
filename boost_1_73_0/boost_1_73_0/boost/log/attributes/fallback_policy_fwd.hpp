/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fallback_policy_fwd.hpp
 * \author Andrey Semashev
 * \date   18.08.2012
 *
 * The header contains forward declaration of fallback policies when attribute value visitation or extraction fails.
 */

#ifndef BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The \c fallback_to_none policy results in returning an empty value reference if the attribute value cannot be extracted.
 */
struct fallback_to_none;

/*!
 * The \c fallback_to_throw policy results in throwing an exception if the attribute value cannot be extracted.
 */
struct fallback_to_throw;

/*!
 * The \c fallback_to_default policy results in a default value if the attribute value cannot be extracted.
 */
template< typename DefaultT >
struct fallback_to_default;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_

/* fallback_policy_fwd.hpp
pyztLPUsHhvHIYfPhv7otgtftjYq+HaZz/A8R2tnwdOiaXkPvWtm+Y1okc5Cv8awMBDRrTQq82ZXxlI6yCZ4sQdZeGz4qIL3Ws6eWTgimgaz8XjOavCdlPEmzjEZ/9h3RkbB05ZP7dVTd6zLrSeIbGuPY6E9FDzqzFpzG+BJI3Oa2p5jGXfOSclwXVDOwMR2Jt7CcMJ1Mp4t+Q7yPRj+oBbiNlED3fEjwf8xy3yXIr0Ycs7VMD1v2uJUnwff8rBoIjXUKkAGPUEnD3yPw1+ASUZx40U7KXXaKqMEhF0sjQXWWZ9azKZJFvpvkHukb8bb1PiTPixnlXS0ve2cFnTTqXUV5YOsaDLbP0n4wq8EbXiKM7Wu8xgmLvMtPIeim2oMDaXjJuT7Y1TXyGnxi5An2uXrRmG0+JVLyDQC04muMS+0VG61FrXXgIwWf3KpAlg8Uam5yWG0+I3zKsxBzbiqwJ2N30jfSHjPcY+LYWi0iCeTaGTcsLIwfCZn75xOhgZO8NOGnwjbhsNPotKSWgv+mdjDbuaF5YRGxmwY2Cp60yQuaTtQWTfZmLW7eKNyFf0kdSTJVtFlnF7kYQEfFBEOGzeXwS0bZkmWYvYg+xnzN8EQZqvPRKO3q9jVIGJRAU4Uh8cPiwwzaEp2HbFh
*/