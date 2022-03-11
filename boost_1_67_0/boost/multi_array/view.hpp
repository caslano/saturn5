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