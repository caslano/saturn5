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