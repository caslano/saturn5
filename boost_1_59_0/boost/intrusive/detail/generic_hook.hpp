/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_GENERIC_HOOK_HPP
#define BOOST_INTRUSIVE_GENERIC_HOOK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/detail/node_holder.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/static_assert.hpp>

namespace boost {
namespace intrusive {

/// @cond

namespace detail {

template <link_mode_type LinkMode>
struct link_dispatch
{};

template<class Hook>
BOOST_INTRUSIVE_FORCEINLINE void destructor_impl(Hook &hook, detail::link_dispatch<safe_link>)
{  //If this assertion raises, you might have destroyed an object
   //while it was still inserted in a container that is alive.
   //If so, remove the object from the container before destroying it.
   (void)hook; BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT(!hook.is_linked());
}

template<class Hook>
BOOST_INTRUSIVE_FORCEINLINE void destructor_impl(Hook &hook, detail::link_dispatch<auto_unlink>)
{  hook.unlink();  }

template<class Hook>
BOOST_INTRUSIVE_FORCEINLINE void destructor_impl(Hook &, detail::link_dispatch<normal_link>)
{}

}  //namespace detail {

enum base_hook_type
{  NoBaseHookId
,  ListBaseHookId
,  SlistBaseHookId
,  RbTreeBaseHookId
,  HashBaseHookId
,  AvlTreeBaseHookId
,  BsTreeBaseHookId
,  TreapTreeBaseHookId
,  AnyBaseHookId
};


template <class HookTags, unsigned int>
struct hook_tags_definer{};

template <class HookTags>
struct hook_tags_definer<HookTags, ListBaseHookId>
{  typedef HookTags default_list_hook;  };

template <class HookTags>
struct hook_tags_definer<HookTags, SlistBaseHookId>
{  typedef HookTags default_slist_hook;  };

template <class HookTags>
struct hook_tags_definer<HookTags, RbTreeBaseHookId>
{  typedef HookTags default_rbtree_hook;  };

template <class HookTags>
struct hook_tags_definer<HookTags, HashBaseHookId>
{  typedef HookTags default_hashtable_hook;  };

template <class HookTags>
struct hook_tags_definer<HookTags, AvlTreeBaseHookId>
{  typedef HookTags default_avltree_hook;  };

template <class HookTags>
struct hook_tags_definer<HookTags, BsTreeBaseHookId>
{  typedef HookTags default_bstree_hook;  };

template <class HookTags>
struct hook_tags_definer<HookTags, AnyBaseHookId>
{  typedef HookTags default_any_hook;  };

template
   < class NodeTraits
   , class Tag
   , link_mode_type LinkMode
   , base_hook_type BaseHookType
   >
struct hooktags_impl
{
   static const link_mode_type link_mode = LinkMode;
   typedef Tag tag;
   typedef NodeTraits node_traits;
   static const bool is_base_hook = !detail::is_same<Tag, member_tag>::value;
   static const bool safemode_or_autounlink = is_safe_autounlink<link_mode>::value;
   static const unsigned int type = BaseHookType;
};

/// @endcond

template
   < boost::intrusive::algo_types Algo
   , class NodeTraits
   , class Tag
   , link_mode_type LinkMode
   , base_hook_type BaseHookType
   >
class generic_hook
   /// @cond
   //If the hook is a base hook, derive generic hook from node_holder
   //so that a unique base class is created to convert from the node
   //to the type. This mechanism will be used by bhtraits.
   //
   //If the hook is a member hook, generic hook will directly derive
   //from the hook.
   : public detail::if_c
      < detail::is_same<Tag, member_tag>::value
      , typename NodeTraits::node
      , node_holder<typename NodeTraits::node, Tag, BaseHookType>
      >::type
   //If this is the a default-tagged base hook derive from a class that
   //will define an special internal typedef. Containers will be able to detect this
   //special typedef and obtain generic_hook's internal types in order to deduce
   //value_traits for this hook.
   , public hook_tags_definer
      < generic_hook<Algo, NodeTraits, Tag, LinkMode, BaseHookType>
      , detail::is_same<Tag, dft_tag>::value ? BaseHookType : NoBaseHookId>
   /// @endcond
{
   /// @cond
   typedef typename get_algo<Algo, NodeTraits>::type  node_algorithms;
   typedef typename node_algorithms::node             node;
   typedef typename node_algorithms::node_ptr         node_ptr;
   typedef typename node_algorithms::const_node_ptr   const_node_ptr;

   public:

   typedef hooktags_impl
      < NodeTraits
      , Tag, LinkMode, BaseHookType>                  hooktags;

   BOOST_INTRUSIVE_FORCEINLINE node_ptr this_ptr() BOOST_NOEXCEPT
   {  return pointer_traits<node_ptr>::pointer_to(static_cast<node&>(*this)); }

   BOOST_INTRUSIVE_FORCEINLINE const_node_ptr this_ptr() const BOOST_NOEXCEPT
   {  return pointer_traits<const_node_ptr>::pointer_to(static_cast<const node&>(*this)); }

   public:
   /// @endcond

   BOOST_INTRUSIVE_FORCEINLINE generic_hook() BOOST_NOEXCEPT
   {
      if(hooktags::safemode_or_autounlink){
         node_algorithms::init(this->this_ptr());
      }
   }

   BOOST_INTRUSIVE_FORCEINLINE generic_hook(const generic_hook& ) BOOST_NOEXCEPT
   {
      if(hooktags::safemode_or_autounlink){
         node_algorithms::init(this->this_ptr());
      }
   }

   BOOST_INTRUSIVE_FORCEINLINE generic_hook& operator=(const generic_hook& ) BOOST_NOEXCEPT
   {  return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE ~generic_hook()
   {
      destructor_impl
         (*this, detail::link_dispatch<hooktags::link_mode>());
   }

   BOOST_INTRUSIVE_FORCEINLINE void swap_nodes(generic_hook &other) BOOST_NOEXCEPT
   {
      node_algorithms::swap_nodes
         (this->this_ptr(), other.this_ptr());
   }

   BOOST_INTRUSIVE_FORCEINLINE bool is_linked() const BOOST_NOEXCEPT
   {
      //is_linked() can be only used in safe-mode or auto-unlink
      BOOST_STATIC_ASSERT(( hooktags::safemode_or_autounlink ));
      return !node_algorithms::unique(this->this_ptr());
   }

   BOOST_INTRUSIVE_FORCEINLINE void unlink() BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT(( (int)hooktags::link_mode == (int)auto_unlink ));
      node_ptr n(this->this_ptr());
      if(!node_algorithms::inited(n)){
         node_algorithms::unlink(n);
         node_algorithms::init(n);
      }
   }
};

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_GENERIC_HOOK_HPP

/* generic_hook.hpp
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
*/