/* Copyright 2016-2018 Joaquin M Lopez Munoz.
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

    using namespace boost::type_erasure;
    using ref_type=any<Concept2,T>;
    using make_ref=any_model_make_reference<_self,ref_type>;
    using concept_=typename concept_of<value_type>::type;

    auto b=make_binding<mpl::map1<mpl::pair<_self,ref_type>>>();

    return {call(binding<make_ref>{b},make_ref{},x),binding<concept_>{b}};
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* any_model.hpp
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
*/