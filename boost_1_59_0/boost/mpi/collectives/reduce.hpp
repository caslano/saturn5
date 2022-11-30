// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor@gmail.com>.
// Copyright (C) 2004 The Trustees of Indiana University

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//   Authors: Douglas Gregor
//            Andrew Lumsdaine

// Message Passing Interface 1.1 -- Section 4.9.1. Reduce
#ifndef BOOST_MPI_REDUCE_HPP
#define BOOST_MPI_REDUCE_HPP

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
#include <boost/scoped_array.hpp>

namespace boost { namespace mpi {


/************************************************************************
 * Implementation details                                               *
 ************************************************************************/
namespace detail {
  /**********************************************************************
   * Simple reduction with MPI_Reduce                                   *
   **********************************************************************/
  // We are reducing at the root for a type that has an associated MPI
  // datatype and operation, so we'll use MPI_Reduce directly.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T* in_values, int n,
              T* out_values, Op /*op*/, int root, mpl::true_ /*is_mpi_op*/,
              mpl::true_/*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), root, comm));
  }

  // We are reducing to the root for a type that has an associated MPI
  // datatype and operation, so we'll use MPI_Reduce directly.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T* in_values, int n, Op /*op*/,
              int root, mpl::true_ /*is_mpi_op*/, mpl::true_/*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(in_values), 0, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), root, comm));
  }

  /**********************************************************************
   * User-defined reduction with MPI_Reduce                             *
   **********************************************************************/

  // We are reducing at the root for a type that has an associated MPI
  // datatype but with a custom operation. We'll use MPI_Reduce
  // directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T* in_values, int n,
              T* out_values, Op op, int root, mpl::false_ /*is_mpi_op*/,
              mpl::true_/*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op;
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            mpi_op.get_mpi_op(), root, comm));
  }

  // We are reducing to the root for a type that has an associated MPI
  // datatype but with a custom operation. We'll use MPI_Reduce
  // directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T* in_values, int n, Op op,
              int root, mpl::false_/*is_mpi_op*/, mpl::true_/*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op;
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(in_values), 0, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            mpi_op.get_mpi_op(), root, comm));
  }

  /**********************************************************************
   * User-defined, tree-based reduction for non-MPI data types          *
   **********************************************************************/

  // Commutative reduction
  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T* in_values, int n,
                   T* out_values, Op op, int root,
                   mpl::true_ /*is_commutative*/)
  {
    std::copy(in_values, in_values + n, out_values);

    int size = comm.size();
    int rank = comm.rank();

    // The computation tree we will use.
    detail::computation_tree tree(rank, size, root);

    int tag = environment::collectives_tag();

    MPI_Status status;
    int children = 0;
    for (int child = tree.child_begin();
         children < tree.branching_factor() && child != root;
         ++children, child = (child + 1) % size) {
      // Receive archive
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, child, tag, ia, status);

      T incoming;
      for (int i = 0; i < n; ++i) {
        ia >> incoming;
        out_values[i] = op(out_values[i], incoming);
      }
    }

    // For non-roots, send the result to the parent.
    if (tree.parent() != rank) {
      packed_oarchive oa(comm);
      for (int i = 0; i < n; ++i)
        oa << out_values[i];
      detail::packed_archive_send(comm, tree.parent(), tag, oa);
    }
  }

