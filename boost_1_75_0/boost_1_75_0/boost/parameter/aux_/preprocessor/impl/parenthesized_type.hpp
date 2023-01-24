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
gNdcnIPXduFpYjEprgR31YffjQ+WNQ2W0cROUB67DzyRczITHdUwx258mpHafdaHahmUFay15nR77PRpm9B4f4mXlwdb6+vPJb715GzRzGWy9LsYflRMHjIQ3n7AyeK4ff4E+yovdwSR6CLQ4nBBZiF2OPrAv0FyrxJ639Ze2a6KxSVdxRXxXHqvQVajCzxZAgIgl54xuSey3LmiyrNKb1UCb+TaxaLbS5Q0ULFl4rJqdYRnKAF0gXYR/DMw/R9t5GeXIKIxxYlZ+JgT6Is+epM8dirhfOvZnNUty119FKI+p7QFW6E5R7u1HFY1g7uo7B1GGbZnsn4qflJUgi+0NeK33QZXcROJt/vByu43G9rgPHA6q77eZnVsxVIvXmmoVFXo8GWjHRcgE/2AmSmThPuO6TsPQK9+SY1OpGUfm+LiQgRoMjq491y5sqb5RWRhM4aU83x3FtOgZpH40pSfOoc7htcJY3FOKiZa8Y/Sx2AR96Ly+1yWihP10wqNKo7dpjV3ZTBJ8wSAtQnzfKw+lN7d723kGyce00qvhZ7D1459E+bF5orlXXCvVG6nWJzD2M5ANE8m7mSphqSQttVh3c++7G9i9DqT1hEotAz6feVUWk3s3VLce4IaeN2e3tddFUiXQWDCf1SSp8DH+db9nBNJ7wbJX9pTTDwY5xDtKbx2VRfdFHkMznwa13vUA6Da67eUWHSdzIyBkJng
*/