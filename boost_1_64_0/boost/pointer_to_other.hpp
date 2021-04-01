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
YEnqxKWymuuJML8Ok1P0X1+POW+5NkjhHM0aOcaRya3noV+QlxgjROtb3pnBS11OCtCRM5FRvkDBrcqilGtx+UxArupNM6ksKTEshj8nhP+vNBAPdVasx5Anss0OKNnyyBBAIwEYPD+pmT66shbe6Q+LsBVfQNRghLZ76JA2oloyUJwJt8Q3FZPTqiv8JyXQ/YR+PZvSMuqoh6nJEngxB4KkDlb7Egc3Jn7SRTwTCqyXaX0iwFhKyuqgYzT41p4QNcYERE4xF9eJOOxJlgc6eRrZVNiauCpRTBaAndKhVICrFY5vxVLgs2s2gxciO4yKbRZqf8DH2+1jPymdsMKi6q4sn9vXHHSswu39BWK/ygAQJa7TxaKQSFOpO6Iook/6I9Z6vyd4KNj84uXE8CH48oxMGohg6EhVsWXZo6LyorB0MAJbvDyN5XYUvjP4lil2ErYWZrtLsNCwbPE6bLsLmhMRjqCtWZg6ETVQ4EXmfRXGaQ2Orc+1D28AuLCEvkHbYN5STeJDxA3jYb7vSssqkOP05sY5+E/5gXv6tqly1ChVLp4860W/GiPaSg==
*/