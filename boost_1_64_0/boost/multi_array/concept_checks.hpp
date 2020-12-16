// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_CONCEPT_CHECKS_HPP
#define BOOST_MULTI_ARRAY_CONCEPT_CHECKS_HPP

//
// concept-checks.hpp - Checks out Const MultiArray and MultiArray
// concepts
//

#include "boost/concept_check.hpp"
#include "boost/iterator/iterator_concepts.hpp"

namespace boost {
namespace multi_array_concepts {

namespace detail {
  //
  // idgen_helper -
  //   This is a helper for generating index_gen instantiations with
  //   the right type in order to test the call to
  //   operator[](index_gen).  Since one would normally write:
  //      A[ indices[range1][range2] ]; // or
  //      B[ indices[index1][index2][range1] ];
  //   idgen helper allows us to generate the "indices" type by
  //   creating it through recursive calls.
  template <std::size_t N>
  struct idgen_helper {

    template <typename Array, typename IdxGen, typename Call_Type>
    static void call(Array& a, const IdxGen& idgen, Call_Type c) {
      idgen_helper<N-1>::call(a,idgen[c],c);
    }
  };

  template <>
  struct idgen_helper<0> {

    template <typename Array, typename IdxGen, typename Call_Type>
    static void call(Array& a, const IdxGen& idgen, Call_Type) {
      a[ idgen ];
    }
  };

} // namespace detail


  template <typename Array, std::size_t NumDims >
  struct ConstMultiArrayConcept
  {
    void constraints() {
    //    function_requires< CopyConstructibleConcept<Array> >();
    function_requires< boost_concepts::ForwardTraversalConcept<iterator> >();
    function_requires< boost_concepts::ReadableIteratorConcept<iterator> >();
    function_requires< boost_concepts::ForwardTraversalConcept<const_iterator> >();
    function_requires< boost_concepts::ReadableIteratorConcept<const_iterator> >();

      // RG - a( CollectionArchetype) when available...
      a[ id ];
      // Test slicing, keeping only the first dimension, losing the rest
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],id);

      // Test slicing, keeping all dimensions.
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],range);

      st = a.size();
      st = a.num_dimensions();
      st = Array::dimensionality;
      st = a.num_elements();
      stp = a.shape();
      idp = a.strides();
      idp = a.index_bases();
      cit = a.begin();
      cit = a.end();
      crit = a.rbegin();
      crit = a.rend();
      eltp = a.origin();
    }

    typedef typename Array::value_type value_type;
    typedef typename Array::reference reference;
    typedef typename Array::const_reference const_reference;
    typedef typename Array::size_type size_type;
    typedef typename Array::difference_type difference_type;
    typedef typename Array::iterator iterator;
    typedef typename Array::const_iterator const_iterator;
    typedef typename Array::reverse_iterator reverse_iterator;
    typedef typename Array::const_reverse_iterator const_reverse_iterator;
    typedef typename Array::element element;
    typedef typename Array::index index;
    typedef typename Array::index_gen index_gen;
    typedef typename Array::index_range index_range;
    typedef typename Array::extent_gen extent_gen;
    typedef typename Array::extent_range extent_range;

    Array a;
    size_type st;
    const size_type* stp;
    index id;
    const index* idp;
    const_iterator cit;
    const_reverse_iterator crit;
    const element* eltp;
    index_gen idgen;
    index_range range;
  };


  template <typename Array, std::size_t NumDims >
  struct MutableMultiArrayConcept
  {
    void constraints() {
      //    function_requires< CopyConstructibleConcept<Array> >();

      function_requires< boost_concepts::ForwardTraversalConcept<iterator> >();
      function_requires< boost_concepts::ReadableIteratorConcept<iterator> >();
      function_requires< boost_concepts::WritableIteratorConcept<iterator> >();
      function_requires< boost_concepts::ForwardTraversalConcept<const_iterator> >();
      function_requires< boost_concepts::ReadableIteratorConcept<const_iterator> >();
      function_requires< boost::OutputIterator<iterator,value_type> >();
      
      // RG - a( CollectionArchetype) when available...
      value_type vt = a[ id ];

      // Test slicing, keeping only the first dimension, losing the rest
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],id);

      // Test slicing, keeping all dimensions.
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],range);

      st = a.size();
      st = a.num_dimensions();
      st = a.num_elements();
      stp = a.shape();
      idp = a.strides();
      idp = a.index_bases();
      it = a.begin();
      it = a.end();
      rit = a.rbegin();
      rit = a.rend();
      eltp = a.origin();
      const_constraints(a);
    }

    void const_constraints(const Array& a) {

      //      value_type vt = a[ id ];

      // Test slicing, keeping only the first dimension, losing the rest
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],id);

      // Test slicing, keeping all dimensions.
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],range);

      st = a.size();
      st = a.num_dimensions();
      st = a.num_elements();
      stp = a.shape();
      idp = a.strides();
      idp = a.index_bases();
      cit = a.begin();
      cit = a.end();
      crit = a.rbegin();
      crit = a.rend();
      eltp = a.origin();
    }

    typedef typename Array::value_type value_type;
    typedef typename Array::reference reference;
    typedef typename Array::const_reference const_reference;
    typedef typename Array::size_type size_type;
    typedef typename Array::difference_type difference_type;
    typedef typename Array::iterator iterator;
    typedef typename Array::const_iterator const_iterator;
    typedef typename Array::reverse_iterator reverse_iterator;
    typedef typename Array::const_reverse_iterator const_reverse_iterator;
    typedef typename Array::element element;
    typedef typename Array::index index;
    typedef typename Array::index_gen index_gen;
    typedef typename Array::index_range index_range;
    typedef typename Array::extent_gen extent_gen;
    typedef typename Array::extent_range extent_range;

    Array a;
    size_type st;
    const size_type* stp;
    index id;
    const index* idp;
    iterator it;
    const_iterator cit;
    reverse_iterator rit;
    const_reverse_iterator crit;
    const element* eltp;
    index_gen idgen;
    index_range range;
  };


} // namespace multi_array

