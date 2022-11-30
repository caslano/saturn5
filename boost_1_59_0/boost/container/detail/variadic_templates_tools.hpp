//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_VARIADIC_TEMPLATES_TOOLS_HPP
#define BOOST_CONTAINER_DETAIL_VARIADIC_TEMPLATES_TOOLS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/move/utility_core.hpp>

#include <boost/container/detail/type_traits.hpp>
#include <cstddef>   //std::size_t

namespace boost {
namespace container {
namespace dtl {

template<typename... Values>
class tuple;

template<> class tuple<>
{};

template<typename Head, typename... Tail>
class tuple<Head, Tail...>
   : private tuple<Tail...>
{
   typedef tuple<Tail...> inherited;

   public:
   tuple()
      : inherited(), m_head()
   {}

   template<class U, class ...Args>
   tuple(U &&u, Args && ...args)
      : inherited(::boost::forward<Args>(args)...), m_head(::boost::forward<U>(u))
   {}

   // Construct tuple from another tuple.
   template<typename... VValues>
   tuple(const tuple<VValues...>& other)
      : inherited(other.tail()), m_head(other.head())
   {}

   template<typename... VValues>
   tuple& operator=(const tuple<VValues...>& other)
   {
      m_head = other.head();
      tail() = other.tail();
      return this;
   }

   typename add_reference<Head>::type head()             {  return m_head; }
   typename add_reference<const Head>::type head() const {  return m_head; }

   inherited& tail()             { return *this; }
   const inherited& tail() const { return *this; }

   protected:
   Head m_head;
};


template<typename... Values>
tuple<Values&&...> forward_as_tuple_impl(Values&&... values)
{ return tuple<Values&&...>(::boost::forward<Values>(values)...); }

template<int I, typename Tuple>
struct tuple_element;

template<int I, typename Head, typename... Tail>
struct tuple_element<I, tuple<Head, Tail...> >
{
   typedef typename tuple_element<I-1, tuple<Tail...> >::type type;
};

template<typename Head, typename... Tail>
struct tuple_element<0, tuple<Head, Tail...> >
{
   typedef Head type;
};

template<int I, typename Tuple>
class get_impl;

template<int I, typename Head, typename... Values>
class get_impl<I, tuple<Head, Values...> >
{
   typedef typename tuple_element<I-1, tuple<Values...> >::type   Element;
   typedef get_impl<I-1, tuple<Values...> >                       Next;

   public:
   typedef typename add_reference<Element>::type                  type;
   typedef typename add_const_reference<Element>::type            const_type;
   static type get(tuple<Head, Values...>& t)              { return Next::get(t.tail()); }
   static const_type get(const tuple<Head, Values...>& t)  { return Next::get(t.tail()); }
};

template<typename Head, typename... Values>
class get_impl<0, tuple<Head, Values...> >
{
   public:
   typedef typename add_reference<Head>::type         type;
   typedef typename add_const_reference<Head>::type   const_type;
   static type       get(tuple<Head, Values...>& t)      { return t.head(); }
   static const_type get(const tuple<Head, Values...>& t){ return t.head(); }
};

template<int I, typename... Values>
typename get_impl<I, tuple<Values...> >::type get(tuple<Values...>& t)
{  return get_impl<I, tuple<Values...> >::get(t);  }

template<int I, typename... Values>
typename get_impl<I, tuple<Values...> >::const_type get(const tuple<Values...>& t)
{  return get_impl<I, tuple<Values...> >::get(t);  }

////////////////////////////////////////////////////
// Builds an index_tuple<0, 1, 2, ..., Num-1>, that will
// be used to "unpack" into comma-separated values
// in a function call.
////////////////////////////////////////////////////

template<std::size_t...> struct index_tuple{ typedef index_tuple type; };

template<class S1, class S2> struct concat_index_tuple;

template<std::size_t... I1, std::size_t... I2>
struct concat_index_tuple<index_tuple<I1...>, index_tuple<I2...>>
  : index_tuple<I1..., (sizeof...(I1)+I2)...>{};

template<std::size_t N> struct build_number_seq;

template<std::size_t N> 
struct build_number_seq
   : concat_index_tuple<typename build_number_seq<N/2>::type
                       ,typename build_number_seq<N - N/2 >::type
   >::type
{};

template<> struct build_number_seq<0> : index_tuple<>{};
template<> struct build_number_seq<1> : index_tuple<0>{};

}}}   //namespace boost { namespace container { namespace dtl {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_VARIADIC_TEMPLATES_TOOLS_HPP

/* variadic_templates_tools.hpp
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
*/