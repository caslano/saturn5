/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_TYPE_RESTITUTION_HPP
#define BOOST_POLY_COLLECTION_DETAIL_TYPE_RESTITUTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/functional.hpp>
#include <boost/poly_collection/detail/iterator_traits.hpp>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* Given types Ts..., a const std::type_info& info and a local_base_iterator
 * it, we denote by restitute<Ts...>(info,it):
 *   - a local_iterator<Ti> from it, if info==typeid(Ti) for some Ti in Ts...
 *   - it otherwise.
 *
 * Using this notation, restitute_range<Ts...>(f,args...)(s) resolves to
 * f(restitute<Ts...>(info,begin),restitute<Ts...>(info,end),args...) where
 * info=s.type_info(), begin=s.begin(), end=s.end().
 */

template<typename F,typename... Ts>
struct restitute_range_class;
       
template<typename F,typename T,typename... Ts>
struct restitute_range_class<F,T,Ts...>:
  restitute_range_class<F,Ts...>
{
  using super=restitute_range_class<F,Ts...>;
  using super::super;
  
  template<typename SegmentInfo>
  auto operator()(SegmentInfo&& s)
    ->decltype(std::declval<F>()(s.begin(),s.end()))
  {
    using traits=iterator_traits<decltype(s.begin())>;
    using local_iterator=typename traits::template local_iterator<T>;

    if(s.type_info()==typeid(T))
      return (this->f)(
        local_iterator{s.begin()},local_iterator{s.end()});
    else
      return super::operator()(std::forward<SegmentInfo>(s));
  }
};

template<typename F>
struct restitute_range_class<F>
{
  restitute_range_class(const F& f):f(f){}
  
  template<typename SegmentInfo>
  auto operator()(SegmentInfo&& s)
    ->decltype(std::declval<F>()(s.begin(),s.end()))
  {
    return f(s.begin(),s.end());
  }

  F f;
};

template<typename... Ts,typename F,typename... Args>
auto restitute_range(const F& f,Args&&... args)
  ->restitute_range_class<
    decltype(tail_closure(f,std::forward<Args>(args)...)),
    Ts...
  >
{
  return tail_closure(f,std::forward<Args>(args)...);
}

/* restitute_iterator<Ts...>(f,args2...)(index,it,args1...) resolves to
 * f(restitute<Ts...>(index,it),args1...,args2...).
 */

template<typename F,typename... Ts>
struct restitute_iterator_class;
       
template<typename F,typename T,typename... Ts>
struct restitute_iterator_class<F,T,Ts...>:
  restitute_iterator_class<F,Ts...>
{
  using super=restitute_iterator_class<F,Ts...>;
  using super::super;
  
  template<typename Iterator,typename... Args>
  auto operator()(
    const std::type_info& info,Iterator&& it,Args&&... args)
    ->decltype(
      std::declval<F>()
        (std::forward<Iterator>(it),std::forward<Args>(args)...))
  {
    using traits=iterator_traits<typename std::decay<Iterator>::type>;
    using local_iterator=typename traits::template local_iterator<T>;

    if(info==typeid(T))
      return (this->f)(
        local_iterator{it},std::forward<Args>(args)...);
    else
      return super::operator()(
        info,std::forward<Iterator>(it),std::forward<Args>(args)...);
  }
};

template<typename F>
struct restitute_iterator_class<F>
{
  restitute_iterator_class(const F& f):f(f){}
  
  template<typename Iterator,typename... Args>
  auto operator()(
    const std::type_info&,Iterator&& it,Args&&... args)
    ->decltype(
      std::declval<F>()
        (std::forward<Iterator>(it),std::forward<Args>(args)...))
  {
    return f(std::forward<Iterator>(it),std::forward<Args>(args)...);
  }

  F f;
};

template<typename... Ts,typename F,typename... Args>
auto restitute_iterator(const F& f,Args&&... args)
  ->restitute_iterator_class<
    decltype(tail_closure(f,std::forward<Args>(args)...)),
    Ts...
  >
{
  return tail_closure(f,std::forward<Args>(args)...);
}

/* binary_restitute_iterator<Ts...>(f,args...)(index1,it1,index2,it2) resolves
 * to f(restitute<Ts...>(index1,it1),restitute<Ts...>(index2,it2),args...).
 */

template<typename F,typename... Ts>
struct binary_restitute_iterator_class
{
  binary_restitute_iterator_class(const F& f):f(f){}

  template<typename Iterator1,typename Iterator2>
  auto operator()(
    const std::type_info& info1,Iterator1&& it1,
    const std::type_info& info2,Iterator2&& it2)
    ->decltype(
      std::declval<F>()
        (std::forward<Iterator1>(it1),std::forward<Iterator2>(it2)))
  {
    return restitute_iterator<Ts...>(*this)(
      info2,std::forward<Iterator2>(it2),info1,std::forward<Iterator1>(it1));
  }

