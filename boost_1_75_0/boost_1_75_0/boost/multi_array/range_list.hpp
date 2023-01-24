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
/4KPbT0bD0qIFl9Hmny0MAi7jo/WPRazj1miqN16i6wszRXf1Y6+B+bDhXQlEFltk7mWK1mwPJbmeHBNmhgeGc02+oerLQ3syXBlhKwDxvReSDEAAiz90zI17GXGczslf8zFMbwl2WlHMzdUATyXNmeoWj2nostPuWCw7wR5q36CentgXY6e9mxYmvqLVd+5I+2U0oqT2RQnW4lmvTqZL+E7hqVp7lLEbHCYHDKxGvX08tTH+1Bi+JugQS0BhPOaX08jxWFHSPosmGckr6wzC+JHk//bzWKXw8q7HFaxywHzzKjDNN0Mgx/WnTIO17GJCvka2tw4+aVBDwWoJh2HBvt1a98dmo0AyUrS5xSI6lWyZbJU7LaYgKmnhd1o4R36eDauPV2AFS5RyJB97FBPSRIWTBvVSR2F5kAtJzlTOQ1TTwdKz7eDuOVbBp9yDv2IkXJwP1z5gnyeqJLGlZScRyua64p2LEl3Up2rNPRRXpbu5DJXmND/o1f1Ldo0iaqouhAZwAjRXszefz27JOt0qrnvO2eTNgBS53uCdlfZFl8LzwINfVB8nWgclbors6xXEfAqS3WOj/IG3qZjwfCRWcGFeE7+mVpOnvAmoPz2nJ2GvzaNbhTfY6hDZ8/aDDdWAZDlRrUisR0fW19REg6tVJfcPqGxPQusVaESiVzOP7OOsG49DX9Zk2qnWqSPzf6UpDUojl1fhLZEM5ST
*/