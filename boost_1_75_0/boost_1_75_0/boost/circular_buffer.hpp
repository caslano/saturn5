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
qk7HQrzl6Bu2aPC7+mpC+XJ1yXNj+8VoF68TEf8OH3Rp6FFwT1IPicef+NAU9hNbj/HmOcptGdf/6Chb04IcPIhZn9wK17C7RJj4wXPW3QRkCG97AiPDgsLuxDzgPMjUGtCQPe0QwUSZpO5NwEAq8N5haJ8eAnDofKDr61nVJlHYBIb+67IfXZvOkzD5xZWSj+Gu3O7Y1jUFVojHyIFDOW0cv0wiuHg0A6wlXpsMtq2KA4MTbmpdCxJqQTtJY/v+YPDAWxK/bxKdbwQ12PlE43XvEGjo21nkG6vzhAkEI3zT1iXvBkacR6kcv22D8YZyjJ8cjVuvcyieLkL13vXuCBDAXohgP7ZIW96Z7L3f/HA6wDHfQl/T3XXh7qg3a9GTSaocGPOn7g2HFSOJ9xOyPVvEbuyX4SWvYLCue5454j2/7PVG4QsmbZJvd381GRj86S8UlWwp9UoK6YOBMv63i4+0//bi44+/jIWdHZ1srYXNjA0tWf/BUL3tMIaTLpqfBdDqGASGNvU96Vchrfga6r+gJU8P+7gbdxlhQX8N+yoZ+P3eQj07S3Rk4CAJyj5To5ezd1RXFKCTNPr2J6u9EQoa9UFJQPzLA+ODuFJpeRs/hnibdFSvhiRFUv8VyHOdt2D6OFBX9RxZHaD3ZuLRpte9+PZ8d7J89hSbU53+Olz+8J6+B8BS6+ObVK1zUMeRuFTpjxPm8c0c2zvd
*/