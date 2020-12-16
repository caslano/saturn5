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
nwJmg1PBAWApOAo8GzwBnAZOBKeDZeClKr818i2o36g7wTzoMZX/itr0XwOHgK+Dp4BvgNPBv4FzwDfBFt37dpnuDXoH+D54P7gX/CH4kZ4B+jHYC3TgL3QBsAhMA4eA3cBRGj4MfBv+8eA/wGngHrBOrms7ufqNoN9iO/Vem6zzp/3hGwEOAU8Gh4ITwOHgJHAUeB14OHgzWAzeBh4FrgOPAR8GjwNfAk8EPwRPAjPI42SwJ1gCDgDHgdPBU8FLwEng1eBk8E7wLPBucAp4D1gKPgqeDX4LPB/cDl4A7gQvAl8Hy8CPwHIwh3rOAfuBFeAAsBI8CpwLTgEvAS8Ga8DZ4KVgI1gL3g9eBj4INoCPgIvAVnAJ+BJYIu0L+u9Y6K7qobkXcnf4hoE5eh/larvmgWeD+SqnOPIOA2ZYxrMbddy4SceNm/3xQd8dwHGW8YGwpPsNmAu+CB4G/g70eP6oevsnL0y9tp7LGXTQHijrPHaBgMZCM6B6iPPr2j3vbiU866Et0A7oVagInnWTAnH+JeaZdmuhzdA26EVIz6jzz6ebAcX6oZhn0PWHxkJ63pxx1hx80KvQe1DsmXJ7KV8LuBGKnBW3G3rxc5xLBsX6tjSBK6G10IPQNj3vbQ8Ye+ZbExQ55209lDszFOUXM/YG0oFylhtUDJVANVDxGf5ZbHHnr2U/rmeuIc88d60SWg6ZZ6u9aPG10TPUxOfGPDdtHdQKbYd2QTNmch1aCW2AtkEvQ3uh3Fns1QuVQjXQtbO6/Ha6fl2/rt//9+8/4v9fUz3nQNj+BzBPN3IQ7wBi+6+smlvOHFsZpvFLq5rmq039h8Y+AYVqw30McqFHoatJv/3CiE29vLKyTKYWO2WbIb3ObUR8tZuqFje1zWH9Uq6f5BxsO+/JSD+GedodhHcEmEfmYtbBbvCQ1LRg39T0YAjsl5qflZ6TmhfsmTlU/pvC8TjpIX9O5Ud5QlYf7l7gsovEluP78tdKuLc/532mhAPOCMqxlAaqROiPkZfpMlmcl+aVgD+CfcK582e3VD/vFuq9BtK5IM27bZ4+JLKvdCYiX+akNY8NJP6JV9fQycGBmUMQGkrL4dp84tdDz8rZhhW+jfXNbEfSe5SvMrbD91OPL73l1qxgps/7hsG7P7Yn8TXXPjXPL6xPsetT60WGPmEqmFun6pSk3Zz07erTMxe1r0+k9/WpCJ0vSvlk9Omyi6P16WLCpj6dSDiiT88GaafQgdOnPbH6pHm8F7Lr0+YQaUId65MnozDl09GnF9XOPVwFDYNWkH7jxdH6VN/cVDanro7xtTYpfSJ9orUkNv3x+fN9/vKKpuq62rLKqkb88y3rTSx5YKcrq+BR0GhZb2LNo6K8tqKqRtPY1i+RJtYWObemfF6j8BYYvAVR8nXtjtpsypjCj9S7v5Gmv6Yx/Tl+to/z0/lmPxtt3ddcuxLVprHrmvy2kzS5fnx0G5E39da5fm0L+KmXrqWJqbOpa7vVP2GoVmYIdOYg4uN1rVPPwt2d1LXd9j616tjuJPo0Rs/M8qj8S6trZSmZRcfs/OWLld+mZ7tjdGbbAdYZsVta+jjb0sdx6+CMuuabumLUyTyz8D01UvXUwvaAbqaMhWWmTjQ3VjWUcWZheVL6QFq/PYPSZ376eH2w8GPvr6kU9rbnzkjhCe1XOyObOL8sUffGjO7x4/BZyCiJaofwGrPO2MtKyjp3b5SUJX9vlJR1/t4oKevcvVFS1rl7I76+nEynJbKMv/D/b99LxFMnzdeoq6lbIa1NMRUcChaAx1P2Fl+38EBEp5ormsq05NG6ZZy5eaekWUIdurFnW55N55Ab+5zlw6sK4frcifg=
*/