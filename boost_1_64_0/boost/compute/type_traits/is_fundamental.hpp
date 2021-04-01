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
/NL5u8KypNp8qCF+1gjpBlRyVNgLY4rA36/ufUwrBgtCkiPgZl3/D8um68CWj2gR2iajLdO7ypqKYJCe8x9vegT40c2Bl5K9ctZxSw5Z2aAd+o9AvvsNExFpRuJ69MiEx6+bcM+66hafwsLJ/Tp9LE24s3Da/2UxXVf+ETmWQTQj2hF/poFwbCtMSGgUm+OFAOaLE2Yu77R6crHgg3E28oaZEgM9nDfpo6BzX/LVjLrahhY/fS0oyt0mVoxGmVUjx3wb11hQZIueoV4bAKN+mP1Fp9aDu/Qt8aJNq2669CuWB3/FwRZM1HzIGrkJII1CZIdpaTsNnHUj3xGbbcjrMvAXsm1V5Svy5WNZRdNllY7JqFHosOHegSyRnq03Km7oe2RGn5Vmk+JsNUdra5P51XnVzpH/rmxpic3WfIhuVHX6rbjXvvZRPvF70RkvZZBan+BTxwO00tyscOiUgdDHpgYQ+wSA/NeIttxqS2Udfn7M3liwGa1BkJ4eWBEkSFY5MoykR+AlfGs71wdygA3af8iWwg3i02OY7WjlgoArXCMFPETGc8RbgBfEsw==
*/