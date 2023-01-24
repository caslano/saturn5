//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP

#include <boost/mpl/bool.hpp>

#include <boost/compute/type_traits/vector_size.hpp>

namespace boost {
namespace compute {

/// Meta-function returning \c true if \p T is a vector type.
///
/// For example,
/// \code
/// is_vector_type<int>::value == false
/// is_vector_type<float4_>::value == true
/// \endcode
///
/// \see make_vector_type, vector_size
template<class T>
struct is_vector_type : boost::mpl::bool_<vector_size<T>::value != 1>
{
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP

/* is_vector_type.hpp
n4Z+/DF640/L+g+6+V9zsE5+4oHanboxrG4IOT/Vr6llejXDiRCcOWU9eyTC66SBKq1UcpFy28CXdESCzP8LIecu6wKtO1TGEryaILw6TyWe9vbVOL1lZOqtVLmTyt9SSfj31YfpNnf799iCkFax+De9JhgVWF2440hZz7k22h7ZF9sePxhpNnutU13G2s5ILBZvVMxzvtRAfGeS5qSeeM6Eqj2OuY/URNXXTP+psoLKWI3hO9yv5zUzHmwR8AyNaGmV3uzuk6nXDeuxuiYa4Kpmz2n9mbUiPB6ZjC6KvBJbHIqscHLUwhxxH2NE4GKRZbElJN/PVvXjp6r6TKuqr2pSc4/XTMu6PEQQ/8lt24NUeZLKNJWwYxbnTl87RowO5OmaIMNxe3W8VtMoXeI02/dYE8Sa1ttLVcPJLl8zx8iB5X1l6NF/J3p06wn0qDNKe8OlR71UOYdKOIyuL/XIEjgwkKWjjbtVQWeJLO1wbg33aqdo36iWG9Mo9MXzaQ0SDZ476dlcd0ejnv75q3QT38jK5u1G2ZwjyjYTrnwiymv3Gar8jMqbUbN2DYEya/eX0SDS/JJ2DluHVdFqNHhw0Wxat00k/iWUx42i321zeV10U+VCKpfPNevXE9KqsCCECfVbaHcZ66tbP9ptFvAlcz0p5ee0KV+Mpg7TErjKXk7F1Uif6WqkmyI3xo7E+3W0OdxslNMHVate7iqn
*/