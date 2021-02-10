//  Copyright (c) 2006-7 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_WORHAROUND_HPP
#define BOOST_MATH_TOOLS_WORHAROUND_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>

namespace boost{ namespace math{ namespace tools{
//
// We call this short forwarding function so that we can work around a bug
// on Darwin that causes std::fmod to return a NaN.  The test case is:
// std::fmod(1185.0L, 1.5L);
//
template <class T>
inline T fmod_workaround(T a, T b) BOOST_MATH_NOEXCEPT(T)
{
   BOOST_MATH_STD_USING
   return fmod(a, b);
}
#if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)) && ((LDBL_MANT_DIG == 106) || (__LDBL_MANT_DIG__ == 106))
template <>
inline long double fmod_workaround(long double a, long double b) BOOST_NOEXCEPT
{
   return ::fmodl(a, b);
}
#endif

}}} // namespaces

#endif // BOOST_MATH_TOOLS_WORHAROUND_HPP


/* workaround.hpp
ZQM2hdLIJN+jJI9EdsyOYYnNJzapr1YEarA2WwKsVFBRjQ/OBnDe78P8IWG3KqCAR2dP4fwK7jemfXMFg6EYXgvC3D3mCYuCAlqfqe8GXqgPTNjIkR0b0hna91AKuOyOLOpQOStAG+cPUPm2xlblO/DaqMomLGFp4VxK/qM/yX/9dkFGpmppMYjuBoJEAxkrQ6iJ8DeCtGqN2a4r+KpCCXazxqbSYJxWpnQ+wGGFIHkkgdRuvVZ2FWUF573JfJlPF6LX6i3mzzkf9IcXh2zojWbT8ROByMWOTo+/RrsIr7S92EKbDlRBTAgldkVCqTy8IVo48qULR0x+dliSqBsXnHYmY22OuPjvyyVsQikE/POXsBeqIr15p+XU/KYxvPc6fl5O508Ju9Eaazo+4Sdt6ZLvV0i+28v3P+IPUEsDBAoAAAAIAC1nSlIlNUbVGQIAAIgDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA0NlVUBQABtkgkYG1TXU/bMBR9t5T/cFRUZUPLTBGqWBZFQgyNbkAryHhBPBjnhkSkdmY7sP772UmhTNpLLNv3nq/rZI6sk8JSzrJGVdovT7R50aa0OTsvitXwwfezgiVJoxyZSkhii9XznGV8V5rxsZvtsT3c
*/