// Copyright David Abrahams, Daniel Wallin 2003.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETERS_031014_HPP
#define BOOST_PARAMETERS_031014_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    // The make_arg_list<> metafunction produces a reversed arg_list,
    // so pass the arguments to the arg_list constructor reversed in turn.
    template <typename ArgList, typename ...Args>
    struct arg_list_factory;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/arg_list.hpp>
#include <utility>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // TODO: Reduce template code bloat. -- Cromwell D. Enage
    template <typename ArgList>
    struct arg_list_factory<ArgList>
    {
        template <typename ...ReversedArgs>
        static inline BOOST_CONSTEXPR ArgList
            reverse(ReversedArgs&&... reversed_args)
        {
            return ArgList(
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_if<
                    ::std::is_same<
#else
                typename ::boost::mpl::if_<
                    ::boost::is_same<
#endif
                        typename ArgList::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >()
#else
                >::type()
#endif
              , ::std::forward<ReversedArgs>(reversed_args)...
            );
        }
    };

    template <typename ArgList, typename A0, typename ...Args>
    struct arg_list_factory<ArgList,A0,Args...>
    {
        template <typename ...ReversedArgs>
        static inline BOOST_CONSTEXPR ArgList
            reverse(A0&& a0, Args&&... args, ReversedArgs&&... reversed_args)
        {
            return ::boost::parameter::aux
            ::arg_list_factory<ArgList,Args...>::reverse(
                ::std::forward<Args>(args)...
              , ::std::forward<A0>(a0)
              , ::std::forward<ReversedArgs>(reversed_args)...
            );
        }
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/make_arg_list.hpp>
#include <boost/parameter/aux_/pack/make_parameter_spec_items.hpp>
#include <boost/parameter/aux_/pack/tag_keyword_arg.hpp>
#include <boost/parameter/aux_/pack/tag_template_keyword_arg.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/identity.hpp>
#endif

#if !defined(BOOST_PARAMETER_VARIADIC_MPL_SEQUENCE)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
//#include <boost/mp11/mpl.hpp>
#define BOOST_PARAMETER_VARIADIC_MPL_SEQUENCE ::boost::mp11::mp_list
#else
#include <boost/fusion/container/list/list_fwd.hpp>

// Newer versions of MSVC fail on the evaluate_category and
// preprocessor_eval_category test programs when parameters uses
// boost::fusion::list.
// -- Cromwell D. Enage
#if defined(BOOST_FUSION_HAS_VARIADIC_LIST) && ( \
        !defined(BOOST_MSVC) || (BOOST_MSVC < 1800) \
    )
#include <boost/fusion/container/list.hpp>
#include <boost/fusion/mpl.hpp>
#define BOOST_PARAMETER_VARIADIC_MPL_SEQUENCE ::boost::fusion::list
#else
#include <boost/fusion/container/deque/deque_fwd.hpp>

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#include <boost/fusion/container/deque.hpp>
#include <boost/fusion/mpl.hpp>
#define BOOST_PARAMETER_VARIADIC_MPL_SEQUENCE ::boost::fusion::deque
#else
#include <boost/mpl/vector.hpp>
#define BOOST_PARAMETER_VARIADIC_MPL_SEQUENCE ::boost::mpl::vector
#endif  // BOOST_FUSION_HAS_VARIADIC_DEQUE
#endif  // BOOST_FUSION_HAS_VARIADIC_LIST
#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // BOOST_PARAMETER_VARIADIC_MPL_SEQUENCE

namespace boost { namespace parameter {

    template <typename ...Spec>
    struct parameters
    {
        typedef BOOST_PARAMETER_VARIADIC_MPL_SEQUENCE<Spec...> parameter_spec;

        typedef typename ::boost::parameter::aux
        ::make_deduced_list<parameter_spec>::type deduced_list;

        // If the elements of NamedList match the criteria of overload
        // resolution, returns a type which can be constructed from
        // parameters.  Otherwise, this is not a valid metafunction
        // (no nested ::type).
        template <typename ArgumentPackAndError>
        struct match_base
#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
          : ::boost::mpl::if_<
                typename ::boost::parameter::aux::match_parameters_base_cond<
                    ArgumentPackAndError
                  , parameter_spec
                >::type
              , ::boost::mpl::identity<
                    ::boost::parameter::parameters<Spec...>
                >
              , ::boost::parameter::void_
            >
#endif
        {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            using type = ::boost::mp11::mp_if<
                typename ::boost::parameter::aux::match_parameters_base_cond<
                    ArgumentPackAndError
                  , parameter_spec
                >::type
              , ::boost::mp11::mp_identity<
                    ::boost::parameter::parameters<Spec...>
                >
              , ::boost::parameter::void_
            >;
#endif
        };

