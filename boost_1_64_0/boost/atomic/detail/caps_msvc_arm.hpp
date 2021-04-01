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
vZTpxnAz6IQaNt3GJ/siN6nUUqxZFGIgMSrKmZoxsuDjIMY1dTiUImuQq28wwtGXpx2jrvGFzwud1x21cRiaY/K5+056YAkuFFGyTZZWU/77mG5FWTTO9bS9pC5aPJ7GFQC1H/fETDhvvUn85wZX0RcVikVAKwRN/sjBEbrMQZt25KmfTNHsjXhvT3UVUJS6rfIPaQ2jRiuTkeGTXnbe5HDsLoucIL2TthkYVFp0nUs2iJdHQwhxuL4vO3elnSGkz2gWszed6PklFviqGDlG/fq9qy4FAYwEiFnte4Ty/L8UkEtaHCM13+psLU4maKi8Uis4CPGo81cSus0A5XQL42U5pwtLjYL6nuY6ISfuQBPdT2EHXOURac+9vg/f+4bIftF5c0lXrjno3qttIgXif+UUVN7FOBnokZiSaPf9RGeYoRfReY+v7tD5uSM3W2kgU78e3MMX9HIBEGRimG7jlUsMhtVPvBTZnYQVHCH6Oa9p/0osTohrZ+0bRu8HHp3lYfHfkK9QfFs34ZCnZL9kNVH3/4VXWISr91iZGNL4aRsY6Nk1ckNcXGZh+g==
*/