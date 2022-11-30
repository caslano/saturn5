// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4. MPI Collectives

/** @file collectives.hpp
 *
 *  This header contains MPI collective operations, which implement
 *  various parallel algorithms that require the coordination of all
 *  processes within a communicator. The header @c collectives_fwd.hpp
 *  provides forward declarations for each of these operations. To
 *  include only specific collective algorithms, use the headers @c
 *  boost/mpi/collectives/algorithm_name.hpp.
 */
#ifndef BOOST_MPI_COLLECTIVES_HPP
#define BOOST_MPI_COLLECTIVES_HPP

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/inplace.hpp>
#include <vector>

namespace boost { namespace mpi {
/**
 *  @brief Gather the values stored at every process into vectors of
 *  values from each process.
 *
 *  @c all_gather is a collective algorithm that collects the values
 *  stored at each process into a vector of values indexed by the
 *  process number they came from. The type @c T of the values may be
 *  any type that is serializable or has an associated MPI data type.
 *
 *  When the type @c T has an associated MPI data type, this routine
 *  invokes @c MPI_Allgather to gather the values.
 *
 *    @param comm The communicator over which the all-gather will
 *    occur.
 *
 *    @param in_value The value to be transmitted by each process. To
 *    gather an array of values, @c in_values points to the @c n local
 *    values to be transmitted.
 *
 *    @param out_values A vector or pointer to storage that will be
 *    populated with the values from each process, indexed by the
 *    process ID number. If it is a vector, the vector will be resized
 *    accordingly.
 */
template<typename T>
void
all_gather(const communicator& comm, const T& in_value, 
           std::vector<T>& out_values);

/**
 * \overload
 */
template<typename T>
void
all_gather(const communicator& comm, const T& in_value, T* out_values);

/**
 * \overload
 */
template<typename T>
void
all_gather(const communicator& comm, const T* in_values, int n,
           std::vector<T>& out_values);

/**
 * \overload
 */
template<typename T>
void
all_gather(const communicator& comm, const T* in_values, int n, T* out_values);

/**
 *  @brief Combine the values stored by each process into a single
 *  value available to all processes.
 *
 *  @c all_reduce is a collective algorithm that combines the values
 *  stored by each process into a single value available to all
 *  processes. The values are combined in a user-defined way,
 *  specified via a function object. The type @c T of the values may
 *  be any type that is serializable or has an associated MPI data
 *  type. One can think of this operation as a @c all_gather, followed
 *  by an @c std::accumulate() over the gather values and using the
 *  operation @c op.
 *
 *  When the type @c T has an associated MPI data type, this routine
 *  invokes @c MPI_Allreduce to perform the reduction. If possible,
 *  built-in MPI operations will be used; otherwise, @c all_reduce()
 *  will create a custom MPI_Op for the call to MPI_Allreduce.
 *
 *    @param comm The communicator over which the reduction will
 *    occur.
 *    @param value The local value to be combined with the local
 *    values of every other process. For reducing arrays, @c in_values
 *    is a pointer to the local values to be reduced and @c n is the
 *    number of values to reduce. See @c reduce for more information.
 *
 *    If wrapped in a @c inplace_t object, combine the usage of both
 *    input and $c out_value and the local value will be overwritten
 *    (a convenience function @c inplace is provided for the wrapping).
 *
 *    @param out_value Will receive the result of the reduction
 *    operation. If this parameter is omitted, the outgoing value will
 *    instead be returned.
 *
 *    @param op The binary operation that combines two values of type
 *    @c T and returns a third value of type @c T. For types @c T that has
 *    ssociated MPI data types, @c op will either be translated into
 *    an @c MPI_Op (via @c MPI_Op_create) or, if possible, mapped
 *    directly to a built-in MPI operation. See @c is_mpi_op in the @c
 *    operations.hpp header for more details on this mapping. For any
 *    non-built-in operation, commutativity will be determined by the
 *    @c is_commmutative trait (also in @c operations.hpp): users are
 *    encouraged to mark commutative operations as such, because it
 *    gives the implementation additional lattitude to optimize the
 *    reduction operation.
 *
 *    @param n Indicated the size of the buffers of array type.
 *    @returns If no @p out_value parameter is supplied, returns the
 *    result of the reduction operation.
 */
template<typename T, typename Op>
void
all_reduce(const communicator& comm, const T* value, int n, T* out_value, 
           Op op);
/**
 * \overload
 */
template<typename T, typename Op>
void
all_reduce(const communicator& comm, const T& value, T& out_value, Op op);
/**
 * \overload
 */
template<typename T, typename Op>
T all_reduce(const communicator& comm, const T& value, Op op);

/**
 * \overload
 */
template<typename T, typename Op>
void
all_reduce(const communicator& comm, inplace_t<T*> value, int n,
           Op op);
/**
 * \overload
 */
template<typename T, typename Op>
void
all_reduce(const communicator& comm, inplace_t<T> value, Op op);

/**
 *  @brief Send data from every process to every other process.
 *
 *  @c all_to_all is a collective algorithm that transmits @c p values
 *  from every process to every other process. On process i, jth value
 *  of the @p in_values vector is sent to process j and placed in the
 *  ith position of the @p out_values vector in process @p j. The type
 *  @c T of the values may be any type that is serializable or has an
 *  associated MPI data type. If @c n is provided, then arrays of @p n
 *  values will be transferred from one process to another.
 *
 *  When the type @c T has an associated MPI data type, this routine
 *  invokes @c MPI_Alltoall to scatter the values.
 *
 *    @param comm The communicator over which the all-to-all
 *    communication will occur.
 *
 *    @param in_values A vector or pointer to storage that contains
 *    the values to send to each process, indexed by the process ID
 *    number.
 *
 *    @param out_values A vector or pointer to storage that will be
 *    updated to contain the values received from other processes. The
 *    jth value in @p out_values will come from the procss with rank j.
 */
template<typename T>
void
all_to_all(const communicator& comm, const std::vector<T>& in_values,
           std::vector<T>& out_values);

/**
 * \overload
 */
template<typename T>
void all_to_all(const communicator& comm, const T* in_values, T* out_values);

/**
 * \overload
 */
template<typename T>
void
all_to_all(const communicator& comm, const std::vector<T>& in_values, int n,
           std::vector<T>& out_values);

/**
 * \overload
 */
template<typename T>
void 
all_to_all(const communicator& comm, const T* in_values, int n, T* out_values);

/**
 * @brief Broadcast a value from a root process to all other
 * processes.
 *
 * @c broadcast is a collective algorithm that transfers a value from
 * an arbitrary @p root process to every other process that is part of
 * the given communicator. The @c broadcast algorithm can transmit any
 * Serializable value, values that have associated MPI data types,
 * packed archives, skeletons, and the content of skeletons; see the
 * @c send primitive for communicators for a complete list. The type
 * @c T shall be the same for all processes that are a part of the
 * communicator @p comm, unless packed archives are being transferred:
 * with packed archives, the root sends a @c packed_oarchive or @c
 * packed_skeleton_oarchive whereas the other processes receive a
 * @c packed_iarchive or @c packed_skeleton_iarchve, respectively.
 *
 * When the type @c T has an associated MPI data type, this routine
 * invokes @c MPI_Bcast to perform the broadcast.
 *
 *   @param comm The communicator over which the broadcast will
 *   occur.
 *
 *   @param value The value (or values, if @p n is provided) to be
 *   transmitted (if the rank of @p comm is equal to @p root) or
 *   received (if the rank of @p comm is not equal to @p root). When
 *   the @p value is a @c skeleton_proxy, only the skeleton of the
 *   object will be broadcast. In this case, the @p root will build a
 *   skeleton from the object help in the proxy and all of the
 *   non-roots will reshape the objects held in their proxies based on
 *   the skeleton sent from the root.
 *
 *   @param n When supplied, the number of values that the pointer @p
 *   values points to, for broadcasting an array of values. The value
 *   of @p n must be the same for all processes in @p comm.
 *
 *   @param root The rank/process ID of the process that will be
 *   transmitting the value.
 */
template<typename T>
void broadcast(const communicator& comm, T& value, int root);

/**
 * \overload
 */
template<typename T>
void broadcast(const communicator& comm, T* values, int n, int root);

/**
 * \overload
 */
template<typename T>
void broadcast(const communicator& comm, skeleton_proxy<T>& value, int root);

/**
 * \overload
 */
template<typename T>
void
broadcast(const communicator& comm, const skeleton_proxy<T>& value, int root);

/**
 *  @brief Gather the values stored at every process into a vector at
 *  the root process.
 *
 *  @c gather is a collective algorithm that collects the values
 *  stored at each process into a vector of values at the @p root
 *  process. This vector is indexed by the process number that the
 *  value came from. The type @c T of the values may be any type that
 *  is serializable or has an associated MPI data type.
 *
 *  When the type @c T has an associated MPI data type, this routine
 *  invokes @c MPI_Gather to gather the values.
 *
 *    @param comm The communicator over which the gather will occur.
 *
 *    @param in_value The value to be transmitted by each process. For
 *    gathering arrays of values, @c in_values points to storage for
 *    @c n*comm.size() values.
 *
 *    @param out_values A vector or pointer to storage that will be
 *    populated with the values from each process, indexed by the
 *    process ID number. If it is a vector, it will be resized
 *    accordingly. For non-root processes, this parameter may be
 *    omitted. If it is still provided, however, it will be unchanged.
 *
 *    @param root The process ID number that will collect the
 *    values. This value must be the same on all processes.
 */
template<typename T>
void
gather(const communicator& comm, const T& in_value, std::vector<T>& out_values,
       int root);

/**
 * \overload
 */
template<typename T>
void
gather(const communicator& comm, const T& in_value, T* out_values, int root);

/**
 * \overload
 */
template<typename T>
void gather(const communicator& comm, const T& in_value, int root);

/**
 * \overload
 */
template<typename T>
void
gather(const communicator& comm, const T* in_values, int n, 
       std::vector<T>& out_values, int root);

/**
 * \overload
 */
template<typename T>
void
gather(const communicator& comm, const T* in_values, int n, T* out_values, 
       int root);

/**
 * \overload
 */
template<typename T>
void gather(const communicator& comm, const T* in_values, int n, int root);

/**
 *  @brief Similar to boost::mpi::gather with the difference that the number
 *  of values to be send by non-root processes can vary.
 *
 *    @param comm The communicator over which the gather will occur.
 *
 *    @param in_values The array of values to be transmitted by each process.
 *
 *    @param in_size For each non-root process this specifies the size
 *    of @p in_values.
 *
 *    @param out_values A pointer to storage that will be populated with
 *    the values from each process. For non-root processes, this parameter
 *    may be omitted. If it is still provided, however, it will be unchanged.
 *
 *    @param sizes A vector containing the number of elements each non-root
 *    process will send.
 *
 *    @param displs A vector such that the i-th entry specifies the
 *    displacement (relative to @p out_values) from which to take the ingoing
 *    data at the @p root process. Overloaded versions for which @p displs is
 *    omitted assume that the data is to be placed contiguously at the root process.
 *
 *    @param root The process ID number that will collect the
 *    values. This value must be the same on all processes.
 */
template<typename T>
void
gatherv(const communicator& comm, const std::vector<T>& in_values,
        T* out_values, const std::vector<int>& sizes, const std::vector<int>& displs,
        int root);

/**
 * \overload
 */
template<typename T>
void
gatherv(const communicator& comm, const T* in_values, int in_size,
        T* out_values, const std::vector<int>& sizes, const std::vector<int>& displs,
        int root);

/**
 * \overload
 */
template<typename T>
void gatherv(const communicator& comm, const std::vector<T>& in_values, int root);

/**
 * \overload
 */
template<typename T>
void gatherv(const communicator& comm, const T* in_values, int in_size, int root);

/**
 * \overload
 */
template<typename T>
void
gatherv(const communicator& comm, const T* in_values, int in_size,
        T* out_values, const std::vector<int>& sizes, int root);

/**
 * \overload
 */
template<typename T>
void
gatherv(const communicator& comm, const std::vector<T>& in_values,
        T* out_values, const std::vector<int>& sizes, int root);

/**
 *  @brief Scatter the values stored at the root to all processes
 *  within the communicator.
 *
 *  @c scatter is a collective algorithm that scatters the values
 *  stored in the @p root process (inside a vector) to all of the
 *  processes in the communicator. The vector @p out_values (only
 *  significant at the @p root) is indexed by the process number to
 *  which the corresponding value will be sent. The type @c T of the
 *  values may be any type that is serializable or has an associated
 *  MPI data type.
 *
 *  When the type @c T has an associated MPI data type, this routine
 *  invokes @c MPI_Scatter to scatter the values.
 *
 *    @param comm The communicator over which the scatter will occur.
 *
 *    @param in_values A vector or pointer to storage that will contain
 *    the values to send to each process, indexed by the process rank.
 *    For non-root processes, this parameter may be omitted. If it is
 *    still provided, however, it will be unchanged.
 *
 *    @param out_value The value received by each process. When
 *    scattering an array of values, @p out_values points to the @p n
 *    values that will be received by each process.
 *
 *    @param root The process ID number that will scatter the
 *    values. This value must be the same on all processes.
 */
template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, T& out_value,
        int root);

/**
 * \overload
 */
template<typename T>
void
scatter(const communicator& comm, const T* in_values, T& out_value, int root);

/**
 * \overload
 */
template<typename T>
void scatter(const communicator& comm, T& out_value, int root);

/**
 * \overload
 */
template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, 
        T* out_values, int n, int root);

