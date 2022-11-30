// Boost.Signals2 library

// Copyright Frank Mori Hess 2007-2008.
// Copyright Timmo Stange 2007.
// Copyright Douglas Gregor 2001-2004. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_SLOT_BASE_HPP
#define BOOST_SIGNALS2_SLOT_BASE_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/signals2/detail/foreign_ptr.hpp>
#include <boost/signals2/expired_slot.hpp>
#include <boost/signals2/signal_base.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/variant.hpp>
#include <vector>

namespace boost
{
  namespace signals2
  {
    namespace detail
    {
      class tracked_objects_visitor;
      class trackable_pointee;

      typedef boost::variant<boost::weak_ptr<trackable_pointee>, boost::weak_ptr<void>, detail::foreign_void_weak_ptr > void_weak_ptr_variant;
      typedef boost::variant<boost::shared_ptr<void>, detail::foreign_void_shared_ptr > void_shared_ptr_variant;
      class lock_weak_ptr_visitor
      {
      public:
        typedef void_shared_ptr_variant result_type;
        template<typename WeakPtr>
        result_type operator()(const WeakPtr &wp) const
        {
          return wp.lock();
        }
        // overload to prevent incrementing use count of shared_ptr associated
        // with signals2::trackable objects
        result_type operator()(const weak_ptr<trackable_pointee> &) const
        {
          return boost::shared_ptr<void>();
        }
      };
      class expired_weak_ptr_visitor
      {
      public:
        typedef bool result_type;
        template<typename WeakPtr>
        bool operator()(const WeakPtr &wp) const
        {
          return wp.expired();
        }
      };
    }

    class slot_base
    {
    public:
      typedef std::vector<detail::void_weak_ptr_variant> tracked_container_type;
      typedef std::vector<detail::void_shared_ptr_variant> locked_container_type;

      const tracked_container_type& tracked_objects() const {return _tracked_objects;}
      locked_container_type lock() const
      {
        locked_container_type locked_objects;
        tracked_container_type::const_iterator it;
        for(it = tracked_objects().begin(); it != tracked_objects().end(); ++it)
        {
          locked_objects.push_back(apply_visitor(detail::lock_weak_ptr_visitor(), *it));
          if(apply_visitor(detail::expired_weak_ptr_visitor(), *it))
          {
            boost::throw_exception(expired_slot());
          }
        }
        return locked_objects;
      }
      bool expired() const
      {
        tracked_container_type::const_iterator it;
        for(it = tracked_objects().begin(); it != tracked_objects().end(); ++it)
        {
          if(apply_visitor(detail::expired_weak_ptr_visitor(), *it)) return true;
        }
        return false;
      }
    protected:
      friend class detail::tracked_objects_visitor;

      void track_signal(const signal_base &signal)
      {
        _tracked_objects.push_back(signal.lock_pimpl());
      }

      tracked_container_type _tracked_objects;
    };
  }
} // end namespace boost

#endif // BOOST_SIGNALS2_SLOT_BASE_HPP

/* slot_base.hpp
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
*/