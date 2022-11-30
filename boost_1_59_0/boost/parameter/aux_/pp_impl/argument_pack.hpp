// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_ARGUMENT_PACK_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_ARGUMENT_PACK_HPP

#include <boost/parameter/aux_/pack/tag_keyword_arg.hpp>
#include <boost/parameter/aux_/pack/make_arg_list.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/parameter/aux_/pack/make_parameter_spec_items.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Parameters, typename ...Args>
    struct argument_pack
    {
        typedef typename ::boost::parameter::aux::make_arg_list<
            typename ::boost::parameter::aux::make_parameter_spec_items<
                typename Parameters::parameter_spec
              , Args...
            >::type
          , typename Parameters::deduced_list
          , ::boost::parameter::aux::tag_keyword_arg
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
          , ::boost::mp11::mp_false
#else
          , ::boost::mpl::false_
#endif
        >::type result;
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_at_c<result,0>;
#else
        typedef typename ::boost::mpl::first<result>::type type;
#endif
    };
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/make_items.hpp>
#include <boost/parameter/aux_/preprocessor/no_perfect_forwarding_begin.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>

namespace boost { namespace parameter { namespace aux {

    template <
        typename Parameters
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
            BOOST_PARAMETER_MAX_ARITY
          , typename A
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
        )
    >
    struct argument_pack
    {
        typedef typename ::boost::parameter::aux::make_arg_list<
            typename BOOST_PARAMETER_build_arg_list(
                BOOST_PARAMETER_MAX_ARITY
              , ::boost::parameter::aux::make_items
              , typename Parameters::parameter_spec
              , A
            )::type
          , typename Parameters::deduced_list
          , ::boost::parameter::aux::tag_keyword_arg
          , ::boost::mpl::false_
        >::type result;
        typedef typename ::boost::mpl::first<result>::type type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/preprocessor/no_perfect_forwarding_end.hpp>

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* argument_pack.hpp
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
*/