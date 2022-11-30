// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_BASE_HPP
#define BOOST_MULTI_ARRAY_BASE_HPP

//
// base.hpp - some implementation base classes for from which
// functionality is acquired
//

#include "boost/multi_array/extent_range.hpp"
#include "boost/multi_array/extent_gen.hpp"
#include "boost/multi_array/index_range.hpp"
#include "boost/multi_array/index_gen.hpp"
#include "boost/multi_array/storage_order.hpp"
#include "boost/multi_array/types.hpp"
#include "boost/config.hpp"
#include "boost/multi_array/concept_checks.hpp" //for ignore_unused_...
#include "boost/mpl/eval_if.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/size_t.hpp"
#include "boost/iterator/reverse_iterator.hpp"
#include "boost/static_assert.hpp"
#include "boost/type.hpp"
#include "boost/assert.hpp"
#include <cstddef>
#include <memory>

namespace boost {

/////////////////////////////////////////////////////////////////////////
// class declarations
/////////////////////////////////////////////////////////////////////////

template<typename T, std::size_t NumDims,
  typename Allocator = std::allocator<T> >
class multi_array;

// This is a public interface for use by end users!
namespace multi_array_types {
  typedef boost::detail::multi_array::size_type size_type;
  typedef std::ptrdiff_t difference_type;
  typedef boost::detail::multi_array::index index;
  typedef detail::multi_array::index_range<index,size_type> index_range;
  typedef detail::multi_array::extent_range<index,size_type> extent_range;
  typedef detail::multi_array::index_gen<0,0> index_gen;
  typedef detail::multi_array::extent_gen<0> extent_gen;
}


// boost::extents and boost::indices are now a part of the public
// interface.  That way users don't necessarily have to create their 
// own objects.  On the other hand, one may not want the overhead of 
// object creation in small-memory environments.  Thus, the objects
// can be left undefined by defining BOOST_MULTI_ARRAY_NO_GENERATORS 
// before loading multi_array.hpp.
#ifndef BOOST_MULTI_ARRAY_NO_GENERATORS
namespace {
  multi_array_types::extent_gen extents;
  multi_array_types::index_gen indices;
}
#endif // BOOST_MULTI_ARRAY_NO_GENERATORS

namespace detail {
namespace multi_array {

template <typename T, std::size_t NumDims>
class sub_array;

template <typename T, std::size_t NumDims, typename TPtr = const T*>
class const_sub_array;

  template <typename T, typename TPtr, typename NumDims, typename Reference,
            typename IteratorCategory>
class array_iterator;

template <typename T, std::size_t NumDims, typename TPtr = const T*>
class const_multi_array_view;

template <typename T, std::size_t NumDims>
class multi_array_view;

/////////////////////////////////////////////////////////////////////////
// class interfaces
/////////////////////////////////////////////////////////////////////////

class multi_array_base {
public:
  typedef multi_array_types::size_type size_type;
  typedef multi_array_types::difference_type difference_type;
  typedef multi_array_types::index index;
  typedef multi_array_types::index_range index_range;
  typedef multi_array_types::extent_range extent_range;
  typedef multi_array_types::index_gen index_gen;
  typedef multi_array_types::extent_gen extent_gen;
};

//
// value_accessor_n
//  contains the routines for accessing elements from
//  N-dimensional views.
//
template<typename T, std::size_t NumDims>
class value_accessor_n : public multi_array_base {
  typedef multi_array_base super_type;
public:
  typedef typename super_type::index index;

