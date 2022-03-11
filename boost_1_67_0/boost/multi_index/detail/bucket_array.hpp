/* Copyright 2003-2020 Joaquin M Lopez Munoz.
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
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/hash_index_node.hpp>
#include <boost/noncopyable.hpp>
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