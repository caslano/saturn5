// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_PARALLEL_ALGORITHM_HPP
#define BOOST_PARALLEL_ALGORITHM_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/optional.hpp>
#include <boost/config.hpp> // for BOOST_STATIC_CONSTANT
#include <vector>

namespace boost { namespace parallel {
  template<typename BinaryOp>
  struct is_commutative
  {
    BOOST_STATIC_CONSTANT(bool, value = false);
  };

  template<typename T>
  struct minimum
  {
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef T result_type;
    const T& operator()(const T& x, const T& y) const { return x < y? x : y; }
  };

  template<typename T>
  struct maximum
  {
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef T result_type;
    const T& operator()(const T& x, const T& y) const { return x < y? y : x; }
  };

  template<typename T>
  struct sum
  {
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef T result_type;
    const T operator()(const T& x, const T& y) const { return x + y; }
  };

  template<typename ProcessGroup, typename InputIterator,
           typename OutputIterator, typename BinaryOperation>
  OutputIterator
  reduce(ProcessGroup pg, typename ProcessGroup::process_id_type root,
         InputIterator first, InputIterator last, OutputIterator out,
         BinaryOperation bin_op);

  template<typename ProcessGroup, typename T, typename BinaryOperation>
  inline T
  all_reduce(ProcessGroup pg, const T& value, BinaryOperation bin_op)
  {
    T result;
    all_reduce(pg,
               const_cast<T*>(&value), const_cast<T*>(&value+1),
               &result, bin_op);
    return result;
  }

  template<typename ProcessGroup, typename T, typename BinaryOperation>
  inline T
  scan(ProcessGroup pg, const T& value, BinaryOperation bin_op)
  {
    T result;
    scan(pg,
         const_cast<T*>(&value), const_cast<T*>(&value+1),
         &result, bin_op);
    return result;
  }


  template<typename ProcessGroup, typename InputIterator, typename T>
  void
  all_gather(ProcessGroup pg, InputIterator first, InputIterator last,
             std::vector<T>& out);
} } // end namespace boost::parallel

#include <boost/graph/parallel/detail/inplace_all_to_all.hpp>

#endif // BOOST_PARALLEL_ALGORITHM_HPP

/* algorithm.hpp
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
*/