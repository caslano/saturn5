/* Copyright 2016-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_ANY_MODEL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_ANY_MODEL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/core/addressof.hpp>
#include <boost/mpl/map/map10.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/poly_collection/detail/any_iterator.hpp>
#include <boost/poly_collection/detail/is_acceptable.hpp>
#include <boost/poly_collection/detail/segment_backend.hpp>
#include <boost/poly_collection/detail/split_segment.hpp>
#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/any_cast.hpp>
#include <boost/type_erasure/binding.hpp>
#include <boost/type_erasure/builtin.hpp>
#include <boost/type_erasure/concept_of.hpp>
#include <boost/type_erasure/is_subconcept.hpp>
#include <boost/type_erasure/relaxed.hpp>
#include <boost/type_erasure/static_binding.hpp>
#include <boost/type_erasure/typeid_of.hpp>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* model for any_collection */

template<typename Concept>
struct any_model;

/* Refine is_acceptable to cover type_erasure::any classes whose assignment
 * operator won't compile.
 */

template<typename Concept,typename Concept2,typename T>
struct is_acceptable<
  type_erasure::any<Concept2,T>,any_model<Concept>,
  typename std::enable_if<
    !type_erasure::is_relaxed<Concept2>::value&&
    !type_erasure::is_subconcept<type_erasure::assignable<>,Concept2>::value&&
    !type_erasure::is_subconcept<
      type_erasure::assignable<type_erasure::_self,type_erasure::_self&&>,
      Concept2>::value
  >::type
>:std::false_type{};

/* is_terminal defined out-class to allow for partial specialization */

template<typename Concept,typename T>
using any_model_enable_if_has_typeid_=typename std::enable_if<
  type_erasure::is_subconcept<
    type_erasure::typeid_<typename std::decay<T>::type>,
    Concept
  >::value
>::type*;

template<typename T,typename=void*>
struct any_model_is_terminal:std::true_type{};

template<typename Concept,typename T>
struct any_model_is_terminal<
  type_erasure::any<Concept,T>,any_model_enable_if_has_typeid_<Concept,T>
>:std::false_type{};

/* used for make_value_type */

template<typename T,typename Q>
struct any_model_make_reference
{
  static T& apply(Q& x){return x;}
}; 

template<typename Concept>
struct any_model
{
  using value_type=type_erasure::any<
    typename std::conditional<
      type_erasure::is_subconcept<type_erasure::typeid_<>,Concept>::value,
      Concept,
      mpl::vector2<Concept,type_erasure::typeid_<>>
    >::type,
    type_erasure::_self&
  >;

  template<typename Concrete>
  using is_implementation=std::true_type; /* can't compile-time check concept
                                           * compliance */
  template<typename T>
  using is_terminal=any_model_is_terminal<T>;

  template<typename T>
  static const std::type_info& subtypeid(const T&){return typeid(T);}

  template<
    typename Concept2,typename T,
    any_model_enable_if_has_typeid_<Concept2,T> =nullptr
  >
  static const std::type_info& subtypeid(
    const type_erasure::any<Concept2,T>& a)
  {
    return type_erasure::typeid_of(a);
  }

  template<typename T>
  static void* subaddress(T& x){return boost::addressof(x);}

  template<typename T>
  static const void* subaddress(const T& x){return boost::addressof(x);}

  template<
    typename Concept2,typename T,
    any_model_enable_if_has_typeid_<Concept2,T> =nullptr
  >
  static void* subaddress(type_erasure::any<Concept2,T>& a)
  {
    return type_erasure::any_cast<void*>(&a);
  }

  template<
    typename Concept2,typename T,
    any_model_enable_if_has_typeid_<Concept2,T> =nullptr
  >
  static const void* subaddress(const type_erasure::any<Concept2,T>& a)
  {
    return type_erasure::any_cast<const void*>(&a);
  }

  using base_iterator=any_iterator<value_type>;
  using const_base_iterator=any_iterator<const value_type>;
  using base_sentinel=value_type*;
  using const_base_sentinel=const value_type*;
  template<typename Concrete>
  using iterator=Concrete*;
  template<typename Concrete>
  using const_iterator=const Concrete*;
  template<typename Allocator>
  using segment_backend=detail::segment_backend<any_model,Allocator>;
  template<typename Concrete,typename Allocator>
  using segment_backend_implementation=
    split_segment<any_model,Concrete,Allocator>;

  static base_iterator nonconst_iterator(const_base_iterator it)
  {
    return base_iterator{
      const_cast<value_type*>(static_cast<const value_type*>(it))};
  }

  template<typename T>
  static iterator<T> nonconst_iterator(const_iterator<T> it)
  {
    return const_cast<iterator<T>>(it);
  }

private:
  template<typename,typename,typename>
  friend class split_segment;

  template<typename Concrete>
  static value_type make_value_type(Concrete& x){return value_type{x};}

  template<typename Concept2,typename T>
  static value_type make_value_type(type_erasure::any<Concept2,T>& x)
  {
    /* I don't pretend to understand what's going on here, see
     * https://lists.boost.org/boost-users/2017/05/87556.php
     */

    using ref_type=type_erasure::any<Concept2,T>;
    using make_ref=any_model_make_reference<type_erasure::_self,ref_type>;
    using concept_=typename type_erasure::concept_of<value_type>::type;

    auto b=type_erasure::make_binding<
      mpl::map1<mpl::pair<type_erasure::_self,ref_type>>>();

    return {
      type_erasure::call(type_erasure::binding<make_ref>{b},make_ref{},x),
      type_erasure::binding<concept_>{b}
    };
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* any_model.hpp
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
*/