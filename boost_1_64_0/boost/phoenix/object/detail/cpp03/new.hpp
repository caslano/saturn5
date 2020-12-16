
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/new.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/new_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

#define BOOST_PHOENIX_ITERATION_PARAMS                                                \
    (3, (1, BOOST_PHOENIX_COMPOSITE_LIMIT,                                            \
    <boost/phoenix/object/detail/cpp03/new.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

    template <typename T, BOOST_PHOENIX_typename_A>
    inline
    typename expression::new_<detail::target<T>, BOOST_PHOENIX_A>::type const
    new_(BOOST_PHOENIX_A_const_ref_a)
    {
        return
            expression::
                new_<detail::target<T>, BOOST_PHOENIX_A>::
                    make(detail::target<T>(), BOOST_PHOENIX_a);
    }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* new.hpp
vlWTuCy7UdqAl7Ty5TP+91u52Y8smM52IcAVEYPRPlytdwXtQnyU5yXw8aIewQC0t19EQtBwq5OgWmtrhjmFpi33IfM2ufVp8Z0e6kOAyI6m89FZOlbWydrv3igbM+irsxYe7e9/1bYWs/afXqfvk9GDcoRm4jzOBEXw0M7Tlpc+wtNfpVzUWIgMToJEV7TnqryIIA0mubBkGAIEk/73p3H6dJgpPjky3qX7G1oZW9Wcpg+4kwsn8fUtgCLW1ttJDoLkSkXyJGWtmUmuGR7Jk5ILg8MgeQD9k7j8Qb86tQuaOKmAk/UTnwJKnp/OM2ot2IvIqrvEaVOJG+l4m97LJ69WM8zuzNlm0ijHXBMP7ciLZ5tVvs3Esx3K8ZEUK1ZIAtL4G5BpYVkflTIrPwbtWph94pUMl6R5IsrgXGOtOiso6OWmdWfsvZwxlELvrS82km4rqbIeRU2FEiJHOVoXFQwlrEOKmj7pJi5LQQsw+PMtC0exQ8gplyB6S3URq5DFJ/AFMoDupfl0T/MTzNKEbLnVCWbOCkqfBHHWJ6JAz/Y7RCL2XptkYiLCRKA2xSaLKBBf3Lz3YZW3I5y3SUxAsZwC7ZGruHecwm3sv/eSKKqPB6k+xqfknndvntUvv+zwmiu0MndBJXmcZLaxShcPgold9HZAz4o/Kfc2KVc5vHJP/QeM+L3AnygqIOnRMq1MVamVqYrg1rS0kYsqSzOnvoiNh/Ahkqki0sUITWTgzSbU+DP9IjZjBxfls9jFHI/kW5aYJDIwie9yp+14ZIpAoRntbDq8hkPHIYRLeP+hbGDiJZzS6qUozMFytfyvdnqKybNNPJvZ0xNw2ZcezYLDF0g8uzqrj639WSVbIxUhz2KXV3twafCNFi5Jcf4Sp5cEJBEtpnjQoTvLR8n1Gdnt3XGVMjrvyyMusTLgHdmgEPAxr+8aBFtsCD6mEFwHBLyjMuj9igVKYqR3R+xn50yykk0luIIOiIe5ynMGdggO2iJpXgDH0KHzBgulKLSZ0kahVyXbSDCouOf/boq+FFd9LrMdwijzd0TYUzZFNOkpjlg91otAMSKVrVjtVKmwrt+At04IajRFsVWRJwxHRzmzHJ38QeaosnPl6KdoTK3aMvlB/E22YeF0rq+72T1ZcsA3wcCUUhGZ79eal0mnFOXbAZj+YZFBiutWEy+5peozWlX13c4BzSTqiXSBWCkoHALoLuGxAB0lCjhyEEHC9Fp70NkIOoQgVQHsQROB0BoUYXxm5E+GN7fZaptzqdS2qSAq81ag7h40VShu/sXE/7wtfueVEv9XI+HXNyj771AgOwGSmYMKOxjQJwTIxtLrRpoGZDqnRLpAKvP8xYHcxjjSOVhjnK6Snk24UraWnlhQ5IpPyulRWpc40djdSVYQzpw8IAwBWQnuqnks4+c1URga0kYOuveU43SbZITYZnVgMJqmq/6PFayppuS3iJLM61QHWjA0TE7H04SOh6ZzOfx6m+HXzTZ+/fkK4VffCENbDqrW+/m9eEwJepOgCjKcskEsKfZCX8GX32WXypizTGncssPseBhhNTcYA1jRRiNfw0fUeslyXr1XM2xlEW5YuihPJzlWld0kiZ1t25TYcoWacGy6wqbSHGSBMWkkqlOfX8PRZ5tJMSe13ee11BxTF/r+pRYp0net9WaNuUwcWNxy6dPbsXKkOCpXlcitcL3E9Qj2VPrH90j7GgB5hpQUm3i4SpdUtFAX0+LLpZjq6cy+WgsvHZ6mMS+EE1PYpFkst4JX8IKfRyi9HXONc7AR6kfvl+SfKhgESxljyfFOwvvqNvbIAx8bFJeb29dc3kyhTRoFRuvgQU2zDdhQmYLluzQ=
*/