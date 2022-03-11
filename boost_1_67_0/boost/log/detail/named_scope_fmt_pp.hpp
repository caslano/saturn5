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
+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
*/