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
/HRAx4ksvkv4Fs17/yYf0vGrYfLTVOyHlcr+10gdPyH+ycyuOm4h+iG2m46vEF4UPlZ3+l/F+IrsrmMU879wjoTwZ5h/9XM6nvLB9hHacg6zuD2/j9bxBqnfwp46prL5eS8dlwQ/vX64rbW8vs6O01Ei+iMzXsfhfmsZVuaLW8v6uzhJ2pfMX/nJkl6XdlR4WEkfmabjAM07fi8xXcdEsn+YPkDHtT75dwp/8zRl/B+o40xS
*/