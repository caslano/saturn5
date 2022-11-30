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
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564)) && \
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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
            is_cv_reference_wrapper::
#endif 
        value> type;
    };

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564)) || \
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
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
*/