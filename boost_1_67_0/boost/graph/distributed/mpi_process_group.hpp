// Copyright (C) 2004-2008 The Trustees of Indiana University.
// Copyright (C) 2007   Douglas Gregor
// Copyright (C) 2007  Matthias Troyer  <troyer@boost-consulting.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Matthias Troyer
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_MPI_PROCESS_GROUP
#define BOOST_GRAPH_DISTRIBUTED_MPI_PROCESS_GROUP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

//#define NO_SPLIT_BATCHES
#define SEND_OOB_BSEND

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <utility>
#include <memory>
#include <boost/function/function1.hpp>
#include <boost/function/function2.hpp>
#include <boost/function/function0.hpp>
#include <boost/mpi.hpp>
#include <boost/property_map/parallel/process_group.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace graph { namespace distributed {

// Process group tags
struct mpi_process_group_tag : virtual boost::parallel::linear_process_group_tag { };

class mpi_process_group
{
  struct impl;

 public:
  /// Number of tags available to each data structure.
  static const int max_tags = 256;

  /**
   * The type of a "receive" handler, that will be provided with
   * (source, tag) pairs when a message is received. Users can provide a
   * receive handler for a distributed data structure, for example, to
   * automatically pick up and respond to messages as needed.  
   */
  typedef function<void(int source, int tag)> receiver_type;

  /**
   * The type of a handler for the on-synchronize event, which will be
   * executed at the beginning of synchronize().
   */
  typedef function0<void>      on_synchronize_event_type;

  /// Used as a tag to help create an "empty" process group.
  struct create_empty {};

  /// The type used to buffer message data
  typedef boost::mpi::packed_oprimitive::buffer_type buffer_type;

  /// The type used to identify a process
  typedef int process_id_type;

  /// The type used to count the number of processes
  typedef int process_size_type;

  /// The type of communicator used to transmit data via MPI
  typedef boost::mpi::communicator communicator_type;

  /// Classification of the capabilities of this process group
  struct communication_category
    : virtual boost::parallel::bsp_process_group_tag, 
      virtual mpi_process_group_tag { };

  // TBD: We can eliminate the "source" field and possibly the
  // "offset" field.
  struct message_header {
    /// The process that sent the message
    process_id_type source;

    /// The message tag
    int tag;

    /// The offset of the message into the buffer
    std::size_t offset;

    /// The length of the message in the buffer, in bytes
    std::size_t bytes;
    
    template <class Archive>
    void serialize(Archive& ar, int)
    {
      ar & source & tag & offset & bytes;
    }
  };

  /**
   * Stores the outgoing messages for a particular processor.
   *
   * @todo Evaluate whether we should use a deque instance, which
   * would reduce could reduce the cost of "sending" messages but
   * increases the time spent in the synchronization step.
   */
  struct outgoing_messages {
        outgoing_messages() {}
        ~outgoing_messages() {}

    std::vector<message_header> headers;
    buffer_type                 buffer;
    
    template <class Archive>
    void serialize(Archive& ar, int)
    {
      ar & headers & buffer;
    }
    
    void swap(outgoing_messages& x) 
    {
      headers.swap(x.headers);
      buffer.swap(x.buffer);
    }
  };

private:
  /**
   * Virtual base from which every trigger will be launched. See @c
   * trigger_launcher for more information.
   */
  class trigger_base : boost::noncopyable
  {
  public:
    explicit trigger_base(int tag) : tag_(tag) { }

    /// Retrieve the tag associated with this trigger  
    int tag() const { return tag_; }

    virtual ~trigger_base() { }

    /**
     * Invoked to receive a message that matches a particular trigger. 
     *
     * @param source      the source of the message
     * @param tag         the (local) tag of the message
     * @param context     the context under which the trigger is being
     *                    invoked
     */
    virtual void 
    receive(mpi_process_group const& pg, int source, int tag, 
            trigger_receive_context context, int block=-1) const = 0;

  protected:
    // The message tag associated with this trigger
    int tag_;
  };

