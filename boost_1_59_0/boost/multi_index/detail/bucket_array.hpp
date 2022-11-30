/* Copyright 2003-2022 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_BUCKET_ARRAY_HPP
#define BOOST_MULTI_INDEX_DETAIL_BUCKET_ARRAY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/core/noncopyable.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/hash_index_node.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <cstddef>
#include <limits.h>

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/access.hpp>
#include <boost/throw_exception.hpp> 
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* bucket structure for use by hashed indices */

#define BOOST_MULTI_INDEX_BA_SIZES_32BIT                                  \
(53ul)(97ul)(193ul)(389ul)(769ul)                                         \
(1543ul)(3079ul)(6151ul)(12289ul)(24593ul)                                \
(49157ul)(98317ul)(196613ul)(393241ul)(786433ul)                          \
(1572869ul)(3145739ul)(6291469ul)(12582917ul)(25165843ul)                 \
(50331653ul)(100663319ul)(201326611ul)(402653189ul)(805306457ul)          \
(1610612741ul)(3221225473ul)

#if ((((ULONG_MAX>>16)>>16)>>16)>>15)==0 /* unsigned long less than 64 bits */
#define BOOST_MULTI_INDEX_BA_SIZES                                         \
BOOST_MULTI_INDEX_BA_SIZES_32BIT                                           \
(4294967291ul)
#else
  /* obtained with aid from
   *   http://javaboutique.internet.com/prime_numb/
   *   http://www.rsok.com/~jrm/next_ten_primes.html
   * and verified with
   *   http://www.alpertron.com.ar/ECM.HTM
   */

#define BOOST_MULTI_INDEX_BA_SIZES                                         \
BOOST_MULTI_INDEX_BA_SIZES_32BIT                                           \
(6442450939ul)(12884901893ul)(25769803751ul)(51539607551ul)                \
(103079215111ul)(206158430209ul)(412316860441ul)(824633720831ul)           \
(1649267441651ul)(3298534883309ul)(6597069766657ul)(13194139533299ul)      \
(26388279066623ul)(52776558133303ul)(105553116266489ul)(211106232532969ul) \
(422212465066001ul)(844424930131963ul)(1688849860263953ul)                 \
(3377699720527861ul)(6755399441055731ul)(13510798882111483ul)              \
(27021597764222939ul)(54043195528445957ul)(108086391056891903ul)           \
(216172782113783843ul)(432345564227567621ul)(864691128455135207ul)         \
(1729382256910270481ul)(3458764513820540933ul)(6917529027641081903ul)      \
(13835058055282163729ul)(18446744073709551557ul)
#endif

template<bool _=true> /* templatized to have in-header static var defs */
class bucket_array_base:private noncopyable
{
protected:
  static const std::size_t sizes[
    BOOST_PP_SEQ_SIZE(BOOST_MULTI_INDEX_BA_SIZES)];

  static std::size_t size_index(std::size_t n)
  {
    const std::size_t *bound=std::lower_bound(sizes,sizes+sizes_length,n);
    if(bound==sizes+sizes_length)--bound;
    return bound-sizes;
  }

#define BOOST_MULTI_INDEX_BA_POSITION_CASE(z,n,_)                    \
  case n:return hash%BOOST_PP_SEQ_ELEM(n,BOOST_MULTI_INDEX_BA_SIZES);

  static std::size_t position(std::size_t hash,std::size_t size_index_)
  {
    /* Accelerate hash%sizes[size_index_] by replacing with a switch on
     * hash%Ci expressions, each Ci a compile-time constant, which the
     * compiler can implement without using integer division.
     */

    switch(size_index_){
      default: /* never used */
      BOOST_PP_REPEAT(
        BOOST_PP_SEQ_SIZE(BOOST_MULTI_INDEX_BA_SIZES),
        BOOST_MULTI_INDEX_BA_POSITION_CASE,~)
    }
  }

private:
  static const std::size_t sizes_length;
};

template<bool _>
const std::size_t bucket_array_base<_>::sizes[]={
  BOOST_PP_SEQ_ENUM(BOOST_MULTI_INDEX_BA_SIZES)
};

template<bool _>
const std::size_t bucket_array_base<_>::sizes_length=
  sizeof(bucket_array_base<_>::sizes)/
  sizeof(bucket_array_base<_>::sizes[0]);

#undef BOOST_MULTI_INDEX_BA_POSITION_CASE
#undef BOOST_MULTI_INDEX_BA_SIZES
#undef BOOST_MULTI_INDEX_BA_SIZES_32BIT

template<typename Allocator>
class bucket_array:bucket_array_base<>
{
  typedef bucket_array_base<>                        super;
  typedef hashed_index_base_node_impl<
    typename rebind_alloc_for<
      Allocator,
      char
    >::type
  >                                                  base_node_impl_type;

public:
  typedef typename base_node_impl_type::base_pointer base_pointer;
  typedef typename base_node_impl_type::pointer      pointer;

  bucket_array(const Allocator& al,pointer end_,std::size_t size_):
    size_index_(super::size_index(size_)),
    spc(al,static_cast<auto_space_size_type>(super::sizes[size_index_]+1))
  {
    clear(end_);
  }

  std::size_t size()const
  {
    return super::sizes[size_index_];
  }

  std::size_t position(std::size_t hash)const
  {
    return super::position(hash,size_index_);
  }

  base_pointer begin()const{return buckets();}
  base_pointer end()const{return buckets()+size();}
  base_pointer at(std::size_t n)const{return buckets()+n;}

  void clear(pointer end_)
  {
    for(base_pointer x=begin(),y=end();x!=y;++x)x->prior()=pointer(0);
    end()->prior()=end_->prior()=end_;
    end_->next()=end();
 }

  void swap(bucket_array& x)
  {
    std::swap(size_index_,x.size_index_);
    spc.swap(x.spc);
  }

  template<typename BoolConstant>
  void swap(bucket_array& x,BoolConstant swap_allocators)
  {
    std::swap(size_index_,x.size_index_);
    spc.swap(x.spc,swap_allocators);
  }

private:
  typedef auto_space<base_node_impl_type,Allocator> auto_space_type;
  typedef typename auto_space_type::size_type       auto_space_size_type;

  std::size_t      size_index_;
  auto_space_type  spc;

  base_pointer buckets()const
  {
    return spc.data();
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  friend class boost::serialization::access;
  
  /* bucket_arrays do not emit any kind of serialization info. They are
   * fed to Boost.Serialization as hashed index iterators need to track
   * them during serialization.
   */

  template<class Archive>
  void serialize(Archive&,const unsigned int)
  {
  }
#endif
};

template<typename Allocator>
void swap(bucket_array<Allocator>& x,bucket_array<Allocator>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
/* bucket_arrays never get constructed directly by Boost.Serialization,
 * as archives are always fed pointers to previously existent
 * arrays. So, if this is called it means we are dealing with a
 * somehow invalid archive.
 */

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace serialization{
#else
namespace multi_index{
namespace detail{
#endif

template<class Archive,typename Allocator>
inline void load_construct_data(
  Archive&,boost::multi_index::detail::bucket_array<Allocator>*,
  const unsigned int)
{
  throw_exception(
    archive::archive_exception(archive::archive_exception::other_exception));
}

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
} /* namespace serialization */
#else
} /* namespace multi_index::detail */
} /* namespace multi_index */
#endif

#endif

} /* namespace boost */

#endif

/* bucket_array.hpp
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
*/