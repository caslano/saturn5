/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix {
    template <typename F>
    inline
    typename detail::expression::function_eval<F>::type const
    bind(F f)
    {
        return detail::expression::function_eval<F>::make(f);
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/bind_function_object.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/bind_function_object_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                            \
            <boost/phoenix/bind/detail/cpp03/bind_function_object.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}

#else

    template <
        typename F
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        F
      , BOOST_PHOENIX_A
    >::type const
    bind(F f, BOOST_PHOENIX_A_const_ref_a)
    {
        return
            detail::expression::function_eval<F, BOOST_PHOENIX_A>::make(
                f
              , BOOST_PHOENIX_a
            );
    }

#endif

/* bind_function_object.hpp
zZ53l3f3Uu3SP3kIuxP1mBMiq9FKkXeAX/vZiJj2VgdxGNFx71c6OwnrWzTVaQ5mUr3SYyHyL1q1VitiWl5P6St9qrv5HD5Hz6KT4djY3Pwsvy4Wsxu3C9V8nuFL7+yphL3X2NLpUI6XnLGs+CO3P958dSMPFreqS56jyHYW624vJO7S6k45aoQwvvF+w79XX6vt850bdddvnB8Hf3HkHXXBdxxw0LIDpFft5pITeXgq2nrMEHB892kTJfTD8fm0kWfi2YhcuFia3UDV2R505iebRMsxJ+qav//Gt7lHn2iXc7U8KQltROLDu9K/aXJZ5bDMKUImMpEbzR6qPvg9jrbCzed1qC/QduStKYqmR3k0NuorfTLJTgdBfNtPDcAN0B4nnPYdNp5HsfkqO8KtxT159BxnNfkgYk3rx7vn+rEpWdXnK8iylOzuN6TG35+dw069tQNGaWSSUiCEzMf6o1+/dEprdo9mlKw3ytIsu2Ti8p66Dm3Tj2yL1t2UTPnOSckNuoMPHhPnOwgPY0w7zZOo2CthoBmhFbdtObP7+XsWSfajY6F7CqFvnz/N+39C2f/aETt6qHVSpG2tNEN7zHOSci+wMhWYIBzXfZpwwrGSJKwAlAZGkR7draj0hHf/lbO7iKmkSQA4/g0MPsDgDh/u7i6Du7u7uzuDuw/u7jA4PNzdXR7u7vLgre8e9rDJHjpd3Ul36lCXf6qS
*/