  /**
   * Launches a specific handler in response to a trigger. This
   * function object wraps up the handler function object and a buffer
   * for incoming data. 
   */
  template<typename Type, typename Handler>
  class trigger_launcher : public trigger_base
  {
  public:
    explicit trigger_launcher(mpi_process_group& self, int tag, 
                              const Handler& handler) 
      : trigger_base(tag), self(self), handler(handler) 
      {}

    void 
    receive(mpi_process_group const& pg, int source, int tag,  
            trigger_receive_context context, int block=-1) const;

  private:
    mpi_process_group& self;
    mutable Handler handler;
  };

  /**
   * Launches a specific handler with a message reply in response to a
   * trigger. This function object wraps up the handler function
   * object and a buffer for incoming data.
   */
  template<typename Type, typename Handler>
  class reply_trigger_launcher : public trigger_base
  {
  public:
    explicit reply_trigger_launcher(mpi_process_group& self, int tag, 
                                    const Handler& handler) 
      : trigger_base(tag), self(self), handler(handler) 
      {}

    void 
    receive(mpi_process_group const& pg, int source, int tag, 
            trigger_receive_context context, int block=-1) const;

  private:
    mpi_process_group& self;
    mutable Handler handler;
  };

  template<typename Type, typename Handler>
  class global_trigger_launcher : public trigger_base
  {
  public:
    explicit global_trigger_launcher(mpi_process_group& self, int tag, 
                              const Handler& handler) 
      : trigger_base(tag), handler(handler) 
      { 
      }

    void 
    receive(mpi_process_group const& pg, int source, int tag, 
            trigger_receive_context context, int block=-1) const;

  private:
    mutable Handler handler;
    // TBD: do not forget to cancel any outstanding Irecv when deleted,
    // if we decide to use Irecv
  };

  template<typename Type, typename Handler>
  class global_irecv_trigger_launcher : public trigger_base
  {
  public:
    explicit global_irecv_trigger_launcher(mpi_process_group& self, int tag, 
                              const Handler& handler, int sz) 
      : trigger_base(tag), handler(handler), buffer_size(sz)
      { 
        prepare_receive(self,tag);
      }

    void 
    receive(mpi_process_group const& pg, int source, int tag, 
            trigger_receive_context context, int block=-1) const;

  private:
    void prepare_receive(mpi_process_group const& pg, int tag, bool force=false) const;
    Handler handler;
    int buffer_size;
    // TBD: do not forget to cancel any outstanding Irecv when deleted,
    // if we decide to use Irecv
  };

public:
  /** 
   * Construct a new BSP process group from an MPI communicator. The
   * MPI communicator will be duplicated to create a new communicator
   * for this process group to use.
   */
  mpi_process_group(communicator_type parent_comm = communicator_type());

  /** 
   * Construct a new BSP process group from an MPI communicator. The
   * MPI communicator will be duplicated to create a new communicator
   * for this process group to use. This constructor allows to tune the
   * size of message batches.
   *    
   *   @param num_headers The maximum number of headers in a message batch
   *
   *   @param buffer_size The maximum size of the message buffer in a batch.
   *
   */
  mpi_process_group( std::size_t num_headers, std::size_t buffer_size, 
                     communicator_type parent_comm = communicator_type());

  /**
   * Construct a copy of the BSP process group for a new distributed
   * data structure. This data structure will synchronize with all
   * other members of the process group's equivalence class (including
   * @p other), but will have its own set of tags. 
   *
   *   @param other The process group that this new process group will
   *   be based on, using a different set of tags within the same
   *   communication and synchronization space.
   *
   *   @param handler A message handler that will be passed (source,
   *   tag) pairs for each message received by this data
   *   structure. The handler is expected to receive the messages
   *   immediately. The handler can be changed after-the-fact by
   *   calling @c replace_handler.
   *
   *   @param out_of_band_receive An anachronism. TODO: remove this.
   */
  mpi_process_group(const mpi_process_group& other,
                    const receiver_type& handler,
                    bool out_of_band_receive = false);

