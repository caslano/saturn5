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
KvKYdYdnMeVK8a+C6EEBg7zceGWUlDu1HCUa74V7UjMqfgktAZZ/oVh++P7+KgAm/RMwiKuK2BS2fqsvIasu0CEGWtotC2Hb5AqkkDMKKeT8rugmD8Kpr7NyshSHN2LJU3mlug5Pgt1bxWZyPgK+ebWDiqW0CmFVukfVtjeYZZor9UP+/DxLhqxaW8DRs2BBcWrU3On1tbW1PC90jNKu9OTJtvhhqwRedQMAir/YQ+V0SlbvSATgGmUGNnvJ4THQZDh3zS1+7IYwZ6Mne6ASr1Rl1lkMuZGRqTQ15GJR+WfC6Cp3GWV2FmfdR1nSFXPHLN43RWVy1xFX18gIDoReppCpoCBcPah+ob2zMcYza2PQKrzRdRI4rvKaybw38n6YLMftFtU4B2dVf7NWON54hrNdWNIbotGlFAB67ROKdL+WJXC1D87of47o9gcYPW/Z2r3+ZZAA3vCgHRveadatKAy0WIPOFvbleTBFvjoIx1wPihrTtZ9KgkYLJgjtRNeYrA9EqCBNTNKouoTEljjy3TIoPI6GeNElTYItHf1kn1BrSkDtqK4ues2PhHvai4MJaLAedoMcyp7o+TGfKRhjALYEhMsQjV3wJhjZg+RQBGSqdSFtOuSE5uL++wnMbWJyT7tdEPm9Aj+BLhmT
*/