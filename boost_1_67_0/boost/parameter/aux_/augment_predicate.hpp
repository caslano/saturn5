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