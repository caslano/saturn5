/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_27042006_2221)
#define BOOST_FUSION_IS_VIEW_IMPL_27042006_2221

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
wrpTWrTqL56b+xWy7Cv1byheYP0BUxO60fqa7dMPaX2lPaeVDbZe2ucs+wFzF9ZJ+zOxyheZfcROrznoT1WzbcWnytDedJ+Onj9/Rgf0+PDo+ZjeslpwSYnh9Zq3n8b0snA7f1Ts6srX/PWYuCEm/TuAaSU0aVWaS9ZywrMUOa81L4hpKrjOW7HGH1GTqTiVQnKaxotVOP9zTJeVyKsBZ6s60pXqZEEV+8Kp5TkXX3qYhrWGVAkE4BdCG2B2Rqjah3lOhrcbPcBYJ5jUitgXJiRbwxwzVBnT6BeTSd61EpFMCpXrSb5LhV+ZzTdRreDNhm1JNYaMok7zMVn5MW1UIUq7IkXYbLq1FLoa37gFg3UxUS1pLuUAB1XBdR8Cp2TI1thKUgPvhbGLVrW21i4rtbkjiLQOQGXX1jCHtECuUEj8mLq64K2Td4nYWRmy7FL+QMlufC9I1fCKRkFCYTKiNdNCj+lDmJ7G5yl9CJbLYJ6uKD6hYL4a8N6F87fghoDVlvhV03INL1oSm0YKXtwx/lM73fPTU5qeL6N4kWZplBwdZ9NwcTpbJnRMo8dP6AwlBLmfjWgkxdpWn37znx75h9iw/zLO9DbT3Ng64wtKaaAmpzQPzmbe/dAXB6QbnoMFlIsGMSOZnTBcD0yh
*/