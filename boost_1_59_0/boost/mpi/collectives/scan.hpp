// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor@gmail.com>.
// Copyright (C) 2004 The Trustees of Indiana University

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//   Authors: Douglas Gregor
//            Andrew Lumsdaine

// Message Passing Interface 1.1 -- Section 4.9.1. Scan
#ifndef BOOST_MPI_SCAN_HPP
#define BOOST_MPI_SCAN_HPP

#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>

// For (de-)serializing sends and receives
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>

// For packed_[io]archive sends and receives
#include <boost/mpi/detail/point_to_point.hpp>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/detail/computation_tree.hpp>
#include <boost/mpi/operations.hpp>
#include <algorithm>
#include <exception>
#include <boost/assert.hpp>

namespace boost { namespace mpi {


/************************************************************************
 * Implementation details                                               *
 ************************************************************************/
namespace detail {
  /**********************************************************************
   * Simple prefix reduction with MPI_Scan                              *
   **********************************************************************/

  // We are performing prefix reduction for a type that has an
  // associated MPI datatype and operation, so we'll use MPI_Scan
  // directly.
  template<typename T, typename Op>
  void
  scan_impl(const communicator& comm, const T* in_values, int n, T* out_values,
            Op /*op*/, mpl::true_ /*is_mpi_op*/, mpl::true_ /*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Scan,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), comm));
  }

  /**********************************************************************
   * User-defined prefix reduction with MPI_Scan                        *
   **********************************************************************/

  // We are performing prefix reduction for a type that has an
  // associated MPI datatype but with a custom operation. We'll use
  // MPI_Scan directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  scan_impl(const communicator& comm, const T* in_values, int n, T* out_values,
            Op op, mpl::false_ /*is_mpi_op*/, mpl::true_ /*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op;
    BOOST_MPI_CHECK_RESULT(MPI_Scan,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            mpi_op.get_mpi_op(), comm));
  }

  /**********************************************************************
   * User-defined, tree-based reduction for non-MPI data types          *
   **********************************************************************/

  template<typename T, typename Op>
  void
  upper_lower_scan(const communicator& comm, const T* in_values, int n,
                   T* out_values, Op& op, int lower, int upper)
  {
    int tag = environment::collectives_tag();
    int rank = comm.rank();

    if (lower + 1 == upper) {
      std::copy(in_values, in_values + n, out_values);
    } else {
      int middle = (lower + upper) / 2;
      
      if (rank < middle) {
        // Lower half
        upper_lower_scan(comm, in_values, n, out_values, op, lower, middle);

        // If we're the last process in the lower half, send our values
        // to everyone in the upper half.
        if (rank == middle - 1) {
          packed_oarchive oa(comm);
          for (int i = 0; i < n; ++i)
            oa << out_values[i];

          for (int p = middle; p < upper; ++p)
            comm.send(p, tag, oa);
        }
      } else {
        // Upper half
        upper_lower_scan(comm, in_values, n, out_values, op, middle, upper);

        // Receive value from the last process in the lower half.
        packed_iarchive ia(comm);
        comm.recv(middle - 1, tag, ia);

        // Combine value that came from the left with our value
        T left_value;
        for (int i = 0; i < n; ++i)
          {
            ia >> left_value;
            out_values[i] = op(left_value, out_values[i]);
          }
      }
    }
  }

  // We are performing prefix reduction for a type that has no
  // associated MPI datatype and operation, so we'll use a simple
  // upper/lower algorithm.
  template<typename T, typename Op>
  inline void
  scan_impl(const communicator& comm, const T* in_values, int n, T* out_values, 
            Op op, mpl::false_ /*is_mpi_op*/, mpl::false_/*is_mpi_datatype*/)
  {
    upper_lower_scan(comm, in_values, n, out_values, op, 0, comm.size());
  }
} // end namespace detail


template<typename T, typename Op>
inline void
scan(const communicator& comm, const T& in_value, T& out_value, Op op)
{
  detail::scan_impl(comm, &in_value, 1, &out_value, op, 
                    is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
inline void
scan(const communicator& comm, const T* in_values, int n, T* out_values, Op op)
{
  detail::scan_impl(comm, in_values, n, out_values, op, 
                    is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
inline T
scan(const communicator& comm, const T& in_value, Op op)
{
  T out_value;
  detail::scan_impl(comm, &in_value, 1, &out_value, op, 
                    is_mpi_op<Op, T>(), is_mpi_datatype<T>());
  return out_value;
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_SCAN_HPP

/* scan.hpp
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
*/