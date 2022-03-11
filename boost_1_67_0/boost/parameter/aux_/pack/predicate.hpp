// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_PACK_PREDICATE_HPP

namespace boost { namespace parameter { namespace aux {

    // helper for get_predicate<...>, below
    template <typename T>
    struct get_predicate_or_default
    {
        typedef T type;
    };

    // helper for predicate<...>, below
    template <typename T>
    struct get_predicate
      : ::boost::parameter::aux
        ::get_predicate_or_default<typename T::predicate>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/use_default.hpp>
#include <boost/parameter/aux_/always_true_predicate.hpp>

namespace boost { namespace parameter { namespace aux {

    template <>
    struct get_predicate_or_default< ::boost::parameter::aux::use_default>
    {
        typedef ::boost::parameter::aux::always_true_predicate type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using predicate = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required<T>
        >
      , ::boost::parameter::aux::get_predicate<T>
      , ::boost::mp11::mp_identity<
            ::boost::parameter::aux::always_true_predicate
        >
    >;
#else
    struct predicate
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::get_predicate<T>
          , ::boost::mpl::identity<
                ::boost::parameter::aux::always_true_predicate
            >
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* predicate.hpp
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
*/