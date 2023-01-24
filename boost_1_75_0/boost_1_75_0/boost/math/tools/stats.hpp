//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_STATS_INCLUDED
#define BOOST_MATH_TOOLS_STATS_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/cstdint.hpp>
#include <boost/math/tools/precision.hpp>

namespace boost{ namespace math{ namespace tools{

template <class T>
class stats
{
public:
   stats()
      : m_min(tools::max_value<T>()),
        m_max(-tools::max_value<T>()),
        m_total(0),
        m_squared_total(0),
        m_count(0)
   {}
   void add(const T& val)
   {
      if(val < m_min)
         m_min = val;
      if(val > m_max)
         m_max = val;
      m_total += val;
      ++m_count;
      m_squared_total += val*val;
   }
   T min BOOST_PREVENT_MACRO_SUBSTITUTION()const{ return m_min; }
   T max BOOST_PREVENT_MACRO_SUBSTITUTION()const{ return m_max; }
   T total()const{ return m_total; }
   T mean()const{ return m_total / static_cast<T>(m_count); }
   boost::uintmax_t count()const{ return m_count; }
   T variance()const
   {
      BOOST_MATH_STD_USING

      T t = m_squared_total - m_total * m_total / m_count;
      t /= m_count;
      return t;
   }
   T variance1()const
   {
      BOOST_MATH_STD_USING

      T t = m_squared_total - m_total * m_total / m_count;
      t /= (m_count-1);
      return t;
   }
   T rms()const
   {
      BOOST_MATH_STD_USING

      return sqrt(m_squared_total / static_cast<T>(m_count));
   }
   stats& operator+=(const stats& s)
   {
      if(s.m_min < m_min)
         m_min = s.m_min;
      if(s.m_max > m_max)
         m_max = s.m_max;
      m_total += s.m_total;
      m_squared_total += s.m_squared_total;
      m_count += s.m_count;
      return *this;
   }
private:
   T m_min, m_max, m_total, m_squared_total;
   boost::uintmax_t m_count;
};

} // namespace tools
} // namespace math
} // namespace boost

#endif


/* stats.hpp
ZnqoYg9GeqhkD4nw4F64/UdAU372q+iFdV/kkNY+YmCeov7I4UFy2lPFnFFmj2X4pFRPMjQbev0tI0gvKGLHIiIUeYIXGUFFrpTsZipyMRbJwCLuOjw7amo+D3tUByJRFpp7sbSMsi4Z0qjhsS2H197Mtl+RogsiXr/9KvxsyIgkxUnVg1L2Ykg+ZyZHH3epLzTrXeo5Zr1L/SeT3qX+qknvUv80Ue9S9ybqXerWRL1L/VWj3qU+wah3qf+coHep+xL0LvUxCXqX+rkJepf6+ni9S/38eL1LvS5O71LfGKd3qd8Wp3ep/8vA+mAgd2IT/ITaHkF1SwoaNHdg0KBzIEuofITuW0iOxid0uZ7Q5ZKkR3RfHgn7sk73ZV1Yzbg0Qudtktl5m0++NOm9mcbQJeQr4k7rwD8E4WA+EEVgQonTbzdbpgXhJ7W6sSfum7KnwT8b/MuAf5nlN80RgrKMfle/Hewn+gW91Dg0hJ7ACYWAhOfJEnH645z+cmzSyRzDecwjDLU48/z2yfCvyNK9XARQ4aeQ/RQb2EoEeypgP0XsZQnD9OtAEXmrKAujx3sTVXrsnainx0+Nenp8yainx7lGPT0OMOrpcUKCnh5/iNfToy9eT48D4vX0uDtOT4+cPjg9/mTQ0+NWg54e/QY9PcYb9PT4kKCnx6sEPT0mCXp6PC6bFHpEvLOfR9jPE2xtr7o/eemR7rz+XBBi
*/