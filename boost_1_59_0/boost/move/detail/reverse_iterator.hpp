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

template<class I>
BOOST_MOVE_FORCEINLINE typename iterator_traits<I>::pointer iterator_arrow_result(const I &i)
{  return i.operator->();  }

template<class T>
BOOST_MOVE_FORCEINLINE T * iterator_arrow_result(T *p)
{  return p;   }

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

   BOOST_MOVE_FORCEINLINE reverse_iterator()
      : m_current()  //Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_MOVE_FORCEINLINE explicit reverse_iterator(It r)
      : m_current(r)
   {}

   BOOST_MOVE_FORCEINLINE reverse_iterator(const reverse_iterator& r)
      : m_current(r.base())
   {}

   template<class OtherIt>
   BOOST_MOVE_FORCEINLINE
      reverse_iterator( const reverse_iterator<OtherIt>& r
                      , typename boost::move_detail::enable_if_convertible<OtherIt, It>::type* =0
                   )
      : m_current(r.base())
   {}

   BOOST_MOVE_FORCEINLINE reverse_iterator & operator=( const reverse_iterator& r)
   {  m_current = r.base();   return *this;  }

   template<class OtherIt>
   BOOST_MOVE_FORCEINLINE typename boost::move_detail::enable_if_convertible<OtherIt, It, reverse_iterator &>::type
         operator=( const reverse_iterator<OtherIt>& r)
   {  m_current = r.base();   return *this;  }

   BOOST_MOVE_FORCEINLINE It base() const
   {  return m_current;  }

   BOOST_MOVE_FORCEINLINE reference operator*() const
   {
      It temp(m_current);
      --temp;
      reference r = *temp;
      return r;
   }

   BOOST_MOVE_FORCEINLINE pointer operator->() const
   {
      It temp(m_current);
      --temp;
      return (iterator_arrow_result)(temp);
   }

   BOOST_MOVE_FORCEINLINE reference operator[](difference_type off) const
   {
      return this->m_current[difference_type(-off - 1)];
   }

   BOOST_MOVE_FORCEINLINE reverse_iterator& operator++()
   {
      --m_current;
      return *this;
   }

   BOOST_MOVE_FORCEINLINE reverse_iterator operator++(int)
   {
      reverse_iterator temp((*this));
      --m_current;
      return temp;
   }

   BOOST_MOVE_FORCEINLINE reverse_iterator& operator--()
   {
      ++m_current;
      return *this;
   }

   BOOST_MOVE_FORCEINLINE reverse_iterator operator--(int)
   {
      reverse_iterator temp((*this));
      ++m_current;
      return temp;
   }

   BOOST_MOVE_FORCEINLINE friend bool operator==(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current == r.m_current;  }

   BOOST_MOVE_FORCEINLINE friend bool operator!=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current != r.m_current;  }

   BOOST_MOVE_FORCEINLINE friend bool operator<(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current > r.m_current;  }

   BOOST_MOVE_FORCEINLINE friend bool operator<=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current >= r.m_current;  }

   BOOST_MOVE_FORCEINLINE friend bool operator>(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current < r.m_current;  }

   BOOST_MOVE_FORCEINLINE friend bool operator>=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current <= r.m_current;  }

   BOOST_MOVE_FORCEINLINE reverse_iterator& operator+=(difference_type off)
   {  m_current -= off; return *this;  }

   BOOST_MOVE_FORCEINLINE reverse_iterator& operator-=(difference_type off)
   {  m_current += off; return *this;  }

   BOOST_MOVE_FORCEINLINE friend reverse_iterator operator+(reverse_iterator l, difference_type off)
   {  return (l += off);  }

   BOOST_MOVE_FORCEINLINE friend reverse_iterator operator+(difference_type off, reverse_iterator r)
   {  return (r += off);   }

   BOOST_MOVE_FORCEINLINE friend reverse_iterator operator-(reverse_iterator l, difference_type off)
   {  return (l-= off);  }

   BOOST_MOVE_FORCEINLINE friend difference_type operator-(const reverse_iterator& l, const reverse_iterator& r)
   {  return r.m_current - l.m_current;  }

   private:
   It m_current;   // the wrapped iterator
};

template< class Iterator >
BOOST_MOVE_FORCEINLINE reverse_iterator<Iterator> make_reverse_iterator( Iterator i )
{  return reverse_iterator<Iterator>(i);  }

} //namespace movelib {
} //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //BOOST_MOVE_DETAIL_REVERSE_ITERATOR_HPP

/* reverse_iterator.hpp
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
*/