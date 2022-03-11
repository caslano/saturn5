/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_HOOK_TRAITS_HPP
#define BOOST_INTRUSIVE_DETAIL_HOOK_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/parent_from_member.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/intrusive/detail/node_holder.hpp>

namespace boost {
namespace intrusive {

template<class T, class NodePtr, class Tag, unsigned int Type>
struct bhtraits_base
{
   public:
   typedef NodePtr                                                   node_ptr;
   typedef typename pointer_traits<node_ptr>::element_type           node;
   typedef node_holder<node, Tag, Type>                              node_holder_type;
   typedef T                                                         value_type;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const node>::type                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<T>::type                               pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const T>::type                         const_pointer;
   //typedef typename pointer_traits<pointer>::reference               reference;
   //typedef typename pointer_traits<const_pointer>::reference         const_reference;
   typedef T &                                                       reference;
   typedef const T &                                                 const_reference;
   typedef node_holder_type &                                        node_holder_reference;
   typedef const node_holder_type &                                  const_node_holder_reference;
   typedef node&                                                     node_reference;
   typedef const node &                                              const_node_reference;

   BOOST_INTRUSIVE_FORCEINLINE static pointer to_value_ptr(const node_ptr & n)
   {
      pointer p = pointer_traits<pointer>::pointer_to
         (static_cast<reference>(static_cast<node_holder_reference>(*n)));
      BOOST_ASSERT(!!p);
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_pointer to_value_ptr(const const_node_ptr & n)
   {
      const_pointer p = pointer_traits<const_pointer>::pointer_to
         (static_cast<const_reference>(static_cast<const_node_holder_reference>(*n)));
      BOOST_ASSERT(!!p);
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr to_node_ptr(reference value)
   {
      node_ptr p = pointer_traits<node_ptr>::pointer_to
         (static_cast<node_reference>(static_cast<node_holder_reference>(value)));
      BOOST_ASSERT(!!p);
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr(const_reference value)
   {
      const_node_ptr p = pointer_traits<const_node_ptr>::pointer_to
         (static_cast<const_node_reference>(static_cast<const_node_holder_reference>(value)));
      BOOST_ASSERT(!!p);
      return p;
   }
};

template<class T, class NodeTraits, link_mode_type LinkMode, class Tag, unsigned int Type>
struct bhtraits
   : public bhtraits_base<T, typename NodeTraits::node_ptr, Tag, Type>
{
   static const link_mode_type link_mode = LinkMode;
   typedef NodeTraits node_traits;
};


template<class T, class Hook, Hook T::* P>
struct mhtraits
{
   public:
   typedef Hook                                                      hook_type;
   typedef typename hook_type::hooktags::node_traits                 node_traits;
   typedef typename node_traits::node                                node;
   typedef T                                                         value_type;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<T>::type                               pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const T>::type                         const_pointer;
   typedef T &                                                       reference;
   typedef const T &                                                 const_reference;
   typedef node&                                                     node_reference;
   typedef const node &                                              const_node_reference;
   typedef hook_type&                                                hook_reference;
   typedef const hook_type &                                         const_hook_reference;

   static const link_mode_type link_mode = Hook::hooktags::link_mode;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr to_node_ptr(reference value)
   {
      return pointer_traits<node_ptr>::pointer_to
         (static_cast<node_reference>(static_cast<hook_reference>(value.*P)));
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr(const_reference value)
   {
      return pointer_traits<const_node_ptr>::pointer_to
         (static_cast<const_node_reference>(static_cast<const_hook_reference>(value.*P)));
   }

   BOOST_INTRUSIVE_FORCEINLINE static pointer to_value_ptr(const node_ptr & n)
   {
      return pointer_traits<pointer>::pointer_to
         (*detail::parent_from_member<T, Hook>
            (static_cast<Hook*>(boost::movelib::to_raw_pointer(n)), P));
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_pointer to_value_ptr(const const_node_ptr & n)
   {
      return pointer_traits<const_pointer>::pointer_to
         (*detail::parent_from_member<T, Hook>
            (static_cast<const Hook*>(boost::movelib::to_raw_pointer(n)), P));
   }
};


template<class Functor>
struct fhtraits
{
   public:
   typedef typename Functor::hook_type                               hook_type;
   typedef typename Functor::hook_ptr                                hook_ptr;
   typedef typename Functor::const_hook_ptr                          const_hook_ptr;
   typedef typename hook_type::hooktags::node_traits                 node_traits;
   typedef typename node_traits::node                                node;
   typedef typename Functor::value_type                              value_type;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<value_type>::type                      pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const value_type>::type                const_pointer;
   typedef value_type &                                              reference;
   typedef const value_type &                                        const_reference;
   static const link_mode_type link_mode = hook_type::hooktags::link_mode;

   static node_ptr to_node_ptr(reference value)
   {  return static_cast<node*>(boost::movelib::to_raw_pointer(Functor::to_hook_ptr(value)));  }

   static const_node_ptr to_node_ptr(const_reference value)
   {  return static_cast<const node*>(boost::movelib::to_raw_pointer(Functor::to_hook_ptr(value)));  }

   static pointer to_value_ptr(const node_ptr & n)
   {  return Functor::to_value_ptr(to_hook_ptr(n));  }

   static const_pointer to_value_ptr(const const_node_ptr & n)
   {  return Functor::to_value_ptr(to_hook_ptr(n));  }

   private:
   static hook_ptr to_hook_ptr(const node_ptr & n)
   {  return hook_ptr(&*static_cast<hook_type*>(&*n));  }

   static const_hook_ptr to_hook_ptr(const const_node_ptr & n)
   {  return const_hook_ptr(&*static_cast<const hook_type*>(&*n));  }
};


} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_HOOK_TRAITS_HPP

/* hook_traits.hpp
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
*/