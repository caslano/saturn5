// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_QUEUE_HPP
#define BOOST_GRAPH_DISTRIBUTED_QUEUE_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/parallel/process_group.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace boost { namespace graph { namespace distributed {

/// A unary predicate that always returns "true".
struct always_push
{
  template<typename T> bool operator()(const T&) const { return true; }
};



/** A distributed queue adaptor.
 *
 * Class template @c distributed_queue implements a distributed queue
 * across a process group. The distributed queue is an adaptor over an
 * existing (local) queue, which must model the @ref Buffer
 * concept. Each process stores a distinct copy of the local queue,
 * from which it draws or removes elements via the @ref pop and @ref
 * top members.
 *
 * The value type of the local queue must be a model of the @ref
 * GlobalDescriptor concept. The @ref push operation of the
 * distributed queue passes (via a message) the value to its owning
 * processor. Thus, the elements within a particular local queue are
 * guaranteed to have the process owning that local queue as an owner.
 *
 * Synchronization of distributed queues occurs in the @ref empty and
 * @ref size functions, which will only return "empty" values (true or
 * 0, respectively) when the entire distributed queue is empty. If the
 * local queue is empty but the distributed queue is not, the
 * operation will block until either condition changes. When the @ref
 * size function of a nonempty queue returns, it returns the size of
 * the local queue. These semantics were selected so that sequential
 * code that processes elements in the queue via the following idiom
 * can be parallelized via introduction of a distributed queue:
 *
 *   distributed_queue<...> Q;
 *   Q.push(x);
 *   while (!Q.empty()) {
 *     // do something, that may push a value onto Q
 *   }
 *
 * In the parallel version, the initial @ref push operation will place
 * the value @c x onto its owner's queue. All processes will
 * synchronize at the call to empty, and only the process owning @c x
 * will be allowed to execute the loop (@ref Q.empty() returns
 * false). This iteration may in turn push values onto other remote
 * queues, so when that process finishes execution of the loop body
 * and all processes synchronize again in @ref empty, more processes
 * may have nonempty local queues to execute. Once all local queues
 * are empty, @ref Q.empty() returns @c false for all processes.
 *
 * The distributed queue can receive messages at two different times:
 * during synchronization and when polling @ref empty. Messages are
 * always received during synchronization, to ensure that accurate
 * local queue sizes can be determines. However, whether @ref empty
 * should poll for messages is specified as an option to the
 * constructor. Polling may be desired when the order in which
 * elements in the queue are processed is not important, because it
 * permits fewer synchronization steps and less communication
 * overhead. However, when more strict ordering guarantees are
 * required, polling may be semantically incorrect. By disabling
 * polling, one ensures that parallel execution using the idiom above
 * will not process an element at a later "level" before an earlier
 * "level".
 *
 * The distributed queue nearly models the @ref Buffer
 * concept. However, the @ref push routine does not necessarily
 * increase the result of @c size() by one (although the size of the
 * global queue does increase by one).
 */
template<typename ProcessGroup, typename OwnerMap, typename Buffer,
         typename UnaryPredicate = always_push>
class distributed_queue
{
  typedef distributed_queue self_type;

  enum {
    /** Message indicating a remote push. The message contains a
     * single value x of type value_type that is to be pushed on the
     * receiver's queue.
     */
    msg_push,
    /** Push many elements at once. */
    msg_multipush
  };

 public:
  typedef ProcessGroup                     process_group_type;
  typedef Buffer                           buffer_type;
  typedef typename buffer_type::value_type value_type;
  typedef typename buffer_type::size_type  size_type;

  /** Construct a new distributed queue.
   *
   * Build a new distributed queue that communicates over the given @p
   * process_group, whose local queue is initialized via @p buffer and
   * which may or may not poll for messages.
   */
  explicit
  distributed_queue(const ProcessGroup& process_group,
                    const OwnerMap& owner,
                    const Buffer& buffer,
                    bool polling = false);

  /** Construct a new distributed queue.
   *
   * Build a new distributed queue that communicates over the given @p
   * process_group, whose local queue is initialized via @p buffer and
   * which may or may not poll for messages.
   */
  explicit
  distributed_queue(const ProcessGroup& process_group = ProcessGroup(),
                    const OwnerMap& owner = OwnerMap(),
                    const Buffer& buffer = Buffer(),
                    const UnaryPredicate& pred = UnaryPredicate(),
                    bool polling = false);

