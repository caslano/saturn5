// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_BINDING_DWA200558_HPP
#define BOOST_PARAMETER_BINDING_DWA200558_HPP

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

    // A metafunction that, given an argument pack, returns the reference type
    // of the parameter identified by the given keyword.  If no such parameter
    // has been specified, returns Default

    template <typename Parameters, typename Keyword, typename Default>
    struct binding0
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_apply_q<
            typename Parameters::binding
          , ::boost::mp11::mp_list<Keyword,Default,::boost::mp11::mp_true>
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
          , ::boost::mpl::true_
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
    struct binding1
    {
        using type = ::boost::mp11::mp_apply_q<
            Placeholder
          , ::boost::mp11::mp_list<Keyword,Default,::boost::mp11::mp_true>
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
    struct binding
#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mpl::eval_if<
            ::boost::parameter::aux::is_mpl_placeholder<Parameters>
          , ::boost::mpl::identity<int>
          , ::boost::parameter::binding0<Parameters,Keyword,Default>
        >
#endif
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = typename ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_mpl_placeholder<Parameters>
          , ::boost::mp11::mp_identity<int>
          , ::boost::mp11::mp_if<
                ::boost::parameter::aux::is_mp11_placeholder<Parameters>
              , ::boost::parameter::binding1<Parameters,Keyword,Default>
              , ::boost::parameter::binding0<Parameters,Keyword,Default>
            >
        >::type;
#endif
    };
}} // namespace boost::parameter

#include <boost/parameter/aux_/result_of0.hpp>

namespace boost { namespace parameter { 

    // A metafunction that, given an argument pack, returns the reference type
    // of the parameter identified by the given keyword.  If no such parameter
    // has been specified, returns the type returned by invoking DefaultFn
    template <typename Parameters, typename Keyword, typename DefaultFn>
    struct lazy_binding
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_apply_q<
            typename Parameters::binding
          , ::boost::mp11::mp_list<
                Keyword
              , typename ::boost::parameter::aux::result_of0<DefaultFn>::type
              , ::boost::mp11::mp_true
            >
        >;
#else
        typedef typename ::boost::mpl::apply_wrap3<
            typename Parameters::binding
          , Keyword
          , typename ::boost::parameter::aux::result_of0<DefaultFn>::type
          , ::boost::mpl::true_
        >::type type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };
}} // namespace boost::parameter

#endif  // include guard


/* binding.hpp
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
*/