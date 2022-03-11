//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MESSAGE_QUEUE_HPP
#define BOOST_INTERPROCESS_MESSAGE_QUEUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/move/detail/type_traits.hpp> //make_unsigned, alignment_of
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/assert.hpp>
#include <algorithm> //std::lower_bound
#include <cstddef>   //std::size_t
#include <cstring>   //memcpy


//!\file
//!Describes an inter-process message queue. This class allows sending
//!messages between processes and allows blocking, non-blocking and timed
//!sending and receiving.

namespace boost{  namespace interprocess{

namespace ipcdetail
{
   template<class VoidPointer>
   class msg_queue_initialization_func_t;
}

//!A class that allows sending messages
//!between processes.
template<class VoidPointer>
class message_queue_t
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Blocking modes
   enum block_t   {  blocking,   timed,   non_blocking   };

   message_queue_t();
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef VoidPointer                                                 void_pointer;
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<char>::type                                    char_ptr;
   typedef typename boost::intrusive::pointer_traits<char_ptr>::difference_type difference_type;
   typedef typename boost::container::dtl::make_unsigned<difference_type>::type        size_type;

   //!Creates a process shared message queue with name "name". For this message queue,
   //!the maximum number of messages will be "max_num_msg" and the maximum message size
   //!will be "max_msg_size". Throws on error and if the queue was previously created.
   message_queue_t(create_only_t create_only,
                 const char *name,
                 size_type max_num_msg,
                 size_type max_msg_size,
                 const permissions &perm = permissions());

   //!Opens or creates a process shared message queue with name "name".
   //!If the queue is created, the maximum number of messages will be "max_num_msg"
   //!and the maximum message size will be "max_msg_size". If queue was previously
   //!created the queue will be opened and "max_num_msg" and "max_msg_size" parameters
   //!are ignored. Throws on error.
   message_queue_t(open_or_create_t open_or_create,
                 const char *name,
                 size_type max_num_msg,
                 size_type max_msg_size,
                 const permissions &perm = permissions());

