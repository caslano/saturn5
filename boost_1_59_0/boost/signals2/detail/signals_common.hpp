// Boost.Signals library

// Copyright Douglas Gregor 2001-2004.
// Copyright Frank Mori Hess 2007. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_SIGNALS_COMMON_HPP
#define BOOST_SIGNALS2_SIGNALS_COMMON_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>
#include <boost/signals2/signal_base.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost {
  namespace signals2 {
    namespace detail {
      // Determine if the given type T is a signal
      template<typename T>
      class is_signal: public mpl::bool_<is_base_of<signal_base, T>::value>
      {};

      // A slot can be a signal, a reference to a function object, or a
      // function object.
      struct signal_tag {};
      struct reference_tag {};
      struct value_tag {};

      // Classify the given slot as a signal, a reference-to-slot, or a
      // standard slot
      template<typename S>
      class get_slot_tag {
        typedef typename mpl::if_<is_signal<S>,
          signal_tag, value_tag>::type signal_or_value;
      public:
        typedef typename mpl::if_<is_reference_wrapper<S>,
                            reference_tag,
                            signal_or_value>::type type;
      };

      // Get the slot so that it can be copied
      template<typename F>
      typename F::weak_signal_type
      get_invocable_slot(const F &signal, signal_tag)
      { return typename F::weak_signal_type(signal); }

      template<typename F>
      const F&
      get_invocable_slot(const F& f, reference_tag)
      { return f; }

      template<typename F>
      const F&
      get_invocable_slot(const F& f, value_tag)
      { return f; }

      // Determines the type of the slot - is it a signal, a reference to a
      // slot or just a normal slot.
      template<typename F>
      typename get_slot_tag<F>::type
      tag_type(const F&)
      {
        typedef typename get_slot_tag<F>::type
          the_tag_type;
        the_tag_type tag = the_tag_type();
        return tag;
      }
    } // end namespace detail
  } // end namespace signals2
} // end namespace boost

#endif // BOOST_SIGNALS2_SIGNALS_COMMON_HPP

/* signals_common.hpp
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
*/