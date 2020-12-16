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
8APpyAkyG2amdY8hd0+IdreMH5/DdxvRT/fzp8Iwn2TGzFyaDviN+RTP7Kt39ATW+ybVds+iQxIxn2RGzFoW2Pgjd8n4M/vEu89DLSfjcejusHgzzi9kZsz27tyKZ44S9rCrBWrIbPE+03kjUlFfhA2d9mgAarKwxm8NVuH+J/rZ+clRX9RIMitmc3tfeYD5JLNk9uLZSdQJRbJqbNOur0U/vYT9/J6n/HdxyByZHVgzJQPzItrNeHQe7eaT2THLb2nbAHuAsG3PD5/B2iQzYFb27pQ2xk6mYHalvjfOZ0VkJsweTAhsVmlU+NTVLJiFdS98glwi4/N59vobnCf8yFyZdTg8LRV1kMyDWeS6f0yxxsicmS0wLMa6PURmy8wm42tznJeEHTxgrInYknkxc3twazZyfouq/Sj+Mwf9JKvJTG1QhDPqNRl/3yPvM+jnfmGp96Pzsd7J+Jw51Qr7hjiQOfL33R5spfxdiGq7tMRHq5GDZA7M7nUNx5moE5kLszXP/K7grEFmz9uNmW6N9UfmzazBx9taGIN4ZkSVJ5jPUjJ7btEfzZAvW1WeSR2fn4x+kvFnPndfeB39JOPPzL3daTn6KZ45tfuk/egnGZ+zmKuZRZhrYY+mdlyG+rlNdT7vvzLcgrkmq8Gsa0ffHsgXMidmd9r23onvYGR2zPofU66VZDIbZuNidyzB3iHs4fg+F7Gmyaoym29Y5IZ1u53uCMwKb090xdoU1vhreDWc+cg8mXU72ac97u9kJsxuTys/hZwn43M2LC+2CdYmmTGz3g/tHbDHkfHxVWk79RfGsEP1rBEb+vM1vomTWTCbZlnig/GR8bn2fX+kMfYqMt5P01+5t5FnZLz2WK74YoMYkTky+1PLGLmURWbETKtx3geMnYzn7sB7Nv+gLonxedQ8gT1OsVO1L6k2T7AXB5DxuFc7eQp1oj8Zn0/vg0Pq4V5Mxt9nUvp8LdaRsG5ZjsjdQ2SmzNbXi3qHPYfMkFnZkBnXkZ9kPEbj60XVx3cbMgM+hsGFkxH3XapnhtN6DzxQQ8gUzI7PL7+GtUnG43Cp7Mh2nF9Eu0O19Rag9gh78fwg1sNgMrYeqG95GzFnZDY858eMqI05I+PzuTx5zCjUJWE3LteYibpEZsXzekBSd9Sl3arjKzzRdiLmRdjhdYFYRx5kxsz2jVP/iFwS7UYdO4faE0JWnedSt8S9+IZE5sZsYY/xJ7BWyPicReq8t8V6IFMwW3XdNBr3MTI+n2orI0/ijrBH9XymoV+E34u6CPvUIC8ccSfj47Oep9MR35DIzJl9jrSdj7gL6znoOfJsGhmflwVRFgdxPiPj87JhbetZGDsZn5eudcsuI7YpqmeilW9OHECMyHi7PeObxeAcSWbLLHt+u584S5EpmI1bPUh5XyEzZPYfd6N2qOVkPA4J3b52wJ+PJDPla8V/fD/87pOMz9mgsiHI+VLRbkNkZiN8t0lV7WfHejtaIrZkVsxcJnRxRGyFZTX1DsEdT1j+kTbGyF3xPgfTEuwr88n4GIb7LuyBORPPTDWLjMM+TWbBbE6vkXaIu2i35cZ4zHWx6Et2dCzyU3Ovau6Gdvwb32YsyNh8Up7PeIP1TmbCbGtUUTHmTNiSmYGIUSfxTLohGGA9iL6s6NagBPNJZsDMbHXmI9zxyIyZaXxQfrtYRcbnrF+pvwJ3PDKe12N61L+KHCRzYOaa+joL80nmzGzRZLujqJH7VPfi31ruO7HGyCyZdYnZtglnBjJHvv4mZ+zDmYGMx6/ZUe8NWH9kPJe0PNQH49svmT23pHfYU7OE1X0bZo3zkujnDJ+oNOyb+1XnzLGh82OsIzIbZiMz/N8=
*/