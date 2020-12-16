/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_DETAIL_REVERSE_ITERATOR_HPP
#define BOOST_MOVE_DETAIL_REVERSE_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/meta_utils.hpp>

namespace boost {
namespace movelib {

template<class It>
class reverse_iterator
{
   public:
   typedef typename boost::movelib::iterator_traits<It>::pointer             pointer;
   typedef typename boost::movelib::iterator_traits<It>::reference           reference;
   typedef typename boost::movelib::iterator_traits<It>::difference_type     difference_type;
   typedef typename boost::movelib::iterator_traits<It>::iterator_category   iterator_category;
   typedef typename boost::movelib::iterator_traits<It>::value_type          value_type;


   typedef It iterator_type;

   reverse_iterator()
      : m_current()  //Value initialization to achieve "null iterators" (N3644)
   {}

   explicit reverse_iterator(It r)
      : m_current(r)
   {}

   reverse_iterator(const reverse_iterator& r)
      : m_current(r.base())
   {}

   template<class OtherIt>
   reverse_iterator( const reverse_iterator<OtherIt>& r
                   , typename boost::move_detail::enable_if_convertible<OtherIt, It>::type* =0
                   )
      : m_current(r.base())
   {}

   reverse_iterator & operator=( const reverse_iterator& r)
   {  m_current = r.base();   return *this;  }

   template<class OtherIt>
   typename boost::move_detail::enable_if_convertible<OtherIt, It, reverse_iterator &>::type
         operator=( const reverse_iterator<OtherIt>& r)
   {  m_current = r.base();   return *this;  }

   It base() const
   {  return m_current;  }

   reference operator*() const
   {
      It temp(m_current);
      --temp;
      reference r = *temp;
      return r;
   }

   pointer operator->() const
   {
      It temp(m_current);
      --temp;
      return iterator_arrow_result(temp);
   }

   reference operator[](difference_type off) const
   {
      return this->m_current[-off - 1];
   }

   reverse_iterator& operator++()
   {
      --m_current;
      return *this;
   }

   reverse_iterator operator++(int)
   {
      reverse_iterator temp((*this));
      --m_current;
      return temp;
   }

   reverse_iterator& operator--()
   {
      ++m_current;
      return *this;
   }

   reverse_iterator operator--(int)
   {
      reverse_iterator temp((*this));
      ++m_current;
      return temp;
   }

   friend bool operator==(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current == r.m_current;  }

   friend bool operator!=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current != r.m_current;  }

   friend bool operator<(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current > r.m_current;  }

   friend bool operator<=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current >= r.m_current;  }

   friend bool operator>(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current < r.m_current;  }

   friend bool operator>=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current <= r.m_current;  }

   reverse_iterator& operator+=(difference_type off)
   {  m_current -= off; return *this;  }

   reverse_iterator& operator-=(difference_type off)
   {  m_current += off; return *this;  }

   friend reverse_iterator operator+(reverse_iterator l, difference_type off)
   {  return (l += off);  }

   friend reverse_iterator operator+(difference_type off, reverse_iterator r)
   {  return (r += off);   }

   friend reverse_iterator operator-(reverse_iterator l, difference_type off)
   {  return (l-= off);  }

   friend difference_type operator-(const reverse_iterator& l, const reverse_iterator& r)
   {  return r.m_current - l.m_current;  }

   private:
   It m_current;   // the wrapped iterator
};

template< class Iterator >
reverse_iterator<Iterator> make_reverse_iterator( Iterator i )
{
    return reverse_iterator<Iterator>(i);
}

} //namespace movelib {
} //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //BOOST_MOVE_DETAIL_REVERSE_ITERATOR_HPP

