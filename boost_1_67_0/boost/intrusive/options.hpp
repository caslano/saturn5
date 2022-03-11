/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_OPTIONS_HPP
#define BOOST_INTRUSIVE_OPTIONS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/pack_options.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

struct empty
{};

template<class Functor>
struct fhtraits;

template<class T, class Hook, Hook T::* P>
struct mhtraits;

struct dft_tag;
struct member_tag;

template<class SupposedValueTraits>
struct is_default_hook_tag;

#endif   //#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

//!This option setter specifies if the intrusive
//!container stores its size as a member to
//!obtain constant-time size() member.
BOOST_INTRUSIVE_OPTION_CONSTANT(constant_time_size, bool, Enabled, constant_time_size)

//!This option setter specifies a container header holder type
BOOST_INTRUSIVE_OPTION_TYPE(header_holder_type, HeaderHolder, HeaderHolder, header_holder_type)

//!This option setter specifies the type that
//!the container will use to store its size.
BOOST_INTRUSIVE_OPTION_TYPE(size_type, SizeType, SizeType, size_type)

//!This option setter specifies the strict weak ordering
//!comparison functor for the value type
BOOST_INTRUSIVE_OPTION_TYPE(compare, Compare, Compare, compare)

//!This option setter specifies a function object
//!that specifies the type of the key of an associative
//!container and an operator to obtain it from a value type.
//!
//!This function object must the define a `type` member typedef and
//!a member with signature `type [const&] operator()(const value_type &) const`
//!that will return the key from a value_type of an associative container
BOOST_INTRUSIVE_OPTION_TYPE(key_of_value, KeyOfValue, KeyOfValue, key_of_value)

//!This option setter specifies a function object
//!that specifies the type of the priority of a treap
//!container and an operator to obtain it from a value type.
//!
//!This function object must the define a `type` member typedef and
//!a member with signature `type [const&] operator()(const value_type &) const`
//!that will return the priority from a value_type of a treap container
BOOST_INTRUSIVE_OPTION_TYPE(priority_of_value, PrioOfValue, PrioOfValue, priority_of_value)

//!This option setter for scapegoat containers specifies if
//!the intrusive scapegoat container should use a non-variable
//!alpha value that does not need floating-point operations.
//!
//!If activated, the fixed alpha value is 1/sqrt(2). This
//!option also saves some space in the container since
//!the alpha value and some additional data does not need
//!to be stored in the container.
//!
//!If the user only needs an alpha value near 1/sqrt(2), this
//!option also improves performance since avoids logarithm
//!and division operations when rebalancing the tree.
BOOST_INTRUSIVE_OPTION_CONSTANT(floating_point, bool, Enabled, floating_point)

//!This option setter specifies the equality
//!functor for the value type
BOOST_INTRUSIVE_OPTION_TYPE(equal, Equal, Equal, equal)

//!This option setter specifies the priority comparison
//!functor for the value type
BOOST_INTRUSIVE_OPTION_TYPE(priority, Priority, Priority, priority)

//!This option setter specifies the hash
//!functor for the value type
BOOST_INTRUSIVE_OPTION_TYPE(hash, Hash, Hash, hash)

//!This option setter specifies the relationship between the type
//!to be managed by the container (the value type) and the node to be
//!used in the node algorithms. It also specifies the linking policy.
BOOST_INTRUSIVE_OPTION_TYPE(value_traits, ValueTraits, ValueTraits, proto_value_traits)

//#define BOOST_INTRUSIVE_COMMA ,
//#define BOOST_INTRUSIVE_LESS <
//#define BOOST_INTRUSIVE_MORE >
//BOOST_INTRUSIVE_OPTION_TYPE (member_hook, Parent BOOST_INTRUSIVE_COMMA class MemberHook BOOST_INTRUSIVE_COMMA MemberHook Parent::* PtrToMember , mhtraits BOOST_INTRUSIVE_LESS Parent BOOST_INTRUSIVE_COMMA MemberHook BOOST_INTRUSIVE_COMMA PtrToMember BOOST_INTRUSIVE_MORE , proto_value_traits)
//template< class Parent , class MemberHook , MemberHook Parent::* PtrToMember>
//struct member_hook {
//   template<class Base> struct pack : Base {
//      typedef mhtraits < Parent , MemberHook , PtrToMember > proto_value_traits;
//   };
//};
//
//#undef BOOST_INTRUSIVE_COMMA
//#undef BOOST_INTRUSIVE_LESS
//#undef BOOST_INTRUSIVE_MORE

//!This option setter specifies the member hook the
//!container must use.
template< typename Parent
        , typename MemberHook
        , MemberHook Parent::* PtrToMember>
struct member_hook
{
// @cond
//   typedef typename MemberHook::hooktags::node_traits node_traits;
//   typedef typename node_traits::node node_type;
//   typedef node_type Parent::* Ptr2MemNode;
//   typedef mhtraits
//      < Parent
//      , node_traits
//      //This cast is really ugly but necessary to reduce template bloat.
//      //Since we control the layout between the hook and the node, and there is
//      //always single inheritance, the offset of the node is exactly the offset of
//      //the hook. Since the node type is shared between all member hooks, this saves
//      //quite a lot of symbol stuff.
//      , (Ptr2MemNode)PtrToMember
//      , MemberHook::hooktags::link_mode> member_value_traits;
   typedef mhtraits <Parent, MemberHook, PtrToMember> member_value_traits;
   template<class Base>
   struct pack : Base
   {
      typedef member_value_traits proto_value_traits;
   };
/// @endcond
};