   //!Opens a previously created process shared message queue with name "name".
   //!If the queue was not previously created or there are no free resources,
   //!throws an error.
   message_queue_t(open_only_t open_only,
                 const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. All opened message queues are still
   //!valid after destruction. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the message queue from the system
   //!use remove().
   ~message_queue_t();

   //!Sends a message stored in buffer "buffer" with size "buffer_size" in the
   //!message queue with priority "priority". If the message queue is full
   //!the sender is blocked. Throws interprocess_error on error.
   void send (const void *buffer,     size_type buffer_size,
              unsigned int priority);

   //!Sends a message stored in buffer "buffer" with size "buffer_size" through the
   //!message queue with priority "priority". If the message queue is full
   //!the sender is not blocked and returns false, otherwise returns true.
   //!Throws interprocess_error on error.
   bool try_send    (const void *buffer,     size_type buffer_size,
                         unsigned int priority);

   //!Sends a message stored in buffer "buffer" with size "buffer_size" in the
   //!message queue with priority "priority". If the message queue is full
   //!the sender retries until time "abs_time" is reached. Returns true if
   //!the message has been successfully sent. Returns false if timeout is reached.
   //!Throws interprocess_error on error.
   bool timed_send    (const void *buffer,     size_type buffer_size,
                           unsigned int priority,  const boost::posix_time::ptime& abs_time);

   //!Receives a message from the message queue. The message is stored in buffer
   //!"buffer", which has size "buffer_size". The received message has size
   //!"recvd_size" and priority "priority". If the message queue is empty
   //!the receiver is blocked. Throws interprocess_error on error.
   void receive (void *buffer,           size_type buffer_size,
                 size_type &recvd_size,unsigned int &priority);

   //!Receives a message from the message queue. The message is stored in buffer
   //!"buffer", which has size "buffer_size". The received message has size
   //!"recvd_size" and priority "priority". If the message queue is empty
   //!the receiver is not blocked and returns false, otherwise returns true.
   //!Throws interprocess_error on error.
   bool try_receive (void *buffer,           size_type buffer_size,
                     size_type &recvd_size,unsigned int &priority);

   //!Receives a message from the message queue. The message is stored in buffer
   //!"buffer", which has size "buffer_size". The received message has size
   //!"recvd_size" and priority "priority". If the message queue is empty
   //!the receiver retries until time "abs_time" is reached. Returns true if
   //!the message has been successfully sent. Returns false if timeout is reached.
   //!Throws interprocess_error on error.
   bool timed_receive (void *buffer,           size_type buffer_size,
                       size_type &recvd_size,unsigned int &priority,
                       const boost::posix_time::ptime &abs_time);

   //!Returns the maximum number of messages allowed by the queue. The message
   //!queue must be opened or created previously. Otherwise, returns 0.
   //!Never throws
   size_type get_max_msg() const;

   //!Returns the maximum size of message allowed by the queue. The message
   //!queue must be opened or created previously. Otherwise, returns 0.
   //!Never throws
   size_type get_max_msg_size() const;

   //!Returns the number of messages currently stored.
   //!Never throws
   size_type get_num_msg() const;

   //!Removes the message queue from the system.
   //!Returns false on error. Never throws
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef boost::posix_time::ptime ptime;

   friend class ipcdetail::msg_queue_initialization_func_t<VoidPointer>;

   bool do_receive(block_t block,
                   void *buffer,         size_type buffer_size,
                   size_type &recvd_size, unsigned int &priority,
                   const ptime &abs_time);

   bool do_send(block_t block,
                const void *buffer,      size_type buffer_size,
                unsigned int priority,   const ptime &abs_time);

   //!Returns the needed memory size for the shared message queue.
   //!Never throws
   static size_type get_mem_size(size_type max_msg_size, size_type max_num_msg);
   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail {

//!This header is the prefix of each message in the queue
template<class VoidPointer>
class msg_hdr_t
{
   typedef VoidPointer                                                           void_pointer;
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<char>::type                                              char_ptr;
   typedef typename boost::intrusive::pointer_traits<char_ptr>::difference_type  difference_type;
   typedef typename boost::container::dtl::make_unsigned<difference_type>::type                  size_type;

   public:
   size_type               len;     // Message length
   unsigned int            priority;// Message priority
   //!Returns the data buffer associated with this this message
   void * data(){ return this+1; }  //
};

//!This functor is the predicate to order stored messages by priority
template<class VoidPointer>
class priority_functor
{
   typedef typename boost::intrusive::
      pointer_traits<VoidPointer>::template
         rebind_pointer<msg_hdr_t<VoidPointer> >::type                  msg_hdr_ptr_t;

   public:
   bool operator()(const msg_hdr_ptr_t &msg1,
                   const msg_hdr_ptr_t &msg2) const
      {  return msg1->priority < msg2->priority;  }
};

//!This header is placed in the beginning of the shared memory and contains
//!the data to control the queue. This class initializes the shared memory
//!in the following way: in ascending memory address with proper alignment
//!fillings:
//!
//!-> mq_hdr_t:
//!   Main control block that controls the rest of the elements
//!
//!-> offset_ptr<msg_hdr_t> index [max_num_msg]
//!   An array of pointers with size "max_num_msg" called index. Each pointer
//!   points to a preallocated message. Elements of this array are
//!   reordered in runtime in the following way:
//!
//!   IF BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX is defined:
//!
//!   When the current number of messages is "cur_num_msg", the array
//!   is treated like a circular buffer. Starting from position "cur_first_msg"
//!   "cur_num_msg" in a circular way, pointers point to inserted messages and the rest
//!   point to free messages. Those "cur_num_msg" pointers are
//!   ordered by the priority of the pointed message and by insertion order
//!   if two messages have the same priority. So the next message to be
//!   used in a "receive" is pointed by index [(cur_first_msg + cur_num_msg-1)%max_num_msg]
//!   and the first free message ready to be used in a "send" operation is
//!   [cur_first_msg] if circular buffer is extended from front,
//!   [(cur_first_msg + cur_num_msg)%max_num_msg] otherwise.
//!
//!   This transforms the index in a circular buffer with an embedded free
//!   message queue.
//!
//!   ELSE (BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX is NOT defined):
//!
//!   When the current number of messages is "cur_num_msg", the first
//!   "cur_num_msg" pointers point to inserted messages and the rest
//!   point to free messages. The first "cur_num_msg" pointers are
//!   ordered by the priority of the pointed message and by insertion order
//!   if two messages have the same priority. So the next message to be
//!   used in a "receive" is pointed by index [cur_num_msg-1] and the first free
//!   message ready to be used in a "send" operation is index [cur_num_msg].
//!
//!   This transforms the index in a fixed size priority queue with an embedded free
//!   message queue.
//!
//!-> struct message_t
//!   {
//!      msg_hdr_t            header;
//!      char[max_msg_size]   data;
//!   } messages [max_num_msg];
//!
//!   An array of buffers of preallocated messages, each one prefixed with the
//!   msg_hdr_t structure. Each of this message is pointed by one pointer of
//!   the index structure.
template<class VoidPointer>
class mq_hdr_t
   : public ipcdetail::priority_functor<VoidPointer>
{
   typedef VoidPointer                                                     void_pointer;
   typedef msg_hdr_t<void_pointer>                                         msg_header;
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<msg_header>::type                                  msg_hdr_ptr_t;
   typedef typename boost::intrusive::pointer_traits
      <msg_hdr_ptr_t>::difference_type                                     difference_type;
   typedef typename boost::container::
      dtl::make_unsigned<difference_type>::type               size_type;
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<msg_hdr_ptr_t>::type                              msg_hdr_ptr_ptr_t;
   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;

   public:
   //!Constructor. This object must be constructed in the beginning of the
   //!shared memory of the size returned by the function "get_mem_size".
   //!This constructor initializes the needed resources and creates
   //!the internal structures like the priority index. This can throw.
   mq_hdr_t(size_type max_num_msg, size_type max_msg_size)
      : m_max_num_msg(max_num_msg),
         m_max_msg_size(max_msg_size),
         m_cur_num_msg(0)
         #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
         ,m_cur_first_msg(0u)
         ,m_blocked_senders(0u)
         ,m_blocked_receivers(0u)
         #endif
      {  this->initialize_memory();  }

   //!Returns true if the message queue is full
   bool is_full() const
      {  return m_cur_num_msg == m_max_num_msg;  }

   //!Returns true if the message queue is empty
   bool is_empty() const
      {  return !m_cur_num_msg;  }

   //!Frees the top priority message and saves it in the free message list
   void free_top_msg()
      {  --m_cur_num_msg;  }

   #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)

   typedef msg_hdr_ptr_t *iterator;

   size_type end_pos() const
   {
      const size_type space_until_bufend = m_max_num_msg - m_cur_first_msg;
      return space_until_bufend > m_cur_num_msg
         ? m_cur_first_msg + m_cur_num_msg : m_cur_num_msg - space_until_bufend;
   }

   //!Returns the inserted message with top priority
   msg_header &top_msg()
   {
      size_type pos = this->end_pos();
      return *mp_index[pos ? --pos : m_max_num_msg - 1];
   }

   //!Returns the inserted message with bottom priority
   msg_header &bottom_msg()
      {  return *mp_index[m_cur_first_msg];   }

   iterator inserted_ptr_begin() const
   {  return &mp_index[m_cur_first_msg]; }

   iterator inserted_ptr_end() const
      {  return &mp_index[this->end_pos()];  }

   iterator lower_bound(const msg_hdr_ptr_t & value, priority_functor<VoidPointer> func)
   {
      iterator begin(this->inserted_ptr_begin()), end(this->inserted_ptr_end());
      if(end < begin){
         iterator idx_end = &mp_index[m_max_num_msg];
         iterator ret = std::lower_bound(begin, idx_end, value, func);
         if(idx_end == ret){
            iterator idx_beg = &mp_index[0];
            ret = std::lower_bound(idx_beg, end, value, func);
            //sanity check, these cases should not call lower_bound (optimized out)
            BOOST_ASSERT(ret != end);
            BOOST_ASSERT(ret != begin);
            return ret;
         }
         else{
            return ret;
         }
      }
      else{
         return std::lower_bound(begin, end, value, func);
      }
   }

   msg_header & insert_at(iterator where)
   {
      iterator it_inserted_ptr_end = this->inserted_ptr_end();
      iterator it_inserted_ptr_beg = this->inserted_ptr_begin();
      if(where == it_inserted_ptr_beg){
         //unsigned integer guarantees underflow
         m_cur_first_msg = m_cur_first_msg ? m_cur_first_msg : m_max_num_msg;
         --m_cur_first_msg;
         ++m_cur_num_msg;
         return *mp_index[m_cur_first_msg];
      }
      else if(where == it_inserted_ptr_end){
         ++m_cur_num_msg;
         return **it_inserted_ptr_end;
      }
      else{
         size_type pos  = where - &mp_index[0];
         size_type circ_pos = pos >= m_cur_first_msg ? pos - m_cur_first_msg : pos + (m_max_num_msg - m_cur_first_msg);
         //Check if it's more efficient to move back or move front
         if(circ_pos < m_cur_num_msg/2){
            //The queue can't be full so m_cur_num_msg == 0 or m_cur_num_msg <= pos
            //indicates two step insertion
            if(!pos){
               pos   = m_max_num_msg;
               where = &mp_index[m_max_num_msg-1];
            }
            else{
               --where;
            }
            const bool unique_segment = m_cur_first_msg && m_cur_first_msg <= pos;
            const size_type first_segment_beg  = unique_segment ? m_cur_first_msg : 1u;
            const size_type first_segment_end  = pos;
            const size_type second_segment_beg = unique_segment || !m_cur_first_msg ? m_max_num_msg : m_cur_first_msg;
            const size_type second_segment_end = m_max_num_msg;
            const msg_hdr_ptr_t backup   = *(&mp_index[0] + (unique_segment ?  first_segment_beg : second_segment_beg) - 1);

            //First segment
            if(!unique_segment){
               std::copy( &mp_index[0] + second_segment_beg
                        , &mp_index[0] + second_segment_end
                        , &mp_index[0] + second_segment_beg - 1);
               mp_index[m_max_num_msg-1] = mp_index[0];
            }
            std::copy( &mp_index[0] + first_segment_beg
                     , &mp_index[0] + first_segment_end
                     , &mp_index[0] + first_segment_beg - 1);
            *where = backup;
            m_cur_first_msg = m_cur_first_msg ? m_cur_first_msg : m_max_num_msg;
            --m_cur_first_msg;
            ++m_cur_num_msg;
            return **where;
         }
         else{
            //The queue can't be full so end_pos < m_cur_first_msg
            //indicates two step insertion
            const size_type pos_end = this->end_pos();
            const bool unique_segment = pos < pos_end;
            const size_type first_segment_beg  = pos;
            const size_type first_segment_end  = unique_segment  ? pos_end : m_max_num_msg-1;
            const size_type second_segment_beg = 0u;
            const size_type second_segment_end = unique_segment ? 0u : pos_end;
            const msg_hdr_ptr_t backup   = *it_inserted_ptr_end;

            //First segment
            if(!unique_segment){
               std::copy_backward( &mp_index[0] + second_segment_beg
                                 , &mp_index[0] + second_segment_end
                                 , &mp_index[0] + second_segment_end + 1);
               mp_index[0] = mp_index[m_max_num_msg-1];
            }
            std::copy_backward( &mp_index[0] + first_segment_beg
                              , &mp_index[0] + first_segment_end
                              , &mp_index[0] + first_segment_end + 1);
            *where = backup;
            ++m_cur_num_msg;
            return **where;
         }
      }
   }

   #else //BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX

   typedef msg_hdr_ptr_t *iterator;

   //!Returns the inserted message with top priority
   msg_header &top_msg()
      {  return *mp_index[m_cur_num_msg-1];   }

   //!Returns the inserted message with bottom priority
   msg_header &bottom_msg()
      {  return *mp_index[0];   }

   iterator inserted_ptr_begin() const
   {  return &mp_index[0]; }

   iterator inserted_ptr_end() const
   {  return &mp_index[m_cur_num_msg]; }

   iterator lower_bound(const msg_hdr_ptr_t & value, priority_functor<VoidPointer> func)
   {  return std::lower_bound(this->inserted_ptr_begin(), this->inserted_ptr_end(), value, func);  }

   msg_header & insert_at(iterator pos)
   {
      const msg_hdr_ptr_t backup = *inserted_ptr_end();
      std::copy_backward(pos, inserted_ptr_end(), inserted_ptr_end()+1);
      *pos = backup;
      ++m_cur_num_msg;
      return **pos;
   }

   #endif   //BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX

   //!Inserts the first free message in the priority queue
   msg_header & queue_free_msg(unsigned int priority)
   {
      //Get priority queue's range
      iterator it  (inserted_ptr_begin()), it_end(inserted_ptr_end());
      //Optimize for non-priority usage
      if(m_cur_num_msg && priority > this->bottom_msg().priority){
         //Check for higher priority than all stored messages
         if(priority > this->top_msg().priority){
            it = it_end;
         }
         else{
            //Since we don't now which free message we will pick
            //build a dummy header for searches
            msg_header dummy_hdr;
            dummy_hdr.priority = priority;

            //Get free msg
            msg_hdr_ptr_t dummy_ptr(&dummy_hdr);

            //Check where the free message should be placed
            it = this->lower_bound(dummy_ptr, static_cast<priority_functor<VoidPointer>&>(*this));
         }
      }
      //Insert the free message in the correct position
      return this->insert_at(it);
   }

   //!Returns the number of bytes needed to construct a message queue with
   //!"max_num_size" maximum number of messages and "max_msg_size" maximum
   //!message size. Never throws.
   static size_type get_mem_size
      (size_type max_msg_size, size_type max_num_msg)
   {
      const size_type
       msg_hdr_align  = ::boost::container::dtl::alignment_of<msg_header>::value,
       index_align    = ::boost::container::dtl::alignment_of<msg_hdr_ptr_t>::value,
         r_hdr_size     = ipcdetail::ct_rounded_size<sizeof(mq_hdr_t), index_align>::value,
         r_index_size   = ipcdetail::get_rounded_size<size_type>(max_num_msg*sizeof(msg_hdr_ptr_t), msg_hdr_align),
         r_max_msg_size = ipcdetail::get_rounded_size<size_type>(max_msg_size, msg_hdr_align) + sizeof(msg_header);
      return r_hdr_size + r_index_size + (max_num_msg*r_max_msg_size) +
         open_create_impl_t::ManagedOpenOrCreateUserOffset;
   }

   //!Initializes the memory structures to preallocate messages and constructs the
   //!message index. Never throws.
   void initialize_memory()
   {
      const size_type
        msg_hdr_align  = ::boost::container::dtl::alignment_of<msg_header>::value,
        index_align    = ::boost::container::dtl::alignment_of<msg_hdr_ptr_t>::value,
         r_hdr_size     = ipcdetail::ct_rounded_size<sizeof(mq_hdr_t), index_align>::value,
         r_index_size   = ipcdetail::get_rounded_size<size_type>(m_max_num_msg*sizeof(msg_hdr_ptr_t), msg_hdr_align),
         r_max_msg_size = ipcdetail::get_rounded_size<size_type>(m_max_msg_size, msg_hdr_align) + sizeof(msg_header);

      //Pointer to the index
      msg_hdr_ptr_t *index =  reinterpret_cast<msg_hdr_ptr_t*>
                                 (reinterpret_cast<char*>(this)+r_hdr_size);

      //Pointer to the first message header
      msg_header *msg_hdr   =  reinterpret_cast<msg_header*>
                                 (reinterpret_cast<char*>(this)+r_hdr_size+r_index_size);

      //Initialize the pointer to the index
      mp_index             = index;

      //Initialize the index so each slot points to a preallocated message
      for(size_type i = 0; i < m_max_num_msg; ++i){
         index[i] = msg_hdr;
         msg_hdr  = reinterpret_cast<msg_header*>
                        (reinterpret_cast<char*>(msg_hdr)+r_max_msg_size);
      }
   }

   public:
   //Pointer to the index
   msg_hdr_ptr_ptr_t          mp_index;
   //Maximum number of messages of the queue
   const size_type            m_max_num_msg;
   //Maximum size of messages of the queue
   const size_type            m_max_msg_size;
   //Current number of messages
   size_type                  m_cur_num_msg;
   //Mutex to protect data structures
   interprocess_mutex         m_mutex;
   //Condition block receivers when there are no messages
   interprocess_condition     m_cond_recv;
   //Condition block senders when the queue is full
   interprocess_condition     m_cond_send;
   #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
   //Current start offset in the circular index
   size_type                  m_cur_first_msg;
   size_type                  m_blocked_senders;
   size_type                  m_blocked_receivers;
   #endif
};


//!This is the atomic functor to be executed when creating or opening
//!shared memory. Never throws
template<class VoidPointer>
class msg_queue_initialization_func_t
{
   public:
   typedef typename boost::intrusive::
      pointer_traits<VoidPointer>::template
         rebind_pointer<char>::type                               char_ptr;
   typedef typename boost::intrusive::pointer_traits<char_ptr>::
      difference_type                                             difference_type;
   typedef typename boost::container::dtl::
      make_unsigned<difference_type>::type                        size_type;

   msg_queue_initialization_func_t(size_type maxmsg = 0,
                         size_type maxmsgsize = 0)
      : m_maxmsg (maxmsg), m_maxmsgsize(maxmsgsize) {}

   bool operator()(void *address, size_type, bool created)
   {
      char      *mptr;

      if(created){
         mptr     = reinterpret_cast<char*>(address);
         //Construct the message queue header at the beginning
         BOOST_TRY{
            new (mptr) mq_hdr_t<VoidPointer>(m_maxmsg, m_maxmsgsize);
         }
         BOOST_CATCH(...){
            return false;
         }
         BOOST_CATCH_END
      }
      return true;
   }

   std::size_t get_min_size() const
   {
      return mq_hdr_t<VoidPointer>::get_mem_size(m_maxmsgsize, m_maxmsg)
      - message_queue_t<VoidPointer>::open_create_impl_t::ManagedOpenOrCreateUserOffset;
   }

   const size_type m_maxmsg;
   const size_type m_maxmsgsize;
};

}  //namespace ipcdetail {

template<class VoidPointer>
inline message_queue_t<VoidPointer>::~message_queue_t()
{}

template<class VoidPointer>
inline typename message_queue_t<VoidPointer>::size_type message_queue_t<VoidPointer>::get_mem_size
   (size_type max_msg_size, size_type max_num_msg)
{  return ipcdetail::mq_hdr_t<VoidPointer>::get_mem_size(max_msg_size, max_num_msg);   }

template<class VoidPointer>
inline message_queue_t<VoidPointer>::message_queue_t(create_only_t,
                                    const char *name,
                                    size_type max_num_msg,
                                    size_type max_msg_size,
                                    const permissions &perm)
      //Create shared memory and execute functor atomically
   :  m_shmem(create_only,
              name,
              get_mem_size(max_msg_size, max_num_msg),
              read_write,
              static_cast<void*>(0),
              //Prepare initialization functor
              ipcdetail::msg_queue_initialization_func_t<VoidPointer> (max_num_msg, max_msg_size),
              perm)
{}

template<class VoidPointer>
inline message_queue_t<VoidPointer>::message_queue_t(open_or_create_t,
                                    const char *name,
                                    size_type max_num_msg,
                                    size_type max_msg_size,
                                    const permissions &perm)
      //Create shared memory and execute functor atomically
   :  m_shmem(open_or_create,
              name,
              get_mem_size(max_msg_size, max_num_msg),
              read_write,
              static_cast<void*>(0),
              //Prepare initialization functor
              ipcdetail::msg_queue_initialization_func_t<VoidPointer> (max_num_msg, max_msg_size),
              perm)
{}

template<class VoidPointer>
inline message_queue_t<VoidPointer>::message_queue_t(open_only_t, const char *name)
   //Create shared memory and execute functor atomically
   :  m_shmem(open_only,
              name,
              read_write,
              static_cast<void*>(0),
              //Prepare initialization functor
              ipcdetail::msg_queue_initialization_func_t<VoidPointer> ())
{}

template<class VoidPointer>
inline void message_queue_t<VoidPointer>::send
   (const void *buffer, size_type buffer_size, unsigned int priority)
{  this->do_send(blocking, buffer, buffer_size, priority, ptime()); }

template<class VoidPointer>
inline bool message_queue_t<VoidPointer>::try_send
   (const void *buffer, size_type buffer_size, unsigned int priority)
{  return this->do_send(non_blocking, buffer, buffer_size, priority, ptime()); }

template<class VoidPointer>
inline bool message_queue_t<VoidPointer>::timed_send
   (const void *buffer, size_type buffer_size
   ,unsigned int priority, const boost::posix_time::ptime &abs_time)
{
   if(abs_time == boost::posix_time::pos_infin){
      this->send(buffer, buffer_size, priority);
      return true;
   }
   return this->do_send(timed, buffer, buffer_size, priority, abs_time);
}

template<class VoidPointer>
inline bool message_queue_t<VoidPointer>::do_send(block_t block,
                                const void *buffer,      size_type buffer_size,
                                unsigned int priority,   const boost::posix_time::ptime &abs_time)
{
   ipcdetail::mq_hdr_t<VoidPointer> *p_hdr = static_cast<ipcdetail::mq_hdr_t<VoidPointer>*>(m_shmem.get_user_address());
   //Check if buffer is smaller than maximum allowed
   if (buffer_size > p_hdr->m_max_msg_size) {
      throw interprocess_exception(size_error);
   }

   #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
   bool notify_blocked_receivers = false;
   #endif
   //---------------------------------------------
   scoped_lock<interprocess_mutex> lock(p_hdr->m_mutex);
   //---------------------------------------------
   {
      //If the queue is full execute blocking logic
      if (p_hdr->is_full()) {
         BOOST_TRY{
            #ifdef BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX
            ++p_hdr->m_blocked_senders;
            #endif
            switch(block){
               case non_blocking :
                  #ifdef BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX
                  --p_hdr->m_blocked_senders;
                  #endif
                  return false;
               break;

               case blocking :
                  do{
                     p_hdr->m_cond_send.wait(lock);
                  }
                  while (p_hdr->is_full());
               break;

               case timed :
                  do{
                     if(!p_hdr->m_cond_send.timed_wait(lock, abs_time)){
                        if(p_hdr->is_full()){
                           #ifdef BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX
                           --p_hdr->m_blocked_senders;
                           #endif
                           return false;
                        }
                        break;
                     }
                  }
                  while (p_hdr->is_full());
               break;
               default:
               break;
            }
            #ifdef BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX
            --p_hdr->m_blocked_senders;
            #endif
         }
         BOOST_CATCH(...){
            #ifdef BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX
            --p_hdr->m_blocked_senders;
            #endif
            BOOST_RETHROW;
         }
         BOOST_CATCH_END
      }

      #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
      notify_blocked_receivers = 0 != p_hdr->m_blocked_receivers;
      #endif
      //Insert the first free message in the priority queue
      ipcdetail::msg_hdr_t<VoidPointer> &free_msg_hdr = p_hdr->queue_free_msg(priority);

      //Sanity check, free msgs are always cleaned when received
      BOOST_ASSERT(free_msg_hdr.priority == 0);
      BOOST_ASSERT(free_msg_hdr.len == 0);

      //Copy control data to the free message
      free_msg_hdr.priority = priority;
      free_msg_hdr.len      = buffer_size;

      //Copy user buffer to the message
      std::memcpy(free_msg_hdr.data(), buffer, buffer_size);
   }  // Lock end

   //Notify outside lock to avoid contention. This might produce some
   //spurious wakeups, but it's usually far better than notifying inside.
   //If this message changes the queue empty state, notify it to receivers
   #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
   if (notify_blocked_receivers){
      p_hdr->m_cond_recv.notify_one();
   }
   #else
   p_hdr->m_cond_recv.notify_one();
   #endif

   return true;
}

template<class VoidPointer>
inline void message_queue_t<VoidPointer>::receive(void *buffer,        size_type buffer_size,
                        size_type &recvd_size,   unsigned int &priority)
{  this->do_receive(blocking, buffer, buffer_size, recvd_size, priority, ptime()); }

template<class VoidPointer>
inline bool
   message_queue_t<VoidPointer>::try_receive(void *buffer,              size_type buffer_size,
                              size_type &recvd_size,   unsigned int &priority)
{  return this->do_receive(non_blocking, buffer, buffer_size, recvd_size, priority, ptime()); }

template<class VoidPointer>
inline bool
   message_queue_t<VoidPointer>::timed_receive(void *buffer,            size_type buffer_size,
                                size_type &recvd_size,   unsigned int &priority,
                                const boost::posix_time::ptime &abs_time)
{
   if(abs_time == boost::posix_time::pos_infin){
      this->receive(buffer, buffer_size, recvd_size, priority);
      return true;
   }
   return this->do_receive(timed, buffer, buffer_size, recvd_size, priority, abs_time);
}

template<class VoidPointer>
inline bool
   message_queue_t<VoidPointer>::do_receive(block_t block,
                          void *buffer,            size_type buffer_size,
                          size_type &recvd_size,   unsigned int &priority,
                          const boost::posix_time::ptime &abs_time)
{
   ipcdetail::mq_hdr_t<VoidPointer> *p_hdr = static_cast<ipcdetail::mq_hdr_t<VoidPointer>*>(m_shmem.get_user_address());
   //Check if buffer is big enough for any message
   if (buffer_size < p_hdr->m_max_msg_size) {
      throw interprocess_exception(size_error);
   }

   #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
   bool notify_blocked_senders = false;
   #endif
   //---------------------------------------------
   scoped_lock<interprocess_mutex> lock(p_hdr->m_mutex);
   //---------------------------------------------
   {
      //If there are no messages execute blocking logic
      if (p_hdr->is_empty()) {
         BOOST_TRY{
            #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
            ++p_hdr->m_blocked_receivers;
            #endif
            switch(block){
               case non_blocking :
                  #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
                  --p_hdr->m_blocked_receivers;
                  #endif
                  return false;
               break;

               case blocking :
                  do{
                     p_hdr->m_cond_recv.wait(lock);
                  }
                  while (p_hdr->is_empty());
               break;

               case timed :
                  do{
                     if(!p_hdr->m_cond_recv.timed_wait(lock, abs_time)){
                        if(p_hdr->is_empty()){
                           #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
                           --p_hdr->m_blocked_receivers;
                           #endif
                           return false;
                        }
                        break;
                     }
                  }
                  while (p_hdr->is_empty());
               break;

               //Paranoia check
               default:
               break;
            }
            #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
            --p_hdr->m_blocked_receivers;
            #endif
         }
         BOOST_CATCH(...){
            #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
            --p_hdr->m_blocked_receivers;
            #endif
            BOOST_RETHROW;
         }
         BOOST_CATCH_END
      }

      #ifdef BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX
      notify_blocked_senders = 0 != p_hdr->m_blocked_senders;
      #endif

      //There is at least one message ready to pick, get the top one
      ipcdetail::msg_hdr_t<VoidPointer> &top_msg = p_hdr->top_msg();

      //Get data from the message
      recvd_size     = top_msg.len;
      priority       = top_msg.priority;

      //Some cleanup to ease debugging
      top_msg.len       = 0;
      top_msg.priority  = 0;

      //Copy data to receiver's bufers
      std::memcpy(buffer, top_msg.data(), recvd_size);

      //Free top message and put it in the free message list
      p_hdr->free_top_msg();
   }  //Lock end

   //Notify outside lock to avoid contention. This might produce some
   //spurious wakeups, but it's usually far better than notifying inside.
   //If this reception changes the queue full state, notify senders
   #ifdef BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX
   if (notify_blocked_senders){
      p_hdr->m_cond_send.notify_one();
   }
   #else
   p_hdr->m_cond_send.notify_one();
   #endif

   return true;
}

template<class VoidPointer>
inline typename message_queue_t<VoidPointer>::size_type message_queue_t<VoidPointer>::get_max_msg() const
{
   ipcdetail::mq_hdr_t<VoidPointer> *p_hdr = static_cast<ipcdetail::mq_hdr_t<VoidPointer>*>(m_shmem.get_user_address());
   return p_hdr ? p_hdr->m_max_num_msg : 0;  }

template<class VoidPointer>
inline typename message_queue_t<VoidPointer>::size_type message_queue_t<VoidPointer>::get_max_msg_size() const
{
   ipcdetail::mq_hdr_t<VoidPointer> *p_hdr = static_cast<ipcdetail::mq_hdr_t<VoidPointer>*>(m_shmem.get_user_address());
   return p_hdr ? p_hdr->m_max_msg_size : 0;
}

template<class VoidPointer>
inline typename message_queue_t<VoidPointer>::size_type message_queue_t<VoidPointer>::get_num_msg() const
{
   ipcdetail::mq_hdr_t<VoidPointer> *p_hdr = static_cast<ipcdetail::mq_hdr_t<VoidPointer>*>(m_shmem.get_user_address());
   if(p_hdr){
      //---------------------------------------------
      scoped_lock<interprocess_mutex> lock(p_hdr->m_mutex);
      //---------------------------------------------
      return p_hdr->m_cur_num_msg;
   }

   return 0;
}

template<class VoidPointer>
inline bool message_queue_t<VoidPointer>::remove(const char *name)
{  return shared_memory_object::remove(name);  }

#else

//!Typedef for a default message queue
//!to be used between processes
typedef message_queue_t<offset_ptr<void> > message_queue;

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}} //namespace boost{  namespace interprocess{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_MESSAGE_QUEUE_HPP

/* message_queue.hpp
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
*/