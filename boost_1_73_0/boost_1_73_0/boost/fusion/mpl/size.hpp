/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_10022005_1617)
#define FUSION_SIZE_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct size_impl;

    template <>
    struct size_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : fusion::result_of::size<Sequence> {};
    };
}}

#endif

/* size.hpp
zwEhSAP0fpbKHKiMOf0ujerDMvjC2OL7Lgk7JKAp/Pj4sQbGeDPrNZtQVu9Oi7IR51hwupXFg6dkHGPJHc8AsqybxtfxvHytozu2uR+X9lQskmLD0YEeTI6iBop7WZbtGJ91og58zABjJESF8MccbS7YU6LZlqCDC9pSotEwwZFwELGEh7Fk9U1xLtwGOTuh+EjyUCyRahdAAuI+AzneEv2by0uvpXLfss20YIzRuEclOC19GGUBmwluFu5ttTfaFJrNrkKQUjnoUYyq4GAYV1lq+SBGo0sYYDOfWwFcI0F5MuTesrhz7ZuL7vv2zeVYWVUwFHfTg7DISleS0aJOFBUcjqlp1ANYPUvD9jtYeWXgqpaekR64D/zomyNPP0uUATxOupYJ0AedB+GZHYcgYbUYZZyHmRZGCjEd0+cQsU/zVTCwi9+BY2w1UTXY3xzzjjf7m3cGRhPtabrK0+mtLFYpoCTNCJTaF0cJcAGZgrgv+AF2YCb1RuFxAR4YEgnT4tUo6zSO5zM12BlvMv4p6MzBMd7MRKd7384MdBKsQVBICBbZOqv8zDc5EKBoJVMyHDYMjHpgo473S0AbaJ4pnrYSdBzryFGbn3mDodZEm4/76JEijitOHqyZxhwBWjvZgLtPa9KwwTDwcALW
*/