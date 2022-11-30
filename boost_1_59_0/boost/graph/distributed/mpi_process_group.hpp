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


/// optimized swap for outgoing messages
inline void
swap(mpi_process_group::outgoing_messages& x,
     mpi_process_group::outgoing_messages& y)
{
  x.swap(y);
}


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

BOOST_CLASS_IMPLEMENTATION(boost::graph::distributed::mpi_process_group::outgoing_messages,object_serializable)
BOOST_CLASS_TRACKING(boost::graph::distributed::mpi_process_group::outgoing_messages,track_never)

#include <boost/graph/distributed/detail/mpi_process_group.ipp>

#endif // BOOST_PARALLEL_MPI_MPI_PROCESS_GROUP_HPP

/* mpi_process_group.hpp
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
*/