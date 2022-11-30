// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_SUBARRAY_HPP
#define BOOST_MULTI_ARRAY_SUBARRAY_HPP

//
// subarray.hpp - used to implement standard operator[] on
// multi_arrays
//

#include "boost/multi_array/base.hpp"
#include "boost/multi_array/concept_checks.hpp"
#include "boost/limits.hpp"
#include "boost/type.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>

namespace boost {
namespace detail {
namespace multi_array {

//
// const_sub_array
//    multi_array's proxy class to allow multiple overloads of
//    operator[] in order to provide a clean multi-dimensional array 
//    interface.
template <typename T, std::size_t NumDims, typename TPtr>
class const_sub_array :
  public boost::detail::multi_array::multi_array_impl_base<T,NumDims>
{
  typedef boost::detail::multi_array::multi_array_impl_base<T,NumDims> super_type;
public: 
  typedef typename super_type::value_type value_type;
  typedef typename super_type::const_reference const_reference;
  typedef typename super_type::const_iterator const_iterator;
  typedef typename super_type::const_reverse_iterator const_reverse_iterator;
  typedef typename super_type::element element;
  typedef typename super_type::size_type size_type;
  typedef typename super_type::difference_type difference_type;
  typedef typename super_type::index index;
  typedef typename super_type::extent_range extent_range;

  // template typedefs
  template <std::size_t NDims>
  struct const_array_view {
    typedef boost::detail::multi_array::const_multi_array_view<T,NDims> type;
  };

  template <std::size_t NDims>
  struct array_view {
    typedef boost::detail::multi_array::multi_array_view<T,NDims> type;
  };

  // Allow default copy constructor as well.

  template <typename OPtr>
  const_sub_array (const const_sub_array<T,NumDims,OPtr>& rhs) :
    base_(rhs.base_), extents_(rhs.extents_), strides_(rhs.strides_),
    index_base_(rhs.index_base_) {
  }

  // const_sub_array always returns const types, regardless of its own
  // constness.
  const_reference operator[](index idx) const {
    return super_type::access(boost::type<const_reference>(),
                              idx,base_,shape(),strides(),index_bases());
  }
  
  template <typename IndexList>
  const element& operator()(const IndexList& indices) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::access_element(boost::type<const element&>(),
                                      indices,origin(),
                                      shape(),strides(),index_bases());
  }

  // see generate_array_view in base.hpp
  template <int NDims>
  typename const_array_view<NDims>::type 
  operator[](const boost::detail::multi_array::
             index_gen<NumDims,NDims>& indices)
    const {
    typedef typename const_array_view<NDims>::type return_type;
    return
      super_type::generate_array_view(boost::type<return_type>(),
                                      indices,
                                      shape(),
                                      strides(),
                                      index_bases(),
                                      base_);
  }

  template <typename OPtr>
  bool operator<(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return std::lexicographical_compare(begin(),end(),rhs.begin(),rhs.end());
  }

  template <typename OPtr>
  bool operator==(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    if(std::equal(shape(),shape()+num_dimensions(),rhs.shape()))
      return std::equal(begin(),end(),rhs.begin());
    else return false;
  }

  template <typename OPtr>
  bool operator!=(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return !(*this == rhs);
  }

  template <typename OPtr>
  bool operator>(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return rhs < *this;
  }

  template <typename OPtr>
  bool operator<=(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return !(*this > rhs);
  }

  template <typename OPtr>
  bool operator>=(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return !(*this < rhs);
  }

  const_iterator begin() const {
    return const_iterator(*index_bases(),origin(),
                          shape(),strides(),index_bases());
  }

  const_iterator end() const {
    return const_iterator(*index_bases()+(index)*shape(),origin(),
                          shape(),strides(),index_bases());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  TPtr origin() const { return base_; }
  size_type size() const { return extents_[0]; }
  size_type max_size() const { return num_elements(); }
  bool empty() const { return size() == 0; }
  size_type num_dimensions() const { return NumDims; }
  const size_type*  shape() const { return extents_; }
  const index* strides() const { return strides_; }
  const index* index_bases() const { return index_base_; }

  size_type num_elements() const { 
    return std::accumulate(shape(),shape() + num_dimensions(),
                           size_type(1), std::multiplies<size_type>());
  }


#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
protected:
  template <typename,std::size_t> friend class value_accessor_n;  
  template <typename,std::size_t,typename> friend class const_sub_array;
#else    
public:  // Should be protected
#endif

  const_sub_array (TPtr base,
                 const size_type* extents,
                 const index* strides,
                 const index* index_base) :
    base_(base), extents_(extents), strides_(strides),
    index_base_(index_base) {
  }

  TPtr base_;
  const size_type* extents_;
  const index* strides_;
  const index* index_base_;
private:
  // const_sub_array cannot be assigned to (no deep copies!)
  const_sub_array& operator=(const const_sub_array&);
};


//
// sub_array
//    multi_array's proxy class to allow multiple overloads of
//    operator[] in order to provide a clean multi-dimensional array 
//    interface.
template <typename T, std::size_t NumDims>
class sub_array : public const_sub_array<T,NumDims,T*>
{
  typedef const_sub_array<T,NumDims,T*> super_type;
public: 
  typedef typename super_type::element element;
  typedef typename super_type::reference reference;
  typedef typename super_type::index index;
  typedef typename super_type::size_type size_type;
  typedef typename super_type::iterator iterator;
  typedef typename super_type::reverse_iterator reverse_iterator;
  typedef typename super_type::const_reference const_reference;
  typedef typename super_type::const_iterator const_iterator;
  typedef typename super_type::const_reverse_iterator const_reverse_iterator;

