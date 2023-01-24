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
ya/6UZ2LuS6pFaX9t5gnU/rYgUOFqzUF5H2A0TvMRm/DFDZ6d1P/wfbqW49T9jbpV4eUKB118HgcmSh0xovAiTBKzfChoz0ncVyvwcqyUXgwD1q2dJTFDrqBLBNgT7J1ODBcBEY5kyhbN+0DC6vNM1Su88qGRRtE5uvKxekzZyQ7nljAjifexucOGFTSjebmm9FNUh9a4kwU9HqNrWxpKk6mk5+ZSFZLxzwTRGmpGc8eifB+/OcgysdwUY7HlOFdn88x7xiU5vVUbAxKc/tokOZP/F2Wt5cKTAwNGmniPDIqhoO613HX90ln2euYVB+51xGkjzn0nYuEzbXq1sYTdZ3Z2jjKHra1EbBxy1j9/kucm2xhhuJHHmPHVh/CcDnl8rcWQfDAPIhnLGYdruuuQ941nSRzJshYnNpUxySympUKJkMFkpe29bQbPH3KduCaqeC+QpQkgR81uxB1l5Z+3vY4T/+yHS/Qdyt8N/PvIBuSZGsLBe7RAyBK62mzAUi2wlDf8XzLeyGayNJ61J2I25YOYG+hohTEYyHn4+tI0cu8ETHhHa/SBXevqVszy7+xscXknieSlIOitI4NwwW9LWG9XFCLUUofZDqsNL5Etr4J4Hp34RJwwj3nclV3CFNyNw7Z8067v6qBYH8wfZ1axkaxlV7FD3lDXqa8du9bvygn5LMpRpVl1aBE+J79HCLS3RMSiDF3Mm3yyl1d
*/