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

#ifndef BOOST_CONTAINER_DETAIL_ITERATORS_HPP
#define BOOST_CONTAINER_DETAIL_ITERATORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/value_init.hpp>
#include <boost/static_assert.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/intrusive/detail/reverse_iterator.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#else
#include <boost/container/detail/variadic_templates_tools.hpp>
#endif
#include <boost/container/detail/iterator.hpp>

namespace boost {
namespace container {

template <class T>
class constant_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, std::ptrdiff_t, const T*, const T &>
{
   typedef  constant_iterator<T> this_type;

   public:
   BOOST_CONTAINER_FORCEINLINE explicit constant_iterator(const T &ref, std::size_t range_size)
      :  m_ptr(&ref), m_num(range_size){}

   //Constructors
   BOOST_CONTAINER_FORCEINLINE constant_iterator()
      :  m_ptr(0), m_num(0){}

   BOOST_CONTAINER_FORCEINLINE constant_iterator& operator++()
   { increment();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE constant_iterator operator++(int)
   {
      constant_iterator result (*this);
      increment();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE constant_iterator& operator--()
   { decrement();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE constant_iterator operator--(int)
   {
      constant_iterator result (*this);
      decrement();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator== (const constant_iterator& i, const constant_iterator& i2)
   { return i.equal(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!= (const constant_iterator& i, const constant_iterator& i2)
   { return !(i == i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator< (const constant_iterator& i, const constant_iterator& i2)
   { return i.less(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator> (const constant_iterator& i, const constant_iterator& i2)
   { return i2 < i; }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<= (const constant_iterator& i, const constant_iterator& i2)
   { return !(i > i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>= (const constant_iterator& i, const constant_iterator& i2)
   { return !(i < i2); }

   BOOST_CONTAINER_FORCEINLINE friend std::ptrdiff_t operator- (const constant_iterator& i, const constant_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic signed
   BOOST_CONTAINER_FORCEINLINE constant_iterator& operator+=(std::ptrdiff_t off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE constant_iterator operator+(std::ptrdiff_t off) const
   {
      constant_iterator other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend constant_iterator operator+(std::ptrdiff_t off, const constant_iterator& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE constant_iterator& operator-=(std::ptrdiff_t off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE constant_iterator operator-(std::ptrdiff_t off) const
   {  return *this + (-off);  }

   BOOST_CONTAINER_FORCEINLINE const T& operator[] (std::ptrdiff_t ) const
   { return dereference(); }

   BOOST_CONTAINER_FORCEINLINE const T& operator*() const
   { return dereference(); }

   BOOST_CONTAINER_FORCEINLINE const T* operator->() const
   { return &(dereference()); }

   //Arithmetic unsigned
   BOOST_CONTAINER_FORCEINLINE constant_iterator& operator+=(std::size_t off)
   {  return *this += std::ptrdiff_t(off);  }

   BOOST_CONTAINER_FORCEINLINE constant_iterator operator+(std::size_t off) const
   {  return *this + std::ptrdiff_t(off);  }

   BOOST_CONTAINER_FORCEINLINE friend constant_iterator operator+(std::size_t off, const constant_iterator& right)
   {  return std::ptrdiff_t(off) + right;  }

   BOOST_CONTAINER_FORCEINLINE constant_iterator& operator-=(std::size_t off)
   {  return *this -= std::ptrdiff_t(off);  }

   BOOST_CONTAINER_FORCEINLINE constant_iterator operator-(std::size_t off) const
   {  return *this - std::ptrdiff_t(off);  }

   BOOST_CONTAINER_FORCEINLINE const T& operator[] (std::size_t off) const
   { return (*this)[std::ptrdiff_t(off)]; }

   private:
   const T *   m_ptr;
   std::size_t m_num;

   BOOST_CONTAINER_FORCEINLINE void increment()
   { --m_num; }

   BOOST_CONTAINER_FORCEINLINE void decrement()
   { ++m_num; }

   BOOST_CONTAINER_FORCEINLINE bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }

   BOOST_CONTAINER_FORCEINLINE bool less(const this_type &other) const
   {  return other.m_num < m_num;   }

   BOOST_CONTAINER_FORCEINLINE const T & dereference() const
   { return *m_ptr; }

   BOOST_CONTAINER_FORCEINLINE void advance(std::ptrdiff_t n)
   {  m_num = std::size_t(std::ptrdiff_t(m_num) - n); }

   BOOST_CONTAINER_FORCEINLINE std::ptrdiff_t distance_to(const this_type &other)const
   {  return std::ptrdiff_t(m_num - other.m_num);   }
};

template <class T>
class value_init_construct_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, std::ptrdiff_t, const T*, const T &>
{
   typedef  value_init_construct_iterator<T> this_type;

   public:
   BOOST_CONTAINER_FORCEINLINE explicit value_init_construct_iterator(std::size_t range_size)
      :  m_num(range_size){}

   //Constructors
   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator()
      :  m_num(0){}

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator& operator++()
   { increment();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator operator++(int)
   {
      value_init_construct_iterator result (*this);
      increment();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator& operator--()
   { decrement();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator operator--(int)
   {
      value_init_construct_iterator result (*this);
      decrement();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator== (const value_init_construct_iterator& i, const value_init_construct_iterator& i2)
   { return i.equal(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!= (const value_init_construct_iterator& i, const value_init_construct_iterator& i2)
   { return !(i == i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator< (const value_init_construct_iterator& i, const value_init_construct_iterator& i2)
   { return i.less(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator> (const value_init_construct_iterator& i, const value_init_construct_iterator& i2)
   { return i2 < i; }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<= (const value_init_construct_iterator& i, const value_init_construct_iterator& i2)
   { return !(i > i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>= (const value_init_construct_iterator& i, const value_init_construct_iterator& i2)
   { return !(i < i2); }

   BOOST_CONTAINER_FORCEINLINE friend std::ptrdiff_t operator- (const value_init_construct_iterator& i, const value_init_construct_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator& operator+=(std::ptrdiff_t off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator operator+(std::ptrdiff_t off) const
   {
      value_init_construct_iterator other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend value_init_construct_iterator operator+(std::ptrdiff_t off, const value_init_construct_iterator& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator& operator-=(std::ptrdiff_t off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator operator-(std::ptrdiff_t off) const
   {  return *this + (-off);  }

   //This pseudo-iterator's dereference operations have no sense since value is not
   //constructed until ::boost::container::construct_in_place is called.
   //So comment them to catch bad uses
   //const T& operator*() const;
   //const T& operator[](difference_type) const;
   //const T* operator->() const;

   private:
   std::size_t  m_num;

   BOOST_CONTAINER_FORCEINLINE void increment()
   { --m_num; }

   BOOST_CONTAINER_FORCEINLINE void decrement()
   { ++m_num; }

   BOOST_CONTAINER_FORCEINLINE bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }

   BOOST_CONTAINER_FORCEINLINE bool less(const this_type &other) const
   {  return other.m_num < m_num;   }

   BOOST_CONTAINER_FORCEINLINE const T & dereference() const
   {
      static T dummy;
      return dummy;
   }

   BOOST_CONTAINER_FORCEINLINE void advance(std::ptrdiff_t n)
   {  m_num = std::size_t(std::ptrdiff_t(m_num) - n); }

   BOOST_CONTAINER_FORCEINLINE std::ptrdiff_t distance_to(const this_type &other)const
   {  return std::ptrdiff_t(m_num - other.m_num);   }
};

template <class T>
class default_init_construct_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, std::ptrdiff_t, const T*, const T &>
{
   typedef  default_init_construct_iterator<T> this_type;

   public:
   BOOST_CONTAINER_FORCEINLINE explicit default_init_construct_iterator(std::size_t range_size)
      :  m_num(range_size){}

   //Constructors
   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator()
      :  m_num(0){}

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator& operator++()
   { increment();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator operator++(int)
   {
      default_init_construct_iterator result (*this);
      increment();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator& operator--()
   { decrement();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator operator--(int)
   {
      default_init_construct_iterator result (*this);
      decrement();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator== (const default_init_construct_iterator& i, const default_init_construct_iterator& i2)
   { return i.equal(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!= (const default_init_construct_iterator& i, const default_init_construct_iterator& i2)
   { return !(i == i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator< (const default_init_construct_iterator& i, const default_init_construct_iterator& i2)
   { return i.less(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator> (const default_init_construct_iterator& i, const default_init_construct_iterator& i2)
   { return i2 < i; }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<= (const default_init_construct_iterator& i, const default_init_construct_iterator& i2)
   { return !(i > i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>= (const default_init_construct_iterator& i, const default_init_construct_iterator& i2)
   { return !(i < i2); }

   BOOST_CONTAINER_FORCEINLINE friend std::ptrdiff_t operator- (const default_init_construct_iterator& i, const default_init_construct_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator& operator+=(std::ptrdiff_t off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator operator+(std::ptrdiff_t off) const
   {
      default_init_construct_iterator other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend default_init_construct_iterator operator+(std::ptrdiff_t off, const default_init_construct_iterator& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator& operator-=(std::ptrdiff_t off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator operator-(std::ptrdiff_t off) const
   {  return *this + (-off);  }

   //This pseudo-iterator's dereference operations have no sense since value is not
   //constructed until ::boost::container::construct_in_place is called.
   //So comment them to catch bad uses
   //const T& operator*() const;
   //const T& operator[](difference_type) const;
   //const T* operator->() const;

   private:
   std::size_t  m_num;

   BOOST_CONTAINER_FORCEINLINE void increment()
   { --m_num; }

   BOOST_CONTAINER_FORCEINLINE void decrement()
   { ++m_num; }

   BOOST_CONTAINER_FORCEINLINE bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }

   BOOST_CONTAINER_FORCEINLINE bool less(const this_type &other) const
   {  return other.m_num < m_num;   }

   BOOST_CONTAINER_FORCEINLINE const T & dereference() const
   {
      static T dummy;
      return dummy;
   }

   BOOST_CONTAINER_FORCEINLINE void advance(std::ptrdiff_t n)
   {  m_num = std::size_t(std::ptrdiff_t(m_num) - n); }

   BOOST_CONTAINER_FORCEINLINE std::ptrdiff_t distance_to(const this_type &other) const
   {  return std::ptrdiff_t(m_num - other.m_num);   }
};


template <class T>
class repeat_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, std::ptrdiff_t, T*, T&>
{
   typedef repeat_iterator<T> this_type;
   public:
   BOOST_CONTAINER_FORCEINLINE explicit repeat_iterator(T &ref, std::size_t range_size)
      :  m_ptr(&ref), m_num(range_size){}

   //Constructors
   BOOST_CONTAINER_FORCEINLINE repeat_iterator()
      :  m_ptr(0), m_num(0){}

   BOOST_CONTAINER_FORCEINLINE this_type& operator++()
   { increment();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator++(int)
   {
      this_type result (*this);
      increment();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE this_type& operator--()
   { increment();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator--(int)
   {
      this_type result (*this);
      increment();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator== (const this_type& i, const this_type& i2)
   { return i.equal(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!= (const this_type& i, const this_type& i2)
   { return !(i == i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator< (const this_type& i, const this_type& i2)
   { return i.less(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator> (const this_type& i, const this_type& i2)
   { return i2 < i; }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<= (const this_type& i, const this_type& i2)
   { return !(i > i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>= (const this_type& i, const this_type& i2)
   { return !(i < i2); }

   BOOST_CONTAINER_FORCEINLINE friend std::ptrdiff_t operator- (const this_type& i, const this_type& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   BOOST_CONTAINER_FORCEINLINE this_type& operator+=(std::ptrdiff_t off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator+(std::ptrdiff_t off) const
   {
      this_type other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend this_type operator+(std::ptrdiff_t off, const this_type& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE this_type& operator-=(std::ptrdiff_t off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator-(std::ptrdiff_t off) const
   {  return *this + (-off);  }

   BOOST_CONTAINER_FORCEINLINE T& operator*() const
   { return dereference(); }

   BOOST_CONTAINER_FORCEINLINE T& operator[] (std::ptrdiff_t ) const
   { return dereference(); }

   BOOST_CONTAINER_FORCEINLINE T *operator->() const
   { return &(dereference()); }

   private:
   T *         m_ptr;
   std::size_t m_num;

   BOOST_CONTAINER_FORCEINLINE void increment()
   { --m_num; }

   BOOST_CONTAINER_FORCEINLINE void decrement()
   { ++m_num; }

   BOOST_CONTAINER_FORCEINLINE bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }

   BOOST_CONTAINER_FORCEINLINE bool less(const this_type &other) const
   {  return other.m_num < m_num;   }

   BOOST_CONTAINER_FORCEINLINE T & dereference() const
   { return *m_ptr; }

   BOOST_CONTAINER_FORCEINLINE void advance(std::ptrdiff_t n)
   {  m_num = std::size_t(std::ptrdiff_t(m_num - n)); }

   BOOST_CONTAINER_FORCEINLINE std::ptrdiff_t distance_to(const this_type &other)const
   {  return std::ptrdiff_t(m_num - other.m_num);   }
};

template <class T, class EmplaceFunctor>
class emplace_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, std::ptrdiff_t, const T*, const T &>
{
   typedef emplace_iterator this_type;

   public:
   typedef std::ptrdiff_t difference_type;
   BOOST_CONTAINER_FORCEINLINE explicit emplace_iterator(EmplaceFunctor&e)
      :  m_num(1), m_pe(&e){}

   BOOST_CONTAINER_FORCEINLINE emplace_iterator()
      :  m_num(0), m_pe(0){}

   BOOST_CONTAINER_FORCEINLINE this_type& operator++()
   { increment();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator++(int)
   {
      this_type result (*this);
      increment();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE this_type& operator--()
   { decrement();   return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator--(int)
   {
      this_type result (*this);
      decrement();
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator== (const this_type& i, const this_type& i2)
   { return i.equal(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!= (const this_type& i, const this_type& i2)
   { return !(i == i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator< (const this_type& i, const this_type& i2)
   { return i.less(i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator> (const this_type& i, const this_type& i2)
   { return i2 < i; }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<= (const this_type& i, const this_type& i2)
   { return !(i > i2); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>= (const this_type& i, const this_type& i2)
   { return !(i < i2); }

   BOOST_CONTAINER_FORCEINLINE friend difference_type operator- (const this_type& i, const this_type& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   BOOST_CONTAINER_FORCEINLINE this_type& operator+=(difference_type off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator+(difference_type off) const
   {
      this_type other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend this_type operator+(difference_type off, const this_type& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE this_type& operator-=(difference_type off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator-(difference_type off) const
   {  return *this + (-off);  }

   private:
   //This pseudo-iterator's dereference operations have no sense since value is not
   //constructed until ::boost::container::construct_in_place is called.
   //So comment them to catch bad uses
   const T& operator*() const;
   const T& operator[](difference_type) const;
   const T* operator->() const;

   public:
   template<class Allocator>
   BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T* ptr)
   {  (*m_pe)(a, ptr);  }

   template<class DestIt>
   BOOST_CONTAINER_FORCEINLINE void assign_in_place(DestIt dest)
   {  (*m_pe)(dest);  }

   private:
   std::size_t m_num;
   EmplaceFunctor *            m_pe;

   BOOST_CONTAINER_FORCEINLINE void increment()
   { --m_num; }

   BOOST_CONTAINER_FORCEINLINE void decrement()
   { ++m_num; }

   BOOST_CONTAINER_FORCEINLINE bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }

   BOOST_CONTAINER_FORCEINLINE bool less(const this_type &other) const
   {  return other.m_num < m_num;   }

   BOOST_CONTAINER_FORCEINLINE const T & dereference() const
   {
      static T dummy;
      return dummy;
   }

   BOOST_CONTAINER_FORCEINLINE void advance(difference_type n)
   {  m_num -= n; }

   BOOST_CONTAINER_FORCEINLINE difference_type distance_to(const this_type &other)const
   {  return difference_type(m_num - other.m_num);   }
};

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<class ...Args>
struct emplace_functor
{
   typedef typename dtl::build_number_seq<sizeof...(Args)>::type index_tuple_t;

   BOOST_CONTAINER_FORCEINLINE emplace_functor(BOOST_FWD_REF(Args)... args)
      : args_(args...)
   {}

   template<class Allocator, class T>
   BOOST_CONTAINER_FORCEINLINE void operator()(Allocator &a, T *ptr)
   {  emplace_functor::inplace_impl(a, ptr, index_tuple_t());  }

   template<class DestIt>
   BOOST_CONTAINER_FORCEINLINE void operator()(DestIt dest)
   {  emplace_functor::inplace_impl(dest, index_tuple_t());  }

   private:
   template<class Allocator, class T, std::size_t ...IdxPack>
   BOOST_CONTAINER_FORCEINLINE void inplace_impl(Allocator &a, T* ptr, const dtl::index_tuple<IdxPack...>&)
   {
      allocator_traits<Allocator>::construct
         (a, ptr, ::boost::forward<Args>(dtl::get<IdxPack>(args_))...);
   }

   template<class DestIt, std::size_t ...IdxPack>
   BOOST_CONTAINER_FORCEINLINE void inplace_impl(DestIt dest, const dtl::index_tuple<IdxPack...>&)
   {
      typedef typename boost::container::iterator_traits<DestIt>::value_type value_type;
      value_type && tmp= value_type(::boost::forward<Args>(dtl::get<IdxPack>(args_))...);
      *dest = ::boost::move(tmp);
   }

   dtl::tuple<Args&...> args_;
};

template<class ...Args>
struct emplace_functor_type
{
   typedef emplace_functor<Args...> type;
};

#else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

//Partial specializations cannot match argument list for primary template, so add an extra argument
template <BOOST_MOVE_CLASSDFLT9, class Dummy = void>
struct emplace_functor_type;

#define BOOST_MOVE_ITERATOR_EMPLACE_FUNCTOR_CODE(N) \
BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
struct emplace_functor##N\
{\
   BOOST_CONTAINER_FORCEINLINE explicit emplace_functor##N( BOOST_MOVE_UREF##N )\
      BOOST_MOVE_COLON##N BOOST_MOVE_FWD_INIT##N{}\
   \
   template<class Allocator, class T>\
   BOOST_CONTAINER_FORCEINLINE void operator()(Allocator &a, T *ptr)\
   {  allocator_traits<Allocator>::construct(a, ptr BOOST_MOVE_I##N BOOST_MOVE_MFWD##N);  }\
   \
   template<class DestIt>\
   BOOST_CONTAINER_FORCEINLINE void operator()(DestIt dest)\
   {\
      typedef typename boost::container::iterator_traits<DestIt>::value_type value_type;\
      BOOST_MOVE_IF(N, value_type tmp(BOOST_MOVE_MFWD##N), dtl::value_init<value_type> tmp) ;\
      *dest = ::boost::move(const_cast<value_type &>(BOOST_MOVE_IF(N, tmp, tmp.get())));\
   }\
   \
   BOOST_MOVE_MREF##N\
};\
\
template <BOOST_MOVE_CLASS##N>\
struct emplace_functor_type<BOOST_MOVE_TARG##N>\
{\
   typedef emplace_functor##N BOOST_MOVE_LT##N BOOST_MOVE_TARG##N BOOST_MOVE_GT##N type;\
};\
//

BOOST_MOVE_ITERATE_0TO9(BOOST_MOVE_ITERATOR_EMPLACE_FUNCTOR_CODE)

#undef BOOST_MOVE_ITERATOR_EMPLACE_FUNCTOR_CODE

#endif

namespace dtl {

template<class T>
struct has_iterator_category
{
   struct two { char _[2]; };

   template <typename X>
   static char test(int, typename X::iterator_category*);

   template <typename X>
   static two test(int, ...);

   static const bool value = (1 == sizeof(test<T>(0, 0)));
};


template<class T, bool = has_iterator_category<T>::value >
struct is_input_iterator
{
   static const bool value = is_same<typename T::iterator_category, std::input_iterator_tag>::value;
};

template<class T>
struct is_input_iterator<T, false>
{
   static const bool value = false;
};

template<class T>
struct is_not_input_iterator
{
   static const bool value = !is_input_iterator<T>::value;
};

template<class T, bool = has_iterator_category<T>::value >
struct is_forward_iterator
{
   static const bool value = is_same<typename T::iterator_category, std::forward_iterator_tag>::value;
};

template<class T>
struct is_forward_iterator<T, false>
{
   static const bool value = false;
};

template<class T, bool = has_iterator_category<T>::value >
struct is_bidirectional_iterator
{
   static const bool value = is_same<typename T::iterator_category, std::bidirectional_iterator_tag>::value;
};

template<class T>
struct is_bidirectional_iterator<T, false>
{
   static const bool value = false;
};

template<class IINodeType>
struct iiterator_node_value_type {
  typedef typename IINodeType::value_type type;
};

template<class IIterator>
struct iiterator_types
{
   typedef typename IIterator::value_type                            it_value_type;
   typedef typename iiterator_node_value_type<it_value_type>::type   value_type;
   typedef typename boost::container::iterator_traits<IIterator>::pointer         it_pointer;
   typedef typename boost::container::iterator_traits<IIterator>::difference_type difference_type;
   typedef typename ::boost::intrusive::pointer_traits<it_pointer>::
      template rebind_pointer<value_type>::type                      pointer;
   typedef typename ::boost::intrusive::pointer_traits<it_pointer>::
      template rebind_pointer<const value_type>::type                const_pointer;
   typedef typename ::boost::intrusive::
      pointer_traits<pointer>::reference                             reference;
   typedef typename ::boost::intrusive::
      pointer_traits<const_pointer>::reference                       const_reference;
   typedef typename IIterator::iterator_category                     iterator_category;
};

template<class IIterator, bool IsConst>
struct iterator_types
{
   typedef typename ::boost::container::iterator
      < typename iiterator_types<IIterator>::iterator_category
      , typename iiterator_types<IIterator>::value_type
      , typename iiterator_types<IIterator>::difference_type
      , typename iiterator_types<IIterator>::const_pointer
      , typename iiterator_types<IIterator>::const_reference> type;
};

template<class IIterator>
struct iterator_types<IIterator, false>
{
   typedef typename ::boost::container::iterator
      < typename iiterator_types<IIterator>::iterator_category
      , typename iiterator_types<IIterator>::value_type
      , typename iiterator_types<IIterator>::difference_type
      , typename iiterator_types<IIterator>::pointer
      , typename iiterator_types<IIterator>::reference> type;
};

template<class IIterator, bool IsConst>
class iterator_from_iiterator
{
   typedef typename iterator_types<IIterator, IsConst>::type   types_t;
   class nat
   {
      public:
      IIterator get() const
      {  return IIterator(); }
   };
   typedef typename dtl::if_c< IsConst
                             , iterator_from_iiterator<IIterator, false>
                             , nat>::type                      nonconst_iterator;

   public:
   typedef typename types_t::pointer             pointer;
   typedef typename types_t::reference           reference;
   typedef typename types_t::difference_type     difference_type;
   typedef typename types_t::iterator_category   iterator_category;
   typedef typename types_t::value_type          value_type;

   BOOST_CONTAINER_FORCEINLINE iterator_from_iiterator()
      : m_iit()
   {}

   BOOST_CONTAINER_FORCEINLINE explicit iterator_from_iiterator(IIterator iit) BOOST_NOEXCEPT_OR_NOTHROW
      : m_iit(iit)
   {}

   BOOST_CONTAINER_FORCEINLINE iterator_from_iiterator(const iterator_from_iiterator& other) BOOST_NOEXCEPT_OR_NOTHROW
      :  m_iit(other.get())
   {}

   BOOST_CONTAINER_FORCEINLINE iterator_from_iiterator(const nonconst_iterator& other) BOOST_NOEXCEPT_OR_NOTHROW
      :  m_iit(other.get())
   {}

   BOOST_CONTAINER_FORCEINLINE iterator_from_iiterator& operator=(const iterator_from_iiterator& other) BOOST_NOEXCEPT_OR_NOTHROW
   {  m_iit = other.get(); return *this;  }

   BOOST_CONTAINER_FORCEINLINE iterator_from_iiterator& operator++() BOOST_NOEXCEPT_OR_NOTHROW
   {  ++this->m_iit;   return *this;  }

   BOOST_CONTAINER_FORCEINLINE iterator_from_iiterator operator++(int) BOOST_NOEXCEPT_OR_NOTHROW
   {
      iterator_from_iiterator result (*this);
      ++this->m_iit;
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE iterator_from_iiterator& operator--() BOOST_NOEXCEPT_OR_NOTHROW
   {
      //If the iterator_from_iiterator is not a bidirectional iterator, operator-- should not exist
      BOOST_STATIC_ASSERT((is_bidirectional_iterator<iterator_from_iiterator>::value));
      --this->m_iit;   return *this;
   }

   BOOST_CONTAINER_FORCEINLINE iterator_from_iiterator operator--(int) BOOST_NOEXCEPT_OR_NOTHROW
   {
      iterator_from_iiterator result (*this);
      --this->m_iit;
      return result;
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator== (const iterator_from_iiterator& l, const iterator_from_iiterator& r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return l.m_iit == r.m_iit;   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!= (const iterator_from_iiterator& l, const iterator_from_iiterator& r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return !(l == r); }

   BOOST_CONTAINER_FORCEINLINE reference operator*()  const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->m_iit->get_data();  }

   BOOST_CONTAINER_FORCEINLINE pointer   operator->() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return ::boost::intrusive::pointer_traits<pointer>::pointer_to(this->operator*());  }

   BOOST_CONTAINER_FORCEINLINE const IIterator &get() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->m_iit;   }

   private:
   IIterator m_iit;
};

}  //namespace dtl {

using ::boost::intrusive::reverse_iterator;

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ITERATORS_HPP

/* iterators.hpp
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
*/