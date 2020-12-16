// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_UNWRAP_CV_REFERENCE_HPP
#define BOOST_PARAMETER_AUX_UNWRAP_CV_REFERENCE_HPP

namespace boost {

    template <typename T>
    class reference_wrapper;
} // namespace boost

#include <boost/parameter/aux_/yesno.hpp>

namespace boost { namespace parameter { namespace aux {

    //
    // reference_wrapper support -- if perfect forwarding is unsupported,
    // then when passing arguments positionally by non-const reference,
    // we ask users of named parameter interfaces to use ref(x) to wrap them.
    //

    template <typename U>
    ::boost::parameter::aux::yes_tag
        is_cv_reference_wrapper_check(
            ::boost::reference_wrapper<U> const volatile*
        );

    ::boost::parameter::aux::no_tag is_cv_reference_wrapper_check(...);
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)
#include <functional>

namespace boost { namespace parameter { namespace aux {

    // Support for std::ref(x) -- Cromwell D. Enage
    template <typename U>
    ::boost::parameter::aux::yes_tag
        is_cv_reference_wrapper_check(
            ::std::reference_wrapper<U> const volatile*
        );
}}} // namespace boost::parameter::aux
#endif

#include <boost/parameter/aux_/preprocessor/nullptr.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11) && !( \
        BOOST_WORKAROUND(BOOST_MSVC, >= 1900) && \
        BOOST_WORKAROUND(BOOST_MSVC, < 1910) \
    )
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11) || MSVC-14.0
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_reference.hpp>
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(BOOST_GCC, < 40000)
#include <boost/mpl/eval_if.hpp>
#endif
#endif  // BOOST_PARAMETER_CAN_USE_MP11 && not MSVC-14.0

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_CAN_USE_MP11) && !( \
        BOOST_WORKAROUND(BOOST_MSVC, >= 1900) && \
        BOOST_WORKAROUND(BOOST_MSVC, < 1910) \
    )
    // This metafunction returns mp11::mp_true if T is of type
    // reference_wrapper<U> cv.
    template <typename T>
    using is_cv_reference_wrapper = ::boost::mp11::mp_bool<
        sizeof(
            ::boost::parameter::aux::is_cv_reference_wrapper_check(
                static_cast<
                    typename ::std::remove_reference<T>::type*
                >(BOOST_PARAMETER_AUX_PP_NULLPTR)
            )
        ) == sizeof(::boost::parameter::aux::yes_tag)
    >;

    // Needed for unwrap_cv_reference below. T might be const, so
    // mp_eval_if<> might fail because of deriving from T const on EDG.
    template <typename T>
    using unwrap_cv_reference_impl = typename ::std::remove_reference<T>::type;

    // Produces the unwrapped type to hold a reference to in
    // tagged_argument<>.  Can't use boost::unwrap_reference<> here
    // because it doesn't handle the case where T = reference_wrapper<U> cv.
    template <typename T>
    using unwrap_cv_reference = ::boost::mp11::mp_eval_if<
        ::boost::parameter::aux::is_cv_reference_wrapper<T>
      , ::boost::parameter::aux::unwrap_cv_reference_impl<T>
      , ::std::remove_reference
      , T
    >;
#else  // !defined(BOOST_PARAMETER_CAN_USE_MP11) || MSVC-14.0
    // This metafunction returns mpl::true_ if T is of type
    // reference_wrapper<U> cv.
    template <typename T>
    struct is_cv_reference_wrapper
    {
        BOOST_STATIC_CONSTANT(
            bool, value = (
                sizeof(
                    ::boost::parameter::aux::is_cv_reference_wrapper_check(
                        static_cast<
                            typename ::boost::remove_reference<T>::type*
                        >(BOOST_PARAMETER_AUX_PP_NULLPTR)
                    )
                ) == sizeof(::boost::parameter::aux::yes_tag)
            )
        );

        typedef boost::mpl::bool_<
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
            is_cv_reference_wrapper::
#endif 
        value> type;
    };

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) || \
    BOOST_WORKAROUND(BOOST_GCC, < 40000)
    template <
        typename T
      , typename = typename ::boost::parameter::aux
        ::is_cv_reference_wrapper<T>::type
    >
    struct unwrap_cv_reference : ::boost::remove_reference<T>
    {
    };

    template <typename T>
    struct unwrap_cv_reference<T const,::boost::mpl::false_>
    {
        typedef T const type;
    };

    template <typename T>
    struct unwrap_cv_reference<T,::boost::mpl::true_> : T
    {
    };
#else   // no Borland or GCC 3- workarounds needed
    // Needed for unwrap_cv_reference below. T might be const, so
    // eval_if<> might fail because of deriving from T const on EDG.
    template <typename T>
    struct unwrap_cv_reference_impl : ::boost::remove_reference<T>::type
    {
    };

    // Produces the unwrapped type to hold a reference to in
    // tagged_argument<>.  Can't use boost::unwrap_reference<> here
    // because it doesn't handle the case where T = reference_wrapper<U> cv.
    template <typename T>
    struct unwrap_cv_reference
      : ::boost::mpl::eval_if<
            ::boost::parameter::aux::is_cv_reference_wrapper<T>
          , ::boost::parameter::aux::unwrap_cv_reference_impl<T>
          , ::boost::remove_reference<T>
        >
    {
    };
