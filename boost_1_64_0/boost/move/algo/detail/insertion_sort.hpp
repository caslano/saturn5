//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_INSERT_SORT_HPP
#define BOOST_MOVE_DETAIL_INSERT_SORT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/utility_core.hpp>
#include <boost/move/algo/move.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/detail/placement_new.hpp>
#include <boost/move/detail/destruct_n.hpp>
#include <boost/move/algo/detail/basic_op.hpp>
#include <boost/move/detail/placement_new.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>

namespace boost {  namespace movelib{

// @cond

template <class Compare, class ForwardIterator, class BirdirectionalIterator, class Op>
void insertion_sort_op(ForwardIterator first1, ForwardIterator last1, BirdirectionalIterator first2, Compare comp, Op op)
{
   if (first1 != last1){
      BirdirectionalIterator last2 = first2;
      op(first1, last2);
      for (++last2; ++first1 != last1; ++last2){
         BirdirectionalIterator j2 = last2;
         BirdirectionalIterator i2 = j2;
         if (comp(*first1, *--i2)){
            op(i2, j2);
            for (--j2; i2 != first2 && comp(*first1, *--i2); --j2) {
               op(i2, j2);
            }
         }
         op(first1, j2);
      }
   }
}

template <class Compare, class ForwardIterator, class BirdirectionalIterator>
void insertion_sort_swap(ForwardIterator first1, ForwardIterator last1, BirdirectionalIterator first2, Compare comp)
{
   insertion_sort_op(first1, last1, first2, comp, swap_op());
}


template <class Compare, class ForwardIterator, class BirdirectionalIterator>
void insertion_sort_copy(ForwardIterator first1, ForwardIterator last1, BirdirectionalIterator first2, Compare comp)
{
   insertion_sort_op(first1, last1, first2, comp, move_op());
}

// @endcond

template <class Compare, class BirdirectionalIterator>
void insertion_sort(BirdirectionalIterator first, BirdirectionalIterator last, Compare comp)
{
   typedef typename boost::movelib::iterator_traits<BirdirectionalIterator>::value_type value_type;
   if (first != last){
      BirdirectionalIterator i = first;
      for (++i; i != last; ++i){
         BirdirectionalIterator j = i;
         if (comp(*i,  *--j)) {
            value_type tmp(::boost::move(*i));
            *i = ::boost::move(*j);
            for (BirdirectionalIterator k = j; k != first && comp(tmp,  *--k); --j) {
               *j = ::boost::move(*k);
            }
            *j = ::boost::move(tmp);
         }
      }
   }
}

template <class Compare, class BirdirectionalIterator, class BirdirectionalRawIterator>
void insertion_sort_uninitialized_copy
   (BirdirectionalIterator first1, BirdirectionalIterator const last1
   , BirdirectionalRawIterator const first2
   , Compare comp)
{
   typedef typename iterator_traits<BirdirectionalIterator>::value_type value_type;
   if (first1 != last1){
      BirdirectionalRawIterator last2 = first2;
      ::new((iterator_to_raw_pointer)(last2), boost_move_new_t()) value_type(::boost::move(*first1));
      destruct_n<value_type, BirdirectionalRawIterator> d(first2);
      d.incr();
      for (++last2; ++first1 != last1; ++last2){
         BirdirectionalRawIterator j2 = last2;
         BirdirectionalRawIterator k2 = j2;
         if (comp(*first1, *--k2)){
            ::new((iterator_to_raw_pointer)(j2), boost_move_new_t()) value_type(::boost::move(*k2));
            d.incr();
            for (--j2; k2 != first2 && comp(*first1, *--k2); --j2)
               *j2 = ::boost::move(*k2);
            *j2 = ::boost::move(*first1);
         }
         else{
            ::new((iterator_to_raw_pointer)(j2), boost_move_new_t()) value_type(::boost::move(*first1));
            d.incr();
         }
      }
      d.release();
   }
}

}} //namespace boost {  namespace movelib{

#endif //#ifndef BOOST_MOVE_DETAIL_INSERT_SORT_HPP

