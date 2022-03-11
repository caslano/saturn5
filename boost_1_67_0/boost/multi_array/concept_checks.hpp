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