/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_GET_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_DETAIL_GET_VALUE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/hook_traits.hpp>

namespace boost {
namespace intrusive {

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

template<class SupposedValueTraits>
struct is_default_hook_tag
{  static const bool value = false;  };

namespace detail{

template <class T, class BaseHook>
struct concrete_hook_base_value_traits
{
   typedef typename BaseHook::hooktags tags;
   typedef bhtraits
      < T
      , typename tags::node_traits
      , tags::link_mode
      , typename tags::tag
      , tags::type> type;
};

template <class BaseHook>
struct concrete_hook_base_value_traits<void, BaseHook>
{
   typedef typename BaseHook::hooktags type;
};

template <class T, class AnyToSomeHook_ProtoValueTraits>
struct any_hook_base_value_traits
{
   //AnyToSomeHook value_traits derive from a generic_hook
   //The generic_hook is configured with any_node_traits
   //and AnyToSomeHook::value_traits with the correct
   //node traits for the container, so use node_traits
   //from AnyToSomeHook_ProtoValueTraits and the rest of
   //elements from the hooktags member of the generic_hook

   typedef typename AnyToSomeHook_ProtoValueTraits::basic_hook_t     basic_hook_t;
   typedef typename pointer_rebind
      < typename basic_hook_t::hooktags::node_traits::node_ptr
      , void>::type                                                  void_pointer;
   typedef typename AnyToSomeHook_ProtoValueTraits::template
      node_traits_from_voidptr<void_pointer>::type                   node_traits;

   typedef bhtraits
      < T
      , node_traits
      , basic_hook_t::hooktags::link_mode
      , typename basic_hook_t::hooktags::tag
      , basic_hook_t::hooktags::type
      > type;
};

template <class AnyToSomeHook_ProtoValueTraits>
struct any_hook_base_value_traits<void, AnyToSomeHook_ProtoValueTraits>
{
   typedef typename AnyToSomeHook_ProtoValueTraits::basic_hook_t     basic_hook_t;
   typedef typename pointer_rebind
      < typename basic_hook_t::hooktags::node_traits::node_ptr
      , void>::type                                                  void_pointer;

   struct type
   {
      typedef typename AnyToSomeHook_ProtoValueTraits::template
         node_traits_from_voidptr<void_pointer>::type                node_traits;
   };
};

template<class MemberHook>
struct get_member_value_traits
{
   typedef typename MemberHook::member_value_traits type;
};

BOOST_INTRUSIVE_INTERNAL_STATIC_BOOL_IS_TRUE(internal_any_hook, is_any_hook)
BOOST_INTRUSIVE_INTERNAL_STATIC_BOOL_IS_TRUE(internal_base_hook, hooktags::is_base_hook)

template <class T>
struct internal_member_value_traits
{
   template <class U> static yes_type test(...);
   template <class U> static no_type test(typename U::member_value_traits* = 0);
   static const bool value = sizeof(test<T>(0)) == sizeof(no_type);
};

template<class SupposedValueTraits, class T, bool = is_default_hook_tag<SupposedValueTraits>::value>
struct supposed_value_traits;

template<class T, class BaseHook, bool = internal_any_hook_bool_is_true<BaseHook>::value>
struct get_base_value_traits;

template<class SupposedValueTraits, class T, bool = internal_base_hook_bool_is_true<SupposedValueTraits>::value>
struct supposed_base_value_traits;

template<class SupposedValueTraits, bool = internal_member_value_traits<SupposedValueTraits>::value>
struct supposed_member_value_traits;

template<class SupposedValueTraits, bool = internal_any_hook_bool_is_true<SupposedValueTraits>::value>
struct any_or_concrete_value_traits;

//Base any hook
template<class T, class BaseHook>
struct get_base_value_traits<T, BaseHook, true>
   : any_hook_base_value_traits<T, BaseHook>
{};

//Non-any base hook
template<class T, class BaseHook>
struct get_base_value_traits<T, BaseHook, false>
   : concrete_hook_base_value_traits<T, BaseHook>
{};

//...It's a default hook
template<class SupposedValueTraits, class T>
struct supposed_value_traits<SupposedValueTraits, T, true>
{  typedef typename SupposedValueTraits::template apply<T>::type type;  };

//...Not  a default hook
template<class SupposedValueTraits, class T>
struct supposed_value_traits<SupposedValueTraits, T, false>
{  typedef SupposedValueTraits type;   };

//...It's a base hook
template<class BaseHook, class T>
struct supposed_base_value_traits<BaseHook, T, true>
   : get_base_value_traits<T, BaseHook>
{};

//...Not a base hook, try if it's a member or value_traits
template<class SupposedValueTraits, class T>
struct supposed_base_value_traits<SupposedValueTraits, T, false>
   : supposed_member_value_traits<SupposedValueTraits>
{};

//...It's a member hook
template<class MemberHook>
struct supposed_member_value_traits<MemberHook, true>
   : get_member_value_traits<MemberHook>
{};

//...Not a member hook
template<class SupposedValueTraits>
struct supposed_member_value_traits<SupposedValueTraits, false>
   : any_or_concrete_value_traits<SupposedValueTraits>
{};

template<class AnyToSomeHook_ProtoValueTraits>
struct any_or_concrete_value_traits<AnyToSomeHook_ProtoValueTraits, true>
{
   //A hook node (non-base, e.g.: member or other value traits
   typedef typename AnyToSomeHook_ProtoValueTraits::basic_hook_t        basic_hook_t;
   typedef typename pointer_rebind
      <typename basic_hook_t::node_ptr, void>::type                     void_pointer;
   typedef typename AnyToSomeHook_ProtoValueTraits::template
      node_traits_from_voidptr<void_pointer>::type                      any_node_traits;

