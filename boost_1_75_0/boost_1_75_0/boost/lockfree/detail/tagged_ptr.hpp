//  tagged pointer, for aba prevention
//
//  Copyright (C) 2008, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED
#define BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/lockfree/detail/prefix.hpp>

#ifndef BOOST_LOCKFREE_PTR_COMPRESSION
#include <boost/lockfree/detail/tagged_ptr_dcas.hpp>
#else
#include <boost/lockfree/detail/tagged_ptr_ptrcompression.hpp>
#endif

#endif /* BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED */

/* tagged_ptr.hpp
dBN81Vs4PFjQsNm6FFqiwwo0cRzoEMWsa9k5O5GSRzrkmyQHX3nrYgd21jdZ133qx4XryLjDww5Q5WbDpuAnVJCDAxPnsM5vCKmu5IEOSjeTdlQOMn9eCOuMuA1G1bhdqc4FpZCZCCARdqXHKpDSL3ioq20paCKR+8elPmltrlm+x4Yj/vPpoKkHf3FaCl/Dhql1z1nvyallfKkhDXramDHOnPqbViWpjRKabhZ8a1xu4nEF3cq1BphKRDA3QZy/7c50hCgScce7+u1PI1rFUJ7QNitWfHUrBpWp2Ra9JgKWHCU5sAat3Z+0jHFoJ2ljxZCuNmR5JbUxnkvzlwqnVZNnfoOFCBHLEMvelxkP1y4rAl0U3WemyC1htOZVVYftJiyFvzvt3UtI6nTE3Se0AssSfg7DQVos3fxBmpaHALhRxYcGTbYXNagWR3DdnErltNMJn1I1U1tQK8jD1KQGCESTzYnVqGhV2+nmlbveGTGPLNwXHR+ApjgjOaikVUK+7h6TQh0sgJd3DQMfkytMD0iHZq4pSkogOdZjurqs4tlBDAbp0TmS/T4/D/phquGxLX9yQ5vzd33zmOE3HCn7Il6bnBJa9ott9fidLWvOs0jLtOgOaRP/+KDB4vXmyIfIE1Qk0z9cs72mhmiioX04eedDuBGIuVJrJkfYGPsem/WjcXowMvL8tYTlzi9EGweb0FEP/V8/vx8Vqx/S
*/