/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/incomplete_marker.hpp
 * \author Andrey Semashev
 * \date   15.03.2014
 *
 * The header contains the \c incomplete_marker keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing incomplete marker for the list of scopes to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, incomplete_marker)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_

/* incomplete_marker.hpp
GrOtqtbhHy+pNtn8wgMRbMpd0T63L3aebNCZBOmYV3lqr1ql8rG0CdNvO3dP+asXCKTzqiQM/gWrs7G1ZOC0Cudhy53E9OeEtmPWN3bupqC2vt37U2mbuR1bAZCtgB1JYZclLv+mjb3t607qqg6E01ZXG/Ll8Cqc4mRrBadxmW+M8g+DtNB26J/TvkL1dw+pPq+tkY2dPqx9qpwlnG1mloz16iWoiDU9QnTyTysnZTrrR6VeXHpaReGnEj1WEuNui4yldjD7a/Yotgyj9AK/mjPgzsNVyYeyUavJXyWiHLByiJ8fTNf09SrDTQGPOkt/h8UNBTlLptUMLroeHpovz0MS1xIBMd64Y100L9D15LNeXdZBg7W1Bykq8pzZhfAxJ0eMjZVHRS9/e6oocnSbmQhzrPIH7kCqqCUCePuOccbJKJVsevJ2dgQ6BCqNKp00WmHyNdXNZLE7AkfXN3XcOCBRj5Pbm+fJF9vvkUnZdfQExjVBHdh4QidYDhkc3uRkHOULY9mL0FsskmXtY90z/7SuEmv8CXi52RSyYWHT8ge3SP6vz8CmkGoFTo5K49b6pU60KYMTw7KTxbsCbicONZCk7/bSrlO730H/iAm1fwL11bzmEI15UTt8LyPO84I8UYoRsdYptCHpqlGRfGPdkr16dxZw/NrnGwc3u0faf1x/63Uh0nSRYm0s9fh7Emz4dV7596B/wc3+vcnD
*/