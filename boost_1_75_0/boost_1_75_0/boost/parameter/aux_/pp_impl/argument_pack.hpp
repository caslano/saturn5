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
qtbtRyZcvcrtilOm3Khy70r5fiuIBul+Od8JI0GtcNF2k3Kl9yktHQRaP7DCisscFx01sqq0kgmJn8Pi0GmQi90R6tztN5emAFrcehmZ4/f7pCyLO0Q2K+gV10zOW48s8esOWW6dxE5pvYEIy5CoLPQSN502qpLQiWbFE0uslHlYx9s46NIqlTcsM54qETNf3N7Z5izvuehBmHOK7myQC1eQR2TPSVwV2QS6k/NOi8IMHNkvrP6EDJcWrw3Ny5sHKntnjiON7o0cdHVeIR08rRUh87iCn7kRHsUcXbf3Ap06iGxJHIMJ5M7K2V+6eGKRLy6QG+dNImZYTytBeAT3yl77FpWowPEW+z8HMj/dhoA657HnC78XSu/BJOxjKMAuNoDaJjhkF6hGAzxExn8PoLt3P3e/t70/TABiJbG8BHa1/GI831BydWLdBzdeyXnbQebHK3w3g23ukTxJUHRlJPbfsT+b8Piv+f9X6TP+92Hzf2H/vy00w/479v+9WZ6KCvuvHz7FSy6ivg5ek6Q0uUjQ7LisRIlJDM55y8Q2Ldk+bqu1hCn+12wNs+nWG80Bbp8/2C+br0hSVZ/Tqri86LHSqJjV7EKhlCmtR6/6oJC5fLNAF7szBrS01BrxbZKR66pVBI/Cx0FuVuOj/G77o6P8DY9PVmmd9wh6LWAo1nQAU9EC55x6ohbd52F15XyVjVoLzgx7l33IoTQT
*/