  // 
  // public typedefs used by classes that inherit from this base
  //
  typedef T element;
  typedef boost::multi_array<T,NumDims-1> value_type;
  typedef sub_array<T,NumDims-1> reference;
  typedef const_sub_array<T,NumDims-1> const_reference;

protected:
  // used by array operator[] and iterators to get reference types.
  template <typename Reference, typename TPtr>
  Reference access(boost::type<Reference>,index idx,TPtr base,
                   const size_type* extents,
                   const index* strides,
                   const index* index_bases) const {

    BOOST_ASSERT(idx - index_bases[0] >= 0);
    BOOST_ASSERT(size_type(idx - index_bases[0]) < extents[0]);
    // return a sub_array<T,NDims-1> proxy object
    TPtr newbase = base + idx * strides[0];
    return Reference(newbase,extents+1,strides+1,index_bases+1);

  }

  value_accessor_n() { }
  ~value_accessor_n() { }
};



//
// value_accessor_one
//  contains the routines for accessing reference elements from
//  1-dimensional views.
//
template<typename T>
class value_accessor_one : public multi_array_base {
  typedef multi_array_base super_type;
public:
  typedef typename super_type::index index;
  //
  // public typedefs for use by classes that inherit it.
  //
  typedef T element;
  typedef T value_type;
  typedef T& reference;
  typedef T const& const_reference;

protected:
  // used by array operator[] and iterators to get reference types.
  template <typename Reference, typename TPtr>
  Reference access(boost::type<Reference>,index idx,TPtr base,
                   const size_type* extents,
                   const index* strides,
                   const index* index_bases) const {

    ignore_unused_variable_warning(index_bases);
    ignore_unused_variable_warning(extents);
    BOOST_ASSERT(idx - index_bases[0] >= 0);
    BOOST_ASSERT(size_type(idx - index_bases[0]) < extents[0]);
    return *(base + idx * strides[0]);
  }

  value_accessor_one() { }
  ~value_accessor_one() { }
};


/////////////////////////////////////////////////////////////////////////
// choose value accessor begins
//

template <typename T, std::size_t NumDims>
struct choose_value_accessor_n {
  typedef value_accessor_n<T,NumDims> type;
};

template <typename T>
struct choose_value_accessor_one {
  typedef value_accessor_one<T> type;
};

template <typename T, typename NumDims>
struct value_accessor_generator {
    BOOST_STATIC_CONSTANT(std::size_t, dimensionality = NumDims::value);
    
  typedef typename
  mpl::eval_if_c<(dimensionality == 1),
                  choose_value_accessor_one<T>,
                  choose_value_accessor_n<T,dimensionality>
  >::type type;
};

template <class T, class NumDims>
struct associated_types
  : value_accessor_generator<T,NumDims>::type
{};

//
// choose value accessor ends
/////////////////////////////////////////////////////////////////////////

// Due to some imprecision in the C++ Standard, 
// MSVC 2010 is broken in debug mode: it requires
// that an Output Iterator have output_iterator_tag in its iterator_category if 
// that iterator is not bidirectional_iterator or random_access_iterator.
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1600)
struct mutable_iterator_tag
 : boost::random_access_traversal_tag, std::input_iterator_tag
{
  operator std::output_iterator_tag() const {
    return std::output_iterator_tag();
  }
};
#endif

////////////////////////////////////////////////////////////////////////
// multi_array_base
////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t NumDims>
class multi_array_impl_base
  :
      public value_accessor_generator<T,mpl::size_t<NumDims> >::type
{
  typedef associated_types<T,mpl::size_t<NumDims> > types;
public:
  typedef typename types::index index;
  typedef typename types::size_type size_type;
  typedef typename types::element element;
  typedef typename types::index_range index_range;
  typedef typename types::value_type value_type;
  typedef typename types::reference reference;
  typedef typename types::const_reference const_reference;

  template <std::size_t NDims>
  struct subarray {
    typedef boost::detail::multi_array::sub_array<T,NDims> type;
  };

  template <std::size_t NDims>
  struct const_subarray {
    typedef boost::detail::multi_array::const_sub_array<T,NDims> type;
  };

  template <std::size_t NDims>
  struct array_view {
    typedef boost::detail::multi_array::multi_array_view<T,NDims> type;
  };

  template <std::size_t NDims>
  struct const_array_view {
  public:
    typedef boost::detail::multi_array::const_multi_array_view<T,NDims> type;
  };

  //
  // iterator support
  //
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1600)
  // Deal with VC 2010 output_iterator_tag requirement
  typedef array_iterator<T,T*,mpl::size_t<NumDims>,reference,
                         mutable_iterator_tag> iterator;
#else
  typedef array_iterator<T,T*,mpl::size_t<NumDims>,reference,
                         boost::random_access_traversal_tag> iterator;
#endif
  typedef array_iterator<T,T const*,mpl::size_t<NumDims>,const_reference,
                         boost::random_access_traversal_tag> const_iterator;

