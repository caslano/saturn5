/*
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::false_type
#include <boost/callable_traits/detail/unguarded/function_ptr_2.hpp>

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::true_type
#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <boost/callable_traits/detail/unguarded/function_ptr_2.hpp>
#endif

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

/* function_ptr.hpp
M3Z9MBVB9y6XBj183T31ThVO0iq1FZK9u0jQkdSHXQnwiDRzBlPX8hC2IvHwPnGMBmZGd0FQmNqAXaU+u1UT3tkUnnxdG9KEMwxzqAo3qRu+6hBJYlLwm2r0fcRpr9v2oHiMN0Jm9aqRP19czcQhxSSDxCLaYt1OMk0n82wJlGs6DRe0jGIjk3rWx5lqS/JJNzF9Y+f3DpZYQqpW+S10FgyqlYY/RM5W1Pc7E6Pq7piFu0BTQwzI+LJeTLA+LAJLTu//8+D7M9y6RvPed4KDGHBORbTWnKKmrBjs1bL1naRYuwx6Ki89DzJ6wKnQX+BEFu+lFhtoiuRDeOTfp73n7AqtzPQ3SrkljWzMJ/R1LgHvmCaMooaz88WQwSifq65RE7WjQHOSGb55Zn1r/IFcNscnOlooTjkzXhw8wbMp/CxxHfhtQpXmDkX0B/d1tUDy+cdH8e7FWaof1TgBVRbSaJXb/dit1/UBenVdlALfzaBNSixF+ag4TSdLQympj3+UtW4JEze2OcSDYay1loX+VCZZ82vW97wv9CkWP6ayqJHq6Rx9riUUc5tlig==
*/