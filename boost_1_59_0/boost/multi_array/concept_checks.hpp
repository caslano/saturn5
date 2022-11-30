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
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
*/