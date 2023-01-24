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
z8XKyOhSV4xgH9JkzpmX3xbmh5xbyvCYH6c7PgQ6Hmjww8FBMxu795jn/FL0twsJEYyNkQjmngREwW70k2A3wGwa0Z3ZykY6wPxS0Hm2Zts9Lp4E81UKaM4QF8Gg7m8uU/gq2QLg32EFQNfyAhwPeJscD1rPre4XMiN9ihlV7tnJ7txMtCDcEP+eoURJ31ghm2fyzxaSxEVO9X67xMo5IGcrC9oGwTQ+2IcaNxJ1Zy+HMSJBM8MulWo+kdiVtY2OLswLyLnECbfIfSEAWqiJG8bw2Lw4709rdjRwoLxYsRtLAfuKOO0IHRqjhoPTseZpapBesO+TUv22XacFfGRzhz7rtwvnCrvq32jv++c1NJ9E8sGbnQzQy7nNTgtSSEPz+whot1NNpE+5mk/3pD8a+E85Ws5hphw+rpyMVlKm4yDybgGYVI3fq+XwzJ4UPVmE+25EsEChr46vrM7y+G8bcQwX0Wkz5T2HzqlUDQFTJA5VyIc8pNAdrPgYMi1QErv2isI5Iet9SK3AEotC/OmghWQ3ZEQP9P7qtOLpWLTKtsvf8lxcK366IMVfywSaILmpfF2jEAWB1Ji1VPy86L+JftEnS1ugGBnwBzMPCpmaAdl71NHSDIFWXmfeJW6s3FmmofnP4BWMk92LE0UTPNns71p43QTebZV9qf8azSpgvCTbly4IDkXlPu/6ZfunokBSxSxQXgaYzvF8TqOz
*/