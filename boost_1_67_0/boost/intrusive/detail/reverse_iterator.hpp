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
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
*/