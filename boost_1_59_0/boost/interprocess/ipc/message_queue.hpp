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
#include <boost/interprocess/detail/timed_utils.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/move/detail/type_traits.hpp> //make_unsigned, alignment_of
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/move/detail/force_ptr.hpp>
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

//Blocking modes
enum mqblock_types   {  blocking,   timed,   non_blocking   };

//!A class that allows sending messages
//!between processes.
template<class VoidPointer>
class message_queue_t
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
   message_queue_t(create_only_t,
                 const char *name,
                 size_type max_num_msg,
                 size_type max_msg_size,
                 const permissions &perm = permissions());

   //!Opens or creates a process shared message queue with name "name".
   //!If the queue is created, the maximum number of messages will be "max_num_msg"
   //!and the maximum message size will be "max_msg_size". If queue was previously
   //!created the queue will be opened and "max_num_msg" and "max_msg_size" parameters
   //!are ignored. Throws on error.
   message_queue_t(open_or_create_t,
                 const char *name,
                 size_type max_num_msg,
                 size_type max_msg_size,
                 const permissions &perm = permissions());

   //!Opens a previously created process shared message queue with name "name".
   //!If the queue was not previously created or there are no free resources,
   //!throws an error.
   message_queue_t(open_only_t, const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a process shared message queue with name "name". For this message queue,
   //!the maximum number of messages will be "max_num_msg" and the maximum message size
   //!will be "max_msg_size". Throws on error and if the queue was previously created.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   message_queue_t(create_only_t,
                 const wchar_t *name,
                 size_type max_num_msg,
                 size_type max_msg_size,
                 const permissions &perm = permissions());

   //!Opens or creates a process shared message queue with name "name".
   //!If the queue is created, the maximum number of messages will be "max_num_msg"
   //!and the maximum message size will be "max_msg_size". If queue was previously
   //!created the queue will be opened and "max_num_msg" and "max_msg_size" parameters
   //!are ignored. Throws on error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   message_queue_t(open_or_create_t,
                 const wchar_t *name,
                 size_type max_num_msg,
                 size_type max_msg_size,
                 const permissions &perm = permissions());

   //!Opens a previously created process shared message queue with name "name".
   //!If the queue was not previously created or there are no free resources,
   //!throws an error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   message_queue_t(open_only_t, const wchar_t *name);

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
   template<class TimePoint>
   bool timed_send    (const void *buffer,     size_type buffer_size,
                           unsigned int priority,  const TimePoint& abs_time);

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
   template<class TimePoint>
   bool timed_receive (void *buffer,           size_type buffer_size,
                       size_type &recvd_size,unsigned int &priority,
                       const TimePoint &abs_time);

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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Removes the message queue from the system.
   //!Returns false on error. Never throws
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *name);

   #endif

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   friend class ipcdetail::msg_queue_initialization_func_t<VoidPointer>;

   template<mqblock_types Block, class TimePoint>
   bool do_receive(void *buffer,         size_type buffer_size,
                   size_type &recvd_size, unsigned int &priority,
                   const TimePoint &abs_time);

   template<mqblock_types Block, class TimePoint>
   bool do_send(const void *buffer,      size_type buffer_size,
                unsigned int priority,   const TimePoint &abs_time);

   //!Returns the needed memory size for the shared message queue.
   //!Never throws
   static size_type get_mem_size(size_type max_msg_size, size_type max_num_msg);
   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;

   template<class Lock, class TimePoint>
   static bool do_cond_wait(ipcdetail::bool_<true>, interprocess_condition &cond, Lock &lock, const TimePoint &abs_time)
   {  return cond.timed_wait(lock, abs_time);  }

   template<class Lock, class TimePoint>
   static bool do_cond_wait(ipcdetail::bool_<false>, interprocess_condition &cond, Lock &lock, const TimePoint &)
   {  cond.wait(lock); return true;  }

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
      return *mp_index[difference_type(pos ? --pos : m_max_num_msg - 1)];
   }

   //!Returns the inserted message with bottom priority
   msg_header &bottom_msg()
      {  return *mp_index[difference_type(m_cur_first_msg)];   }

   iterator inserted_ptr_begin() const
   {  return &mp_index[difference_type(m_cur_first_msg)]; }

   iterator inserted_ptr_end() const
      {  return &mp_index[difference_type(this->end_pos())];  }

   iterator lower_bound(const msg_hdr_ptr_t & value, priority_functor<VoidPointer> func)
   {
      iterator begin(this->inserted_ptr_begin()), end(this->inserted_ptr_end());
      if(end < begin){
         iterator idx_end = &mp_index[difference_type(m_max_num_msg)];
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
         return *mp_index[difference_type(m_cur_first_msg)];
      }
      else if(where == it_inserted_ptr_end){
         ++m_cur_num_msg;
         return **it_inserted_ptr_end;
      }
      else{
         size_type pos  = size_type(where - &mp_index[0]);
         size_type circ_pos = pos >= m_cur_first_msg ? pos - m_cur_first_msg : pos + (m_max_num_msg - m_cur_first_msg);
         //Check if it's more efficient to move back or move front
         if(circ_pos < m_cur_num_msg/2){
            //The queue can't be full so m_cur_num_msg == 0 or m_cur_num_msg <= pos
            //indicates two step insertion
            if(!pos){
               pos   = m_max_num_msg;
               where = &mp_index[difference_type(m_max_num_msg-1u)];
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
               mp_index[difference_type(m_max_num_msg-1u)] = mp_index[0];
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
                                 , &mp_index[0] + second_segment_end + 1u);
               mp_index[0] = mp_index[difference_type(m_max_num_msg-1u)];
            }
            std::copy_backward( &mp_index[0] + first_segment_beg
                              , &mp_index[0] + first_segment_end
                              , &mp_index[0] + first_segment_end + 1u);
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
      {  return *mp_index[difference_type(m_cur_num_msg-1u)];   }

   //!Returns the inserted message with bottom priority
   msg_header &bottom_msg()
      {  return *mp_index[0];   }

   iterator inserted_ptr_begin() const
   {  return &mp_index[0]; }

   iterator inserted_ptr_end() const
   {  return &mp_index[difference_type(m_cur_num_msg)]; }

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
      msg_hdr_ptr_t *index =  move_detail::force_ptr<msg_hdr_ptr_t*>
                                 (reinterpret_cast<char*>(this)+r_hdr_size);

      //Pointer to the first message header
      msg_header *msg_hdr   =  move_detail::force_ptr<msg_header*>
                                 (reinterpret_cast<char*>(this)+r_hdr_size+r_index_size);

      //Initialize the pointer to the index
      mp_index             = index;

      //Initialize the index so each slot points to a preallocated message
      for(size_type i = 0; i < m_max_num_msg; ++i){
         index[i] = msg_hdr;
         msg_hdr  = move_detail::force_ptr<msg_header*>
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
         } BOOST_CATCH_END
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

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

template<class VoidPointer>
inline message_queue_t<VoidPointer>::message_queue_t(create_only_t,
                                    const wchar_t *name,
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
                                    const wchar_t *name,
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
inline message_queue_t<VoidPointer>::message_queue_t(open_only_t, const wchar_t *name)
   //Create shared memory and execute functor atomically
   :  m_shmem(open_only,
              name,
              read_write,
              static_cast<void*>(0),
              //Prepare initialization functor
              ipcdetail::msg_queue_initialization_func_t<VoidPointer> ())
{}

#endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

template<class VoidPointer>
inline void message_queue_t<VoidPointer>::send
   (const void *buffer, size_type buffer_size, unsigned int priority)
{  this->do_send<blocking>(buffer, buffer_size, priority, 0); }

template<class VoidPointer>
inline bool message_queue_t<VoidPointer>::try_send
   (const void *buffer, size_type buffer_size, unsigned int priority)
{  return this->do_send<non_blocking>(buffer, buffer_size, priority, 0); }

template<class VoidPointer>
template<class TimePoint>
inline bool message_queue_t<VoidPointer>::timed_send
   (const void *buffer, size_type buffer_size
   ,unsigned int priority, const TimePoint &abs_time)
{
   if(ipcdetail::is_pos_infinity(abs_time)){
      this->send(buffer, buffer_size, priority);
      return true;
   }
   return this->do_send<timed>(buffer, buffer_size, priority, abs_time);
}

template<class VoidPointer>
template<mqblock_types Block, class TimePoint>
inline bool message_queue_t<VoidPointer>::do_send(
                                const void *buffer,      size_type buffer_size,
                                unsigned int priority,   const TimePoint &abs_time)
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
            switch(Block){
               case non_blocking :
                  #ifdef BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX
                  --p_hdr->m_blocked_senders;
                  #endif
                  return false;
               break;

               case blocking :
                  do{
                     (void)do_cond_wait(ipcdetail::bool_<false>(), p_hdr->m_cond_send, lock, abs_time);
                  }
                  while (p_hdr->is_full());
               break;

               case timed :
                  do{
                     if(!do_cond_wait(ipcdetail::bool_<Block == timed>(), p_hdr->m_cond_send, lock, abs_time)) {
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
         } BOOST_CATCH_END
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
{  this->do_receive<blocking>(buffer, buffer_size, recvd_size, priority, 0); }

template<class VoidPointer>
inline bool
   message_queue_t<VoidPointer>::try_receive(void *buffer,              size_type buffer_size,
                              size_type &recvd_size,   unsigned int &priority)
{  return this->do_receive<non_blocking>(buffer, buffer_size, recvd_size, priority, 0); }

template<class VoidPointer>
template<class TimePoint>
inline bool
   message_queue_t<VoidPointer>::timed_receive(void *buffer,            size_type buffer_size,
                                size_type &recvd_size,   unsigned int &priority,
                                const TimePoint &abs_time)
{
   if(ipcdetail::is_pos_infinity(abs_time)){
      this->receive(buffer, buffer_size, recvd_size, priority);
      return true;
   }
   return this->do_receive<timed>(buffer, buffer_size, recvd_size, priority, abs_time);
}

template<class VoidPointer>
template<mqblock_types Block, class TimePoint>
inline bool
   message_queue_t<VoidPointer>::do_receive(
                          void *buffer,            size_type buffer_size,
                          size_type &recvd_size,   unsigned int &priority,
                          const TimePoint &abs_time)
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
            switch(Block){
               case non_blocking :
                  #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
                  --p_hdr->m_blocked_receivers;
                  #endif
                  return false;
               break;

               case blocking :
                  do{
                     (void)do_cond_wait(ipcdetail::bool_<false>(), p_hdr->m_cond_recv, lock, abs_time);
                  }
                  while (p_hdr->is_empty());
               break;

               case timed :
                  do{
                     if(!do_cond_wait(ipcdetail::bool_<Block == timed>(), p_hdr->m_cond_recv, lock, abs_time)) {
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
         } BOOST_CATCH_END
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

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

template<class VoidPointer>
inline bool message_queue_t<VoidPointer>::remove(const wchar_t *name)
{  return shared_memory_object::remove(name);  }

#endif

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