//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_MERGE_HPP
#define BOOST_MOVE_MERGE_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/move/algo/move.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/algo/detail/basic_op.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/destruct_n.hpp>
#include <boost/move/algo/predicate.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>
#include <boost/assert.hpp>
#include <cstddef>

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

namespace boost {
namespace movelib {

template<class T, class RandRawIt = T*, class SizeType = typename iter_size<RandRawIt>::type>
class adaptive_xbuf
{
   adaptive_xbuf(const adaptive_xbuf &);
   adaptive_xbuf & operator=(const adaptive_xbuf &);

   #if !defined(UINTPTR_MAX)
   typedef std::size_t uintptr_t;
   #endif

   public:
   typedef RandRawIt iterator;
   typedef SizeType  size_type;

   BOOST_MOVE_FORCEINLINE adaptive_xbuf()
      : m_ptr(), m_size(0), m_capacity(0)
   {}

   BOOST_MOVE_FORCEINLINE adaptive_xbuf(RandRawIt raw_memory, size_type cap)
      : m_ptr(raw_memory), m_size(0), m_capacity(cap)
   {}

   template<class RandIt>
   void move_assign(RandIt first, size_type n)
   {
      typedef typename iterator_traits<RandIt>::difference_type rand_diff_t;
      if(n <= m_size){
         boost::move(first, first+rand_diff_t(n), m_ptr);
         size_type sz = m_size;
         while(sz-- != n){
            m_ptr[sz].~T();
         }
         m_size = n;
      }
      else{
         RandRawIt result = boost::move(first, first+rand_diff_t(m_size), m_ptr);
         boost::uninitialized_move(first+rand_diff_t(m_size), first+rand_diff_t(n), result);
         m_size = n;
      }
   }

   template<class RandIt>
   void push_back(RandIt first, size_type n)
   {
      BOOST_ASSERT(m_capacity - m_size >= n);
      boost::uninitialized_move(first, first+n, m_ptr+m_size);
      m_size += n;
   }

   template<class RandIt>
   iterator add(RandIt it)
   {
      BOOST_ASSERT(m_size < m_capacity);
      RandRawIt p_ret = m_ptr + m_size;
      ::new(&*p_ret) T(::boost::move(*it));
      ++m_size;
      return p_ret;
   }

   template<class RandIt>
   void insert(iterator pos, RandIt it)
   {
      if(pos == (m_ptr + m_size)){
         this->add(it);
      }
      else{
         this->add(m_ptr+m_size-1);
         //m_size updated
         boost::move_backward(pos, m_ptr+m_size-2, m_ptr+m_size-1);
         *pos = boost::move(*it);
      }
   }

   BOOST_MOVE_FORCEINLINE void set_size(size_type sz)
   {
      m_size = sz;
   }

   void shrink_to_fit(size_type const sz)
   {
      if(m_size > sz){
         for(size_type szt_i = sz; szt_i != m_size; ++szt_i){
            m_ptr[szt_i].~T();
         }
         m_size = sz;
      }
   }

   void initialize_until(size_type const sz, T &t)
   {
      BOOST_ASSERT(m_size < m_capacity);
      if(m_size < sz){
         BOOST_TRY
         {
            ::new((void*)&m_ptr[m_size]) T(::boost::move(t));
            ++m_size;
            for(; m_size != sz; ++m_size){
               ::new((void*)&m_ptr[m_size]) T(::boost::move(m_ptr[m_size-1]));
            }
            t = ::boost::move(m_ptr[m_size-1]);
         }
         BOOST_CATCH(...)
         {
            while(m_size)
            {
               --m_size;
               m_ptr[m_size].~T();
            }
         }
         BOOST_CATCH_END
      }
   }

   private:
   template<class RIt>
   BOOST_MOVE_FORCEINLINE static bool is_raw_ptr(RIt)
   {
      return false;
   }

   BOOST_MOVE_FORCEINLINE static bool is_raw_ptr(T*)
   {
      return true;
   }

