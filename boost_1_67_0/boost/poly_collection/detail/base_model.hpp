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