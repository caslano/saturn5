/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_deque;

    template <typename First, typename Last>
    struct build_deque<First, Last, true>
    {
        typedef deque<> type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename T, typename Rest>
    struct push_front_deque;

    template <typename T, typename ...Rest>
    struct push_front_deque<T, deque<Rest...>>
    {
        typedef deque<T, Rest...> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(T const& first, deque<Rest...> const& rest)
        {
            return type(front_extended_deque<deque<Rest...>, T>(rest, first));
        }
    };

    template <typename First, typename Last>
    struct build_deque<First, Last, false>
    {
        typedef
            build_deque<typename result_of::next<First>::type, Last>
        next_build_deque;

        typedef push_front_deque<
            typename result_of::value_of<First>::type
          , typename next_build_deque::type>
        push_front;

        typedef typename push_front::type type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return push_front::call(
                v, next_build_deque::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_deque.hpp
v1rMOUPsItQMLscoBvcodc/ucDVrYNWwdM90IldROCvOAnjDSJLlDVK3OO1tXnO8otvqR51PsViSflrgrWb064+G63u8OC4FTJdp6at6+StnT/Lq2EjP9jt9dARDaRNr7KckR0kdodLVQVkA0DK65vDjHDLa6GpT1GzHOTj6+I9/9Oqpci0PQa1JOQR6tw2EegWE+lYQGhUQGltBOK6AcGwgCOEq2xY3fN5M2YsCfH5n1jndV26n/BDTTdaOiXxT5R+OhoPCs23wCAz24/01J+qz/BQKegcmEULgJQUeUlsfH9VrjocNSWdfeH4MGKqK23W0RiFErz9EPa1Y+HcHfO9vrg4AyPWCtvFPhccojZhXA6j3uBe5cuKR660ZQ73ibcNrVLw99k5K36Ljf3mRIka20785unI8O9598QJejdAfZGmCdi9R+FJ43Lm47LdHHcWS5N9d9crfAq/orQOmEG+JVISFl/jUmSAZW1iDOVuVJ2tVx5tVkHMpQ+2usVZkCf/JH/aJ1RlednpINurt7AjIXW+/vstdSZzkGlxfMN/ZlRqi6tnCPITybHP9r8iqLLay+/gHJ9pEfWLO0IKtUclZMAru3f+KgieIDs91A9sb53ohYTqhU5H5u7H7vvTzxTbf1/S6LXZlOS9p
*/