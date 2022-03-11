/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_ANY_HOOK_HPP
#define BOOST_INTRUSIVE_ANY_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/any_node_and_algorithms.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Helper metafunction to define a \c \c any_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
struct make_any_base_hook
{
   /// @cond
   typedef typename pack_options
      < hook_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3
      #else
      Options...
      #endif
      >::type packed_options;

   typedef generic_hook
   < AnyAlgorithm
   , any_node_traits<typename packed_options::void_pointer>
   , typename packed_options::tag
   , packed_options::link_mode
   , AnyBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from this hook in order to store objects of that class
//! in an intrusive container.
//!
//! The hook admits the following options: \c tag<>, \c void_pointer<> and
//! \c link_mode<>.
//!
//! \c tag<> defines a tag to identify the node.
//! The same tag value can be used in different classes, but if a class is
//! derived from more than one \c any_base_hook, then each \c any_base_hook needs its
//! unique tag.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link, \c safe_link).
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class any_base_hook
   :  public make_any_base_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3>
      #else
      <Options...>
      #endif
      ::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   any_base_hook();

   //! <b>Effects</b>: If link_mode is or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   any_base_hook(const any_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   any_base_hook& operator=(const any_base_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a container an assertion is raised.
   //!
   //! <b>Throws</b>: Nothing.
   ~any_base_hook();

   //! <b>Precondition</b>: link_mode must be \c safe_link.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c container::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;
   #endif
};

//! Helper metafunction to define a \c \c any_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
struct make_any_member_hook
{
   /// @cond
   typedef typename pack_options
      < hook_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3
      #else
      Options...
      #endif
      >::type packed_options;

   typedef generic_hook
   < AnyAlgorithm
   , any_node_traits<typename packed_options::void_pointer>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Store this hook in a class to be inserted
//! in an intrusive container.
//!
//! The hook admits the following options: \c void_pointer<> and
//! \c link_mode<>.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link or \c safe_link).
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class any_member_hook
   :  public make_any_member_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3>
      #else
      <Options...>
      #endif
      ::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   any_member_hook();

   //! <b>Effects</b>: If link_mode is or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   any_member_hook(const any_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   any_member_hook& operator=(const any_member_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a container an assertion is raised.
   //!
   //! <b>Throws</b>: Nothing.
   ~any_member_hook();

   //! <b>Precondition</b>: link_mode must be \c safe_link.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c container::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;
   #endif
};

/// @cond

namespace detail{

BOOST_INTRUSIVE_INTERNAL_STATIC_BOOL_IS_TRUE(old_proto_value_traits_base_hook, hooktags::is_base_hook)

//!This option setter specifies that the container
//!must use the specified base hook
template<class BasicHook, template <class> class NodeTraits>
struct any_to_some_hook
{
   typedef typename BasicHook::template pack<empty>::proto_value_traits old_proto_value_traits;

   template<class Base>
   struct pack : public Base
   {
      struct proto_value_traits
      {
         //proto_value_traits::hooktags::is_base_hook is used by get_value_traits
         //to detect base hooks, so mark it in case BasicHook has it.
         struct hooktags
         {
            static const bool is_base_hook = old_proto_value_traits_base_hook_bool_is_true
               <old_proto_value_traits>::value;
         };

         typedef old_proto_value_traits basic_hook_t;
         static const bool is_any_hook = true;

         template<class VoidPtr>
         struct node_traits_from_voidptr
         {  typedef NodeTraits<VoidPtr> type;  };
      };
   };
};

}  //namespace detail{

/// @endcond

//!This option setter specifies that
//!any hook should behave as an slist hook
template<class BasicHook>
struct any_to_slist_hook
/// @cond
   :  public detail::any_to_some_hook<BasicHook, any_slist_node_traits>
/// @endcond
{};

//!This option setter specifies that
//!any hook should behave as an list hook
template<class BasicHook>
struct any_to_list_hook
/// @cond
   :  public detail::any_to_some_hook<BasicHook, any_list_node_traits>
/// @endcond
{};

//!This option setter specifies that
//!any hook should behave as a set hook
template<class BasicHook>
struct any_to_set_hook
/// @cond
   :  public detail::any_to_some_hook<BasicHook, any_rbtree_node_traits>
/// @endcond
{};

//!This option setter specifies that
//!any hook should behave as an avl_set hook
template<class BasicHook>
struct any_to_avl_set_hook
/// @cond
   :  public detail::any_to_some_hook<BasicHook, any_avltree_node_traits>
/// @endcond
{};

//!This option setter specifies that any
//!hook should behave as a bs_set hook
template<class BasicHook>
struct any_to_bs_set_hook
/// @cond
   :  public detail::any_to_some_hook<BasicHook, any_tree_node_traits>
/// @endcond
{};

//!This option setter specifies that any hook
//!should behave as an unordered set hook
template<class BasicHook>
struct any_to_unordered_set_hook
/// @cond
   :  public detail::any_to_some_hook<BasicHook, any_unordered_node_traits>
/// @endcond
{};


} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_ANY_HOOK_HPP

/* any_hook.hpp
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
*/