/* insertion_sort.hpp
Jusb2Gh9Cxut7/0jm6pvHt7HhSIcyfcpVUkS/KokeH+z8FmAN1PRZ2hzkV0APzIO/tMjFXwL9h892F7FU9xNC9TDk+1SWTsQ9XkbF1CgvSsa6tEe4mp0awyfU7fG4/NEwNs/O6IpfA7E+zj82D2bw89XBwCvx3vgiJbw8/Ae3d+BjfZ3d0J/FxI8zf/hqr+N428MLSW7eHd9gxNC7HQrZxtbS78ke+CZ9lq1MzxRUsPnxOz+KuddhLOad+DTwr+3/mDkqE78k6z4+PGGUNjnfWg6CQmf7uQb0sle0smqiR4xTEXsxGCKXxRb2kbp9+/WG1H5YQkVvB2QCtpwBVkpxVRBlh/vhjIkYjTap/d060SolmEJtdysanmWj9MQeU1LuLaQmPWPepSFhtHu/BTCvO319SbD0HUmf4nRk54jJNQVC8a+/z0sA+A43M6Ri/8goSOBgHYggQjv6GqeDYVYMJthiUp0hlhNybL60W5ABR2R4uHhk7laVvxMSOHWuOWPovUmCPmV9kHN9Lfzg/V+7buJ+8/Kam7/nQV4s/8W5ba0//70F73/Hujc2P5bsi1+/10PePv8w5o6L9rQjpf6Tmu0vjsS6nuTdjJZ1DVVX5hySyRJUmO8RLIAnRyfh/d/F3c8B3WDc/uqGeEU1/eGLCRJ0YYNcJQV2U7rbhZTTfD/bWQDdPJS5ScQQZZ8fbg6ijeADRvcot3lCBf99gGuDXJVjx1+G8A7yvFuB3lT0h0IpR7V1sQjv2BgWp0nYX9G+vIU95OnBRxCFSrhnb+WLdaPX6eq1xVwm5rxV95rJjOZvZ9GI5dptHQCTIpSUImkVPVzfk97XjajEN66LFmh3tIQ5F3wY1VjSe/wFMHEZRoT1/gFE34+UHo1FOdU5PdC1Rnw6VJcC2wuAvYpu+rp0OvVFxJjVPvofu61wj9hekBxR8bBw58r9G/leNzicWHjoFi1m98g9HBiphp7O/cyhKTrHs6YCKXQGfbinRh9pXKgO9m6G+thQr2qpxKwlaUbfZLaYCMhkkKtck0BjvqSxWFSOzB2fGaNVEbHWcvokyBjnEZGSQYjg0e+tZab4Gpfg0SDmyO/LFoArlAQH3b5zwgFsaVZe453Opr7UrzZm/1ZqqOEocSyWI/3Yj0ah87rPKKi97MxjY8/vuDxac8LEDg/MP2ARjcr5R4Laafmcpb1kukhKedR3w88yhc/qDTu3fUKAeQE5CD5leydXqhJPxz6tbNr/saN+5m6+lP8qM9vdIOnvqEAqa3tKUJFF420f0OPyaDdGLopR9bVJpQpu0jaXV2lb1LUc9FxS0tCuF5Evm9v+3N9gzjCsF9XAGv2EtpNaVjq9o3qDsCUnpb8ytd5d9m3UyknAt5x4Tz7QoGExSeE4FjgTCIXDMbpOuMjZ4F3ZO4m/TNN6qJHWW+6VvbbsrLv9fHKZrL41qcOWcx48ztAFpull59RbxP4/47N0cszBh1I5P+bhb8e9Tv8f05L9HX/wANu/r9/S/z/EOb/OzRHv3YkkTEsX9CtMdYdf6ZpPN76SKZxt1dO68uQzID/gZoOob4MLpQ4/fBa68WxbvV7+3XmJ0eyZc7xXKH1PlWn61yp6uzjVdTz5x8kUM+J0otZusRpqkQ1ToP0Gjf1fDqJet75tYt6DtlB26NoNwKvks5yng9FyjXprP/YRTpDmnR+JE8J5SEhnbff6yadm/Fak87cLzWhS6uajM49/YGbdB7SKOnE5cKQzu4JpPP1vQ7pnClouEyjYbJH0PABfYVuzr7ziySCKC5nt0snwTfk2QhieAM2Pq5+Q6iZwQWIuO/KIE2fdxgfGhVviTSgNoy+bcivQBcvfK0Rujg=
*/