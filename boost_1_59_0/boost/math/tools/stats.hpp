//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_STATS_INCLUDED
#define BOOST_MATH_TOOLS_STATS_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <cstdint>
#include <cmath>
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
   std::uintmax_t count()const{ return m_count; }
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
   std::uintmax_t m_count;
};

} // namespace tools
} // namespace math
} // namespace boost

#endif


/* stats.hpp
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
*/