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
8S3K10lepet/MRHjipehZTMwr70Vud02/0jZxgbq5eTU0V7TTpo7Jem943n2aC03lvpiNiHE+nmbq3ZX1fMwTL2BZtgNaVLQ5nvQdZuuAx+99t7NQrP9Vc+p82rRZ2D83r5v9YQ/07iDSt9czRZVxT6wMVv1qQtDwVm3vXqOisn03OcF6gpYleT2FfoqZE44HGHERWgsqrycPkCjWXYjmRizV1+Z3mth9Fmh9Le8zElcC2z74HlX1Q6PumRypu5vt06yqxuge1tIDTdQO/GE5Q/0r4+yf2PH6/GrOF3Vn92dg/SJcLg/YWLnQ6BdD2qDoePdgSgrkl085qDajMCW27rVCOtAf+f6IFiTzn25iYhnJJrqTp9J0+m7x91hc6V6Naq2x/5PcnN5VIpSqk42DCHUjlXzLXo7yBicVHnXhPhHpRyzVSnpTqe3c15JHCvfoNJiBcfBddalNA4P1HJQDzGeKyESccFruSv0deG/8b40Xp20TzcW26xmORqJiFJ35tyDZvK8NrVz7KqV0WB8HyblI5n980p+h8PFYOxRsWh2jt5m0I620/V5MVAJq9G4J5qdUO3t8sdRqUJ/MLZ3yOi4CW559znYE+w8BrKKxYNOLYX9jR03Uswwu7nyvTA6FhkZXT4RWXdMm71/vwIGrbfDlXyyvNmwfjLYgnk5yFKU5or0rsP5fdBlE2HHsbL0DqcL9e4kMyMqGcCx
*/