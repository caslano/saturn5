
#if !BOOST_PHOENIX_IS_ITERATING

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/operator/detail/cpp03/preprocessed/mem_fun_ptr_eval_result_of.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/mem_fun_ptr_eval_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD(Z, N, D)                 \
            typedef                                                             \
                typename                                                        \
                evaluator::impl<                                                \
                    BOOST_PP_CAT(A, N)                                          \
                  , Context                                                     \
                  , proto::empty_env                                            \
                >::result_type                                                  \
                BOOST_PP_CAT(child, N);                                         \
        /**/

        #define BOOST_PHOENIX_ITERATION_PARAMS                                  \
            (3, (2, BOOST_PHOENIX_LIMIT,                                        \
                 <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval_result_of.hpp>))
        #include BOOST_PHOENIX_ITERATE()

#undef BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else // BOOST_PHOENIX_ITERATE

        template <typename Context, BOOST_PHOENIX_typename_A>
        struct mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>
        {
            BOOST_PP_REPEAT(
                BOOST_PHOENIX_ITERATION
              , BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD
              , _
            )

            typedef
                typename boost::result_of<
                    child1(
                        BOOST_PP_ENUM_SHIFTED_PARAMS(
                            BOOST_PHOENIX_ITERATION
                          , child
                        )
                    )
                >::type
                type;
        };

#endif

/* mem_fun_ptr_eval_result_of.hpp
GwndV9FNBlmN31TnX2UcVvNVf4elvOw9rhWmVn03Hgv9RKYoc6nviv0ien9jDyt5X2ATB1uYOjq+RIphYMPt7UGU8fU34vDpnkBCj9mAMQGNe9r8eLmiulbgpl9RlNUHYsEpy4kYFsJwuSINMGcOecI3xh3PXqlf21Z9+4QEFEZ/4EO6Z2hiRjVUP2W2ImeoLo7EH5GgxZOb3FPjZZr4+ebnXMiYgT9sWtRIZQM5RJKjI3zwDQIcPibhM2kaeYjwT9HEJISVAAu+cqbi2/sr6O6r4rOmMN340dCWQWA71OeND6voNfPN6WgJ7ePibgWwqflTr0+r41gB8Z3jX0b68rS4KWIuZytn7X123Bw+DBcLVzJ+lztpfof1VXb6ehUNUlsG1a6qt24vbmsaJ9L1ULBWpctRzbd+lA8ntQG2+2mGJp0nWn0Unnqymf9TM6JKkq4Gfb8XKGFDt3zqdri9MVnw0vdiLBNpBu1OWpf4+FpZotPnLqfY2vXq2f771TYrtn399KEaw7YjnYjiYs48bkIhIbB00jf3n/oEb3OwexPG6CtWYNDhlRiZPhaZtNidu2jYvH7VNNqriAhpBWmoXUJC9YmFY3urZYS1EPXVzK8tZ+cdqbKwX4LQn/kUNwDzmLBC67xfw/gqgoXs9X+6sRim54yQupyszxPClpjfkzV7ccCWhquz24ANTieJ6KxOJ3r1TaF74Nw9sPGf
*/