/**
 * \overload
 */
template<typename T>
void
scatter(const communicator& comm, const T* in_values, T* out_values, int n,
        int root);

/**
 * \overload
 */
template<typename T>
void scatter(const communicator& comm, T* out_values, int n, int root);

/**
 *  @brief Similar to boost::mpi::scatter with the difference that the number
 *  of values stored at the root process does not need to be a multiple of
 *  the communicator's size.
 *
 *    @param comm The communicator over which the scatter will occur.
 *
 *    @param in_values A vector or pointer to storage that will contain
 *    the values to send to each process, indexed by the process rank.
 *    For non-root processes, this parameter may be omitted. If it is
 *    still provided, however, it will be unchanged.
 *
 *    @param sizes A vector containing the number of elements each non-root
 *    process will receive.
 *
 *    @param displs A vector such that the i-th entry specifies the
 *    displacement (relative to @p in_values) from which to take the outgoing
 *    data to process i. Overloaded versions for which @p displs is omitted
 *    assume that the data is contiguous at the @p root process.
 *
 *    @param out_values The array of values received by each process.
 *
 *    @param out_size For each non-root process this will contain the size
 *    of @p out_values.
 *
 *    @param root The process ID number that will scatter the
 *    values. This value must be the same on all processes.
 */
template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values,
         const std::vector<int>& sizes, const std::vector<int>& displs,
         T* out_values, int out_size, int root);

