/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_09172005_1120)
#define FUSION_EQUAL_TO_IMPL_09172005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<cons_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
0TP5N9pSBbQUAWySKWYuEED5vJ+kdBYBLQU600qSR6iRPuC1Wxs49TALcsGOU6hgD5FLkZYndWoC0GhLV0jWgdeeJ9HdqkDbbusPyNGBQ/QjoUnxk01wir68kCgOGnAv1arxgEsYrQy4bLBVPufQcqCviqT8WUo1kIyP5JtCf+1v+f/2TSFvx28KhdAwPAnmCb5mYbhEFtJRzIvyRGO4A2/ffZR+GswX35dvgZ8UJclvKlanMywqRRzQbNLGaTZ5q/URFdl+kqnYMx5J70LewWzfqGK83m8qs6WhZmJR0VxatJdRbgZTOOZ+Z6Sao1Lbg1Kn32BKJBbPiceb9Z562yC6JLYYpkR6jAqLzfYlq43jJTOmwSD/Ztk1CtDA6u1olP3sKtUXwgcnUDwXi6fQnqnyzrNB5E77+EU35dtlscp0kf23yyQQYZcasGAfECSYdibhkBz5LymJvir0MyKRiKm+b4I1+6qlq++YPdrN8ZtgMAc/CHUQG6T+yEGShI+Y3YpsyGe/Zt1Q1/3sF/bc1hnJ/hUBCyiTz8QvGZFJIhbwfBv+Mt0bkSIWYuVbBlhEwXa8uVox6XfaANJ/WIZFg4P/KLykLUWUOcVIM1L0p2ZqFULLXo4WSZBqfydokRS0eHG0fEbRIilVj0dVE9xkYD4iL9+y6Fl3qPESUTOKowZzI6srG8b8mqkpgCTHmTUCoCSQSNU1AqACAqAU
*/