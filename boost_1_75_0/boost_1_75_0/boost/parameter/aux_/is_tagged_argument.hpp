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
Lw4eJBVsfCRqDnAekCWZad0dAI3sZ9CWGrPY4BLT+mRo8IQQHM7HzgSNHGICaerWZWMEBr/3JwUJjc6haMlt86dQDndiSdDqwxX2CvDxJTFje75acAv1+ovKdRwjtydgOqS7E4CQNBZHunhCiZA2WBv5SajppY9/f64k4ZK0CDgOiuTecLePE9zR0AfiqkcJjSEQoAuUft9B6MZz06jV6ADm06pC9hO3J9irchrEEEnYxNMoFFzokTTx0faXEbFBS+glw9tOZggK55/cfqneckhF/Lemef8ft1n+F7eFBP5Z1nF1svCw+ze08X0ASp6yHk1VLdZLyQwfngxGvzsNpfMMu3MrBVXfMs4PeKnt/jMsbwLyODcsU3h7O3P1WmAJkGS9d4uyt+9am1qWbkx89luK8Zc9bgkPjPRfaTklXnhxAE9q4p6ckIf+QgOL46fuuos0iY027/OxTIkEiWvxxscSPl6fc5MEU4R6VqqXNnWXbnmhu1Lm1Bsdma/ygWDdNy9Ot3+7QFx0H7CmelpFDt2AO+OWpujVz/TQq76K9BipC5k4dMojXCB1Zu2Z2yEsvm+UBTp5aECdL8Z+UKZ0iB8syZ1X1KXtaVYc07PXHPi47ySQTeJRXa1jVY6pd6UWWvxlcLVOyBH/lkk1nYUjNMAJG+k43Go1nhk3BoqNGPFXqNsQmeoa9lawu5WU0uGhDj3AnUxYuiJGy0ga
*/