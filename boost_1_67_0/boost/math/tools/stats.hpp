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
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
*/