namespace detail {
  namespace multi_array { // Old locations for these
    using boost::multi_array_concepts::ConstMultiArrayConcept;
    using boost::multi_array_concepts::MutableMultiArrayConcept;
  }
}

} // namespace boost


#endif

/* concept_checks.hpp
BB0gyw/x9rycZPp92w/LIMkgLyDC83Kac6MoLHwL1fO8nOV5KdwiSazcE3qPHyxpjrPnuYxnebnlhRaGAWyTGf0Fk7F930rCtMR0wEqmzHYukwZlaLl2ium0yezjMkESu67n2pgOWMCUCblMFrtebMU+pkNl6Lx8Pz4v45F/PS/rfvPdn9B+41thaUsbi5WO1D210EHdeIf4J/x7sYxDWS3Fut/EjvUdYjr3uL7wvCRO46IU43My8OZz1uYhbObUiorKOrt8WD6dtbbYhYCeKgLNXhVjDvzl/32wXDOqvMGCa3lGfqPD9VPwlyvMjoqJzBsPC7f67T/yt6n5ZWmN2WXpRlK/bXhIxSsSvOuLb/HefxiQ2QltGHxXVNkacBXiU+pj7+/i78trq/j7dzfA7wsyPmjveZPd/jf8iRH4ffnZE9OyvqYmpZRaZ6PcgVGF65/x962b6t/h84if4VS/6+89fANU/w5PIJDfz2+uf3+ejLDawd/lG7jwu4xVBKUj/K/dRP8uS0diUL3yJzxudR6EQew5ZvhobFu6/g6w+sO3MbEOHlDXASB3xTst8PvizCCbnUWc2+xtI9Xvps2GRqvf4TOjR34/oX83bHnnjdXvpi1/Uf+ubYnzwt5hMv4lbuBafhkKFusz1/MN62uJCIPUDp1o3d/d2r6Xf0zsC/eD6v5xs7rde7kDDV+dmbp5/RuadXaJ3Zd+YF0X/J4j9AWNwfdO00d25w2Ay7SNCsP6QpzX46lR/buqMPx950b9u6oY/P0Y/q4qBn//3Cb9u6oYbLPbf8RjTTq5F7lJEYqpyV5HLtBUBGsIbmLU0f1+xOvI9a28tB1vvXWE77cwfaXICs9Jcse9hv8MXvtb6EgM/oe930L1uamIwiTKkzS6Dn3Ls7Ogz0mpvnNMXyjKIIlzx/OuX5+bUX13/zHVF4nIiayo9K4nf1Be1BfrdTnVZ8OCMUjdctD7N/P0brEO9pHpvL3cyFsR5p7rR/F15K21rGeoPtlEHC8rU9srr6FvdbHLyor9+cIPaX+Wx3Tq/nzbuu/aN+yB/sz67YPqfls1axbnQGJSx4B+eQ5xY04a0b/zfvld/J33SzGqf5dPPfTIvR38nffXmU3696q/xnpt+EMe4zNx48ApZH+VDdZfWJMGlP/tsf/M6P/TKyb6PvGDVfyv7grEflNB6nvoV5NzTBsOq4Y+p9zQypntSgzHNsWpcLn2ULFj7ivrCqK2jKdFoHy/dfAYGIMfXGFjzjgi6vfd9PfFLv6+F39XlQG/qzQeSdNAiSGFPYZiKKXWkmibhwzL0lSx0aphS4dHq9aSOIZe+Q4fQ+M0tpIoSftx9Rfmp1YmV55vxObc+l22XkjiMM2dLBW95/dWO4uGFEnv7t/l6dlWamWZ44qp+UMyPImKVy9fU+n0DB/JHiqXCz/1IzcIXQGPC6CMET/PZWlFwvZSr/CtTLjyvZ156YoJ5XJcPnxkKrC1X4HJJyJx7DC1oljItdD86uQCTDDP7SzImaKR7f67BUxHKILQDvwisfBdD/12lFEGnYe3MflUBFacuqkXiOWpZ3Wm4dGJGflu0LwszspA232O264si8gL3FiUXmbKYOzn73IZr0wTrww9MdO09+N0Xs+hDL5RE/l5EYjDe3ftl4NjZwUyOj25ehV73WjYq0gyN4nlX8ANS2b0Qfba8T0qnwk/j/wySUoBwZ7mD62t6IcZ5JA9qN4fzXQkIigiq4wdX72TtVx1iapTDS7HQaYjEnnu+KXjRgK+AOUzu9PSHmsrzzXzgP3kMJUvRVgEieVIM3iOO2Y1k11CXwCVK0RoOVmSxyAWmlJCy7yNyuQikE1cduZUjI0=
*/