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
G1UM8Zph7zeyYsx8Xew7hSbpEsiGMHt28ulElLfJpDwTiyU7xazRuHOTYJvdp4szsfjN+jzP9drjD9viPp3LxBJMLNHExFb35mtiQSYWYmKhJhZmYuEmFmVi0SYWY2KxJhZnYvEm5jKxBBNLNDGxzaT/TCyIrC6z3tFhF9AuJuliTSzOxOJNzGViCSaWaGJiu0m7kB1mdnNerT2wHSZtRhYsbZ+WtLfdlAoYu2RFYPpvqMWYmMvEfHc6RAZm6YbXcmGOkQUxy9U6ogbmikm6aLLMzBYPK7IU/WdiCWTpmD0+1mOHum7Ut0u6KSXnop679PFVHh1+D/PWxOJMLHGXPr6ZDRreUdeb+nZZum2w+s3ybvfpwnfrYw9qXHgV+s/E4nfr26Vt1u5b0WZk06XtoT90f/uxOebRHocoqSkr06ubHW22zyHyCmWezWZMRJuRvZK2O+n64Uwx9XvteIfox2xZgWkZEft+h2jgoaxtRPZJaOsjjuTrHGlnPi7tifY8qo6pu5Kuuc78rvaeIvubmVfOe/Foz2MOsYRZzXpbniC+4w5RmFmxbtvU74vJXMzejEp8i7F7wiF6Mau2/a46vz7pEFWYRWXsMBZ5kg1g1tM1+QLSnaJrJ2alLj1HDDFkTZiVT4z1xZg/7RDlmDUdMS4V1gIyL5j+/CycrLRF2ZXXjbuhXVyO5PsF0j6em1sb68Q5eZ4lrWrbC+qbkOcdohaza5GLhyN2srwszzkzGqm9My84RAeLsiGl6/wBu+wQtzVltaz/aah+O0fn1xZlgzZOOqzev3aIm5qylKuzF1V7/jlEdmYDT40fiLlyxyHesBhehcyqrN4XdogE3p7V+k5Em92j8pi9G/NS9cN9h5jB7K8R1rPI84E8v5aWZ8/5QPQRWRiznSvTqN8fkaWGGb7DQeYHM7y79dB9upCH7tOFmViUSZ4xJuniyCpJ22m4j+L7yCG+SNuR9K57p9ddUZfHDuEPM3wvmWwAs+I/u3sizycOkRam3xM2hGwGs4/Ft6o9ucimMmu85e8yiOGpQ3yzKuv/LN962CtH8vtE0mbWH4Q12fXaIboz6/yvS+3rkOgQi5hVehn1Sr2P4hCBMMN3McgywQzfVSBLDTN8n5LMD6bvI5eJJbLythvKC3rrELOYhf/cgHmbQJab2aa0DdQeRO/cWyhZXmYTHv7qhTXZxOLJ8jArW+9ga6yf793HEEL2F7Mbc06lRLsY0v1a4vMp5PnBvYWQ5WB2a8F99fsOsubStiU9t+9UcBjajOw+s1nfwjOivI8OcYtZ8OKbs9APnxyiKbNMJ5qo80GyjMw2+Ge0YkyQZdCU+bqCV6OPvsj7YNLEjN/OIQayUcx2nnSo3w58dYjRzDJ3GbcGfUTWh5UXIgoVw/nEd4f4nVn34HvpMCZoOJ5leXYYnv6Yuh/pFN01ZRl8KmVFu1ic4qBQ5p1zTDGY1SlSwwzf9SLzgxm+/2di0WT+0rYa1qxYsrQwwzeHyHIwa7T6Mo5HiWRTmH06+noM+s/DvUV5OsV1Zu+un8yNetqc4jdmf+3J8h1jkKwUs0mDXR0wru3uLZpsjKbseMNX5VEXp1PkYZa9ebkviM/LKRzM+uQ6kR794ONMPneT9uFj+xQoj8wLpj/viSE7x6zKoFbqOyop3FtcSqcoyyzr45HqOXMqp+jCrOK11z4oj2wBs5B5xbNhvPg6RQVm3c7HWlAe2Q1mG3stx/rpSu0Up5jtqd6iPSyNUwxlVq57N3VfOK1T9GWWM3Ai2sw3nVO4mHVvtvE55oOfUwxgVsTvQkqMT7JGzBa1zXYPY4IeHpVhdvrgpwroI7I9zLI/qhKIevo7xXxmO2o=
*/