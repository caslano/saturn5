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
+fO2MS39NYL8uL0htPezIUGG5/OBtLdZu1XdwdgutjcnHq02k32xSziVIaJ55qhTVGc1uwVw1rnlLFs6hi2LlJG9IpctvPF+6PMvpB44GJ60Xmzk55HAb0JvWoYQZc1LigRXc/Wh0GUUxbvzxDd0c5e0vANSbvIknaTeFs2hyjiuc8B6MdYUAd5i2r7SoC/rVw7hQspCNfbC1LQGZGKc6z3Hc9tiTTCAK/DhcVxJkkKBDAA378v/zyjc2f4vMLgqwmJpVCvXTTAOKgVzUV5WdSszn81T6onRGJVfKgz+k70rAY+qusKZySQZYCADDBD2CGHRoFLACiIV0ChCIwk1ilVRK+JzAEWdCAhhMSDEGJfWhbq07tVWLW0VwaJFVERFBYqIihoQ9cWJGnWqoU1Iz3/Ovfe9mcmGra1dwhcy896527nLOfesX41y31B4C/1I2D++ZAX44q+qqiAc4KO3wLZMZXKZKj1GynYTJxwsVk+uFxj3fCNy44r/r8eH6sfrwVlIj8aj4L6FCuwefdEjyR0bSomPLhvkSAgHFWrdxFeoOMqF3/1J+OWdVMOf4dvP2AjQJQt4wKtqZPxWwlVeX+2gHHPclFDrvag1YbYyumkEc05FZ8LyRiZN2IxWTNgTXRufsMNcE1bmlXd41DYXefpjudtw9gUPBnOt+3H4nxE4XxHRRbPN5mythSoDWOKeDrTu0IhQYxrU20y555vMb4jlP8Md/amEPK2FWGN6D33AqUCp4phxQaoKB5GOgJfVEaqBxWzMKk7QL338chUEJg/hJQ6KXP0yNXN5haxKnh9qq3SAmWtkd2XwXgzupyMaMr7ZVg1OZj4vX5OT+Y5BWvB4Ga+L4483dz+Y918Z4K/mUpKPGQaxZTNtyAaUZXJNdBjsa6thy8bN8zjvFD2FO/YOK+H6e/lIbCWS/4EfIw9uP4zpL+YnxpIxUEKs3iPtxzPdctDejKNwunWbIGjBQIUgdoVF+sKAs2+DBfZzIlzkAwMtMcvHgw931ZkyssOHCuaxRXXF/aTiqpe0KIlo9bkpkX7wLBbj4TrZ8cS9nduwnWYWsU2WAhpPiYnLSYmcqYgx7pjCLtkL+8ftbG90FhOd8DgzsSCQd7fVEwuQk7nDVcfwM2VV3yN8rKCive7xnAFK/MqJfWJlXoXI/IARv/bhR20ZSaMpq1+AV+ENx3xrAtiW51/sP45uWf/w7MjG7T8CzP9Azs3DJXiRn5e0j183Oa/wurldkHV8jl43Yawbvw6UbNzZJoX08ugdzkkonC6Fqzp61Laf0c2lNUyPZNH/kcjUpSW1OB0yl8EArAoZD1WkKxwHU7L1cUA1YLrGh3AMUGtDpLX2urVV/aW1e1FLOf1njlAoPIgoduypU9P0CB+VUPhMKRy9KHpqYrHK/k6xMQnFclSxYdHe4ePxTjaHfp2mXndu7RI7fOS/a4k1zk/debjml42InfjVkcFiySDjA9+6VF8Qb6FjssCeLeeF45w13YyUqXmZ0a6m9tCrgfY9JdAjkSwLg6PpkuOArwzZMODQJR46Ua6H7CQ281m2jaA11ECqiEus5zAzs62rBfXXHMKotz3oFJ8Ll4if6Tf3imwEPyVDDghGfAYj2Ae6LyukLweyTV79Qu3V8G6edhumcizCiGVpEQKHoA6WgCknOqxk6bViFBIT5d/FG7NSDirEW+P3oady0X+csqQiBzlASzVEAH0pSkZpKw1LRb6ogezVKZjl9V4d9tlxSkRPWuBv4Flsj06Pz8p0nBErYguckKG3mxDfOp42Zqdx4IR9vNbWfF5/EP6eaH/JK43IJ56iypPC6t1yrOuG7inuItmulu5NgQDkJS/LH5o=
*/