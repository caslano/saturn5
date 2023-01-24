#ifndef BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_move_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_move_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_move_new_t)
{}

#endif   //BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
LMeVGjmuVsilWpH3Oe2wPM8tLRINkLPrsY/6E/lkFuvXyBjrVxvwoF+S+TQGgGJINQNUnz5EcUT16aUD1qz5C1TkGdH7Il4kbXXD6tTxZBLMV6q27iaCvc28m2jxALeFWw7AEwOmLsyu1HXGlKIUONKGA0JADEgBaGcKFyiNkObL5URupoqmYqXWjEekpGPA0Ph38InYeXiIn1r7m/UVHj/KOw0F+Be2wXQP8bhRxJ6L4CpiuIoARexGeEz/lNwdVVfE7wlqsynvBuyV96fS1d6mNKarG1IQj2c0PK2HIvi7CP5H4XHgU9NG0B5BqM/eO/7ydI2fkBukMjEhRMkdMfRsk/q15qFAwo8CQLPtfq2XPuW02nUB9vwLpB0dRfyOpX777Vfm7SZkYTX738flQp1YKxXJ25VK+TlcLlODADPujtcRN6zpAh/j2wH4yQUSZ6vCvMepjUsE1ic69ZO4giOPSdtwIUWdCe8+O97nIdGSFbRkOF0yc4yjgQv8DPlLAHI+S9/LZdWJUc2Ul+FMSNXiYlwo0bo47qsaMeS+KvZ/+L1Fhf9no1Hr2f9bPuP2RPMA6PzM1CvamdoKrQXfKyyjtknzRQ0z26RRGHna2V6/8zO+Xz8NwJE0DvvqqFCrUBDHBb8YoZe0XzV+x8XPuF74CgATLpq6RqdlcHq/tmZzBb++gE6FcCv/WEIKyjGlWH1Kq1Lb6I2MIRpw
*/