  /** Construct a new distributed queue.
   *
   * Build a new distributed queue that communicates over the given @p
   * process_group, whose local queue is default-initalized and which
   * may or may not poll for messages.
   */
  distributed_queue(const ProcessGroup& process_group, const OwnerMap& owner,
                    const UnaryPredicate& pred, bool polling = false);

  /** Virtual destructor required with virtual functions.
   *
   */
  virtual ~distributed_queue() {}

  /** Push an element onto the distributed queue.
   *
   * The element will be sent to its owner process to be added to that
   * process's local queue. If polling is enabled for this queue and
   * the owner process is the current process, the value will be
   * immediately pushed onto the local queue.
   *
   * Complexity: O(1) messages of size O(sizeof(value_type)) will be
   * transmitted.
   */
  void push(const value_type& x);

  /** Pop an element off the local queue.
   *
   * @p @c !empty()
   */
  void pop() { buffer.pop(); }

  /**
   * Return the element at the top of the local queue.
   *
   * @p @c !empty()
   */
  value_type& top() { return buffer.top(); }

  /**
   * \overload
   */
  const value_type& top() const { return buffer.top(); }

  /** Determine if the queue is empty.
   *
   * When the local queue is nonempty, returns @c true. If the local
   * queue is empty, synchronizes with all other processes in the
   * process group until either (1) the local queue is nonempty
   * (returns @c true) (2) the entire distributed queue is empty
   * (returns @c false).
   */
  bool empty() const;

  /** Determine the size of the local queue.
   *
   * The behavior of this routine is equivalent to the behavior of
   * @ref empty, except that when @ref empty returns true this
   * function returns the size of the local queue and when @ref empty
   * returns false this function returns zero.
   */
  size_type size() const;

  // private:
  /** Synchronize the distributed queue and determine if all queues
   * are empty.
   *
   * \returns \c true when all local queues are empty, or false if at least
   * one of the local queues is nonempty.
   * Defined as virtual for derived classes like depth_limited_distributed_queue.
   */
  virtual bool do_synchronize() const;

 private:
  // Setup triggers
  void setup_triggers();

  // Message handlers
  void 
  handle_push(int source, int tag, const value_type& value, 
              trigger_receive_context);

  void 
  handle_multipush(int source, int tag, const std::vector<value_type>& values, 
                   trigger_receive_context);

  mutable ProcessGroup process_group;
  OwnerMap owner;
  mutable Buffer buffer;
  UnaryPredicate pred;
  bool polling;

  typedef std::vector<value_type> outgoing_buffer_t;
  typedef std::vector<outgoing_buffer_t> outgoing_buffers_t;
  shared_ptr<outgoing_buffers_t> outgoing_buffers;
};

/// Helper macro containing the normal names for the template
/// parameters to distributed_queue.
#define BOOST_DISTRIBUTED_QUEUE_PARMS                           \
  typename ProcessGroup, typename OwnerMap, typename Buffer,    \
  typename UnaryPredicate

/// Helper macro containing the normal template-id for
/// distributed_queue.
#define BOOST_DISTRIBUTED_QUEUE_TYPE                                    \
  distributed_queue<ProcessGroup, OwnerMap, Buffer, UnaryPredicate>

/** Synchronize all processes involved with the given distributed queue.
 *
 * This function will synchronize all of the local queues for a given
 * distributed queue, by ensuring that no additional messages are in
 * transit. It is rarely required by the user, because most
 * synchronization of distributed queues occurs via the @c empty or @c
 * size methods.
 */
template<BOOST_DISTRIBUTED_QUEUE_PARMS>
inline void
synchronize(const BOOST_DISTRIBUTED_QUEUE_TYPE& Q)
{ Q.do_synchronize(); }

/// Construct a new distributed queue.
template<typename ProcessGroup, typename OwnerMap, typename Buffer>
inline distributed_queue<ProcessGroup, OwnerMap, Buffer>
make_distributed_queue(const ProcessGroup& process_group,
                       const OwnerMap& owner,
                       const Buffer& buffer,
                       bool polling = false)
{
  typedef distributed_queue<ProcessGroup, OwnerMap, Buffer> result_type;
  return result_type(process_group, owner, buffer, polling);
}

} } } // end namespace boost::graph::distributed

#include <boost/graph/distributed/detail/queue.ipp>

#undef BOOST_DISTRIBUTED_QUEUE_TYPE
#undef BOOST_DISTRIBUTED_QUEUE_PARMS

#endif // BOOST_GRAPH_DISTRIBUTED_QUEUE_HPP

/* queue.hpp
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
*/