  typedef ::boost::reverse_iterator<iterator> reverse_iterator;
  typedef ::boost::reverse_iterator<const_iterator> const_reverse_iterator;

  BOOST_STATIC_CONSTANT(std::size_t, dimensionality = NumDims);
protected:

  multi_array_impl_base() { }
  ~multi_array_impl_base() { }

  // Used by operator() in our array classes
  template <typename Reference, typename IndexList, typename TPtr>
  Reference access_element(boost::type<Reference>,
                           const IndexList& indices,
                           TPtr base,
                           const size_type* extents,
                           const index* strides,
                           const index* index_bases) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    ignore_unused_variable_warning(index_bases);
    ignore_unused_variable_warning(extents);
#if !defined(NDEBUG) && !defined(BOOST_DISABLE_ASSERTS)
    for (size_type i = 0; i != NumDims; ++i) {
      BOOST_ASSERT(indices[i] - index_bases[i] >= 0);
      BOOST_ASSERT(size_type(indices[i] - index_bases[i]) < extents[i]);
    }
#endif

    index offset = 0;
    {
      typename IndexList::const_iterator i = indices.begin();
      size_type n = 0; 
      while (n != NumDims) {
        offset += (*i) * strides[n];
        ++n;
        ++i;
      }
    }
    return base[offset];
  }

  template <typename StrideList, typename ExtentList>
  void compute_strides(StrideList& stride_list, ExtentList& extent_list,
                       const general_storage_order<NumDims>& storage)
  {
    // invariant: stride = the stride for dimension n
    index stride = 1;
    for (size_type n = 0; n != NumDims; ++n) {
      index stride_sign = +1;
      
      if (!storage.ascending(storage.ordering(n)))
        stride_sign = -1;
      
      // The stride for this dimension is the product of the
      // lengths of the ranks minor to it.
      stride_list[storage.ordering(n)] = stride * stride_sign;
      
      stride *= extent_list[storage.ordering(n)];
    } 
  }

  // This calculates the offset to the array base pointer due to:
  // 1. dimensions stored in descending order
  // 2. non-zero dimension index bases
  template <typename StrideList, typename ExtentList, typename BaseList>
  index
  calculate_origin_offset(const StrideList& stride_list,
                          const ExtentList& extent_list,
                          const general_storage_order<NumDims>& storage,
                          const BaseList& index_base_list)
  {
    return
      calculate_descending_dimension_offset(stride_list,extent_list,
                                            storage) +
      calculate_indexing_offset(stride_list,index_base_list);
  }

  // This calculates the offset added to the base pointer that are
  // caused by descending dimensions
  template <typename StrideList, typename ExtentList>
  index
  calculate_descending_dimension_offset(const StrideList& stride_list,
                                const ExtentList& extent_list,
                                const general_storage_order<NumDims>& storage)
  {
    index offset = 0;
    if (!storage.all_dims_ascending()) 
      for (size_type n = 0; n != NumDims; ++n)
        if (!storage.ascending(n))
          offset -= (extent_list[n] - 1) * stride_list[n];

    return offset;
  }

  // This is used to reindex array_views, which are no longer
  // concerned about storage order (specifically, whether dimensions
  // are ascending or descending) since the viewed array handled it.

