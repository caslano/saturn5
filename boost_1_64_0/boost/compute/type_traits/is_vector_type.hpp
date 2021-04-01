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
ZuElbmnmGRdJnrsppFYH/ftnBgzhavLnLGHpl8vZ6DGCPuqBWflTkzJpb42XtuHTxDjBa62LXkQmRmG5Rsily6vEKy1rFuzsyNAuDk8b20llkF0/NhriUbOjN+MPzK79ZptJ5AFpyuKW+EjOqvNHnNZj+Zh1Ufy1trFQM3zGItskUUYp169SN/6e05gMhLW3WT0Wx/05562uVvTbPXTtXVGhk4n9+e2z/ncB5pOOEM9x8o5UT63+WAXclwQ6h6B2Qs3/RkOwzY1H/d2lb5T1qPyUkECu+Xq3oTWFJB5GcgDJlBrDsIS7bHTT8arjt4WSu6adqeFmPui1VUezShongrEQuE+Y2Cf0BYphTm1C0sM0fxn5D6lvZKoSIpCvNsRP3yu8pwKzG3q3uGfPWisdcmO71uOfKpTDfCr1p3t2o/pWf2fvhkc2ERA9IiYQkIs6Oau/o36Qml+QtdyYTb2C3NF5W9Xuy+0/a0ljficUg0A+n2pStoX1kQ2+0DOy30w8i+pBPLqsRe4lDlmi54ZuXcjDZmNPW/a6Ii3sevo/70zq0T3hcBqEMmcXLA==
*/