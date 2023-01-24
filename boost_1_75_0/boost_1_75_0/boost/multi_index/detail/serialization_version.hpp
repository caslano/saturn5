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
Dwdo0pUtpjM4/yEFg7neTHRBAdItgjgIxR5MxCmU22AY2lnTu5q8AFoD4umE2KrYJ5zDbPErUqk33ZTJ0DRWKtoLp6AoHSWi9tTdbtLy2MB6PRgWUIG+0hWwueyy4eectUXXSHIaKl0ciOzQg31FATNlypsnsbvAOWKUTGetF+ioXvhGpOQfa/MEpia4VqeSGAWa6JmZ/lBXe8k8enWMLdgDOw+kF+K8W8dT59GlAbq+TD2tZqY/0LVon+SfAgBwDfwAF/OQLThGogHvyEwv6FrUE25swTjJmRfvjUPXFTnTRg+g77XBbhjWV67NTL+vq9dOnoaYNo6eH8NPHjFj0tpdqPCV4HtwjnjflAJjgfZ4IB5jkGpgETHBD2UPS4Y1l9tqy67E4av4hrbm/hS33A4XCAfgvcQwxofuMY7x2/PaGKE+WrtXQoHEqXqh63fESynbAE7qlQ+x3H8FdAFm4uF4cco/yLaYeeRYoyk5GsWAGpZHJvinkbSR3Zl6r++ANhF9T8+d4J+eGZgKtOBkqHpbulZ3cKJeN4W+Px2OvsnpUDux6XmwUq3JCRwZyj89foLfaQzj2pgWIeoU/Y0vf0jPYcYyUCQlSrd7o9PK68aiK2LGfelFl8K/UlGSFBiWLPke5ZXpQLacj9MZ6IVNMUiqu4KlooAWHopHksg3k6tGwV6Ewoclt8hgtu1PRHyB7BrJN0OxSfYBcOXP
*/