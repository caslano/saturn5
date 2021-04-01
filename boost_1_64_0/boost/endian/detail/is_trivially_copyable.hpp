#ifndef BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
# include <type_traits>
#endif

namespace boost
{
namespace endian
{
namespace detail
{

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)

using std::is_trivially_copyable;

#else

template<class T> struct is_trivially_copyable: boost::integral_constant<bool,
    boost::has_trivial_copy<T>::value && boost::has_trivial_assign<T>::value> {};

#endif

} // namespace detail
} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED

/* is_trivially_copyable.hpp
35n04ZGxu/AYBQYsYYLecT22JhUp4ZzW919XyPqoAVtWF9OdE+Z66fYM5E20j8SaU4gv0G3TMs5UNy53XPW2mHMTIsAy4JOHFV+E6VV8kqRzlgNAOHUUYt7pAdy71tqidMEET+NcU6faeRlHDVz+jxh5MHc4OMy6n1AWm/HHJQ5IO0Vfw6H6adxPecFTPFOi6+2QLQAx7MAkge+NFp2FmREWzqETgKz0lxa5pibt4YeWiEKva9I/mu0apkT3D59yWEKryE0k/4ezW9kein00lzc6JvNmpwXWomBN46jOxI43+VWkEsfGEbwq6sQi23sBJHX7n9IUkkMueIz6DJ9/ygeKYfEixEjE8Ho/4D2mL3YUVQr4hFaTIePiGvbvTzcM1YAhZsWLAQ+nnN2e3Hs089mTD+c7qdPbFV+eUw61RC7tFfjr+DxlaGYm+MxLlZaApvAr7tW406yPVPVAzRk+eb9LmUw1uoiDqjjrv39ip0yPz3Kc7/Vto1RNyvItcTegI/QAxlQUZvH8qVv6TRTjctk1l0SbrfAr5NkDG+4lf/YcxKNcJUI1jVnuyQ==
*/