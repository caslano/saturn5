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
my7xLjtRvWhDe3qqFTajruPS8ZzZuIIP2Zy+cKmQxemKvgxkaz4Y4Vf/5PXpUb9pTDJ7gBgPc6V4KoruBlF3ZCj/CYirF1+841RGCpmj6VPrKjEBR5gtkMcLx4LGiivGm0XZ2ed4Lmy+PXbYEryHWIFPNRiTJirswWFr6OsLBtWhUviD3RiXh+Me1EdqqH/0cCq/j7nLUEHPuBQpl2DXLFgXO4CmGfhDIOJ4tyM6mGPK/wTulG7EU6s4NKvg2+z0EuibO38+HiKFxAtQVBoOd6lDvIFgg9iPF+rbH+3i7GWQZl3OTXqrpR5ob5vxb+vcac50AqlCe8lXnmEy3SzJbXRF7bP2uzocp4LfnPVAmetdDI4vfMUtk3QTZbvdIbUR/uQS1pHg9VZByflA94qUfBiKTEiuDyVfaRyNmAV5++6SySpeJmZPsMuTqUMRZcOST9vY46jO/aS6lnLeaKpzw1406zwYyYprOnWdpbTFPwuJekEMi0YjeHgcXV05qkbRHR7il32d8GLnprNdjLN2BSry12K8iHRvIpqPBDWNmSYfwHBTbZktOpuj7llcdtJmzq9mBIEZ7jnRc5O0XXlQZ9ayseaWisIY4HHT0mA6UOJ3Xk5+nrmBvZL+/4z+odIu5dWW8i9I51+mLbj0
*/