//!This option setter specifies the function object that will
//!be used to convert between values to be inserted in a container
//!and the hook to be used for that purpose.
BOOST_INTRUSIVE_OPTION_TYPE(function_hook, Functor, fhtraits<Functor>, proto_value_traits)

//!This option setter specifies that the container
//!must use the specified base hook
BOOST_INTRUSIVE_OPTION_TYPE(base_hook, BaseHook, BaseHook, proto_value_traits)

//!This option setter specifies the type of
//!a void pointer. This will instruct the hook
//!to use this type of pointer instead of the
//!default one
BOOST_INTRUSIVE_OPTION_TYPE(void_pointer, VoidPointer, VoidPointer, void_pointer)

//!This option setter specifies the type of
//!the tag of a base hook. A type cannot have two
//!base hooks of the same type, so a tag can be used
//!to differentiate two base hooks with otherwise same type
BOOST_INTRUSIVE_OPTION_TYPE(tag, Tag, Tag, tag)

//!This option setter specifies the link mode
//!(normal_link, safe_link or auto_unlink)
BOOST_INTRUSIVE_OPTION_CONSTANT(link_mode, link_mode_type, LinkType, link_mode)

//!This option setter specifies if the hook
//!should be optimized for size instead of for speed.
BOOST_INTRUSIVE_OPTION_CONSTANT(optimize_size, bool, Enabled, optimize_size)

//!This option setter specifies if the slist container should
//!use a linear implementation instead of a circular one.
BOOST_INTRUSIVE_OPTION_CONSTANT(linear, bool, Enabled, linear)

//!If true, slist also stores a pointer to the last element of the singly linked list.
//!This allows O(1) swap and splice_after(iterator, slist &) for circular slists and makes
//!possible new functions like push_back(reference) and back().
BOOST_INTRUSIVE_OPTION_CONSTANT(cache_last, bool, Enabled, cache_last)

//!This option setter specifies the bucket traits
//!class for unordered associative containers. When this option is specified,
//!instead of using the default bucket traits, a user defined holder will be defined
BOOST_INTRUSIVE_OPTION_TYPE(bucket_traits, BucketTraits, BucketTraits, bucket_traits)

//!This option setter specifies if the unordered hook
//!should offer room to store the hash value.
//!Storing the hash in the hook will speed up rehashing
//!processes in applications where rehashing is frequent,
//!rehashing might throw or the value is heavy to hash.
BOOST_INTRUSIVE_OPTION_CONSTANT(store_hash, bool, Enabled, store_hash)

//!This option setter specifies if the unordered hook
//!should offer room to store another link to another node
//!with the same key.
//!Storing this link will speed up lookups and insertions on
//!unordered_multiset containers with a great number of elements
//!with the same key.
BOOST_INTRUSIVE_OPTION_CONSTANT(optimize_multikey, bool, Enabled, optimize_multikey)

//!This option setter specifies if the bucket array will be always power of two.
//!This allows using masks instead of the default modulo operation to determine
//!the bucket number from the hash value, leading to better performance.
//!In debug mode, if power of two buckets mode is activated, the bucket length
//!will be checked with assertions.
BOOST_INTRUSIVE_OPTION_CONSTANT(power_2_buckets, bool, Enabled, power_2_buckets)

//!This option setter specifies if the container will cache a pointer to the first
//!non-empty bucket so that begin() is always constant-time.
//!This is specially helpful when we can have containers with a few elements
//!but with big bucket arrays (that is, hashtables with low load factors).
BOOST_INTRUSIVE_OPTION_CONSTANT(cache_begin, bool, Enabled, cache_begin)

//!This option setter specifies if the container will compare the hash value
//!before comparing objects. This option can't be specified if store_hash<>
//!is not true.
//!This is specially helpful when we have containers with a high load factor.
//!and the comparison function is much more expensive that comparing already
//!stored hash values.
BOOST_INTRUSIVE_OPTION_CONSTANT(compare_hash, bool, Enabled, compare_hash)

//!This option setter specifies if the hash container will use incremental
//!hashing. With incremental hashing the cost of hash table expansion is spread
//!out across each hash table insertion operation, as opposed to be incurred all at once.
//!Therefore linear hashing is well suited for interactive applications or real-time
//!appplications where the worst-case insertion time of non-incremental hash containers
//!(rehashing the whole bucket array) is not admisible.
BOOST_INTRUSIVE_OPTION_CONSTANT(incremental, bool, Enabled, incremental)

/// @cond

struct hook_defaults
{
   typedef void* void_pointer;
   static const link_mode_type link_mode = safe_link;
   typedef dft_tag tag;
   static const bool optimize_size = false;
   static const bool store_hash = false;
   static const bool linear = false;
   static const bool optimize_multikey = false;
};

/// @endcond

}  //namespace intrusive {
}  //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTRUSIVE_OPTIONS_HPP

/* options.hpp
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
*/