  // template typedefs
  template <std::size_t NDims>
  struct const_array_view {
    typedef boost::detail::multi_array::const_multi_array_view<T,NDims> type;
  };

  template <std::size_t NDims>
  struct array_view {
    typedef boost::detail::multi_array::multi_array_view<T,NDims> type;
  };

  // Assignment from other ConstMultiArray types.
  template <typename ConstMultiArray>
  sub_array& operator=(const ConstMultiArray& other) {
    function_requires< boost::multi_array_concepts::ConstMultiArrayConcept< 
        ConstMultiArray, NumDims> >();

    // make sure the dimensions agree
    BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
    BOOST_ASSERT(std::equal(other.shape(),other.shape()+this->num_dimensions(),
                            this->shape()));
    // iterator-based copy
    std::copy(other.begin(),other.end(),begin());
    return *this;
  }


  sub_array& operator=(const sub_array& other) {
    if (&other != this) {
      // make sure the dimensions agree
      BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
      BOOST_ASSERT(std::equal(other.shape(),
                              other.shape()+this->num_dimensions(),
                              this->shape()));
      // iterator-based copy
      std::copy(other.begin(),other.end(),begin());
    }
    return *this;
  }

  T* origin() { return this->base_; }
  const T* origin() const { return this->base_; }

  reference operator[](index idx) {
    return super_type::access(boost::type<reference>(),
                              idx,this->base_,this->shape(),this->strides(),
                              this->index_bases());
  }

  // see generate_array_view in base.hpp
  template <int NDims>
  typename array_view<NDims>::type 
  operator[](const boost::detail::multi_array::
             index_gen<NumDims,NDims>& indices) {
    typedef typename array_view<NDims>::type return_type;
    return
      super_type::generate_array_view(boost::type<return_type>(),
                                      indices,
                                      this->shape(),
                                      this->strides(),
                                      this->index_bases(),
                                      origin());
  }

  template <class IndexList>
  element& operator()(const IndexList& indices) {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::access_element(boost::type<element&>(),
                                      indices,origin(),
                                      this->shape(),this->strides(),
                                      this->index_bases());
  }

  iterator begin() {
    return iterator(*this->index_bases(),origin(),
                    this->shape(),this->strides(),this->index_bases());
  }

  iterator end() {
    return iterator(*this->index_bases()+(index)*this->shape(),origin(),
                    this->shape(),this->strides(),this->index_bases());
  }

  // RG - rbegin() and rend() written naively to thwart MSVC ICE.
  reverse_iterator rbegin() {
    reverse_iterator ri(end());
    return ri;
  }

  reverse_iterator rend() {
    reverse_iterator ri(begin());
    return ri;
  }

  //
  // proxies
  //

  template <class IndexList>
  const element& operator()(const IndexList& indices) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::operator()(indices);
  }

  const_reference operator[](index idx) const {
    return super_type::operator[](idx);
  }

  // see generate_array_view in base.hpp
  template <int NDims>
  typename const_array_view<NDims>::type 
  operator[](const boost::detail::multi_array::
             index_gen<NumDims,NDims>& indices)
    const {
    return super_type::operator[](indices);
  }

  const_iterator begin() const {
    return super_type::begin();
  }
  
  const_iterator end() const {
    return super_type::end();
  }

  const_reverse_iterator rbegin() const {
    return super_type::rbegin();
  }

  const_reverse_iterator rend() const {
    return super_type::rend();
  }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
private:
  template <typename,std::size_t> friend class value_accessor_n;
#else
public: // should be private
#endif

  sub_array (T* base,
            const size_type* extents,
            const index* strides,
            const index* index_base) :
    super_type(base,extents,strides,index_base) {
  }

};

} // namespace multi_array
} // namespace detail
//
// traits classes to get sub_array types
//
template <typename Array, int N>
class subarray_gen {
  typedef typename Array::element element;
public:
  typedef boost::detail::multi_array::sub_array<element,N> type;
};

template <typename Array, int N>
class const_subarray_gen {
  typedef typename Array::element element;
public:
  typedef boost::detail::multi_array::const_sub_array<element,N> type;  
};
} // namespace boost
  
#endif

/* subarray.hpp
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
*/