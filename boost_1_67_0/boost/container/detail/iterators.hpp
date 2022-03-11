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

template <class T, class Difference = std::ptrdiff_t>
class constant_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, Difference, const T*, const T &>
{
   typedef  constant_iterator<T, Difference> this_type;

   public:
   BOOST_CONTAINER_FORCEINLINE explicit constant_iterator(const T &ref, Difference range_size)
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

   BOOST_CONTAINER_FORCEINLINE friend Difference operator- (const constant_iterator& i, const constant_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   BOOST_CONTAINER_FORCEINLINE constant_iterator& operator+=(Difference off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE constant_iterator operator+(Difference off) const
   {
      constant_iterator other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend constant_iterator operator+(Difference off, const constant_iterator& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE constant_iterator& operator-=(Difference off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE constant_iterator operator-(Difference off) const
   {  return *this + (-off);  }

   BOOST_CONTAINER_FORCEINLINE const T& operator*() const
   { return dereference(); }

   BOOST_CONTAINER_FORCEINLINE const T& operator[] (Difference ) const
   { return dereference(); }

   BOOST_CONTAINER_FORCEINLINE const T* operator->() const
   { return &(dereference()); }

   private:
   const T *   m_ptr;
   Difference  m_num;

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

   BOOST_CONTAINER_FORCEINLINE void advance(Difference n)
   {  m_num -= n; }

   BOOST_CONTAINER_FORCEINLINE Difference distance_to(const this_type &other)const
   {  return m_num - other.m_num;   }
};

template <class T, class Difference>
class value_init_construct_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, Difference, const T*, const T &>
{
   typedef  value_init_construct_iterator<T, Difference> this_type;

   public:
   BOOST_CONTAINER_FORCEINLINE explicit value_init_construct_iterator(Difference range_size)
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

   BOOST_CONTAINER_FORCEINLINE friend Difference operator- (const value_init_construct_iterator& i, const value_init_construct_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator& operator+=(Difference off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator operator+(Difference off) const
   {
      value_init_construct_iterator other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend value_init_construct_iterator operator+(Difference off, const value_init_construct_iterator& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator& operator-=(Difference off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE value_init_construct_iterator operator-(Difference off) const
   {  return *this + (-off);  }

   //This pseudo-iterator's dereference operations have no sense since value is not
   //constructed until ::boost::container::construct_in_place is called.
   //So comment them to catch bad uses
   //const T& operator*() const;
   //const T& operator[](difference_type) const;
   //const T* operator->() const;

   private:
   Difference  m_num;

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

   BOOST_CONTAINER_FORCEINLINE void advance(Difference n)
   {  m_num -= n; }

   BOOST_CONTAINER_FORCEINLINE Difference distance_to(const this_type &other)const
   {  return m_num - other.m_num;   }
};

template <class T, class Difference>
class default_init_construct_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, Difference, const T*, const T &>
{
   typedef  default_init_construct_iterator<T, Difference> this_type;

   public:
   BOOST_CONTAINER_FORCEINLINE explicit default_init_construct_iterator(Difference range_size)
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

   BOOST_CONTAINER_FORCEINLINE friend Difference operator- (const default_init_construct_iterator& i, const default_init_construct_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator& operator+=(Difference off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator operator+(Difference off) const
   {
      default_init_construct_iterator other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend default_init_construct_iterator operator+(Difference off, const default_init_construct_iterator& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator& operator-=(Difference off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE default_init_construct_iterator operator-(Difference off) const
   {  return *this + (-off);  }

   //This pseudo-iterator's dereference operations have no sense since value is not
   //constructed until ::boost::container::construct_in_place is called.
   //So comment them to catch bad uses
   //const T& operator*() const;
   //const T& operator[](difference_type) const;
   //const T* operator->() const;

   private:
   Difference  m_num;

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

   BOOST_CONTAINER_FORCEINLINE void advance(Difference n)
   {  m_num -= n; }

   BOOST_CONTAINER_FORCEINLINE Difference distance_to(const this_type &other) const
   {  return m_num - other.m_num;   }
};


template <class T, class Difference = std::ptrdiff_t>
class repeat_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, Difference, T*, T&>
{
   typedef repeat_iterator<T, Difference> this_type;
   public:
   BOOST_CONTAINER_FORCEINLINE explicit repeat_iterator(T &ref, Difference range_size)
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

   BOOST_CONTAINER_FORCEINLINE friend Difference operator- (const this_type& i, const this_type& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   BOOST_CONTAINER_FORCEINLINE this_type& operator+=(Difference off)
   {  this->advance(off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator+(Difference off) const
   {
      this_type other(*this);
      other.advance(off);
      return other;
   }

   BOOST_CONTAINER_FORCEINLINE friend this_type operator+(Difference off, const this_type& right)
   {  return right + off; }

   BOOST_CONTAINER_FORCEINLINE this_type& operator-=(Difference off)
   {  this->advance(-off); return *this;   }

   BOOST_CONTAINER_FORCEINLINE this_type operator-(Difference off) const
   {  return *this + (-off);  }

   BOOST_CONTAINER_FORCEINLINE T& operator*() const
   { return dereference(); }

   BOOST_CONTAINER_FORCEINLINE T& operator[] (Difference ) const
   { return dereference(); }

   BOOST_CONTAINER_FORCEINLINE T *operator->() const
   { return &(dereference()); }

   private:
   T *         m_ptr;
   Difference  m_num;

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

   BOOST_CONTAINER_FORCEINLINE void advance(Difference n)
   {  m_num -= n; }

   BOOST_CONTAINER_FORCEINLINE Difference distance_to(const this_type &other)const
   {  return m_num - other.m_num;   }
};

template <class T, class EmplaceFunctor, class Difference /*= std::ptrdiff_t*/>
class emplace_iterator
  : public ::boost::container::iterator
      <std::random_access_iterator_tag, T, Difference, const T*, const T &>
{
   typedef emplace_iterator this_type;

   public:
   typedef Difference difference_type;
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
   difference_type m_num;
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