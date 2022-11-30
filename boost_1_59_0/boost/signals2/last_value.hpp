// last_value function object (documented as part of Boost.Signals)

// Copyright Frank Mori Hess 2007.
// Copyright Douglas Gregor 2001-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_LAST_VALUE_HPP
#define BOOST_SIGNALS2_LAST_VALUE_HPP

#include <boost/core/no_exceptions_support.hpp>
#include <boost/optional.hpp>
#include <boost/signals2/expired_slot.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace boost {
  namespace signals2 {

    // no_slots_error is thrown when we are unable to generate a return value
    // due to no slots being connected to the signal.
    class no_slots_error: public std::exception
    {
    public:
      virtual const char* what() const throw() {return "boost::signals2::no_slots_error";}
    };

    template<typename T>
    class last_value {
    public:
      typedef T result_type;

      template<typename InputIterator>
      T operator()(InputIterator first, InputIterator last) const
      {
        if(first == last)
        {
          boost::throw_exception(no_slots_error());
        }
        optional<T> value;
        while (first != last)
        {
          BOOST_TRY
          {
            value = *first;
          }
          BOOST_CATCH(const expired_slot &) {}
          BOOST_CATCH_END
          ++first;
        }
        if(value) return value.get();
        boost::throw_exception(no_slots_error());
      }
    };

    template<>
    class last_value<void> {
    public:
      typedef void result_type;
      template<typename InputIterator>
        result_type operator()(InputIterator first, InputIterator last) const
      {
        while (first != last)
        {
          BOOST_TRY
          {
            *first;
          }
          BOOST_CATCH(const expired_slot &) {}
          BOOST_CATCH_END
          ++first;
        }
        return;
      }
    };
  } // namespace signals2
} // namespace boost
#endif // BOOST_SIGNALS2_LAST_VALUE_HPP

/* last_value.hpp
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
*/