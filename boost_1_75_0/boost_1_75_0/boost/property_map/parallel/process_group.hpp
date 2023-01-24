// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_PROPERTY_MAP_PARALLEL_PROCESS_GROUP_HPP
#define BOOST_PROPERTY_MAP_PARALLEL_PROCESS_GROUP_HPP

#include <cstdlib>
#include <utility>

namespace boost { namespace parallel {

/**
 * A special type used as a flag to a process group constructor that
 * indicates that the copy of a process group will represent a new
 * distributed data structure.
 */
struct attach_distributed_object { };

/**
 * Describes the context in which a trigger is being invoked to
 * receive a message.
 */
enum trigger_receive_context {
  /// No trigger is active at this time.
  trc_none,
  /// The trigger is being invoked during synchronization, at the end
  /// of a superstep.
  trc_in_synchronization,
  /// The trigger is being invoked as an "early" receive of a message
  /// that was sent through the normal "send" operations to be
  /// received by the end of the superstep, but the process group sent
  /// the message earlier to clear its buffers.
  trc_early_receive,
  /// The trigger is being invoked for an out-of-band message, which
  /// must be handled immediately.
  trc_out_of_band,
  /// The trigger is being invoked for an out-of-band message, which
  /// must be handled immediately and has alredy been received by 
  /// an MPI_IRecv call.
  trc_irecv_out_of_band  
};

// Process group tags
struct process_group_tag {};
struct linear_process_group_tag : virtual process_group_tag {};
struct messaging_process_group_tag : virtual process_group_tag {};
struct immediate_process_group_tag : virtual messaging_process_group_tag {};
struct bsp_process_group_tag : virtual messaging_process_group_tag {};
struct batch_process_group_tag : virtual messaging_process_group_tag {};
struct locking_process_group_tag : virtual process_group_tag {};
struct spawning_process_group_tag : virtual process_group_tag {};

struct process_group_archetype
{
  typedef int process_id_type;
};

void wait(process_group_archetype&);
void synchronize(process_group_archetype&);
int process_id(const process_group_archetype&);
int num_processes(const process_group_archetype&);

template<typename T> void send(process_group_archetype&, int, int, const T&);

template<typename T>
process_group_archetype::process_id_type
receive(const process_group_archetype& pg,
        process_group_archetype::process_id_type source, int tag, T& value);

template<typename T>
std::pair<process_group_archetype::process_id_type, std::size_t>
receive(const process_group_archetype& pg, int tag, T values[], std::size_t n);

template<typename T>
std::pair<process_group_archetype::process_id_type, std::size_t>
receive(const process_group_archetype& pg,
        process_group_archetype::process_id_type source, int tag, T values[],
        std::size_t n);

} } // end namespace boost::parallel

namespace boost { namespace graph { namespace distributed {
  using boost::parallel::trigger_receive_context;
  using boost::parallel::trc_early_receive;
  using boost::parallel::trc_out_of_band;
  using boost::parallel::trc_irecv_out_of_band;
  using boost::parallel::trc_in_synchronization;
  using boost::parallel::trc_none;
  using boost::parallel::attach_distributed_object;
} } } // end namespace boost::graph::distributed

#endif // BOOST_PROPERTY_MAP_PARALLEL_PROCESS_GROUP_HPP

/* process_group.hpp
uLim5BbtjC8Gk8t6GO/7SBBabqBnONqDT3wpkEp3SPWVBSIUKI1MzT2TGe6QQmLwwuGpj9chDk9IjPSjLx++eQo23TKlCKUp1Ln9VANJaVGsQSrKXYEaGfnsGHdAI6HlfzOENYSsvutY21AIoj0X2dqTxe8ovTDjlDk4Zehe4MQbTHjTfGq28tsvMHdhH3oJuDfIcuYu1EcnzctG4eW232IvivfFKJD5xrKgbGgQMzoVf9AuwATWMoLMMBKxNlRvnbTdQfS7TL0Rqm5B1d3buStuVBga4rdR4eVgbaPCCTRcXeTSbVS4CX2G+VSLRUotbrlhYXuwUKq1qvsnNrUzjFurtmEWQV9fbQ5rimawXKZNC0PDuMG6FEpzWPdQx9Mq0iTaYI2arlGwsaIVDk5MtZotya6ziiURmRp9fxYXdq5i2anYbVuurDlhhkUe9Q3ulAdA9jv734AsCzECOc8fyJ0hZiCHBfkB2TtIA/KLED8gGwRVHcgx1ziQ91/C1p9i1Y3/WRmQ8yoPZBcrB/IeKwEZdi0QkJmWKgC5OtgMpPVXI5B/nTECScD9swxiE6AfN5SO3JwCF+k4T4e9FRGZDi7Ksx/h3itZ4Q5fITGUvlIVbhZ9h1+lMs4oldL2IBt2hnk9Gdj6SdfAXxkJ1maKss7FNr363z7c0rH0NqjBMZQe5CdZeAtQ2QkNv0eRqWhl/6wVpwWcqYxGyH+m
*/