#endif  // Borland or GCC 3- workarounds needed
#endif  // BOOST_PARAMETER_CAN_USE_MP11 && not MSVC-14.0
}}} // namespace boost::parameter::aux

#endif  // include guard


/* unwrap_cv_reference.hpp
b+O22Hj2oZjBJj6zY6OpNhlUnu7xpbFx/pRuGKQpw8HxU+NnxQ+N7RzVMTY9qlt839j2/ra+2KSo9myP3I+K1o68H0fZMsr1durY/bJf8IsE9H1+jyIxLsW/6qTA9aLEwO/fwGOIEd63VdpUVNnPebzJiCN5lCJ77SSo6xxfJ3ZliybfDHu3KHurxJ6soVV67fV+mHEqbRZ7pnva6PVsBcrMr9fwNys7daRemceRn3qP5SskPI7yovL2kLnfsDo13crbdYYd8rWKnS8OEqaUIP/6elM9i/H1m4H9UckjM45mnfZInW7mntGWbYwlbcm/0WptbOM2f0yn0PX5orcJvTFqrf/aeY7zfrTOLnQqMfO3XVvu2H9A6xwW/3Bnp9Mv+7k9YzFLQKDK//adAjxTro02Jznadd39FJKPeIxT6xc7q7ockxioPyzRq5X2SLez0j6o9kjW0+s6n6jqZEGaMlM6p7guVNeqPqh14N9WblPiZN38Q3K9nOugdk02ux7sRQ/2h0a71tw7qF0zKnW4hs3Zruny7esTOHvDpU3DfWebZnjhvqZedF3rUTIcqvx5O2x92dgnuL7czrWzvhzHzF5f1vdpub60UTodvaerH2lK52PPMurHc4TB6T71Q69ZTVdmn3gcdUOVmW6U1V20Q03xUlajO/hj2/pjyLPQ+iG6O+PN+tH4Y0f90DqH4s360fiso35onVPxun50cfr1RdpFWQcb7txpVUdOqjTxlFRXlQbqTJ/W1JlAmaLOqDS09+ujzefTDgEPb5bnvk3ICuP5NEOX/5KGGv2wZy/ry+3n8WxR+sWeae77l4t7XrFvlSWzz16l7m+ktWVXe+dZc1KWvqd0LmIMNsZW1lVfq/eQ2qN0JvH82kbv4faAMhvp6YipylPq/AEybSx544/BL8feLT1EJ5q0+S1m/ughfm+sPy7K7830M5mrA/o+9H+egIgd090BHaQ8tVvscS1P6MxB57DhbptJWmevQ6emgzzPxl/ueJbV+/ZT1nT5avGsYUdZIe+C9w8p7xhQzhVLE5HuJGhmX10O3N5RVD6VJQSfB5mt7OS4lQPci+x9pYOEt0zWItvb7DckrAPEQn9kC+nQGBzW0lUFJUX1RQX5xovpgoXz5p+tXmHUC6xO0192avlZ2Z5OTUmBG/nSXyyCVWmUHe237LOhE0rqoKOdd0kb3AjfzqfAN9X9TK9bO98F/lXd76va45o0s26wr0ldue4rTiqdHl5HPdR91nvqfm9vuDb4KGmfjL1xqj3s6o9J9UfZ9+sb00nKqOiOTTTrWeMGRz3TOkvQOSvQTu8wdR5PCtZpRCcnWT3HTDB1hjj82poodabD2p6OOqN19iWa9bPxRbf6iY5qm8er5y+rT3g0ya29D9vWUzeD2/pF0t5Hh6uj0t7/tV9we/9KP0d7H0HbbpbVPZ1C3+kPdyds/XVZdXmfb3l/gpr+rXuXR1+/y28iTeo7hX+XN/K0ptMXf5d37GVw2vf40XL+zxzZZGKJpNeFhqTRtgTSy/Ud/vy04L6wC/yx0p9CPrj3hbjnfK/X/df31L3B9F5e17QUu2H7vwNiv6fRR0r/91dlFq36vr2k7f5kqQPxY0L7KNFpTjbrbRdH/6j7H8p8+P4nLkz/Q3pJ/+M63qDPvDwpeRGDmFyN3fQBKi8qywPN+txJ55ytzosx86NG5UdlOZcuaS/2+U+3Iadt/9OD9v6oMcIubtvDejglNKxXoJvpEtaKqjreIiILa6YZVslrxj1cy4TW023V54uTmR/4hVlJUN3Y2yU0jg3YzXWJY1XpZSp+tSp+5WVVYeKHXV2W65RusdJ1iaPW1f1MK/KtVsVRhUM=
*/