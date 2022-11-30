/*
  boost::signals2::connection provides a handle to a signal/slot connection.

  Author: Frank Mori Hess <fmhess@users.sourceforge.net>
  Begin: 2007-01-23
*/
// Copyright Frank Mori Hess 2007-2008.
// Distributed under the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/signals2 for library home page.

#ifndef BOOST_SIGNALS2_CONNECTION_HPP
#define BOOST_SIGNALS2_CONNECTION_HPP

#include <boost/config.hpp>
#include <boost/function.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2/detail/auto_buffer.hpp>
#include <boost/signals2/detail/null_output_iterator.hpp>
#include <boost/signals2/detail/unique_lock.hpp>
#include <boost/signals2/slot.hpp>
#include <boost/weak_ptr.hpp>

namespace boost
{
  namespace signals2
  {
    inline void null_deleter(const void*) {}
    namespace detail
    {
      // This lock maintains a list of shared_ptr<void>
      // which will be destroyed only after the lock
      // has released its mutex.  Used to garbage
      // collect disconnected slots
      template<typename Mutex>
      class garbage_collecting_lock: public noncopyable
      {
      public:
        garbage_collecting_lock(Mutex &m):
          lock(m)
        {}
        void add_trash(const shared_ptr<void> &piece_of_trash)
        {
          garbage.push_back(piece_of_trash);
        }
      private:
        // garbage must be declared before lock
        // to insure it is destroyed after lock is
        // destroyed.
        auto_buffer<shared_ptr<void>, store_n_objects<10> > garbage;
        unique_lock<Mutex> lock;
      };
      
      class connection_body_base
      {
      public:
        connection_body_base():
          _connected(true), m_slot_refcount(1)
        {
        }
        virtual ~connection_body_base() {}
        void disconnect()
        {
          garbage_collecting_lock<connection_body_base> local_lock(*this);
          nolock_disconnect(local_lock);
        }
        template<typename Mutex>
        void nolock_disconnect(garbage_collecting_lock<Mutex> &lock_arg) const
        {
          if(_connected)
          {
            _connected = false;
            dec_slot_refcount(lock_arg);
          }
        }
        virtual bool connected() const = 0;
        shared_ptr<void> get_blocker()
        {
          unique_lock<connection_body_base> local_lock(*this);
          shared_ptr<void> blocker = _weak_blocker.lock();
          if(blocker == shared_ptr<void>())
          {
            blocker.reset(this, &null_deleter);
            _weak_blocker = blocker;
          }
          return blocker;
        }
        bool blocked() const
        {
          return !_weak_blocker.expired();
        }
        bool nolock_nograb_blocked() const
        {
          return nolock_nograb_connected() == false || blocked();
        }
        bool nolock_nograb_connected() const {return _connected;}
        // expose part of Lockable concept of mutex
        virtual void lock() = 0;
        virtual void unlock() = 0;

        // Slot refcount should be incremented while
        // a signal invocation is using the slot, in order
        // to prevent slot from being destroyed mid-invocation.
        // garbage_collecting_lock parameter enforces 
        // the existance of a lock before this
        // method is called
        template<typename Mutex>
        void inc_slot_refcount(const garbage_collecting_lock<Mutex> &)
        {
          BOOST_ASSERT(m_slot_refcount != 0);
          ++m_slot_refcount;
        }
        // if slot refcount decrements to zero due to this call, 
        // it puts a
        // shared_ptr to the slot in the garbage collecting lock,
        // which will destroy the slot only after it unlocks.
        template<typename Mutex>
        void dec_slot_refcount(garbage_collecting_lock<Mutex> &lock_arg) const
        {
          BOOST_ASSERT(m_slot_refcount != 0);
          if(--m_slot_refcount == 0)
          {
            lock_arg.add_trash(release_slot());
          }
        }

      protected:
        virtual shared_ptr<void> release_slot() const = 0;

        weak_ptr<void> _weak_blocker;
      private:
        mutable bool _connected;
        mutable unsigned m_slot_refcount;
      };

      template<typename GroupKey, typename SlotType, typename Mutex>
      class connection_body: public connection_body_base
      {
      public:
        typedef Mutex mutex_type;
        connection_body(const SlotType &slot_in, const boost::shared_ptr<mutex_type> &signal_mutex):
          m_slot(new SlotType(slot_in)), _mutex(signal_mutex)
        {
        }
        virtual ~connection_body() {}
        virtual bool connected() const
        {
          garbage_collecting_lock<mutex_type> local_lock(*_mutex);
          nolock_grab_tracked_objects(local_lock, detail::null_output_iterator());
          return nolock_nograb_connected();
        }
        const GroupKey& group_key() const {return _group_key;}
        void set_group_key(const GroupKey &key) {_group_key = key;}
        template<typename M>
        void disconnect_expired_slot(garbage_collecting_lock<M> &lock_arg)
        {
          if(!m_slot) return;
          bool expired = slot().expired();
          if(expired == true)
          {
            nolock_disconnect(lock_arg);
          }
        }
        template<typename M, typename OutputIterator>
        void nolock_grab_tracked_objects(garbage_collecting_lock<M> &lock_arg,
          OutputIterator inserter) const
        {
          if(!m_slot) return;
          slot_base::tracked_container_type::const_iterator it;
          for(it = slot().tracked_objects().begin();
            it != slot().tracked_objects().end();
            ++it)
          {
            void_shared_ptr_variant locked_object
            (
              apply_visitor
              (
                detail::lock_weak_ptr_visitor(),
                *it
              )
            );
            if(apply_visitor(detail::expired_weak_ptr_visitor(), *it))
            {
              nolock_disconnect(lock_arg);
              return;
            }
            *inserter++ = locked_object;
          }
        }
        // expose Lockable concept of mutex
        virtual void lock()
        {
          _mutex->lock();
        }
        virtual void unlock()
        {
          _mutex->unlock();
        }
        SlotType &slot()
        {
          return *m_slot;
        }
        const SlotType &slot() const
        {
          return *m_slot;
        }
      protected:
        virtual shared_ptr<void> release_slot() const
        {
          
          shared_ptr<void> released_slot = m_slot;
          m_slot.reset();
          return released_slot;
        }
      private:
        mutable boost::shared_ptr<SlotType> m_slot;
        const boost::shared_ptr<mutex_type> _mutex;
        GroupKey _group_key;
      };
    }

