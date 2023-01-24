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
bW2/kyqPzBK6cJxFXY8Z3ZfYTfOfs35g3+j0avsutdw2OlTBVzxWr83yjdW7dBN1MFZVTnCsHrKfo5GqL9sBrkJ7OulnRjfQS5VljtBJaq++jL6vamO09kZp3dE3ae2NGf6fftZ+AV0mqVh+lt261npR68o27nZ8bbydbo5wG++saONh++lyG8trPlxe88/54bjy+cv0wH7bbJOGRY46afwkdVKmXp30hm/+Z0fVf3HfaaBKnsqnqbAOBqr2AdbEuPrAo0YTM2I0MayDOWO2t88fpFXSEG4/qketI+HLCMOkXZOH1alXhjud6yN7o4ucRepykthj4cZIfEacettsXx/upptHZmMs7p8dJA+/cb5T1p2YvRcJ6n/9cFy59nX3/Wrgn5Ms5ezx6f/CUdg8GqjSEnbn2Cg/SVx3B081dNeoU7fNV6eON6lTMyerU4lnLEtqvG5H6bU9LozzqLKLStSQ7el0JfGeMtejIOTmui/+ijqfGJwlzpJwKrI+2mBZtyn/GinLGz65xL2vNTIu8WfEtwuP9hx9uv1Furxi+mHUKFZGxQ1dbpul4tSHeKZRxauSSnii2Bxacqb/VGmZY/r/dXe17tVXGVpoeC0aRlpvDbTWG6hdDZPEa/l4+hF6bewc991h1ZC0IVMQ75hcnTDtmqA/5b5El2up3DbH4EEzBAYP3jgnyHh8OeTsta7T+xT4ZaPznkf9rFVz
*/