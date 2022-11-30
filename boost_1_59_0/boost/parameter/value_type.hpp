// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_VALUE_TYPE_060921_HPP
#define BOOST_PARAMETER_VALUE_TYPE_060921_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { 

    // A metafunction that, given an argument pack, returns the value type
    // of the parameter identified by the given keyword.  If no such parameter
    // has been specified, returns Default

    template <typename Parameters, typename Keyword, typename Default>
    struct value_type0
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_apply_q<
            typename Parameters::binding
          , ::boost::mp11::mp_list<Keyword,Default,::boost::mp11::mp_false>
        >;

        static_assert(
            ::boost::mp11::mp_if<
                ::std::is_same<Default,::boost::parameter::void_>
              , ::boost::mp11::mp_if<
                    ::std::is_same<type,::boost::parameter::void_>
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
              , ::boost::mp11::mp_true
            >::value
          , "required parameters must not result in void_ type"
        );
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::mpl::apply_wrap3<
            typename Parameters::binding
          , Keyword
          , Default
          , ::boost::mpl::false_
        >::type type;

        BOOST_MPL_ASSERT((
            typename ::boost::mpl::eval_if<
                ::boost::is_same<Default,::boost::parameter::void_>
              , ::boost::mpl::if_<
                    ::boost::is_same<type,::boost::parameter::void_>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::true_
            >::type
        ));
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    template <typename Placeholder, typename Keyword, typename Default>
    struct value_type1
    {
        using type = ::boost::mp11::mp_apply_q<
            Placeholder
          , ::boost::mp11::mp_list<Keyword,Default,::boost::mp11::mp_false>
        >;

        static_assert(
            ::boost::mp11::mp_if<
                ::std::is_same<Default,::boost::parameter::void_>
              , ::boost::mp11::mp_if<
                    ::std::is_same<type,::boost::parameter::void_>
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
              , ::boost::mp11::mp_true
            >::value
          , "required parameters must not result in void_ type"
        );
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}} // namespace boost::parameter

#include <boost/parameter/aux_/is_placeholder.hpp>

namespace boost { namespace parameter { 

    template <
        typename Parameters
      , typename Keyword
      , typename Default = ::boost::parameter::void_
    >
    struct value_type
#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mpl::eval_if<
            ::boost::parameter::aux::is_mpl_placeholder<Parameters>
          , ::boost::mpl::identity<int>
          , ::boost::parameter::value_type0<Parameters,Keyword,Default>
        >
#endif
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = typename ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_mpl_placeholder<Parameters>
          , ::boost::mp11::mp_identity<int>
          , ::boost::mp11::mp_if<
                ::boost::parameter::aux::is_mp11_placeholder<Parameters>
              , ::boost::parameter::value_type1<Parameters,Keyword,Default>
              , ::boost::parameter::value_type0<Parameters,Keyword,Default>
            >
        >::type;
#endif
    };
}} // namespace boost::parameter

#include <boost/parameter/aux_/result_of0.hpp>

namespace boost { namespace parameter { 

    // A metafunction that, given an argument pack, returns the value type
    // of the parameter identified by the given keyword.  If no such parameter
    // has been specified, returns the type returned by invoking DefaultFn
    template <typename Parameters, typename Keyword, typename DefaultFn>
    struct lazy_value_type
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_apply_q<
            typename Parameters::binding
          , ::boost::mp11::mp_list<
                Keyword
              , typename ::boost::parameter::aux::result_of0<DefaultFn>::type
              , ::boost::mp11::mp_false
            >
        >;
#else
        typedef typename ::boost::mpl::apply_wrap3<
            typename Parameters::binding
          , Keyword
          , typename ::boost::parameter::aux::result_of0<DefaultFn>::type
          , ::boost::mpl::false_
        >::type type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };
}} // namespace boost::parameter

#endif  // include guard


/* value_type.hpp
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
*/