/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2012 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_msvc_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_

/* caps_msvc_arm.hpp
X1yFw14PuoNwhC8nb6/cwfU59u8/UEsDBAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAaAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9VVAUAAbZIJGBQSwMECgAAAAgALWdKUtwiP+QvAAAAOgAAACMACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzLy5jaGVja3NyY1VUBQABtkgkYEvJLE5MyklVCIkMcHVxdQsOCQp1DuFKgYoG+wUEefqFuMEFnBz9/Fxd3EL9nLkAUEsDBAoAAAAIAC1nSlKeLDt+2QEAACwEAAAkAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy8uZ2l0aWdub3JlVVQFAAG2SCRgXZPRruQgCIbvfZcmu7MPtGGUTs2oGME5M/v0B8X2JHtTP6gg4O/vXxvIBpvEjA6S8Ms7KB/octQuzmOTWHZy/nhyRQzOEz0j/o1FsO3g0QW894fDt9oFEpN/org9Juw1EQS3U8XidqnbV0zBQwvDeIxNc5npDRtyHcjr75nhpL1Rzph/HBrQte4zy1x1A7WPm+lCbOjFHaKnV2Kj2xboq8zMZtbOxxVnLsb2wjZ+LMcqZRh/7LtVPR2L5fSdhfKBELBNxxjeWufJe8QUeLrYxQx1
*/