  /**
   * Construct a copy of the BSP process group for a new distributed
   * data structure. This data structure will synchronize with all
   * other members of the process group's equivalence class (including
   * @p other), but will have its own set of tags. 
   */
  mpi_process_group(const mpi_process_group& other, 
                    attach_distributed_object,
                    bool out_of_band_receive = false);

  /**
   * Create an "empty" process group, with no information. This is an
   * internal routine that users should never need.
   */
  explicit mpi_process_group(create_empty) {}

  /**
   * Destroys this copy of the process group.
   */
  ~mpi_process_group();

  /**
   * Replace the current message handler with a new message handler.
   *
   * @param handle The new message handler.
   * @param out_of_band_receive An anachronism: remove this
   */
  void replace_handler(const receiver_type& handler,
                       bool out_of_band_receive = false);

  /**
   * Turns this process group into the process group for a new
   * distributed data structure or object, allocating its own tag
   * block.
   */
  void make_distributed_object();

  /**
   * Replace the handler to be invoked at the beginning of synchronize.
   */
  void
  replace_on_synchronize_handler(const on_synchronize_event_type& handler = 0);

  /** 
   * Return the block number of the current data structure. A value of
   * 0 indicates that this particular instance of the process group is
   * not associated with any distributed data structure.
   */
  int my_block_number() const { return block_num? *block_num : 0; }

  /**
   * Encode a block number/tag pair into a single encoded tag for
   * transmission.
   */
  int encode_tag(int block_num, int tag) const
  { return block_num * max_tags + tag; }

  /**
   * Decode an encoded tag into a block number/tag pair. 
   */
  std::pair<int, int> decode_tag(int encoded_tag) const
  { return std::make_pair(encoded_tag / max_tags, encoded_tag % max_tags); }

  // @todo Actually write up the friend declarations so these could be
  // private.

  // private:

  /** Allocate a block of tags for this instance. The block should not
   * have been allocated already, e.g., my_block_number() ==
   * 0. Returns the newly-allocated block number.
   */
  int allocate_block(bool out_of_band_receive = false);

  /** Potentially emit a receive event out of band. Returns true if an event 
   *  was actually sent, false otherwise. 
   */
  bool maybe_emit_receive(int process, int encoded_tag) const;

  /** Emit a receive event. Returns true if an event was actually
   * sent, false otherwise. 
   */
  bool emit_receive(int process, int encoded_tag) const;

  /** Emit an on-synchronize event to all block handlers. */
  void emit_on_synchronize() const;

  /** Retrieve a reference to the stored receiver in this block.  */
  template<typename Receiver>
  Receiver* get_receiver();

  template<typename T>
  void
  send_impl(int dest, int tag, const T& value,
            mpl::true_ /*is_mpi_datatype*/) const;

  template<typename T>
  void
  send_impl(int dest, int tag, const T& value,
            mpl::false_ /*is_mpi_datatype*/) const;

  template<typename T>
  typename disable_if<boost::mpi::is_mpi_datatype<T>, void>::type
  array_send_impl(int dest, int tag, const T values[], std::size_t n) const;

  template<typename T>
  bool
  receive_impl(int source, int tag, T& value,
               mpl::true_ /*is_mpi_datatype*/) const;

  template<typename T>
  bool
  receive_impl(int source, int tag, T& value,
               mpl::false_ /*is_mpi_datatype*/) const;

  // Receive an array of values
  template<typename T>
  typename disable_if<boost::mpi::is_mpi_datatype<T>, bool>::type
  array_receive_impl(int source, int tag, T* values, std::size_t& n) const;

  optional<std::pair<mpi_process_group::process_id_type, int> > probe() const;

  void synchronize() const;

  operator bool() { return bool(impl_); }

  mpi_process_group base() const;

  /**
   * Create a new trigger for a specific message tag. Triggers handle
   * out-of-band messaging, and the handler itself will be called
   * whenever a message is available. The handler itself accepts four
   * arguments: the source of the message, the message tag (which will
   * be the same as @p tag), the message data (of type @c Type), and a
   * boolean flag that states whether the message was received
   * out-of-band. The last will be @c true for out-of-band receives,
   * or @c false for receives at the end of a synchronization step.
   */
  template<typename Type, typename Handler>
  void trigger(int tag, const Handler& handler);

