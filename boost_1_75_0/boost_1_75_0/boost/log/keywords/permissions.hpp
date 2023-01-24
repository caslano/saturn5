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
J4mPiDwBwg4xP7qHyot8RygnaCfLLGkvfm7Wq3GZ0XPRlJdlULpUqS01aPxE6JE5n88fTKUcpuSh8K7i84Dk6joDIH0zxMbkjagbO222ODid1EueVRokS98eM4/WneZcuOJWQAMk3BTMPB9a1MO4Fq1puba5Oe1KJ1LWqNzCOGnK5ArM7oJ/mfHYCRwG2QuZvz1mmIuECWG7Gg4rM9W/smfzpxyrEJd7gBC/KT8+ej+0ivgFKPxOFvVVw4C3b/UOTwWFd5Uh7OFpFrcFDurXHtBNSvQ6jct3hoaX+a6O0EbH49HwmNAFdkeTFr1+o8eZQoudVx0i5sTVt+VzyNNYzCtQB6MVwAIZLIWK51LqwtTd1stSKZVIzYWjLVNxi9UzLGbbYDhg+d8UipkbQ0GjG/iLvrnua4nVpuNKzJ2hfn5+ceQCbdYAjbmmsG4lpcCTX9PHNvGO9HMJ0JTAHSnA7lc4t3HwRbXjm6NG47a36Iq5IFJLcsu9uGKruu1SUMKRKaH7alBoeMgQIxeGE8Y4z0G0eb0L7TyVENIjh+FdcCHaXPhvy/utQiqbIcOsH4nfIzVKq3/GmF9DXocmshU607J20gofVpzWSDj2WX5LqfXzQH1TezCpU+yLDLy9LtH/dOmEBUHrp/gJ83Lf9gBZ1xUWii3jreKhew+tmgt1IlU7Yo8RvDfv2tPlDclASGcFcnLzmxXHZZR2XNBC
*/