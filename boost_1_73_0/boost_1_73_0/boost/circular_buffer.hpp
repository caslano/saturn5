// Circular buffer library header file.

// Copyright (c) 2003-2008 Jan Gaspar

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See www.boost.org/libs/circular_buffer for documentation.

/*! @file
Includes <boost/circular_buffer/base.hpp>
*/

#if !defined(BOOST_CIRCULAR_BUFFER_HPP)
#define BOOST_CIRCULAR_BUFFER_HPP

#if defined(_MSC_VER)
    #pragma once
#endif

#include <boost/circular_buffer_fwd.hpp>
#include <boost/config/workaround.hpp>
#include <boost/static_assert.hpp>

/*! Debug support control. */
#if !defined(BOOST_CB_ENABLE_DEBUG)
    #define BOOST_CB_ENABLE_DEBUG 0
#endif

/*! INTERNAL ONLY */
#if BOOST_CB_ENABLE_DEBUG
    #include <boost/assert.hpp>
    #define BOOST_CB_ASSERT(Expr) BOOST_ASSERT(Expr)
#else
    #define BOOST_CB_ASSERT(Expr) ((void)0)
#endif

/*! INTERNAL ONLY */
#if BOOST_WORKAROUND(__BORLANDC__, <= 0x0550) || BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
    #define BOOST_CB_IS_CONVERTIBLE(Iterator, Type) ((void)0)
#else
    #include <iterator>
    #include <boost/type_traits/is_convertible.hpp>
    #define BOOST_CB_IS_CONVERTIBLE(Iterator, Type) \
        BOOST_STATIC_ASSERT((is_convertible<typename std::iterator_traits<Iterator>::value_type, Type>::value))
#endif

/*! INTERNAL ONLY */
#if defined(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
    #define BOOST_CB_ASSERT_TEMPLATED_ITERATOR_CONSTRUCTORS BOOST_STATIC_ASSERT(false);
#else
    #define BOOST_CB_ASSERT_TEMPLATED_ITERATOR_CONSTRUCTORS ((void)0);
#endif

#include <boost/circular_buffer/debug.hpp>
#include <boost/circular_buffer/details.hpp>
#include <boost/circular_buffer/base.hpp>
#include <boost/circular_buffer/space_optimized.hpp>

#undef BOOST_CB_ASSERT_TEMPLATED_ITERATOR_CONSTRUCTORS
#undef BOOST_CB_IS_CONVERTIBLE
#undef BOOST_CB_ASSERT

#endif // #if !defined(BOOST_CIRCULAR_BUFFER_HPP)

/* circular_buffer.hpp
46SPtQs+giyzZKigC03eW7CpR+OUBHvDLKuF/nyvKJ8ACWXZiTgt2mguFIF1NEF2XBenSY22ByM2hdWHPAySO+M1E7W19jFkHkctH5vQtWi9I3KdcaQQ/gFQSwMECgAAAAgALWdKUlo6cJ2qAgAApAUAABUACQBjdXJsLW1hc3Rlci8ubGd0bS55bWxVVAUAAbZIJGCtU9tq20AQffdXDPFDk6JLmqfGhFLj0Na0dULsEgwBsdKOrG1Wu2JnZTvgj++sZCcptPgla6y9aM45s2dGw/dvNwZDODqy7p/x4DkAbp39jYX/d3CW7aD/MeiB5yMSKbwgdtkZHEXs4LRDZHuNq7DOsiMyDyGx8EgD8CELSz4ZDBk3sc2TU6vKw+nkDD5cXn6EGC7OL84juBZGoYa5R5OjW0VwJbuTz5XYbhPCTxGgB6GTjmhRKQKypd8Ih8BrrQo0hBIEgUQqnMp5owz4CqFUGmFyc7uczr5GsKlUUTHHk22BKttqCZVYIzgsUK17ikY4D7ZkNHNLRZ75Wq+sSVgawaOriSmCuNBkQayF0iJnGeGh8r6hUZoWrdOceSptQWlxuHpS+Xp/iyVnUIsnsI0Hb6EljCDERVBbqcowsxV82LS5VlRFL6mwkJGpdUCoNVMxTCH1KSPM
*/