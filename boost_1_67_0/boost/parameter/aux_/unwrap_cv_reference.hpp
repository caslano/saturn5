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
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
*/