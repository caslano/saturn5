/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/phoenix/bind/detail/cpp03/function_ptr.hpp>

namespace boost { namespace phoenix {

    template <
        typename RT
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<0, RT, RT(*)()>
    >::type const
    bind(RT(*f)())
    {
        typedef detail::function_ptr<0, RT, RT(*)()> fp_type;
        return detail::expression::function_eval<fp_type>::make(fp_type(f));
    }

    template <
        typename RT
      , typename T0
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<1, RT, RT(*)(T0)>
      , A0
    >::type const
    bind(RT(*f)(T0), A0 const & a0)
    {
        typedef detail::function_ptr<1, RT, RT(*)(T0)> fp_type;
        return detail::expression::function_eval<fp_type, A0>::make(fp_type(f), a0);
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/bind_function.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/bind_function_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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
    (3, (2, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                            \
            <boost/phoenix/bind/detail/cpp03/bind_function.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}

#else

    template <
        typename RT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        >
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , BOOST_PHOENIX_a
            );
    }

#endif

/* bind_function.hpp
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
*/