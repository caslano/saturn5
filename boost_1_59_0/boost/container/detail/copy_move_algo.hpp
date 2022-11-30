//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_COPY_MOVE_ALGO_HPP
#define BOOST_CONTAINER_DETAIL_COPY_MOVE_ALGO_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

// container
#include <boost/container/allocator_traits.hpp>
// container/detail
#include <boost/container/detail/iterator.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/construct_in_place.hpp>
#include <boost/container/detail/destroyers.hpp>

// move
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/iterator.hpp>
#include <boost/move/utility_core.hpp>
// other
#include <boost/core/no_exceptions_support.hpp>
// std
#include <cstring> //for memmove/memcpy

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#pragma GCC diagnostic push
//pair memcpy optimizations rightfully detected by GCC
#  if defined(BOOST_GCC) && (BOOST_GCC >= 80000)
#     pragma GCC diagnostic ignored "-Wclass-memaccess"
#  endif
//GCC 8 seems a bit confused about array access error with static_vector
//when out of bound exceptions are being thrown.
#  if defined(BOOST_GCC) && (BOOST_GCC >= 80000) && (BOOST_GCC < 80200)
#     pragma GCC diagnostic ignored "-Wstringop-overflow"
#  endif
#  pragma GCC diagnostic ignored "-Warray-bounds"
#endif

