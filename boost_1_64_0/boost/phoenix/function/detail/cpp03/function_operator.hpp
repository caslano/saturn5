
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_FUNCTION_DETAIL_FUNCTION_OPERATOR_HPP
#define BOOST_PHOENIX_FUNCTION_DETAIL_FUNCTION_OPERATOR_HPP

#include <boost/phoenix/function/detail/cpp03/preprocessed/function_operator.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_FUNCTION_DETAIL_FUNCTION_OPERATOR_HPP
#define BOOST_PHOENIX_FUNCTION_DETAIL_FUNCTION_OPERATOR_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/function_operator_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                          \
    <boost/phoenix/function/detail/cpp03/function_operator.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
        template <typename This, BOOST_PHOENIX_typename_A>
        struct result<This(BOOST_PHOENIX_A_const_ref)>
            : detail::expression::function_eval<F, BOOST_PHOENIX_A>
        {};

        template <BOOST_PHOENIX_typename_A>
        typename detail::expression::function_eval<F, BOOST_PHOENIX_A>::type const
        operator()(BOOST_PHOENIX_A_const_ref_a) const
        {
            return detail::expression::function_eval<F, BOOST_PHOENIX_A>::make(f, BOOST_PHOENIX_a);
        }

#endif

#endif // PHOENIX_DONT_USE_PREPROCESSED_FILES

/* function_operator.hpp
ndsLn7vUkzrarcNPlP0RR5bMQH+fQ37T0BXmQR2OZVz5nSd5N3jSpSN+zu6uDMHGPvMF+oB+u8wP7sT25E0mDh9/oNNdnnj4Kg79Y+JrzNGYC9V/7Eo/7j00E5/9CnQpD7/B9WQVc4J9aOcb1nlyBuc3+5D8aYellOvQMZ7sscKTOGVo+4ArQ89w5cg5yONabBALtuvzGZu7MY/qjT+Cbu+KLfSm47t09GQxNj63lH7ZlvERv774KNJc48qz+DAnofsb5qNv2MYbx+KTPuHKPm3Ri1MdeQ09fRW8A94D92fRj75BR3pjP5Fv7p6OvDcPHzcNf+1s7KHvO/2Ab83Y/cCZrnxDOw5Hvrcz9rZbne6MEH7Mb0Z3Za7GnKRM/vY3XDb+7/F//NeeCYwT/1sSAZV8b/0OYQ5DBp5a0/a5UwpCro3hXhoUclsY7mvFbWW4a3NCbge4n+EubBNyPQ23zeYhN8BwA1W6gYb7reIGwaEKUuaF3BA4zAfvbYVcmuEGKS4DDjeLMobcKHOPE9Q99jDXdlbpxpp0e6h02YbLUFzMXBtT1xbDvQq3QnE15toH1LVLDfe1E3JnwTGlkePVtRfCjYLbV3EPwy2Ey1Xco6YshYp7xsjvC8W9CIfayXjF/RHuTbipqizr4AYg9xxPyW+7RJnnKy4fzr/2M5Xf3nD1pPlAcWXm2kvUPRYabulmIbcMDtdbuqprT4D7EW4HxT1mrt3HDbmX4OLk9bgq32dwvqyq1bXfw/l1e19d+1dT5kpRet8x0R4TRek9nC+/gYrbFs4vy2zVvh3NtdupdLvD+fr4UIHSP3Ntvqv0D84vcx917QQ4v8x3KW6qSaf7whzDZSiuGm4Zcnle6yTcTXALVXv82tRthEp3Ety7pOuvuAvMPQ5Q3EVwnan/M4q7A24i3C6Ku9dcO11xD8CdTjrdvg8Z+eUr7klTlrGKe87Ib7SS3xq4B638vjH57ae47+DaYZd2VVxmp0R+fZS9Ggbn68ZIlS4LzpfpE9puwPl1K1DcOMPNVdwkuGzyH6q4XDhffr9X3BRz328UN9OUr1jVtxbOr1tfP5165nMq93hfte/t5tq7HSV7ON9e4eaGsod7nWu7q/wegUP2jbinI2SwNqIe75l73KO4n41cdlLchoi6uZ0T3HTFtYGz9bkdHLrWSAad9LXqOZUvl0/9+qp3JnNGJT6wULt4UXll8lsLwaZ65osLg5fUsU3S8OQ59ogazAd9+HzOYBPRbVLIhDBPNuAqMddNj5UUBw/BphTxZ/rQIelpQzKGcSbYyX1SbV09O68Gu6aXV/u7ubfgm65+lHrdouDbMbP/+fUoSX77o6o82Lr9a3OPwbn/xLv0/afmpnZ5s3PV0tvI6ch92nMaPiE/rSheml1QwFa1k2FziqYmtr1NbjirkhZPKoxn5xQpJn9qac4svvGcGyuN509ka1t1riA3xr8SdBGbh40p6U8pdTGT5SRcvd6STQuEE+xtVlJZM7eqprJucHppekn/8PYbvaE0yOKX3JnT/s1mZJr9wPw9zOrSkjt+mR3VlDCKZhUZuUbupQybhwRzcvmzYa/jeGxaYTyQcLyAndfYPo1T0/JzY1Nz4n6i5J9TchJbtu1T1TfYV7OlHTW7OG/KhJivHUlZ+GqyCTmE6tk/NqqErWPn8on0vhP8Dzj13RXx/aphW7++k6vq2ZYuXjxhJhsXlwwdkjUkveHqksUL+rc0h/S05FUUIm1I+rC0rMwhaUGczC/PZGjmSD+TRFtLF1aE/TlI6bb4BKAMzAarsBflHP/h+/wj9TVZHFxVQ4XN9r4p32Hab9uob5LtzlhR6Cvc7GX1hAsm+XT48fk=
*/