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
EedkT2xuUeo+vMr0opiLa+Fbe3w3BG7tEXC1EK/FOMtmnUr0DsisqwGOlp+sapDEJmW7fwlRuffii8Obu1I6VKMX9qyWkTywLhCfsBuUeC3isDPsoyOQhXc4hUQqdnTmq+ms33mFjmnxQGYXMzlJtWhUhO+knN3aULgdXJt1o3M2JuE0icCGTfTpgRZn/lEawSmfzCP3U+Tq0lgZQVNFE4s66eGxelvaZpQDs18Kx2vfN13Fo/l1lKVvGsqXxgUKuhCB9vADr38Ey3k5CKEd00QxjiD+1sYTxkhNc25QQqV76RJs5LF1OqVfB6Z7eGHMNSFc/MtUFRz7Qd/bdEq6haNeOjyNH0jzmz9N8uAJ8ig/jf+E0MCw31rLB+7wbIrzCJjXW0KqAC9newHGiR5FefDz30Ru+7WbBe4NE0IgGKxWXQRg7OXCNkmawCWn+UTLEI4rP7k3YJBrfUBuddq9ZiKs++AWq/yqQgGniOJA1+rsqfHOWNmNvA3ek5jOtzxmmt4eVdU2zGrZZs97CO47ytaRj3IRBQPnnw8/ErUn9IIePOGrAC3gEDJpGQ==
*/