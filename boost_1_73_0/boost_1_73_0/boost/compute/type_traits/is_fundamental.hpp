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
/s6v2GLOMeQK/JI0zq3rNgqGmBMMXISTpoSjyNICqoWkaqVgGue/35ldrRCSsNzcfrj01Ajt7DOz87azszl49s99Kgek9KPz/3X4wDdOGAXeH9QMi4l1/YGI/2DSJ/guYXFEtjMe9AYpnfFA6nyGHvP4GZ91vYTNJxQM/xzhxE86PsKbygHMa3v+JrAXy5DU2w1yenz8kjTh6/RYIZfGF9si2tJYk58tBl+v/zBub2mw9sy7Tcv0Vr9whMnSZoR583BtBJTAs2Ob1GXUIgYjFmVmYN/CD9sl4ZKSue1Q0h6OPvYGbxWyXtrmEjA2XkTY0osciyyNL5QE1KT2FwHhG0FIvDnMBmzLZiHgRaHtuS1gTUlIgxUDCGRuOMwjxhfDdoxbYGOEZBmGPvvp6MiMAqfF6JHlmezIlGtuLcOV0+Kr+AgSrIwN8fyQhB6JGFUI0ilk5Vn2HL9psICXfnTr2GypbEUBRq515AWEUccBKJhmUyZEpkSLNaMgFfFBWjvEL+a5DDmtl95qhxBUCCDzKHCBDagAaCwPFKyQyLVowGn5oiWHWJtcta1ik2xltYjngiSkqmqkp1XJrcFsppAPvcnV8GZCPqjjsTqYfCTDLlEHHwHrXW9wqRBqA6eA0Hs/oAw4B8Re+Y5NLc7w
*/