//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_IS_FUNDAMENTAL_HPP

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// Meta-function returning \c true if \p T is a fundamental (i.e.
/// built-in) type.
///
/// For example,
/// \code
/// is_fundamental<float>::value == true
/// is_fundamental<std::pair<int, float>>::value == false
/// \endcode
template<class T>
struct is_fundamental : public boost::false_type {};

/// \internal_
#define BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(type) \
    template<> struct is_fundamental<BOOST_PP_CAT(type, _)> : boost::true_type {}; \
    template<> struct is_fundamental<BOOST_PP_CAT(BOOST_PP_CAT(type, 2), _)> : boost::true_type {}; \
    template<> struct is_fundamental<BOOST_PP_CAT(BOOST_PP_CAT(type, 4), _)> : boost::true_type {}; \
    template<> struct is_fundamental<BOOST_PP_CAT(BOOST_PP_CAT(type, 8), _)> : boost::true_type {}; \
    template<> struct is_fundamental<BOOST_PP_CAT(BOOST_PP_CAT(type, 16), _)> : boost::true_type {}; \
    template<> struct is_fundamental<BOOST_PP_CAT(cl_, BOOST_PP_CAT(type, 2))> : boost::true_type {}; \
    template<> struct is_fundamental<BOOST_PP_CAT(cl_, BOOST_PP_CAT(type, 4))> : boost::true_type {}; \
    template<> struct is_fundamental<BOOST_PP_CAT(cl_, BOOST_PP_CAT(type, 8))> : boost::true_type {}; \
    template<> struct is_fundamental<BOOST_PP_CAT(cl_, BOOST_PP_CAT(type, 16))> : boost::true_type {};

BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(char)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(uchar)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(short)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(ushort)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(int)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(uint)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(long)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(ulong)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(float)
BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL(double)

#undef BOOST_COMPUTE_DETAIL_DECLARE_FUNDAMENTAL

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_IS_FUNDAMENTAL_HPP

/* is_fundamental.hpp
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
*/