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
rEnX8hkpSDXbXLVx1QJeSeEcLyrG0ngM+EzLSahGu20bB3VlDAq3/gyPoQT4u0TsDUpjSmQH1KY5FTH8KjCIIxOV/HG57xXnh7fV7m71VMia/RTZ1hLXKJQA0+6lvF+BTDQvWXP4shKEj2V20en7pxSpIEn6HPez3zfw98dms1k+6aOyF59S2sTmPfC1w0nxJKSx7XtFTxSJvJlYUOSrYkqQz/F2QxeMom0xUwKN7GOZxz0kfGQX8RilNWcywk1tKuHtesjoMcHazcxD+QiakqWUM8VkjUdjmXKM85X3r99hnJ4YdMLTO84RD8rBrfuTAujafXE1An+lBKiIT4FBXYkjVWAnTiKyOv7ywJwCUQMmXKo1Wk9+J86023afDfvt3mD7FlUVh6fCoDJ1ygs8cLyM9EToN2F4IOxt9v4GS9/UVTbKANx/FIynYOCGJD1gHA0QSmK0EryLJ2eh2oBiQvDoWJOCRV/qUqN2SLqUgw3dm+T7WrPJvuz8Yn9fNpgoTfnpNrvJBO5sgO58Mfgf1kP/4cuBF6Kfks2UXd7SfgGlMBE/52iri3C7FStxzpPEibwiUnV4+W9BZYGUUuFAPG+YehPPxzVKggrktcJWm1v/UGRq+RSXljlh5gKjwcrRPxYxzrtYzVtYpUEe
*/