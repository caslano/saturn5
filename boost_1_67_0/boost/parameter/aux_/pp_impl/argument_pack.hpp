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