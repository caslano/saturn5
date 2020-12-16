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
h5B9hn3mSdKIsdPp20m3dLqv7g4dYp4JgiAIgiDmUKZSHjx48KCKBw8eVMmDeSjKUFJKFXvtc/a6a+17bgYh/XfO962153nvtZiORBTwyNZT6b3d81ZiR/8y1VGJJCzC2MlTIdktIV6fr3+O12fpV1EQRC4X4leLbP8NP6M6SuF7QRVUoS8kvTFUC82asv8VCzdWZSeDCPZfZPt1GXt+PvJ5y19IkPqJk/vt8j3sg9B2IpOXoiiLMnIdDJ9em7H3VSaYbCrCLA3SvPS47Nws2RxjeT7F5HORFoEfBU40IH+Ka6Bz0HWmoxJx6QS5G6RcR09ZTp+pn0FNH4cHVQP+gq4wPYVw4WGd64VcD5glHdAiTPn/kOpQKsogjL0oRhX91dHIafRTxMLNhAyTIoo9kv8Dm/CNCuIzxqoDsAyp3MQXeNwMOsAYoD5BHpizbL/G81ClO5YZKUeU54Vp5+HkNd4PJb6v0hK4g3qsQiX+b45ds+zWV0EWhxWJy2pbe1gx8ueYfCTcNCs8P5NM3m4PRP6SJe8F0nOrEsvDuiaE8mb9+U0m74qiCB2/KDJhH5E1axBTd350je8Tp2kW5GEiyKnYQNv9OQtLijwI0iByXDF47GWEhVlX/5XKZqIsktxLfceIYk016Rr5At+byhzf9xOnEANHpFxuJ5NzRFFmpZ+rjLGOhuy+9MlUrhBB6BfSgWJk+8N8r++gFVaSyiKWbolCfJ8G41hZcr5TRUEoKyL3irZxt0vlPHCOWRVhEIjbnbrQPvTSF2w/DYEMsiwWrccsWI7LuHb+gtX2Xd+FnUoub2czWa9Z8hXYQ4gkF8ccsOaPTDYUrsw8GO9ab9FYvm62fpGVbxzmnhMkCcoSf3RLuP/LZYpMNc08FvRSWi1CZB5PZUqRuzKsZBKhEGlZKDPJw4kKCT7VXEFvsZm44V4dlfECEQWZVwRZKG5zdYyu/9eYDgl7Qqmbps7d6LjCdCQijhNVpH4hbnddjpzP/IzqcGHNFwQRbLTzK22mPbzC1MXfMblYlG4QpmFRiSFX3bQ88Q83+iW+V5tJN/KdKGLyy+ypFPaFuyzZMvRCB3zLtV2Ns84VDlLZQmRlnPtlmKIoGbeXTHgZC8+Hvd0yUIGi0OB0H+PatWTL2A2CIE/E4FOTgTXjuS/xehbGflo5Lgl39bZ15BrTIYUbOlWRZs7d6PgZ05GIIIszWTihuN2TFqJj65ctHyYyrbysKO5Gx+SXeTxKKXMnr0quo72+4x75ly3bzWmURglpu2a7iVfcBTwfZPKOSDMv8twC+vCWnfG+r9srVC4XeelFblVUgrzswPLH/TkWVixcN89CR0ox5MlHowDj+mMm74owCX0/TiOxMN5tOSdeQ79GTM4XMkm8vKp8kLvdOfFNK8xc1ZOwiEGUHRPb573bvmLt5TulH0elVILLIKjHViKHfQGTU8WYxtJP/UrghtdgqeC5nyXrVlUW+UUmcHNpuOxRSzZIEreKq0rgRs6grEnrmpXWKsucFMaP5fEFnlZ+jvB2JueLyIsKN6kSsQw7tLPssNH2iXbFim8RZWWQZ55ofWrM0/r9r9j+36Trl1UkWp5r2/6rf2bncZEGsZsVovWZNs+nv9p1ogA3GGEuLLPAJp9MWxv9Kvd7XVayivxQ0Nef9nxyx1etuXyVuGkQlUwI3bj2w3o8latEEedOnGcYRRZDHIO4jFS5GZVJIPjrUJ4XlRU/v3AdGYeVsJ+MWvHr8ryQWV7mJUrpYht4J7xGZTIhyywuMscVcFZl+VV00CbKV6064rh5knuFOK5COHNa3X45s6Z+nFAe3GaWTvb9xbrmnJnJJ6JInSAN3VKQMWmIEhE=
*/