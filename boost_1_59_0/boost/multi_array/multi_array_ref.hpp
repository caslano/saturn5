// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_MULTI_ARRAY_REF_HPP
#define BOOST_MULTI_ARRAY_MULTI_ARRAY_REF_HPP

//
// multi_array_ref.hpp - code for creating "views" of array data.
//

#include "boost/multi_array/base.hpp"
#include "boost/multi_array/collection_concept.hpp"
#include "boost/multi_array/concept_checks.hpp"
#include "boost/multi_array/iterator.hpp"
#include "boost/multi_array/storage_order.hpp"
#include "boost/multi_array/subarray.hpp"
#include "boost/multi_array/view.hpp"
#include "boost/multi_array/algorithm.hpp"
#include "boost/type_traits/is_integral.hpp"
#include "boost/utility/enable_if.hpp"
#include "boost/array.hpp"
#include "boost/concept_check.hpp"
#include "boost/functional.hpp"
#include "boost/limits.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <numeric>

namespace boost {

template <typename T, std::size_t NumDims,
  typename TPtr = const T*
>
class const_multi_array_ref :
    public detail::multi_array::multi_array_impl_base<T,NumDims>
{
  typedef detail::multi_array::multi_array_impl_base<T,NumDims> super_type;
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
  typedef general_storage_order<NumDims> storage_order_type;

  // template typedefs
  template <std::size_t NDims>
  struct const_array_view {
    typedef boost::detail::multi_array::const_multi_array_view<T,NDims> type;
  };

  template <std::size_t NDims>
  struct array_view {
    typedef boost::detail::multi_array::multi_array_view<T,NDims> type;
  };

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
  // make const_multi_array_ref a friend of itself
  template <typename,std::size_t,typename>
  friend class const_multi_array_ref;
#endif

  // This ensures that const_multi_array_ref types with different TPtr 
  // types can convert to each other
  template <typename OPtr>
  const_multi_array_ref(const const_multi_array_ref<T,NumDims,OPtr>& other)
    : base_(other.base_), storage_(other.storage_),
      extent_list_(other.extent_list_),
      stride_list_(other.stride_list_),
      index_base_list_(other.index_base_list_),
      origin_offset_(other.origin_offset_),
      directional_offset_(other.directional_offset_),
      num_elements_(other.num_elements_)  {  }

  template <typename ExtentList>
  explicit const_multi_array_ref(TPtr base, const ExtentList& extents) :
    base_(base), storage_(c_storage_order()) {
    boost::function_requires<
      CollectionConcept<ExtentList> >();

    index_base_list_.assign(0);
    init_multi_array_ref(extents.begin());
  }
  
  template <typename ExtentList>
  explicit const_multi_array_ref(TPtr base, const ExtentList& extents,
                       const general_storage_order<NumDims>& so) : 
    base_(base), storage_(so) {
    boost::function_requires<
      CollectionConcept<ExtentList> >();

    index_base_list_.assign(0);
    init_multi_array_ref(extents.begin());
  }
  
  explicit const_multi_array_ref(TPtr base,
                         const detail::multi_array::
                         extent_gen<NumDims>& ranges) :
    base_(base), storage_(c_storage_order()) {

    init_from_extent_gen(ranges);
  }
  
  explicit const_multi_array_ref(TPtr base,
                           const detail::multi_array::
                           extent_gen<NumDims>& ranges,
                           const general_storage_order<NumDims>& so) :
    base_(base), storage_(so) {

    init_from_extent_gen(ranges);
  }
  
  template <class InputIterator>
  void assign(InputIterator begin, InputIterator end) {
    boost::function_requires<InputIteratorConcept<InputIterator> >();

    InputIterator in_iter = begin;
    T* out_iter = base_;
    std::size_t copy_count=0;
    while (in_iter != end && copy_count < num_elements_) {
      *out_iter++ = *in_iter++;
      copy_count++;      
    }
  }

  template <class BaseList>
#ifdef BOOST_NO_SFINAE
  void
#else
  typename
  disable_if<typename boost::is_integral<BaseList>::type,void >::type
#endif // BOOST_NO_SFINAE
  reindex(const BaseList& values) {
    boost::function_requires<
      CollectionConcept<BaseList> >();
    boost::detail::multi_array::
      copy_n(values.begin(),num_dimensions(),index_base_list_.begin());
    origin_offset_ =
      this->calculate_origin_offset(stride_list_,extent_list_,
                              storage_,index_base_list_);
  }

  void reindex(index value) {
    index_base_list_.assign(value);
    origin_offset_ =
      this->calculate_origin_offset(stride_list_,extent_list_,
                              storage_,index_base_list_);
  }

  template <typename SizeList>
  void reshape(const SizeList& extents) {
    boost::function_requires<
      CollectionConcept<SizeList> >();
    BOOST_ASSERT(num_elements_ ==
                 std::accumulate(extents.begin(),extents.end(),
                                 size_type(1),std::multiplies<size_type>()));

    std::copy(extents.begin(),extents.end(),extent_list_.begin());
    this->compute_strides(stride_list_,extent_list_,storage_);

    origin_offset_ =
      this->calculate_origin_offset(stride_list_,extent_list_,
                              storage_,index_base_list_);
  }

  size_type num_dimensions() const { return NumDims; }

  size_type size() const { return extent_list_.front(); }

  // given reshaping functionality, this is the max possible size.
  size_type max_size() const { return num_elements(); }

  bool empty() const { return size() == 0; }

  const size_type* shape() const {
    return extent_list_.data();
  }

  const index* strides() const {
    return stride_list_.data();
  }

  const element* origin() const { return base_+origin_offset_; }
  const element* data() const { return base_; }

  size_type num_elements() const { return num_elements_; }

  const index* index_bases() const {
    return index_base_list_.data();
  }


  const storage_order_type& storage_order() const {
    return storage_;
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
                              shape(),strides(),index_bases());
  }

