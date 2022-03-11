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