        // Specializations are to be used as an optional argument
        // to eliminate overloads via SFINAE.
        template <typename ...Args>
        struct match
          : ::boost::parameter::parameters<Spec...>
            ::BOOST_NESTED_TEMPLATE match_base<
                typename ::boost::parameter::aux::make_arg_list<
                    typename ::boost::parameter::aux
                    ::make_parameter_spec_items<parameter_spec,Args...>::type
                  , deduced_list
                  , ::boost::parameter::aux::tag_keyword_arg
                    // Don't emit errors when doing SFINAE.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                  , ::boost::mp11::mp_false
#else
                  , ::boost::mpl::false_
#endif
                >::type
            >::type
        {
        };

        // Metafunction that returns an ArgumentPack.
        template <typename ...Args>
        struct bind
#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
          : ::boost::mpl::first<
                typename ::boost::parameter::aux::make_arg_list<
                    typename ::boost::parameter::aux
                    ::make_parameter_spec_items<parameter_spec,Args...>::type
                  , deduced_list
                  , ::boost::parameter::aux::tag_template_keyword_arg
                >::type
            >
#endif
        {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            using type = ::boost::mp11::mp_at_c<
                typename ::boost::parameter::aux::make_arg_list<
                    typename ::boost::parameter::aux
                    ::make_parameter_spec_items<parameter_spec,Args...>::type
                  , deduced_list
                  , ::boost::parameter::aux::tag_template_keyword_arg
                >::type
              , 0
            >;
#endif
        };

        // The function call operator is used to build an arg_list that
        // labels the positional parameters and maintains whatever other
        // tags may have been specified by the caller.
        inline ::boost::parameter::aux::empty_arg_list operator()() const
        {
            return ::boost::parameter::aux::empty_arg_list();
        }

        template <typename A0, typename ...Args>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        inline ::boost::mp11::mp_at_c<
#else
        inline typename ::boost::mpl::first<
#endif
            typename ::boost::parameter::aux::make_arg_list<
                typename ::boost::parameter::aux
                ::make_parameter_spec_items<parameter_spec,A0,Args...>::type
              , deduced_list
              , ::boost::parameter::aux::tag_keyword_arg
            >::type
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
          , 0
        >
#else
        >::type
#endif
            operator()(A0&& a0, Args&& ...args) const
        {
            typedef typename ::boost::parameter::aux::make_arg_list<
                typename ::boost::parameter::aux
                ::make_parameter_spec_items<parameter_spec,A0,Args...>::type
              , deduced_list
              , ::boost::parameter::aux::tag_keyword_arg
            >::type list_error_pair;

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            using result_type = ::boost::mp11::mp_at_c<list_error_pair,0>;

            using error = ::boost::mp11::mp_at_c<list_error_pair,1>;
#else
            typedef typename ::boost::mpl
            ::first<list_error_pair>::type result_type;

            typedef typename ::boost::mpl
            ::second<list_error_pair>::type error;
#endif

            error();

            return ::boost::parameter::aux
            ::arg_list_factory<result_type,A0,Args...>::reverse(
                ::std::forward<A0>(a0)
              , ::std::forward<Args>(args)...
            );
        }
    };
}} // namespace boost::parameter

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/parameter/aux_/pack/make_arg_list.hpp>
#include <boost/parameter/aux_/pack/make_items.hpp>
#include <boost/parameter/aux_/pack/make_deduced_items.hpp>
#include <boost/parameter/aux_/pack/tag_template_keyword_arg.hpp>
#include <boost/parameter/aux_/preprocessor/binary_seq_for_each.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/selection/min.hpp>

#if ( \
        BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY < \
        BOOST_PARAMETER_MAX_ARITY \
    )
#include <boost/parameter/aux_/pack/tag_keyword_arg_ref.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#endif

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
#include <boost/parameter/aux_/pack/tag_keyword_arg.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/preprocessor/repetition/enum_params.hpp>
#else
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