  template <typename StrideList, typename BaseList>
  index
  calculate_indexing_offset(const StrideList& stride_list,
                          const BaseList& index_base_list)
  {
    index offset = 0;
    for (size_type n = 0; n != NumDims; ++n)
        offset -= stride_list[n] * index_base_list[n];
    return offset;
  }

  // Slicing using an index_gen.
  // Note that populating an index_gen creates a type that encodes
  // both the number of dimensions in the current Array (NumDims), and 
  // the Number of dimensions for the resulting view.  This allows the 
  // compiler to fail if the dimensions aren't completely accounted
  // for.  For reasons unbeknownst to me, a BOOST_STATIC_ASSERT
  // within the member function template does not work. I should add a 
  // note to the documentation specifying that you get a damn ugly
  // error message if you screw up in your slicing code.
  template <typename ArrayRef, int NDims, typename TPtr>
  ArrayRef
  generate_array_view(boost::type<ArrayRef>,
                      const boost::detail::multi_array::
                      index_gen<NumDims,NDims>& indices,
                      const size_type* extents,
                      const index* strides,
                      const index* index_bases,
                      TPtr base) const {

    boost::array<index,NDims> new_strides;
    boost::array<index,NDims> new_extents;

    index offset = 0;
    size_type dim = 0;
    for (size_type n = 0; n != NumDims; ++n) {

      // Use array specs and input specs to produce real specs.
      const index default_start = index_bases[n];
      const index default_finish = default_start+extents[n];
      const index_range& current_range = indices.ranges_[n];
      index start = current_range.get_start(default_start);
      index finish = current_range.get_finish(default_finish);
      index stride = current_range.stride();
      BOOST_ASSERT(stride != 0);

      // An index range indicates a half-open strided interval 
      // [start,finish) (with stride) which faces upward when stride 
      // is positive and downward when stride is negative, 

      // RG: The following code for calculating length suffers from 
      // some representation issues: if finish-start cannot be represented as
      // by type index, then overflow may result.

      index len;
      if ((finish - start) / stride < 0) {
        // [start,finish) is empty according to the direction imposed by 
        // the stride.
        len = 0;
      } else {
        // integral trick for ceiling((finish-start) / stride) 
        // taking into account signs.
        index shrinkage = stride > 0 ? 1 : -1;
        len = (finish - start + (stride - shrinkage)) / stride;
      }

      // start marks the closed side of the range, so it must lie
      // exactly in the set of legal indices
      // with a special case for empty arrays
      BOOST_ASSERT(index_bases[n] <= start &&
                   ((start <= index_bases[n]+index(extents[n])) ||
                     (start == index_bases[n] && extents[n] == 0)));

#ifndef BOOST_DISABLE_ASSERTS
      // finish marks the open side of the range, so it can go one past
      // the "far side" of the range (the top if stride is positive, the bottom
      // if stride is negative).
      index bound_adjustment = stride < 0 ? 1 : 0;
      BOOST_ASSERT(((index_bases[n] - bound_adjustment) <= finish) &&
        (finish <= (index_bases[n] + index(extents[n]) - bound_adjustment)));
      ignore_unused_variable_warning(bound_adjustment);
#endif // BOOST_DISABLE_ASSERTS


      // the array data pointer is modified to account for non-zero
      // bases during slicing (see [Garcia] for the math involved)
      offset += start * strides[n];

      if (!current_range.is_degenerate()) {

        // The stride for each dimension is included into the
        // strides for the array_view (see [Garcia] for the math involved).
        new_strides[dim] = stride * strides[n];
        
        // calculate new extents
        new_extents[dim] = len;
        ++dim;
      }
    }
    BOOST_ASSERT(dim == NDims);

    return
      ArrayRef(base+offset,
               new_extents,
               new_strides);
  }
                     

};

} // namespace multi_array
} // namespace detail

} // namespace boost

#endif

/* base.hpp
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
*/