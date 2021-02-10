/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SET_FACTORY_HPP
#define BOOST_FLYWEIGHT_SET_FACTORY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/allocator_utilities.hpp>
#include <boost/flyweight/assoc_container_factory.hpp>
#include <boost/flyweight/factory_tag.hpp>
#include <boost/flyweight/set_factory_fwd.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/if.hpp>
#include <set>

/* Particularization of assoc_container_factory_class using a set.
 */

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Compare,typename Allocator
>
class set_factory_class:
  public assoc_container_factory_class<
    std::set<
      Entry,
      typename boost::mpl::if_<
        mpl::is_na<Compare>,
        std::less<Key>,
        Compare
      >::type,
      typename boost::mpl::if_<
        mpl::is_na<Allocator>,
        std::allocator<Entry>,
        Allocator
      >::type
    >
  >
{
public:
  typedef set_factory_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(
    4,set_factory_class,(Entry,Key,Compare,Allocator))
};

/* set_factory_class specifier */

template<
  typename Compare,typename Allocator
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF
>
struct set_factory:factory_marker
{
  template<typename Entry,typename Key>
  struct apply:
    mpl::apply2<
      set_factory_class<
        boost::mpl::_1,boost::mpl::_2,Compare,Allocator
      >,
      Entry,Key
    >
  {};
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* set_factory.hpp
Ut+RYctoBwAAchAAAC8ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1JFU09MVkUuM1VUBQABtkgkYK1XbXPaxhb+rl9xhjtzx46xsJ20bpy0cwmmNTcEMYCT64kzmkVamW2EpGpXYKbpf+9zdiUD9s0kH4rHIHb3vD/n2YN/26Jn/9jL81kdffMV2v8QL3w2QuMy/11G5v8LhOEXcn8QvMXnd5jq0FbqS3hI3yX1hQ6sVFjbes3PYfgd5m7ZSX7rsPBtyI9YcZK1fC8vNqW6Wxg66B3S6cuXP9ExnZ2cnbTpUmRKpjQ1MpvL8q5Nr2O78p+FuL/3tfylTdKQSP09hbOF0qTzxKxFKQnPqYpkpmVMQlMsdVSqOb6ojMxCUqJSSb1gfDMY/dam9UJFi1rPJq9IL/IqjWkhVpJKGUm1cmoKURrKE2iA/lhpA52VUXnmw7wkI8ulrtWwEyLVOYmVUKmYw5wwtDCm0BedTlSVKSLpxHmkO1GTCn9hlo+iuoE3S7GhvDBkcqq0bBOfb9Myj1XCn0gRFotqniq9aG/dgsEs7uQlaZmmtTqIKqldCJKmdbbafJIKeK8Mf+g802xtvciXeweR1lpRUpUZzCEtOBfnSHybqiyWpT1vE9FY
*/