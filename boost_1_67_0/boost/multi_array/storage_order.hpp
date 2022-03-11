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