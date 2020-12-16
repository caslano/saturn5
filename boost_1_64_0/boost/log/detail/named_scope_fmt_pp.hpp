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
J9YaV9G3LSAFnHuqX5U0GG6PrdrI+Xle/aXk1dsSnj4+v59961t+5uTPp2hb9eKM+NHcNM0kHaOpPYqNs29/W+zNxMexRlLArd7/tJnMDrknjATzQ5PxudZH61prVkOUG4fb9c2zH9f7XeoL1PfLqFeNDOkDpV6VaH+1ATr7yTu5fovaKaXsjaPQNGqCzzi+NlH6Suxp/+ndP0rdSzxH3SNeVap7jn4Rd9SxcnWnzN3P2fXJUWdd/dku3HJwTvlG+iCXENj0z+3+LC9/mfthVNtCrhflec+dWO5NxzP23IK8hcF2d6FcT/SsN7itsLZ3ZTXmiPxhi9ewxTqfRyUM7vZkvC56wXs5mutcwUY7/gtzCguZSqv8edwr/urePOdcQbnnZ9fzWplOZs3QvJmOXIS9HZ9ZYZMw+Z+Y87Kynfki43q7nXlU7I8zBnjPE+BfhfmgLKqyZ95gt5xeT6xqHfMaZ2C/0j0M9eEf5XoX4l2DEXEt2Z8wmTxZgQeryZSo82r6oiOalZ9PkrW4llmJ9HPVLR8ec0wab/d3Du34ufKmSUNDjhaIxbHkTcppd94wKCVvKsw12e1fD7HfyIjxnsdQ/3RN7tnzxrabRBqewvAAjeka0jC6VnhU7agWJGRkpGPNuV0XB4q7uMD65n9ibqvc+mbC506rdYkV93D0wyz5jCutqjc3K27NcunqmS7YLV9mcxZlZXMrzzLr9ruP+E0T7K1XFrvfztyvpqErXd3lUMLs2oPQR+xK2Fz7zyI0oS+yJliRqdgtCaY3/mfMKSrI1TbjHHOgjvTQfSTe88VuuzpfzA6JbsHyvkmuN+d6uEfau92Hhav7VM+0x667n1hL2t9QjfT3aAfsfSEV999IPNz7PyRs7rLeST+o3MNUnSPwfNJ+z0kr7SnlS6wm27vNjsN80KfYZ0Xn5fjtlSf4Z6fToED57+2dJ2rX/awnY29rbFiubbbzaqaEIVLa5mbal7wqfiWZTQjFGq7cjBzmt/0caO2dwX4DzvqJHx1o2306ZvV+lnOETUa/1njtYnFfg3N1w3Urnsfd7hbgTsxPqXn3WDFn0OMeG+ozI/lAkjvmlY9I3GLNOO53EGlGOxqdRFlrEuiLosOXR9eqFdWZhrQ2Xnj2SamYRWF2rKE8s8nz2WZ+t8PBpORAP3UBLIGtIb8rjA+jy5dXxoeHJR3IIP8IUc2eVrPsORieo1xTRjCTMuJ+DtOy4H5ekzz0fDY7HjxfaPl1yvZL8sAec5L+mEn6u+pIbnPtB3QOpSEcRvjST7nqSPYiRx0ZomW8kv4At579gV2ffiDXX2X/p897zKnuHeVDXhg65y1yxc4p42PXfEJWvpRXrR/hMp7pzHmwnBEQ+7nooPixnroT5nwutNpTyQN//51CO7KvWaD/9o+AhkZF+VHbKnM3Yr4OcfTn9nfY75V71CNePtc+Kmfdvk3sJMmeUGe5ZR5PymZGfSHziVJG5dnmnYaB56P+8X6zc39b2v9ck/ZZxTmFIVoWK+n3tCzqvJ6kjbv8HE72Hk9knnGWH1TXB0YUVRpPZFZjPJFZzfFEZjXGE5n/geOJw+cZcvTS95U99X3lAesZSbSA8c7S4z1lImavib2OlEifV9rjT4X3lPazyytyrRvhMr3yArfuMcD65G//veUJncDuoH16G9jFH7EyZ/y1Sz9Ln54r9ncxq9HKMx3wzy5XX8a75nW94o79f65fv7GsYr+eIGYx0q8v5soK5GOvfl3bmPlljn5d+1zv+Snvfn1F2Vn7de+5XUdf3VTcR0hf/VfEaxxwxn5XW3Ec4O/bj55H3ra0+vb55+zbO2AWidma+tq3O+Zal8PWyUL6+HM=
*/