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