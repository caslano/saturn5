//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_APPLY_OPERATION_HPP
#define BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_APPLY_OPERATION_HPP

#include <boost/gil/detail/mp11.hpp>

#include <boost/variant/apply_visitor.hpp>

namespace boost { namespace gil {

/// \ingroup Variant
/// \brief Invokes a generic mutable operation (represented as a unary function object) on a variant
template <typename Types, typename UnaryOp>
BOOST_FORCEINLINE
auto apply_operation(variant<Types>& arg, UnaryOp op)
#if defined(BOOST_NO_CXX14_DECLTYPE_AUTO) || defined(BOOST_NO_CXX11_DECLTYPE_N3276)
    -> typename UnaryOp::result_type
#endif
{
    return apply_visitor(op, arg);
}

/// \ingroup Variant
/// \brief Invokes a generic constant operation (represented as a unary function object) on a variant
template <typename Types, typename UnaryOp>
BOOST_FORCEINLINE
auto apply_operation(variant<Types> const& arg, UnaryOp op)
#if defined(BOOST_NO_CXX14_DECLTYPE_AUTO) || defined(BOOST_NO_CXX11_DECLTYPE_N3276)
    -> typename UnaryOp::result_type
#endif
{
    return apply_visitor(op, arg);
}

/// \ingroup Variant
/// \brief Invokes a generic constant operation (represented as a binary function object) on two variants
template <typename Types1, typename Types2, typename BinaryOp>
BOOST_FORCEINLINE
auto apply_operation(
    variant<Types1> const& arg1,
    variant<Types2> const& arg2,
    BinaryOp op)
#if defined(BOOST_NO_CXX14_DECLTYPE_AUTO) || defined(BOOST_NO_CXX11_DECLTYPE_N3276)
    -> typename BinaryOp::result_type
#endif
{
    return apply_visitor(op, arg1, arg2);
}

}}  // namespace boost::gil

#endif

/* apply_operation.hpp
2rZsEF7dLhvdn07NTSsQW1Y+YHCcWF0TlYHKU2KQyGeXRAfJJUQ3rF5r25TBRIw5LREAklHXePcYN71xav5WsaiQMeH6yliIbFWbDkkaLrOTLyKVsBOWkJHGtjpW02A06m/UzMAS6k8sHZiBpRmQ9LMZM5IQlUpos5kO4n95a+IiJIKGLeEL19CxDYJP83PwzN1OYUaSaXxGsu5JZJQdBVxKjtlIJPhZZyPnOpLqWvHrwP+D
*/