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
1O87l/PtUWP2n15zjb4vk0rmkDbNSHuvM9ZPp/Gx/V7d1Nh2ZuS5cn1loAdysnz+MWaf+jIyVIZ3p0V8467hmrk+4dzbwz43A9RX7qty/fRAnrPSfcwd6riBXGcEIeHnymeFP8XJ8WVTvoYqXvXbfILmi4xX3SX0w9FuJt9VnPXByo3vgxEfqA/D9We+4jq/LFeL7PPUJ4n1CBK+E4+vPO67MuLh8+Nvo4eHEn+ev5aiQWQuCrSVjSafV14vZdN8ZwrPe24aqY50DkLqd9jJbQHzw6f6bbRJeAKaxnVaJTw8cCRv8K18GZ3qnsnKkTxnq3uRE+mHhcLTGIjsvXafhMcHotqpbu5c/vDXmVwsPNcFRgcOkf5+vbeW2Wnbay4s5wFKdw17epQnaIMysz+4byQjv62vFd6J9Hqula+H8s27LXxGYl9thx9L3uVuHTOCLxPr4OM2QvUkUr9eTjrzQi3M1dUzd32K8z3a5UN84oaIzuAjaLSFp4+F4bwlzyB/ne/lqb6AKYRfFd4UqWcq4Ra5fgGlCjm9qEMPvfciMiP+zevyYqndtRZqP03pFZaDA1BFXW1jdWVVg+Gn3y88vui4pGOV3sc6LkXGKu5RXYugY84GHfzehVzoHWgQ8tZ9MWbMOa26trzGiR27fd/0mas9/pPQ1Qzbc0LlueZ45evXvXLt787f+Nf23NC0dt1RHXhIeOYxlqI72vd/lbixjDWDyFfKza/e16N+UubjHavuK8/XRcYMpOTzH3G+3CORm46eBY3xa6H/LBsmsg/1/dyHSDjgiE+2oQePdOKsTvPZomsy/L43+3RsejjxQSqkADoYvl2rY/p0Um11kxP1DLH1Hek6XDeCnqo+JijTNt3H7LAAbzPgcHAgfM4dMWXSB5tRJn/c7SO8OTYfcORYn2M2fYLX+s6i4zn1kOtvsY5vPHNHS13b+4jKsI6HOWAO17kaqHWeYWfLu50hqjstEv+Q2885h/mFmc6f8c49hHFoknsQPrrHOA/wHlOSHt737St55JVanJoTzGStV+/MYZlnpoayMoOpaVlpvVNLg+mZw1KHBVMyD82sypzPSrBuGbAU8Ud6Wmb3zEMyB2fOTR1C2kGsE8vIyg6kZgZ7pWYFQybHnMzDM+ektjyVlZaTOTLzMAQckTmC2FGZRZnjyLUXOAq+wfydR8JAIPO01JFZaaleXdHlkGVMS/ROcKLUfYcb8QEulnCm9fl/gVzr77/TnHun7NuoYdrxzsTP93xNM15krHZPog+607YDvHg/3z+4vRmvzmenrCHuCOcc9xz/OSDXeTq090wcIzwvuGVuIemI8+WmxulEX9WJl+X6R+jP6U45T6O1jCuDo/Si1qYX+t5gKZdlHPyctMs4Ws7yDDXWV94gsu50htIqZ5LXEtDaPlxt5eTMPPcux3wu5uhz8W3h/Qz6zTuTPhtvk7hTGB0PCz8vCf1S+9qryz+Munjv5xGb/Vf0WZidaN3hvj3z5N5WGz42gM7beI+7QWyz054Z+80rC1b3yjnqxu/sfeSJxLZcu406kQ2887Zfu4298z4Fxvmr8s1UDJ4KfUX/LofC9j/9/tLvyOIY+5+nvkcAqeB4sBt4DpgGzgYzwLfBgoC+8+s3TrHKztJv1DLdi6sczAHngIXgJeAYcAF4MlgDloK14HSwHpwLNoEN4DfBFnAtuBy8C7wR/Ap4O/gIeLfybQC/BW4HN4HPg0+Ar4LfAXeDW8C9ascNUfjvghlgK5gPPg2OAHeAJ4FbwRLwB+B8cBu4QO2tteCPwYXgT8DrwWfB5WrXvQF8DrwJ3A7eDf4cXKfyHwXXg1vA+8Bt4AbwBfBr4B/BB8C3wa8=
*/