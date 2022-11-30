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
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
*/