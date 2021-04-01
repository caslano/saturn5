
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/core/detail/cpp03/preprocessed/actor_result_of.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/actor_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

        template <typename Expr
            , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_ACTOR_LIMIT)
            , typename Dummy = void>
        struct actor;

        template <typename Expr>
        struct nullary_actor_result
        {
            typedef
                typename boost::phoenix::evaluator::impl<
                    Expr const&
                  , vector2<
                        vector1<const ::boost::phoenix::actor<Expr> *> &
                      , default_actions
                    > const &
                  , proto::empty_env
                >::result_type
                type;
        };

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                          \
    <boost/phoenix/core/detail/cpp03/actor_result_of.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename Expr, BOOST_PHOENIX_typename_A>
        struct actor<Expr, BOOST_PHOENIX_A>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            BOOST_PP_CAT(
                                vector
                              , BOOST_PP_INC(BOOST_PHOENIX_ITERATION)
                            )<const ::boost::phoenix::actor<Expr> *, BOOST_PHOENIX_A> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* actor_result_of.hpp
yjsyLCiDZdnK9izIkdtBNfaAqa2FRVLSIphdMJ2cZVCRFn8Q8oJrlYgz3PmiVz2BePl8xS/HdwtjWxmx4Ncd5Kz0aGWxK4YdFwEwhD8KHVBl2y54qvSXVN7UePylG+bL1nbjx89u9RZ8dHANIrmvN/8J/rdPUwpDAkIC4aI9b6nHNBE8tTecYoiJf9Xb/0iY8sPE9u/7NVH0eBS+bJMhxH8GcjmUxn+fX+wfubOzEKiSq8nFmf6vkXBwzGbe6VBCY3Pp/5XKYMhh9c3kI8naNiNzVLxo5DurAfNhe8iS05z9dnJ6718cNaSq5QmOCKLPB8fOsEXxBZr9iuPk95p5BR06z7Y233xZblpq2Ven+RSi2qr9ZA4N8fuwkd8o/kchQ8vQxOqdtYxrazOPlGd3p+8QBIDN31egU+L3b3cKW3j7SjDF1xQz2gPlrzdVdW10Cy8WZYxD5AKT9qtj7ySsfx72aWWzLLwKpVdWCM6PI587Xl5uMxOOlDNAgkkYoYaBQFrDBI5lQtoiPAsFiyyu4l42VnWRxM8hshs9RrVGdMmkvjBSan07QNtZfg==
*/