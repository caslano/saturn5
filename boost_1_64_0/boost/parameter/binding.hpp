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
7ZP0Xmt4VWPs0Vmn8n1El6u9eh5qTTMzpqxzgpQTOXL5J/pVZHayopse/H5gsug3N25VMAX/Ev53yrmPcob9zw2mm/WujrRpgQofEVyGYf4zKUtnXb5OnDzVSqX1pSetDh1V2WjSSHvOdMLhcyn8lz4j6YRkrNBnrupx5k8qTg5puGlSPiUvkb1ZLyuaM+VZ0qRk2ZzvuBuhS0OhZHUAg73SWrcImPMPdXZjjtCNcOla1q1Jazk8rcWqljG0bpqFOs26t0k0bprXQNcxTLc9LZiS1sLIf7vQZgrtVp3/qpBOz0Oz002v1arx3nRcfZ5NeCdDT3fG9cwM+1Xgx9+gciZNfN0kbXGy4ms7pZuyGqmbXF2P3sAPvSFnvf5BtR1rLbOj9dd2uZOgRPR8MW4ocfPD9525hVOnnBDknWvoPjtL0RcgpUgIzjr//nf8+UYncKkKP4nxsoV1XrBchY8NjCL17vCQcOFhzLuZ7qPFKs501gCl+Nb13jFRrX9LjrefpvH7pT7NcPy3vjPniFsK7217WerLwez9P3ks/n4s+76f+Puf7Puo4u+7yp/n+IdarUnbtr7DquvueLHnDx7se0fj95kdrH1X9v1J8ffD2fe3NX4fkn0fVfx9Wvb9XvH3b9n3w8XfZ2bfjxV/v519n1b8/Wr2/Vtx96uZ+7SU/pwMHo7raPwt6wnFFoEewu3C6fWEsm7TwefBTPAFMBwPJ/E6W+KtkHjng53A7xnx8hPkt03iPSv5PSfxct13ZXmfnSw60NW5hxt0dT7oQkF5p5J3xl3CkxSxC10FXTL4A7AjeAOYBz4BjgefAieCN4GzwZvBeeA6sBq8BVwD3gpeA64HbwA3gD8Cbwc3gneAuMCd4D3gJvA+8C5wC7gZ/BN4P/gu+AD4OfigrIPcArYBHf9s8DGwB/gEOBR8ChwGbgWPA38KTgUfApeAD4PXgj/X62ll7g8+I+1jrqftKeu5eoPtwb5gD/AYcCDYDxwD9gdngMeC54B54DpwEHg3OBj8GTgEfBocKvk/GpT5sMzTdyka6i/tMkLWM48WuToB7AWeCPaW52PkeTg4BjwOHAueDI4Hi8AJUq5q8EKwBrwErJV2Own8PjhZ2mcK+LT4bwengr8CTwFflOeX5PkVed4Jngq+DU4D98jzu/K8D5wNtqZuZ4IhcC7YGZwHDgLng6PAAnA8WAROB4vBQrAELAYXgYvBUmnXMvA8cAl4HbgU/JGkczc4BdwOngS+AU4H3wTzwffAGeA34EywU1KYT0eCNWBfsBbMk+dh8izrO2XuQNlEfsz1nReK/NTJeuxVYBq4Rtp1tcjTJeB0eZ4LXg6eJXQF4KVgsTxPTVHrvxKvEWPD2KO428bKGhpcKW4lbt34g7N2bNMFDa8fe1HWkO3GDYH5uXHXj+FWxl9D9uiFB2cdWflFDa8l23VRw+vJ3LVku+BxovVk2y5215T9b64n20v53TVldbh138GaMnc9Wdol//01ZQeon21d2YuUZeqZB2dNWdaAYNS6su2XNm9t2cFcV5ZH2fJxNbi1uK24nbh6XIhNpHl5h9aBHfod+h36/X/9vuv7/8vLFjT7/n/n2/+0HHT61Y6tp7hoeUkBdtnwt/3DOwT0vQL7RIW7779dcfNywpvVne3646YULKguKapaWFqgDO1llaUlVQVl2mbG+WfQqSO0rLYx0tG2sWplX1tAja3fQaH1fjNVH4et3/iEVttCc318x3btYE6ZO0qZXbsiZcOPsnnPUJYymGdv58v37X6S+DG4reSfd7W5HiJyqtXCmqpyyx3e+nvkCBXvSCzOLezntXn5Ynyj6wAOUeF9iG//nmrGv48InA0=
*/