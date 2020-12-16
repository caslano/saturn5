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
+UDG+1l283tf7Edkdswq22z+C/sRWTVma8Natkfsop83X974CnvqMv0ZZdypMoGoCTIHZgMv2aPmfcl4fO03vP4P9hwyXZ1ddCt+jymu6XUkNwJrFpkVs9Tnl94hdrJPmD2f0nsI9luyeswuR1k1Rc0v15/1Y8+vG4X8kdVgdrjw6Ric58l4P0vNTL2IGMjqMrO2cn+EfpLxeXtqZmF/5IiM97P2sAF4VjN8r+/nadvdzbEukfF+1mq5F/XpS8bz4Fk3zRN5IOP9fDBz9r+oMzKe967XNoVh3SUryyw7pC1iTyfjMew4tXE/YojSt4teO6Y+6oyM13yFRWdsUGdkTsyqPy/EecmfjI+Lu1PJTMwj0e5Y22MjUEtkvJ8T3StMwdpKZmTW4UZhO8wVMmce36o7U1FLK/Ttps675oEYyHhffDv61kEMZHz+3Xi9Yx72DjIeX1P7u9bIEZk9s7LjK2NNTiTj873LwXlbEZ/oy620mlgnDCvFWB/yvo46I+P3q5Vz8CbmChmvl43LmhV/d5KsPLPj3+/GeIaQOevWien52APE/WZf+2Mp9gDRbsfA0nmIj6wWswG+vxcgvmh9u1ltTxoRH1k5ZvPmr/DF+ZOsDrNv7ng3RnxkPD6Hay8GIj6ymrwGN5UMR3xkNsyWnIm4hvoU7br1SLDDHCPTvR+8FN0Iax0Zz0ONSVd+xT62Sm/VbcoUInYyPmZlL7r0whoi2u3tPvB3xEfmwiyt682aqE8yHl9imwH3kD8yR14TPzeqjPjIdO8L5jo1wB5OxsdlQaRrQ8S3Wnyf4Unzs9inyery+dDrafEaScbrbPCgPwZjnSerwmxDhRNfY50nq8rsdZs6xesLmW4+dLiKmkgl43Ps4LMq6Eue6Euds+M+R3xr9OZmW7E04iOzY9bq0KXzqF2yaszGhCUewtpDxuOLvzP8K6w9ol3Quj8TULtkvF6ss1JCsT+QVWI2/ccqzzE3yRyYtflxM+ZtgbBaf03EuDis1c/bZ2XssbZ6kfF2xuYOJzA3hQ263qAc9gcyXoMDU9tUQu2S8Tqzj1u0Fvlbqx+zU0eLn0lyyWowexwXgHXXGKOviV4hV1ATHmS8Lyfsn+1EfYp2XVckIEchZDxHLWv/iGe8KDIjsyqzT9dBfZLpPssy/NkW84+Mx1d4MGU56lP0c9bjV1MQ3zr9+6WWI9ti3jqT8Xqx9Xv8Hu8VySowK7d3ySXUJ1ldXvPbY70x/8h4bpNLV+iE+MjqMHu3o9dzxEfGx+xC2dPF+zsZH+t5pbrMQHzr9TU4bc/qaphjZLqz4utHN1CDZGWZvUz8fh7yJ9qFX23dHHOMzInZZ7+3nYw5Jiysz08rUYNkfP7t8rTEPmb4Qb9mZf1pn48ckfF+Tp1VEI76JOPjkpA0B3XmS1aZmfXKR+8QH1lt3s+La20QHxnP34Khc4rPL2T1mM3uUeUl4iPjuW1Vs9Vu5GiDvs4a1x8zCTki4+0ye6ybjhyR8b68dtoYg3WCjM+HdluWvsI6QcbzYOhe6SbWCXHNxiNbFSAGMmdmo4+lFSKGjfoczbhUbRvyQMZjeJa/awvmChmPvcuqe9mIgYzn79WJUn8jBjIe333XO+hnsrhmWMyB/yIG0S6uXCc77FWb9DXxWfeY4u9Dk/GaWNHmwTXUEhm/3/FbXe9hPyLTzU2PFYNRS2SuzBzqH6+DPJDxMbMb2ccd8130xXC+32/Yc37U5/bz/cXvWLzI+DUtozdZ48xApnvfk93HBWsWWSVeg7vWWSIP4n6Hph6xQwxkdjwP89OxLmWT8RhWLrs8EHmI1a+tn2/o8gTxkfF2LfPi5iA+Mt5PV5tdqHl/Mkc=
*/