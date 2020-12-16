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
pDgxS+d269y1/fKz5ArRr9Z5esd0XmGp9HdA58tdqPpulD9Kv3fq/PSf6Tz6In2+8B065+18nf/2OOnzwzpvTuccDh/SuZSO4pPk3/Yl9cvrdO7WqM5DvErlihQ/Fuq8tBvlx8M6v3eu9HOax8/n79I5kI70nNF5dbvVL6okT6mJv/pUHCsS/QH1x/2KP7fdoHgnPVfNkX8Yf36X4on657D8/o5jOgf7qWr3Y/InnfvV8HnFv2PyW7Vfcq7i5Yekn7/pfKsX6PyvZTp/v0ZxU+dclfxK8adYdv6T/JyriOvbz1f8errOW5yneNCvc9MOq17FxZRwH1sm/tcoTsh/6j4kfxWfez6i84IrdC7bnYrTOp/ujmfrfL9d0tM/dS7cH0VPS4+S5/N3SI5u6eMu6eeb0sMZ6mdj8s+/69yyQY0X75N9pnWe2sck34lZ4ltxeZH8caH8ZKfO85Ycp39C+NPkXwd17vR89ce/ib83a7xYqf52o+LB48y5jopnL5Rdf6NxkquI696E4ojOI3/gi9JfrcaRed79My+SHhXXH3lQ/qlzDO84rv7xPdnxecoHniF/Vr9+wbflxzqX94EWneso/lauUP5wltpXHK74ocalX+pcQ9njB7eLj0s1vp8l/X5D44HkbxiTXLJ7hdH7Dp0/6J+DrfFljuw6IXsrDtxYUqS8SfU8ov55v851fLzKrdZ5fWt0jt4qnVv3Q7WjePbOS9Se7HCmGR/manx7ovxT551eLf7f/Cfx/X2Np3/V+ZI63/XHOu/7/rvlJy+VnpUvveaoxtcL1S8Xy3/fLH9Rv912gexRpP6SVPy9QfIojl3Yrfvy10veo366Tf51ts4BPKF+ZM6ZfVj62qM4+AGND8vlJ+eLzytVTnFp/y61o3GrTvL/xeh9k/r5c1XfL5RnzTHjvfzpmPKPeZJX51zPk3wXbpTevqr+epPOgT1T47v4KTmueKW4drnOxXzEnKep9j9fqXKrdH7zjYrXadWzUPa/SrhJ5UPP1/g0JH2/TOfuTiuOalxo+Kv0sUD2Oaz+d4Hiy1Nk52L5z53Kb65R3Hut5Df5n+LX5erH/7xNeYjyld+p/qLfir8fK/9VPLnzfco3BuRn+vzw9Tr/8zT5r85dT0k/z5bezvy3xpHPaZzWOPexT2tcqVC8+bL62SzFoY8qn3uF7HG6+JpWfD1N8v5M52cOaLwrlr5Oip/fmTxNcfwHmpdo/Kn7p+x6rfKtOs0X1O6HH1Lek5G+dJ77C1pnye9k5/Nkv/fovPX7ZK/vq/99Vvz+SHZVPOibp+9vUX0ParxQP723VHn3S0XXOfIlsvc7S9SvTlP//Jv0qHnEUyX/nm9oXL9H/WyO4uEsjUvnKj9Tv/ndgPT9Dtn5J8rzlqg/3qTzyO+Xnv6p9o4qrlYpzm3VOary62+rf98vvoePyT7Pl97+qPHtC/LrGulxkeLuQtlHetgmeySXafwU/TW3azy5V/OlxZpv7VO8/qDGPfGRFN/3z1d/0PUM5RfPvktyfFt6GFV/Pya7qj+dqX56ybDySbVfdIPmjbw329aYqGnfmhhKZSoS6eRgso9w+DTnLCKYe6aRWz7RFmASyd50fyI9OJAZGHISzxQu/oxIHH/0pjozic4diHS+sCNhLPTUYBaU8tstgBnKDAym+GXui4WbKoC7MjXYs3N/ojPZ27sj2bnbUb2cq5SP70l3pwYTvT1DGafTyMNz0zxcb0+qP5OoqfKgzg6DnbxnVgGsxAJr+J2eGZvq39XTj3yOwY/9LB8/MLC7J5XYlepPDSYzKeoHZ3iZKIiXRkBXGh1H6ALNJXt7upKZnoH+QHtOxtRf/qyIMr0Du7I=
*/