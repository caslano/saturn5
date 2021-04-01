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
h/opK78F/maFvrwydCREgXrC1I9OyItvn0NGiIA5NMN/7zMdhZhhs/gtZogPK6LMvmTqJd/D49DW4/kayhBo+J9XUg57kVL3du/3qkPMR8frpe6HjYsR3BDqEKz3NnVQ8X2np29h0k0DT8tZzLURH3CaRxShavvgQV8yGwHY7/zpvCgyvjsXwwceMXSTHobqYou52Mwdx5vARUxSUPAGglEvelhsd3rzHTLJsZ7wEKWeHN+a9LIa9nv9GkaQX/n/F+yIGPMbMAMQWzxxDzgTn2JC4LIZx+K5Ir9q6nwZawK0S5EPRpGBSuUNR5KZFClFZZxAbjlYnFBpKDFmn9CmqgyqF65JQBV0OuZUbbPgA3albsagRcVfrJcHkLF4TCOMgv6SuopVT7UH3aVqgW2YCmolCyC3scahCAZ6wqLGrofZrbbI//2Gdx2WkeFg2qmoM7fYpy//S2HVPt/DP4JG4S04Gvovwc2GIypbbprQ7BGKQyPsjWJyHZyfqkTtpnjlTLjLX7DG5ZqiYP8jNhEZj0SeXgPIwdb34YWQzUraQnRB0WhSNkdpb7ZRHA==
*/