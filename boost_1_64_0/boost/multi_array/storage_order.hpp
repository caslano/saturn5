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
c8OcY+J/M/C6uaFNXnQLjrPmRveDbmnysLnhuuxLgzmtJ1Fxvb6NyFVREcl3FWCDrqSQePy3bvDMLojndB50G+Be+2oMnp1s8rF5sXa8vcGjzQPr5LLiNZZQuIY683YjXm+W+F6QOeJ5K8sQiKjaIdnbv0RoxBa+QOUz4RVR7LtFqMVlDWC4sUUtc5nLRH6UWEHiCjuHteusfCkP7w4v6j2m0Xfw2FpRmLtFnMZiZvf8hOeURv5WMLYZk3NFkFlhmeWFlkuYJI9RtstIs3ACKw2zQMtWrTfRce6ElnOZnCXcMklDP5RyyxP0BESdIModMNLz3dJ1wrjeQlrsyTkYpkWU03W4wORi4YWZ4yYFEVQrkjn5wtoMfBos13Wo0z1i2rZIHD8ofWEuQSu5WZ3ucSYXqTNFVpgVgm35muL9dD9npFv6WWpZsSvMYw+V4PO13FnDvl5YJqEdZYIf69DpPR/bKpUrRG45fpraUSXG08I2cNm0TZKEVmiXwjxCUclhWlveydJKHSsrwzwWeFe4H17X0jI7qEwusiB2/cQtKhleJszf/d7J85fabhAXNtQBdHbVb3eDq6TOn+4Xj2Zyroi8MHWSLKBy9YHIRr8YZ7KOSArPiiM707KyXzBRLbdgyAVOaQVukFK5zlJT7uVGGeM0TGCY0XJrUyw5lDtmyPlhloSO4/XlMDkmd9KQSxw7LbwwruXAmruVgQy5Lxk2TTyriDJbmCejzLiPv2BygYgsO7f9OBatR6q47GUmK7ts5AV5GqtEk9ZkSXzw47z/lnYSl2lQcFmeMvRfLf8gQz7JCzdzHKiX6lz2C3bvvYG4lLS8XcuHTB6C5ue2bIIpl4cVE1lBGWVYaOShTIvSL5gOfWtEqtL9R8u/ksknIgitxHKcnMmzTS1+rvKEIR/bSZC4QcTlnyejbC0/rzODOcBzh2eofCpiJwsSv0hE/6Y97wu/YOlZwvcD2fUCWxhX6M05929UrhRSwo2irBT89jtvW0PvMmIWF1nhOg6MEWqZWa3vdtNDFDtx3mWygXBit4ysPDdklSt33oj5uofKOo6w3VKmGkdC77SDs+jQ8mJn5flVzao2Mt9dEEOo4yDTEYkwtfzECVDFoCt79BzxEVaGUqSJFfhlxpU07601YlWeZnpiGId8L1JtpP3kQB3nU8v/xJC3HbeoYoO3n1DQ8rYeI5gtMiErIvGKLGTybffFxJDQOu73bkNH7HhBbEftOnqtOg4yHYnwskIdL7vWIQ261jn6bm4LNyltOEosWo/zY5Ne1vKnDPky8GwnzPOmPOsSy7pdn2XygUjsyAl8y26Rx75u6z7IZHNROBl4WmNxlWsBdfpCp7/tPTz9zLGy3EkK0XpdgKf/ICabiSAP8zRzmeiAtix0nyipDscSTp7ZXpp5glzH6e7evWeAIszLYZaXVJROKbMSx6ae5tA9ZGkdx1hecuFmSR6FQWbqaDRsEqP7rFGewHHSJLW4DjmEX6s8V8zyhEEiTeOYeq5Wnh3v5eWJ4zL0PD9t19FenvK9Rv1EYRllqcV07N39sIlr1c97eXlCL/fDMm7ouWr9GOWJYityC6dVh1ke7G8sH4FIUzuQPS4RrdfNjHjahmwexZHrZz6Xbe8rW97H+0qeR25QZizvA2xoYX+jOpxQ1oXjeH6UiWtdGxd9HQdZPgrhh4kVRdhPBk1B/O4H05EIpyiTMk1yMfBqM5c/zuQjkdtx7OVcvjl9DaH85wz52AscL7ACMeDqp9kWf8HsaIvEljURl4m41tVgsh4Yej8/2wwRcqPAadXBdkGJjj2mDs8pErv0W3X02nXM/Y+zKwuyq5vCfZPOgCAIYg5Syizd6UQ=
*/