#include <boost/parameter/aux_/preprocessor/no_perfect_forwarding_begin.hpp>

namespace boost { namespace parameter {

    template <
        typename PS0
      , BOOST_PP_ENUM_SHIFTED(
            BOOST_PARAMETER_MAX_ARITY
          , BOOST_PARAMETER_template_args
          , PS
        )
    >
    struct parameters
    {
        typedef typename BOOST_PARAMETER_build_deduced_list(
            BOOST_PARAMETER_MAX_ARITY
          , ::boost::parameter::aux::make_deduced_items
          , PS
        )::type deduced_list;

        // If the elements of NamedList match the criteria of overload
        // resolution, returns a type which can be constructed from
        // parameters.  Otherwise, this is not a valid metafunction
        // (no nested ::type).
#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
        // If NamedList satisfies the PS0, PS1, ..., this is a metafunction
        // returning parameters.  Otherwise it has no nested ::type.
        template <typename ArgumentPackAndError>
        struct match_base
          : ::boost::mpl::if_<
                // ::boost::mpl::and_<
                //    aux::satisfies_requirements_of<NamedList,PS0>
                //  , ::boost::mpl::and_<
                //       aux::satisfies_requirements_of<NamedList,PS1>...
                //           ..., ::boost::mpl::true_
                // ...> >
                typename BOOST_PP_REPEAT(
                    BOOST_PARAMETER_MAX_ARITY
                  , BOOST_PARAMETER_satisfies_begin
                  , PS
                )
                ::boost::is_same<
                    typename ::boost::mpl
                    ::second<ArgumentPackAndError>::type
                  , ::boost::parameter::void_
                >
                BOOST_PP_REPEAT(
                    BOOST_PARAMETER_MAX_ARITY
                  , BOOST_PARAMETER_satisfies_end
                  , ::boost::mpl::false_
                )::type
              , ::boost::mpl::identity<
                    ::boost::parameter::parameters<
                        BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, PS)
                    >
                >
              , ::boost::parameter::void_
            >
        {
        };
#endif  // SFINAE enabled, not Borland

        // Specializations are to be used as an optional argument
        // to eliminate overloads via SFINAE.
        template <
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
            // Borland simply can't handle default arguments in member
            // class templates.  People wishing to write portable code can
            // explicitly specify BOOST_PARAMETER_MAX_ARITY arguments.
            BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, typename A)
#else
            BOOST_PP_ENUM_BINARY_PARAMS(
                BOOST_PARAMETER_MAX_ARITY
              , typename A
              , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
            )
#endif
        >
        struct match
#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
          : ::boost::parameter::parameters<
                BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, PS)
            >::BOOST_NESTED_TEMPLATE match_base<
                typename ::boost::parameter::aux::make_arg_list<
                    typename BOOST_PARAMETER_build_arg_list(
                        BOOST_PARAMETER_MAX_ARITY
                      , ::boost::parameter::aux::make_items
                      , PS
                      , A
                    )::type
                  , deduced_list
                  , ::boost::parameter::aux::tag_keyword_arg
                    // Don't emit errors when doing SFINAE.
                  , ::boost::mpl::false_
                >::type
            >::type
        {
        };
#else
        {
            typedef ::boost::parameter::parameters<
                BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, PS)
            > type;
        };
#endif  // SFINAE enabled, not Borland

        // Metafunction that returns an ArgumentPack.

        // TODO, bind has to instantiate the error type in the result
        // of make_arg_list.

        template <
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
            // Borland simply can't handle default arguments in member
            // class templates.  People wishing to write portable code can
            // explicitly specify BOOST_PARAMETER_MAX_ARITY arguments.
            BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, typename A)
#else
            BOOST_PP_ENUM_BINARY_PARAMS(
                BOOST_PARAMETER_MAX_ARITY
              , typename A
              , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
            )
