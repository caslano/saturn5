// Copyright David Abrahams 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_TYPE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_TYPE_HPP

namespace boost { namespace parameter { namespace aux {

    // A metafunction that transforms void(*)(T) -> T
    template <typename UnaryFunctionPointer>
    struct unaryfunptr_arg_type;

    template <typename Arg>
    struct unaryfunptr_arg_type<void(*)(Arg)>
    {
        typedef Arg type;
    };

    template <>
    struct unaryfunptr_arg_type<void(*)(void)>
    {
        typedef void type;
    };
}}} // namespace boost::parameter::aux

// A macro that takes a parenthesized C++ type name (T) and transforms it
// into an un-parenthesized type expression equivalent to T.
#define BOOST_PARAMETER_PARENTHESIZED_TYPE(x)                                \
    ::boost::parameter::aux::unaryfunptr_arg_type< void(*)x >::type

#endif  // include guard


/* parenthesized_type.hpp
SDNYxOP2BBmrdOUkvoznVJZBKMpCn2TcIQ5wwETvDs5nrY2AoUFpTt90pPZU9kRSmK4/pzPZ+iBI2fVxMEAys+rPIiyCcRkPruciBBd4EQ1MT8wXidS2JMOUC5Et6ejAJKKQwcjdJrUdjfo+KHn0e+B76TT2TXCP2jKUaVkWYG5k87lMafXBxDRzkxO/d5+m+lzEqe2vkYGvCUVpwuDROk/sZBgp+6s3TSMMOU/S65EvDZSgTIN8vGVs7mpblFXC6yvvWlsuUYbVqFJHNojrspCCxk22dUteCC/eg2yv61DYI23egFosbbnl4ZHqXPiwubILLtmi7cSfqLMDzCWQP8rzAd4g9WPLxYrRRxicq2aIAnXxZc4VizxqjFv4eEvtPxhOh8HHXjCijX0QYXw92tL5jakMI++Q97PThaETAevTKISHRgMLN9hDiuZ7X3aA36CsTfQEtTIWdiUoGZv3w37kJ2GqCi5rzkAE0KeQZbTH12HzAtDkmEGVQsZiskhCVeSbLXb1KZd60GdbLIp9SR6I8uj1bTAymjMHBwMOFgWEx1Z8FRGBfgVfVZYeBpiyICRagboga4JQnEcNRaTHuDIZuXplMGfgT1v6Afdy/QD9jnrSfTDEhyvp1UGHqE9yM/t1nmG0oTgOJj57
*/