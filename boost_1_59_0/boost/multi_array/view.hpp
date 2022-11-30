// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_VIEW_HPP
#define BOOST_MULTI_ARRAY_VIEW_HPP

//
// view.hpp - code for creating "views" of array data.
//

#include "boost/multi_array/base.hpp"
#include "boost/multi_array/concept_checks.hpp"
#include "boost/multi_array/iterator.hpp"
#include "boost/multi_array/storage_order.hpp"
#include "boost/multi_array/subarray.hpp"
#include "boost/multi_array/algorithm.hpp"
#include "boost/type_traits/is_integral.hpp"
#include "boost/utility/enable_if.hpp"
#include "boost/array.hpp"
#include "boost/limits.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <numeric>

namespace boost {
namespace detail {
namespace multi_array {

// TPtr = const T* defaulted in base.hpp
template <typename T, std::size_t NumDims, typename TPtr>
class const_multi_array_view :
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

  template <typename OPtr>
  const_multi_array_view(const 
                         const_multi_array_view<T,NumDims,OPtr>& other) :
    base_(other.base_), origin_offset_(other.origin_offset_),
    num_elements_(other.num_elements_), extent_list_(other.extent_list_),
    stride_list_(other.stride_list_), index_base_list_(other.index_base_list_)
  { }


  template <class BaseList>
#ifdef BOOST_NO_SFINAE
  void
#else
  typename
  disable_if<typename boost::is_integral<BaseList>::type,void >::type
#endif
  reindex(const BaseList& values) {
    boost::function_requires<
      CollectionConcept<BaseList> >();
    boost::detail::multi_array::
      copy_n(values.begin(),num_dimensions(),index_base_list_.begin());
    origin_offset_ =
      this->calculate_indexing_offset(stride_list_,index_base_list_);
  }

  void reindex(index value) {
    index_base_list_.assign(value);
    origin_offset_ =
      this->calculate_indexing_offset(stride_list_,index_base_list_);
  }

  size_type num_dimensions() const { return NumDims; }

  size_type size() const { return extent_list_.front(); }
  size_type max_size() const { return num_elements(); }
  bool empty() const { return size() == 0; }

  const size_type* shape() const {
    return extent_list_.data();
  }

  const index* strides() const {
    return stride_list_.data();
  }

  const T* origin() const { return base_+origin_offset_; }

  size_type num_elements() const { return num_elements_; }

  const index* index_bases() const {
    return index_base_list_.data();
  }

  template <typename IndexList>
  const element& operator()(IndexList indices) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::access_element(boost::type<const element&>(),
                                      indices,origin(),
                                      shape(),strides(),index_bases());
  }

  // Only allow const element access
  const_reference operator[](index idx) const {
    return super_type::access(boost::type<const_reference>(),
                              idx,origin(),
                              shape(),strides(),
                              index_bases());
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
                                      origin());
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


  template <typename OPtr>
  bool operator==(const
                  const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    if(std::equal(extent_list_.begin(),
                  extent_list_.end(),
                  rhs.extent_list_.begin()))
      return std::equal(begin(),end(),rhs.begin());
    else return false;
  }

  template <typename OPtr>
  bool operator<(const
                 const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return std::lexicographical_compare(begin(),end(),rhs.begin(),rhs.end());
  }

  template <typename OPtr>
  bool operator!=(const
                  const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return !(*this == rhs);
  }

  template <typename OPtr>
  bool operator>(const
                 const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return rhs < *this;
  }

  template <typename OPtr>
  bool operator<=(const
                 const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return !(*this > rhs);
  }

  template <typename OPtr>
  bool operator>=(const
                 const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return !(*this < rhs);
  }


#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
protected:
  template <typename,std::size_t> friend class multi_array_impl_base;
  template <typename,std::size_t,typename> friend class const_multi_array_view;
#else
public: // should be protected
#endif