   public:
   template<class U>
   bool supports_aligned_trailing(size_type sz, size_type trail_count) const
   {
      if(this->is_raw_ptr(this->data()) && m_capacity){
         uintptr_t u_addr_sz = uintptr_t(&*(this->data()+sz));
         uintptr_t u_addr_cp = uintptr_t(&*(this->data()+this->capacity()));
         u_addr_sz = ((u_addr_sz + sizeof(U)-1)/sizeof(U))*sizeof(U);
         return (u_addr_cp >= u_addr_sz) && ((u_addr_cp - u_addr_sz)/sizeof(U) >= trail_count);
      }
      return false;
   }

   template<class U>
   BOOST_MOVE_FORCEINLINE U *aligned_trailing() const
   {
      return this->aligned_trailing<U>(this->size());
   }

   template<class U>
   BOOST_MOVE_FORCEINLINE U *aligned_trailing(size_type pos) const
   {
      uintptr_t u_addr = uintptr_t(&*(this->data()+pos));
      u_addr = ((u_addr + sizeof(U)-1)/sizeof(U))*sizeof(U);
      return (U*)u_addr;
   }

   BOOST_MOVE_FORCEINLINE ~adaptive_xbuf()
   {
      this->clear();
   }

   BOOST_MOVE_FORCEINLINE size_type capacity() const
   {  return m_capacity;   }

   BOOST_MOVE_FORCEINLINE iterator data() const
   {  return m_ptr;   }

   BOOST_MOVE_FORCEINLINE iterator begin() const
   {  return m_ptr;   }

   BOOST_MOVE_FORCEINLINE iterator end() const
   {  return m_ptr+m_size;   }

   BOOST_MOVE_FORCEINLINE size_type size() const
   {  return m_size;   }

   BOOST_MOVE_FORCEINLINE bool empty() const
   {  return !m_size;   }

   BOOST_MOVE_FORCEINLINE void clear()
   {
      this->shrink_to_fit(0u);
   }

   private:
   RandRawIt m_ptr;
   size_type m_size;
   size_type m_capacity;
};

template<class Iterator, class SizeType, class Op>
class range_xbuf
{
   range_xbuf(const range_xbuf &);
   range_xbuf & operator=(const range_xbuf &);

   public:
   typedef SizeType size_type;
   typedef Iterator iterator;

   range_xbuf(Iterator first, Iterator last)
      : m_first(first), m_last(first), m_cap(last)
   {}

   template<class RandIt>
   void move_assign(RandIt first, size_type n)
   {
      BOOST_ASSERT(size_type(n) <= size_type(m_cap-m_first));
      typedef typename iter_difference<RandIt>::type d_type;
      m_last = Op()(forward_t(), first, first+d_type(n), m_first);
   }

   ~range_xbuf()
   {}

   size_type capacity() const
   {  return m_cap-m_first;   }

   Iterator data() const
   {  return m_first;   }

   Iterator end() const
   {  return m_last;   }

   size_type size() const
   {  return m_last-m_first;   }

   bool empty() const
   {  return m_first == m_last;   }

   void clear()
   {
      m_last = m_first;
   }

   template<class RandIt>
   iterator add(RandIt it)
   {
      Iterator pos(m_last);
      *pos = boost::move(*it);
      ++m_last;
      return pos;
   }

   void set_size(size_type sz)
   {
      m_last  = m_first;
      m_last += sz;
   }

