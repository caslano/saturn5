/* Copyright 2006-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SERIALIZE_HPP
#define BOOST_FLYWEIGHT_SERIALIZE_HPP

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/flyweight_fwd.hpp>
#include <boost/flyweight/detail/archive_constructed.hpp>
#include <boost/flyweight/detail/serialization_helper.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/throw_exception.hpp> 
#include <memory>

/* Serialization routines for flyweight<T>. 
 */

namespace boost{
  
namespace serialization{

template<
  class Archive,
  typename T,typename Arg1,typename Arg2,typename Arg3
>
inline void serialize(
  Archive& ar,::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>& f,
  const unsigned int version)
{
  split_free(ar,f,version);              
}                                               

template<
  class Archive,
  typename T,typename Arg1,typename Arg2,typename Arg3
>
void save(
  Archive& ar,const ::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>& f,
  const unsigned int /*version*/)
{
  typedef ::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>    flyweight;
  typedef ::boost::flyweights::detail::save_helper<flyweight> helper;
  typedef typename helper::size_type                          size_type;

  helper& hlp=ar.template get_helper<helper>();

  size_type n=hlp.find(f);
  ar<<make_nvp("item",n);
  if(n==hlp.size()){
    ar<<make_nvp("key",f.get_key());
    hlp.push_back(f);
  }
}

template<
  class Archive,
  typename T,typename Arg1,typename Arg2,typename Arg3
>
void load(
  Archive& ar,::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>& f,
  const unsigned int version)
{
  typedef ::boost::flyweights::flyweight<T,Arg1,Arg2,Arg3>    flyweight;
  typedef typename flyweight::key_type                        key_type;
  typedef ::boost::flyweights::detail::load_helper<flyweight> helper;
  typedef typename helper::size_type                          size_type;

  helper& hlp=ar.template get_helper<helper>();

  size_type n=0;
  ar>>make_nvp("item",n);
  if(n>hlp.size()){
    throw_exception(
      archive::archive_exception(archive::archive_exception::other_exception));
  }
  else if(n==hlp.size()){
    ::boost::flyweights::detail::archive_constructed<key_type> k(
      "key",ar,version);
    hlp.push_back(flyweight(k.get()));
  }
  f=hlp[n];
}

} /* namespace serialization */

} /* namespace boost */

#endif

/* serialize.hpp
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
*/