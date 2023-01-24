// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_DEDUCED_HPP
#define BOOST_PARAMETER_DEDUCED_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.
    //
    // If a keyword k is specified with deduced<...>, that keyword
    // will be automatically deduced from the argument list.
    template <typename Tag>
    struct deduced
    {
        typedef Tag key_type;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_deduced_aux
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag>
    struct is_deduced_aux< ::boost::parameter::deduced<Tag> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };

    template <typename T>
    struct is_deduced0
      : ::boost::parameter::aux::is_deduced_aux<typename T::key_type>::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/if.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    //
    // tag_type, has_default, and predicate --
    //
    // These metafunctions accept a ParameterSpec and extract the
    // keyword tag, whether or not a default is supplied for the
    // parameter, and the predicate that the corresponding actual
    // argument type is required match.
    //
    // a ParameterSpec is a specialization of either keyword<...>,
    // required<...>, optional<...>
    //

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using has_default = ::boost::mp11::mp_if<
        ::boost::parameter::aux::is_required<T>
      , ::boost::mp11::mp_false
      , ::boost::mp11::mp_true
    >;
#else
    struct has_default
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_required<T>
          , ::boost::mpl::false_
          , ::boost::mpl::true_
        >::type
    {
    };
#endif

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using is_deduced = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required<T>
        >
      , ::boost::parameter::aux::is_deduced0<T>
      , ::boost::mp11::mp_false
    >;
#else
    struct is_deduced
      : ::boost::mpl::if_<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::is_deduced0<T>
          , ::boost::mpl::false_
        >::type
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* deduced.hpp
ihABa8uGsWL1rXLA2hlh3X3iryG/z0ouNZhkkNRN+qNI8AUD4QlV0OUzrgE+pNS3mN3U34IFjTQDKLlLak8Ziljvp0sKlB6nIoWPm/B2AqxvSaueHAci5VQyn25Jf3pV8+xf30tuJfp7VNC6y98CdFb5srwLhvSjyfmVNT4ZhyCqFdZz13GfHQ91en9//4/fS0/n33v7AbwvrvumO1bwKdHOP7p9H2H2Y0qUrwC8vpYlXQwR3vnzZhblL8+QbT9krrzn2p/+uFvtZPMvhvdSqV46aSOaiDFlaka7X06RX7kGMZZp/H2paowZ3dUWh7nVZT5m83e1mA6rAdnpnp/45es9E6vXj4SlzjDkkYc8eJ7UqDn6weL1Hrcoco9grtduEIvuHIXN7KOxUE5rirxonShipabURSrkCWOvb38gL1kUb9e1XenWRpWvgVxwgWqSK+txSAkdGSQRF4GzXn0GEBnr2nisL8uhToMSYx4sM58U6GNZOcAddntiTEcwoeNmH4aIp+4rPOa7yscvN5/h6OOS4cW5TQhnwB/4cJI9jFoBQ5u4xICpiPgGWtoDpiw82v4lBrYXg4HWY7oynx7F/7V9ekMQwK4/hpsps8UyCMT1oPP4FkkB5Ln8/kOYTqASN5TPern9dcpJCr/rZmIAJyiysellDTlpjQQ3X9hl/M2NUmxfahAv0qEUtRrO3y2kNVpKbjM/+iU9rHqP
*/