// Boost.Signals2 library

// Copyright Douglas Gregor 2001-2004.
// Copyright Frank Mori Hess 2007-2008.
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_SLOT_CALL_ITERATOR_HPP
#define BOOST_SIGNALS2_SLOT_CALL_ITERATOR_HPP

#include <boost/assert.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/optional.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/signals2/connection.hpp>
#include <boost/signals2/slot_base.hpp>
#include <boost/signals2/detail/auto_buffer.hpp>
#include <boost/signals2/detail/unique_lock.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/weak_ptr.hpp>

namespace boost {
  namespace signals2 {
    namespace detail {
      template<typename ResultType, typename Function>
        class slot_call_iterator_cache
      {
      public:
        slot_call_iterator_cache(const Function &f_arg):
          f(f_arg),
          connected_slot_count(0),
          disconnected_slot_count(0),
          m_active_slot(0)
        {}

        ~slot_call_iterator_cache()
        {
          if(m_active_slot)
          {
            garbage_collecting_lock<connection_body_base> lock(*m_active_slot);
            m_active_slot->dec_slot_refcount(lock);
          }
        }

        template<typename M>
        void set_active_slot(garbage_collecting_lock<M> &lock,
          connection_body_base *active_slot)
        {
          if(m_active_slot)
            m_active_slot->dec_slot_refcount(lock);
          m_active_slot = active_slot;
          if(m_active_slot)
            m_active_slot->inc_slot_refcount(lock);
        }

        optional<ResultType> result;
        typedef auto_buffer<void_shared_ptr_variant, store_n_objects<10> > tracked_ptrs_type;
        tracked_ptrs_type tracked_ptrs;
        Function f;
        unsigned connected_slot_count;
        unsigned disconnected_slot_count;
        connection_body_base *m_active_slot;
      };

      // Generates a slot call iterator. Essentially, this is an iterator that:
      //   - skips over disconnected slots in the underlying list
      //   - calls the connected slots when dereferenced
      //   - caches the result of calling the slots
      template<typename Function, typename Iterator, typename ConnectionBody>
      class slot_call_iterator_t
        : public boost::iterator_facade<slot_call_iterator_t<Function, Iterator, ConnectionBody>,
        typename Function::result_type,
        boost::single_pass_traversal_tag,
        typename boost::add_reference<typename boost::add_const<typename Function::result_type>::type>::type >
      {
        typedef boost::iterator_facade<slot_call_iterator_t<Function, Iterator, ConnectionBody>,
          typename Function::result_type,
          boost::single_pass_traversal_tag,
          typename boost::add_reference<typename boost::add_const<typename Function::result_type>::type>::type >
        inherited;

        typedef typename Function::result_type result_type;

        typedef slot_call_iterator_cache<result_type, Function> cache_type;

        friend class boost::iterator_core_access;

      public:
        slot_call_iterator_t(Iterator iter_in, Iterator end_in,
          cache_type &c):
          iter(iter_in), end(end_in),
          cache(&c), callable_iter(end_in)
        {
          lock_next_callable();
        }

        typename inherited::reference
        dereference() const
        {
          if (!cache->result) {
            BOOST_TRY
            {
              cache->result.reset(cache->f(*iter));
            }
            BOOST_CATCH(expired_slot &)
            {
              (*iter)->disconnect();
              BOOST_RETHROW
            }
            BOOST_CATCH_END
          }
          return cache->result.get();
        }

        void increment()
        {
          ++iter;
          lock_next_callable();
          cache->result.reset();
        }

        bool equal(const slot_call_iterator_t& other) const
        {
          return iter == other.iter;
        }

      private:
        typedef garbage_collecting_lock<connection_body_base> lock_type;

        void set_callable_iter(lock_type &lock, Iterator newValue) const
        {
          callable_iter = newValue;
          if(callable_iter == end)
            cache->set_active_slot(lock, 0);
          else
            cache->set_active_slot(lock, (*callable_iter).get());
        }

        void lock_next_callable() const
        {
          if(iter == callable_iter)
          {
            return;
          }
  
          for(;iter != end; ++iter)
          {
            cache->tracked_ptrs.clear();
            lock_type lock(**iter);
            (*iter)->nolock_grab_tracked_objects(lock, std::back_inserter(cache->tracked_ptrs));
            if((*iter)->nolock_nograb_connected())
            {
              ++cache->connected_slot_count;
            }else
            {
              ++cache->disconnected_slot_count;
            }
            if((*iter)->nolock_nograb_blocked() == false)
            {
              set_callable_iter(lock, iter);
              break;
            }
          }
          
          if(iter == end)
          {
            if(callable_iter != end)
            {
              lock_type lock(**callable_iter);
              set_callable_iter(lock, end);
            }
          }
        }

        mutable Iterator iter;
        Iterator end;
        cache_type *cache;
        mutable Iterator callable_iter;
      };
    } // end namespace detail
  } // end namespace BOOST_SIGNALS_NAMESPACE
} // end namespace boost

#endif // BOOST_SIGNALS2_SLOT_CALL_ITERATOR_HPP

/* slot_call_iterator.hpp
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
*/