namespace boost {
namespace container {
namespace dtl {

template<class I>
struct are_elements_contiguous
{
   static const bool value = false;
};

/////////////////////////
//    raw pointers
/////////////////////////

template<class T>
struct are_elements_contiguous<T*>
{
   static const bool value = true;
};

/////////////////////////
//    move iterators
/////////////////////////

template<class It>
struct are_elements_contiguous< ::boost::move_iterator<It> >
   : are_elements_contiguous<It>
{};

}  //namespace dtl {

/////////////////////////
//    predeclarations
/////////////////////////

template <class Pointer, bool IsConst>
class vec_iterator;

}  //namespace container {

namespace interprocess {

template <class PointedType, class DifferenceType, class OffsetType, std::size_t OffsetAlignment>
class offset_ptr;

}  //namespace interprocess {

namespace container {

namespace dtl {

/////////////////////////
//vector_[const_]iterator
/////////////////////////

template <class Pointer, bool IsConst>
struct are_elements_contiguous<boost::container::vec_iterator<Pointer, IsConst> >
{
   static const bool value = true;
};

/////////////////////////
//    offset_ptr
/////////////////////////

template <class PointedType, class DifferenceType, class OffsetType, std::size_t OffsetAlignment>
struct are_elements_contiguous< ::boost::interprocess::offset_ptr<PointedType, DifferenceType, OffsetType, OffsetAlignment> >
{
   static const bool value = true;
};

template <typename I, typename O>
struct are_contiguous_and_same
   : boost::move_detail::and_
      < are_elements_contiguous<I>
      , are_elements_contiguous<O>
      , is_same< typename remove_const< typename ::boost::container::iter_value<I>::type >::type
               , typename ::boost::container::iterator_traits<O>::value_type
               >
      >
{};

template <typename I, typename O>
struct is_memtransfer_copy_assignable
   : boost::move_detail::and_
      < are_contiguous_and_same<I, O>
      , dtl::is_trivially_copy_assignable< typename ::boost::container::iter_value<I>::type >
      >
{};

template <typename I, typename O>
struct is_memtransfer_copy_constructible
   : boost::move_detail::and_
      < are_contiguous_and_same<I, O>
      , dtl::is_trivially_copy_constructible< typename ::boost::container::iter_value<I>::type >
      >
{};

template <typename I, typename O, typename R>
struct enable_if_memtransfer_copy_constructible
   : enable_if<dtl::is_memtransfer_copy_constructible<I, O>, R>
{};

template <typename I, typename O, typename R>
struct disable_if_memtransfer_copy_constructible
   : disable_if<dtl::is_memtransfer_copy_constructible<I, O>, R>
{};

template <typename I, typename O, typename R>
struct enable_if_memtransfer_copy_assignable
   : enable_if<dtl::is_memtransfer_copy_assignable<I, O>, R>
{};

template <typename I, typename O, typename R>
struct disable_if_memtransfer_copy_assignable
   : disable_if<dtl::is_memtransfer_copy_assignable<I, O>, R>
{};

template
   <typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE F memmove(I f, I l, F r) BOOST_NOEXCEPT_OR_NOTHROW
{
   typedef typename boost::container::iter_value<I>::type      value_type;
   typedef typename boost::container::iterator_traits<F>::difference_type r_difference_type;
   value_type *const dest_raw = boost::movelib::iterator_to_raw_pointer(r);
   const value_type *const beg_raw = boost::movelib::iterator_to_raw_pointer(f);
   const value_type *const end_raw = boost::movelib::iterator_to_raw_pointer(l);
   if(BOOST_LIKELY(beg_raw != end_raw && dest_raw && beg_raw)){
      const std::size_t n = std::size_t(end_raw - beg_raw)   ;
      std::memmove(dest_raw, beg_raw, sizeof(value_type)*n);
      r += static_cast<r_difference_type>(n);
   }
   return r;
}

template
   <typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE F memmove_n(I f, std::size_t n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{
   typedef typename boost::container::iter_value<I>::type value_type;
   typedef typename boost::container::iterator_traits<F>::difference_type r_difference_type;
   if(BOOST_LIKELY(n != 0)){
      void *dst = boost::movelib::iterator_to_raw_pointer(r);
      const void *src = boost::movelib::iterator_to_raw_pointer(f);
      if (dst && src)
         std::memmove(dst, src, sizeof(value_type)*n);
      r += static_cast<r_difference_type>(n);
   }

   return r;
}

template
   <typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE I memmove_n_source(I f, std::size_t n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{
   if(BOOST_LIKELY(n != 0)){
      typedef typename boost::container::iter_value<I>::type value_type;
      typedef typename boost::container::iterator_traits<I>::difference_type i_difference_type;
      void *dst = boost::movelib::iterator_to_raw_pointer(r);
      const void *src = boost::movelib::iterator_to_raw_pointer(f);
      if (dst && src)
         std::memmove(dst, src, sizeof(value_type)*n);
      f += static_cast<i_difference_type>(n);
   }
   return f;
}

template
   <typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE I memmove_n_source_dest(I f, std::size_t n, F &r) BOOST_NOEXCEPT_OR_NOTHROW
{
   typedef typename boost::container::iter_value<I>::type value_type;
   typedef typename boost::container::iterator_traits<F>::difference_type i_difference_type;
   typedef typename boost::container::iterator_traits<F>::difference_type f_difference_type;

   if(BOOST_LIKELY(n != 0)){
      void *dst = boost::movelib::iterator_to_raw_pointer(r);
      const void *src = boost::movelib::iterator_to_raw_pointer(f);
      if (dst && src)
         std::memmove(dst, src, sizeof(value_type)*n);
      f += i_difference_type(n);
      r += f_difference_type(n);
   }
   return f;
}

template <typename O>
struct is_memzero_initializable
{
   typedef typename ::boost::container::iterator_traits<O>::value_type value_type;
   static const bool value = are_elements_contiguous<O>::value &&
      (  dtl::is_integral<value_type>::value || dtl::is_enum<value_type>::value
      #if defined(BOOST_CONTAINER_MEMZEROED_POINTER_IS_NULL)
      || dtl::is_pointer<value_type>::value
      #endif
      #if defined(BOOST_CONTAINER_MEMZEROED_FLOATING_POINT_IS_ZERO)
      || dtl::is_floating_point<value_type>::value
      #endif
      #if defined(BOOST_CONTAINER_MEMZEROED_FLOATING_POINT_IS_ZERO) && defined(BOOST_CONTAINER_MEMZEROED_POINTER_IS_NULL)
      || dtl::is_pod<value_type>::value
      #endif
      );
};

template <typename O, typename R>
struct enable_if_memzero_initializable
   : enable_if_c<dtl::is_memzero_initializable<O>::value, R>
{};

template <typename O, typename R>
struct disable_if_memzero_initializable
   : enable_if_c<!dtl::is_memzero_initializable<O>::value, R>
{};

template <typename I, typename R>
struct enable_if_trivially_destructible
   : enable_if_c < dtl::is_trivially_destructible
                  <typename boost::container::iter_value<I>::type>::value
               , R>
{};

template <typename I, typename R>
struct disable_if_trivially_destructible
   : enable_if_c <!dtl::is_trivially_destructible
                  <typename boost::container::iter_value<I>::type>::value
               , R>
{};

}  //namespace dtl {

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_move_alloc
//
//////////////////////////////////////////////////////////////////////////////


//! <b>Effects</b>:
//!   \code
//!   for (; f != l; ++r, ++f)
//!      allocator_traits::construct(a, &*r, boost::move(*f));
//!   \endcode
//!
//! <b>Returns</b>: r
template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_move_alloc(Allocator &a, I f, I l, F r)
{
   F back = r;
   BOOST_TRY{
      while (f != l) {
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(r), boost::move(*f));
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_move_alloc(Allocator &, I f, I l, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove(f, l, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_move_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; n--; ++r, ++f)
//!      allocator_traits::construct(a, &*r, boost::move(*f));
//!   \endcode
//!
//! <b>Returns</b>: r
template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_move_alloc_n(Allocator &a, I f, std::size_t n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n) {
         --n;
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(r), boost::move(*f));
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_move_alloc_n(Allocator &, I f, std::size_t n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_move_alloc_n_source
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; n--; ++r, ++f)
//!      allocator_traits::construct(a, &*r, boost::move(*f));
//!   \endcode
//!
//! <b>Returns</b>: f (after incremented)
template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_constructible<I, F, I>::type
   uninitialized_move_alloc_n_source(Allocator &a, I f, std::size_t n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n) {
         --n;
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(r), boost::move(*f));
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return f;
}

template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_constructible<I, F, I>::type
   uninitialized_move_alloc_n_source(Allocator &, I f, std::size_t n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n_source(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_copy_alloc
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; f != l; ++r, ++f)
//!      allocator_traits::construct(a, &*r, *f);
//!   \endcode
//!
//! <b>Returns</b>: r
template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_copy_alloc(Allocator &a, I f, I l, F r)
{
   F back = r;
   BOOST_TRY{
      while (f != l) {
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(r), *f);
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_copy_alloc(Allocator &, I f, I l, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove(f, l, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_copy_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; n--; ++r, ++f)
//!      allocator_traits::construct(a, &*r, *f);
//!   \endcode
//!
//! <b>Returns</b>: r
template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_copy_alloc_n(Allocator &a, I f, std::size_t n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n) {
         --n;
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(r), *f);
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_copy_alloc_n(Allocator &, I f, std::size_t n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_copy_alloc_n_source
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; n--; ++r, ++f)
//!      allocator_traits::construct(a, &*r, *f);
//!   \endcode
//!
//! <b>Returns</b>: f (after incremented)
template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_constructible<I, F, I>::type
   uninitialized_copy_alloc_n_source(Allocator &a, I f, std::size_t n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n) {
         boost::container::construct_in_place(a, boost::movelib::iterator_to_raw_pointer(r), f);
         ++f; ++r; --n;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return f;
}

template
   <typename Allocator,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_constructible<I, F, I>::type
   uninitialized_copy_alloc_n_source(Allocator &, I f, std::size_t n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n_source(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_value_init_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; n--; ++r, ++f)
//!      allocator_traits::construct(a, &*r);
//!   \endcode
//!
//! <b>Returns</b>: r
template
   <typename Allocator,
    typename F> // F models ForwardIterator
inline typename dtl::disable_if_memzero_initializable<F, F>::type
   uninitialized_value_init_alloc_n(Allocator &a, std::size_t n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n) {
         --n;
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(r));
         ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

template
   <typename Allocator,
    typename F> // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memzero_initializable<F, F>::type
   uninitialized_value_init_alloc_n(Allocator &, std::size_t n, F r)
{
   typedef typename boost::container::iterator_traits<F>::value_type value_type;
   typedef typename boost::container::iterator_traits<F>::difference_type r_difference_type;

   if (BOOST_LIKELY(n != 0)){
      std::memset((void*)boost::movelib::iterator_to_raw_pointer(r), 0, sizeof(value_type)*n);
      r += static_cast<r_difference_type>(n);
   }
   return r;
}

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_default_init_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; n--; ++r, ++f)
//!      allocator_traits::construct(a, &*r);
//!   \endcode
//!
//! <b>Returns</b>: r
template
   <typename Allocator,
    typename F> // F models ForwardIterator
inline F uninitialized_default_init_alloc_n(Allocator &a, std::size_t n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n) {
         --n;
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(r), default_init);
         ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_fill_alloc
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; f != l; ++r, ++f)
//!      allocator_traits::construct(a, &*r, *f);
//!   \endcode
//!
//! <b>Returns</b>: r
template
   <typename Allocator,
    typename F, // F models ForwardIterator
    typename T>
inline void uninitialized_fill_alloc(Allocator &a, F f, F l, const T &t)
{
   F back = f;
   BOOST_TRY{
      while (f != l) {
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(f), t);
         ++f;
      }
   }
   BOOST_CATCH(...){
      for (; back != l; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
}


//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_fill_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; n--; ++r, ++f)
//!      allocator_traits::construct(a, &*r, v);
//!   \endcode
//!
//! <b>Returns</b>: r
template
   <typename Allocator,
    typename T,
    typename F> // F models ForwardIterator
inline F uninitialized_fill_alloc_n(Allocator &a, const T &v, std::size_t n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n) {
         --n;
         allocator_traits<Allocator>::construct(a, boost::movelib::iterator_to_raw_pointer(r), v);
         ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(back));
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

//////////////////////////////////////////////////////////////////////////////
//
//                               copy
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I,   // I models InputIterator
typename F>    // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, F>::type
   copy(I f, I l, F r)
{
   while (f != l) {
      *r = *f;
      ++f; ++r;
   }
   return r;
}

template
<typename I,   // I models InputIterator
typename F>    // F models ForwardIterator
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, F>::type
   copy(I f, I l, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove(f, l, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                               copy_n
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, F>::type
   copy_n(I f, U n, F r)
{
   while (n) {
      --n;
      *r = *f;
      ++f; ++r;
   }
   return r;
}

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_assignable<I, F, F>::type
   copy_n(I f, U n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                            copy_n_source
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, I>::type
   copy_n_source(I f, U n, F r)
{
   while (n) {
      --n;
      boost::container::assign_in_place(r, f);
      ++f; ++r;
   }
   return f;
}

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_assignable<I, F, I>::type
   copy_n_source(I f, std::size_t n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n_source(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                            copy_n_source_dest
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, I>::type
   copy_n_source_dest(I f, std::size_t n, F &r)
{
   while (n) {
      --n;
      *r = *f;
      ++f; ++r;
   }
   return f;
}

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_assignable<I, F, I>::type
   copy_n_source_dest(I f, std::size_t n, F &r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n_source_dest(f, n, r);  }

//////////////////////////////////////////////////////////////////////////////
//
//                         move
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, F>::type
   move(I f, I l, F r)
{
   while (f != l) {
      *r = ::boost::move(*f);
      ++f; ++r;
   }
   return r;
}

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, F>::type
   move(I f, I l, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove(f, l, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                         move_n
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, F>::type
   move_n(I f, U n, F r)
{
   while (n) {
      --n;
      *r = ::boost::move(*f);
      ++f; ++r;
   }
   return r;
}

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_assignable<I, F, F>::type
   move_n(I f, U n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n(f, n, r); }


//////////////////////////////////////////////////////////////////////////////
//
//                         move_backward
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I,   // I models BidirectionalIterator
typename F>    // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, F>::type
   move_backward(I f, I l, F r)
{
   while (f != l) {
      --l; --r;
      *r = ::boost::move(*l);
   }
   return r;
}

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_assignable<I, F, F>::type
   move_backward(I f, I l, F r) BOOST_NOEXCEPT_OR_NOTHROW
{
   typedef typename boost::container::iter_value<I>::type value_type;
   const std::size_t n = boost::container::iterator_udistance(f, l);
   if (BOOST_LIKELY(n != 0)){
      r -= n;
      std::memmove((boost::movelib::iterator_to_raw_pointer)(r), (boost::movelib::iterator_to_raw_pointer)(f), sizeof(value_type)*n);
   }
   return r;
}

//////////////////////////////////////////////////////////////////////////////
//
//                         move_n_source_dest
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I    // I models InputIterator
,typename U    // U models unsigned integral constant
,typename F>   // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, I>::type
   move_n_source_dest(I f, U n, F &r)
{
   while (n) {
      --n;
      *r = ::boost::move(*f);
      ++f; ++r;
   }
   return f;
}

template
<typename I    // I models InputIterator
,typename F>   // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_assignable<I, F, I>::type
   move_n_source_dest(I f, std::size_t n, F &r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n_source_dest(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                         move_n_source
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I    // I models InputIterator
,typename U    // U models unsigned integral constant
,typename F>   // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, I>::type
   move_n_source(I f, U n, F r)
{
   while (n) {
      --n;
      *r = ::boost::move(*f);
      ++f; ++r;
   }
   return f;
}

template
<typename I    // I models InputIterator
,typename F>   // F models ForwardIterator
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_memtransfer_copy_assignable<I, F, I>::type
   move_n_source(I f, std::size_t n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n_source(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                               destroy_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

template
   <typename Allocator
   ,typename I   // I models InputIterator
   ,typename U>  // U models unsigned integral constant
inline typename dtl::disable_if_trivially_destructible<I, void>::type
   destroy_alloc_n(Allocator &a, I f, U n)
{
   while(n){
      --n;
      allocator_traits<Allocator>::destroy(a, boost::movelib::iterator_to_raw_pointer(f));
      ++f;
   }
}

template
   <typename Allocator
   ,typename I   // I models InputIterator
   ,typename U>  // U models unsigned integral constant
BOOST_CONTAINER_FORCEINLINE typename dtl::enable_if_trivially_destructible<I, void>::type
   destroy_alloc_n(Allocator &, I, U)
{}

//////////////////////////////////////////////////////////////////////////////
//
//                         deep_swap_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

template
   <std::size_t MaxTmpBytes
   ,typename Allocator
   ,typename F // F models ForwardIterator
   ,typename G // G models ForwardIterator
   >
inline typename dtl::disable_if_memtransfer_copy_assignable<F, G, void>::type
   deep_swap_alloc_n( Allocator &a, F short_range_f, std::size_t  n_i, G large_range_f, std::size_t n_j)
{
   std::size_t n = 0;
   for (; n != n_i ; ++short_range_f, ++large_range_f, ++n){
      boost::adl_move_swap(*short_range_f, *large_range_f);
   }
   boost::container::uninitialized_move_alloc_n(a, large_range_f, std::size_t(n_j - n_i), short_range_f);  // may throw
   boost::container::destroy_alloc_n(a, large_range_f, std::size_t(n_j - n_i));
}

static const std::size_t DeepSwapAllocNMaxStorage = std::size_t(1) << std::size_t(11); //2K bytes

template
   <std::size_t MaxTmpBytes
   ,typename Allocator
   ,typename F // F models ForwardIterator
   ,typename G // G models ForwardIterator
   >
inline typename dtl::enable_if_c
   < dtl::is_memtransfer_copy_assignable<F, G>::value && (MaxTmpBytes <= DeepSwapAllocNMaxStorage) && false
   , void>::type
   deep_swap_alloc_n( Allocator &a, F short_range_f, std::size_t n_i, G large_range_f, std::size_t n_j)
{
   typedef typename allocator_traits<Allocator>::value_type value_type;
   typedef typename dtl::aligned_storage
      <MaxTmpBytes, dtl::alignment_of<value_type>::value>::type storage_type;
   storage_type storage;

   const std::size_t n_i_bytes = sizeof(value_type)*n_i;
   void *const large_ptr = static_cast<void*>(boost::movelib::iterator_to_raw_pointer(large_range_f));
   void *const short_ptr = static_cast<void*>(boost::movelib::iterator_to_raw_pointer(short_range_f));
   void *const stora_ptr = static_cast<void*>(boost::movelib::iterator_to_raw_pointer(storage.data));
   std::memcpy(stora_ptr, large_ptr, n_i_bytes);
   std::memcpy(large_ptr, short_ptr, n_i_bytes);
   std::memcpy(short_ptr, stora_ptr, n_i_bytes);
   boost::container::iterator_uadvance(large_range_f, n_i);
   boost::container::iterator_uadvance(short_range_f, n_i);
   boost::container::uninitialized_move_alloc_n(a, large_range_f, std::size_t(n_j - n_i), short_range_f);  // may throw
   boost::container::destroy_alloc_n(a, large_range_f, std::size_t(n_j - n_i));
}

template
   <std::size_t MaxTmpBytes
   ,typename Allocator
   ,typename F // F models ForwardIterator
   ,typename G // G models ForwardIterator
   >
inline typename dtl::enable_if_c
   < dtl::is_memtransfer_copy_assignable<F, G>::value && true//(MaxTmpBytes > DeepSwapAllocNMaxStorage)
   , void>::type
   deep_swap_alloc_n( Allocator &a, F short_range_f, std::size_t n_i, G large_range_f, std::size_t n_j)
{
   typedef typename allocator_traits<Allocator>::value_type value_type;
   typedef typename dtl::aligned_storage
      <DeepSwapAllocNMaxStorage, dtl::alignment_of<value_type>::value>::type storage_type;
   storage_type storage;
   const std::size_t sizeof_storage = sizeof(storage);

   std::size_t n_i_bytes = sizeof(value_type)*n_i;
   char *large_ptr = static_cast<char*>(static_cast<void*>(boost::movelib::iterator_to_raw_pointer(large_range_f)));
   char *short_ptr = static_cast<char*>(static_cast<void*>(boost::movelib::iterator_to_raw_pointer(short_range_f)));
   char *stora_ptr = static_cast<char*>(static_cast<void*>(storage.data));

   std::size_t szt_times = n_i_bytes/sizeof_storage;
   const std::size_t szt_rem = n_i_bytes%sizeof_storage;

   //Loop unrolling using Duff's device, as it seems it helps on some architectures
   const std::size_t Unroll = 4;
   std::size_t n = (szt_times + (Unroll-1))/Unroll;
   const std::size_t branch_number = (!szt_times)*Unroll + (szt_times % Unroll);
   switch(branch_number){
      case 4:
         break;
      case 0: do{
         std::memcpy(stora_ptr, large_ptr, sizeof_storage);
         std::memcpy(large_ptr, short_ptr, sizeof_storage);
         std::memcpy(short_ptr, stora_ptr, sizeof_storage);
         large_ptr += sizeof_storage;
         short_ptr += sizeof_storage;
         BOOST_FALLTHROUGH;
      case 3:
         std::memcpy(stora_ptr, large_ptr, sizeof_storage);
         std::memcpy(large_ptr, short_ptr, sizeof_storage);
         std::memcpy(short_ptr, stora_ptr, sizeof_storage);
         large_ptr += sizeof_storage;
         short_ptr += sizeof_storage;
         BOOST_FALLTHROUGH;
      case 2:
         std::memcpy(stora_ptr, large_ptr, sizeof_storage);
         std::memcpy(large_ptr, short_ptr, sizeof_storage);
         std::memcpy(short_ptr, stora_ptr, sizeof_storage);
         large_ptr += sizeof_storage;
         short_ptr += sizeof_storage;
         BOOST_FALLTHROUGH;
      case 1:
         std::memcpy(stora_ptr, large_ptr, sizeof_storage);
         std::memcpy(large_ptr, short_ptr, sizeof_storage);
         std::memcpy(short_ptr, stora_ptr, sizeof_storage);
         large_ptr += sizeof_storage;
         short_ptr += sizeof_storage;
         } while(--n);
   }
   std::memcpy(stora_ptr, large_ptr, szt_rem);
   std::memcpy(large_ptr, short_ptr, szt_rem);
   std::memcpy(short_ptr, stora_ptr, szt_rem);
   boost::container::iterator_uadvance(large_range_f, n_i);
   boost::container::iterator_uadvance(short_range_f, n_i);
   boost::container::uninitialized_move_alloc_n(a, large_range_f, std::size_t(n_j - n_i), short_range_f);  // may throw
   boost::container::destroy_alloc_n(a, large_range_f, std::size_t(n_j - n_i));
}


//////////////////////////////////////////////////////////////////////////////
//
//                         copy_assign_range_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

template
   <typename Allocator
   ,typename I // F models InputIterator
   ,typename O // G models OutputIterator
   >
void copy_assign_range_alloc_n( Allocator &a, I inp_start, std::size_t n_i, O out_start, std::size_t n_o )
{
   if (n_o < n_i){
      inp_start = boost::container::copy_n_source_dest(inp_start, n_o, out_start);     // may throw
      boost::container::uninitialized_copy_alloc_n(a, inp_start, std::size_t(n_i - n_o), out_start);// may throw
   }
   else{
      out_start = boost::container::copy_n(inp_start, n_i, out_start);  // may throw
      boost::container::destroy_alloc_n(a, out_start, std::size_t(n_o - n_i));
   }
}

//////////////////////////////////////////////////////////////////////////////
//
//                         move_assign_range_alloc_n
//
//////////////////////////////////////////////////////////////////////////////

template
   <typename Allocator
   ,typename I // F models InputIterator
   ,typename O // G models OutputIterator
   >
void move_assign_range_alloc_n( Allocator &a, I inp_start, std::size_t n_i, O out_start, std::size_t n_o )
{
   if (n_o < n_i){
      inp_start = boost::container::move_n_source_dest(inp_start, n_o, out_start);  // may throw
      boost::container::uninitialized_move_alloc_n(a, inp_start, std::size_t(n_i - n_o), out_start);  // may throw
   }
   else{
      out_start = boost::container::move_n(inp_start, n_i, out_start);  // may throw
      boost::container::destroy_alloc_n(a, out_start, std::size_t(n_o - n_i));
   }
}

template<class Allocator, class Iterator>
struct array_destructor
{
   typedef typename ::boost::container::iterator_traits<Iterator>::value_type value_type;
   typedef typename dtl::if_c
      <dtl::is_trivially_destructible<value_type>::value
      ,dtl::null_scoped_destructor_range<Allocator>
      ,dtl::scoped_destructor_range<Allocator>
      >::type type;
};

template
   <typename Allocator
   ,typename F // F models ForwardIterator
   ,typename O // G models OutputIterator
   ,typename InsertionProxy
   >
void uninitialized_move_and_insert_alloc
   ( Allocator &a
   , F first
   , F pos
   , F last
   , O d_first
   , std::size_t n
   , InsertionProxy insert_range_proxy)
{
   typedef typename array_destructor<Allocator, F>::type array_destructor_t;

   //Anti-exception rollbacks
   array_destructor_t new_values_destroyer(d_first, d_first, a);

   //Initialize with [begin(), pos) old buffer
   //the start of the new buffer
   O d_last = ::boost::container::uninitialized_move_alloc(a, first, pos, d_first);
   new_values_destroyer.set_end(d_last);
   //Initialize new objects, starting from previous point
   insert_range_proxy.uninitialized_copy_n_and_update(a, d_last, n);
   d_last += n;
   new_values_destroyer.set_end(d_last);
   //Initialize from the rest of the old buffer,
   //starting from previous point
   (void) ::boost::container::uninitialized_move_alloc(a, pos, last, d_last);
   //All construction successful, disable rollbacks
   new_values_destroyer.release();
}

template
   <typename Allocator
   ,typename F // F models ForwardIterator
   ,typename InsertionProxy
   >
void expand_forward_and_insert_alloc
   ( Allocator &a
   , F pos
   , F last
   , std::size_t n
   , InsertionProxy insert_range_proxy)
{
   typedef typename array_destructor<Allocator, F>::type array_destructor_t;

   if (BOOST_UNLIKELY(!n)){
      return;
   }
   else if (last == pos){
      insert_range_proxy.uninitialized_copy_n_and_update(a, last, n);
   }
   else{
      const std::size_t elems_after = static_cast<std::size_t>(last - pos);
      if(elems_after >= n){
         //New elements can be just copied.
         //Move to uninitialized memory last objects
         ::boost::container::uninitialized_move_alloc_n(a, last - n, n, last);
         array_destructor_t on_exception(last, last, a);
         //Copy previous to last objects to the initialized end
         boost::container::move_backward(pos, last - n, last);
         //Insert new objects in the pos
         insert_range_proxy.copy_n_and_update(a, pos, n);
         on_exception.release();
      }
      else {
         //The new elements don't fit in the [pos, end()) range.
         //Copy old [pos, end()) elements to the uninitialized memory (a gap is created)
         F new_last = ::boost::container::uninitialized_move_alloc(a, pos, last, pos + n);
         array_destructor_t on_exception(pos + n, new_last, a);
         //Copy first new elements in pos (gap is still there)
         insert_range_proxy.copy_n_and_update(a, pos, elems_after);
         //Copy to the beginning of the unallocated zone the last new elements (the gap is closed).
         insert_range_proxy.uninitialized_copy_n_and_update(a, last, std::size_t(n - elems_after));
         on_exception.release();
      }
   }
}

}  //namespace container {
}  //namespace boost {

//#pragma GCC diagnostic ignored "-Wclass-memaccess"
#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#pragma GCC diagnostic pop
#endif

#endif   //#ifndef BOOST_CONTAINER_DETAIL_COPY_MOVE_ALGO_HPP

/* copy_move_algo.hpp
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
*/