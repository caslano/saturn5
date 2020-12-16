//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP
#define BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/iterator.hpp>

namespace boost {
namespace container {

template <class PseudoReference>
struct operator_arrow_proxy
{
   operator_arrow_proxy(const PseudoReference &px)
      :  m_value(px)
   {}

   typedef PseudoReference element_type;

   PseudoReference* operator->() const { return &m_value; }

   mutable PseudoReference m_value;
};

template <class T>
struct operator_arrow_proxy<T&>
{
   operator_arrow_proxy(T &px)
      :  m_value(px)
   {}

   typedef T element_type;

   T* operator->() const { return const_cast<T*>(&m_value); }

   T &m_value;
};

template <class Iterator, class UnaryFunction>
class transform_iterator
   : public UnaryFunction
   , public boost::container::iterator
      < typename Iterator::iterator_category
      , typename dtl::remove_reference<typename UnaryFunction::result_type>::type
      , typename Iterator::difference_type
      , operator_arrow_proxy<typename UnaryFunction::result_type>
      , typename UnaryFunction::result_type>
{
   public:
   explicit transform_iterator(const Iterator &it, const UnaryFunction &f = UnaryFunction())
      :  UnaryFunction(f), m_it(it)
   {}

   explicit transform_iterator()
      :  UnaryFunction(), m_it()
   {}

   //Constructors
   transform_iterator& operator++()
   { increment();   return *this;   }

   transform_iterator operator++(int)
   {
      transform_iterator result (*this);
      increment();
      return result;
   }

   friend bool operator== (const transform_iterator& i, const transform_iterator& i2)
   { return i.equal(i2); }

   friend bool operator!= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i == i2); }

/*
   friend bool operator> (const transform_iterator& i, const transform_iterator& i2)
   { return i2 < i; }

   friend bool operator<= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i > i2); }

   friend bool operator>= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i < i2); }
*/
   friend typename Iterator::difference_type operator- (const transform_iterator& i, const transform_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   transform_iterator& operator+=(typename Iterator::difference_type off)
   {  this->advance(off); return *this;   }

   transform_iterator operator+(typename Iterator::difference_type off) const
   {
      transform_iterator other(*this);
      other.advance(off);
      return other;
   }

   friend transform_iterator operator+(typename Iterator::difference_type off, const transform_iterator& right)
   {  return right + off; }

   transform_iterator& operator-=(typename Iterator::difference_type off)
   {  this->advance(-off); return *this;   }

   transform_iterator operator-(typename Iterator::difference_type off) const
   {  return *this + (-off);  }

   typename UnaryFunction::result_type operator*() const
   { return dereference(); }

   operator_arrow_proxy<typename UnaryFunction::result_type>
      operator->() const
   { return operator_arrow_proxy<typename UnaryFunction::result_type>(dereference());  }

   Iterator & base()
   {  return m_it;   }

   const Iterator & base() const
   {  return m_it;   }

   private:
   Iterator m_it;

   void increment()
   { ++m_it; }

   void decrement()
   { --m_it; }

   bool equal(const transform_iterator &other) const
   {  return m_it == other.m_it;   }

   bool less(const transform_iterator &other) const
   {  return other.m_it < m_it;   }

   typename UnaryFunction::result_type dereference() const
   { return UnaryFunction::operator()(*m_it); }

   void advance(typename Iterator::difference_type n)
   {  boost::container::iterator_advance(m_it, n); }

   typename Iterator::difference_type distance_to(const transform_iterator &other)const
   {  return boost::container::iterator_distance(other.m_it, m_it); }
};

template <class Iterator, class UnaryFunc>
transform_iterator<Iterator, UnaryFunc>
make_transform_iterator(Iterator it, UnaryFunc fun)
{
   return transform_iterator<Iterator, UnaryFunc>(it, fun);
}

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP

/* transform_iterator.hpp
Fpfg3rfv3CHf5cMayHzM7nnm1YGwdjKLmflNFKxH2NDU2yfAYiK0XJjFfblwKCxW2Kpvl+yCJZPxnL8PK7Bh6cK6b7noFFgWGR/DId1z34QVkdk8Z39yM6xC5Cz++udeWK3oc8sXi12wVlFv5e0vl8J6hC2IXPsvmHdudC/jZ/31R1gsGe/FvH8eFhJx942qewGWSuZlxtd7JpmHmZlnsIjIaeYZrECYmWewMsd6OaOq2BjGuDNmrX571qmwejIfs993t3fA2oT5j9oegPWKnIu2Hf8szDOP+mQWfq1yFixA5mXG+wyS+ZmZ7RaWqsRlknmYmeUJizjGjQrmMRvrHpEz/L6zr4EVkfmZNf8+biysiszHbPZLEwfCGsksZquWHHIRrI0sltnRb751Ksz11+h6g086uwsWIOM5H901/QZYAhnv5ZWm8y1YKpnNLP+e6UfCIiLnplFf/9/yRS/vFz0zE1Yu6g0bmtECqxNxZv3B2si8zPh66BL2t/g/psD6lDhPVnQv5roKFksWYPbBljP2wVLIbGbmmguW6RjnSi4kwzwb586ew+9RFzML0TxjllNKhmV9Nt1TNX9DgVWR2cxML7AGk5MZP8Y1MRsvjn8tirVxE8e4DsW6yLzMzPsSYH1kNrPApzsvhFnzo614jXUILE6xJMXSySxmvpnHnQfL4ibea1RA5rRcikScWUewctGL+bYxrBaGuIRfhsGaRU5zXQXrIPPC5PvBFHMtcDaLDNvDOeL3ivFkNkw8e5ws7GtPXS0sg8xillS96TFYtojL+erHMKxI2LbPv/0IViFymu9hwmrFGMz3gWAtwiY+v/gGWLdinoXR1nD10MGwWDLe51z3x4/AEsl4n2MXZu2BpZL5mU25/+46WDaZFybWUYHoxdzXgJWLXg7sC+jfwgZ4O9fDmkXOqvknjId1iTH4bv56BqyfzGm++LJZnNge4sl4Lw8PeeRKWDIZz3n58u2/wDJ5TvHsVa6I48/qlTCTy6ya9yJ/M0vmZ1b/7eU7YJ0ibsG/R/4d1i/6fOPSgY/CrJui43Zs++IHWByZU1wiGe/lxLsn/ATLEDmbB+3zwXJFzpOu++g+WBGZ03ypIHNanvXM5PJsEznNb+RhPcJ2pk34EeZZJMZO78KA+cl4vS+eC78OC5HxnD9/P/FzWCqZ0/IMi7hrNt/3ICxfiSsh8zBjz7bMLmNx57nDI8ych1WT+Zg9N3XudFgTmc3spJ5dT8I6RM6impljYb3Cfvh816swT050vVk7zvbAYnOcc4bIeC8/XnhGNyxV5NzoPfERWJbIad43AysQOXdtq74EVgZDzl/XzYfViJxHvxjscWHbZHHni+22nZs4VvVyE8cqby7Vg4ljVSCXxYljVYibOFal8pziWBUm88HEsaqAmzgelStWx00cq1p5n+JY1c37FMcq182074HxYxX9Ni1Ahrgk8bvDBDIfMzPnYalkNjMz52ERkdPMT1i+MDPnYSWinpnzsGolZ4Poxcx5WJvIaeY8rFfkNHMe5rklOqeZ87CAMDPnYSEynvPAnJ+5aBIZzgsucK8e8FbPvJ9gGWQ2szuXF34JyyWzmJlvucKKhJn33sHKyXzMtlbc2w2rE/WWrwq+DWsROWPyCybDOoUNv3F+CqxP1EvfOng+zL41up7ZxmDxZDyn2cZgSWR+Znl/TB4DyxQ5f7/uwSmwPJHzqsyUw2HFZB5m5joHVkrGxzDn0FFv7rdFc2rIsP4udI8cx9//2WByMjM5YU1kNjMzP2EdZD5mZn7C+sksZmZ+wqy86JxmfsLihJn5CUsi4znN/ISlibh5x648DpYlbEfraQFYobAr7lz4KKxc1Ds=
*/