#endif
        >
        struct bind
        {
            typedef typename ::boost::parameter::aux::make_arg_list<
                typename BOOST_PARAMETER_build_arg_list(
                    BOOST_PARAMETER_MAX_ARITY
                  , ::boost::parameter::aux::make_items
                  , PS
                  , A
                )::type
              , deduced_list
              , ::boost::parameter::aux::tag_template_keyword_arg
            >::type result;

            typedef typename ::boost::mpl::first<result>::type type;
        };

        BOOST_PP_REPEAT(
            BOOST_PARAMETER_MAX_ARITY
          , BOOST_PARAMETER_forward_typedef
          , (PS)(parameter_spec)
        )

        // The function call operator is used to build an arg_list that
        // labels the positional parameters and maintains whatever other
        // tags may have been specified by the caller.
        //
        // !!!NOTE!!!
        //
        // The make_arg_list<> metafunction produces a reversed arg_list,
        // so pass the arguments to the arg_list constructor reversed in turn.
        inline ::boost::parameter::aux::empty_arg_list operator()() const
        {
            return ::boost::parameter::aux::empty_arg_list();
        }

#if (0 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY)
        BOOST_PP_REPEAT(
            BOOST_PP_MIN(
                BOOST_PP_INC(BOOST_PARAMETER_MAX_ARITY)
              , BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY
            )
          , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_Z
          , (BOOST_PARAMETER_function_call_op_overload_R)(_)
        )
#if ( \
        BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY < \
        BOOST_PARAMETER_MAX_ARITY \
    )
#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,( \
        BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY \
      , BOOST_PARAMETER_MAX_ARITY \
      , <boost/parameter/aux_/preprocessor/overloads.hpp> \
    ))
#include BOOST_PP_ITERATE()
#endif
#else   // (0 == BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY)
        template <typename A0>
        inline typename ::boost::mpl::first<
            typename ::boost::parameter::aux::make_arg_list<
                ::boost::parameter::aux::item<
                    PS0,A0
                >
              , deduced_list
              , ::boost::parameter::aux::tag_keyword_arg_ref
            >::type
        >::type
            operator()(A0& a0) const
        {
            typedef typename ::boost::parameter::aux::make_arg_list<
                ::boost::parameter::aux::item<
                    PS0,A0
                >
              , deduced_list
              , ::boost::parameter::aux::tag_keyword_arg_ref
            >::type result;

            typedef typename ::boost::mpl::first<result>::type result_type;
            typedef typename ::boost::mpl::second<result>::type error;
            error();

            return result_type(
                a0
                // , void_(), void_(), void_() ...
                BOOST_PP_ENUM_TRAILING_PARAMS(
                    BOOST_PP_SUB(BOOST_PARAMETER_COMPOSE_MAX_ARITY, 1)
                  , ::boost::parameter::aux::void_reference() BOOST_PP_INTERCEPT
                )
            );
        }

        template <typename A0, typename A1>
        inline typename ::boost::mpl::first<
            typename ::boost::parameter::aux::make_arg_list<
                ::boost::parameter::aux::item<
                    PS0,A0
                  , ::boost::parameter::aux::item<
                        PS1,A1
                    >
                >
              , deduced_list
              , ::boost::parameter::aux::tag_keyword_arg_ref
            >::type
        >::type
            operator()(A0& a0, A1& a1) const
        {
            typedef typename ::boost::parameter::aux::make_arg_list<
                ::boost::parameter::aux::item<
                    PS0,A0
                  , ::boost::parameter::aux::item<
                        PS1,A1
                    >
                >
              , deduced_list
              , ::boost::parameter::aux::tag_keyword_arg
            >::type result;

            typedef typename ::boost::mpl::first<result>::type result_type;
            typedef typename ::boost::mpl::second<result>::type error;
            error();

            return result_type(
                a1
              , a0
                // , void_(), void_() ...
                BOOST_PP_ENUM_TRAILING_PARAMS(
                    BOOST_PP_SUB(BOOST_PARAMETER_COMPOSE_MAX_ARITY, 2)
                  , ::boost::parameter::aux::void_reference() BOOST_PP_INTERCEPT
                )
            );
        }

#if (2 < BOOST_PARAMETER_MAX_ARITY)
        // Higher arities are handled by the preprocessor
#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,( \
        3 \
      , BOOST_PARAMETER_MAX_ARITY \
      , <boost/parameter/aux_/preprocessor/overloads.hpp> \
    ))
#include BOOST_PP_ITERATE()
#endif
#endif  // exponential overloads
    };
}} // namespace boost::parameter

#include <boost/parameter/aux_/preprocessor/no_perfect_forwarding_end.hpp>

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* parameters.hpp
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
*/