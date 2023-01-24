/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

template< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename ArgT) >
BOOST_FORCEINLINE format_named_scope_actor<
    fallback_to_none,
    typename boost::log::aux::deduce_char_type<
        typename parameter::binding<
            typename boost::log::aux::make_arg_list< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), ArgT) >::type,
            keywords::tag::format,
            void
        >::type
    >::type
> format_named_scope(attribute_name const& name, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), ArgT, const& arg))
{
    typedef typename boost::log::aux::deduce_char_type<
        typename parameter::binding<
            typename boost::log::aux::make_arg_list< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), ArgT) >::type,
            keywords::tag::format,
            void
        >::type
    >::type char_type;
    return aux::format_named_scope< char_type, phoenix::actor >(name, fallback_to_none(), (BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), arg)));
}

template< typename DescriptorT, template< typename > class ActorT, BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename ArgT) >
BOOST_FORCEINLINE format_named_scope_actor<
    fallback_to_none,
    typename boost::log::aux::deduce_char_type<
        typename parameter::binding<
            typename boost::log::aux::make_arg_list< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), ArgT) >::type,
            keywords::tag::format,
            void
        >::type
    >::type,
    ActorT
>
format_named_scope(attribute_keyword< DescriptorT, ActorT > const& keyword, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), ArgT, const& arg))
{
    BOOST_STATIC_ASSERT_MSG((is_same< typename DescriptorT::value_type, attributes::named_scope::value_type >::value),\
        "Boost.Log: Named scope formatter only accepts attribute values of type attributes::named_scope::value_type.");

    typedef typename boost::log::aux::deduce_char_type<
        typename parameter::binding<
            typename boost::log::aux::make_arg_list< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), ArgT) >::type,
            keywords::tag::format,
            void
        >::type
    >::type char_type;
    return aux::format_named_scope< char_type, ActorT >(keyword.get_name(), fallback_to_none(), (BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), arg)));
}

template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename ArgT) >
BOOST_FORCEINLINE format_named_scope_actor<
    FallbackPolicyT,
    typename boost::log::aux::deduce_char_type<
        typename parameter::binding<
            typename boost::log::aux::make_arg_list< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), ArgT) >::type,
            keywords::tag::format,
            void
        >::type
    >::type,
    ActorT
>
format_named_scope(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& placeholder, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), ArgT, const& arg))
{
    BOOST_STATIC_ASSERT_MSG((is_same< T, attributes::named_scope::value_type >::value),\
        "Boost.Log: Named scope formatter only accepts attribute values of type attributes::named_scope::value_type.");

    typedef typename boost::log::aux::deduce_char_type<
        typename parameter::binding<
            typename boost::log::aux::make_arg_list< BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), ArgT) >::type,
            keywords::tag::format,
            void
        >::type
    >::type char_type;
    return aux::format_named_scope< char_type, ActorT >(placeholder.get_name(), placeholder.get_fallback_policy(), (BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), arg)));
}

/* named_scope_fmt_pp.hpp
4Ef10IXScilcY8W+o8oXgj8OeSh/9X2Kh2bqdVGZDrinFDpkdKskXQi+eD502lsfp/iFLl/QSAh1PjoX+snABw0+rbuaLeQMot0s32fEPSuy7oDHt6ZkhRhFkEnlpZCf217w1PAbquy8QAnZvGKlx7YqYIkIOvvZeLiN7WF3zUdZCj5W3cfvBAWx8O19Wo3+utdH+4Qb1TEd0MJw+4zMJ88POD/Be0spxuLVuQbfIofPwf2MAF6H+pPy0YhX6hatMjmuPRe8deEl7CqQkDc7LwNvkQ51rbcG7loChnuHaZq9KK9yZyH4waQz6ytUJbryMhPDrS2DTvzlApO+fEm91beCZcm3OhleOxrrgD/aga+hNV0hwLeXw//D5EoGN1uXAdYEvpfHrmEwvdNt9fO48YXQ1WdfwOAlNqp7cX8vwFVCb5FXfiTSL3f72EoAuKOzwHc11gBts9vDaM/H2lG/IwBXu/1+dz3LbwvO/eSdsgDOaK/xC7SKSsBX8zcFcBWO2jqhjEfnId2O+8T68BNYjjs1D+Uo/kTEGa0+P+AdM1H2QT+KcFylcbgbfIwWbPHk9zSJONjjA761BO059i8Mzs0heD+UA77iQt5G7Mod6+9yHfizZDeVM6xraPvw+bUccrCj2raKphD4cp0RfLkrldklVNiddH0Axz3cDlsP/6PuBNFfxdp5eHcmiOcvtiLI8WNV1YKeXDgP7x9U
*/