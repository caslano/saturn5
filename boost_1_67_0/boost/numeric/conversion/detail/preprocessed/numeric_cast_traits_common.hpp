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
wtGd5WnEumImnv/ljaNIvX/V11qVFM89sGtstRniH39tFrRsyifPVSPfl3l3xN8DnvOzHzmY2nBGDjQHsI9eXLzjy1O3Eq+tywucxt6W6UbSwTu6/Qy7vM62j0vWjbwtc3I75t7OrKAbWdtwRzJbqnM2n0Czc10MdxUSG21hmqZ51h9++eHHqnyVr8Uc2tNPpn+/YsySFy/+kxJ6b8vSJa6GGygO3ugzTcGq283u/2pQJ+YegzLaVo23pIzJ/rr0Y3m9ZdlsR6PwI+iUB3+kr2X4m9tMfwfz7SXPeVtDextTMTXKNrpCcrNleLG4vwV1nnhP0/A84a6K3nnsdbm0ncjLUkqboZu5msZ+57+667GCLxBz3gJOufBbpEL/D7LQ2zL6uUq7Fd2GoFDQl3xKY4Y3h+jAsJBIS7fqYTm0qKdJiger4T8j5+j3MhPD22XehyZ48szwqS2OEA9WRU+T1f8e/++o+WuhKZIhQpJLPb+DeexXyUQpS504g3pmm90mI2iyTqn4X+7qE7ptU+sooyJlzDTyEcJdRXXxiW3Oq1ksNy7q3/axxYzU/4DJ/pkEVDdXydH4Dx7pIDWhNGHizPAlEsH/bzxHIsj8nQ0SohAP56+z+I8aAi+RBArHW46Fk22nJLvfljlsf1eSsfmxjPfv7r4KbuOgsOBlTP941MoIdof34a5Pn2j05cZX5UDAbQfgf/a8jTrIfjrkkLkXFIl85DkC0FxZENMhU/Gx3eUquUzPGbgdXIdmvte7g5HY3P8MeLw+n6//HwTjf7mZV+HVizey1G8ntZ6N1VQPEYULl4XZ5JsTb7We9S8OBqvFGP0PF+iNFsPVbm2TATIXDJjCNWOGKIvUPrp2baMBKpcfus2DGTdvpAmDF0seuI6vsRmnmvj9EdnPwdjc1/Dc1zsk3t+nzz6pz3+FeP9Dfw7+vxRKfjs/jDUZl//+LYwWKB+yNPK3FfIXQkeHpmodFmhHh6W1sDBcR8dGU8d/h9raja+dyW18atddf7qbtI3slpupj2PvgctuwRlKX98OZ8uVCF88Cbcxyo/qpGucDTXiluXXGAwWvOcv7j1/QRbV5y3aS/SU7kByLjt0lTYoOOwQ5+t+htC94I7aUX23Axoqe3SdNigo7BDX629jWFDXH5rQgA7fVMG+rVx2o9ymYJVvqR1CqjTI148swYeToQD8vtxd2VvSV6RPiO+gP98gvgG8/5UI/a/w/5b8v1iC/4cEfucz+Bh1/T45XAPagr5MmM+o2vK85gngOxAQ+BHYc27s++vjbJQJ88f/3xn4swGFByMdPk4XJ0ZszOXp+enp6WHxjfvWktlNKR73VZT3zMWw/RpXvXzD0UPtnhmeMJ0v7sdvyR0ZKw7DZmewsrKCZzSRWt3YIOQPABFLocKYLxIPnExnLFSp0ihVKkOUSKYIDgCFMuDDg1GusEiLopzVKWfzOIKp5vKOgKBclgMJz5CSzv93rh2+TTQvXpSYJrMgbTQ/4USQqEPSVXlmA3mGMk+5KC9WY+ZFVlqkKl6ToEMcPI4o4x39nlEeuk+bniEQfcbEzdUlHsRPAI2oH/cHOFQInaj/LwJYOJ1YkP8A0f8IA/8j681H+h/hfxWZ5hFgw+3EoMGrAHm4Y4K6kC0omKVzGfTjyVul/I0wlUiouGCc5P8hpdeOBgWXBNuNBgmSYNf3O2XkUPTjI4Gl040G+RfLkGAz6MdBBI6rFpWXxO2f0i6l6YQTKhAtrzwqKVoF05EjK+UDQOorkDULoKFgCsmvqmXIgMdKe0TUyHkF7zNGIEfU0HHry/0JLDDPYsmGSBc1HUXvotCXI8+RWFXqz1fgkqEe4GeXgwgdt5sdZNs6LEJETa4tBREo9vOCgEdNxlZmUBDPR0RtplIKCWaTh4gcv++rq13qVZN7VZj/EyiCztSfhwAWTXd7JISu9F+yNMiflv6/pFkQPyE0ExPzPNJ/GcU1HT7DWT1Mdgsjookowv34KzQvKxNCQuaUPPFEkktXrIEQmIFG8wW780Vyq81WBNUanaGrjZa72z3B1o6Og1/y9f4IiqvbUo3L9xvvJd/sO7KjRtGVxLbMndMYbdsDM1NmizeODorDW7Agt/6CXmr42lb3vGTzGfjlsNn2kX+UKWQuTUr3fLidGiPTaudW0aQcy1Fxa9Xso89Ri4ElncGwkJz1eWE5yx54+GJh+YYrbXCjbOeNOZDVhbZUgro+1XPdi/HG3Aqn7oOfz/LM5e+QZO1GZ7pOpSPNsq323ysgSiq4stKh5wRwNTvZz4WbJKinLZFWGFb0IeEFrtW5pbnk6+W5UtuTvQAzMFbSwIa+qeHdfUCfLb4Wp0CoV+dtvH2OTTqAgXRevNg24DktqRd3VlNgrFhm7pxE058WOS7CHJrnZwj3nV4f6BAaCJhhHya0a1vbRlfAnmloqRUMHWDW2/0ZmMc79x02HxLDGENP92c9xBUVW66TxRxe32kLKG7vgnASjVYLhCiDdbzKLbiy1n88G6TWUVNOvAYvJY3NHoxX+fxdeDCk9oR3N6dIokIcKXrOCVXbAVDgUL2unr6xGd/ufjuiObRCd/a6Ze+cuv8+IuhHwtDpCQiEIwYtV8jkC/5aLJZeuqeu1M0VioJzV/UtL6esNNYZDPX7/nyBc3JyDsbgZK602u8P8m+22iPQ6nD91tzclU4IJBKhAqHwODZ7AyLxBJDfdDhytrs/HIsnEIYskkpHLFMoFjhfLHO3zmKx1iiSTIU9WygRDYHGiKM3FDEaTwpfmVSvN+JfrlSPp9ZkMZrJwWF3OOSbzmKPp1SlOZzOxnK/P9xjNt/udI+n1eVhY2P76/v9SSaXB1BTB4VCEdQfDFUoFk9AptFIFoFCGbI/FFkoFI5Ipl5PVDMkmUoDIyoqmkSuCGY8kRKcmIiUlZ0tX63FnkSri4tCocQ3FIHifqXT5mCsVKYQfP5cXqpShVmuWhODyWyRZzKV0dldo93B8jv3wHbniwKdLo9S3R4eTCYzvxAYrAL5QhGzzVb6GsUMFuuIX+V894djs7kCUI1mq/DfAnfX3uR8sWy28A9mvdk60uVqPd/74/l0Nh+Yw+UyTCabI9/xZNouvySaRrs9z3Kl+nS5CktLW3uuy9P18XQucIWv0WiuwVT28XwJqsvzRSSXx3u2xVb38WIF7uvj5eTCbrfXH53JDB4MDjcKXzBE7xe406WAOBaBUETvcDQendkCWSQWN5recFjvcrUOndUGezgWL/Y3Unr7g+FpTOaIJLI5UeSK//R+F9d5ncHjzWEymdZ3sZXOaGrwG4k0bk+W48n0wDbHE4Nfx6fJOq/8Fupauz0BKo3GP5FotMMJxJK1TmcKVJrN0BOptCO/rq91OJKo1GiCrFCtGc5gtqx1udKo1GyBvVipGfl1l5t3i/kCidV2J4Zms1XfcpVmnfUGi9VONw6ny2XvdDZnneUKzeV2F5bn82Xfdpdnne0Oz3eH224vIDaXG3woLE7/3kCo/eEoAja3B/JIDM7Ab4fxm4gQWVzuCSvxlSQ83u9MvykT2GA6s7/Z5sjm+81Fo9Xq9zvT/fliyVavN4Zqrbb+i6lfT++9P1202h+A2Wx3hmu22NxhPv6evtXzheZ6qyP04+XmoC8QvJPG+/EUAZfXJ4pUNmf3N1/dni8xPJ8Pns5/EfmKEX9TIXilRjdwnNDNze2W43mrw9Xt55u71KP/twu6O1sg9fr+TF9p0e3xGWqx3bn9+nD97YmAeX2/B2t0e155CiEQCITEWhOaoiWVMonm/wqFxd2SDrmvpR6q2UWzlmmED1tWneGdP9/ELz/DWfTSEavo+ubLVHZ/U8UVSo60Op/Pts2AQCniWH0HR+VOr4HOdMYQ7xWitOT42t3s8Kcc29VW9wBnRFrTDi7rliJV1PAyHr2WWox1faMQly+aK4u9YxXL1EpNT7Np4Fu+ee70SCfWIXcTf/N4Yc6ay6HGrX3DHs7yXXrhN34HdPsELPASLeeqM7SEkA+EGeT28iSc0Xawt9tALD642n2YPm/+WAUYejhzhWrq4fyAbr/cxO38YN46TqD9B2eT38oPv+FbYOvb9OnJNCQrYy08NqdzOc6ZZGssWBtK9IP7BCC3J3DHNyAVnG/5Zo05bj8U/+HnyxaVUXNkZ+Tb+tzpzyWX12BLb09gC/PG4OqYtbrXw5cjFk6G2fZrw+7mqe1dB97d1PzrBZ5Y18yToTik10dmKlCiqywU+e2VLQmoznKssGRvas+aZC/e2qHGXwosVpuvt27a6xtVMgYgn+9vyW+e5540/68bGx/0d3Qap4+Dm9cJ/BNaz4OZAMfCnqEbn0FWyYMa379PPG8NRKDdX1OS/itHGEmv9NRRtOD23w7wJ3i9z4PF3ww/rGI/uT0/BT0PNz+9lM+8dT/hXzPrHzs/t/MQEZ9I//0Y19MOeST9RuRjFglQJN4dxN7Uv00BW8ah14/IjibGWss4gXPN+EDiCHZnaUl779VAAW2EhjON4iAg7UAqi6IHYINclyAB2FALlnbtlApagEAACIK7Ek1EwA+XSqx3izfnw/lFSnbG0NVUlZJ/P/v86u34osaz+9tb15fxwdz06QTlh4Ar5x2V62mjVHa0+ePG/pTW08pYVJPFfVMLRP3H/f7zJVbWV/OTBXbZMzv06tP+UddWPSAEGGXY9Xv1A618b6ZRF7txm/d6/eiT3r7/+WW05UOWC57tYwTMf85TMovE7jl2DiTiZ/AIKOa7Lpv3PZe084h3jYXna0dS/kG0cKs55r6GvO6lZfgG6+cFbo8P1J4Q3fEHiPjT+6jl7qUn8+oG7+DaF+LLI2LCcUrtpUart5vnxSIAW24m918nq85X1d0Hyes3lGMep4i/3uTXjVhID9apL+vWi+7w1s9ms1tPTuW2b6zuDyGEU6/qGl4emlKM7s/g8A2I1Q/XuC3c4KavPsPnFt9Px1mz/UsPb+HHS5BVIUwJ/Yus0adMb4rXz9Wwze8EWNeeS26/N6Q9fnI2EzQdJG3GPl4OU/5DflBs9WD1PGRXfVZbmEH73HAZfYyBfldszHQ+G8bhD8ts+VkfXFyqQfFH4Nmu/o01/rmQ5f0yZJGIa6o9vrBU73hFdQvDMQ2tF7ToYGPZECfLTLuyrIk8bJjrfn5fv8hg+F5YWeGpIj9g7FpyMWwgrsOobjnHe/NsGq85Izl3NUA6DRyf0Q9C1nhLj4oTyFQcgw3OV8aQ1HWWmmhrBPkiCn0usQL3jziOkQszQ3Ukc7PMP2WxZy42nrRyxekOcBlloYcvDdMAGKGHwnBqbsdlgrvoW1fFWXCgUQ4dXNsDzX3rmJ0EiZXBP8RjHCT9ZcZ2gmW+aZzuXfN/pAs7Ui0e35RXZ/pPaPlmBk9A+3iFdl4VOkQLM8+qjTG/VNvbUPusu0UULKAmxMmf00GPitQIu7uM+sdrDlo7a1Mm5zdM6w8CpHwmD2evNdn9L7OrJ2ibohWBvgkSXkTK+lVfdpZPDdpjcLiFfEZbuy0kvsuSHFMpnMGcPi0bbYhAj2ancsX54oYwISpFGjNrHTDXx6FGh9faJ6vi+uj3Ms7n4yAqjXjfezzaL1XP0R0h1kkKqG+iEbumunXBrCnFEDIze+Li1FG8UjjnR7eIPSTLrHNhr6DwvWOrmaceETT4JtDMidTk+1Hw2duHX+J6khIUmTVkoP5msks++2vFzRQUBagLPtPaY+C9guQiJeqjLm1ska1OueJBdBpN5vCMHSsxZm+C4VDYrmhKWn0oTVb84f5Xf5OXvBP8AIb9kBHlwkLLwKwrIbP/AHn6gOhNQvmQUfVI64Khm72CuHYtAvjUGy/4AYtdDstnqoWN1h85DxJahRLFGoubSVscENeeaHQzALrjqrc0eZ5u82WdxUlHUI2EHqNNDW0TZyj48to2DJXnWQ6cSRUDTPR8KDkmNS25VIfgXY9sdZ/8Hak9rFqnTrSxVdqWJn6VKbvNS4qTk5vAc+KzuTGn9H6PPTbzl4lYrDT22yuGIhNsjZT3nUb8jXhMz+yTDI1CGoZXA94rBBYCEfGQrayKncNFqMy/0OwFWLhcvsoOJpvECm/2lHFHTfDr7F1+DhPRa5P0Vozx02Jdizx33D3ueSahax6ayzs20V3i5++wjLagl1yf9Y3ph/ngImFnZZnuIEID0zfNsyNSUNcupzB9zxTvVIFs+9oum8OCb4I32y0Jp0z+i/5cclc6d+AsMaR3icAPlIHArSkVdfw9j+ZHuVeIW0XH5C1oT95ui+R9Oh56M6ulwvB05+CITY/iqqVkZDoup9etS6KG0ClI+3zNHE6jXnxfMtMr5VlQcAi0CoQo7yWPdAyWDAFpuVD5qwiwpyolkiV1bLc/BvLwd06OcKpTQ5/94aJXgjcda85c4OtqZq1irelNTr+Q4sJxKvfT/bP2B89X5fksnou171tZ/Zt5rRCm95CwR4Lw+0tNalFDU8ea8L2lzQHNrWGVL7hHz+jKtSaS4TzwSgnDuHH6iJj6LOpaUn39yCqzSvgi1bAhHMa+pKeworcVe9Wyt1TJrqT6o/qrLLN29+iuBOanqfmygOBwZOzZgchtHRkiCx7lP/D9Z/oHKR2vyaTnc8POUDzCWlUYBLzPfWbeYf2at62CuRY3L/c5PH7IF2jeXjVhp0DefTUi4wvewwYq4dmWW2ZpT2IYhCCQVryl164cT4LEfcCw1eJdfi4Zbmg4CcYviHiKVEkE375IgpHhGs1MMxs/Qj+3jiOsTLO/2rwU60IBsXWtuU9UHTZ9qX9TOVXHSxxwi4AbjGhdtjxYIrUrcAkfkr5bbazFtwapD5tN7X0laeif/tBanqPZC7lsrdebLxhSbch5+em2GPhA0a78/8ce/yMO+bka7XOBVuexf2lkRKfhHRPeO9eb1Pd5pjarXxx/eLdf+GThCcG4W9Zx17W78qb6Ax1VPeH6zOq2XemaH/4R40XUkoeAZQ0jpYOI0joeJuxjuuXT6/jdG5/MZeft2GqPVn2z5e+dSnfS5CHXUTdSJ9XAjknP2A1n9H+uHNOX7E28PbhIow6s5L6ce5+7Fl1Rv9u6Fe5VR3XhuMPvU7GUKlBZe39sF7wem4IG0F5pTzeozIkJJpTR4t1lpLlJ40mn74TfGzEV6Nl6jHrnBJH6K7OMquEHGMlq6prlXF4rtfqTzPOjS924E8kx8WEPlhzbWdP6gCOrYt+6iVeKFMnfMwdbWra/XTk/M+lwOy75Y3OyBm9+cz0gQqXWm51phvEFU4rarVDO0LPURQEKVRLKHqjOM7AA+2Tl866hMhj/9rFYApdjKfhKo7lWwYdKMXH3RpE87JACjMnfxDQHFX9QJlxcI1S+Ide7kf++bMF6pH+nl5oiL/OJ+b6fmP71V/5spCoEqFqZXDa2WTLFZ4SMM9EZZtZh1n6mdI4aq0zuV6ae27j8EMnTEKIYFfUgMfkBXuJyjSM22ecMsU9HqcBbnWGkrcw2NihPNb0zJBmhAtGOkV45Sl0f1j/xAOBIovBy3qmcc3aiX9BLFdn5ZuZhvCtbPPWnbaJtCmW684W4ydGb4t2JBH3Jhr4TP85NfDsx+mZP982pmdtyPUgs8U3Zb5B6+4SZ4aY9cv6He8cgDJtwY3rKfszFGDr5Uqz/7Jq5Ztg9A294/qal5fr1KRoypjU2kby2x8V8U6E4hFBWzHChSVXG5CNCeBHBmVDoxHHtnDIV36lpRMIqO/ad4b4uphQ+OZaxtqb0FUVAm5g/d/l3pgA9yypdfyqxMzihnZJA+TQBf8hbZPyhBYlhq5g67yLB4nADt89xvaNFXCZk0uxYfLuFqOkvAfMKMVo4pasezgTZiZSL+dPFzN0MPLOkmGL+gu4WCTt/OspkIlfPSBTum4kUO4clCZ2Az3QKo9PEpLE6GMnZc+Vm9hmmtuzJAE1kPXI1o69KVNdoAjWq0qIVGnkYcUXcFbljMhK1YfGoSeiEcvAYT18GlhlC5XdgY1j9YGr7WvoHIM+EcIhpXV6BiYXB8IjgMjGpRvNQhGwSV2QGP/+lNKgMcTedwqBuI//PP3i7NYHFSdDsUPnrHmmHAAbFeFJ3n1h1sPuptHuw5UuhoCx/6ti9FOrRemip+UIjyElsgOXV7NtM5BcVYswIqmkVubK3hET83IYHohvNBA34+PGwWy8pXxnvMD9yQFHNDPcq+JMfTznyxy6vsYmUmQr3hBY5BVfhon+tPJYyc6f0HLHG20xQvAudCgW0BO5yP2Bs6YRtLaOmA1xH7vNe95FCXzgmX0SeYOlqRtugu2fghrjppLEORw1aOe9J//4T1VB+5UkD2YZ3jNeFJQVvXkFfignG3PbXbqZJH+JnXiK4u7pVR1SVHZp2DNHHj52cEq+WiHtb3bolsVFqjH2kq6uPA/3mIi+Do0S2TTX3ZpnrvpOwehmLZgQGYkGvqKufapgR1e+X8+TW8aO5FIQXh2MlZVdTLORIOUH/6xi1C5Uspun2LpSIIXlDGsNA3339WI00bY5hnB+3eLSnp3g5V8/IhmGtYYgHt7mQHFyoFknLfjpZsmn6xYHUdqcOLVzfya7CK50QWvaJ9ERlw5MT7cIB9uX3yTHZEdif0tvnJp9Vl9fgRE9VnJ0nvYU+Uo6Yr30FXUG21ULUyWB9dFkrDOp1ZU5VQ8jcz2N5qfzngx+r6s+z76uXgAW1L07O41xWz7IO/dQ6x/tb9GemZEHrSYNDhRojWC97kEkkPB4GhkWsUO32YG3E0B7RHVSVXiGrV1ecH5RXNA4KrnWBxZVqaGdvH0xHfyCZVfBuNo9/e9aFViP565A1uGyei+GTxd0eepRmp2sr7eDe8nxin7TZFaIQoVV0MO1hCHZsDIvAysIYHK4Gu5OmZHo6eLiIws0OHWo1OTC2eJ9PL3R5tzrqhsESsqilIYJYTpJf/K0RHP19rj2h5IuXnuJ2IDmzbQ4jBw6f7eMre9p5M4u24NOzGEwWs3JPi3M4Do3/DjyDqBcz1kD90K9hwFFxoTQZpdjS/oLgHRmYgrLNYjQiLR0LcugGkZRScOE18HVy1J3Eh3RVyE030UmvV6ylsQUdkxXQTk9wLA/QCKaBmi1iP/Pj2+V/6fE2TKjbWYE6xqsCnkapGxLwLYWzfwrlmdZFLtnac/SJwqwvR5yhfy4=
*/