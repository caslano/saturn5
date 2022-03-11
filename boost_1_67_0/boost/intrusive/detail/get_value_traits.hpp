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