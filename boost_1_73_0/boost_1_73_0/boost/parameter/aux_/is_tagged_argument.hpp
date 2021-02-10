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
bL1EsIzEZJQJjeAZyeEokSIsY/68T6fR+FWmQZKHgppGaOxVc0GCKkieSk3mB2JePBTDUPTzAUsboCDHeU5kn7U9q+4F0WAqsapeoNJIDrZY3zcyICOHwjMkRiqIPRVFWpgt6mCPwAGbWQVibzIdEOCXdjK1veM2VXfpm+xKw8ZYyXABU5gPRw6AwSqI/YzabNvPI67TGaGYGJcOj08OqI1khT90Gy+1icIuT7UcpCiKwsHIZC5p+cD58o9rk0hVLCatxjf4Kt/JrXodgCmqHbHBnQxNTDvUnax37VsZOaUT2wrb0DA49MYWMOSE9SgH9jtBAYozwikZKpQuahV9RIiU+WHb2vW7wnU0yhAycsp8qbmkl1DPSw859e/BIDndydLDpHWTNl2asmaZmuGmSJa/W4VXlTmSw2yRpG37glerOwWAFn1rWOun0bvvHiabhFiy8GST/6XInr6VIcEAZ50qwyeTO1bochu8IyReZlqACAoQAUDYyFiurramyOEbqOxrC34mpWegbUwYGDb5izX62tqa6otEiznj3GiniRUMCg+l8mOZeI3NmYJr0fIyzQMq8M4mHsQiuLWHoLvf7YHVCA/obYhzK0do+ihLbpY4DGj/PqXiDochFdzvijKpGarqCnFr8CWAVVqv
*/