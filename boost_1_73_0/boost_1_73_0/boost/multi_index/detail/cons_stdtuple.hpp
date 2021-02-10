/* Copyright 2003-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_CONS_STDTUPLE_HPP
#define BOOST_MULTI_INDEX_DETAIL_CONS_STDTUPLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/if.hpp>
#include <boost/tuple/tuple.hpp>
#include <tuple>

namespace boost{

namespace multi_index{

namespace detail{

/* std::tuple wrapper providing the cons-based interface of boost::tuple for
 * composite_key interoperability.
 */

template<typename StdTuple,std::size_t N>
struct cons_stdtuple;

struct cons_stdtuple_ctor_terminal
{
  typedef boost::tuples::null_type result_type;

  template<typename StdTuple>
  static result_type create(const StdTuple&)
  {
    return boost::tuples::null_type();
  }
};

template<typename StdTuple,std::size_t N>
struct cons_stdtuple_ctor_normal
{
  typedef cons_stdtuple<StdTuple,N> result_type;

  static result_type create(const StdTuple& t)
  {
    return result_type(t);
  }
};

template<typename StdTuple,std::size_t N=0>
struct cons_stdtuple_ctor:
  boost::mpl::if_c<
    N<std::tuple_size<StdTuple>::value,
    cons_stdtuple_ctor_normal<StdTuple,N>,
    cons_stdtuple_ctor_terminal
  >::type
{};

template<typename StdTuple,std::size_t N>
struct cons_stdtuple
{
  typedef typename std::tuple_element<N,StdTuple>::type head_type;
  typedef cons_stdtuple_ctor<StdTuple,N+1>              tail_ctor;
  typedef typename tail_ctor::result_type               tail_type;
  
  cons_stdtuple(const StdTuple& t_):t(t_){}

  const head_type& get_head()const{return std::get<N>(t);}
  tail_type get_tail()const{return tail_ctor::create(t);}
    
  const StdTuple& t;
};

template<typename StdTuple>
typename cons_stdtuple_ctor<StdTuple>::result_type
make_cons_stdtuple(const StdTuple& t)
{
  return cons_stdtuple_ctor<StdTuple>::create(t);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* cons_stdtuple.hpp
sy1aCCttTB+P5++m53P6OD47G5/OL2j6lsanFz7Y++PTA7ReAqwmvq5qtgCvSZaVkpx1mN/uGkTfSZ2qJmPacmzRqq3oVvQqT7VT/eJ19MAMk6G86a0UxWuFZO9LSy4zXjTLNmzGudRM88PZPHk3Pj1K5scnh56IH4cofXc4HEbRYId+Gg6plArN59TozGLelLlC8TTW4MTVXDLppsTCIbBMip2lhR9nGN5gKLAu6pVwGO0IaxRNDQHIYO79ZFj/Uoq0QDJhMOpGt3PvS4PAkOely/Zk/HvyZjLdf394EPJNTmY+wyiS2gWHXlqImnbOzybb0d8A3McT7RRAwtr4hU7PJ5NRJz6hnfKRwsdBmyEZrl8t6FUJ0tJSL1sFNNZhjSYeMnGyhKa3HeRLZRZCJVJL1/MoydFk+mY8ScaTSWvAwt606hb8jtSyw0Ls5HFIcvphnuAWk69otMHwt8OzN9PZYUy7HVbZKCdbsPIuWisXWZa00rU2psdWWLO5qctbk2f3CGlNxcKADaO/EsKmcR0j2PGAcN+JfG88iXWDc8bbr4Sizm8UdHnmy8QNk5Q9EF3V0vEDGV+nXLUy37VSXOcZuvV8b2/0FNaCURU/qRI5tplWowxazqEMWqfXdytApusRuSdvWoVfPcPh
*/