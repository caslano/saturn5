/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : struct_is_view<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct is_view_impl<assoc_struct_tag>
      : is_view_impl<struct_tag>
    {};
}}}

#endif

/* is_view_impl.hpp
CoHIbDBMye/wOTR8OKxLEQkM8CzUUTgJLQyI2N2eIr/J3oEHqql93m53Eq/5Jl0YJ0KaCoZT802OT0Na183Wprt1BkNhAasX3hm3z8nfy1j4qzmVTeWq8XqcDmctaf85jMWJaRPf4rL8ENTzMDftu9XdNGb+EGICnw/Yel9NxsKm2PllXIjbCDaNR2C9baVY3Uo1I0vcLgB1fDVa8MJykI1Y4XqmhT0cZ0DQ/v/Ai4NYxE0sK4g4IR1vgtpo4uq1zSc+IH305dndiN6grwzTwef9p8S3YIQnuPe5o9RvDAgf0vJMGTqvEOg1wJwFmX3UGmEH1qpwcyyyAL6C+hwqsIY4L3yOnxyucOr+4X1igeJFc5dCxpz4QZBBJWO+4BrXJSKTogRtDFW0XqkxIkqbmNpubJgyRW1/VHgRyQLIb/6N3+IMYLtOSLdqLyczSUbiwKWwenE9g/EfJ8BI/bUNuSKrBibdBMon3R6jbqT13GiFs0y5danNBJbrFxJ+gPlDKqdFxH/inEGDf2Uk1gWksIaL3iG1vABZBUTYfw2HVymuaxik0cjgPm4rzA==
*/