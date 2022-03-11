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