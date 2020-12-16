/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_TUPLE_TIE_10032005_0846)
#define FUSION_TUPLE_TIE_10032005_0846

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/fusion/tuple/detail/tuple.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/tuple_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/tuple_tie" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/tuple/detail/tuple_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_REF

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return tuple<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* tuple_tie.hpp
npez6bKRYz9ys0WvLi8bDQZbkCjErU3vggOQ2S/9oRPXh0xSrhzTdnZPF67CPF2nrRsDtWpLN7/mHPPeFhb23WdlfmFeePsIBuc72O920vvyvjK0SexvYcaQD/U4tS83+jEv/tGJbefFu+7ThaOYg/dtY+C2DVJffkIxsr7JBaEZckfL/VoYPc5HzPU2Rp55JeeHvnqghdHdGKb/yP3bGFlpVC4ZuB9041rn0F/1gE4c2o9nCnfDQWaZuA89sBOHZ9HwDMzBThzGOKDeblzr3NrnHtSJ08MgxD31UCcO50RP1+W+C05F9UikeS71wd1YmEwS3MxDOnF60om43+2Cuwh5c/6uZoz4oYfeGw7G5cub8NcmTeXD7g0vLTDuJHt4GwsNF238Ugd93FG/Fg534+z69b1OXLt+rT6iG2fXr8OP7MRh/UK9nbh2/dp+VDeO1i85IO3G2fXrq5247vr1qsd0Y2n9koXXjbPr19c6ce369arHdeF2r19HjnTgaf3Csd1PJJbcGzqSeJxXjB4v6e17Km/K72otBuRVXQ3yXH2CpCk5ctKOc4SZJ5LvrZsNca1e4uQ4GZOQ+Yui8GpHjbjVo9242hzE/WEXXD10R9zoSd04dd+due+4C07PP3DN5bU0BjdJs9RJMu9Ox5HmmvLrsFxxzKAmrE/HuXwXhnThKO9qGzvW8h6LZ4IJppJj3qXVRa9aI2IuTxGMHHfU60KNnu1pgsHmh/3tnk56q91/W+Eg59TorU5Pf1uer1uDJUOso+leiVPfAdCU2desMovDJOWeuOMyM8/BvRbtRvfYrE9MdNGrZOG9w5MmBl0nOQ/YouO6UT3u6cRA9qjRsHHHxrSJQ/eLuj67x6ajvbiOPbeXYKTbQ362r0XDMsRxP8GgO2ziB/Z30K30ivsQjO0qsb286r73gqtkYt24ZNUNL+UiDO94WkjqxlDpfqlSW28ioD5G9MXMz11feO5t3wuuFT7SWBNYVfpOQ7YrbYR2oaLBmSyk4b3XDS0iebLfsjH1hBcF8W2vK3fZeF7pKoDJtsOkUTsuD+l+WMTTJErEbe+H1XbgeaOvmfLckuV+XKQ5d9QBFzgjAxvRm1vw7s262v/i1Vf5l/mdDfn+trohFc+/NPuQvzDlpizxnSwqUo+Vao375HyCkdfNW2M3TJ6M5a5XFFkJPNCGwaeZTCfx3TSqp3RDnntlyEodDT9u73UOmnawNK4GNUgXE4ReBUCuNOV21aIPt8dIW5gkNOj6jbHSlE3rj9BEw69/kuLksNUEoi42TXBk3+HbbVrfPI+9sIfQ5XQO039Pm9b3RJM/h/d20E876LM+1EH3udxFBxl4vreNOWXI2G7T1S4G+k71Tr+NOUbs/GSbTux89H3adNvOL7Ux0k4crz7zvm06nOKoN1tWRpswbCRr7C18v748rw6lsu6GX70fwZM1jJ9QWn0KhFQVlHP2AMGS9ZIfUtpoC2yupIybOnn/LoxslHheH+f2bZxq8E08yAMJZrx0cWAajbiDBylO3m4Cz8KrBmfWg89aOKMeYDwQpdN68MMWvV0PVg9RjF0Pph9s07vrAZ7nb+HrO7/1uOIhnXS1Zoj3+FOM3BtE2uJDCU3yNu8zUNqOvKXlvBlj9DCg47iy2vOEOTG5H/+FD5cYSUfbcL39wGGgyTnDmfmZE31ncfFU5L5k0Te3SHBserfCqn5EHbTCOx2sPi4peRw62W3ftYjzCcPnr2CacSwHm6PGWril0/WSIOLijvclTJ3Ljc6VgaFTnyuY+bI8I1Im/PR8/+IsbGAkXjArpwvDizDkb2y7ukrHY0GZhLHgt79XW9mG8m6uWmex0jhLuZt0x8A=
*/