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
      , is_same< typename remove_const< typename ::boost::container::iterator_traits<I>::value_type >::type
               , typename ::boost::container::iterator_traits<O>::value_type
               >
      >
{};

template <typename I, typename O>
struct is_memtransfer_copy_assignable
   : boost::move_detail::and_
      < are_contiguous_and_same<I, O>
      , dtl::is_trivially_copy_assignable< typename ::boost::container::iterator_traits<I>::value_type >
      >
{};

template <typename I, typename O>
struct is_memtransfer_copy_constructible
   : boost::move_detail::and_
      < are_contiguous_and_same<I, O>
      , dtl::is_trivially_copy_constructible< typename ::boost::container::iterator_traits<I>::value_type >
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
inline F memmove(I f, I l, F r) BOOST_NOEXCEPT_OR_NOTHROW
{
   typedef typename boost::container::iterator_traits<I>::value_type value_type;
   value_type *const dest_raw = boost::movelib::iterator_to_raw_pointer(r);
   const value_type *const beg_raw = boost::movelib::iterator_to_raw_pointer(f);
   const value_type *const end_raw = boost::movelib::iterator_to_raw_pointer(l);
   if(BOOST_LIKELY(beg_raw != end_raw && dest_raw && beg_raw)){
      const typename boost::container::iterator_traits<I>::difference_type n = end_raw - beg_raw;
      std::memmove(dest_raw, beg_raw, sizeof(value_type)*n);
      boost::container::iterator_advance(r, n);
   }
   return r;
}

template
   <typename I, // I models InputIterator
    typename U, // U models unsigned integral constant
    typename F> // F models ForwardIterator
