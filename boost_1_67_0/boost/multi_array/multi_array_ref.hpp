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