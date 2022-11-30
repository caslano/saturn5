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
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
*/