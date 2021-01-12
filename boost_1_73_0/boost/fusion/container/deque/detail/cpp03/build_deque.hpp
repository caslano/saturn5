/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/deque/detail/cpp03/as_deque.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque
            : detail::as_deque<result_of::size<Sequence>::value>
        {
            typedef typename
                detail::as_deque<result_of::size<Sequence>::value>
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef typename result_of::as_deque<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef typename result_of::as_deque<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* build_deque.hpp
RwJ13bo4O7Pzq7pcpQ0m7+eOr3F6PWXGtGtq2//BVFZbbvLOvt0xFrY7VadriIxvs218I+7o41M1ZRc3xqhprzrOEmrbu0S7i3/RXjTOGjLOs2wIm+jJ02l0PU+zp6fVzcOVlp9DGXEglYtbLW08unoU9+ji0UNv8dmq/+eTfTpkX7Vf08lxq6I6vxlOm/juRpsUX6i08aYPOWtcr9LV+pZ+WeXdMrqr8k+Otc+2xUyLra21
*/