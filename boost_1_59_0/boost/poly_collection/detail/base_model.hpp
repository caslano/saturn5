/* Copyright 2016-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_BASE_MODEL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_BASE_MODEL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/core/addressof.hpp>
#include <boost/poly_collection/detail/is_final.hpp>
#include <boost/poly_collection/detail/packed_segment.hpp>
#include <boost/poly_collection/detail/stride_iterator.hpp>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* model for base_collection */

template<typename Base>
struct base_model
{
  using value_type=Base;
  template<typename Derived>
  using is_implementation=std::is_base_of<Base,Derived>;
  template<typename T>
  using is_terminal=is_final<T>; //TODO: should we say !is_polymorhpic||is_final?

private:
  template<typename T>
  using enable_if_not_terminal=
    typename std::enable_if<!is_terminal<T>::value>::type*;
  template<typename T>
  using enable_if_terminal=
    typename std::enable_if<is_terminal<T>::value>::type*;

public:
  template<typename T,enable_if_not_terminal<T> =nullptr>
  static const std::type_info& subtypeid(const T& x){return typeid(x);}

  template<typename T,enable_if_terminal<T> =nullptr>
  static const std::type_info& subtypeid(const T&){return typeid(T);}

  template<typename T,enable_if_not_terminal<T> =nullptr>
  static void* subaddress(T& x)
  {
    return dynamic_cast<void*>(boost::addressof(x));
  }

  template<typename T,enable_if_not_terminal<T> =nullptr>
  static const void* subaddress(const T& x)
  {
    return dynamic_cast<const void*>(boost::addressof(x));
  }

  template<typename T,enable_if_terminal<T> =nullptr>
  static void* subaddress(T& x){return boost::addressof(x);}

  template<typename T,enable_if_terminal<T> =nullptr>
  static const void* subaddress(const T& x){return boost::addressof(x);}

  using base_iterator=stride_iterator<Base>;
  using const_base_iterator=stride_iterator<const Base>;
  using base_sentinel=Base*;
  using const_base_sentinel=const Base*;
  template<typename Derived>
  using iterator=Derived*;
  template<typename Derived>
  using const_iterator=const Derived*;
  template<typename Allocator>
  using segment_backend=detail::segment_backend<base_model,Allocator>;
  template<typename Derived,typename Allocator>
  using segment_backend_implementation=
    packed_segment<base_model,Derived,Allocator>;

  static base_iterator nonconst_iterator(const_base_iterator it)
  {
    return {
      const_cast<value_type*>(static_cast<const value_type*>(it)),
      it.stride()
    };
  }

  template<typename T>
  static iterator<T> nonconst_iterator(const_iterator<T> it)
  {
    return const_cast<iterator<T>>(it);
  }

private:
  template<typename,typename,typename>
  friend class packed_segment;

  template<typename Derived>
  static const Base* value_ptr(const Derived* p)noexcept
  {
    return p;
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* base_model.hpp
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
*/