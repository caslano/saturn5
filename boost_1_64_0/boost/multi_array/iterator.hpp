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
UkFrIG2bcfAcKN6FE5vI2Rj6HsBM57l6zxr306E/DQ+m5to39nljXgmjKMmidZ+/0+uS01Tf/izPytAvLe0tQx9GR/O/xPhBEodOkYmePHhMtoQkH2PZU34u7MQtLct2cUsI1k1670PPdVtpG94bJlbiBhAHNCvH9ablnOZup9w9YeK7uZ26gvq85vSa+86UK/OQxbaTJzL72vE5uXBoWb6aMbfY07J78A0EKvuIyEpy1wpK8bhd+jvSzRtxkVMmk8Vh6lqF9lrUSUA/+/FDZL2qc0v6e+0FHT2Z1PdOMa6FR863Kedg7eVTfQDnFuC1ORHJ+d0NnGPEv5KZ4XidjJ5hkPfydl7jfKsYBR68nFHk/sSTrPSJ6r4Y5vlUE8ex7a7kvJt3lXscb+M4Hb9xHrmRc2BMRv1zmxiGY/DtdH+v8fmuvG2zyt/88Nn9A4g/JpflpA5t7bv5LPefFmUZFEnsiUL2WRX0/8DuvXsfJgPqYmPU7QrvzZ5ROuRj9YcVldzcHOrcrh57Tv37ZjD2VMqGhib0mHT3y+R3vTECa2K9ySI/pXPtZ/wcf6spcuLMD6Lrv4syLf8Icg7w88a+RxAmju0G6g0a+SfpwYs9US5rP3Ll3YAnRE+yxuU6W51VcAt8h8bX365MXyR827dyN8j7+rQty9oftz+Rn8IPl4qYn+noo+mY5rhFkJeW09cClkEpOY3p8giWfixyG15O8tNB5XminUZOszhYnmcyfaFIvFBFGm8pj6o3szi6PG+j5dlnZ1Hi5UnZ1yJrHaUkfRruKYe31+2qrVlBH9h8q9c8VK0wKrQqzdAd69+H8feq1qjMBo3JkgdermJ4vVn+7jnwS7W+P6b+3x2zJsaiYKj67dcVpyyifFzfoRS74Dd8mlD9drLiBU8onlgCD/TL7gmrlofvnlhV6/tfYnooC/0a+28wLMstV/GrJC7enYf17/KO5AQGDJYM8i4ecvg7Ty/aoH9XoxSOP1fwd9jkW+7SsenSCMXUtQ8cmz49qjFojXIlJt9ioWPj0Y0M7ywZ+MFNDFfKadpDmxFfmzLuhB6nGCZNdG+hOCaNukdvQnFerhOI9eSCcUU6mKpKwPcCb4q4nBX7Ol+uflc7pWh8jJl4M4bNdGSJqS3OcVz+Vz4kAj7geowsP39z2Z4lNhH4XZku+NTkRCGzXT2mPjtbTarLK9LJJIeVnmz+6jy0+k5vytZHrw9pzqVvtXBmphaAg3rOtnCkM1huP+P6ctsP2zi9iclVyZR5lMZE7q4BXBn1U5qdn+k++tMmt24S01rfqV+2cBbl9lltHnVGTM85vx5kzx4TuY++8/37Fr70s8iQnotrC0MdzTs1mNd7zoq8r6DL42veIfmyBzJl9XVW6i4/q3WWd9Zc2Sw0E7rM7mW4d7yqecfv1MKTlN3AlTy00x1aeOrdGrzvOLtb32PnOjmX332c1/kQtzNl9AVlxVzTvKGX1LyZOWRJt+6aVMx459tsqsxWLenQpn8YxMMl4rSu/7ODuSpwspbQedh2YSAf4iZiuzo+kAfOCGzXyBd/Hsg/1MY/e/Gq/JnOoWoBeoPu1wP5dY3MzMP386IcNGDwxXa862+D+ge3+fmBPLR5D/vc3wdx223eHcxXNt+t29E/BvJU1IHl/tCz9FhdvjYZYMfdlWV4SW3+uWw4BZoUG9byxy+12fXa8jie/2twngeM5129xlv4LF8Dx5HtJVZ5/W/K1mtgjHug7pV6Ds1KtTXD3oSVnMYUgviXRhBnwzPiGzXOphf8jry4meN8eB1C3vEtjMeHV5gva154E+Ctr3r0femjNwXZ6+0ysm/qMtwM5K45pGBZ5rZyPh9SyF0=
*/