#ifndef BOOST_METAPARSE_V1_FOLDR_HPP
#define BOOST_METAPARSE_V1_FOLDR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr : foldr_start_with_parser<P, return_<State>, BackwardOp> {};
    }
  }
}

#endif


/* foldr.hpp
63oZopNQUDMV/P1ARwHHy47EjJzP4D8lkfjNScV370zO4W9tI8dvD6/Lp/lLJO6KAls+vpSX/Y2cKUaQQgyLoQ7XC4Y8uG3bkvVYAlkoa6dXDe9rA029CuBCcehkCyo53JQRP5VKnqzI87/yB1BLAwQKAAAACAAtZ0pSJRIZJOoBAAA8BAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyNDZVVAUAAbZIJGCtVNFq4zAQfBf4H5aGECjIisPRQhCmoZRLabmEJO27Kq9jUVsyltImf3+SXSeBFnIPh7Gx1ruzs7ODuUPrpLCYEq50blIygA9sVH6Al9UzfCpXQGGs06JCQJ0pvQWloTY7nYFVW034Ox4+TZPZlMw3m2X7gN8Pm+6lbsz+QDg7JXHW9SED32qNje9GrcqQ8Abr8uATMuFEB8aSOIHJeAyLJ3JvtEPt6DPqrSumcBMiGqVTRk9BlsYiITQ3hvoWHUQHlVzGuv0RSxpT9mBJIP5FsGV+X6qA0DGX7cGn2HaelBTO1b6gPwIP+qXkKOloMALhgqBg8lZgaBVW2joUbXDERr6OdYXApakqobOUUNpqCqHFlLHhfLHePC6nwzDjcrHa9B/CYuMGK+MwLsR+H1uMk8mvm1Pm4C6Z
*/