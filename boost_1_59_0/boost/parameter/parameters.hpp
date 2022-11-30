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
    !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x592))
#include <boost/parameter/aux_/pack/tag_keyword_arg.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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
    !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x592))
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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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
    !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x592))
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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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