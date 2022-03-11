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