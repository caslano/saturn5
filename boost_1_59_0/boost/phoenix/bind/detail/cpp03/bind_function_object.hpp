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
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
*/