  // Commutative reduction from a non-root.
  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T* in_values, int n, Op op,
                   int root, mpl::true_ /*is_commutative*/)
  {
    scoped_array<T> results(new T[n]);
    detail::tree_reduce_impl(comm, in_values, n, results.get(), op, root,
                             mpl::true_());
  }

  // Non-commutative reduction
  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T* in_values, int n,
                   T* out_values, Op op, int root,
                   mpl::false_ /*is_commutative*/)
  {
    int tag = environment::collectives_tag();

    int left_child = root / 2;
    int right_child = (root + comm.size()) / 2;

    MPI_Status status;
    if (left_child != root) {
      // Receive value from the left child and merge it with the value
      // we had incoming.
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, left_child, tag, ia, status);
      T incoming;
      for (int i = 0; i < n; ++i) {
        ia >> incoming;
        out_values[i] = op(incoming, in_values[i]);
      }
    } else {
      // There was no left value, so copy our incoming value.
      std::copy(in_values, in_values + n, out_values);
    }

    if (right_child != root) {
      // Receive value from the right child and merge it with the
      // value we had incoming.
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, right_child, tag, ia, status);
      T incoming;
      for (int i = 0; i < n; ++i) {
        ia >> incoming;
        out_values[i] = op(out_values[i], incoming);
      }
    }
  }

  // Non-commutative reduction from a non-root.
  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T* in_values, int n, Op op,
                   int root, mpl::false_ /*is_commutative*/)
  {
    int size = comm.size();
    int rank = comm.rank();

    int tag = environment::collectives_tag();

    // Determine our parents and children in the commutative binary
    // computation tree.
    int grandparent = root;
    int parent = root;
    int left_bound = 0;
    int right_bound = size;
    int left_child, right_child;
    do {
      left_child = (left_bound + parent) / 2;
      right_child = (parent + right_bound) / 2;

      if (rank < parent) {
        // Go left.
        grandparent = parent;
        right_bound = parent;
        parent = left_child;
      } else if (rank > parent) {
        // Go right.
        grandparent = parent;
        left_bound = parent + 1;
        parent = right_child;
      } else {
        // We've found the parent
        break;
      }
    } while (true);

    // Our parent is the grandparent of our children. This is a slight
    // abuse of notation, but it makes the send-to-parent below make
    // more sense.
    parent = grandparent;

    MPI_Status status;
    scoped_array<T> out_values(new T[n]);
    if (left_child != rank) {
      // Receive value from the left child and merge it with the value
      // we had incoming.
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, left_child, tag, ia, status);
      T incoming;
      for (int i = 0; i < n; ++i) {
        ia >> incoming;
        out_values[i] = op(incoming, in_values[i]);
      }
    } else {
      // There was no left value, so copy our incoming value.
      std::copy(in_values, in_values + n, out_values.get());
    }

    if (right_child != rank) {
      // Receive value from the right child and merge it with the
      // value we had incoming.
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, right_child, tag, ia, status);
      T incoming;
      for (int i = 0; i < n; ++i) {
        ia >> incoming;
        out_values[i] = op(out_values[i], incoming);
      }
    }

    // Send the combined value to our parent.
    packed_oarchive oa(comm);
    for (int i = 0; i < n; ++i)
      oa << out_values[i];
    detail::packed_archive_send(comm, parent, tag, oa);
  }

  // We are reducing at the root for a type that has no associated MPI
  // datatype and operation, so we'll use a simple tree-based
  // algorithm.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T* in_values, int n,
              T* out_values, Op op, int root, mpl::false_ /*is_mpi_op*/,
              mpl::false_ /*is_mpi_datatype*/)
  {
    detail::tree_reduce_impl(comm, in_values, n, out_values, op, root,
                             is_commutative<Op, T>());
  }

  // We are reducing to the root for a type that has no associated MPI
  // datatype and operation, so we'll use a simple tree-based
  // algorithm.
  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T* in_values, int n, Op op,
              int root, mpl::false_ /*is_mpi_op*/,
              mpl::false_ /*is_mpi_datatype*/)
  {
    detail::tree_reduce_impl(comm, in_values, n, op, root,
                             is_commutative<Op, T>());
  }
} // end namespace detail

template<typename T, typename Op>
void
reduce(const communicator& comm, const T* in_values, int n, T* out_values,
       Op op, int root)
{
  if (comm.rank() == root)
    detail::reduce_impl(comm, in_values, n, out_values, op, root,
                        is_mpi_op<Op, T>(), is_mpi_datatype<T>());
  else
    detail::reduce_impl(comm, in_values, n, op, root,
                        is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
void
reduce(const communicator& comm, const T* in_values, int n, Op op, int root)
{
  BOOST_ASSERT(comm.rank() != root);

  detail::reduce_impl(comm, in_values, n, op, root,
                      is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
void
reduce(const communicator & comm, std::vector<T> const & in_values, Op op,
       int root)
{
  reduce(comm, detail::c_data(in_values), in_values.size(), op, root);
}

template<typename T, typename Op>
void
reduce(const communicator & comm, std::vector<T> const & in_values,
       std::vector<T> & out_values, Op op, int root)
{
  if (root == comm.rank()) out_values.resize(in_values.size());
  reduce(comm, detail::c_data(in_values), in_values.size(), detail::c_data(out_values), op,
         root);
}


template<typename T, typename Op>
void
reduce(const communicator& comm, const T& in_value, T& out_value, Op op,
       int root)
{
  if (comm.rank() == root)
    detail::reduce_impl(comm, &in_value, 1, &out_value, op, root,
                        is_mpi_op<Op, T>(), is_mpi_datatype<T>());
  else
    detail::reduce_impl(comm, &in_value, 1, op, root,
                        is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
void reduce(const communicator& comm, const T& in_value, Op op, int root)
{
  BOOST_ASSERT(comm.rank() != root);

  detail::reduce_impl(comm, &in_value, 1, op, root,
                      is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_REDUCE_HPP

/* reduce.hpp
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
*/