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