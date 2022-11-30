// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_TAGGED_ARGUMENT_HPP
#define BOOST_PARAMETER_IS_TAGGED_ARGUMENT_HPP

namespace boost { namespace parameter { namespace aux {

    struct tagged_argument_base
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) || \
    (0 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY)
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    // This metafunction identifies tagged_argument specializations
    // and their derived classes.
    template <typename T>
    struct is_tagged_argument
      : ::boost::mpl::if_<
            // Cannot use is_convertible<> to check if T is derived from
            // tagged_argument_base. -- Cromwell D. Enage
            ::boost::is_base_of<
                ::boost::parameter::aux::tagged_argument_base
              , typename ::boost::remove_const<
                    typename ::boost::remove_reference<T>::type
                >::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#else   // no perfect forwarding support and no exponential overloads
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_tagged_argument_aux
      : ::boost::is_convertible<
            T*
          , ::boost::parameter::aux::tagged_argument_base const*
        >
    {
    };

    // This metafunction identifies tagged_argument specializations
    // and their derived classes.
    template <typename T>
    struct is_tagged_argument
      : ::boost::mpl::if_<
            ::boost::is_lvalue_reference<T>
          , ::boost::mpl::false_
          , ::boost::parameter::aux::is_tagged_argument_aux<T>
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // perfect forwarding support, or exponential overloads

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_tagged_argument_mp11 = ::std::is_base_of<
        ::boost::parameter::aux::tagged_argument_base
      , typename ::std::remove_const<
            typename ::std::remove_reference<T>::type
        >::type
    >;
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_tagged_argument.hpp
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
*/