  /**
   * Create a new trigger for a specific message tag, along with a way
   * to send a reply with data back to the sender. Triggers handle
   * out-of-band messaging, and the handler itself will be called
   * whenever a message is available. The handler itself accepts four
   * arguments: the source of the message, the message tag (which will
   * be the same as @p tag), the message data (of type @c Type), and a
   * boolean flag that states whether the message was received
   * out-of-band. The last will be @c true for out-of-band receives,
   * or @c false for receives at the end of a synchronization
   * step. The handler also returns a value, which will be routed back
   * to the sender.
   */
  template<typename Type, typename Handler>
  void trigger_with_reply(int tag, const Handler& handler);

  template<typename Type, typename Handler>
  void global_trigger(int tag, const Handler& handler, std::size_t buffer_size=0); 



  /**
   * Poll for any out-of-band messages. This routine will check if any
   * out-of-band messages are available. Those that are available will
   * be handled immediately, if possible.
   *
   * @returns if an out-of-band message has been received, but we are
   * unable to actually receive the message, a (source, tag) pair will
   * be returned. Otherwise, returns an empty optional.
   *
   * @param wait When true, we should block until a message comes in.
   *
   * @param synchronizing whether we are currently synchronizing the
   *                      process group
   */
  optional<std::pair<int, int> > 
  poll(bool wait = false, int block = -1, bool synchronizing = false) const;

  /**
   * Determines the context of the trigger currently executing. If
   * multiple triggers are executing (recursively), then the context
   * for the most deeply nested trigger will be returned. If no
   * triggers are executing, returns @c trc_none. This might be used,
   * for example, to determine whether a reply to a message should
   * itself be sent out-of-band or whether it can go via the normal,
   * slower communication route.
   */
  trigger_receive_context trigger_context() const;

  /// INTERNAL ONLY
  void receive_batch(process_id_type source, outgoing_messages& batch) const;

  /// INTERNAL ONLY
  ///
  /// Determine the actual communicator and tag will be used for a
  /// transmission with the given tag.
  std::pair<boost::mpi::communicator, int> 
  actual_communicator_and_tag(int tag, int block) const;

  /// set the size of the message buffer used for buffered oob sends
  
  static void set_message_buffer_size(std::size_t s);

  /// get the size of the message buffer used for buffered oob sends

  static std::size_t message_buffer_size();
  static int old_buffer_size;
  static void* old_buffer;
private:

  void install_trigger(int tag, int block, 
      shared_ptr<trigger_base> const& launcher); 

  void poll_requests(int block=-1) const;

  
  // send a batch if the buffer is full now or would get full
  void maybe_send_batch(process_id_type dest) const;

  // actually send a batch
  void send_batch(process_id_type dest, outgoing_messages& batch) const;
  void send_batch(process_id_type dest) const;

  void pack_headers() const;

  /**
   * Process a batch of incoming messages immediately.
   *
   * @param source         the source of these messages
   */
  void process_batch(process_id_type source) const;
  void receive_batch(boost::mpi::status& status) const;

  //void free_finished_sends() const;
          
  /// Status messages used internally by the process group
  enum status_messages {
    /// the first of the reserved message tags
    msg_reserved_first = 126,
    /// Sent from a processor when sending batched messages
    msg_batch = 126,
    /// Sent from a processor when sending large batched messages, larger than
    /// the maximum buffer size for messages to be received by MPI_Irecv
    msg_large_batch = 127,
    /// Sent from a source processor to everyone else when that
    /// processor has entered the synchronize() function.
    msg_synchronizing = 128,
    /// the last of the reserved message tags
    msg_reserved_last = 128
  };

  /**
   * Description of a block of tags associated to a particular
   * distributed data structure. This structure will live as long as
   * the distributed data structure is around, and will be used to
   * help send messages to the data structure.
   */
  struct block_type
  {
    block_type() { }

    /// Handler for receive events
    receiver_type     on_receive;

    /// Handler executed at the start of  synchronization 
    on_synchronize_event_type  on_synchronize;

