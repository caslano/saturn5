//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/move/unique_ptr.hpp>

//!\file
//!This header provides utilities to define a unique_ptr that plays nicely with managed segments.

namespace boost{
namespace interprocess{

//For backwards compatibility
using ::boost::movelib::unique_ptr;

//!Returns the type of a unique pointer
//!of type T with boost::interprocess::deleter deleter
//!that can be constructed in the given managed segment type.
template<class T, class ManagedMemory>
struct managed_unique_ptr
{
   typedef boost::movelib::unique_ptr
   < T
   , typename ManagedMemory::template deleter<T>::type
   > type;
};

//!Returns an instance of a unique pointer constructed
//!with boost::interproces::deleter from a pointer
//!of type T that has been allocated in the passed managed segment
template<class T, class ManagedMemory>
inline typename managed_unique_ptr<T, ManagedMemory>::type
   make_managed_unique_ptr(T *constructed_object, ManagedMemory &managed_memory)
{
   return typename managed_unique_ptr<T, ManagedMemory>::type
      (constructed_object, managed_memory.template get_deleter<T>());
}

}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED

/* unique_ptr.hpp
ADoACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDMTAvc3JjL2N1cmwudmN4cHJvai5maWx0ZXJzVVQFAAG2SCRglZLbjpswEIbv9ykQ9w6EczqEFWxCm7tVT/fBDOAI29Q2KVLVd69putJKVdtUmn+ksf4ZzSdP/rjw0bmi0kyKvbvd+K6DgsqWiX7vzqYjmftYPOTPSl6QGuejlKP+/GKPVrsdIPTeHYyZ3niepgPys95wRpXUsjMbKrnX4hVHOaHyuG5mNrZe4PuhWzw4Tn4yyN8qOU9rZeuajQaVcxJ0nFvcux/krCg69hm1e/NY1yfBvsx4alEY1jFUxbeofkrDtN6Sp7SMSRSmCSn9JCFBGQaHNA7KoK6/595vjS8Tj4tBsXLpgk4TUKA2lgVa7EC2IzCrYbpAczZw1nzVknuvum7re7f9/wDzDs+trf8Jswt3uzjMfJLtqgOJGj8iWXasSBLEdXWMg2NVV3fCDDDYsESDhRk4MGFZBIVFt/+9/nvUd/5Gkh7KpKwSUme+TyLqZySr0pJkYVVtg21ZHvztnQCKAqMS6Kyg4RO0Yw+KBlYGGiZA9Rp61sFl6q3wZwKFegE7slsTTKKHr+cr8I4q1jRSEK7/zp57r84y936df/EDUEsD
*/