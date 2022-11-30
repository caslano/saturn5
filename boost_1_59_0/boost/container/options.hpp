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

template<class GrowthType, class StoredSizeType>
struct devector_opt
   : vector_opt<GrowthType, StoredSizeType>
{};

typedef devector_opt<void, void> devector_null_opt;

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

//! Helper metafunction to combine options into a single type to be used
//! by \c boost::container::devector.
//! Supported options are: \c boost::container::growth_factor and \c boost::container::stored_size
#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED) || defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct devector_options
{
   /// @cond
   typedef typename ::boost::intrusive::pack_options
      < devector_null_opt,
      #if !defined(BOOST_CONTAINER_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;
   typedef devector_opt< typename packed_options::growth_factor_type
                       , typename packed_options::stored_size_type> implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

//! Helper alias metafunction to combine options into a single type to be used
//! by \c boost::container::devector.
//! Supported options are: \c boost::container::growth_factor and \c boost::container::stored_size
template<class ...Options>
using devector_options_t = typename boost::container::devector_options<Options...>::type;

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
+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
*/