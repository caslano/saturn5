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
If0BtWuor7xY5mJaVSogEBIwf7uEDpX0xhUw7Ylo9bZWbZi/BwR3SCkTH0FgFNOqXEZbStrlgZAAaut7+fKrpb+VTTe3evetKuRJ9t75YIssaALV+0p6Q6TIuPrqU/iwfIqpm8Yl+aECUa0Gd9tdJDA+/kgS4eqKDYpipdNr9oqnf4I/GWaKPG+XMwE3BPIh3SIXECkC8iwL3b34xdsQUsJaYzlFXTBYcgIurqzCjPPCDxzp0uX82/3vRuTW9ShC8XVntJ8Mp1+rVicZvUoYhEsEkNf53c0OuCQWvz5SxmAsgI/OOvauj2/g8T/nnHXgB56k9S+0e5IK3eqotWxAucckNjtyhvTsEFfHEZSNm5MexMvYVu6f1DAcSJJ8cSKiGocaBI1+aiZOh9fdTqBOdrcwPJOilNtPrxW+tBrinfZP8+DvAs08wfuZtcKac8HictJZ3fDuMB/Uol9qT828Jm/Q6hR0snj97ZsS78HFon0POGTs3Ce7WaOVuVmkMYFmYhNbX+uScpE8aHuCD8kGRweyfSMp3Ps1UbhziWXr9tJSPKvDEFHvaDkrPw==
*/