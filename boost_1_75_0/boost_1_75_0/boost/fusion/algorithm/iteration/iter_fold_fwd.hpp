/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct iter_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State const
      , F
    >::type
    iter_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State const
      , F
    >::type
    iter_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State
      , F
    >::type
    iter_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State
      , F
    >::type
    iter_fold(Seq const& seq, State& state, F f);
}}

#endif

/* iter_fold_fwd.hpp
ZSu1jiF49wAevmgH3r7zlzS26fCBo+k8WW+H1s9hCfVSEyv0KC7jo1g5REdxeStH8fjReKYW8tFbwM+8fEzOyWdbffF0KY3qQM4+m5996Ovuo9GvzBijYxn/62lLQC4199cS5MstfV7mQ7mqALnlQ+hiBtylg81wnvJLnvI9hN8BTZJzOppIsNGnI2gnixVN7YiBcsohtpv6xWXNQRkXWezvHLGz80vEevcXs5bn+whm0+WfJuZudjkXq0Ingr4qggM/udv7+RwEAz97RvD2RqnJYloMec3+Wgr8ojJw3PiJr8EK9cOmNF/zzzlWfBA4l3rkPYekwncbKiGO/KMVRnKTOzRcFHc9tClwCX09mL8+AUHM/YvJDyJk3MwZnToaRpNwjvTPOSgRyyOuV/I9gv85B448f72J/OjArRb+kJND7m2qyLuNn1iJz87WT5ccwUjkCBYivyBof8eY7oC43yLdEbQ/aUw/KNKhrweD9geM6fEiPVWkxwftdxrTM0W6W6RnBu1XG9KriFWroqPDT0h6oLFAORWgQ8hPNHvK2egr5yOUS/ppcP7FZHbiJ4xxRBTZVLVcO+/EAMNK7NBK0EEnhhpW4m2tBJ1wYtBhJRZqJehoE8MPK3G3VoLONDERYSVGaiViaThLIgynn1YojgqVRyhkFoWU/ELYTEliTBVN5lIH/OlYcdxswyn2Xx/TtExkfYh027PkZ+eB
*/