  // see generate_array_view in base.hpp
  template <int NDims>
  typename const_array_view<NDims>::type 
  operator[](const detail::multi_array::
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
                  const_multi_array_ref<T,NumDims,OPtr>& rhs)
    const {
    if(std::equal(extent_list_.begin(),
                  extent_list_.end(),
                  rhs.extent_list_.begin()))
      return std::equal(begin(),end(),rhs.begin());
    else return false;
  }

  template <typename OPtr>
  bool operator<(const
                 const_multi_array_ref<T,NumDims,OPtr>& rhs)
    const {
    return std::lexicographical_compare(begin(),end(),rhs.begin(),rhs.end());
  }

  template <typename OPtr>
  bool operator!=(const
                  const_multi_array_ref<T,NumDims,OPtr>& rhs)
    const {
    return !(*this == rhs);
  }

  template <typename OPtr>
  bool operator>(const
                 const_multi_array_ref<T,NumDims,OPtr>& rhs)
    const {
    return rhs < *this;
  }

  template <typename OPtr>
  bool operator<=(const
                 const_multi_array_ref<T,NumDims,OPtr>& rhs)
    const {
    return !(*this > rhs);
  }

  template <typename OPtr>
  bool operator>=(const
                 const_multi_array_ref<T,NumDims,OPtr>& rhs)
    const {
    return !(*this < rhs);
  }


#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
protected:
#else
public:
#endif

  typedef boost::array<size_type,NumDims> size_list;
  typedef boost::array<index,NumDims> index_list;

  // This is used by multi_array, which is a subclass of this
  void set_base_ptr(TPtr new_base) { base_ = new_base; }


  // This constructor supports multi_array's default constructor
  // and constructors from multi_array_ref, subarray, and array_view
  explicit
  const_multi_array_ref(TPtr base,
                        const storage_order_type& so,
                        const index * index_bases,
                        const size_type* extents) :
    base_(base), storage_(so), origin_offset_(0), directional_offset_(0)
 {
   // If index_bases or extents is null, then initialize the corresponding
   // private data to zeroed lists.
   if(index_bases) {
     boost::detail::multi_array::
       copy_n(index_bases,NumDims,index_base_list_.begin());
   } else {
     std::fill_n(index_base_list_.begin(),NumDims,0);
   }
   if(extents) {
     init_multi_array_ref(extents);
   } else {
     boost::array<index,NumDims> extent_list;
     extent_list.assign(0);
     init_multi_array_ref(extent_list.begin());
   }
 }


  TPtr base_;
  storage_order_type storage_;
  size_list extent_list_;
  index_list stride_list_;
  index_list index_base_list_;
  index origin_offset_;
  index directional_offset_;
  size_type num_elements_;

private:
  // const_multi_array_ref cannot be assigned to (no deep copies!)
  const_multi_array_ref& operator=(const const_multi_array_ref& other);

  void init_from_extent_gen(const
                        detail::multi_array::
                        extent_gen<NumDims>& ranges) { 
    
    typedef boost::array<index,NumDims> extent_list;

    // get the index_base values
    std::transform(ranges.ranges_.begin(),ranges.ranges_.end(),
              index_base_list_.begin(),
              boost::mem_fun_ref(&extent_range::start));

    // calculate the extents
    extent_list extents;
    std::transform(ranges.ranges_.begin(),ranges.ranges_.end(),
              extents.begin(),
              boost::mem_fun_ref(&extent_range::size));

    init_multi_array_ref(extents.begin());
  }


#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
protected:
#else
public:
#endif
  // RG - move me!
  template <class InputIterator>
  void init_multi_array_ref(InputIterator extents_iter) {
    boost::function_requires<InputIteratorConcept<InputIterator> >();

    boost::detail::multi_array::
      copy_n(extents_iter,num_dimensions(),extent_list_.begin());

    // Calculate the array size
    num_elements_ = std::accumulate(extent_list_.begin(),extent_list_.end(),
                            size_type(1),std::multiplies<size_type>());

    this->compute_strides(stride_list_,extent_list_,storage_);

    origin_offset_ =
      this->calculate_origin_offset(stride_list_,extent_list_,
                              storage_,index_base_list_);
    directional_offset_ =
      this->calculate_descending_dimension_offset(stride_list_,extent_list_,
                                            storage_);
  }
};

