//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_REAL_CAST_HPP
#define BOOST_MATH_TOOLS_REAL_CAST_HPP

#include <boost/math/tools/config.hpp>

#ifdef _MSC_VER
#pragma once
#endif

namespace boost{ namespace math
{
  namespace tools
  {
    template <class To, class T>
    inline BOOST_MATH_CONSTEXPR To real_cast(T t) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && BOOST_MATH_IS_FLOAT(To))
    {
       return static_cast<To>(t);
    }
  } // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_REAL_CAST_HPP




/* real_cast.hpp
Htm2DstWSha0V7VdyCxINu0o2TleviVYaGrYCW3aB7jefCzCHr7a3xhTGw6HwdxbqEL9XCHeYNfmDSF9UEG9fCOsTB/d1KGNqyEy1JWd06EQMQ7rVQJ5hltCbSP0EQdoDGDuwhHgxqjNZ4eF/O5RGLtoZ4B1AOvdfMYHS1lHFXVj/iiwzB+T6ppqq8QA8mFf5Duz6wOHatkHgsvcW+oRmhfD9apbfz1MoyQ0yPHm6Xp5mgOf0tMz5GkdDdUsoRc=
*/