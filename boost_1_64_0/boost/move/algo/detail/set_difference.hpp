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
bXm00ZsRl644wN0540He+TxBPRpdXGigHQ0pmk4f1Pl/0Txv8Nn53uBO+vsubcdl9PkJ+vy7+f+/aybGE0mJO1ee9KnkU03BW9iNcUVWmCJN889PbcX5W+3Wd7A4K3IovGyvzCI5THLQoUoSOCCTQbDK59W2OcTstWF9hs8TCSpOknfCHvH/5LiRacU96ZXmxbXlcJBzT0RHUEWl80il3l8pTXdDjCm8fFDFENwtuvGoH4+8YnfMzLnNWjGIr0hLXsejsRtylj+32BtUte2ipSjKGUh+YCYZq+rnMfYAighVZRr1NG6fxyiGG+mOVPciwxCmcRQnCA3BZkA2/F9FvIdhd6Thls4P6fHTC6rqGu/KvAa6AlD7OgwfYpyJPWAF8jPuiGYYzdMOzYX2f0c4ytsd2LyAjj8CWMjPme2nQOGPMWz0MkfpHFo6L4R1UXwY65gDdJ2O9JWMsm4ts2TGWXsAFlUjJPAE46kWOI4xfA++TIbEi2Mf0wX74+nMb6is1tct8gYHEL73099T6O8C+nsWf9a/eP+fsc8d+8dXmD8xFMYXlxeGycjqugZN52A6FWDTqXQ2mGqjE8JnKFsd1qSys418OQA1Qcwr1imGEKbzRTXEeD+b7VN6OSShjvUVfAZ/zQQqpPvDCjw563tJn3jOOjDsQ/fweS0mg16VLc7DlUM8CO8miYJ6wTbRJKW2aGR9ED8mvlj+Fqod41qoIlZGMKpwg8rti75v/QWPSht/c1Azi3KNbdmpcjAW4i5qooDJdeMkRlkMZ5XWW8amcHVLpTp9HUFtPQwYDjUB+7GAfcMRG/vt2S8be6P4sMIwSsxctlL7z+f6Vf4fbwktkixeJBdbsJXjcfLCyhCYmVspoMrZr6ox15jEp4NxE1tqSsAl6WgFZTSzpeY1Eo+mPcavqWy1jrJ2lnGeMNwD968cbKxkRT/SZIteg4dgEqpZ3NWg3Sv5It79TrkFPiFasWskXgaxJYZjqYFfYid39nV296vluns4DZ5oPO3ynAY5EC1bTGO1qDQ5bPZ41x3a0gWm6zjVqulUi95qLbmGkl4HuPb16Vx7AVQCDV1mvd8fyfaUwlt3ECQmDx3UhgzstRWgTjNG5qebDg4yrpG1kPDDruK9c9RRWAtjPhwTsegabahHmPYWT9LNgGKhGYNv46iJIXdymunONNLvZOvuyu8C0eesB828Imr74XwOBKyHzFOEwOj2+++US8pB/WA/Hcv5/zfX63xPdewioMR2MDzbXJFPGk0/W95nRQbg6BTbgNGp5rRmrlgLAvdFBzMQpDZE1/gOgzcw2MA5DItiY7eRtXQvX0KKsmg5DuCrTsi59cC5zMsnuw7fjl6Q8PAT+qJ4nK2I/XqMbNYHCZjqgcwwSwXLpmmFhhYhs73u2NmQoUS6cn3B4g60gCDQgz3slmjvF/K2qAgs3IXdWva4O+gYqGia04bVYx5Wj20tsNelqoVVU3IGTgPWze/DQ77iaLY/yDImiCtxzznh5+osxmXauefsGJVvC9uz1aNiVO8g7itaQRwbSz3Z7Kznyy4FqWKk7vIoPAQj3YWXqJTQjJ++pICrkf2mkvgvfTOq5ptRddUFKMpYATncV+AuziTO/o06CLZMcfeDWZUt6h0rEHbBQEGL7WwAiBnC99nWF5dOb3E2h267nG/lPtVjufmcI8/Qpe1q4qGkAEVPQiKfHA23ctvusxtJJaX/NTL8z17Uw+dh/wjDjuTDBU3ubzVs9Md98qihxLflxNyV1ngQAS7w6G26w9EcQlw7KqgcdVng51wYTrv1H6GB/8k/Tv6/Z9lej8kT0yY+n8sn+kZP8JW0k0SKuHW3ERIgFro0a7A=
*/