   struct type : basic_hook_t
   {
      typedef any_node_traits node_traits;
   };
};

template<class SupposedValueTraits>
struct any_or_concrete_value_traits<SupposedValueTraits, false>
{
   typedef SupposedValueTraits type;
};

////////////////////////////////////////
//  get_value_traits / get_node_traits
////////////////////////////////////////

template<class T, class SupposedValueTraits>
struct get_value_traits
   : supposed_base_value_traits<typename supposed_value_traits<SupposedValueTraits, T>::type, T>
{};

template<class SupposedValueTraits>
struct get_node_traits
{
   typedef typename get_value_traits<void, SupposedValueTraits>::type::node_traits type;
};

}  //namespace detail{

#endif   //BOOST_INTRUSIVE_DOXYGEN_INVOKED

}  //namespace intrusive {
}  //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_GET_VALUE_TRAITS_HPP

/* get_value_traits.hpp
g3vAh8AgbdwMZoMLwYPBReAwcDF4DLgEPBG8HDwJ/Cw4CbwSPAu8CpwKLgMrwKvBeeA1YCN4LdgMXgcuAq8HbwY/B94CLgdvBW8A79Ty3Av+Suffd0Xe9cB3Vc8Ogqi3/H6jdp0XwGzwJbC32inzwF3gYLVPDlX75DC1Sx6mdsmj1C55htojZ6l98gLwDbAM/Bu4CNwNXq/2yRXgP1Rf/gk+pnbKVrVTfh98H3wD/JfW50PwH+Be8B0vrPHH+e9U1E/rGYJGQRG/Bg9P1fqdBhaAp/v2Yn3/0Pep4hh78RlqH56u7XE26PHMAP9KonPBXqSbCeaBs8BDwAvA4eCFIPeS2CYctUPshjw7wXLoDrUFeHP7W6CxuofZBGg2dG0J8dBO6A5jHrkSMuZ3sRGEnGJoBtQE3XZ219xp16/r1/Xr+nX9un5dv65f16/r1/X79H4hqOE/Y/+fU1NXsSC8C+D+7QOYg415yCC+S38fYt5r/GJH9/5bb5z9l6bz8WcSOgycAGJr5qNf5uMXza8OFyxcKubd/Pl47NiGzf6QGz3+Ya5lTl5luVa/ghywl1z/jH2OnmumbZi5UatfgMk3XPbkONNhvw3Kpt/SV3rX3yHNPRKfo2UrX+bFP4PMLVyDX/N9C36kEQevxvVp8eKCfvosaPLVctYasU/66bOha67y4svCvBq3R9Ivw4V2UTASnwsdeo0X/xwyfuT01fgCaJXw72YXlKPZS+X+QER+f+hcKd/YsHyN63WtF3c5cup9OYUer9SxJJjJLPJ57h/dSLsUQV8QOTtJvzJcV41fI7JyfDnDoAKp6wOBTDx+F7qD3Uh5RkGXSH0PCpdH406X8l8fCjpLQxE5xdALIucj9ohpcJe5C/08RkOzJc01pHma9Q7fCkbyOA76hpT1lHAeGrde2u4MZB3rRuLHQidpvwadp0RfLmSuuU03pquM8O/olXK2Gfp4lN+HIS9e8suM0peLl3tx9wSCzl3SH701vn6FF58VpUPDJH0oSoe2XtemQ7017nCReUuojzMvJOlVtw7W9Ka+jfy8F7eL/F8I56/x26QOvaN0MMfMX+O+fr2Rv8b9S/JPD+U6O/32zoW6mflr3G7J/x0Xj0pfjwqgvXL/7e0ecvZ0zzF0+PbPhfOTsmrcFpHRx8k39Pnvkv6IHiFnaA9Tp799g/CSXy8/v0LoFeGfA/+MML/GNy0XObTP8ECOoefTpX0GROn4fSu0LZRP1jyI3PuRe0cP4dX4G1cY9dC4flIPfByM+2C7pN9K+i09zHthnPT76alB58TUCH8x9Izwvw7/r8L5afz5Rtl6a1xPkfGZlJDzU9GTAo0vEd6efjlGQ0+I3JyeIefDcDk0/h8iY05K0DknJd+4tx4W/hPhL+qZY9xffaLrTRykuh5JPxb6sqSv65nulPY078Onrw+PAd2duSFvvB7TfIrj7Y0l4zX3ZTjuaZz+Y+NOcUNxcU+7afFxgaz4tMHseL5gblycGyiIi1sWKIrnCw6L53NGxfO5xfF87uj4uOBxRlwqtEX3OjpExoTJYwBp3wIdo96RMXNet63OX1LMcScg49990j99NO5+0cuvO1ompxTZpZLXB9mRPphhxBn5jo7Nt0nG0b7dtjj3RuXbIvFro/L9g9zrj/j5lljynWDP95jYfMdIfcd1e8J5OirfcVfH5/uk3PMP+/lOtOQ72Z7vkYDKCv/6yXNsU1RZjpN75qtpX3N+IWXJ1Xzny5jyomuW5WThfSCcXuMGicxQ6mbnWb1vXZFbIuPrb4UXe6vwhsvYz03HShEp+9q4+rADr70+R2l9/PeeP17V9h7TW+O6yTP2RuLa6pgp9+kW/54=
*/