F memmove_n(I f, U n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{
   typedef typename boost::container::iterator_traits<I>::value_type value_type;
   if(BOOST_LIKELY(n)){
      std::memmove(boost::movelib::iterator_to_raw_pointer(r), boost::movelib::iterator_to_raw_pointer(f), sizeof(value_type)*n);
      boost::container::iterator_advance(r, n);
   }

   return r;
}

template
   <typename I, // I models InputIterator
    typename U, // U models unsigned integral constant
    typename F> // F models ForwardIterator
I memmove_n_source(I f, U n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{
   if(BOOST_LIKELY(n)){
      typedef typename boost::container::iterator_traits<I>::value_type value_type;
      std::memmove(boost::movelib::iterator_to_raw_pointer(r), boost::movelib::iterator_to_raw_pointer(f), sizeof(value_type)*n);
      boost::container::iterator_advance(f, n);
   }
   return f;
}

template
   <typename I, // I models InputIterator
    typename U, // U models unsigned integral constant
    typename F> // F models ForwardIterator
I memmove_n_source_dest(I f, U n, F &r) BOOST_NOEXCEPT_OR_NOTHROW
{
   typedef typename boost::container::iterator_traits<I>::value_type value_type;
   if(BOOST_LIKELY(n)){
      std::memmove(boost::movelib::iterator_to_raw_pointer(r), boost::movelib::iterator_to_raw_pointer(f), sizeof(value_type)*n);
      boost::container::iterator_advance(f, n);
      boost::container::iterator_advance(r, n);
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
                  <typename boost::container::iterator_traits<I>::value_type>::value
               , R>
{};

template <typename I, typename R>
struct disable_if_trivially_destructible
   : enable_if_c <!dtl::is_trivially_destructible
                  <typename boost::container::iterator_traits<I>::value_type>::value
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
inline typename dtl::enable_if_memtransfer_copy_constructible<I, F, F>::type
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
   uninitialized_move_alloc_n(Allocator &a, I f, typename boost::container::allocator_traits<Allocator>::size_type n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n--) {
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
inline typename dtl::enable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_move_alloc_n(Allocator &, I f, typename boost::container::allocator_traits<Allocator>::size_type n, F r) BOOST_NOEXCEPT_OR_NOTHROW
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
   uninitialized_move_alloc_n_source(Allocator &a, I f, typename boost::container::allocator_traits<Allocator>::size_type n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n--) {
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
inline typename dtl::enable_if_memtransfer_copy_constructible<I, F, I>::type
   uninitialized_move_alloc_n_source(Allocator &, I f, typename boost::container::allocator_traits<Allocator>::size_type n, F r) BOOST_NOEXCEPT_OR_NOTHROW
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
inline typename dtl::enable_if_memtransfer_copy_constructible<I, F, F>::type
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
   uninitialized_copy_alloc_n(Allocator &a, I f, typename boost::container::allocator_traits<Allocator>::size_type n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n--) {
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
inline typename dtl::enable_if_memtransfer_copy_constructible<I, F, F>::type
   uninitialized_copy_alloc_n(Allocator &, I f, typename boost::container::allocator_traits<Allocator>::size_type n, F r) BOOST_NOEXCEPT_OR_NOTHROW
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
   uninitialized_copy_alloc_n_source(Allocator &a, I f, typename boost::container::allocator_traits<Allocator>::size_type n, F r)
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
inline typename dtl::enable_if_memtransfer_copy_constructible<I, F, I>::type
   uninitialized_copy_alloc_n_source(Allocator &, I f, typename boost::container::allocator_traits<Allocator>::size_type n, F r) BOOST_NOEXCEPT_OR_NOTHROW
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
   uninitialized_value_init_alloc_n(Allocator &a, typename boost::container::allocator_traits<Allocator>::size_type n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n--) {
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
inline typename dtl::enable_if_memzero_initializable<F, F>::type
   uninitialized_value_init_alloc_n(Allocator &, typename boost::container::allocator_traits<Allocator>::size_type n, F r)
{
   typedef typename boost::container::iterator_traits<F>::value_type value_type;
   std::memset((void*)boost::movelib::iterator_to_raw_pointer(r), 0, sizeof(value_type)*n);
   boost::container::iterator_advance(r, n);
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
inline F uninitialized_default_init_alloc_n(Allocator &a, typename boost::container::allocator_traits<Allocator>::size_type n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n--) {
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
inline F uninitialized_fill_alloc_n(Allocator &a, const T &v, typename boost::container::allocator_traits<Allocator>::size_type n, F r)
{
   F back = r;
   BOOST_TRY{
      while (n--) {
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
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, F>::type
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
   while (n--) {
      boost::container::assign_in_place(r, f);
      ++f; ++r;
   }
   return f;
}

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, I>::type
   copy_n_source(I f, U n, F r) BOOST_NOEXCEPT_OR_NOTHROW
{  return dtl::memmove_n_source(f, n, r); }

//////////////////////////////////////////////////////////////////////////////
//
//                            copy_n_source_dest
//
//////////////////////////////////////////////////////////////////////////////

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
inline typename dtl::disable_if_memtransfer_copy_assignable<I, F, I>::type
   copy_n_source_dest(I f, U n, F &r)
{
   while (n--) {
      *r = *f;
      ++f; ++r;
   }
   return f;
}

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, I>::type
   copy_n_source_dest(I f, U n, F &r) BOOST_NOEXCEPT_OR_NOTHROW
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
   while (n--) {
      *r = ::boost::move(*f);
      ++f; ++r;
   }
   return r;
}

template
<typename I,   // I models InputIterator
typename U,   // U models unsigned integral constant
typename F>   // F models ForwardIterator
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, F>::type
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
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, F>::type
   move_backward(I f, I l, F r) BOOST_NOEXCEPT_OR_NOTHROW
{
   typedef typename boost::container::iterator_traits<I>::value_type value_type;
   const typename boost::container::iterator_traits<I>::difference_type n = boost::container::iterator_distance(f, l);
   r -= n;
   std::memmove((boost::movelib::iterator_to_raw_pointer)(r), (boost::movelib::iterator_to_raw_pointer)(f), sizeof(value_type)*n);
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
   while (n--) {
      *r = ::boost::move(*f);
      ++f; ++r;
   }
   return f;
}

template
<typename I    // I models InputIterator
,typename U    // U models unsigned integral constant
,typename F>   // F models ForwardIterator
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, I>::type
   move_n_source_dest(I f, U n, F &r) BOOST_NOEXCEPT_OR_NOTHROW
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
   while (n--) {
      *r = ::boost::move(*f);
      ++f; ++r;
   }
   return f;
}

template
<typename I    // I models InputIterator
,typename U    // U models unsigned integral constant
,typename F>   // F models ForwardIterator
inline typename dtl::enable_if_memtransfer_copy_assignable<I, F, I>::type
   move_n_source(I f, U n, F r) BOOST_NOEXCEPT_OR_NOTHROW
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
inline typename dtl::enable_if_trivially_destructible<I, void>::type
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
   deep_swap_alloc_n( Allocator &a, F short_range_f, typename allocator_traits<Allocator>::size_type n_i
                    , G large_range_f, typename allocator_traits<Allocator>::size_type n_j)
{
   typename allocator_traits<Allocator>::size_type n = 0;
   for (; n != n_i ; ++short_range_f, ++large_range_f, ++n){
      boost::adl_move_swap(*short_range_f, *large_range_f);
   }
   boost::container::uninitialized_move_alloc_n(a, large_range_f, n_j - n_i, short_range_f);  // may throw
   boost::container::destroy_alloc_n(a, large_range_f, n_j - n_i);
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
   deep_swap_alloc_n( Allocator &a, F short_range_f, typename allocator_traits<Allocator>::size_type n_i
                    , G large_range_f, typename allocator_traits<Allocator>::size_type n_j)
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
   boost::container::iterator_advance(large_range_f, n_i);
   boost::container::iterator_advance(short_range_f, n_i);
   boost::container::uninitialized_move_alloc_n(a, large_range_f, n_j - n_i, short_range_f);  // may throw
   boost::container::destroy_alloc_n(a, large_range_f, n_j - n_i);
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
   deep_swap_alloc_n( Allocator &a, F short_range_f, typename allocator_traits<Allocator>::size_type n_i
                    , G large_range_f, typename allocator_traits<Allocator>::size_type n_j)
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
   boost::container::iterator_advance(large_range_f, n_i);
   boost::container::iterator_advance(short_range_f, n_i);
   boost::container::uninitialized_move_alloc_n(a, large_range_f, n_j - n_i, short_range_f);  // may throw
   boost::container::destroy_alloc_n(a, large_range_f, n_j - n_i);
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
void copy_assign_range_alloc_n( Allocator &a, I inp_start, typename allocator_traits<Allocator>::size_type n_i
                              , O out_start, typename allocator_traits<Allocator>::size_type n_o )
{
   if (n_o < n_i){
      inp_start = boost::container::copy_n_source_dest(inp_start, n_o, out_start);     // may throw
      boost::container::uninitialized_copy_alloc_n(a, inp_start, n_i - n_o, out_start);// may throw
   }
   else{
      out_start = boost::container::copy_n(inp_start, n_i, out_start);  // may throw
      boost::container::destroy_alloc_n(a, out_start, n_o - n_i);
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
void move_assign_range_alloc_n( Allocator &a, I inp_start, typename allocator_traits<Allocator>::size_type n_i
                              , O out_start, typename allocator_traits<Allocator>::size_type n_o )
{
   if (n_o < n_i){
      inp_start = boost::container::move_n_source_dest(inp_start, n_o, out_start);  // may throw
      boost::container::uninitialized_move_alloc_n(a, inp_start, n_i - n_o, out_start);  // may throw
   }
   else{
      out_start = boost::container::move_n(inp_start, n_i, out_start);  // may throw
      boost::container::destroy_alloc_n(a, out_start, n_o - n_i);
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