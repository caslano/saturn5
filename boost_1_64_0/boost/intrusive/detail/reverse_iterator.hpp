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
pjussD+Buu2yqV1v89pGj19u04f9XSNtZ8YJszj81vKqLYnV27yuTW+zbB2POHRsi44Fbh2ZvJ7Efes0dfTq4BL5FligOnghoR06FkbryAAh3378kZZ137vQxC8M9LLue/dqDbPzE5jrb9ttZZr/3ZK96gdGp5poneyx1ZbdwnV71Mj9JvCq25cE6dr3M/lZqaKseq6qNccHu9v/rvbzQ4S/G8mndTN+F6LnIDnlLf9Akh9q5Ddgw7nOuUlKQ+tUhV9rFYTKaNpxOEeJtXlzuiV2rzH3a2PDyDluvm3M/nSzP7aPoj0d9D1fdXMpoSP1oLabqx6YZ/WEn2FII2L9eyPu+yh60xzPij7nlqxZ953CFXTw2sKWaS0QjmwPPb8Xs7MSu6+7bWuv+WV0NbaaJ1vtk3+ArkooV+ukF3d322pDBQukV24uX7M+NDBtRdn6teu3VCVoO9L06+xWc278hPz1lUtNnGyX/ZBvetvl3VfJl31+vmHvDI90Ur+F6k2Rnmkq3bYoK780ueca0tH5955rwpJwllkyahvNPZFnjsTqQ+jau617/Guvm/28Ea5PuJ+R9MgxlgRsc9xtG+YOlm8yNWTNaufzRwZ8vnvs9fNJ17/Ofm9kSSiGjey4LVL9NdGd7ebx06hD3rX0+/p9q23fEuSrdafD7dY3I9puWditzm03rZpp0o5pt1Nx7FZn2eJXjditLgm71Z0Bu/0qCbsVy2ALdS2WEnJC7xc93HYzixZqcctYz7sXGNlcl91I1712pX0/zTZx5tOvFYy2p5WGt+7nm3qOeYpQkNn4vTJmu+VYm9GeIz9BHWNmI6SH3mer49qKppsn20Tve9U9En+3re5x+nXFfu+060URmZjrSvWiDyGXfwfilvXy8kTb6ANWOZeaeiBZ3d8fNsfbOsuNrO2vyrzDbM5svJ2OZwd0YB86RNhhiebMf13pPUPoFmqPnXawHZMlZgfSiXi+rE8iZhts2a1zur82tb++9N/M8XXuNlmy9rqs9lrNJ8zxQ9bcjK1bLh1r/ET5z8o/UJyw72vWtf8Tc/yR+rXByfggCU8kpKVdFv3+rzjHOD7JfG+5JOr9vz/bZt5aTv1zcWlm/ffPyZZftxLv3Cew/nLM73Syu91mYl+t1RzeDtRpHv0IXRvDvTpxVmN1YkXIzWLM96AXjPzgQD/3exDpJ1lXznLWFXfdOCtW3dDztjneMvq86/iL5nhr/5q8jJ1Tchr/nnomzos/z7xb9DNAXuhe1jP6vGi+E08Ase//WT1j3/9J07fX6/Hv/8RN/P6f3vP02/TXE7j/++9wms+9PMh+uAzmY7OCcJut2Vy+Cn9crCFfWbGpqtxts1w42sgtDLpsRpp+/d1o6iOffVasXl/htpsdX98b9cxs1btvhOKwZbb59bbZzjYyS0w9tXXWt5Be9fOmQuvED6DOzGRQ1lTqavuU9oNapaS1bh3QOvI6fpTjRRxvUX2y/RQipHcMRNbzmNfNKJNXJ1+/eWY7I+Z11M0cby2/XSZ/M/hzWqh9bLGrd/t27ae1nx/SMqNh/iXHZshnY0jO+84wU23kLBjScbZ4AWEOYS5hHmG+4s1IYG5dvOuVc8o+nVPdR2erX2+J5pUPo34NgD3gsNDzeS+7npnrcm35ptLQpfme9VvWNbwCI6P7EvFXVW0abq5fPTOSXl4onT8z1yHdeb2Sj38NZnjfkFz1zhl3K5Gd1ytxY75r+316HY1urYK/px64vg+Rhv++WtAnwJ9MwK1js3R8jf63dhyvVF+jV5c3mLRnmvzr2z3TrPn6vqz+yBEm3S0bA1b7NsLIjq7f5tcrZjvXfDfZS51b1jPUH0k5248=
*/