    class shared_connection_block;

    class connection
    {
    public:
      friend class shared_connection_block;

      connection() BOOST_NOEXCEPT {}
      connection(const connection &other) BOOST_NOEXCEPT: _weak_connection_body(other._weak_connection_body)
      {}
      connection(const boost::weak_ptr<detail::connection_body_base> &connectionBody) BOOST_NOEXCEPT:
        _weak_connection_body(connectionBody)
      {}
      
      // move support
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
      connection(connection && other) BOOST_NOEXCEPT: _weak_connection_body(std::move(other._weak_connection_body))
      {
        // make sure other is reset, in case it is a scoped_connection (so it
        // won't disconnect on destruction after being moved away from).
        other._weak_connection_body.reset();
      }
      connection & operator=(connection && other) BOOST_NOEXCEPT
      {
        if(&other == this) return *this;
        _weak_connection_body = std::move(other._weak_connection_body);
        // make sure other is reset, in case it is a scoped_connection (so it
        // won't disconnect on destruction after being moved away from).
        other._weak_connection_body.reset();
        return *this;
      }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
      connection & operator=(const connection & other) BOOST_NOEXCEPT
      {
        if(&other == this) return *this;
        _weak_connection_body = other._weak_connection_body;
        return *this;
      }

      ~connection() {}
      void disconnect() const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        if(connectionBody == 0) return;
        connectionBody->disconnect();
      }
      bool connected() const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        if(connectionBody == 0) return false;
        return connectionBody->connected();
      }
      bool blocked() const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        if(connectionBody == 0) return true;
        return connectionBody->blocked();
      }
      bool operator==(const connection& other) const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        boost::shared_ptr<detail::connection_body_base> otherConnectionBody(other._weak_connection_body.lock());
        return connectionBody == otherConnectionBody;
      }
      bool operator!=(const connection& other) const
      {
        return !(*this == other);
      }
      bool operator<(const connection& other) const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        boost::shared_ptr<detail::connection_body_base> otherConnectionBody(other._weak_connection_body.lock());
        return connectionBody < otherConnectionBody;
      }
      void swap(connection &other) BOOST_NOEXCEPT
      {
        using std::swap;
        swap(_weak_connection_body, other._weak_connection_body);
      }
    protected:

      boost::weak_ptr<detail::connection_body_base> _weak_connection_body;
    };
    inline void swap(connection &conn1, connection &conn2) BOOST_NOEXCEPT
    {
      conn1.swap(conn2);
    }

    class scoped_connection: public connection
    {
    public:
      scoped_connection() BOOST_NOEXCEPT {}
      scoped_connection(const connection &other) BOOST_NOEXCEPT:
        connection(other)
      {}
      ~scoped_connection()
      {
        disconnect();
      }
      scoped_connection& operator=(const connection &rhs) BOOST_NOEXCEPT
      {
        disconnect();
        connection::operator=(rhs);
        return *this;
      }

      // move support
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
      scoped_connection(scoped_connection && other) BOOST_NOEXCEPT: connection(std::move(other))
      {
      }
      scoped_connection(connection && other) BOOST_NOEXCEPT: connection(std::move(other))
      {
      }
      scoped_connection & operator=(scoped_connection && other) BOOST_NOEXCEPT
      {
        if(&other == this) return *this;
        disconnect();
        connection::operator=(std::move(other));
        return *this;
      }
      scoped_connection & operator=(connection && other) BOOST_NOEXCEPT
      {
        if(&other == this) return *this;
        disconnect();
        connection::operator=(std::move(other));
        return *this;
      }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

      connection release()
      {
        connection conn(_weak_connection_body);
        _weak_connection_body.reset();
        return conn;
      }
    private:
      scoped_connection(const scoped_connection &other);
      scoped_connection& operator=(const scoped_connection &rhs);
    };
    // Sun 5.9 compiler doesn't find the swap for base connection class when
    // arguments are scoped_connection, so we provide this explicitly.
    inline void swap(scoped_connection &conn1, scoped_connection &conn2) BOOST_NOEXCEPT
    {
      conn1.swap(conn2);
    }
  }
}

#endif  // BOOST_SIGNALS2_CONNECTION_HPP

/* connection.hpp
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
*/