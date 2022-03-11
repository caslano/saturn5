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
void destructor_impl(Hook &hook, detail::link_dispatch<safe_link>)
{  //If this assertion raises, you might have destroyed an object
   //while it was still inserted in a container that is alive.
   //If so, remove the object from the container before destroying it.
   (void)hook; BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT(!hook.is_linked());
}

template<class Hook>
void destructor_impl(Hook &hook, detail::link_dispatch<auto_unlink>)
{  hook.unlink();  }

template<class Hook>
void destructor_impl(Hook &, detail::link_dispatch<normal_link>)
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

   BOOST_INTRUSIVE_FORCEINLINE node_ptr this_ptr()
   {  return pointer_traits<node_ptr>::pointer_to(static_cast<node&>(*this)); }

   BOOST_INTRUSIVE_FORCEINLINE const_node_ptr this_ptr() const
   {  return pointer_traits<const_node_ptr>::pointer_to(static_cast<const node&>(*this)); }

   public:
   /// @endcond

   BOOST_INTRUSIVE_FORCEINLINE generic_hook()
   {
      if(hooktags::safemode_or_autounlink){
         node_algorithms::init(this->this_ptr());
      }
   }

   BOOST_INTRUSIVE_FORCEINLINE generic_hook(const generic_hook& )
   {
      if(hooktags::safemode_or_autounlink){
         node_algorithms::init(this->this_ptr());
      }
   }

   BOOST_INTRUSIVE_FORCEINLINE generic_hook& operator=(const generic_hook& )
   {  return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE ~generic_hook()
   {
      destructor_impl
         (*this, detail::link_dispatch<hooktags::link_mode>());
   }

   BOOST_INTRUSIVE_FORCEINLINE void swap_nodes(generic_hook &other)
   {
      node_algorithms::swap_nodes
         (this->this_ptr(), other.this_ptr());
   }

   BOOST_INTRUSIVE_FORCEINLINE bool is_linked() const
   {
      //is_linked() can be only used in safe-mode or auto-unlink
      BOOST_STATIC_ASSERT(( hooktags::safemode_or_autounlink ));
      return !node_algorithms::unique(this->this_ptr());
   }

   BOOST_INTRUSIVE_FORCEINLINE void unlink()
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