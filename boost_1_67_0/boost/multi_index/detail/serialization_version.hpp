/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_SERIALIZATION_VERSION_HPP
#define BOOST_MULTI_INDEX_DETAIL_SERIALIZATION_VERSION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* Helper class for storing and retrieving a given type serialization class
 * version while avoiding saving the number multiple times in the same
 * archive.
 * Behavior undefined if template partial specialization is not supported.
 */

template<typename T>
struct serialization_version
{
  serialization_version():
    value(boost::serialization::version<serialization_version>::value){}

  serialization_version& operator=(unsigned int x){value=x;return *this;};

  operator unsigned int()const{return value;}

private:
  friend class boost::serialization::access;

  BOOST_SERIALIZATION_SPLIT_MEMBER()

  template<class Archive>
  void save(Archive&,const unsigned int)const{}

  template<class Archive>
  void load(Archive&,const unsigned int version)
  {
    this->value=version;
  }

  unsigned int value;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

namespace serialization {
template<typename T>
struct version<boost::multi_index::detail::serialization_version<T> >
{
  BOOST_STATIC_CONSTANT(int,value=version<T>::value);
};
} /* namespace serialization */

} /* namespace boost */

#endif

/* serialization_version.hpp
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
*/