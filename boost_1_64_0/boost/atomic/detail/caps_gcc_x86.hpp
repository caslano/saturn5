/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_x86.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_x86.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(__x86_64__) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B) && (defined(BOOST_HAS_INT128) || !defined(BOOST_NO_ALIGNMENT))
#define BOOST_ATOMIC_INT128_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_

/* caps_gcc_x86.hpp
e1r4Cod/Y/M+rNEfjA72hH+5F/6XNvBNA4NdQVWt6KR/ckT4ee/d0yWDMqwkCFXz9p9I0GoeFaTivnfPG65WYSQKmslPmxPk/TwwiPHEa6ghMWEgvCd77tsFl//8mRmLjRvNetal3lTQAWAALvjK5We9Ied3ix8rYaMvZwdiFwHDCkPjPCy/aXNUeomNIXeaMoIkMhnWPQWan3KKa/3aeEQMt23YhZ5dpQu8K1AgbVuyxgmFLo4F//1OyTxAhHQ2YYMViYfUK83g5HdnDZ+UJdLjlMy4cN1a4lPAGrCzWUulO0fLLCSyaSBeQqQpErvjbYd4tpaG+VI2/qYseZB4UrDQrr9u9E62P4dWPtiCYzjmzICZXTP1bKpmBbvXdT8apkg4wWZAdgyX0yJY+XZsBvY+Va/Zzerz2roLiWDp5Q8CLTvvLqvhrXq58+PM9b3FbYUVu/3Ws9ZBZ6yn74pZJG3p3b54KW5IqGtnVgRAPQIn0vCVZHNv9MK0XZ7TOO4MsBvZh+0Z/gtf3F0tKDVgEHjniPYBgZ5lmWzYoG4O4wOuaSCmlozWaP5gyQ==
*/