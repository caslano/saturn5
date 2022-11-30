// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_HAS_NESTED_TEMPLATE_FN_HPP
#define BOOST_PARAMETER_AUX_HAS_NESTED_TEMPLATE_FN_HPP

#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    template <template <typename ...> class F>
    struct has_nested_template_fn_variadic
    {
    };
#else
    template <template <typename P0, typename P1> class F>
    struct has_nested_template_fn_arity_2
    {
    };
#endif

    template <typename T>
    class has_nested_template_fn_impl
    {
        template <typename U>
        static ::boost::parameter::aux::no_tag _check(...);

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename U>
        static ::boost::parameter::aux::yes_tag
            _check(
                ::boost::mp11::mp_identity<U> const volatile*
              , ::boost::parameter::aux::has_nested_template_fn_variadic<
                    U::template fn
                >* = BOOST_PARAMETER_AUX_PP_NULLPTR
            );
#else
        template <typename U>
        static BOOST_CONSTEXPR ::boost::parameter::aux::yes_tag
            _check(
                ::boost::mpl::identity<U> const volatile*
              , ::boost::parameter::aux::has_nested_template_fn_arity_2<
                    U::template fn
                >* = BOOST_PARAMETER_AUX_PP_NULLPTR
            );
#endif

     public:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_bool<
#else
        typedef ::boost::mpl::bool_<
#endif
            sizeof(
                ::boost::parameter::aux::has_nested_template_fn_impl<T>
                ::template _check<T>(
                    static_cast<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                        ::boost::mp11::mp_identity<T> const volatile*
#else
                        ::boost::mpl::identity<T> const volatile*
#endif
                    >(BOOST_PARAMETER_AUX_PP_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::yes_tag)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        > type;
#endif
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/type_traits/remove_const.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using has_nested_template_fn = typename ::boost::parameter::aux
    ::has_nested_template_fn_impl<typename ::std::remove_const<T>::type>
    ::type;
#else
    struct has_nested_template_fn
      : ::boost::parameter::aux::has_nested_template_fn_impl<
            typename ::boost::remove_const<T>::type
        >::type
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard


/* has_nested_template_fn.hpp
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
*/