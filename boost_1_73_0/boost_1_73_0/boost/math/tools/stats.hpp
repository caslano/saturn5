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
AAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA0VVQFAAG2SCRgRZFPT4NAEMXvm/AdJjU91m0TvTQbohaMHCpYaJt6W2EQIuwSdq3ip3f4k/Y0O7PvvfllV1g0NpUGXSZKlWsqX9j96DYzLntOIvYaPoXeiQl+HQs+Km8gxvaM7cKUGTLRYlN1dGvKP0q7X5FuPAo+XZFjU5Wo7ORIh6a3DDkuy23Tu6YOhJI1DhiwWBQoM7AaPtFCXlYIfThoVXUk5KMSRKrrWqpsiFpzPn8J4ySI1nPKiMJdwiVvpC34ank3RdK+i4eOExGRHrAt8w4yaSXI3GILtkDonwsKaeADUcHMFNrOmDgPWgpoWm11qiuX7WN/B1Jp1dX62zgseoxjIKgH/JV1U+EtbaXp0XPY5uiBHEsP57Ctl2yBEB2WnCIfAofFwbs/TnZ+nMDSYW/7IHGI+LpR8AsGv/7qP1BLAwQKAAAACAAtZ0pSl8tpidwBAAAEBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwNDBVVAUAAbZIJGC9U0Fu2zAQvBPQHxYufAkgU0rTtBUUAYER1AaK2rDV3BlqZRGhSIOk4/r3XUqxfei17YUgl6vZ4cyoDOiDFB4r9gG2
*/