  // This constructor is used by multi_array_impl_base::generate_array_view
  // to create strides  
  template <typename ExtentList, typename Index>
  explicit const_multi_array_view(TPtr base,
                           const ExtentList& extents,
                           const boost::array<Index,NumDims>& strides): 
    base_(base), origin_offset_(0) {

    index_base_list_.assign(0);

    // Get the extents and strides
    boost::detail::multi_array::
      copy_n(extents.begin(),NumDims,extent_list_.begin());
    boost::detail::multi_array::
      copy_n(strides.begin(),NumDims,stride_list_.begin());

    // Calculate the array size
    num_elements_ = std::accumulate(extent_list_.begin(),extent_list_.end(),
                                    size_type(1),std::multiplies<size_type>());
  }

  typedef boost::array<size_type,NumDims> size_list;
  typedef boost::array<index,NumDims> index_list;

  TPtr base_;
  index origin_offset_;
  size_type num_elements_;
  size_list extent_list_;
  index_list stride_list_;
  index_list index_base_list_;

private:
  // const_multi_array_view cannot be assigned to (no deep copies!)
  const_multi_array_view& operator=(const const_multi_array_view& other);
};


template <typename T, std::size_t NumDims>
class multi_array_view :
  public const_multi_array_view<T,NumDims,T*>
{
  typedef const_multi_array_view<T,NumDims,T*> super_type;
public: 
  typedef typename super_type::value_type value_type;
  typedef typename super_type::reference reference;
  typedef typename super_type::iterator iterator;
  typedef typename super_type::reverse_iterator reverse_iterator;
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

  // Assignment from other ConstMultiArray types.
  template <typename ConstMultiArray>
  multi_array_view& operator=(const ConstMultiArray& other) {
    function_requires< 
      boost::multi_array_concepts::
      ConstMultiArrayConcept<ConstMultiArray,NumDims> >();

    // make sure the dimensions agree
    BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
    BOOST_ASSERT(std::equal(other.shape(),other.shape()+this->num_dimensions(),
                            this->shape()));
    // iterator-based copy
    std::copy(other.begin(),other.end(),begin());
    return *this;
  }


  multi_array_view& operator=(const multi_array_view& other) {
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

  element* origin() { return this->base_+this->origin_offset_; }

  template <class IndexList>
  element& operator()(const IndexList& indices) {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::access_element(boost::type<element&>(),
                                      indices,origin(),
                                      this->shape(),this->strides(),
                                      this->index_bases());
  }


  reference operator[](index idx) {
    return super_type::access(boost::type<reference>(),
                              idx,origin(),
                              this->shape(),this->strides(),
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
  
  
  iterator begin() {
    return iterator(*this->index_bases(),origin(),
                    this->shape(),this->strides(),
                    this->index_bases());
  }

  iterator end() {
    return iterator(*this->index_bases()+(index)*this->shape(),origin(),
                    this->shape(),this->strides(),
                    this->index_bases());
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  // Using declarations don't seem to work for g++
  // These are the proxies to work around this.

  const element* origin() const { return super_type::origin(); }

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
  template <typename,std::size_t> friend class multi_array_impl_base;
#else
public: // should be private
#endif

  // constructor used by multi_array_impl_base::generate_array_view to
  // generate array views
  template <typename ExtentList, typename Index>
  explicit multi_array_view(T* base,
                            const ExtentList& extents,
                            const boost::array<Index,NumDims>& strides) :
    super_type(base,extents,strides) { }

};

} // namespace multi_array
} // namespace detail

//
// traits classes to get array_view types
//
template <typename Array, int N>
class array_view_gen {
  typedef typename Array::element element;
public:
  typedef boost::detail::multi_array::multi_array_view<element,N> type;
};

template <typename Array, int N>
class const_array_view_gen {
  typedef typename Array::element element;
public:
  typedef boost::detail::multi_array::const_multi_array_view<element,N> type;  
};

} // namespace boost

#endif

/* view.hpp
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
*/