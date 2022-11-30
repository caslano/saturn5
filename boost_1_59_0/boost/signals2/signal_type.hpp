/*
  A meta function which supports using named template type parameters
  via Boost.Parameter to specify the template type parameters for
  the boost::signals2::signal class.

  Author: Frank Mori Hess <fmhess@users.sourceforge.net>
  Begin: 2009-01-22
*/
// Copyright Frank Mori Hess 2009
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_SIGNAL_TYPE_HPP
#define BOOST_SIGNALS2_SIGNAL_TYPE_HPP

#include <boost/parameter/config.hpp>

#if BOOST_PARAMETER_MAX_ARITY < 7
#error Define BOOST_PARAMETER_MAX_ARITY as 7 or greater.
#endif

#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>
#include <boost/parameter/value_type.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/signals2/signal.hpp>
#include <functional>

namespace boost
{
  namespace signals2
  {
    namespace keywords
    {
      BOOST_PARAMETER_TEMPLATE_KEYWORD(signature_type)
      BOOST_PARAMETER_TEMPLATE_KEYWORD(combiner_type)
      BOOST_PARAMETER_TEMPLATE_KEYWORD(group_type)
      BOOST_PARAMETER_TEMPLATE_KEYWORD(group_compare_type)
      BOOST_PARAMETER_TEMPLATE_KEYWORD(slot_function_type)
      BOOST_PARAMETER_TEMPLATE_KEYWORD(extended_slot_function_type)
      BOOST_PARAMETER_TEMPLATE_KEYWORD(mutex_type)
    } // namespace keywords

    template <
        typename A0,
        typename A1 = parameter::void_,
        typename A2 = parameter::void_,
        typename A3 = parameter::void_,
        typename A4 = parameter::void_,
        typename A5 = parameter::void_,
        typename A6 = parameter::void_
      >
    class signal_type
    {
      typedef parameter::parameters<
          parameter::required<keywords::tag::signature_type, is_function<boost::mpl::_> >,
          parameter::optional<keywords::tag::combiner_type>,
          parameter::optional<keywords::tag::group_type>,
          parameter::optional<keywords::tag::group_compare_type>,
          parameter::optional<keywords::tag::slot_function_type>,
          parameter::optional<keywords::tag::extended_slot_function_type>,
          parameter::optional<keywords::tag::mutex_type>
        > parameter_spec;

    public:
      // ArgumentPack
      typedef typename parameter_spec::bind<A0, A1, A2, A3, A4, A5, A6>::type
        args;

      typedef typename parameter::value_type<args, keywords::tag::signature_type>::type
        signature_type;

      typedef typename parameter::value_type
        <
          args,
          keywords::tag::combiner_type,
          optional_last_value
            <
              typename boost::function_traits<signature_type>::result_type
            >
        >::type combiner_type;

      typedef typename
        parameter::value_type<args, keywords::tag::group_type, int>::type group_type;

      typedef typename
        parameter::value_type<args, keywords::tag::group_compare_type, std::less<group_type> >::type
        group_compare_type;

      typedef typename
        parameter::value_type<args, keywords::tag::slot_function_type, function<signature_type> >::type
        slot_function_type;

      typedef typename
        parameter::value_type
          <
            args,
            keywords::tag::extended_slot_function_type,
            typename detail::extended_signature<function_traits<signature_type>::arity, signature_type>::function_type
          >::type
          extended_slot_function_type;

      typedef typename
        parameter::value_type<args, keywords::tag::mutex_type, mutex>::type mutex_type;

      typedef signal
        <
          signature_type,
          combiner_type,
          group_type,
          group_compare_type,
          slot_function_type,
          extended_slot_function_type,
          mutex_type
        > type;
    };
  } // namespace signals2
} // namespace boost

#endif // BOOST_SIGNALS2_SIGNAL_TYPE_HPP

/* signal_type.hpp
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
*/