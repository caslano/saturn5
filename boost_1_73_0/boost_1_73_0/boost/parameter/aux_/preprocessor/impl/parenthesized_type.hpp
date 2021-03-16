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
tW1epht86vXwHSV7aYDs8gx2LTev6ZV9lpJ9doB8tWA911o1hzJWSxz6HNHRFcqeITpX4Zp3Hr+UvuxfM+9TY+YbMgmf7u837FHikNe0T69ZWckn+U1W/Ol7ef1A2F3nbXqVsVDRezCs8QTbamYXx9jkpbN2PuST7eGwLZf8kzoyZVusaC0J0G09yGfJYFsPoi3H6jgFq8bDXX8Ab3xepug+bujtKtJlVe7GsRVh+88bJwWeoLbgM/JoaZA/0yo=
*/