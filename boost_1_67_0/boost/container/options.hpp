/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2013-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_OPTIONS_HPP
#define BOOST_CONTAINER_OPTIONS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/intrusive/pack_options.hpp>
#include <boost/static_assert.hpp>

namespace boost {
namespace container {

////////////////////////////////////////////////////////////////
//
//
//       OPTIONS FOR ASSOCIATIVE TREE-BASED CONTAINERS
//
//
////////////////////////////////////////////////////////////////

//! Enumeration used to configure ordered associative containers
//! with a concrete tree implementation.
enum tree_type_enum
{
   red_black_tree,
   avl_tree,
   scapegoat_tree,
   splay_tree
};

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<tree_type_enum TreeType, bool OptimizeSize>
struct tree_opt
{
   static const boost::container::tree_type_enum tree_type = TreeType;
   static const bool optimize_size = OptimizeSize;
};

typedef tree_opt<red_black_tree, true> tree_assoc_defaults;

#endif   //!defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

//!This option setter specifies the underlying tree type
//!(red-black, AVL, Scapegoat or Splay) for ordered associative containers
BOOST_INTRUSIVE_OPTION_CONSTANT(tree_type, tree_type_enum, TreeType, tree_type)

//!This option setter specifies if node size is optimized
//!storing rebalancing data masked into pointers for ordered associative containers
BOOST_INTRUSIVE_OPTION_CONSTANT(optimize_size, bool, Enabled, optimize_size)

//! Helper metafunction to combine options into a single type to be used
//! by \c boost::container::set, \c boost::container::multiset
//! \c boost::container::map and \c boost::container::multimap.
//! Supported options are: \c boost::container::optimize_size and \c boost::container::tree_type
#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED) || defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct tree_assoc_options
{
   /// @cond
   typedef typename ::boost::intrusive::pack_options
      < tree_assoc_defaults,
      #if !defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;
   typedef tree_opt<packed_options::tree_type, packed_options::optimize_size> implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

//! Helper alias metafunction to combine options into a single type to be used
//! by tree-based associative containers
template<class ...Options>
using tree_assoc_options_t = typename boost::container::tree_assoc_options<Options...>::type;

#endif


////////////////////////////////////////////////////////////////
//
//
//       OPTIONS FOR ASSOCIATIVE HASH-BASED CONTAINERS
//
//
////////////////////////////////////////////////////////////////

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<bool StoreHash>
struct hash_opt
{
   static const bool store_hash = StoreHash;
};

typedef hash_opt<false> hash_assoc_defaults;

#endif   //!defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

//!This option setter specifies if node size is optimized
//!storing rebalancing data masked into pointers for ordered associative containers
BOOST_INTRUSIVE_OPTION_CONSTANT(store_hash, bool, Enabled, store_hash)

//! Helper metafunction to combine options into a single type to be used
//! by \c boost::container::hash_set, \c boost::container::hash_multiset
//! \c boost::container::hash_map and \c boost::container::hash_multimap.
//! Supported options are: \c boost::container::store_hash
#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED) || defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct hash_assoc_options
{
   /// @cond
   typedef typename ::boost::intrusive::pack_options
      < hash_assoc_defaults,
      #if !defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;
   typedef hash_opt<packed_options::store_hash> implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

//! Helper alias metafunction to combine options into a single type to be used
//! by hash-based associative containers
template<class ...Options>
using hash_assoc_options_t = typename boost::container::hash_assoc_options<Options...>::type;

#endif

////////////////////////////////////////////////////////////////
//
//
//          OPTIONS FOR VECTOR-BASED CONTAINERS
//
//
////////////////////////////////////////////////////////////////

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<class T, class Default>
struct default_if_void
{
   typedef T type;
};

template<class Default>
struct default_if_void<void, Default>
{
   typedef Default type;
};

#endif

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<class AllocTraits, class StoredSizeType>
struct get_stored_size_type_with_alloctraits
{
   typedef StoredSizeType type;
};

template<class AllocTraits>
struct get_stored_size_type_with_alloctraits<AllocTraits, void>
{
   typedef typename AllocTraits::size_type type;
};

template<class GrowthType, class StoredSizeType>
struct vector_opt
{
   typedef GrowthType      growth_factor_type;
   typedef StoredSizeType  stored_size_type;

   template<class AllocTraits>
   struct get_stored_size_type
      : get_stored_size_type_with_alloctraits<AllocTraits, StoredSizeType>
   {};
};

class default_next_capacity;

typedef vector_opt<void, void> vector_null_opt;

#else    //!defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

//!This growth factor argument specifies that the container should increase it's
//!capacity a 50% when existing capacity is exhausted.
struct growth_factor_50{};

//!This growth factor argument specifies that the container should increase it's
//!capacity a 60% when existing capacity is exhausted.
struct growth_factor_60{};

//!This growth factor argument specifies that the container should increase it's
//!capacity a 100% (doubling its capacity) when existing capacity is exhausted.
struct growth_factor_100{};

#endif   //!defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

//!This option setter specifies the growth factor strategy of the underlying vector.
//!
//!\tparam GrowthFactor A function object that has the following signature:<br/><br/>
//!`template<class SizeType>`<br/>
//!`SizeType operator()(SizeType cur_cap, SizeType add_min_cap, SizeType max_cap) const;`.<br/><br/>
//!`cur_cap` is the current capacity, `add_min_cap` is the minimum additional capacity
//!we want to achieve and `max_cap` is the maximum capacity that the allocator or other 
//!factors allow. The implementation should return a value between `cur_cap` + `add_min_cap`
//!and `max_cap`. `cur_cap` + `add_min_cap` is guaranteed not to overflow/wraparound,
//! but the implementation should handle wraparound produced by the growth factor.
//!
//!Predefined growth factors that can be passed as arguments to this option are:
//!\c boost::container::growth_factor_50
//!\c boost::container::growth_factor_60
//!\c boost::container::growth_factor_100
//!
//!If this option is not specified, a default will be used by the container.
BOOST_INTRUSIVE_OPTION_TYPE(growth_factor, GrowthFactor, GrowthFactor, growth_factor_type)

//!This option specifies the unsigned integer type that a user wants the container
//!to use to hold size-related information inside a container (e.g. current size, current capacity).
//!
//!\tparam StoredSizeType An unsigned integer type. It shall be smaller than than the size
//! of the size_type deduced from `allocator_traits<A>::size_type` or the same type.
//!
//!If the maximum capacity() to be used is limited, a user can try to use 8-bit, 16-bit 
//!(e.g. in 32-bit machines), or 32-bit size types (e.g. in a 64 bit machine) to see if some
//!memory can be saved for empty vectors. This could potentially performance benefits due to better
//!cache usage.
//!
//!Note that alignment requirements can disallow theoretical space savings. Example:
//!\c vector holds a pointer and two size types (for size and capacity), in a 32 bit machine
//!a 8 bit size type (total size: 4 byte pointer + 2 x 1 byte sizes = 6 bytes) 
//!will not save space when comparing two 16-bit size types because usually
//!a 32 bit alignment is required for vector and the size will be rounded to 8 bytes. In a 64-bit
//!machine a 16 bit size type does not usually save memory when comparing to a 32-bit size type.
//!Measure the size of the resulting container and do not assume a smaller \c stored_size
//!will always lead to a smaller sizeof(container).
//!
//!If a user tries to insert more elements than representable by \c stored_size, vector
//!will throw a length_error.
//!
//!If this option is not specified, `allocator_traits<A>::size_type` (usually std::size_t) will
//!be used to store size-related information inside the container.
BOOST_INTRUSIVE_OPTION_TYPE(stored_size, StoredSizeType, StoredSizeType, stored_size_type)

//! Helper metafunction to combine options into a single type to be used
//! by \c boost::container::vector.
//! Supported options are: \c boost::container::growth_factor and \c boost::container::stored_size
#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED) || defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct vector_options
{
   /// @cond
   typedef typename ::boost::intrusive::pack_options
      < vector_null_opt,
      #if !defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;
   typedef vector_opt< typename packed_options::growth_factor_type
                     , typename packed_options::stored_size_type> implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

//! Helper alias metafunction to combine options into a single type to be used
//! by \c boost::container::vector.
//! Supported options are: \c boost::container::growth_factor and \c boost::container::stored_size
template<class ...Options>
using vector_options_t = typename boost::container::vector_options<Options...>::type;

#endif

////////////////////////////////////////////////////////////////
//
//
//          OPTIONS FOR SMALL-VECTOR CONTAINER
//
//
////////////////////////////////////////////////////////////////

//! This option specifies the desired alignment for the value_type stored
//! in the container.
//! A value zero represents the natural alignment.
//!
//!\tparam Alignment An unsigned integer value. Must be power of two.
BOOST_INTRUSIVE_OPTION_CONSTANT(inplace_alignment, std::size_t, Alignment, inplace_alignment)

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<class GrowthType, std::size_t InplaceAlignment>
struct small_vector_opt
{
   typedef GrowthType      growth_factor_type;
   static const std::size_t inplace_alignment = InplaceAlignment;
};

typedef small_vector_opt<void, 0u> small_vector_null_opt;

#endif    //!defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

//! Helper metafunction to combine options into a single type to be used
//! by \c boost::container::small_vector.
//! Supported options are: \c boost::container::growth_factor and \c boost::container::inplace_alignment
#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED) || defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct small_vector_options
{
   /// @cond
   typedef typename ::boost::intrusive::pack_options
      < small_vector_null_opt,
      #if !defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;
   typedef small_vector_opt< typename packed_options::growth_factor_type
                           , packed_options::inplace_alignment> implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

//! Helper alias metafunction to combine options into a single type to be used
//! by \c boost::container::small_vector.
//! Supported options are: \c boost::container::growth_factor and \c boost::container::stored_size
template<class ...Options>
using small_vector_options_t = typename boost::container::small_vector_options<Options...>::type;

#endif


////////////////////////////////////////////////////////////////
//
//
//          OPTIONS FOR STATIC-VECTOR CONTAINER
//
//
////////////////////////////////////////////////////////////////

//!This option specifies if the container will throw if in
//!the static capacity is not sufficient to hold the required
//!values. If false is specified, insufficient capacity will
//!lead to BOOST_ASSERT, and if this assertion returns, to undefined behaviour,
//!which potentially can lead to better static_vector performance.
//!The default value is true.
//!
//!\tparam ThrowOnExhaustion A boolean value. True if throw is required.
BOOST_INTRUSIVE_OPTION_CONSTANT(throw_on_overflow, bool, ThrowOnOverflow, throw_on_overflow)

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<bool ThrowOnOverflow, std::size_t InplaceAlignment>
struct static_vector_opt
{
   static const bool throw_on_overflow = ThrowOnOverflow;
   static const std::size_t inplace_alignment = InplaceAlignment;
};

typedef static_vector_opt<true, 0u> static_vector_null_opt;

#endif    //!defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

//! Helper metafunction to combine options into a single type to be used
//! by \c boost::container::static_vector.
//! Supported options are: \c boost::container::throw_on_overflow and \c boost::container::inplace_alignment
#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED) || defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct static_vector_options
{
   /// @cond
   typedef typename ::boost::intrusive::pack_options
      < static_vector_null_opt,
      #if !defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;
   typedef static_vector_opt< packed_options::throw_on_overflow
                            , packed_options::inplace_alignment> implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

//! Helper alias metafunction to combine options into a single type to be used
//! by \c boost::container::static_vector.
//! Supported options are: \c boost::container::growth_factor and \c boost::container::stored_size
template<class ...Options>
using static_vector_options_t = typename boost::container::static_vector_options<Options...>::type;

#endif


////////////////////////////////////////////////////////////////
//
//
//          OPTIONS FOR DEQUE-BASED CONTAINERS
//
//
////////////////////////////////////////////////////////////////

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<std::size_t BlockBytes, std::size_t BlockSize>
struct deque_opt
{
   static const std::size_t block_bytes = BlockBytes;
   static const std::size_t block_size  = BlockSize;
   BOOST_STATIC_ASSERT_MSG(!(block_bytes && block_size), "block_bytes and block_size can't be specified at the same time");
};

typedef deque_opt<0u, 0u> deque_null_opt;

#endif

//! Helper metafunction to combine options into a single type to be used
//! by \c boost::container::deque.
//! Supported options are: \c boost::container::block_bytes
#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED) || defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct deque_options
{
   /// @cond
   typedef typename ::boost::intrusive::pack_options
      < deque_null_opt,
      #if !defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;
   typedef deque_opt< packed_options::block_bytes, packed_options::block_size > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

//! Helper alias metafunction to combine options into a single type to be used
//! by \c boost::container::deque.
//! Supported options are: \c boost::container::block_bytes
template<class ...Options>
using deque_options_t = typename boost::container::deque_options<Options...>::type;

#endif

//!This option specifies the maximum size of a block in bytes: this delimites the number of contiguous elements
//!that will be allocated by deque as min(1u, BlockBytes/sizeof(value_type))
//!A value zero represents the default value.
//!
//!\tparam BlockBytes An unsigned integer value.
BOOST_INTRUSIVE_OPTION_CONSTANT(block_bytes, std::size_t, BlockBytes, block_bytes)

//!This option specifies the size of a block, delimites the number of contiguous elements
//!that will be allocated by deque as BlockSize.
//!A value zero represents the default value.
//!
//!\tparam BlockBytes An unsigned integer value.
BOOST_INTRUSIVE_OPTION_CONSTANT(block_size, std::size_t, BlockSize, block_size)

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_OPTIONS_HPP

/* options.hpp
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
*/