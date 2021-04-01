/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FOR_EACH_05052005_1028)
#define FUSION_FOR_EACH_05052005_1028

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {
namespace detail
{
    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each_linear(First const&, Last const&, F const&, mpl::true_)
    {
    }

    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each_linear(First const& first, Last const& last, F& f, mpl::false_)
    {
        f(*first);
        detail::for_each_linear(fusion::next(first), last, f, 
                                result_of::equal_to<typename result_of::next<First>::type, Last>());
    }


    template <typename Sequence, typename F, typename Tag>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each_dispatch(Sequence& seq, F& f, Tag)
    {
        detail::for_each_linear(
                                fusion::begin(seq)
                                , fusion::end(seq)
                                , f
                                , result_of::equal_to<
                                typename result_of::begin<Sequence>::type
                                , typename result_of::end<Sequence>::type>());
    }

    template<int N>
    struct for_each_unrolled
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(I0 const& i0, F& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            f(*i2);
            typedef typename result_of::next<I2>::type I3;
            I3 i3(fusion::next(i2));
            f(*i3);
            for_each_unrolled<N-4>::call(fusion::next(i3), f);
        }
    };

    template<>
    struct for_each_unrolled<3>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(I0 const& i0, F& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            f(*i2);
        }
    };

    template<>
    struct for_each_unrolled<2>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(I0 const& i0, F& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
        }
    };

    template<>
    struct for_each_unrolled<1>
    {
        template<typename I0, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(I0 const& i0, F& f)
        {
            f(*i0);
        }
    };

    template<>
    struct for_each_unrolled<0>
    {
        template<typename It, typename F>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static void call(It const&, F const&)
        {
        }
    };

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each_dispatch(Sequence& seq, F& f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        for_each_unrolled<result_of::distance<begin, end>::type::value>::call(fusion::begin(seq), f);
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each(Sequence& seq, F& f, mpl::false_) // unsegmented implementation
    {
        detail::for_each_dispatch(seq, f, typename traits::category_of<Sequence>::type());
    }
}}}


#endif


/* for_each.hpp
R2md6wSONW6/CF9yoDwuQluK2IBsGNg/k2aZbNJjTmFEMbXC0teDvJQoUjX5uH0J36H86hTYrKJCrcV6UHH5m2I0/6FecTNd0M8ARl/p//kQf+ktHZ0+/SufW8cgXiT9FaO08vLn673c+gVvm3kSgE2OFAw3QlHO2MQtDzK/m/qUNVIHUxkyEIYL5ESrHzDYwR9zp73H0dpwfyBwiYFw3nhyoweDggoyJBdMnJyFSAEIpiqPcv1UY/cwURLBdASpVmYzM7Jz3bvlGKQezV6f5+o/bNhqzUcJTqNjTF0h5WEWg65J5ZTUMf0DvC1bByVYmt8pA9zkOo+esV+XPtLM4+2cqDX7Abvu7jNrwjbCQb+Mld39qsnl/OVvGeIuA7eEDxzuW3bebL6pCz7iWEgs06ClEnaAEEb1tKuL1sSdtUQsIIWFa1Sil8FoedYHbczZaJAn9/zYfsTfyJuJQBkep73stezcTImvtpRpePJdpYkjID5G9U6rNB7zWMNK/F2lN5YuCjnQsNTXwlx55mFyT5hBxKENCx2Ookm0rqqrVKXvkijf8ogy5Esv7g==
*/