   private:
   Iterator const m_first;
   Iterator m_last;
   Iterator const m_cap;
};



// @cond

/*
template<typename Unsigned>
inline Unsigned gcd(Unsigned x, Unsigned y)
{
   if(0 == ((x &(x-1)) | (y & (y-1)))){
      return x < y ? x : y;
   }
   else{
      do
      {
         Unsigned t = x % y;
         x = y;
         y = t;
      } while (y);
      return x;
   }
}
*/

//Modified version from "An Optimal In-Place Array Rotation Algorithm", Ching-Kuang Shene
template<typename Unsigned>
Unsigned gcd(Unsigned x, Unsigned y)
{
   if(0 == ((x &(x-1)) | (y & (y-1)))){
      return x < y ? x : y;
   }
   else{
      Unsigned z = 1;
      while((!(x&1)) & (!(y&1))){
         z = Unsigned(z << 1);
         x = Unsigned(x >> 1);
         y = Unsigned(y >> 1);
      }
      while(x && y){
         if(!(x&1))
            x = Unsigned(x >> 1);
         else if(!(y&1))
            y = Unsigned (y >> 1);
         else if(x >=y)
            x = Unsigned((x-y) >> 1u);
         else
            y = Unsigned((y-x) >> 1);
      }
      return Unsigned(z*(x+y));
   }
}

template<typename RandIt>
RandIt rotate_gcd(RandIt first, RandIt middle, RandIt last)
{
   typedef typename iter_size<RandIt>::type size_type;
   typedef typename iterator_traits<RandIt>::value_type value_type;

   if(first == middle)
      return last;
   if(middle == last)
      return first;
   const size_type middle_pos = size_type(middle - first);
   RandIt ret = last - middle_pos;
   if (middle == ret){
      boost::adl_move_swap_ranges(first, middle, middle);
   }
   else{
      const size_type length = size_type(last - first);
      for( RandIt it_i(first), it_gcd(it_i + gcd(length, middle_pos))
         ; it_i != it_gcd
         ; ++it_i){
         value_type temp(boost::move(*it_i));
         RandIt it_j = it_i;
         RandIt it_k = it_j+middle_pos;
         do{
            *it_j = boost::move(*it_k);
            it_j = it_k;
            size_type const left = size_type(last - it_j);
            it_k = left > middle_pos ? it_j + middle_pos : first + middle_pos - left;
         } while(it_k != it_i);
         *it_j = boost::move(temp);
      }
   }
   return ret;
}

template <class RandIt, class T, class Compare>
RandIt lower_bound
   (RandIt first, const RandIt last, const T& key, Compare comp)
{
   typedef typename iter_size<RandIt>::type size_type;
   size_type len = size_type(last - first);
   RandIt middle;

   while (len) {
      size_type step = size_type(len >> 1);
      middle = first;
      middle += step;

      if (comp(*middle, key)) {
         first = ++middle;
         len = size_type(len - (step + 1));
      }
      else{
         len = step;
      }
   }
   return first;
}

template <class RandIt, class T, class Compare>
RandIt upper_bound
   (RandIt first, const RandIt last, const T& key, Compare comp)
{
   typedef typename iter_size<RandIt>::type size_type;
   size_type len = size_type(last - first);
   RandIt middle;

   while (len) {
      size_type step = size_type(len >> 1);
      middle = first;
      middle += step;

      if (!comp(key, *middle)) {
         first = ++middle;
         len = size_type(len - (step + 1));
      }
      else{
         len = step;
      }
   }
   return first;
}


template<class RandIt, class Compare, class Op>
void op_merge_left( RandIt buf_first
                    , RandIt first1
                    , RandIt const last1
                    , RandIt const last2
                    , Compare comp
                    , Op op)
{
   for(RandIt first2=last1; first2 != last2; ++buf_first){
      if(first1 == last1){
         op(forward_t(), first2, last2, buf_first);
         return;
      }
      else if(comp(*first2, *first1)){
         op(first2, buf_first);
         ++first2;
      }
      else{
         op(first1, buf_first);
         ++first1;
      }
   }
   if(buf_first != first1){//In case all remaining elements are in the same place
                           //(e.g. buffer is exactly the size of the second half
                           //and all elements from the second half are less)
      op(forward_t(), first1, last1, buf_first);
   }
}

// [buf_first, first1) -> buffer
// [first1, last1) merge [last1,last2) -> [buf_first,buf_first+(last2-first1))
// Elements from buffer are moved to [last2 - (first1-buf_first), last2)
// Note: distance(buf_first, first1) >= distance(last1, last2), so no overlapping occurs
template<class RandIt, class Compare>
void merge_left
   (RandIt buf_first, RandIt first1, RandIt const last1, RandIt const last2, Compare comp)
{
   op_merge_left(buf_first, first1, last1, last2, comp, move_op());
}

// [buf_first, first1) -> buffer
// [first1, last1) merge [last1,last2) -> [buf_first,buf_first+(last2-first1))
// Elements from buffer are swapped to [last2 - (first1-buf_first), last2)
// Note: distance(buf_first, first1) >= distance(last1, last2), so no overlapping occurs
template<class RandIt, class Compare>
void swap_merge_left
   (RandIt buf_first, RandIt first1, RandIt const last1, RandIt const last2, Compare comp)
{
   op_merge_left(buf_first, first1, last1, last2, comp, swap_op());
}

template<class RandIt, class Compare, class Op>
void op_merge_right
   (RandIt const first1, RandIt last1, RandIt last2, RandIt buf_last, Compare comp, Op op)
{
   RandIt const first2 = last1;
   while(first1 != last1){
      if(last2 == first2){
         op(backward_t(), first1, last1, buf_last);
         return;
      }
      --last2;
      --last1;
      --buf_last;
      if(comp(*last2, *last1)){
         op(last1, buf_last);
         ++last2;
      }
      else{
         op(last2, buf_last);
         ++last1;
      }
   }
   if(last2 != buf_last){  //In case all remaining elements are in the same place
                           //(e.g. buffer is exactly the size of the first half
                           //and all elements from the second half are less)
      op(backward_t(), first2, last2, buf_last);
   }
}

// [last2, buf_last) - buffer
// [first1, last1) merge [last1,last2) -> [first1+(buf_last-last2), buf_last)
// Note: distance[last2, buf_last) >= distance[first1, last1), so no overlapping occurs
template<class RandIt, class Compare>
void merge_right
   (RandIt first1, RandIt last1, RandIt last2, RandIt buf_last, Compare comp)
{
   op_merge_right(first1, last1, last2, buf_last, comp, move_op());
}

// [last2, buf_last) - buffer
// [first1, last1) merge [last1,last2) -> [first1+(buf_last-last2), buf_last)
// Note: distance[last2, buf_last) >= distance[first1, last1), so no overlapping occurs
template<class RandIt, class Compare>
void swap_merge_right
   (RandIt first1, RandIt last1, RandIt last2, RandIt buf_last, Compare comp)
{
   op_merge_right(first1, last1, last2, buf_last, comp, swap_op());
}

///////////////////////////////////////////////////////////////////////////////
//
//                            BUFFERED MERGE
//
///////////////////////////////////////////////////////////////////////////////
template<class RandIt, class Compare, class Op, class Buf>
void op_buffered_merge
      ( RandIt first, RandIt const middle, RandIt last
      , Compare comp, Op op
      , Buf &xbuf)
{
   if(first != middle && middle != last && comp(*middle, middle[-1])){
      typedef typename iter_size<RandIt>::type   size_type;
      size_type const len1 = size_type(middle-first);
      size_type const len2 = size_type(last-middle);
      if(len1 <= len2){
         first = boost::movelib::upper_bound(first, middle, *middle, comp);
         xbuf.move_assign(first, size_type(middle-first));
         op_merge_with_right_placed
            (xbuf.data(), xbuf.end(), first, middle, last, comp, op);
      }
      else{
         last = boost::movelib::lower_bound(middle, last, middle[-1], comp);
         xbuf.move_assign(middle, size_type(last-middle));
         op_merge_with_left_placed
            (first, middle, last, xbuf.data(), xbuf.end(), comp, op);
      }
   }
}

template<class RandIt, class Compare, class XBuf>
void buffered_merge
      ( RandIt first, RandIt const middle, RandIt last
      , Compare comp
      , XBuf &xbuf)
{
   op_buffered_merge(first, middle, last, comp, move_op(), xbuf);
}

//Complexity: min(len1,len2)^2 + max(len1,len2)
template<class RandIt, class Compare>
void merge_bufferless_ON2(RandIt first, RandIt middle, RandIt last, Compare comp)
{
   if((middle - first) < (last - middle)){
      while(first != middle){
         RandIt const old_last1 = middle;
         middle = boost::movelib::lower_bound(middle, last, *first, comp);
         first = rotate_gcd(first, old_last1, middle);
         if(middle == last){
            break;
         }
         do{
            ++first;
         } while(first != middle && !comp(*middle, *first));
      }
   }
   else{
      while(middle != last){
         RandIt p = boost::movelib::upper_bound(first, middle, last[-1], comp);
         last = rotate_gcd(p, middle, last);
         middle = p;
         if(middle == first){
            break;
         }
         --p;
         do{
            --last;
         } while(middle != last && !comp(last[-1], *p));
      }
   }
}

static const std::size_t MergeBufferlessONLogNRotationThreshold = 16u;

template <class RandIt, class Compare>
void merge_bufferless_ONlogN_recursive
   ( RandIt first, RandIt middle, RandIt last
   , typename iter_size<RandIt>::type len1
   , typename iter_size<RandIt>::type len2
   , Compare comp)
{
   typedef typename iter_size<RandIt>::type size_type;

   while(1) {
      //trivial cases
      if (!len2) {
         return;
      }
      else if (!len1) {
         return;
      }
      else if (size_type(len1 | len2) == 1u) {
         if (comp(*middle, *first))
            adl_move_swap(*first, *middle);  
         return;
      }
      else if(size_type(len1+len2) < MergeBufferlessONLogNRotationThreshold){
         merge_bufferless_ON2(first, middle, last, comp);
         return;
      }

      RandIt first_cut = first;
      RandIt second_cut = middle;
      size_type len11 = 0;
      size_type len22 = 0;
      if (len1 > len2) {
         len11 = len1 / 2;
         first_cut +=  len11;
         second_cut = boost::movelib::lower_bound(middle, last, *first_cut, comp);
         len22 = size_type(second_cut - middle);
      }
      else {
         len22 = len2 / 2;
         second_cut += len22;
         first_cut = boost::movelib::upper_bound(first, middle, *second_cut, comp);
         len11 = size_type(first_cut - first);
      }
      RandIt new_middle = rotate_gcd(first_cut, middle, second_cut);

      //Avoid one recursive call doing a manual tail call elimination on the biggest range
      const size_type len_internal = size_type(len11+len22);
      if( len_internal < (len1 + len2 - len_internal) ) {
         merge_bufferless_ONlogN_recursive(first, first_cut,  new_middle, len11, len22, comp);
         first = new_middle;
         middle = second_cut;
         len1 = size_type(len1-len11);
         len2 = size_type(len2-len22);
      }
      else {
         merge_bufferless_ONlogN_recursive
            (new_middle, second_cut, last, size_type(len1 - len11), size_type(len2 - len22), comp);
         middle = first_cut;
         last = new_middle;
         len1 = len11;
         len2 = len22;
      }
   }
}


//Complexity: NlogN
template<class RandIt, class Compare>
void merge_bufferless_ONlogN(RandIt first, RandIt middle, RandIt last, Compare comp)
{
   typedef typename iter_size<RandIt>::type size_type;
   merge_bufferless_ONlogN_recursive
      (first, middle, last, size_type(middle - first), size_type(last - middle), comp);
}

template<class RandIt, class Compare>
void merge_bufferless(RandIt first, RandIt middle, RandIt last, Compare comp)
{
   #define BOOST_ADAPTIVE_MERGE_NLOGN_MERGE
   #ifdef BOOST_ADAPTIVE_MERGE_NLOGN_MERGE
   merge_bufferless_ONlogN(first, middle, last, comp);
   #else
   merge_bufferless_ON2(first, middle, last, comp);
   #endif   //BOOST_ADAPTIVE_MERGE_NLOGN_MERGE
}

// [r_first, r_last) are already in the right part of the destination range.
template <class Compare, class InputIterator, class InputOutIterator, class Op>
void op_merge_with_right_placed
   ( InputIterator first, InputIterator last
   , InputOutIterator dest_first, InputOutIterator r_first, InputOutIterator r_last
   , Compare comp, Op op)
{
   BOOST_ASSERT((last - first) == (r_first - dest_first));
   while ( first != last ) {
      if (r_first == r_last) {
         InputOutIterator end = op(forward_t(), first, last, dest_first);
         BOOST_ASSERT(end == r_last);
         boost::ignore_unused(end);
         return;
      }
      else if (comp(*r_first, *first)) {
         op(r_first, dest_first);
         ++r_first;
      }
      else {
         op(first, dest_first);
         ++first;
      }
      ++dest_first;
   }
   // Remaining [r_first, r_last) already in the correct place
}

template <class Compare, class InputIterator, class InputOutIterator>
void swap_merge_with_right_placed
   ( InputIterator first, InputIterator last
   , InputOutIterator dest_first, InputOutIterator r_first, InputOutIterator r_last
   , Compare comp)
{
   op_merge_with_right_placed(first, last, dest_first, r_first, r_last, comp, swap_op());
}

// [first, last) are already in the right part of the destination range.
template <class Compare, class Op, class BidirIterator, class BidirOutIterator>
void op_merge_with_left_placed
   ( BidirOutIterator const first, BidirOutIterator last, BidirOutIterator dest_last
   , BidirIterator const r_first, BidirIterator r_last
   , Compare comp, Op op)
{
   BOOST_ASSERT((dest_last - last) == (r_last - r_first));
   while( r_first != r_last ) {
      if(first == last) {
         BidirOutIterator res = op(backward_t(), r_first, r_last, dest_last);
         BOOST_ASSERT(last == res);
         boost::ignore_unused(res);
         return;
      }
      --r_last;
      --last;
      if(comp(*r_last, *last)){
         ++r_last;
         --dest_last;
         op(last, dest_last);
      }
      else{
         ++last;
         --dest_last;
         op(r_last, dest_last);
      }
   }
   // Remaining [first, last) already in the correct place
}

// @endcond

// [first, last) are already in the right part of the destination range.
template <class Compare, class BidirIterator, class BidirOutIterator>
void merge_with_left_placed
   ( BidirOutIterator const first, BidirOutIterator last, BidirOutIterator dest_last
   , BidirIterator const r_first, BidirIterator r_last
   , Compare comp)
{
   op_merge_with_left_placed(first, last, dest_last, r_first, r_last, comp, move_op());
}

// [r_first, r_last) are already in the right part of the destination range.
template <class Compare, class InputIterator, class InputOutIterator>
void merge_with_right_placed
   ( InputIterator first, InputIterator last
   , InputOutIterator dest_first, InputOutIterator r_first, InputOutIterator r_last
   , Compare comp)
{
   op_merge_with_right_placed(first, last, dest_first, r_first, r_last, comp, move_op());
}

// [r_first, r_last) are already in the right part of the destination range.
// [dest_first, r_first) is uninitialized memory
template <class Compare, class InputIterator, class InputOutIterator>
void uninitialized_merge_with_right_placed
   ( InputIterator first, InputIterator last
   , InputOutIterator dest_first, InputOutIterator r_first, InputOutIterator r_last
   , Compare comp)
{
   BOOST_ASSERT((last - first) == (r_first - dest_first));
   typedef typename iterator_traits<InputOutIterator>::value_type value_type;
   InputOutIterator const original_r_first = r_first;

   destruct_n<value_type, InputOutIterator> d(dest_first);

   while ( first != last && dest_first != original_r_first ) {
      if (r_first == r_last) {
         for(; dest_first != original_r_first; ++dest_first, ++first){
            ::new((iterator_to_raw_pointer)(dest_first)) value_type(::boost::move(*first));
            d.incr();
         }
         d.release();
         InputOutIterator end = ::boost::move(first, last, original_r_first);
         BOOST_ASSERT(end == r_last);
         boost::ignore_unused(end);
         return;
      }
      else if (comp(*r_first, *first)) {
         ::new((iterator_to_raw_pointer)(dest_first)) value_type(::boost::move(*r_first));
         d.incr();
         ++r_first;
      }
      else {
         ::new((iterator_to_raw_pointer)(dest_first)) value_type(::boost::move(*first));
         d.incr();
         ++first;
      }
      ++dest_first;
   }
   d.release();
   merge_with_right_placed(first, last, original_r_first, r_first, r_last, comp);
}

/// This is a helper function for the merge routines.
template<typename BidirectionalIterator1, typename BidirectionalIterator2>
   BidirectionalIterator1
   rotate_adaptive(BidirectionalIterator1 first,
      BidirectionalIterator1 middle,
      BidirectionalIterator1 last,
      typename iter_size<BidirectionalIterator1>::type len1,
      typename iter_size<BidirectionalIterator1>::type len2,
      BidirectionalIterator2 buffer,
      typename iter_size<BidirectionalIterator1>::type buffer_size)
{
   if (len1 > len2 && len2 <= buffer_size)
   {
      if(len2) //Protect against self-move ranges
      {
         BidirectionalIterator2 buffer_end = boost::move(middle, last, buffer);
         boost::move_backward(first, middle, last);
         return boost::move(buffer, buffer_end, first);
      }
      else
         return first;
   }
   else if (len1 <= buffer_size)
   {
      if(len1) //Protect against self-move ranges
      {
         BidirectionalIterator2 buffer_end = boost::move(first, middle, buffer);
         BidirectionalIterator1 ret = boost::move(middle, last, first);
         boost::move(buffer, buffer_end, ret);
         return ret;
      }
      else
         return last;
   }
   else
      return rotate_gcd(first, middle, last);
}

template<typename BidirectionalIterator,
   typename Pointer, typename Compare>
   void merge_adaptive_ONlogN_recursive
   (BidirectionalIterator first,
      BidirectionalIterator middle,
      BidirectionalIterator last,
      typename  iter_size<BidirectionalIterator>::type len1,
      typename  iter_size<BidirectionalIterator>::type len2,
      Pointer buffer,
      typename  iter_size<BidirectionalIterator>::type buffer_size,
      Compare comp)
{
   typedef typename  iter_size<BidirectionalIterator>::type size_type;
   //trivial cases
   if (!len2 || !len1) {
      // no-op
   }
   else if (len1 <= buffer_size || len2 <= buffer_size) {
      range_xbuf<Pointer, size_type, move_op> rxbuf(buffer, buffer + buffer_size);
      buffered_merge(first, middle, last, comp, rxbuf);
   }
   else if (size_type(len1 + len2) == 2u) {
      if (comp(*middle, *first))
         adl_move_swap(*first, *middle);
   }
   else if (size_type(len1 + len2) < MergeBufferlessONLogNRotationThreshold) {
      merge_bufferless_ON2(first, middle, last, comp);
   }
   else {
      BidirectionalIterator first_cut = first;
      BidirectionalIterator second_cut = middle;
      size_type len11 = 0;
      size_type len22 = 0;
      if (len1 > len2)  //(len1 < len2)
      {
         len11 = len1 / 2;
         first_cut += len11;
         second_cut = boost::movelib::lower_bound(middle, last, *first_cut, comp);
         len22 = size_type(second_cut - middle);
      }
      else
      {
         len22 = len2 / 2;
         second_cut += len22;
         first_cut = boost::movelib::upper_bound(first, middle, *second_cut, comp);
         len11 = size_type(first_cut - first);
      }

      BidirectionalIterator new_middle
         = rotate_adaptive(first_cut, middle, second_cut,
            size_type(len1 - len11), len22, buffer,
            buffer_size);
      merge_adaptive_ONlogN_recursive(first, first_cut, new_middle, len11,
         len22, buffer, buffer_size, comp);
      merge_adaptive_ONlogN_recursive(new_middle, second_cut, last,
         size_type(len1 - len11), size_type(len2 - len22), buffer, buffer_size, comp);
   }
}


template<typename BidirectionalIterator, typename Compare, typename RandRawIt>
void merge_adaptive_ONlogN(BidirectionalIterator first,
		                     BidirectionalIterator middle,
		                     BidirectionalIterator last,
		                     Compare comp,
                           RandRawIt uninitialized,
                           typename  iter_size<BidirectionalIterator>::type uninitialized_len)
{
   typedef typename iterator_traits<BidirectionalIterator>::value_type  value_type;
   typedef typename  iter_size<BidirectionalIterator>::type   size_type;

   if (first == middle || middle == last)
      return;

   if(uninitialized_len)
   {
      const size_type len1 = size_type(middle - first);
      const size_type len2 = size_type(last - middle);

      ::boost::movelib::adaptive_xbuf<value_type, RandRawIt> xbuf(uninitialized, uninitialized_len);
      xbuf.initialize_until(uninitialized_len, *first);
	   merge_adaptive_ONlogN_recursive(first, middle, last, len1, len2, xbuf.begin(), uninitialized_len, comp);
   }
   else
   {
      merge_bufferless(first, middle, last, comp);
   }
}

}  //namespace movelib {
}  //namespace boost {

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

#endif   //#define BOOST_MOVE_MERGE_HPP

/* merge.hpp
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
*/