template <typename T, std::size_t NumDims>
class multi_array_ref :
  public const_multi_array_ref<T,NumDims,T*>
{
  typedef const_multi_array_ref<T,NumDims,T*> super_type;
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

  typedef typename super_type::storage_order_type storage_order_type;
  typedef typename super_type::index_list index_list;
  typedef typename super_type::size_list size_list;

  template <std::size_t NDims>
  struct const_array_view {
    typedef boost::detail::multi_array::const_multi_array_view<T,NDims> type;
  };

  template <std::size_t NDims>
  struct array_view {
    typedef boost::detail::multi_array::multi_array_view<T,NDims> type;
  };

  template <class ExtentList>
  explicit multi_array_ref(T* base, const ExtentList& extents) :
    super_type(base,extents) {
    boost::function_requires<
      CollectionConcept<ExtentList> >();
  }

  template <class ExtentList>
  explicit multi_array_ref(T* base, const ExtentList& extents,
                           const general_storage_order<NumDims>& so) :
    super_type(base,extents,so) {
    boost::function_requires<
      CollectionConcept<ExtentList> >();
  }


  explicit multi_array_ref(T* base,
                           const detail::multi_array::
                           extent_gen<NumDims>& ranges) :
    super_type(base,ranges) { }


  explicit multi_array_ref(T* base,
                           const detail::multi_array::
                           extent_gen<NumDims>&
                             ranges,
                           const general_storage_order<NumDims>& so) :
    super_type(base,ranges,so) { }


  // Assignment from other ConstMultiArray types.
  template <typename ConstMultiArray>
  multi_array_ref& operator=(const ConstMultiArray& other) {
    function_requires< 
      multi_array_concepts::
      ConstMultiArrayConcept<ConstMultiArray,NumDims> >();

    // make sure the dimensions agree
    BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
    BOOST_ASSERT(std::equal(other.shape(),other.shape()+this->num_dimensions(),
                            this->shape()));
    // iterator-based copy
    std::copy(other.begin(),other.end(),this->begin());
    return *this;
  }

  multi_array_ref& operator=(const multi_array_ref& other) {
    if (&other != this) {
      // make sure the dimensions agree
      
      BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
      BOOST_ASSERT(std::equal(other.shape(),
                              other.shape()+this->num_dimensions(),
                              this->shape()));
      // iterator-based copy
      std::copy(other.begin(),other.end(),this->begin());
    }
    return *this;
  }

  element* origin() { return super_type::base_+super_type::origin_offset_; }

  element* data() { return super_type::base_; }

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


  // See note attached to generate_array_view in base.hpp
  template <int NDims>
  typename array_view<NDims>::type 
  operator[](const detail::multi_array::
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
    return iterator(*this->index_bases(),origin(),this->shape(),
                    this->strides(),this->index_bases());
  }

  iterator end() {
    return iterator(*this->index_bases()+(index)*this->shape(),origin(),
                    this->shape(),this->strides(),
                    this->index_bases());
  }

  // rbegin() and rend() written naively to thwart MSVC ICE.
  reverse_iterator rbegin() {
    reverse_iterator ri(end());
    return ri;
  }

  reverse_iterator rend() {
    reverse_iterator ri(begin());
    return ri;
  }

  // Using declarations don't seem to work for g++
  // These are the proxies to work around this.

  const element* origin() const { return super_type::origin(); }
  const element* data() const { return super_type::data(); }

  template <class IndexList>
  const element& operator()(const IndexList& indices) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::operator()(indices);
  }

  const_reference operator[](index idx) const {
    return super_type::access(boost::type<const_reference>(),
                              idx,origin(),
                              this->shape(),this->strides(),
                              this->index_bases());
  }

  // See note attached to generate_array_view in base.hpp
  template <int NDims>
  typename const_array_view<NDims>::type 
  operator[](const detail::multi_array::
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

protected:
  // This is only supplied to support multi_array's default constructor
  explicit multi_array_ref(T* base,
                           const storage_order_type& so,
                           const index* index_bases,
                           const size_type* extents) :
    super_type(base,so,index_bases,extents) { }

};

} // namespace boost

#endif

/* multi_array_ref.hpp
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
*/