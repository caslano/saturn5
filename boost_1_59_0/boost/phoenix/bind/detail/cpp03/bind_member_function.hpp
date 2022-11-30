/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2014      John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/phoenix/bind/detail/cpp03/member_function_ptr.hpp>

namespace boost { namespace phoenix
{

    template <typename RT, typename ClassT, typename ClassA>
    inline
    typename boost::lazy_enable_if<
      boost::is_member_function_pointer<RT (ClassT::*)()>,
    typename detail::expression::function_eval<
            detail::member_function_ptr<0, RT, RT(ClassT::*)()>
          , ClassA >
    >::type const
    bind(RT(ClassT::*f)(), ClassA const& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)()> fp_type;
        return
            detail::expression::function_eval<fp_type, ClassA>::make(
                fp_type(f)
              , obj
            );
    }

    template <typename RT, typename ClassT, typename ClassA>
    inline
    typename boost::lazy_enable_if<
      boost::is_member_function_pointer<RT (ClassT::*)()>,
    typename detail::expression::function_eval<
            detail::member_function_ptr<0, RT, RT(ClassT::*)() const>
          , ClassA >
    >::type const
    bind(RT(ClassT::*f)() const, ClassA const& obj)
    {
        typedef
            detail::member_function_ptr<0, RT, RT(ClassT::*)() const>
            fp_type;
        return
            detail::expression::function_eval<fp_type, ClassA>::make(
                fp_type(f)
              , obj
            );
    }

    template <typename RT, typename ClassT>
    inline
    typename detail::expression::function_eval<
            detail::member_function_ptr<0, RT, RT(ClassT::*)()>
          , ClassT
    >::type const
    bind(RT(ClassT::*f)(), ClassT& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)()> fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
            >::make(
                fp_type(f)
              , obj
            );
    }

    template <typename RT, typename ClassT>
    inline
    typename detail::expression::function_eval<
            detail::member_function_ptr<0, RT, RT(ClassT::*)() const>
          , ClassT
    >::type const
    bind(RT(ClassT::*f)() const, ClassT& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)() const> fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
            >::make(
                fp_type(f)
              , obj
            );
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/bind_member_function.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/bind_member_function_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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
            <boost/phoenix/bind/detail/cpp03/bind_member_function.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}

#else

    template <
        typename RT
      , typename ClassT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , typename ClassA
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        >
      , ClassA
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(ClassT::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
      , ClassA const & obj
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , obj
              , BOOST_PHOENIX_a
            );
    }

    template <
        typename RT
      , typename ClassT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , typename ClassA
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T)) const
        >
      , ClassA
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(ClassT::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T)) const
      , ClassA const & obj
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T)) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , obj
              , BOOST_PHOENIX_a
            );
    }

    template <
        typename RT
      , typename ClassT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        >
      , ClassT
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(ClassT::*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
      , ClassT & obj
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::member_function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , obj
              , BOOST_PHOENIX_a
            );
    }

#endif


/* bind_member_function.hpp
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
*/