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
TPqn2gJt/tW2Tg3nOnUFXrGY6wrgJFmnrkD3SxvLCKsMKQxEUB1UY3Sx5gSt9eoJXLw4fGkWyqNvBCV1txizCUqhLOVoFsof9rIeHWdK+ndkhAldvzG6cj4ldHXeQ+hq96aOruUTDXRFxRno6nW5lTK7FJKxjPLfXsLRLYV6rj/Mu4GJJTEXmjK0EO35AzCkpSSuGD2Bi2Xlc809fbyzAYnXA+W7SCyf84fHyCyfhysjfDiRM1WD2v5Tez1eBjM+IJqVTzD3kebu0WDXe8nr4nhRNqUV5LQt02I5uGojwZE2gyOy0JLlVtC2CqI8Gm/j5raCSblBUncZr7/2QbRct+JX9oVXLsd1NnLjpXiC6CbwdL5YL/qTyIku66dVo4kD418WkixGnOr1AUT9a5eelPhmOFLHujjYaQSeDHORNJX5x8M//Vycu3iUUOMNQvnrXKROKIuJUA5lKqcyUU4mXWSw9LYbmEaSkUawPBPQyOX7iEaidhGN/PYa00iyekce00iy5q66UNBIshrRi1m6UDKIpFWcKP7k5BtJx7NgWiyFTwZBP7cQ5uoyPNQW4v6hZ8Em/NkDinJJe5heaU6VGeoF5I/0Bb9oci9K/u1ou4+Nt4l8eeuYUA7uZPXPBKtOvHdexrupyUquyPiSrN7Zhz3YvnlEz/iSrI5M5M1vm43jL/ay0TcZ6W7iyzZcFSfgtN2tW0PT9qegwGCK
*/