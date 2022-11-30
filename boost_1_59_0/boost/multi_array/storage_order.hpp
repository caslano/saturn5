// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_STORAGE_ORDER_HPP
#define BOOST_MULTI_ARRAY_STORAGE_ORDER_HPP

#include "boost/multi_array/types.hpp"
#include "boost/array.hpp"
#include "boost/multi_array/algorithm.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <numeric>
#include <vector>

namespace boost {

  // RG - This is to make things work with VC++. So sad, so sad.
  class c_storage_order; 
  class fortran_storage_order;

  template <std::size_t NumDims>
  class general_storage_order
  {
  public:
    typedef detail::multi_array::size_type size_type;
    template <typename OrderingIter, typename AscendingIter>
    general_storage_order(OrderingIter ordering,
                          AscendingIter ascending) {
      boost::detail::multi_array::copy_n(ordering,NumDims,ordering_.begin());
      boost::detail::multi_array::copy_n(ascending,NumDims,ascending_.begin());
    }

    // RG - ideally these would not be necessary, but some compilers
    // don't like template conversion operators.  I suspect that not
    // too many folk will feel the need to use customized
    // storage_order objects, I sacrifice that feature for compiler support.
    general_storage_order(const c_storage_order&) {
      for (size_type i=0; i != NumDims; ++i) {
        ordering_[i] = NumDims - 1 - i;
      }
      ascending_.assign(true);
    }

    general_storage_order(const fortran_storage_order&) {
      for (size_type i=0; i != NumDims; ++i) {
        ordering_[i] = i;
      }
      ascending_.assign(true);
    }

    size_type ordering(size_type dim) const { return ordering_[dim]; }
    bool ascending(size_type dim) const { return ascending_[dim]; }

    bool all_dims_ascending() const {
      return std::accumulate(ascending_.begin(),ascending_.end(),true,
                      std::logical_and<bool>());
    }

    bool operator==(general_storage_order const& rhs) const {
      return (ordering_ == rhs.ordering_) &&
        (ascending_ == rhs.ascending_);
    }

  protected:
    boost::array<size_type,NumDims> ordering_;
    boost::array<bool,NumDims> ascending_;
  };

  class c_storage_order 
  {
    typedef detail::multi_array::size_type size_type;
  public:
    // This is the idiom for creating your own custom storage orders.
    // Not supported by all compilers though!
#ifndef __MWERKS__ // Metrowerks screams "ambiguity!"
    template <std::size_t NumDims>
    operator general_storage_order<NumDims>() const {
      boost::array<size_type,NumDims> ordering;
      boost::array<bool,NumDims> ascending;

      for (size_type i=0; i != NumDims; ++i) {
        ordering[i] = NumDims - 1 - i;
        ascending[i] = true;
      }
      return general_storage_order<NumDims>(ordering.begin(),
                                            ascending.begin());
    }
#endif
  };

  class fortran_storage_order
  {
    typedef detail::multi_array::size_type size_type;
  public:
    // This is the idiom for creating your own custom storage orders.
    // Not supported by all compilers though! 
#ifndef __MWERKS__ // Metrowerks screams "ambiguity!"
    template <std::size_t NumDims>
    operator general_storage_order<NumDims>() const {
      boost::array<size_type,NumDims> ordering;
      boost::array<bool,NumDims> ascending;

      for (size_type i=0; i != NumDims; ++i) {
        ordering[i] = i;
        ascending[i] = true;
      }
      return general_storage_order<NumDims>(ordering.begin(),
                                            ascending.begin());
    }
#endif
  };

} // namespace boost

#endif

/* storage_order.hpp
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
*/