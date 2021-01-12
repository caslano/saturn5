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
74P496F1qCumpWTsX8dkNJF+QWGUdivKfwTl/gn+9sG8qNcGZ6CoOJCnlvbDvd/D72VwtQtq1SFqHdc6VgIQ5xCYBX4U2OxcaX4MVi0dD6wBNKz3RkZU+TXCzvk/Y5qPrfOAh5ff0aHlXZif0LHxN5b1X7GsewLvg3gDpbHJ0nx2oapv5kDXL1V+j7Py+7uSd4Gx7z/wty3Lf7KyVOn+TdcfCIn49UdxXn9qI849WP51Eb/+
*/