/**
 * \overload
 */
template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         const std::vector<int>& sizes, const std::vector<int>& displs,
         T* out_values, int out_size, int root);

/**
 * \overload
 */
template<typename T>
void scatterv(const communicator& comm, T* out_values, int out_size, int root);

/**
 * \overload
 */
template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         const std::vector<int>& sizes, T* out_values, int root);

/**
 * \overload
 */
template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values,
         const std::vector<int>& sizes, T* out_values, int root);

/**
 *  @brief Combine the values stored by each process into a single
 *  value at the root.
 *
 *  @c reduce is a collective algorithm that combines the values
 *  stored by each process into a single value at the @c root. The
 *  values can be combined arbitrarily, specified via a function
 *  object. The type @c T of the values may be any type that is
 *  serializable or has an associated MPI data type. One can think of
 *  this operation as a @c gather to the @p root, followed by an @c
 *  std::accumulate() over the gathered values and using the operation
 *  @c op. 
 *
 *  When the type @c T has an associated MPI data type, this routine
 *  invokes @c MPI_Reduce to perform the reduction. If possible,
 *  built-in MPI operations will be used; otherwise, @c reduce() will
 *  create a custom MPI_Op for the call to MPI_Reduce.
 *
 *    @param comm The communicator over which the reduction will
 *    occur.
 *
 *    @param in_value The local value to be combined with the local
 *    values of every other process. For reducing arrays, @c in_values
 *    contains a pointer to the local values. In this case, @c n is
 *    the number of values that will be reduced. Reduction occurs
 *    independently for each of the @p n values referenced by @p
 *    in_values, e.g., calling reduce on an array of @p n values is
 *    like calling @c reduce @p n separate times, one for each
 *    location in @p in_values and @p out_values.
 *
 *    @param out_value Will receive the result of the reduction
 *    operation, but only for the @p root process. Non-root processes
 *    may omit if parameter; if they choose to supply the parameter,
 *    it will be unchanged. For reducing arrays, @c out_values
 *    contains a pointer to the storage for the output values.
 *
 *    @param op The binary operation that combines two values of type
 *    @c T into a third value of type @c T. For types @c T that has
 *    ssociated MPI data types, @c op will either be translated into
 *    an @c MPI_Op (via @c MPI_Op_create) or, if possible, mapped
 *    directly to a built-in MPI operation. See @c is_mpi_op in the @c
 *    operations.hpp header for more details on this mapping. For any
 *    non-built-in operation, commutativity will be determined by the
 *    @c is_commmutative trait (also in @c operations.hpp): users are
 *    encouraged to mark commutative operations as such, because it
 *    gives the implementation additional lattitude to optimize the
 *    reduction operation.
 *
 *    @param root The process ID number that will receive the final,
 *    combined value. This value must be the same on all processes.
 */
