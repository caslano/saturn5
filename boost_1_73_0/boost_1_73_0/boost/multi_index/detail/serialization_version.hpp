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
hqVJ50ZLAT1OM0TsTGcZc5DsvaVR61/P8I6r2AvEbutPCg0UXX68MZOtmW5NsTXRmwYdzRUMjlsfNylY+QcS8K2RDr34NOcGesTabBQbS0VQZ1bWInxL+O9ILaEZa4ZRcMeB5oQGXq4KbR7PP40g3nEaGPQdeEJfuaOv6KldhScX80notqmKjn+BXl6QQKWLFX1z6EQ1tpPrpj6hYsjtPbPo6FR3QoCPjWdLNokv2WI2Gp2yyfjDeBnVIN3j/xC4HH8YRTXhjvBtNB3xTJu1D++GXPyk+Glr6kuAtdJtcuiOm/eQX1DjfZMqy9D84jfYaD6P52wx/nn060btSumEKyYL6UJ12Pkkfj+csOFkErQRFrzbkRYcX5AsPSLwOp93vZyPl6Ozi+nJchxPo80svSAyJPT+4uxsNI+aTF8QNY1n8/h8PlosIhi8ROBPhD+ensVbjf84tYRCMKWhRmWd9sLRb88beCWui3bd5870ggr62G2qqJ/GQPI6gsOwLrMObXXD0c4aJOvoo20iaNOdvpmvBIHaAEquOyk/AXs4GNCv8usdaPjiXUhpxOLZaD70mYRJPKUv9/+jBUBlMYTW9IO9MowK8akibAueKuRFVTazvj+Vj3ubDP0x6RB4N8z7x9ZfUEsDBAoAAAAI
*/