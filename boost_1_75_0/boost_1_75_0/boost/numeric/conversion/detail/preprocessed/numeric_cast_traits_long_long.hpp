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
R/QJGYg+URleLEa43YNuTHRYvL1b92a16yUxs7DWoPneG5iP/awHBGEHGTHIB988lt9feFdH33vbDVG+9yMf0H3vC5n3hboyq7PvfSe/v0gOiDSX/LUbC9PuYTyBvlqYugaF6jJHYKQQaNf83TRrxQ48T5tc2Ye86Hh2ObxywgVH+F9O0cFc7VLuOuNS5hpcpi+J/3fZDosf7HGIk/c6bEcXTvcCbS1wPBqXmt48ptk/3vGoM9VQWT1/rOtRT6rRVbl1fja+Napyj394+rWOJV9fK37Q4BA3xaWW1DTHl3SH6w9qSmq+xsuSYI91yA2E7A5lnGZTF451PJqc+mhNevWYav9les8ou/r6Q39W6CwdutuKr4sfVPMeWMGShtAQbNcH2lnoc+sRU0uG15QE4x2oN9nlMdWYVGyTCG2AJaozetHHzkrhiACi1oOu4OCB1SP+DHxJ5wCVtEixhHBOHCpQ+I/pGE6P+XHkA4FbSacbuDWdePTArVkoeQRuzRECt6Lm9VYJLgrg3zTyLHQkYtZHzMiJMtzWBiTjealI3Htp1pu2gsydVxAJopiCR/XZ81sWMu5GvemSs+S3VMzatI75iICa/GsbMoDFMBeeGgjuvcjupQqYczNQPE2I9i0HgcQBtCrlgS8wW1h3Yq70hAUN6r4P6FyMzkuZpSedBBHIaqO3ZjXRB7Lw1fiwN99z7N1HHRmV1T5TYJgQ
*/