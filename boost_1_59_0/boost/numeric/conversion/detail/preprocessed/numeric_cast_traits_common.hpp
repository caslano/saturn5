//
//! Copyright (c) 2011-2012
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
	
	
	
namespace boost { namespace numeric {
    
    template <>
    struct numeric_cast_traits
        <
            char
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , signed char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<signed char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , unsigned char
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned char> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , unsigned short
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned short> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , unsigned int
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned int> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , unsigned long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , float
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<float> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<double> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , long double
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long double> rounding_policy;
    }; 
}}

/* numeric_cast_traits_common.hpp
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
*/