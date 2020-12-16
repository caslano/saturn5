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
T+/mg5Ic7EOZf6V7PsX3dkHnE6+byaLWpL2TwxwTjE1Sh6N7USb7Md1pfJL4D03jk97ZzxB7ieuGuRn0vZDEUR+s5c1//b2IeknKT1bebz7OH/m4cM5Ptta31g53QfbYq2SymJwog3q679WwbDsK8zoI14hyqIMrD88vxBsRIy7HXL5mjonydLbCQvdtBsxnr40xScdCVJf72jddL8OkTMS3JJff9Aa5PHX1YmRdJr98YiTffXqu/8aFfDv2FbO28qybJDn0ISHt97xpej6vPnH5vwl0d58ZGMs+Nmsvya1u78xk5NqZ7Gnnk5GUHtD5xiw9MPY4Hp9DeqYcN8z9oHaliBLBME3b/75dnd/o+iFZvt5wXNlwdrIVD3Oa9eGPo+fJc8L7EaeGIE8qflH55s5+5y+HNBZytbG3f6DiDcCPmWHuWGDc+qUBAmX37msOGPBjB4Psg5lsK7rindXZubwnsjK6YtEYaWvtFUnj+DPdvGYc19fT/1NKor3Y/7lj7P88xrpTCxNlnZgIeo4+pvMz82Xd87vcb9avEvaRE37usZ2uu8bnTSi1Yd/5+uM5M67aZ+34RcdLeRxmrs3a8TevnuTQbrq03OfesR2eOxvjJybcu3Pysedm7+bHU39l8AGXDvYTqF+fi+m93o2eepcI6MosBj2vxLtQJxtPTbwke8JdY1tAspUkhLT+Kv68dtCdFB9up1AHsC2uOlc+2V1ZAx0nrllgEgJ8S7R/nUIOGmbfrB9dL2GmrTy3s7fyNFQOrxn0xPjGvBzcMLf85Pz9agiXlLqq+a/9dnpZSN+nflisk53Vzsz5oS25+Mxzhurp9ln6Xg3pmxJXUt9qmFO46kg+dLqhT/3+q40xaWZmsnpwKffpD73GGLe23uUCMJvXQRhUXvANv8EYEwPn463GM1u7J0aY3oPO8v6Nm40xqVcIbeCWI3nySagtPvQ2Y8zBygX47j/vtkkeBZMro7948mRz/+LG+eTHhz7u7bH80s4eyC7fYZCt7cRbm1Ff45t3HGSbOztPjsPWzdm7+pU7D7Ltg2fE32E8WbQzXVWUNrL+X9tZGvfd43bxPXxS0heHL5PTcUfqtK0tx7ameYvaWmqXMj6PdwIP7RLK74vx51VD+V1Y3cLtL8WJYnneZu49jKeucSRmEm2eWsja4F2vU2KhfYG+F13/KMxY369OlNhxW/zEjUvMuC1evCnGlG3xeTcby/fi6C0GS87ydvMSM26vz7olxpTt9eO3SvIomFxIY4ZUs2gc9bLbgjzdYD3IoV0e3L6Xpxz24lT/Z1P9X7kK9Z/7x1cO6YnzmXPr96pHYqZvTaaPXLPEjuv3e9eeh0H6wLe96HoZNlbrQZHG+/e4pRsehZuv91U3LvCQDqz3jjc7Ggd6i/J8xSxve/Py/7KrF5iyfWf12VwnYXtQDEZE84nXxbI475AijdDc3Mnr9ZjlB3b0u2fpfDmkYfpdvAJSOiunv111jIPUQr5TfEeJAxSk91XXTZgo3MPFN8xHraY2urqFvp0b8Rnn7ZHfzpeBzbHvetlVSvm4bTfXOBKTfn3g6SyPa9ctseO6FTc8CjPW98SbIizyS+B/b1Zixj7lerfIMeBToA2YW0Z5agMPPJ0m8+B5uBU8T20DteGXgr7kNMb9hC9eHWPysrh71ud9yYCZnrU/icfzHa7EAdfGM9YBd+74GNd179NFSFlZ/G4ODuY6hvZ6lRFmGCuAvatd7ShM/NBvz9K1eTSuq6b7D+m/+r/FbaxsxtyuZXU6B38Yo7rzfNzxGmPMMzqdeEzx4mx+IDmPzb4P/9P7xv5LN68cBbHBdLNc/Xv2syjrnx6UfYEXwRik62U=
*/