template<typename T, typename Op>
void
reduce(const communicator& comm, const T& in_value, T& out_value, Op op,
       int root);

/**
 * \overload
 */
template<typename T, typename Op>
void reduce(const communicator& comm, const T& in_value, Op op, int root);

/**
 * \overload
 */
template<typename T, typename Op>
void
reduce(const communicator& comm, const T* in_values, int n, T* out_values, 
       Op op, int root);

/**
 * \overload
 */
template<typename T, typename Op>
void 
reduce(const communicator& comm, const T* in_values, int n, Op op, int root);

/**
 *  @brief Compute a prefix reduction of values from all processes in
 *  the communicator.
 *
 *  @c scan is a collective algorithm that combines the values stored
 *  by each process with the values of all processes with a smaller
 *  rank. The values can be arbitrarily combined, specified via a
 *  function object @p op. The type @c T of the values may be any type
 *  that is serializable or has an associated MPI data type. One can
 *  think of this operation as a @c gather to some process, followed
 *  by an @c std::prefix_sum() over the gathered values using the
 *  operation @c op. The ith process returns the ith value emitted by
 *  @c std::prefix_sum().
 *
 *  When the type @c T has an associated MPI data type, this routine
 *  invokes @c MPI_Scan to perform the reduction. If possible,
 *  built-in MPI operations will be used; otherwise, @c scan() will
 *  create a custom @c MPI_Op for the call to MPI_Scan.
 *
 *    @param comm The communicator over which the prefix reduction
 *    will occur.
 *
 *    @param in_value The local value to be combined with the local
 *    values of other processes. For the array variant, the @c
 *    in_values parameter points to the @c n local values that will be
 *    combined.
 *
 *    @param out_value If provided, the ith process will receive the
 *    value @c op(in_value[0], op(in_value[1], op(..., in_value[i])
 *    ... )). For the array variant, @c out_values contains a pointer
 *    to storage for the @c n output values. The prefix reduction
 *    occurs independently for each of the @p n values referenced by
 *    @p in_values, e.g., calling scan on an array of @p n values is
 *    like calling @c scan @p n separate times, one for each location
 *    in @p in_values and @p out_values.
 *
 *    @param op The binary operation that combines two values of type
 *    @c T into a third value of type @c T. For types @c T that has
 *    ssociated MPI data types, @c op will either be translated into
 *    an @c MPI_Op (via @c MPI_Op_create) or, if possible, mapped
 *    directly to a built-in MPI operation. See @c is_mpi_op in the @c
 *    operations.hpp header for more details on this mapping. For any
 *    non-built-in operation, commutativity will be determined by the
 *    @c is_commmutative trait (also in @c operations.hpp).
 *
 *    @returns If no @p out_value parameter is provided, returns the
 *    result of prefix reduction.
 */
template<typename T, typename Op>
void
scan(const communicator& comm, const T& in_value, T& out_value, Op op);

/**
 * \overload
 */
template<typename T, typename Op>
T
scan(const communicator& comm, const T& in_value, Op op);

/**
 * \overload
 */
template<typename T, typename Op>
void
scan(const communicator& comm, const T* in_values, int n, T* out_values, Op op);

} } // end namespace boost::mpi
#endif // BOOST_MPI_COLLECTIVES_HPP

#ifndef BOOST_MPI_COLLECTIVES_FORWARD_ONLY
// Include implementations of each of the collectives
#  include <boost/mpi/collectives/all_gather.hpp>
#  include <boost/mpi/collectives/all_reduce.hpp>
#  include <boost/mpi/collectives/all_to_all.hpp>
#  include <boost/mpi/collectives/broadcast.hpp>
#  include <boost/mpi/collectives/gather.hpp>
#  include <boost/mpi/collectives/gatherv.hpp>
#  include <boost/mpi/collectives/scatter.hpp>
#  include <boost/mpi/collectives/scatterv.hpp>
#  include <boost/mpi/collectives/reduce.hpp>
#  include <boost/mpi/collectives/scan.hpp>
#endif


/* collectives.hpp
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
*/