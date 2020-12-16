// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
// Copyright (c) 2007, 2014 Peter Dimov
// Copyright (c) Beman Dawes 2011
// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_ASSERT_HPP
#define BOOST_GEOMETRY_CORE_ASSERT_HPP

#include <boost/assert.hpp>

#undef BOOST_GEOMETRY_ASSERT
#undef BOOST_GEOMETRY_ASSERT_MSG

#if defined(BOOST_GEOMETRY_ENABLE_ASSERT_HANDLER) || ( defined(BOOST_GEOMETRY_ENABLE_ASSERT_DEBUG_HANDLER) && !defined(NDEBUG) )

#include <boost/config.hpp> // for BOOST_LIKELY
#include <boost/current_function.hpp>

namespace boost { namespace geometry
{
    void assertion_failed(char const * expr, char const * function, char const * file, long line); // user defined
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line); // user defined
}} // namespace boost::geometry

#define BOOST_GEOMETRY_ASSERT(expr) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::geometry::assertion_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define BOOST_GEOMETRY_ASSERT_MSG(expr, msg) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::geometry::assertion_failed_msg(#expr, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

#define BOOST_GEOMETRY_ASSERT(expr) BOOST_ASSERT(expr)
#define BOOST_GEOMETRY_ASSERT_MSG(expr, msg) BOOST_ASSERT_MSG(expr, msg)

#endif

#endif // BOOST_GEOMETRY_CORE_EXCEPTION_HPP

/* assert.hpp
gmfOa76zpZKWyFcZor7KsLxITfUxf5jCrxIvldRkRQhZUp/NsBJxuardf7iia/dyHWeAxHneEs6xVzaw6HhSXHC+OG+SZX9h9ahO7sGve6vOA4mmZMpr/EECF0BNvQT0VN/Jj7/uXC4LJCHZvd4phRceGhcie6odKE+CMPRLqYyf6fEnIIHQeq6jJg0m4O94WJtpHhQuzD2qMBktCrMCT1J8KZI3zOoW2rNnkPM/nMIdKoWPcqNT8DKFAfJb6yXQYqmWFYeCJ8YJ/+8xuM+YTv7/RaFV+sTz9So9X4r82jppwoqDamEXUkCkyEDohScWHSVo2iLkjqq8ptt1SMYxnzrdYlGxqyJe5o+QCMLmioOB7i2WId7mt3uoW5LAFHHU9FzhXzp0vfqlk1zRhOgrBl8Xvq9ZulloCkPUFVVaxnj3XDkF7iphD3WEi9InZtpO53OpPO89jc8L5fl99cxztrfUc6U8v6SeV8rzJvW8Sp7XqefV8vyImj4bAtzhOlhBbhutXGUVKWuKskqUVaqshcoqV1alslYqa5Wy5Fek0pUl8lhPiHbkqxipTVmeSHkqIuWpUAWpcCurSFlTlFWirFJlLVRWubIqlbVSWauUtVpZ05WlynOCbPiKDmbItSH6eaz5qov6UWXVD9CijhL+Hwt0+I3VRX0Z+Pc4yD56+s8vaJH+QEbpefT0f6bC5xsbsR6tLhrA8B8uOmr4a1qm35/h/3j08KOj8t+HgT/9/rHy3z4qfDrD1yP8sfrTG/6j9SetX2TrKOlPGHrR3juw7XM0X9OVz7ny/IB6dsvzXeq5SJ5XqOcp8nxT18gAsUA9l8jzd9VzqTxf0VX3p3J7uD+l2mklKytNWQOUlaWsXGW5lSW/zLEnPF5Jz1NWqbKkZNIB7V9nf4paj13rC9exLMSUdO+15F2WQ7SZ6pBD9zSUVN50h0tVb7rfpak33f1QC6guPEg9SFdVlltZRcqSepAupyypB+mxyspQyT2okpPqMG6Rro9OTJ8flmh5rynmhV3DNc7d/w4LA5SGAwxVAXJDAdaoAAvDAdqrAO5QgFtVgHIdoKP5QUr4+8lZjw+elWHPF5XnFO15qXDVhj3XKM/p2nMkPFeHPe9QnqXasyc8V2nPM82FKZHmIWf5MrvfSLJ+HjOOQWAZrPjZttA9oFZqf8i2Yr5oz9hhxTqi0jm0GMPdeD4WEtUItw5/ajVh2pLY2nXXKs2WrmWIx6R2ka51aedI1xrfOdK1zusc6VqZnSNdq3/nSNfq3jnStZydI13L3vmwnZ5xy+PypSFFMHrpfapX0f8+g0W5bpz+DmHBAOXSgOuPFj73yPClxwq/8MjwDx4rfMaR4adL+BOhJ9BUXqNLtWAUj77QlW2wNPAqKSxFlJiPdFI/kx5qP906SrP8jTw3O4XQ/bZOUZ036BstjUtH7y3CIeaEU9Ct7uVkppCrU3jRLFIpqFh7mYI7ksIr5qBwCrqt/kil4NYpvGB2UCmIA5eCiCrJhPsl7mW3Cynmro4qpTNDLdejUpLn5iSzgWVTsQww/Oth3J3N4iIz2cy17zQ8uOUhGQ8S2pegNgt23DX+a5JyT42J7C/le4dFwXrnhqYKj2FC9CDkrZl/kxrQJ+YiZFAp/ncnqyPQPyRHPi744c1fyrvUXfiLmTeLk/5iDVJ3NOa8ZL679bu3WkUyzscOU8+mlEryMpyETVZe08zxTAy/jKt+LYM4LH5YWFR45XfS4maPdv/NPc23rgnff2dH9jQNtvnw5OGQniZfk4bU0WtwDpUrAaWMTQnXgGTVLCmpXFrxLVe93aLeWAu+H+CplE/zo/ZL7gQyEU+X83dxAG0SOFnaR3Y=
*/