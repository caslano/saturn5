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
   any_member_hook() BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   any_member_hook(const any_member_hook&) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   any_member_hook& operator=(const any_member_hook&) BOOST_NOEXCEPT;

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
   bool is_linked() const BOOST_NOEXCEPT;
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