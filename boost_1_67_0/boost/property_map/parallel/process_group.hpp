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
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
*/