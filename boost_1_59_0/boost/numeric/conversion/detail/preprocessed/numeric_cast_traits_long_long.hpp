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
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            boost::long_long_type
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            boost::long_long_type
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            boost::ulong_long_type
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            boost::ulong_long_type
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
}}

/* numeric_cast_traits_long_long.hpp
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
*/