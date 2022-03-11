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
#ifndef BOOST_MOVE_ALGO_BASIC_OP
#define BOOST_MOVE_ALGO_BASIC_OP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/utility_core.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/detail/iterator_traits.hpp>

namespace boost {
namespace movelib {

struct forward_t{};
struct backward_t{};
struct three_way_t{};
struct three_way_forward_t{};
struct four_way_t{};

struct move_op
{
   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE void operator()(SourceIt source, DestinationIt dest)
   {  *dest = ::boost::move(*source);  }

   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE DestinationIt operator()(forward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return ::boost::move(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE DestinationIt operator()(backward_t, SourceIt first, SourceIt last, DestinationIt dest_last)
   {  return ::boost::move_backward(first, last, dest_last);  }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   BOOST_MOVE_FORCEINLINE void operator()(three_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
   }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   DestinationIt2 operator()(three_way_forward_t, SourceIt srcit, SourceIt srcitend, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      //Destination2 range can overlap SourceIt range so avoid boost::move
      while(srcit != srcitend){
         this->operator()(three_way_t(), srcit++, dest1it++, dest2it++);
      }
      return dest2it;
   }

   template <class SourceIt, class DestinationIt1, class DestinationIt2, class DestinationIt3>
   BOOST_MOVE_FORCEINLINE void operator()(four_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it, DestinationIt3 dest3it)
   {
      *dest3it = boost::move(*dest2it);
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
   }
};

struct swap_op
{
   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE void operator()(SourceIt source, DestinationIt dest)
   {  boost::adl_move_swap(*dest, *source);  }

   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE DestinationIt operator()(forward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return boost::adl_move_swap_ranges(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE DestinationIt operator()(backward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return boost::adl_move_swap_ranges_backward(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   BOOST_MOVE_FORCEINLINE void operator()(three_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      typename ::boost::movelib::iterator_traits<SourceIt>::value_type tmp(boost::move(*dest2it));
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
      *srcit = boost::move(tmp);
   }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   DestinationIt2 operator()(three_way_forward_t, SourceIt srcit, SourceIt srcitend, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      while(srcit != srcitend){
         this->operator()(three_way_t(), srcit++, dest1it++, dest2it++);
      }
      return dest2it;
   }

   template <class SourceIt, class DestinationIt1, class DestinationIt2, class DestinationIt3>
   BOOST_MOVE_FORCEINLINE void operator()(four_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it, DestinationIt3 dest3it)
   {
      typename ::boost::movelib::iterator_traits<SourceIt>::value_type tmp(boost::move(*dest3it));
      *dest3it = boost::move(*dest2it);
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
      *srcit = boost::move(tmp);
   }
};


}} //namespace boost::movelib

#endif   //BOOST_MOVE_ALGO_BASIC_OP

/* basic_op.hpp
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
*/