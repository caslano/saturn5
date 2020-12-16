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
lPkRou8uaX/gbl1c9MuaBk1LmQqOK7xdbNY7/AbBixo6puGcVSq5aTopRXTCMCD+nI8/Lusyr+tGjPBNXb44LP88wed1K9u8TVgMSUGnZ1/cig7frdPv8fEN087mbVImTCeHBA7wd9OpzKdAB9RH/sN0P5A3TSXruGRcFDdNK7is0GxBLIN/bwR58IuiiqK4YXqzSTbwdH1/56uC2MAxj8o6ScGwX0TZjp4Qz3+BmAliTgwJv2BtptJUPxzYnvVAJ3tyQHmTporSpBjdh5i07RxCAtv4MkfxZuQJXd1P+ndEZVOBnjgUU83Q9xs3DIJ4LCoVgqdMbG0sLeiXA6hP7vLo+zy8Zdo44iJVDMbS0qZehUee6EuLmll73iWqlfASEBJv67hCefdWwB9fac7qqBFp1GxTDgxw+CKHhivIMgD/B/6Vswlnr36dpqRMeMzLlEHdddjW+qZjozasuDhCPv6ZlWizqohbxBu0F8/oPMELlYGJt9UIfzi4U3kn1akq8yrlAsDT3X9jkam60+vQxR/y+Y7VWamqNi08NmhFGD/mwz7PdAEsZVFIj0fU3Aoi30BfpfOqm3N/vYPQYKGkcfx+fs8+3S4ZeI6922JGecFw4vbP0h9gMfpuYQ6uYFdOwTEZfqe950FIv8WEXkLauQc72ro9+sB41vsszVzKou3ZrZIrY+8NHW4DZhzjYIvvfh9paabmyCMfbX/HFjmeLz3B0qzKnK4Pkt/JucfFQ0Cz502wVrjf73qa/l373cOI8XOZH9a/h5+YuP7+dIN+t9WpUG2eX3VORLteuTH18VeRWFt1zZWI427WPFF2ccI6u/8Zme8imLPiMtPvIk/MROM+81xeqVsoX14WNS9yyfiV+W70+VqYu2QlpFBMJOO4rH1a+/+a6RPdFGMZtqdxL7Wyo4fBXvf3XPfu4cigeBT66wHO+n74MR8snd0/pPf9Uj7Xw1Afu5N7KN3GsXUyOPyNdBqn0cVi83X6LCG0y0BVMnsAS9eO23xsxUTTtEUtM+adJHeqR58EWn7OozpOS2YPcoMcV4AlcfELVci2rFlwhGvZ8Kwl4KvaVknZNpRv0/G5cxPCp1iaRmUpec22+QQI305fIvySiTZPs7Ys2PhPA5fTzuoGjM6f/9NKCsklcJsDYJuPpRubu3xsydq0FLVUOcPTYtpX+1bom0uZZakoOKMnyDS22yEqI4+LJqmjlOFXCpVx4wqNSyaVqGRTIB5b7XjKFWpDbZzlXMbMO0Xv+R68jMrJuGiLsi0sj98UtLsVn+dZSSrKOEkVs4fatB1btE6VhLUeVhELHm/X50n5WSKjPOWS2Umclv8eWv+6kWnetDUjK3Jg0x9eCeJqNUVd5WVKmfr9/i3a7yqqJE8zzugKTvetd60EPuQVb9M6KwImTw+497lMeGMm2yhK2pyFK71ldOdv/6Y6yVUNc4+yfOt+n+I55+7V4E2erPKMy5pts/yHcTAP+vzHYRrikset4cYe8OKvTfn4mskERpGKUsfgKWTO5XkjdcwA22SpftQ79sguOF8M2qeEjJRqIrbNUV44H50L+Ju44nWWt5Qf56SOv+vLOwh/wkSeVXUWlax3ZEnt53OrwbdLCRNBmWXIF8rE/exPV2l+wrwQea0aRk7sR0yv6/rxlz7PdNVESkZ1wdymK5RxicpIZJyUQkhGdmlWRtemv5E2pUzFUVmJtEamXqMid4e0FsS2gIk3U6Vg/e1F7yz/IOGFOjYihXHRUt7Q/NAGOOFXjEt9e1LVlL83oO/R1f2Va2FuRFiyi5qd0mmwT8GpxbEpnXsLs2H6ffnHHSS2bVLlVVmMWDHTJM35uLVGxlgGJpdGlWU=
*/