/* reverse_iterator.hpp
hB6oDt2EmNCKml9swAps76skdS5Z0k9q4sWziuhY1xpOusaZglu2whUtbm1eUz7/CfzGRiAl8AmpNd42fxA7FPgt5+2863vSg4l2vG+fMUontre+tqmq+RruttNam9e7YpMJGKsGMuiosjrIGQFYJa8n+WiyBlE23OstuDspEcO9PiszVNnrGdr1KBzx6+Nt8xjaeRa0P/sToJ0n0Ha6mEJirc0rXc2lRHN7fxdvuhN0vzIeujMRuvMuKf61RGi1BcCWRNNqBmC1IwElb22+09VCeFtdPv+n/AzSuZaXqqvdsTLKtX3GmC0nU1GsdFkNisamZ5RgcfPmmzwLE1nlilLclVacPMu0VVkdXlNNZN+O5NXtiMDaCU0ZzcDRHLKx+vF4aCMGR3h9PLzs+hKDS8H2EuxpoxgPTGx9nixUKfnePUgOVqRGr0eilmsYiA9gRZSz7b2AtKD22uIOXopu5MG90WCYXMTJkZNNuwZrWTIjI+u5lJVq583pjcmnjFyVNB1latZHZ+SqRK6mjdzNyAVAj4P2ICffr/c680EBSiTtavmAk6QDm2k0NOQA+vWMrA/DxvAJ9NkChVm4Ev1c5MSc+uZkZJrH9a1HfQ6iRH2dufVVZ2Q9w6hvGWMxpwPe/IczscqL8GXcAcuAj3vcgbYnzA6ujBVvD/3g0qSPfkOkFvxBLpp+kFHcVsrJQ+K4yAk5YC7KSPoVEOcxkeocAGdbySA+XE1jwNUymZazDONqotLAZhoNuZBMyMh3WnI7E+wJkcocQN74uzOlCirawlT0tMOC6eLX0u/Q/sK7n/+uD+Q77PXoowac8t25hksAOuaAzc8doS552+MweodGg4fERGadE00XAtBiVvAB9Umtz0+NzYSV2YKq+cWwkbmmggo+gc2vqkPBDchyeLiCslD6ZCXnYCFwlwiBJGm1drMQuKuSiXdS63MKLHIrFUg9HTN+frhKLyq/7KGJiEuoRIYtIhFt4bXBxtTTcsJgYxfvBlfWPNlQn2jaSUNnW71+PRkL4ML0xnq9kmT8BLT7G5f4PItnjOqmF2jSEVRZs6W+MRHeSeNsG20PvpAeBNxNO6mMkaGdkA26xs1vx29sBLL1SrYuYm/E7cbxPHtxF5UfWr99RhFOiU6sDnfFYbc/sbapaz4YKJ1noHkWoWtwAgSwrzalz9WM4FhVdWxNdYx4RUejflicbRqq++OxPaShRz9I35BuHy/SX4xFFdcCdtaG91A9TXSc/SHM5zS7PZTAyYlOIynwJ1PfHkx92CPIP/Pc+aqT3x1DMFrnGMBpd/HMsyuXkV2Yke9lrrKD9kJoK+f9iTA9leVOqxMz8qylPJSSe6UjuRXNbqnh3xPyzKt9/U522JwIdfKk2pl8mk+VTHZ2FHhvdy7ID/bn8N49+XnvgoyUKiGRee8eg/d+Wpjvi3/7P2K+4C9BPv/4l7TD3oMXLcEOGoy8MMTyHVpU0GSVqFb5enD9LLbjUfgy3spqnClP4wI6MJM0E3jaXFzOP2oD9OLV4fQHw1XNI0mW9sLDTxVGThVisK3XDdIOp/f+1rgUseWjnBUXT0HC/mCkMof4vvdnJ/FtlymUSSZt3e2V/DG2x6+dbRQWStWGqpo/TqpeImfehuzLpapPSLnxkH0jAI4oMeVcTBpsJtMB64B/8m5u8YwMeE/NA+8brzhp8D3W8Q8b2LX/TuWCbf/zSnqQ18amXouPOfOaN+VcH+MiGcaFknz22eHZF8j9l1z+JD5jQotI/KhhhZaMO6lUeoBaDcvZflqpXz3CQpNhgTv0/YjP9mXNl10gYByN7pYOfm4HK57Edf1g7FxiMHT+BoG8ce2nHG9i4+BjMJA=
*/