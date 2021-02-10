/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/enable_final_rotation.hpp
 * \author Andrey Semashev
 * \date   27.11.2016
 *
 * The header contains the \c enable_final_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for enabling/disabling final log file rotation on sink backend destruction
BOOST_PARAMETER_KEYWORD(tag, enable_final_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_

/* enable_final_rotation.hpp
wd/H+PfdEiA01NOX7JkGRn65QE5q8OG32HGLODNeiCfNFqHbPKNmgJRquQedNh9JEiMW370wqIPoLWarOA0aAkQuSwRJpSyhyNH7dTreBLPQX41xbXBCIquDX4RihlYN9pxmfGnOwFQEXoOJJYYGfiQ48CnKMGg4w4XjswTWHJpN2rqdxUmCETSEU8GAJkpfwn47mU/oGvnw4CWMDjxsL1msNd1z0X79vzre+/bo1Hpy0TnV+aKwYjh7qS7PTPlvaAUBwsAEYUh5ya1QZFKSmNy+Fxbp6+uLi+7IG/f+T5c1jp89e3r87OT7JupdUvlgxCgzgD2Vv6XE8YswAQpFMfcYxBxUt1tRw5WvtUPDHbS9Z7TgBgiqoyi4Y0/0d094SxECRP8ymCMVwNTkkT3Zl4aUshTsjhpOdJ/Cn2KOXa83SNcNLEDk0njWEMvO8S2swWOaOVh+e5umPlkOy0N+qEbQlIYCpzQoAxDswkrISQqI5GN+wQg7TYFCc3RwOLUU4TcxikRYV/gYaSynw4R98DJCZSOgmsBUKw5r6oMWFABRPwTJ6t6caQSwOXi5SYJbHedVDjq+deKJIcoc03IybKTwwgmUf8MceZ/wi+++I+bjEi+LwY5k0XY9hS8NriHL0zCfxFS9E1KPjQKF
*/