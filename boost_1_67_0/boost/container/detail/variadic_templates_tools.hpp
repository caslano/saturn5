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