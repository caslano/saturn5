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
  reduce(comm, &in_values.front(), in_values.size(), op, root);
}

template<typename T, typename Op>
void
reduce(const communicator & comm, std::vector<T> const & in_values,
       std::vector<T> & out_values, Op op, int root)
{
  if (root == comm.rank()) out_values.resize(in_values.size());
  reduce(comm, &in_values.front(), in_values.size(), &out_values.front(), op,
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