// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUGMENT_PREDICATE_HPP
#define BOOST_PARAMETER_AUGMENT_PREDICATE_HPP

#include <boost/parameter/keyword_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename V, typename R, typename Tag>
    struct augment_predicate_check_consume_ref
      : ::boost::mpl::eval_if<
            ::boost::is_scalar<V>
          , ::boost::mpl::true_
          , ::boost::mpl::eval_if<
                ::boost::is_same<
                    typename Tag::qualifier
                  , ::boost::parameter::consume_reference
                >
              , ::boost::mpl::if_<
                    ::boost::is_lvalue_reference<R>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , boost::mpl::true_
            >
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/type_traits/is_const.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename V, typename R, typename Tag>
    struct augment_predicate_check_out_ref
      : ::boost::mpl::eval_if<
            ::boost::is_same<
                typename Tag::qualifier
              , ::boost::parameter::out_reference
            >
          , ::boost::mpl::eval_if<
                ::boost::is_lvalue_reference<R>
              , ::boost::mpl::if_<
                    ::boost::is_const<V>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::false_
            >
          , ::boost::mpl::true_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/lambda_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/lambda.hpp>

namespace boost { namespace parameter { namespace aux {

    template <
        typename Predicate
      , typename R
      , typename Tag
      , typename T
      , typename Args
    >
    class augment_predicate
    {
        typedef typename ::boost::mpl::lambda<
            Predicate
          , ::boost::parameter::aux::lambda_tag
        >::type _actual_predicate;

     public:
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux
                ::augment_predicate_check_consume_ref<T,R,Tag>
              , ::boost::parameter::aux
                ::augment_predicate_check_out_ref<T,R,Tag>
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::apply_wrap2<_actual_predicate,T,Args>
          , ::boost::mpl::false_
        >::type type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename V, typename R, typename Tag>
    using augment_predicate_check_consume_ref_mp11 = ::boost::mp11::mp_if<
        ::std::is_scalar<V>
      , ::boost::mp11::mp_true
      , ::boost::mp11::mp_if<
            ::std::is_same<
                typename Tag::qualifier
              , ::boost::parameter::consume_reference
            >
          , ::boost::mp11::mp_if<
                ::std::is_lvalue_reference<R>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_true
            >
          , boost::mp11::mp_true
        >
    >;

    template <typename V, typename R, typename Tag>
    using augment_predicate_check_out_ref_mp11 = ::boost::mp11::mp_if<
        ::std::is_same<
            typename Tag::qualifier
          , ::boost::parameter::out_reference
        >
      , ::boost::mp11::mp_if<
            ::std::is_lvalue_reference<R>
          , ::boost::mp11::mp_if<
                ::std::is_const<V>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_true
            >
          , ::boost::mp11::mp_false
        >
      , ::boost::mp11::mp_true
    >;
}}} // namespace boost::parameter::aux

#include <boost/mp11/list.hpp>

namespace boost { namespace parameter { namespace aux {

    template <
        typename Predicate
      , typename R
      , typename Tag
      , typename T
      , typename Args
    >
    struct augment_predicate_mp11_impl
    {
        using type = ::boost::mp11::mp_if<
            ::boost::mp11::mp_if<
                ::boost::parameter::aux
                ::augment_predicate_check_consume_ref_mp11<T,R,Tag>
              , ::boost::parameter::aux
                ::augment_predicate_check_out_ref_mp11<T,R,Tag>
              , ::boost::mp11::mp_false
            >
          , ::boost::mp11
            ::mp_apply_q<Predicate,::boost::mp11::mp_list<T,Args> >
          , ::boost::mp11::mp_false
        >;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/has_nested_template_fn.hpp>

namespace boost { namespace parameter { namespace aux {