    /// Individual message triggers. Note: at present, this vector is
    /// indexed by the (local) tag of the trigger.  Any tags that
    /// don't have triggers will have NULL pointers in that spot.
    std::vector<shared_ptr<trigger_base> > triggers;
  };

  /**
   * Data structure containing all of the blocks for the distributed
   * data structures attached to a process group.
   */
  typedef std::vector<block_type*> blocks_type;

  /// Iterator into @c blocks_type.
  typedef blocks_type::iterator block_iterator;

  /**
   * Deleter used to deallocate a block when its distributed data
   * structure is destroyed. This type will be used as the deleter for
   * @c block_num.
   */
  struct deallocate_block;
  
  static std::vector<char> message_buffer;

public:
  /**
   * Data associated with the process group and all of its attached
   * distributed data structures.
   */
  shared_ptr<impl> impl_;

  /**
   * When non-null, indicates that this copy of the process group is
   * associated with a particular distributed data structure. The
   * integer value contains the block number (a value > 0) associated
   * with that data structure. The deleter for this @c shared_ptr is a
   * @c deallocate_block object that will deallocate the associated
   * block in @c impl_->blocks.
   */
  shared_ptr<int>  block_num;

  /**
   * Rank of this process, to avoid having to call rank() repeatedly.
   */
  int rank;

  /**
   * Number of processes in this process group, to avoid having to
   * call communicator::size() repeatedly.
   */
  int size;
};



inline mpi_process_group::process_id_type 
process_id(const mpi_process_group& pg)
{ return pg.rank; }

inline mpi_process_group::process_size_type 
num_processes(const mpi_process_group& pg)
{ return pg.size; }

mpi_process_group::communicator_type communicator(const mpi_process_group& pg);

template<typename T>
void
send(const mpi_process_group& pg, mpi_process_group::process_id_type dest,
     int tag, const T& value);

template<typename InputIterator>
void
send(const mpi_process_group& pg, mpi_process_group::process_id_type dest,
     int tag, InputIterator first, InputIterator last);

template<typename T>
inline void
send(const mpi_process_group& pg, mpi_process_group::process_id_type dest,
     int tag, T* first, T* last)
{ send(pg, dest, tag, first, last - first); }

template<typename T>
inline void
send(const mpi_process_group& pg, mpi_process_group::process_id_type dest,
     int tag, const T* first, const T* last)
{ send(pg, dest, tag, first, last - first); }

template<typename T>
mpi_process_group::process_id_type
receive(const mpi_process_group& pg, int tag, T& value);

template<typename T>
mpi_process_group::process_id_type
receive(const mpi_process_group& pg,
        mpi_process_group::process_id_type source, int tag, T& value);

optional<std::pair<mpi_process_group::process_id_type, int> >
probe(const mpi_process_group& pg);

void synchronize(const mpi_process_group& pg);

template<typename T, typename BinaryOperation>
T*
all_reduce(const mpi_process_group& pg, T* first, T* last, T* out,
           BinaryOperation bin_op);

template<typename T, typename BinaryOperation>
T*
scan(const mpi_process_group& pg, T* first, T* last, T* out,
           BinaryOperation bin_op);

template<typename InputIterator, typename T>
void
all_gather(const mpi_process_group& pg,
           InputIterator first, InputIterator last, std::vector<T>& out);

template<typename InputIterator>
mpi_process_group
process_subgroup(const mpi_process_group& pg,
                 InputIterator first, InputIterator last);

template<typename T>
void
broadcast(const mpi_process_group& pg, T& val, 
          mpi_process_group::process_id_type root);


/*******************************************************************
 * Out-of-band communication                                       *
 *******************************************************************/

