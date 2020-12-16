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
1dlH3+dtnni+8kvg11LHBb54c+L7w1Lz3dXXPOOB1tulM1fd7X4p+9Go+zB67OCJoyaO1/O3hbWljEt8pfTaxlf6ISnjHl9Zc90/Phw71703sXsl/ZO+eHPdh/3CXPfJsJLUaZqvjLnuRldfUdJc7StDp278GuyQezQjNE5aJxE64Nngchg6z27is6WMy30unbvqqmtK/ARfWfPWr4fx5q1XhuOlbRah+fcwl2qrsduoJn202Io3Z/3AYTNn3dhLpMh1pHmm2tepL47oZ/d1z3ZPgLQRXTttVSRFklaeA03bj7RtbNLGnDva1/506etJxqbid3I8Ke4512IzlfsrfKFfYvbNXHl08u458AQz793See8PIbPZ9+icdq+SIDpyv+rJAyqvRZ5E2Q/nT2I/mZCi5ane3ujRzZx8tfWa8yv06bd/7ejTKxy2XP64/Y4s1+jTD7nnsx895J7Pvv+QWz+/65BbP//+Ibd+/s1Dbv388kNu/fz8Q279/FxHZq7jBkdm6nz1Ibd+vsjIWspxo8Ox+vlTv47Vz/Nudenn15ehn99axnz2/XF08f3jzF8fFmf++u4489evj56/rmm7GX29ebZkXvvwI9Zv4u/73zXv/N+lx4+n5+0l+v1nv3/ykxt7fZkxKTftxxFHz931/6ff/0/T1x/rPPu/Na+9t1e/nfW7vSU7w9jvpD9nn6t681awDmwPG8EucDrsCm+B3eBT8CLVm18M18H+cCscALfBQXAPLIafwqHwSzgMHoYjoJc6jISJcDTMgGNgJiyBx8NLYB04CTZUffop8HLYVPXpLeGV8FzVp7eNM7+9G5wBe8CZsLfqz/vBWXAS7AqvgL3hdbAPvAH2hTfDm+Dt8GY4D/aAT8Oe8Dl4K3xL9e3vwTvgPngn/AnOg15PWL9eEc6H56g+/UK4EA6GD8NRcBG8FC6BU1VvPhcuhffDZ+BC+Hv4HHwOroTL4Sr4MnwXvgJ3qr79IHwVfg9fg4le9E0wDf4BZsA3YSZcDRvofPRT4TvwTLgWdtZ56X3hOlgE18Mhqp8vgZvgPaqnX6x6+d/Db+Bq+C1cA7fD9+AOuBt+CPfCnfAL1d//BHfDBJ2nnqh6+dqql68LD8BT4GF4lurp28Ov4AXwO9gHfg/7q35+IHwUToSPwWmqn5+l+vlbfADeDT1wKfTCN6Ff9PS/7Fc5og/fuqJcH/6/pg8v14Ufmy68XA/+360HP7qiXAdevpVv5Vv5Vr6Vb+Vb+fav3P658/+H/abr/09x2QAgc9sAIHPbACBz2wCo3G0DgNxlA4DMZQOAzG0DYNIGYtb8R+b26S+yJEe/r7JYHwBpKksNlyc69ilxdOwfBZ25/21/Ye7/MJn6Xz73/7eY+5+rdg3LdR2DTwL8za+cR8yrTAaRNnem/seb969pR5e2WzD6xXH7kdEiGVYFtWUweVxz+YM69/pPEj8iMNr2WVHz+Y3/+cr7QvGdA6VtIYLqC+BUiW8SuM9frcw1AAotKGkKAq41AHS+f4LEXxjozazjWJ8Bjl3HDXJt2bSo18yrrib5OgSotz7vY41uv7nEtaBOb7F+YJe/Obffue6hVg21qThO8i/wp9it8bo+w6rt7WVvY035WmpfUU/qc2bCuaw297bd1Rrr7W8d8D5qve77Wa5hVljfThM592fuAcus8Z6tevwUOU/PwIXYkdzA5Ke7/NHrvEdcQliSvjKSTEm/yJ9OvVbbz3s2+npSJ+Ki6nSSNZs6XWzq9ISvsh3xnZAk+XsHyrK9yFTd+A/SJwKBBH+GtZH7Gm07cYa2792fh9I85s3ifuQSOhGGEKYS7iY8S1hL+JYV2md5U607vUHj/6E=
*/