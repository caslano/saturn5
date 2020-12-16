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
fGo+NZ+aT83nP//82fb/iZkZKX+E/b9mq70/hPH/GO2+2hFzXOLcpGx1//8W+86M0/fNxSB4QZotMTU5237/f5b79evl/v+4DKUbShk0sLAvmHuWRer+X7vtHzJu7PC4ITGxcYkcFXMN6QmzspVtfHdlx56YaMvRwg3y0yI8qcLVM7OBlzjdVNh5Fi2sikv59TL49brk93fnFRw27lpeGktecFPxaWk0ljSUfbMcc47YsB+StN5CgwhvWXzlMadgfJudarnieIM53iYEqaPC7OE9m+78/kdty2Zz+3+Jm5KRY9cssPyJI4hv16p9N1o6Y4UWqLmxNVW5pVraWLyx/fJQ4X5SJZGowgVox6b8hHFs9VW4AD2c1dKeI7tB0ntBhbPqddRX+fFV8fjxrZfa7kDOm3BcY/wq3Lhno4zm+mu/jWb1ce/g0yDAYL//mq/dXt4xD/Q97akSnTOZB/J1ob6MdRMvtu7JyPF7qT3xa1liUjdZyZq3K9uilE9tFSbOvD6WyHoMjncJBxHgIcdbf5DT45ztq+uK4/Rx8Tgda1FOeVy5jqIvfnNNjjMjeYF+jBYLi1ssl863e5V/Dz3Pbfxdm4tznP/txf48W+xAs9ARrh8FJvlgOUi3OGtWckpaTtUy19vyWyrccOwja5mWO/HKNUC1S74RoeF4CtX+JqbXBGNYqyo/21wr/wPlXPyr2j+H43fDftJPt13PdFJnXi7UmeNaQl5xI69Vyi9U7OnrO9qBXD/Dl5qWn1w9zdusv9bWVbi6ZmVHnK5fP8OX/nnXz1ApuDkS0WzUn/ARTo6ZXsjp8Q5VYWaZHm+E4Xi9VVshJmkrjWCk2p9oevwRf8Dxe6s6J80qdR5W98rjH0D4MufHH0fETsvgWDVlUGYoAx8/LSxBDWVQXk0ZlP0BZUCauOEkZdBdyiDKW67vjvEDjCB8/LLLy4DRxxXH3VbO17uU308tWn83EI1DySgDPYlMyoP4q14/SAH3lnL92ar2v6x6xXA0iBHWOHg7ofWyMcQj5WaIb35C+rxkS7D0IUeVvwTCuFua8r8dNFuvR3z6+r6PQ9R1el6GPWsqLj/4nPKzhfL0JB4PbM0ny3WPnv5mlRuVD5tFhZ9v0dKQsCdU2H7sr6WH6a7CeFCeU9QxWMn/eRrFD+gC0rbr6/z3+qzLr38ckPjzcbhJeTVg1dQn5FGtSQq5vE8fIBdH7YDqyHXlS/yU3nxFW4lLyJqFN+fXxx9VGH+ztiHxudnL0EP1LUSXqPcP+9T+DEt9fE8nh2bnjDGOL0IccczX+7eP1P4bLcPM24ExvIy7CC71qH5DWO2PsQxRfnCDR5Rb7ap1r/eJ3rna/k6y7fDvcXkaGaQh14Qzan8IR+iujwv8/8P6pzxxU+Wp1z/lI27zL7s+JjWQZ4kSebiMKeJzr6xv1XribAutyVfUufn5n2t+/ut1aPAj9Wt2Tuple4vy662X7d1qu5aMHeR8cuH5pqvnjr4WzzA43ibjh61STuHzVTlpxTMkOcuWlpKWmGAzKZ8G0q4HKP9zzMpL4nKren3Tx8i91P4tZueCHtZ47xEo5dZH7ZtsaUpMvZDeNpV7LdO2HAQHq/1rVJ2sCVT3JSnc1GYkzCVPjnGc8tNRth1xepL2FHV8P1IfPyFtTJf5b47FL6sbKRNj3cTyX51ZMi6Od9RNzqW6SU1IyxgyaDjZv6Ju9Ot2T+V/qqUTf6b1k2NaP+b1IX47cs/i4Wvvm39uBD0s3rW923m3927n6eXu6d3Bs5aPh7enp0+Ip96O/4K/XqjBpbqkaV0aOw9WcY9Q95LtLW7qvsfV9eVXU67F/ublWrygarlGJ9hSnZdryYI=
*/