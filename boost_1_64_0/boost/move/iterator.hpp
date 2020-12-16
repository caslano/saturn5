//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_ITERATOR_HPP
#define BOOST_MOVE_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>  //forceinline
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {

//////////////////////////////////////////////////////////////////////////////
//
//                            move_iterator
//
//////////////////////////////////////////////////////////////////////////////

//! Class template move_iterator is an iterator adaptor with the same behavior
//! as the underlying iterator except that its dereference operator implicitly
//! converts the value returned by the underlying iterator's dereference operator
//! to an rvalue reference. Some generic algorithms can be called with move
//! iterators to replace copying with moving.
template <class It>
class move_iterator
{
   public:
   typedef It                                                              iterator_type;
   typedef typename boost::movelib::iterator_traits<iterator_type>::value_type        value_type;
   #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_DOXYGEN_INVOKED)
   typedef value_type &&                                                   reference;
   #else
   typedef typename ::boost::move_detail::if_
      < ::boost::has_move_emulation_enabled<value_type>
      , ::boost::rv<value_type>&
      , value_type & >::type                                               reference;
   #endif
   typedef It                                                              pointer;
   typedef typename boost::movelib::iterator_traits<iterator_type>::difference_type   difference_type;
   typedef typename boost::movelib::iterator_traits<iterator_type>::iterator_category iterator_category;

   BOOST_MOVE_FORCEINLINE move_iterator()
      : m_it()
   {}

   BOOST_MOVE_FORCEINLINE explicit move_iterator(const It &i)
      :  m_it(i)
   {}

   template <class U>
   BOOST_MOVE_FORCEINLINE move_iterator(const move_iterator<U>& u)
      :  m_it(u.m_it)
   {}

   BOOST_MOVE_FORCEINLINE reference operator*() const
   {
      #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)
      return *m_it;
      #else
      return ::boost::move(*m_it);
      #endif
   }

   BOOST_MOVE_FORCEINLINE pointer   operator->() const
   {  return m_it;   }

   BOOST_MOVE_FORCEINLINE move_iterator& operator++()
   {  ++m_it; return *this;   }

   BOOST_MOVE_FORCEINLINE move_iterator<iterator_type>  operator++(int)
   {  move_iterator<iterator_type> tmp(*this); ++(*this); return tmp;   }

   BOOST_MOVE_FORCEINLINE move_iterator& operator--()
   {  --m_it; return *this;   }

   BOOST_MOVE_FORCEINLINE move_iterator<iterator_type>  operator--(int)
   {  move_iterator<iterator_type> tmp(*this); --(*this); return tmp;   }

   move_iterator<iterator_type>  operator+ (difference_type n) const
   {  return move_iterator<iterator_type>(m_it + n);  }

   BOOST_MOVE_FORCEINLINE move_iterator& operator+=(difference_type n)
   {  m_it += n; return *this;   }

   BOOST_MOVE_FORCEINLINE move_iterator<iterator_type>  operator- (difference_type n) const
   {  return move_iterator<iterator_type>(m_it - n);  }

   BOOST_MOVE_FORCEINLINE move_iterator& operator-=(difference_type n)
   {  m_it -= n; return *this;   }

   BOOST_MOVE_FORCEINLINE reference operator[](difference_type n) const
   {
      #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)
      return m_it[n];
      #else
      return ::boost::move(m_it[n]);
      #endif
   }

   BOOST_MOVE_FORCEINLINE friend bool operator==(const move_iterator& x, const move_iterator& y)
   {  return x.m_it == y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend bool operator!=(const move_iterator& x, const move_iterator& y)
   {  return x.m_it != y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend bool operator< (const move_iterator& x, const move_iterator& y)
   {  return x.m_it < y.m_it;   }

   BOOST_MOVE_FORCEINLINE friend bool operator<=(const move_iterator& x, const move_iterator& y)
   {  return x.m_it <= y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend bool operator> (const move_iterator& x, const move_iterator& y)
   {  return x.m_it > y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend bool operator>=(const move_iterator& x, const move_iterator& y)
   {  return x.m_it >= y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend difference_type operator-(const move_iterator& x, const move_iterator& y)
   {  return x.m_it - y.m_it;   }

   BOOST_MOVE_FORCEINLINE friend move_iterator operator+(difference_type n, const move_iterator& x)
   {  return move_iterator(x.m_it + n);   }

   private:
   It m_it;
};

//is_move_iterator
namespace move_detail {

template <class I>
struct is_move_iterator
{
   static const bool value = false;
};

template <class I>
struct is_move_iterator< ::boost::move_iterator<I> >
{
   static const bool value = true;
};

}  //namespace move_detail {

//////////////////////////////////////////////////////////////////////////////
//
//                            move_iterator
//
//////////////////////////////////////////////////////////////////////////////

//!
//! <b>Returns</b>: move_iterator<It>(i).
template<class It>
inline move_iterator<It> make_move_iterator(const It &it)
{  return move_iterator<It>(it); }

//////////////////////////////////////////////////////////////////////////////
//
//                         back_move_insert_iterator
//
//////////////////////////////////////////////////////////////////////////////


//! A move insert iterator that move constructs elements at the
//! back of a container
template <typename C> // C models Container
class back_move_insert_iterator
{
   C* container_m;

   public:
   typedef C                           container_type;
   typedef typename C::value_type      value_type;
   typedef typename C::reference       reference;
   typedef typename C::pointer         pointer;
   typedef typename C::difference_type difference_type;
   typedef std::output_iterator_tag    iterator_category;

   explicit back_move_insert_iterator(C& x) : container_m(&x) { }

   back_move_insert_iterator& operator=(reference x)
   { container_m->push_back(boost::move(x)); return *this; }

   back_move_insert_iterator& operator=(BOOST_RV_REF(value_type) x)
   {  reference rx = x; return this->operator=(rx);  }

   back_move_insert_iterator& operator*()     { return *this; }
   back_move_insert_iterator& operator++()    { return *this; }
   back_move_insert_iterator& operator++(int) { return *this; }
};

//!
//! <b>Returns</b>: back_move_insert_iterator<C>(x).
template <typename C> // C models Container
inline back_move_insert_iterator<C> back_move_inserter(C& x)
{
   return back_move_insert_iterator<C>(x);
}

//////////////////////////////////////////////////////////////////////////////
//
//                         front_move_insert_iterator
//
//////////////////////////////////////////////////////////////////////////////

//! A move insert iterator that move constructs elements int the
//! front of a container
template <typename C> // C models Container
class front_move_insert_iterator
{
   C* container_m;

public:
   typedef C                           container_type;
   typedef typename C::value_type      value_type;
   typedef typename C::reference       reference;
   typedef typename C::pointer         pointer;
   typedef typename C::difference_type difference_type;
   typedef std::output_iterator_tag    iterator_category;

   explicit front_move_insert_iterator(C& x) : container_m(&x) { }

   front_move_insert_iterator& operator=(reference x)
   { container_m->push_front(boost::move(x)); return *this; }

   front_move_insert_iterator& operator=(BOOST_RV_REF(value_type) x)
   {  reference rx = x; return this->operator=(rx);  }

   front_move_insert_iterator& operator*()     { return *this; }
   front_move_insert_iterator& operator++()    { return *this; }
   front_move_insert_iterator& operator++(int) { return *this; }
};

//!
//! <b>Returns</b>: front_move_insert_iterator<C>(x).
template <typename C> // C models Container
inline front_move_insert_iterator<C> front_move_inserter(C& x)
{
   return front_move_insert_iterator<C>(x);
}

//////////////////////////////////////////////////////////////////////////////
//
//                         insert_move_iterator
//
//////////////////////////////////////////////////////////////////////////////
template <typename C> // C models Container
class move_insert_iterator
{
   C* container_m;
   typename C::iterator pos_;

   public:
   typedef C                           container_type;
   typedef typename C::value_type      value_type;
   typedef typename C::reference       reference;
   typedef typename C::pointer         pointer;
   typedef typename C::difference_type difference_type;
   typedef std::output_iterator_tag    iterator_category;

   explicit move_insert_iterator(C& x, typename C::iterator pos)
      : container_m(&x), pos_(pos)
   {}

   move_insert_iterator& operator=(reference x)
   {
      pos_ = container_m->insert(pos_, ::boost::move(x));
      ++pos_;
      return *this;
   }

   move_insert_iterator& operator=(BOOST_RV_REF(value_type) x)
   {  reference rx = x; return this->operator=(rx);  }

   move_insert_iterator& operator*()     { return *this; }
   move_insert_iterator& operator++()    { return *this; }
   move_insert_iterator& operator++(int) { return *this; }
};

//!
//! <b>Returns</b>: move_insert_iterator<C>(x, it).
template <typename C> // C models Container
inline move_insert_iterator<C> move_inserter(C& x, typename C::iterator it)
{
   return move_insert_iterator<C>(x, it);
}

}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_ITERATOR_HPP

/* iterator.hpp
O7GMGUpeqy1r+sV5N45g/BIyAPglZPETPg71Zz8OZpJizIIr0td3JRCDpuB1SnPd8uIulbMPT33+xydtPyVvgAPuq8xuqb1ICVE9NPwVhP/SQeERH037B87yVnwGkrrWqezb70KB2ITTtKMx0JCL5xT5wnMInHY9vfrBb02CG4yLHXtX5l+GNda8kwFIkAFZv1AVMKFFLML0W3GtHPKg6l2hcxFHvPy+Yj7Un/KxxZ7DHlr0TxxIjU/bVT6GIwj+3bzJw20ymb8/dpBfHjQ1sr14PB3cxLyQyx7zvRcZw28Ke1O4YROeIbeq2ntLB/mT9h7oSBlCunE7QabjcDqt+Ytb4ZEFXfQi9Mq2OIaWljUHU2KMcWXb1SCFkrtxLJ5Tw05wec29HNDV/iRitZKRwSTlT6+81ZvHv5b6tC+J+xk21DeL0eTxjetpf9JK2YOp11ft7XW1ugF6NZb51fDmsjTyjq2+FsKGoQk87uvndg1PSvDZan63Lr8b7ig1f08qH0c1IZLyBNs9RibRUo87ZoBkBB+qUDPhicMVAflP9q4FPsriiN8rySU5uAMOiIgQ3mhQUFGBoAIlmirRSyQWHyha1M/TWqt3ikqANKA5wlVsTaWKLdQXig98IVpAsAqo0KJFxRZrpLT9zi/WtI01IpLOf/bxfZcHCWhb+2sP7st3u7Ozu7O7s7uzszM1BMnRtL2cOwfr8dkC7+U14ZJq4h+XU9fWyYLPwdWoazGJks+U4tzyPXQYNJaMkyDthOBzRU1DXLQh5p/HEnwjwdPv2OHB58obSRMxn+JyGQyvMYDlpH77b9M3aKs/jGL5H62MnfrQsjt4MWWrY7caWOLdEZwPw2gwB1Pkj4epihCMx3JfAJsgaplWJvcck7V16SQLJ2ikyvs2I9jZPLi2rtwdEkTe+AGO+nX7qcBQbkl9W+H+tsJbBlqzNHjHsFNEcFrYGOWKhieZbllqOY2OXsF8L+Xi+ntxut1gcRBqB4M5JTvi3amlw9DfyGbLzZoU/th1mFOjmUlMR295Jd7tWG/xuolmXeyAMR73FJZvr5hIixNsd3hdT10GtDZzN0YoOrh6ck9CMscjVZHraKhIjZezaZvgLamj8WI9bo3D7K58m6BchMbM3V7GE+WENlJ3o/nSC1tFu1JdqVPSYaIQbyynRRY658tT3aFV9J1P30b6Dp/69daJ1Pol9xJzjbqN/IewUghJ4+q0buHWqxOiPRqqRJL4WN5HQv8dYgatzfqkl2dJwcBlT3hIW3NKYWfLqxQfN3iY+lRUKKvc9Kbk/I1GFk5PBqMM6AOlNOa0xF9OCdPYxnJDkq87mTQpiMRiO9Vkl2aQLo3RRSEFgJl6n5FyGRljpijgv4a1aPqeTDsBp/zP33wDU+g9KpxSKTqZp9AmmkCiuUksHweI/Ws0B9UVi+Owo1mW4x5iDsRxd0ksLmBhBUbfQ4wFQ/R3WxgLBlYDd/R0LBcASyawlNLbwnJ/dfnHdPPi46qmuXO60DE87R19NBGZVq/gaop5zlcOvo+IQRsxeGnYmFW7L4nNwdiBss9xvCnPpEG9ye2OupPlH7dRdlzZFTcZf0cP6nkhKnDrwq2nyPZQ/BwoPECBKwAY/JUfZPpo0hiDgpYZYUECrNF3bhYk8IKsYBcaE3eBC9awHG6qqPaF8aNRu8oPgkA2IOox+hKm1qmGcOZWPypf0cfphEV8mviz8tP9/wrx55f+6PvG90KdHBKX7+mbNV4M0kY2QtUYO5/WWZg1PvMpmejCRDX1VJIf7xOeW6rqgsoY6cLFHDW1y76oR6ogYj/loE1IH1JbP6VF5BudXZlq/a2P6BynPSsbFYdTf5pBbYY=
*/