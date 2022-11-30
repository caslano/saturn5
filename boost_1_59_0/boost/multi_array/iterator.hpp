// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_ITERATOR_HPP
#define BOOST_MULTI_ARRAY_ITERATOR_HPP

//
// iterator.hpp - implementation of iterators for the
// multi-dimensional array class
//

#include "boost/multi_array/base.hpp"
#include "boost/iterator/iterator_facade.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>

namespace boost {
namespace detail {
namespace multi_array {

/////////////////////////////////////////////////////////////////////////
// iterator components
/////////////////////////////////////////////////////////////////////////

template <class T>
struct operator_arrow_proxy
{
  operator_arrow_proxy(T const& px) : value_(px) {}
  T* operator->() const { return &value_; }
  // This function is needed for MWCW and BCC, which won't call operator->
  // again automatically per 13.3.1.2 para 8
  operator T*() const { return &value_; }
  mutable T value_;
};

template <typename T, typename TPtr, typename NumDims, typename Reference,
          typename IteratorCategory>
class array_iterator;

template <typename T, typename TPtr, typename NumDims, typename Reference,
          typename IteratorCategory>
class array_iterator
  : public
    iterator_facade<
        array_iterator<T,TPtr,NumDims,Reference,IteratorCategory>
      , typename associated_types<T,NumDims>::value_type
      , IteratorCategory
      , Reference
    >
    , private
          value_accessor_generator<T,NumDims>::type
{
  friend class ::boost::iterator_core_access;
  typedef detail::multi_array::associated_types<T,NumDims> access_t;

  typedef iterator_facade<
            array_iterator<T,TPtr,NumDims,Reference,IteratorCategory>
      , typename detail::multi_array::associated_types<T,NumDims>::value_type
      , boost::random_access_traversal_tag
      , Reference
    > facade_type;

  typedef typename access_t::index index;
  typedef typename access_t::size_type size_type;

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
  template <typename, typename, typename, typename, typename>
    friend class array_iterator;
#else
 public:
#endif 

  index idx_;
  TPtr base_;
  const size_type* extents_;
  const index* strides_;
  const index* index_base_;
 
public:
  // Typedefs to circumvent ambiguities between parent classes
  typedef typename facade_type::reference reference;
  typedef typename facade_type::value_type value_type;
  typedef typename facade_type::difference_type difference_type;

  array_iterator() {}

  array_iterator(index idx, TPtr base, const size_type* extents,
                const index* strides,
                const index* index_base) :
    idx_(idx), base_(base), extents_(extents),
    strides_(strides), index_base_(index_base) { }

  template <typename OPtr, typename ORef, typename Cat>
  array_iterator(
      const array_iterator<T,OPtr,NumDims,ORef,Cat>& rhs
    , typename boost::enable_if_convertible<OPtr,TPtr>::type* = 0
  )
    : idx_(rhs.idx_), base_(rhs.base_), extents_(rhs.extents_),
    strides_(rhs.strides_), index_base_(rhs.index_base_) { }


  // RG - we make our own operator->
  operator_arrow_proxy<reference>
  operator->() const
  {
    return operator_arrow_proxy<reference>(this->dereference());
  }
  

  reference dereference() const
  {
    typedef typename value_accessor_generator<T,NumDims>::type accessor;
    return accessor::access(boost::type<reference>(),
                            idx_,
                            base_,
                            extents_,
                            strides_,
                            index_base_);
  }
  
  void increment() { ++idx_; }
  void decrement() { --idx_; }

  template <class IteratorAdaptor>
  bool equal(IteratorAdaptor& rhs) const {
    const std::size_t N = NumDims::value;
    return (idx_ == rhs.idx_) &&
      (base_ == rhs.base_) &&
      ( (extents_ == rhs.extents_) ||
        std::equal(extents_,extents_+N,rhs.extents_) ) &&
      ( (strides_ == rhs.strides_) ||
        std::equal(strides_,strides_+N,rhs.strides_) ) &&
      ( (index_base_ == rhs.index_base_) ||
        std::equal(index_base_,index_base_+N,rhs.index_base_) );
  }

  template <class DifferenceType>
  void advance(DifferenceType n) {
    idx_ += n;
  }

  template <class IteratorAdaptor>
  typename facade_type::difference_type
  distance_to(IteratorAdaptor& rhs) const {
    return rhs.idx_ - idx_;
  }


};

} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* iterator.hpp
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
*/