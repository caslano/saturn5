//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_SET_DIFFERENCE_HPP
#define BOOST_MOVE_SET_DIFFERENCE_HPP

#include <boost/move/algo/move.hpp>
#include <boost/move/iterator.hpp>
#include <boost/move/utility_core.hpp>

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

namespace boost {
namespace move_detail{

template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt result)
{
   while (first != last) {
      *result++ = *first;
      ++result;
      ++first;
   }
   return result;
}

}  //namespace move_detail{

namespace movelib {

//Moves the elements from the sorted range [first1, last1) which are not found in the sorted
//range [first2, last2) to the range beginning at result.
//The resulting range is also sorted. Equivalent elements are treated individually,
//that is, if some element is found m times in [first1, last1) and n times in [first2, last2),
//it will be moved to result exactly max(m-n, 0) times.
//The resulting range cannot overlap with either of the input ranges.
template<class InputIt1, class InputIt2,
         class OutputIt, class Compare>
OutputIt set_difference
   (InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt result, Compare comp)
{
   while (first1 != last1) {
      if (first2 == last2)
         return boost::move_detail::copy(first1, last1, result);

      if (comp(*first1, *first2)) {
         *result = *first1;
         ++result;
         ++first1;
      }
      else {
         if (!comp(*first2, *first1)) {
            ++first1;
         }
         ++first2;
      }
   }
   return result;
}

//Moves the elements from the sorted range [first1, last1) which are not found in the sorted
//range [first2, last2) to the range beginning at first1 (in place operation in range1).
//The resulting range is also sorted. Equivalent elements are treated individually,
//that is, if some element is found m times in [first1, last1) and n times in [first2, last2),
//it will be moved to result exactly max(m-n, 0) times.
template<class InputOutputIt1, class InputIt2, class Compare>
InputOutputIt1 inplace_set_difference
   (InputOutputIt1 first1, InputOutputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
{
   while (first1 != last1) {
      //Skip copying from range 1 if no element has to be skipped
      if (first2 == last2){
         return last1;
      }
      else if (comp(*first1, *first2)){
         ++first1;
      }
      else{
         if (!comp(*first2, *first1)) {
            InputOutputIt1 result = first1;
            //An element from range 1 must be skipped, no longer an inplace operation
            return boost::movelib::set_difference
               ( boost::make_move_iterator(++first1)
               , boost::make_move_iterator(last1)
               , ++first2, last2, result, comp);
         }
         ++first2;
      }
   }
   return first1;
}

//Moves the elements from the sorted range [first1, last1) which are not found in the sorted
//range [first2, last2) to the range beginning at first1.
//The resulting range is also sorted. Equivalent elements from range 1 are moved past to end
//of the result,
//that is, if some element is found m times in [first1, last1) and n times in [first2, last2),
//it will be moved to result exactly max(m-n, 0) times.
//The resulting range cannot overlap with either of the input ranges.
template<class ForwardIt1, class InputIt2,
         class OutputIt, class Compare>
OutputIt set_unique_difference
   (ForwardIt1 first1, ForwardIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt result, Compare comp)
{
   while (first1 != last1) {
      if (first2 == last2){
         //unique_copy-like sequence with forward iterators but don't write i
         //to result before comparing as moving *i could alter the value in i.
         ForwardIt1 i = first1;
         while (++first1 != last1) {
            if (comp(*i, *first1)) {
               *result = *i;
               ++result;
               i = first1;
            }
         }
         *result = *i;
         ++result;
         break;
      }

      if (comp(*first1, *first2)) {
         //Skip equivalent elements in range1 but don't write i
         //to result before comparing as moving *i could alter the value in i.
         ForwardIt1 i = first1;
         while (++first1 != last1) {
            if (comp(*i, *first1)) {
               break;
            }
         }
         *result = *i;
         ++result;
      }
      else {
         if (comp(*first2, *first1)) {
            ++first2;
         }
         else{
            ++first1;
         }
      }
   }
   return result;
}

//Moves the elements from the sorted range [first1, last1) which are not found in the sorted
//range [first2, last2) to the range beginning at first1 (in place operation in range1).
//The resulting range is also sorted. Equivalent elements are treated individually,
//that is, if some element is found m times in [first1, last1) and n times in [first2, last2),
//it will be moved to result exactly max(m-n, 0) times.
template<class ForwardOutputIt1, class ForwardIt2, class Compare>
ForwardOutputIt1 inplace_set_unique_difference
   (ForwardOutputIt1 first1, ForwardOutputIt1 last1, ForwardIt2 first2, ForwardIt2 last2, Compare comp )
{
   while (first1 != last1) {
      //Skip copying from range 1 if no element has to be skipped
      if (first2 == last2){
         //unique-like algorithm for the remaining range 1
         ForwardOutputIt1 result = first1;
         while (++first1 != last1) {
            if (comp(*result, *first1) && ++result != first1) {
               *result = boost::move(*first1);
            }
         }
         return ++result;
      }
      else if (comp(*first2, *first1)) {
         ++first2;
      }
      else if (comp(*first1, *first2)){
         //skip any adjacent equivalent element in range 1
         ForwardOutputIt1 result = first1;
         if (++first1 != last1 && !comp(*result, *first1)) {
            //Some elements from range 1 must be skipped, no longer an inplace operation
            while (++first1 != last1 && !comp(*result, *first1)){}
            return boost::movelib::set_unique_difference
               ( boost::make_move_iterator(first1)
               , boost::make_move_iterator(last1)
               , first2, last2, ++result, comp);
         }
      }
      else{
         ForwardOutputIt1 result = first1;
         //Some elements from range 1 must be skipped, no longer an inplace operation
         while (++first1 != last1 && !comp(*result, *first1)){}
         //An element from range 1 must be skipped, no longer an inplace operation
         return boost::movelib::set_unique_difference
            ( boost::make_move_iterator(first1)
            , boost::make_move_iterator(last1)
            , first2, last2, result, comp);
      }
   }
   return first1;
}

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

}  //namespace movelib {
}  //namespace boost {

#endif   //#define BOOST_MOVE_SET_DIFFERENCE_HPP

/* set_difference.hpp
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
*/