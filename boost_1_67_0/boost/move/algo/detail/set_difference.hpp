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



}  //namespace movelib {
}  //namespace boost {

#endif   //#define BOOST_MOVE_SET_DIFFERENCE_HPP

/* set_difference.hpp
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
*/