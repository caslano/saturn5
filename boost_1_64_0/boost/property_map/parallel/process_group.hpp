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
Wg7EvcxlOemZFpNR9n+zHNmaHFNHH2dealyWYUrPWZpu/Y9yUMGQIMZR+Wpc4ui5tiICZlrsS4xq2Tp3mSqd34kliaP3NVuMy7KyMnPMucZVfnTGIxJhW+V+v3utB9PhCPVW6dzkCHm88c6aJuJrofy5qOpv2DZFJul0+O5B5aGPRijfdETi3x6XohT8OFxxKdjMyp3t0dBE6hRsVt3d3xBkiY2fR20TQn8f8i+3jHcVhBZU/vJgZYkq//R7EtYG3R5nQtLcpLmJpQkb/fMSkxbcqatKnZ/gh0qqM6FS9agOv6rtgdWAX9ttrlrlu7eNy6ZTShyhayP6UMxJjCrWKaZVRR+KmiW1DyvjqXt+aN+RvDJ+tO5OdWMBO1htLsgrL/f4C2wr8c+k5LlJiXPnpYRqPO61BRCswK8GQtdI5pavXf9fHavJHbrmc3NEbntxGOTelzHldWVke4sy/gFlZOsKU0Z061kdf0/mzOsvcMjCNCTavWz67nw1LgtXPkS9w6F33FenfF5qoxRjsoJNnsmPUbD94Qf3RO8Rc6pCnv4/V3tsy5rOrZnhSgZ11kPnH29KeL8yskUrgfHKyJZokL8HK27tuXc6b3KXPT2vyF3mDtwbzUe1P1r/RHO4UhMm+hug/8ZzXxxWRrZHlEG9MrIN6GXOh6/ewznfqFaGllf3Rnk2/iZ7H3h3uPKoTnR/ALo7Nuw/KLVvDf3N0MjW/qDoHnPx3uruLt18z1Rn23f0bp8ZrrxGm38Qes+3fO1JZWSbqAy/S8Emf1c0XcH2xh7dPdM74L83Ogf8Y/SNmhSu/IX6RkDf6MUV31RGtknKjSeUkc0zQfT1vX4P9fVX+u6NwtLwaNtWosOVCL3oHAmdPzvxa9/XMhVXhDKyDRrEtl330q/9vg2OknukNZserXcx/vA1h3P9EPRW1j/+c6l9m2L5mIJNnmV/PBTXeu/lXPtU1Xmv9NaaxqbZ+I4w5SnqPQ56e47GviS1k5XmGGVk8z0s8z0wfC/n2+v2qvdIb2l6bM6yPUwJUu/x0HuZb+VtqZ2iVEVwBB6Q+bbf0/lW/f4i972acWn8Tbon1oUpDp6/JkD38EezNkntY0pitDKypUbK37EPDyXcwzkvCty7Sb/T9t3zNhKWq9T7YeidX3VipjKyvV0ZeFAZ2YoNMuftPfdyzov85SUb1HuUsWmtj9X9adg7dX8LdJ/8x2cY16cqO53KyLY/EeupkN3/Kfae6q5WblQr75nud1q/G9v/oFNO09ejQue0tPYvKSPbNGWoQsEmf9M2I6T7jp3/le4j73pq1vG3b7Xf3OE7rb7L38ZZwXfD1vLdbJ9RpP6tfOeNn+/EfouUHTt00k4x33U4h+9OWsl34dr5jpL3hEs7S6W8/T3+lkOytL9lk3wf/JVO+jnJd5/OkPKV70r/6gfD+BuE/G2LPJ20c53vGrwgpeEJ/obPp/nu3T4p3Qeph88g8vxAJ/pqv2mwXepPfF32dyTw3SvnpVSXs/+NOtHzEN8Ja9WLPH+S0lEv+0efkvoElluWcxx+K6W3je9Y/Eg430XDd9tXU4+H+c6pbL7L/FGpv/kDvnvqN4r0O5fvNEvnu1nfK8cvKtHxXTJ6aTegk+MHpdzcz99u/BPnq0H2S3FLmfRXvkvnPI9/F+dNz3cjDSsy/zF6Kbuknei/KSLPLr77rkHKc09o74ZWZBwn8p3a6VJW8LdXz8fTHqP0ctx3+O6i3XyHUpeUW3+tiD3TPs4ulnLCBxXRe0COyy6SdoPfoT3tk/0MJ6T+5iK+c/zX8r37p/L9iRraXTXta1BK9Vs60e/zUn9qo0HqF1HPGzqRY6WU2e+Seu9yKa8=
*/