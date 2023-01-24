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
#include <functional>

namespace boost { namespace parallel {
  template<typename BinaryOp>
  struct is_commutative
  {
    BOOST_STATIC_CONSTANT(bool, value = false);
  };

  template<typename T>
  struct minimum : std::binary_function<T, T, T>
  {
    const T& operator()(const T& x, const T& y) const { return x < y? x : y; }
  };

  template<typename T>
  struct maximum : std::binary_function<T, T, T>
  {
    const T& operator()(const T& x, const T& y) const { return x < y? y : x; }
  };

  template<typename T>
  struct sum : std::binary_function<T, T, T>
  {
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
XjP8KEEsu7KT24+D1LPtiwJChwQOvYifKBl9taPOSuACDyKHfulgdZQ6SqY713SmWsuzFVRjUimYsbEiZULwC1coyKsN22KoXH9NqDZ+DQfA9jNtXxw6jjckcnI5pmQkWbWnF2uPmN8BgG9ahG+Or94clQ/FmnYEbF51W/uZ/snwMeSpm9DAFkzeFhq/YbOIqjd6bvSneMwKaEFuHvmnxGR6PyM4Jjv5EJHWG5J7SssgQ21zt/JFJ6mgG8CEUSqIxt460kDMms0QC4DPPqZ/p+Na2FhO5jO+2zjeN5KYbNjVOWRxXSd6hCg6pU8eSSO/hR/s033C0wAqpXV8NMiERSEFjy1cMz+JpDJsQ9nen+1LY6Z1LL0/8j6YViQfAsYw0A1Vr8zFCjNIvn43IoBVHZAMOPJubpWOrP/TxTvme2OsNI5xnrTyQPf12f06zolZW8QKiYjVnL4F+UiYLvklN957Ld4UH2h1wsQkZ0mFlFV5ws0PHl53KzqfhZrQXFTeXWnik8jaqG7NPGcSdFi4BjRrt9YjHJIy7mQBqs06PRdUR6M951l1a0nhCsNd6Ok3uqxlcvKMcZhngZ29q1bamQvUBmqynlghJXOnDryEHlFFb11cWw0zlR4Gy+SyhUzIDsKJ310/ncmdPEXzbBd8ExKnCvjDY8eWJUctclPpMZZbkCI9Qz9F/wSk1DW05tAZC6xdH8JA+hOVB5NW
*/