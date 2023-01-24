/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_REVERSE_ITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_REVERSE_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/iterator.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {

template<class It>
class reverse_iterator
{
   public:
   typedef typename boost::intrusive::iterator_traits<It>::pointer             pointer;
   typedef typename boost::intrusive::iterator_traits<It>::reference           reference;
   typedef typename boost::intrusive::iterator_traits<It>::difference_type     difference_type;
   typedef typename boost::intrusive::iterator_traits<It>::iterator_category   iterator_category;
   typedef typename boost::intrusive::iterator_traits<It>::value_type          value_type;


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
                   , typename boost::intrusive::detail::enable_if_convertible<OtherIt, It>::type* =0
                   )
      : m_current(r.base())
   {}

   reverse_iterator & operator=( const reverse_iterator& r)
   {  m_current = r.base();   return *this;  }

   template<class OtherIt>
   typename boost::intrusive::detail::enable_if_convertible<OtherIt, It, reverse_iterator &>::type
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

} //namespace intrusive {
} //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_REVERSE_ITERATOR_HPP

/* reverse_iterator.hpp
deKm3EUYg0eof+Z5GerxB992489vvALZ+xpf+J5JiNYIbuWf2Z55oTjujVtF06a1z2bPou7Fh0fTRxz1EF90kTHFFRajguU6mlcGKLFfWLdIEcf0VVzlr8fDG6lBifWpK9xhSdz4yOCppEgxykVx6GGTMVy4XNCqOdbS/diT/jckQ1pYXLgCkp8eG8x+5HnsRMHhpz+sOI3BJ/7yLHZb9B71/RBdiPmSpsfJRL0GO/3PxXLzUDn+4/QRl8eCQ2K/E1Iug2xt8yrOGr4lEpYYtyF6s2pB5RMZ7CmjpO5IwT+U7Xhu0oWDKzLgaPSfBONqZqQv2HlX+bNmWju/2sGCputKT/hA0NYRz9T0irDmMa9fz6PkdN4pHJfoif0p99bIdEhHGfMJjgJfpIPDw16gtW9z9WcAqoJse3COnICH9/MX7q9Zvjniw8ZkUFlu5Foxo7CbkmkuRz88aJzHxW13ewD8zRXcwbM6Le0zADWfTw5QwFOrwXfEs9GAf+QRr38YCSO7eEA0xuxU34XbN5Tj3HoZtivkb8n+BGnfpkC3LgDAB66L8p6SHjNYC76gHsJzJzAS/6jxXIBo1njDg2vm+OSUZRExjaMHBlTfhMFQ/2Fkcv/zzkmcN/9/FDc3Jx/3fzWyb7ZMs8SNucBFsXVSqsbzSml8S3JTlp2C/pxcQ1xr15yGPJtV9TH/UyarvTtE3AqJSOCndmdVwZeu
*/