  template<typename Iterator2,typename Iterator1>
  auto operator()(
    Iterator2&& it2,const std::type_info& info1,Iterator1&& it1)
    ->decltype(
      std::declval<F>()
        (std::forward<Iterator1>(it1),std::forward<Iterator2>(it2)))
  {
    return restitute_iterator<Ts...>(f)(
      info1,std::forward<Iterator1>(it1),std::forward<Iterator2>(it2));
  }
  
  F f;
};

template<typename... Ts,typename F,typename... Args>
auto binary_restitute_iterator(const F& f,Args&&... args)
  ->binary_restitute_iterator_class<
    decltype(tail_closure(f,std::forward<Args>(args)...)),
    Ts...
  >
{
  return tail_closure(f,std::forward<Args>(args)...);
}

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* type_restitution.hpp
jurSd8tjM6yva1vJo4fmuWcKRyJ0k4IEYc/om3NsMLTWiDSBZQi1hjqgWraKr9OeHFq2yE63zIIwa9obtuBlcauUbPqWPnTWkheqf44wd03drw3g3KNeoRjZ9plLPC3MgAmqvMIYo6Ky5VTboC8PzbkrC8Mw7RRRnR81TzOJW5MXdAG177V4QF32Yb+MVMYj86kleyz/0kgfw3GyW2G70oxl6WI9Mavo9P+w8sdDA/DczWOe/+QA031t97J5DgDX2tJP0jZPTxu/Zj3CTMzOdVTbZQafAGf1EW430bjRR1vcpHdG2XCXrT1fFVQwozejdLMnz5lOcWnZ2nP4QRXDk7TOv3nGTs1TJPuCrINPWHXQ7fSyNMor5L/ZE80T8/sP/8fZlcf6nU3xH4rai9qLohh7+/pKK2S++75c7RuGiDevfa8Lr+89b6kOg6IYS6REEBlLBJnYYo+IMJH5Q6xjS0SE/uEPu5FIiPjD536/dzn3/O6rYulMf+dzzj33fu9y7rnnnsvkJE2IQNo0tjrQwHXigGKxHn8/637THAYSlmXTp3gKaB13oNti14rbFiIpkgQeEehhD9jUAORz174VZk/XZZ0mlVwcvE/667LNOkH5+6DpagHPYTEUrTbfJHxxsmRsEafcTu4ZRRrmub9c9XQ92xNtrrAzpR5fMesqFG7Dl1VcogmFZDLey/UQXV5HebWtHrIZlYwZPf9TGZ0MncrjFncDpQtMxeFjJnS/+XeccguMH/TBuCmccsU4J9WYkfh3+y3j76IM62TX2ELt1C2zmvH4gskq29NUbdQVcb5N+bb50WXMmeKqa99kfR1jGOOMfHnRXt5So1AdubvGqT2zb7g+uJCQIH5kG33IZ5gsmv2Ko48IZE9u4dxz9fE7hQNiJ9/q6NIjprcrmqQzY8KfNsr9vt9fZXfA4lzGfoqAXMHhfhnK/7tVFseWFlGT1rWjAy6f8i6i++TONfesp4pgUtQFil/fWHID089l+qxmjZ0R13AEVZXgZfq7hfVpB1QOjsml3VvEsuzpCgNe6/IFLz+J2hBrEy/f2w3Inuv8mhtLVOe9jCWMApm2Vq5Ji7QzohM4DgP7DT665n7DJOzzNOkiRx/i5uV3sb7h8KdBhcW+hNkO00Y5xVUk4TqSPJxnftE1dzw0TddHedJsUzZtiBMmJnWNny2UfZmEtHzumVvS/WfXK53+kzUwzSKYKTSziipvXX/3va9kcX+ZiPoUhvDambWlZVgRNAydnvE5fGGQ4iQgbCs59p208dy3UbyS+b+LLCmw/Gozaozu0rnh3PGx+Ep33SqbpEyzKlDZYcaDm5Fl1fjbX8nOyeClzXDkFGAuQFlqMjCxRVsrLJ7pEmufsiix0LfjvIJC2Z3ZLXNOw/jasowjbHrHcp2N0XE9R+syv8baNi+bOq5a1bY4YItDYifaeKHvszK7qBdlJApTpvL40DL1Huyy27Z9XnXDvLXd/uNOXr+wxDUMtMv6khwezlUxfo60Y53F2DUwwdpUBDrtDTYC2pbj55571tl5a9TjEKdJVLkqXFruQtYGa5bbwIcZP449kljFQqgU2Evn3MIDs09eZ/tkEZUINg0DFTew3U0os09ed9cH7LHDVEDQtumG3Da/tO62eZ7j8AnePVM+Dwcjferj6+xOa51mSYvFhaUa4v64b6xP+X6ysuqLgJxpDHs+skjwOe1X/Jsh9qVtESPrS1HE9h3/dHiboMzKOMdQIuXjQw2e3NXF0Z+9rmScMPEMG+y8C1FUfVKWsn+PN/XV5ikO7ZxM7LbZDTaHxHWWYl1wdWCfnaytYsMdz2WXt3lRjRMXYgfhthuagccmLzK9u7QbQko=
*/