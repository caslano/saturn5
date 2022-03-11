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