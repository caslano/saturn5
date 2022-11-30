// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor -at- gmail.com>
// Copyright (C) 2004 The Trustees of Indiana University

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//   Authors: Douglas Gregor
//            Andrew Lumsdaine

// Message Passing Interface 1.1 -- Section 4.9.1. Reduce
#ifndef BOOST_MPI_ALL_REDUCE_HPP
#define BOOST_MPI_ALL_REDUCE_HPP

#include <vector>

#include <boost/mpi/inplace.hpp>

// All-reduce falls back to reduce() + broadcast() in some cases.
#include <boost/mpi/collectives/broadcast.hpp>
#include <boost/mpi/collectives/reduce.hpp>

namespace boost { namespace mpi {
namespace detail {
  /**********************************************************************
   * Simple reduction with MPI_Allreduce                                *
   **********************************************************************/
  // We are reducing for a type that has an associated MPI
  // datatype and operation, so we'll use MPI_Allreduce directly.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op /*op*/, mpl::true_ /*is_mpi_op*/,
                  mpl::true_ /*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Allreduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), comm));
  }

  /**********************************************************************
   * User-defined reduction with MPI_Allreduce                          *
   **********************************************************************/
  // We are reducing at the root for a type that has an associated MPI
  // datatype but with a custom operation. We'll use MPI_Reduce
  // directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op /* op */, mpl::false_ /*is_mpi_op*/,
                  mpl::true_ /*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op;
    BOOST_MPI_CHECK_RESULT(MPI_Allreduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            mpi_op.get_mpi_op(), comm));
  }

  /**********************************************************************
   * User-defined, tree-based reduction for non-MPI data types          *
   **********************************************************************/
  // We are reducing at the root for a type that has no associated MPI
  // datatype and operation, so we'll use a simple tree-based
  // algorithm.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op op, mpl::false_ /*is_mpi_op*/,
                  mpl::false_ /*is_mpi_datatype*/)
  {
    if (in_values == MPI_IN_PLACE) {
      // if in_values matches the in place tag, then the output
      // buffer actually contains the input data.
      // But we can just go back to the out of place 
      // implementation in this case.
      // it's not clear how/if we can avoid the copy.
      std::vector<T> tmp_in( out_values, out_values + n);
      reduce(comm, detail::c_data(tmp_in), n, out_values, op, 0);
    } else {
      reduce(comm, in_values, n, out_values, op, 0);
    }
    broadcast(comm, out_values, n, 0);
  }
} // end namespace detail

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, const T* in_values, int n, T* out_values,
           Op op)
{
  detail::all_reduce_impl(comm, in_values, n, out_values, op,
                          is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, inplace_t<T*> inout_values, int n, Op op)
{
  all_reduce(comm, static_cast<const T*>(MPI_IN_PLACE), n, inout_values.buffer, op);
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, inplace_t<T> inout_values, Op op)
{
  all_reduce(comm, static_cast<const T*>(MPI_IN_PLACE), 1, &(inout_values.buffer), op);
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, const T& in_value, T& out_value, Op op)
{
  detail::all_reduce_impl(comm, &in_value, 1, &out_value, op,
                          is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
T all_reduce(const communicator& comm, const T& in_value, Op op)
{
  T result;
  ::boost::mpi::all_reduce(comm, in_value, result, op);
  return result;
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_ALL_REDUCE_HPP

/* all_reduce.hpp
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
*/