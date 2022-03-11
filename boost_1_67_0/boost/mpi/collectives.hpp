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
nHnrvOdVsos3bWjTTsHq9eez4b/2Ldx0UOorhtplDYnZmz5DvPd0MhUHDMXrHJkHxo4IvH11+dsCB0PaP3upmOaAKkQ8Kw3GjYNbJ/d+yW2YDgmGa6Y7PtbF4Wz5Z11QTItdR9sM7qZeVU5Aaum6N6Mp6A3shqqVlH149wlSqEEkDCC7yRMYSOHasDvwmiRivZcI75l7F0K697LTEHFdlrzLm3U4PYFzV2hRvwGDoXsnLbC/I3nHLPDCCF5RzGpPi52qG6mFq/EpUPZ+PbN+zhMeBXcHt+L50jjpinTTU119MBQVemf1VRLbwBSJu8XaU9/JGFj/BNof8NsRd3/1IQLL7MXs6A+MYwx4lya1UkBwbnc9Bjx9Ij2V5UAHZ0cYOu95+Hm1HrUp+8b08uOXFxAlJpDB/GuT5J3IPDTaE/R5W1GP+1IpHDv9VmTPmNN+W3Y/xgAALP/TGhKOndWMvZc26cnpNC6Q9J5T5PYd+BYPKl8mmSb6h4sdhK1nOQH0iSnDbnZr7N6Me9x2e/BXwYyhP5+YA8m1tiT5kGwAaDYrr7WhDGf9YDV+0OLDMt7hq+1H1/BT8vLrLxh+1DUpEOHvIvcKe4Xk9oHvUxHOXQzRC5iwe12OCNGJ7uzBJ+nIZxmY7OQcEaGQsuKpS1+aX4MVDG5DYaO4GEhYTW+wOMe+7+BA+MRqdh36jn7nAN+a50kAFtrD6NWNeOvhjCAKbPlPnijGeKbCggbed/QTUQTKuhH/rDXEnJ/3ewD/POfRjdzpoApbfqimF0jY50fpDmfIuTH6n7je2K8AhXMvUIwNXfVWnnuh/kFduJDoI8G4rOTnl8IbB5hnvzfvs9Pa9OwcIKkL+8fGHdN/ZOs60xXrHbgBcHOhelAtxwbAvZOV07MF5dI8+mTmsj3+sVFPBi2kcb03qcfy/ioQl3/+6ceI8iqhx4y0767zQY4ByjMASJrT/GjwcwNLhEu85FqVHrJuVgxhJxg6c0uI+kRL0Xw9+e2K3hf1rfg75MSL8QCEYH9mMfMcuEPI20R0E8MZfZ0k9NTrQpOnqcMj9X6UFaX1e4EFfVjjmxKS8H7X8GL1NpbkVFwXTZkamqGHB/XeKidujWzykKCE/1fJ/XvGNfo9F3uBS5T/5P8/cT/leyg4bX/UziK5DtrBWBD5l1Zyfs/sevSuPNBquO8jtpKm+JaUztEH5Qjy+/EeYeuQisAHM2+vAzbv7gpFxpF585z6nsjPLRG5j73MJFncO+yx0vkuHtQGVtLBuNpm8cwr6QC5eo93ihi5L8IWT3H0byZCJxw+IMTb9XTJ63mxWrrLYIME86d3ldvX1OBtipR0p81naTbOmjdo2UK0zfY+43k5TBKCZf4FNMxMf4VQO87lH3dMt1VWDJgHC+eGtRrKAUtufTrR90SrIZwx2/vquNcLY//zGRDcitz8H5N2ARZF1DYOH0RBpEREulVESrpBWkRAREG6S7p7Vwnp7u5QupulG5ZuWHrppRfYXfZbn/d93v93Xf7cmWHmzDn3fe6ZsxfkWvODyD5I3yUcbypyNm60ES0gAWn7cFt6a0MixKOqxrp1hJAL4qM1COf6T1Vj172Si09jHbyrw6OmqrHnfm1yU4MA8WIB2gM4sDr7E+z36oiuCi3eMyo5UWXQoMg6usSn0AZ8I/4RRUtbCCCO/iLFnX62rj5pqC044YsTO5oQ+7V7Xal3dV12/7LjK96dGKay9Xsl1v9gCjs4RChgOUTIf76QBuEBi34Gh/Fx9SLgYqoz4o63FSxZl2l1krEraXWAY4/3yLz8aIf3V6Gf3T3ysS6myOBw6V5W+X7WmA5smKKAH5U6ktFQtX0TNRRU1WT5PQLYMP/unorjcud4KaapTVnoJZeDuezmOZfQBraQCfzy0KSumsW98ZMAAmFAkKgoWfalIPHgGO1i5vH9jpYyEAhMfvGi/MYNibrAvOLOQK3jyVYgACWANvud3ED3ltL4n8xzxx9SJmeV8wZ9twc6SBrBKV/cah1fThTKmmUXFhZSSbedZKMoCVwF8Tjd1tl/0pO0oyFLVkP0x/aH35LPGDwdsSyiHAh/1EvTpaXGE0VBvAngRGlEbPXJbEqfLv7beLaJWdZgNuSZMDl0Edzy3Hj5b1VDq64VI1lY8gCFfniJRofeQyzuUbV13L/93h7ZVQGnVjo+LyV3dniI3wEXIDb2sJhrroXGTkmGaw3FcDW2I3Zj2E8UNF4xNPoBQmZBzBjoeD4IZ72kp2tuf9Nz4aH9oNiMeABWKRI6sHpe7Q5UYcm6OsiO/Pb2tEwNfUT9Cp6Iq5xjCCucO9ALgfYOhero83eQiT3rbdwWY35/FXazu37WSW6syTTaosQS9MchO4A8dBnqKL957dXM7ISos/2h5AmocdPYPNUQekUMaWBzutm3aOtiquG0IasHbs8f8C923HXVhiK6KIqpBqa1gIc0V5I/GWlVPyJAK3jvPgK2o+IYvPK3Fe+LYtc8GlEEV3DAKFAj8vBCZtP91AvzhgXjgc3aAppwfK2YxcAufOVqXa2UhphlDCDk7Mmm/WlLaP/5MEPSTr0d4xVCy2DoV/gHV6EXG7weXkKkxFZkJFGcXziXzmyvJReXth+9ltlCfILhHNSSEM8UfAu74SD5al09TLqLF1/K0FzmRd3+VpLDT20Sz7wwp38whz+52uh00U484liHcva5wsEH409TwTyp3ZRiXygbPCnF6t75Pu+fie0enAjmiexusih4x7tlPPPDeGbk3cN0poCYduqPV4Oeayn0HSYPyMpJiksk+bt3+Lb2YWTcR3EwZQf6PxIFWl8QwYi+rcirMSXxx5LpnlfWXeEhHv7FT+HtzHfJJv/WPGX86L0XJ8ohwZg1a2WQD4XTCNAYHe8p4cnmRHPD10tQ6aVeVox5e2vpjs0hdhJDESwe5pv3gxqpTVJ/Sz6JS94o4oPcEk6XFfBBqxEeXzdhodEht3aSzru/nguCxpbDF3F2DFnKLIonAE88GyvufxY/5X4Am51lOHXZ2kMRnErqo7ClFNqo2wy1gHXnrGuPKw4OojXvezlB3fcDwqZ+48syV9i+j87cQbbcBA0pfmrtjyAMSSHIJz07ZU4coCWSsBvhIbTvd6JX04if6/K9dJhnBWe5FXdvJuZhsdylHNKK+Zok1qnfu6pzF5rsn/yscmpKrY1aj+kEJ1uxjaotw5PF8/VZ/Lr9v3JSuoSLOZKc5SQBNpsdHhtIt2koA+OqJb8+g2G+Ouh5rJkfJvUel9spb17Pdbxy8iGwV1pZE/3k6eoLuEdIFZ81d26HRC/8rDlaxAvwyNAG2Kp77su+UB5jwTnwH3ykDvnSvkHN08bxJXONxCQAWi2PA8enudqYeMTzqXSE/53gkxO8Jrz1rpOdNZIZv6Tw2L0PkGPCDLkgwGn3I3Glc66DK53Mkbochj1NNGolKIRyoI3kmksLDig6Tg0h/ZEhaPr4b5eUXucT8VdvWaiUBgyrPCkeZR7slliPsUiLODxdcKadvcp5w+V2FFLM2LumtvRxhwQvuH/K09kMJI+yvzHZLjnxZRZbxLzVU6stUD4nc707mY0CTl5QBxW9tUfr5iYhaYxJ7DDJ9p4vgq/Xn4FnbMp6SHeQ0rTgJ6tegGT5Y4aAN7jiUj1Qj1RZ0p0HzPe/rvnjJtE2sQkhu3ny3119m5UJSTalYK8bwwzDW7RqNfobnwi15knWd7FCXTc0RLPsoyWPe6bHPL3psiqms7xZ2E8ed2TWlfc5r3diF77/ifODdDBfMREUvLjJMyMFDLq3orlSXK8dmIBQwOjCkFONKh0OUOrn1/VmMH9UTNB4+INK1hNcGPMJtgOjAaagPQV3aSIxLxG3XoJ1AMmZwmkk9fyTotG8EwYh2ltzXf7hX45zh0mDkSk+fR1qlne800n7Cpm9dYn7X4vsPhXzZfa5Ck67F7mkjJsvdV3KFCW/0x+si99nLgpP5TJe6nNlm34yvfOpNXWt6xJr2rgIL5XeAtPG0uzO3bn50rDr22nBounUcRPR5RJFEHcql3wULOKmbtlGAja4I3sks5MXLQ8c1dxUeTyknfQ1qWD9o2k9wuEsix8A6OXsv6mvvrnmK+eVMJoJu+grfEGq99fE0KUzr8K4q29qOTZu/f5D7BtCR5WAplXqALKKOUKWcym/jlf3YSVCRJ7aL/PVAjOM8Ji9Z8s6xFPGLZbGXYmnmz9BeTLBrtjTF6kGnXUB+0F8Kgfh3OYzCOrGVf2XejricPvWVjmEWos/3sFYdqNC1Cub6Jgh8k0pzIJJs3K2dfQgwrekyWJ4OFHvee3HqvwK/UJqUT/he0WrY+KZib/ZhL31sjOVE03ZJAqXO0CGPnRu7LP19lpdYb+DPMuTWojykjvzsyzf3pZ7URg/TEJpjYQ5E3yf77bscOo4fHe25mRQ/E0c+VmqJ6Sfn3otovRJpekJWssTSNvuO+PzZC1EL7X6I+uTfVd7m7JFuUrJWbjHp62OiYlWfQeqc/jbEzy74Zau7+e7Qb6z8ABBc8NE4GQpz9UW/vSOUMoMvMtJa9Lw60rOIbd4UxksO2v6iqITc2Sm5maGb7XTlWXaJ8XeoiXIWmq6/FMjz+q4a8w+cRE3X7l+ZjFDZQomienWYtMin6C8mQOYmYCZAJYtYfs6RU4Qzb39+hq0yJAn6zTqU+knQwud1jAlKQYj0dmS9I/1F3z6m0LWexQ6AY4KvFEEtFLRUIXLZPjt1pmbrIOwk3CFk9iXvfDl+7fTOH4a6XUMRhs2WhT7UO5Puqmq5kv9rqLT2p8s+ewsRYP39YouUsZBQwXtyV98DI15mdK4VxJGvRfPG2RbNeVs7g+iZY9jG5UdFZXPbt057J0mCmISuz/rv6Tv8/YvyTdDJj0YIz9xbe/K7yfl8k6MBkgO10VjBnCYam/UErsv8UmIb7W7Lntfs2g5xd7Su7Mk3VEjvKRabC2a/g1tu2hQMhgYrSxMbwWP5aAwjXPXVfLtREzS3LPjte19Y7m7wp/mKlJO1Uzhslwaqwvef1LEnlph4i02PfsJZkQNVwzs+GyGnhn2TFcXOn4qMSDrgZlBgLPscRLDhpWrCssMLWQFuj997qeLN6xsFnBYb5h93SorpiIM41AtCxwj2fcDub8w+JeRaD6/uH3VIjWe1TFX7mm/T/B/JdLpmrIvXRSc2jFa517/qwNk9v8vvv+XN1fJ6UefwJbe2NPERRS87YH7MkWZnyh49Edd//WePaXC7D8pPUydUzUBVd/3ePosxdtkJJ1fnKaTuRy3XU4YgGiBrdqe7Z8Q1WuLjMdabZlc9CUU47TR4n9XoYUKPcqkfrZKAwSvIUJHLtrDFWwjmmnVgKwLywbAa3s2Ml8k+YoHmFd5kbD6vt9r8seecn96hkv96bRp7bOj09db2q5mnGEotRbrt1npwh2aA4AV0FX7wm+jSyttP5S5aPb+gyIoX/tPa7xpYZjA5UQ/nEXLp4M9c5MaosY2ryo1Cyu2wutUlXA7Gz57e1kFR4VsoMbM+28uMRGKnJaUFXIziNgbhxO2I5CpISfi4Il9iq1fVlCP32uvIi9EZR3i+m8zctsLnOgt9+SnhIF8l/zWGY1US++poTa/NWP7vZJzhQwPQg8PgrW9mAClBjHXwvoXwOVWtHD28OXZFiuRikx8onzcSzGloJjEssSXJOxmAtqLt3WmabGzBdrsuXDZuSeHLK+H/srL/tXWFlOJn7kbrHwJ0owL8Z1se1X2pFS7A8zH1y/MEH2QDQNCvMQNTlxWpSoQLZh/YBFYKlxkU9dleOfULu3sm+UOGzQKfQ83zNIOiJs3Anx26dmHISUN90u5wQdoQ4glIcSSqpLXqYfKp7tRqz+9Ts9DgesESI/oOETFW0J4vV4Dn8Gid9WGCN6im/fFbzXuDgbDEEzMjWGDG8uMW6VztuKmDjoFEi9iBxS3lUi9PspxeSUa9R16NSYH3FQTpY+PUnSovVvbOfL+DSOJaBRhD4YRRAj9+8CLmJfEfOBEaP3bQ4czpGtyJbcdVG6iHOXGwwdvSZu3Z5XJj6MHl5nPo0IyMgAVtB10bJIVB8GWRwSQ38+l3DW8OvijL0kgHs8deI9XLsAU0UAgINr33Wja50mPVzfpGvTiHh2nfjJnTh5A15ZuRMCmvsmO8xDC/61BNIszOiTDu4IWBBgcgGZAuuGoXhsSbimGbYV+7pBBL1IRXzG1NqPhxYvp5mOyUpjmWTC8ptLvvKE9yv/ojow7JYV/z386XUuLOP1j48paTb6HsmG7xtk9N3N2yGDfv66LkMPQzM4mchUvYuOZnctD9FiZ56MHiVic4SG0HXav1nYwr6yztFivrIvppQCIGyAt0+vk1lra4hL5/PpNy23ARWb2tcIWzxtxiOXxm0bLiebjWubzMMy1nC8NTsP1d+bzP1dINOtVXH3eBvwnHVsszqpyxJAKUkOBZnFId6N1L8Hwzmwiq3k77XOhDKddxP4rGLikCRAAJoPBvNF9i416GaEe1+tWbcoGMWcnCGi4x811pGdyHXh8IZ2s2lLzXybf9yHgkN/zaPIdONkG4sHmo9brZENuZpSl/PYiqYgQM1RxuzukjZ+ZO3yQnfk8LaSNi9khYlCX+bwhRO9c3LnPN3JQibTZWM7+RayY4vap19rNX54dOEkAy7E2qQg3M3fYvzy/+5/LnW/qSlHfOzo2psvO/KUSR15F52m2gUIG9f8TM8lMKobGGvHsMJbjV9E6mhFAOdXRsAxIT/FrREVFm+3USNdREvgRGXrHzDC/ZHYjb9ovXBSVvx3OYgnUr7YfJ9zyW2vyNrnKKIsjkK03KMwWH6/Tm6nde9YzTM/M5iXKa+CjcwvT6i5m2Jr2SBp5BRbTRKJ6vsKF/KRu88QBuSs7ZRnCkStFegb6XkeGBsTnhp4VR75noDWpr2gPL8jtbfX2ZEcYFB6SQR5by3J+GiLOyzzAfL4QIi7JrBY2qMGMSU4WaSwmbnGKPW93ZeVUIwZnmZ2/yBFnZ4cJUZ2bayOhrplk95XKmShd6Cp0eA493DgyDzS5OmXjvJ1Vjy7wGLlgb4Ux3dZbWvODPmZ1hFXqG2RBNi5Uz5yUwUhU2eVk0RNQdOkFIu6qvezoAnYwbNy3GD3oQq24TJO9vCa+tIbMuBYSQ0u2gXzRE/sMd+IzqTYfh2TVXSTFryWyo7uhlZvfDugktwyH8tUmD3VLWYt80ZB550gONEJnyPRLMEP5Kby+qllLfU53oOPi188pxeS3gI7oQToWZ2jIigCzR/SgBItzdkjGs1iE4vZMSMaLWL7xxJEOQ3WvzzIKN4Mqk6d00PvuwrL2uOtT0uS8hA8++/nU5DAKBjHwHfInlGeX35cDFoxE1W+rh4SdhWNmNGbC652/ke27Ch/sASfy+XMubsCln/F1W+KGnSBeniNKpiprtFbQLCyHVLEIue2EkBUp5mKF7bqQDJ5z8bOKb5jvexASGwXNBZJXhqVrid+MpQLH2sO+EIAspWxDF2o5mWEhg60s55j1kmuFeLGOsef9p0tYTZDleLYYRNgHxXH7w7XPU3FbklTkFTM8evAPqQgns6XcdhepCDuzpeL2BqnXdslFGWS+HNh550b/zRj1sWPXb7aHfI7b9uQbf+t663zlEeITHPnzVlAzo3Jbt0mLE7V75EujvGtzL3GRCPjWsImybdY7X52+gbnTS+mfc07flONFZwL4kILWvqD82USKKpvlZL6AqcqofgISa67bFqvMRsFMLoQDazcJJ6yDCqDBfz9ofBzZky+rGJ2I/phzWZqLCSnzeUSIODszOGqweeccjb4FnvKdf1WoOpWi6hL7Hk0n7P/e7xm18cV+hBGbc2wAZU1MWNZeiNmMArmv3Wjx93CZbRPe34yP9Cef1HZ7IWntYqi+trzl+yBjWidNUmBC+dqoUnIDbC79VMw6ilraYuLh8QTNPuWvjJw6yHU8VRd2mQy2QZftp77vhH1Yroq6/LI8f/3SSWcUXWZee2gUmb7pZ8Hz+h4W+UaG5++LcHKdXL47RvJFymC2wT5n2z7ph8jK0KK9kKy96K4SJ3GWD+87fwegxx+7m0ok5T8liA2nSvlp/EFezVWGhl/a7mXejZyC43NENQ5N9QOvlEjaiL6nl7IedfK8P1iYaMFZx9+DC78HaqdETA4qiN7lionmmS9EVypGDeHbymGfxwScUf76eilvWSeDM/P+FS3q9+pCmMKAsouFa+aokXPmVL3qwjedZKSbwgRxOKimYTiXMhI/JUj+e1j9m262l5OLT8cmcagoQ6kGCZRb+o3e3eUSpOUz/d1cV+fpEn1uIllk8vK3EZZ3jkRaDq4qcgS5EFFY0helt+Ma0c94KUfD3y198fULvQQzSRUuzIjHoPMhoSLulwnysUksAcdNR4UqPN1T4hdGT35vYl8qWNZJ8x4wYQcTa/OVyTMZdDK7PzwacxKnlj3D8s4jP9iYSZ6juQrj1fu8TXXOQ6HBg7v4QVHKVUHZdseS6E6LjSa+dHNCusGUzlsUj7DTiHDg+6d+jjZ/mTLZXx3NKWGr43R9JXMTzYEZv+2tAsxm5B5EAbo0y7qfbTPhmcYEPXftirT6+VfY66cdZnaM9n2N6PpckE8imvfqIPcZce+x6bbx636TN1OTeHSTtETqRH2bnk+Xq+lH1EP0PikQan+Qd3CV1X2Zj5gv9Nl6Ah3Dc2LHNeG3l/5G2Jnp+Vhi8qnQljGhAvmlAsuMXAk37TwlRT512uaPuvd0ev7eVtqCJ2k1TsBvc++Z7XuwV35qmm9VcNLA7VKj7G/Yfq/TrRB5KFe7mbs4dB1/D2H2jYjyJKncfH4+4jvMdQHL3gvre/Oe+iDvmQF3ba2bdtnbxFtHaW0/Uy/+oqOW+s2p0fWnz+J5A2hi9Vj4hLUl+L7/Jt0Lvn5TkURlqyjpHBP0usS/PdkM92ISH/taa4wwyVQSN18ojtRotS+164FZDkHa+lcTiyqaZs9fnNbDm+G8AeUhsYd6MVR18m+XpxJMY6Nd7UZuasaceNI0hwlxjSWvWW5lLkxJJbStgiO/8QakUv7sX9BIVdn7pIXzPH3r8bXJo11T3tf703SzVRzSyIkXivvg1qpL2o5Zev1wrmsH9pemMOg5HYyRJGCC7HiS8kodB18=
*/