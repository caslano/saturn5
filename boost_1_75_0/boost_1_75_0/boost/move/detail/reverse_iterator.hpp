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
hUuEVkcm8L3Wfiqdj9XVdA8skT6iJx5pWeXqd5leAnRf0f3vSw9a/CXxGyeN7LM7Utn5nUPu8skThlxs6fBPK//RBN5j3DHZVG7hMXjHBO4rYPlwsn/V7cbttDdXq/dpJSDe1PoTgXPBLQHd3+SL682hRPiTyM6wHmoyKnVdM6AnE1ZPsn4MhgKaX4uEwlroqv149kvC/8ADfUV8INL9aPagTHqwRLwZA7mkNsItXuARc1DuXkvnHf+KxwGdSICvTPurbhs/4rC+5YEQ6tAG8zZIMSkkyA4n68CSFileacj67PqKr8/HAdgL6aWv0nYhnLQzMzzKfz73lbVofwNNuhGrZUBkElI9LkY6jgzFP2DivwKA/2sPKvw6bWvhOE5jQT2orUXoa+dXxpOvFItF8jQcJF+hvFYuu+uL6v/g/QLzDH46ZISpuIS8Q+6l3Ou8l3JqWleZl1FX2f21ef8vAM9/TcYuWMzHLr0rAdNdKbwoPukm10tS7qFGRFf3e7r4tc3vyXXZg0ZdJjRQVjyXnXq9Z4f5bF5NZTavJsTsPkfTOF12u8/UZW4jOB2AuZBWXE7fccgv8aM6qw7rUz2V0KBbh2nniUthsXgKX0JN9A5zetd1O7/rOoN+7OBlm37sGGTeu8xssl657FSILRS0/bjaoRDLiwM9T1QBHS8bEvdDv8LvIBwDwD9dIfsem+eDz+n/G3cQkmBHQrt1
*/