template<typename T>
typename enable_if<boost::mpi::is_mpi_datatype<T> >::type
send_oob(const mpi_process_group& pg, mpi_process_group::process_id_type dest,
         int tag, const T& value, int block=-1)
{
  using boost::mpi::get_mpi_datatype;

  // Determine the actual message tag we will use for the send, and which
  // communicator we will use.
  std::pair<boost::mpi::communicator, int> actual
    = pg.actual_communicator_and_tag(tag, block);

#ifdef SEND_OOB_BSEND
  if (mpi_process_group::message_buffer_size()) {
    MPI_Bsend(const_cast<T*>(&value), 1, get_mpi_datatype<T>(value), dest, 
              actual.second, actual.first);
    return;
  }
#endif
  MPI_Request request;
  MPI_Isend(const_cast<T*>(&value), 1, get_mpi_datatype<T>(value), dest, 
            actual.second, actual.first, &request);
  
  int done=0;
  do {
    pg.poll();
    MPI_Test(&request,&done,MPI_STATUS_IGNORE);
  } while (!done);
}

template<typename T>
typename disable_if<boost::mpi::is_mpi_datatype<T> >::type
send_oob(const mpi_process_group& pg, mpi_process_group::process_id_type dest,
         int tag, const T& value, int block=-1)
{
  using boost::mpi::packed_oarchive;

  // Determine the actual message tag we will use for the send, and which
  // communicator we will use.
  std::pair<boost::mpi::communicator, int> actual
    = pg.actual_communicator_and_tag(tag, block);

  // Serialize the data into a buffer
  packed_oarchive out(actual.first);
  out << value;
  std::size_t size = out.size();

  // Send the actual message data
#ifdef SEND_OOB_BSEND
  if (mpi_process_group::message_buffer_size()) {
    MPI_Bsend(const_cast<void*>(out.address()), size, MPI_PACKED,
            dest, actual.second, actual.first);
   return;
  }
#endif
  MPI_Request request;
  MPI_Isend(const_cast<void*>(out.address()), size, MPI_PACKED,
            dest, actual.second, actual.first, &request);

  int done=0;
  do {
    pg.poll();
    MPI_Test(&request,&done,MPI_STATUS_IGNORE);
  } while (!done);
}

template<typename T>
typename enable_if<boost::mpi::is_mpi_datatype<T> >::type
receive_oob(const mpi_process_group& pg, 
            mpi_process_group::process_id_type source, int tag, T& value, int block=-1);

template<typename T>
typename disable_if<boost::mpi::is_mpi_datatype<T> >::type
receive_oob(const mpi_process_group& pg, 
            mpi_process_group::process_id_type source, int tag, T& value, int block=-1);

template<typename SendT, typename ReplyT>
typename enable_if<boost::mpi::is_mpi_datatype<ReplyT> >::type
send_oob_with_reply(const mpi_process_group& pg, 
                    mpi_process_group::process_id_type dest,
                    int tag, const SendT& send_value, ReplyT& reply_value,
                    int block = -1);

template<typename SendT, typename ReplyT>
typename disable_if<boost::mpi::is_mpi_datatype<ReplyT> >::type
send_oob_with_reply(const mpi_process_group& pg, 
                    mpi_process_group::process_id_type dest,
                    int tag, const SendT& send_value, ReplyT& reply_value,
                    int block = -1);

} } } // end namespace boost::graph::distributed

BOOST_IS_BITWISE_SERIALIZABLE(boost::graph::distributed::mpi_process_group::message_header)
namespace boost { namespace mpi {
    template<>
    struct is_mpi_datatype<boost::graph::distributed::mpi_process_group::message_header> : mpl::true_ { };
} } // end namespace boost::mpi

namespace std {
/// optimized swap for outgoing messages
inline void 
swap(boost::graph::distributed::mpi_process_group::outgoing_messages& x,
     boost::graph::distributed::mpi_process_group::outgoing_messages& y)
{
  x.swap(y);
}


}

BOOST_CLASS_IMPLEMENTATION(boost::graph::distributed::mpi_process_group::outgoing_messages,object_serializable)
BOOST_CLASS_TRACKING(boost::graph::distributed::mpi_process_group::outgoing_messages,track_never)

#include <boost/graph/distributed/detail/mpi_process_group.ipp>

#endif // BOOST_PARALLEL_MPI_MPI_PROCESS_GROUP_HPP

/* mpi_process_group.hpp
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
*/