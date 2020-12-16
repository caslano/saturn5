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
ALN1TedNhQWeZ2MQz/7HKRZULKRYkmIpiqUqlk7mZTb2yqWDYBEyP7PSgrlbYEVkFrOr1z/1DqxcyVmt5GxWcnYoY+hSrIfMZuZ65MbtMM/fo3t578yn/4TFkfFe+HeTEsk8MPkdTWayl0mKpSk5M5iVRb33gN43yOwBep+A+R0ZLIvMZrZv2QnzYYXCpr335umwcsVqRT308t/v+LG4jfT9sfg7Bx4EayWzmB3VWNUL6xJxMwJ33A9zvUD1mPF6HsUsxXyKBRSLUyyoWEixJGFmPwhLUSzVMeeoYDqzB+n7cdwyFYsolq1YnmIFihUpVqJYmWIVilUpVqNYnWINijUp1qJYm2IdinUp1qNYn2KuOmfzKGYp5lMsoFicYkHFQoolKZaiWKpi6YplKhZRLFuxPMUKFCtSrESxMsUqFKtSrEaxOsUaFGtSrEWxNsU6FOtSrEexPsVcLyrbn2KWYj7FAorFKRZ0NFdyiFk5fbOUW5JiKYqlKpauWKZiEcWyFcsjs5iZv+fAihWrIPMyM9eNsBoyH7O0d+O+hDUrvbQKM+eDsHYlrlOxbmFH/XjqrbBe0WfDc+nrYdZL0bZ9wvM2LJ7MZjbRW9YLSxZx5tk5WKaI+yjpoe37LWdOHhn6fEh8/7aA2cP0HVtuRYqVKFamWIViVYrVKFZHZsPEd3pbyLzMzFyCdZD5mJm/F8P6ySyY+C6w9Q9niyXjOc3vvWFJZE5jSFEsVbF0xTIViyiWrVieMHPuDStQ4ooUK1GsTLEKxaoUq1GsTrEGZexNSlyLYm2KdSjWpViPYn2KueqdzcNMjt1S4nyKBRSLUyyoWEixJMVSFEtVxp6uxGWS2czeHvT3TfvN5cojw35iE927qLnvoSdgpWQWTHzft0qYeVYdVk/mhYl3YDYrOTvIPMzMbytgXUpcv2LWyyyneK+mj8ypzzjFQiInO4a7kshsZlcv27wClk7mY/bW0dntsFxhjx8+dSisRLFq1kuFGF8tmQ0T3/5tJvMzizm6dxOsG/WQc/ER98I826JzXnPEaUNhATKLmXl/JCyBzAsTyzPZ0TJmpZFhfJvpNwRmXsMyFAsrlqVYrmL5ihWS+ZmZ98LBKsl8zBpW3fU8rIHMZnbCOQN/h7WRWczy7MlZsG5h7DvEc1zbD/T5CH030PQJ8yhmKeZTLKBYnGJBxUKKJSmWolgqmcWML7MwmY9Ze9zhG2EFZF6Y+KZnCZmf2WF1h58Fq+G9iO991pHZzIbc9cYvsBZHm5vVxXJuEe+771GsTzFXg7N5FLMU8ykWUCyOzM/MbEewFDIvs6q1F34LSyeLZTZmVP8CWAGZxSzp/RUDYKVkNjOzj4RVi7jOoa9+C2sQcUckzNgDayPzMRtYduqxsF6Rs+eM5t0wzyvRY+91Tz0ZFkfGx77h69cfgYXIeC+/9R7xJyxV2PTKtpdgEcUKyHif5jd7sFLRy/fzOr6BVYoxuK4tvA3WKGz9xud+g3WKXhZtej0b1i9s5NxvD4HZO1if4tujcWQ87ve9M/NhSUpcGpmHmTm+wzJEHPYhZLOyWVwl/+0WWZ5iBWQWM56zlMzLzOx7YJWK1Sr16pW4ZjKbmflbK6xTydmt5OxX4mJ20rbC7MC175xwgAxxj/Lvd5DFKRYUZt7PAAsplqRYimKpSi/pimUqOSOKZSs58xQrUHIWKVai5CxTrELJWaVYDTfxW8Y6xRqUnE2KtShjaFOsQ8nZpViPkrNPMVejc06PYhYzucx8igWUnHGKBZnJMYQUS1JypiiWquRMVyxTyRlRLFvJmfcfvu4HvOp5jwP42Rwc+eHIDycdOXSwalg1mUyG3WtqMgyTc7U0TCY=
*/