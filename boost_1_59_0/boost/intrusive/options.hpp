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
+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
*/