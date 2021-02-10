// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ASSERT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ASSERT_HPP

#include <boost/geometry/core/assert.hpp>

#undef BOOST_GEOMETRY_INDEX_ASSERT

#define BOOST_GEOMETRY_INDEX_ASSERT(CONDITION, TEXT_MSG) \
    BOOST_GEOMETRY_ASSERT_MSG(CONDITION, TEXT_MSG)

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ASSERT_HPP

/* assert.hpp
Ct0t9PvENVPr4Bzzgk1vtOkV+qc5zTrM4EHDMyzI4tgAZWTPgCdeZFuzet73WM55mKCmS1Yh1gwJyk3ZeYAcuQqTtN3DiePOAMYvSjHMcQg2UU5NkBG4vvO7ZuTJo5Y5W094t6plfs7ELRl0RgktNf1SGKUJbIHz1B4kT+ggeGPUVqurC28ZooH0DJcXoKzYndq7ea70oEbn7FDgAQibjNP5hDO/yM7oQ6dBlyCewE+TI5glaPoymzo7pbn6A4eVZdUbzWVq6DVGn4M0vKBbS2s3kMdNvLU9jnJwUUZrBToEiUQJKeCC+PCMn35/IN6fkmg0yOXcd3ZbdcWi7FXW21VTCLZSQmL0bYcshTCPwwYd4ikb7n6k1KUxrVPpSunlU4r1A4wBxssAvCfHPv9GF1I39FRwejPqpNuYuI70ubltrtTbdH6VkIHdSolmEogw1IstTubJ6gtEvPBLgM5jz66lkh+j56bgLnaZLld7s5nwzG5o7HFP7u+B/3vTjZ5veOAVn8pFQJzKgJtqBEQj4oHcBNXr0keYG7hhdon1/5R8yBXawIsZBO0UtyQ+LfHxcxPeiP2+na3ST8eCWpf7+IZ3PVcfHEq5WJSOjmiAuqAgQukJJaISISrnxIy83KBrtN1l3ideI9WRwuwk
*/