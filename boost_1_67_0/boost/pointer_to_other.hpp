#ifndef BOOST_POINTER_TO_OTHER_HPP_INCLUDED
#define BOOST_POINTER_TO_OTHER_HPP_INCLUDED

//
//  pointer_to_other.hpp
//
//  (C) Copyright Ion Gaztanaga 2005.
//  Copyright (c) 2005 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

namespace boost
{

// Defines the same pointer type (raw or smart) to another pointee type

template<class T, class U>
struct pointer_to_other;

template<class T, class U, 
         template<class> class Sp>
struct pointer_to_other< Sp<T>, U >
{
   typedef Sp<U> type;
};

template<class T, class T2, class U, 
         template<class, class> class Sp>
struct pointer_to_other< Sp<T, T2>, U >
{
   typedef Sp<U, T2> type;
};

template<class T, class T2, class T3, class U, 
         template<class, class, class> class Sp>
struct pointer_to_other< Sp<T, T2, T3>, U >
{
   typedef Sp<U, T2, T3> type;
};

template<class T, class U>
struct pointer_to_other< T*, U >
{
   typedef U* type;
};

} // namespace boost

#endif // #ifndef BOOST_POINTER_TO_OTHER_HPP_INCLUDED

/* pointer_to_other.hpp
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
*/