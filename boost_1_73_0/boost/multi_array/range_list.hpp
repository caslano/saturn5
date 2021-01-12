// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_RANGE_LIST_HPP
#define BOOST_MULTI_ARRAY_RANGE_LIST_HPP
//
// range_list.hpp - helper to build boost::arrays for *_set types
//

#include "boost/array.hpp"

namespace boost {
namespace detail {
namespace multi_array {

/////////////////////////////////////////////////////////////////////////
// choose range list begins
//

struct choose_range_list_n {
  template <typename T, std::size_t NumRanges>
  struct bind {
    typedef boost::array<T,NumRanges> type;
  };
};

struct choose_range_list_zero {
  template <typename T, std::size_t NumRanges>
  struct bind {
    typedef boost::array<T,1> type;
  };
};


template <std::size_t NumRanges>
struct range_list_gen_helper {
  typedef choose_range_list_n choice;
};

template <>
struct range_list_gen_helper<0> {
  typedef choose_range_list_zero choice;
};

template <typename T, std::size_t NumRanges>
struct range_list_generator {
private:
  typedef typename range_list_gen_helper<NumRanges>::choice Choice;
public:
  typedef typename Choice::template bind<T,NumRanges>::type type;
};

//
// choose range list ends
/////////////////////////////////////////////////////////////////////////

} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* range_list.hpp
mp+J1cx6t1TQ4omFA1btL6VfNoqulPj+FN/jVUyp+6V8t33UpvXd0Sv5u5iQEQtfyudvMU5eOeXz4fw+hV6Xl1nPr+PnlNMMn8u7G9MUGpIzGVl6OaK8lzpLkNXez0zfxv28gZ9zv8nY1SeYviANmABSqN5BUdpun9lRqZe5yXcs+oMKPHU2JGsdbVLe7yDbkuShO/PW2MzSV+sLMYwKcAd81vNnme8G0THy+bf8Pls3ch2I
*/