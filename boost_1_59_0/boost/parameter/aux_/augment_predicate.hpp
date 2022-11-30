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
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
*/