    template <
        typename Predicate
      , typename R
      , typename Tag
      , typename T
      , typename Args
    >
    using augment_predicate_mp11 = ::boost::mp11::mp_if<
        ::boost::parameter::aux::has_nested_template_fn<Predicate>
      , ::boost::parameter::aux
        ::augment_predicate_mp11_impl<Predicate,R,Tag,T,Args>
      , ::boost::parameter::aux
        ::augment_predicate<Predicate,R,Tag,T,Args>
    >;
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* augment_predicate.hpp
obgvku2lsq23m3/a0xlp0m7cJR0PWEfbJ+nVk/fZe8v7lhvA7rARjIQBEr+vm/y2rawtPCPjFQ9ZTxgl7/+MlvfL3SDX/1iold80GX/NlOt8KtTyf5Ncn7NgPsyG98P58BG4AD4Gc2ARXAxL4BK4Ay6FL8FV8GO4Gn4H74E/wHXwR/ggdCOvD8G6cCMMhg/DUPgIbA6LYEv4JOwKt8H+8Dk4Dm6H02AJlP5QfvOUMYdJf/hGbbHjkuf9+2Xd2QFZd3YQauXzibwH7RCcAMvgTHgEJsN3YDr8GFrFfxZ8Dy4U96Xivgz+Hd4h23fCj+BT4u85cdfHKfI7jO4m14PfpD+0+Nj7dTeov+/oDufj+bMS7nt5n06l2Emdg47w0ZXOw1+Q8D9K+J8l/EVDP5Er4Y+a9BMt5X0+HaT/7izP28NhPOwG58DucCXsAe+DfeAm2B+WwOtkven1ku4Fi/xGJLzD5PciuvuyrhT29JV1hbAdHAFnwbFwORwH74Y3wrVwEtwAY33t6U6GL8JpcB+cDo/CGfADGAe/hvHQj3wkwqYwW0sP2uAwOA+OgDlwGlwIE+FSOBfeBW+Cd8Ol8B6YC/PhChgJb5dt/b1LP1zqP4Kq2HEF1hL7a6g/Lxb/fU3Gn4/IPHgBrAs511V9b4atYKE8h3jcYrhf+sH5fZqHm9xHwobaPnlu6AX9YR0YLNuR9ejnuIgHDCZelIO2oXLkO4T88iKjaWglKkbl6DTSJnUDUGcUg3LQRlRAXLvRIS7Q4YSPQtvQIbSRif5T0DIUsj8UpqI8VIgu4ha2mGsI34+joGGcl2gaisQ9Htn4vhqtRyVo5WLCov18P4V8h9PO0VC0H/czKGk4/tAaVKK5o+MoYAl5RLEobATtFVn5nouiR+Af5sCdcCMsRofQcU24XYStIwmHLmrxwCWoEIUtpexQLFqCdn9IHHAn2s/+U8hnJGWAynHrDAegeKQ6h2XEjdaPJCyqQBeQ1yjiRhFoKPvTYd4oyPd8VMz3MrSbuqiARbjtRV6jKU8UjiJRPCrHfSW8AAtgCTqGTmp+byZ/UbR1NBSlDqEcoQ3loXD2F8GTyGsM/lAEisXdiqL5nq/5QaXIxnYF3AaXDCFP8Di6iELH0mZzKQM4FLXOJQ14TNvOJQ1YidJzyS/yGkd6qC9aw7YNrkbbUBkqwa0CekTjDw1Fqej4h+xn3xK+F6Ld6IwW33LywXefG0gbhbHdE8agvny3wfVoNzqOpuF2GuZAr/GkgfL5HgFLYDpcj3JREdqJytFx9p2B2oRkADrDdmvYE8UiK8pF+agI+d5COaNolIpyUSnux7Wwmh+2fWMoN1TG9yg4DZ3k+xJYCQugzwrKG55CHhPJLxqK0lEe2oZ2o0PoJLLcSJyECYLtUTSyopVoPdqNjmvu+LkIvSZRZmgoikVWtB6VoOPIhr8z0BLLsfG9SIub7+FoP99Poyi+e6zkGGEhKtH2oeOo/Ur8QJ/JhEFRKB3lo90omv3H4CnkNYW4UV8UiaahQvZb4V6YB0/CnfACDL2VsFMIizpPpQ7ZjkUxfLehJXxfA4tQAd93w3J0Cl1AYdOIF/eecP0Q8sv3qGn2h8StUSrfh8KVcA0qRNO0bVTC9yJ4HF5AXtOpA7ZD4Rk4AMYgG/JaRRhYgHaj46gSheLuMYP653y/gEJ5yDYUpaI8VITKUCUKHco+lIRyUREqQ5UolI4yElnRGlSKLqBQHs5FoHS0Hu1Fp1HQCNxRKlqDilEZuoBaRxIXsqKNqBSdQkEjCYNsqAAdQxZe7NoXpaL1aD86jUJHk1dkQ0XoJPKKwi9KRXloJzqJfMcQL0pFa1AJKkeWsW6WMBQ=
*/