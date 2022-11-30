// DEPRECATED in favor of adl_postconstruct and adl_predestruct with
// deconstruct<T>().
// A factory function for creating a shared_ptr that enhances the plain
// shared_ptr constructors by adding support for postconstructors
// and predestructors through the boost::signals2::postconstructible and
// boost::signals2::predestructible base classes.
//
// Copyright Frank Mori Hess 2007-2008.
//
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SIGNALS2_DECONSTRUCT_PTR_HPP
#define BOOST_SIGNALS2_DECONSTRUCT_PTR_HPP

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/signals2/postconstructible.hpp>
#include <boost/signals2/predestructible.hpp>
#include <boost/shared_ptr.hpp>

namespace boost
{
  namespace signals2
  {
    namespace detail
    {
      inline void do_postconstruct(const postconstructible *ptr)
      {
        postconstructible *nonconst_ptr = const_cast<postconstructible*>(ptr);
        nonconst_ptr->postconstruct();
      }
      inline void do_postconstruct(...)
      {
      }
      inline void do_predestruct(...)
      {
      }
      inline void do_predestruct(const predestructible *ptr)
      {
        BOOST_TRY
        {
          predestructible *nonconst_ptr = const_cast<predestructible*>(ptr);
          nonconst_ptr->predestruct();
        }
        BOOST_CATCH(...)
        {
          BOOST_ASSERT(false);
        }
        BOOST_CATCH_END
      }
    }

    template<typename T> class predestructing_deleter
    {
    public:
      void operator()(const T *ptr) const
      {
        detail::do_predestruct(ptr);
        checked_delete(ptr);
      }
    };

    template<typename T>
    shared_ptr<T> deconstruct_ptr(T *ptr)
    {
      if(ptr == 0) return shared_ptr<T>(ptr);
      shared_ptr<T> shared(ptr, boost::signals2::predestructing_deleter<T>());
      detail::do_postconstruct(ptr);
      return shared;
    }
    template<typename T, typename D>
    shared_ptr<T> deconstruct_ptr(T *ptr, D deleter)
    {
      shared_ptr<T> shared(ptr, deleter);
      if(ptr == 0) return shared;
      detail::do_postconstruct(ptr);
      return shared;
    }
  }
}

#endif // BOOST_SIGNALS2_DECONSTRUCT_PTR_HPP

/* deconstruct_ptr.hpp
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
*/