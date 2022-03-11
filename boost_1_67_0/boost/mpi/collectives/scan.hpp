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