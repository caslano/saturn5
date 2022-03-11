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