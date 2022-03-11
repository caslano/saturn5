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
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
*/