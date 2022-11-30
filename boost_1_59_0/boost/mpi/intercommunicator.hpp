// Copyright (C) 2007 The Trustees of Indiana University.

// Authors: Douglas Gregor
//          Andrew Lumsdaine

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file intercommunicator.hpp
 *
 *  This header defines the @c intercommunicator class, which permits
 *  communication between different process groups.
 */
#ifndef BOOST_MPI_INTERCOMMUNICATOR_HPP
#define BOOST_MPI_INTERCOMMUNICATOR_HPP

#include <boost/mpi/communicator.hpp>

namespace boost { namespace mpi {

/**
 * INTERNAL ONLY
 *
 * Forward declaration of the MPI "group" representation, for use in
 * the description of the @c intercommunicator class.
 */ 
class group;

/**
 * @brief Communication facilities among processes in different
 * groups.
 *
 * The @c intercommunicator class provides communication facilities
 * among processes from different groups. An intercommunicator is
 * always associated with two process groups: one "local" process
 * group, containing the process that initiates an MPI operation
 * (e.g., the sender in a @c send operation), and one "remote" process
 * group, containing the process that is the target of the MPI
 * operation.
 *
 * While intercommunicators have essentially the same point-to-point
 * operations as intracommunicators (the latter communicate only
 * within a single process group), all communication with
 * intercommunicators occurs between the processes in the local group
 * and the processes in the remote group; communication within a group
 * must use a different (intra-)communicator.
 * 
 */   
class BOOST_MPI_DECL intercommunicator : public communicator
{
private:
  friend class communicator;

  /**
   * INTERNAL ONLY
   *
   * Construct an intercommunicator given a shared pointer to the
   * underlying MPI_Comm. This operation is used for "casting" from a
   * communicator to an intercommunicator.
   */
  explicit intercommunicator(const shared_ptr<MPI_Comm>& cp)
  {
    this->comm_ptr = cp;
  }

public:
  /**
   * Build a new Boost.MPI intercommunicator based on the MPI
   * intercommunicator @p comm.
   *
   * @p comm may be any valid MPI intercommunicator. If @p comm is
   * MPI_COMM_NULL, an empty communicator (that cannot be used for
   * communication) is created and the @p kind parameter is
   * ignored. Otherwise, the @p kind parameter determines how the
   * Boost.MPI communicator will be related to @p comm:
   *
   *   - If @p kind is @c comm_duplicate, duplicate @c comm to create
   *   a new communicator. This new communicator will be freed when
   *   the Boost.MPI communicator (and all copies of it) is
   *   destroyed. This option is only permitted if the underlying MPI
   *   implementation supports MPI 2.0; duplication of
   *   intercommunicators is not available in MPI 1.x.
   *
   *   - If @p kind is @c comm_take_ownership, take ownership of @c
   *   comm. It will be freed automatically when all of the Boost.MPI
   *   communicators go out of scope.
   *
   *   - If @p kind is @c comm_attach, this Boost.MPI communicator
   *   will reference the existing MPI communicator @p comm but will
   *   not free @p comm when the Boost.MPI communicator goes out of
   *   scope. This option should only be used when the communicator is
   *   managed by the user.
   */
  intercommunicator(const MPI_Comm& comm, comm_create_kind kind)
    : communicator(comm, kind) { }

  /**
   * Constructs a new intercommunicator whose local group is @p local
   * and whose remote group is @p peer. The intercommunicator can then
   * be used to communicate between processes in the two groups. This
   * constructor is equivalent to a call to @c MPI_Intercomm_create.
   *
   * @param local The intracommunicator containing all of the
   * processes that will go into the local group.
   *
   * @param local_leader The rank within the @p local
   * intracommunicator that will serve as its leader.
   *
   * @param peer The intracommunicator containing all of the processes
   * that will go into the remote group.
   *
   * @param remote_leader The rank within the @p peer group that will
   * serve as its leader.
   */
  intercommunicator(const communicator& local, int local_leader,
                    const communicator& peer, int remote_leader);

  /**
   * Returns the size of the local group, i.e., the number of local
   * processes that are part of the group.
   */
  int local_size() const { return this->size(); }

  /**
   * Returns the local group, containing all of the local processes in
   * this intercommunicator.
   */
  boost::mpi::group local_group() const;

  /**
   * Returns the rank of this process within the local group.
   */
  int local_rank() const { return this->rank(); }

  /**
   * Returns the size of the remote group, i.e., the number of
   * processes that are part of the remote group.
   */
  int remote_size() const;

  /**
   * Returns the remote group, containing all of the remote processes
   * in this intercommunicator.
   */
  boost::mpi::group remote_group() const;

  /**
   * Merge the local and remote groups in this intercommunicator into
   * a new intracommunicator containing the union of the processes in
   * both groups. This method is equivalent to @c MPI_Intercomm_merge.
   *  
   * @param high Whether the processes in this group should have the
   * higher rank numbers than the processes in the other group. Each
   * of the processes within a particular group shall have the same
   * "high" value.
   *
   * @returns the new, merged intracommunicator
   */
  communicator merge(bool high) const;
};

} } // end namespace boost::mpi

#endif // BOOST_MPI_INTERCOMMUNICATOR_HPP

/* intercommunicator.hpp
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
*/