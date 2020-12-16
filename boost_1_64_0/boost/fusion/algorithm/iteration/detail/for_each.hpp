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
/cTIfuKwH8bjYJyAt2MCpmIipuNEnI2TcAEm4XJMxhU4Ga35K/1G8JhO/sYr5QsTsBMm4gCciNNxMt6HU/B+TMFcnIqPYyp+hGl4GM1SnoJM0v8D75f9esuzl0nGla2Fo/FevFPKQ4RJ+nHgMvleJewu33tQ8msOtsX5cvwX4nx8GB/GXEl/EqFItpch26uKY2V7HXys8eiIN2AnbIKdsQ+G4kjsghOwK07GbpiC3TEVe/jI8faS/g7SD0LZXxun+QvWEq8A3IzS/iGnC76E8bgDs3AnLsFduAZfxvX4Cj6Pb+CnuAfP4Jvowz7ewQZ4AJviu9gT38e++AH2w48wEj/F8XgEU/AzzMCjuAqPYSF+jm9hMVYlTcexJp7CVPwOp+FZfAV/xKP4E36Fv2I18uM3rIUXsT6avLnOYAXsit4YiT6YhhUxAyvhJvTFF7Ea7kQ/3I01pdzlmaS/AQbL9bKmlCVr/3f2i5OxNU7BjpiCY3AqxmIq3oVp+BiacT3eha9iBn6ImXgEp+HneDcq+T4db8J7MRBnYFvMRjk/pM8A/1/n/KhYkXzCStgaK6PUW9Len33r1Fs1WK8x+mEA1pTv18LeWBv7YR28A+vieKyHaVhf9lNkkvb5uEjyUcm3PbKfcMm/ARiBA3EYDsJxGIkJOETOk6H4KEbhXhyGRTgcj+IIPIMj8TyOwhbsNxpb4hjsj3fgALwTJ+FYnILjcCqOx3SMwXswDrMxHmU8cmlbr7S5145HnsAqzTARQ3Ei9sJJOBiTcAomy3jZk7EAp+ALmIInMBVrs/27cDimYzRmOI3jLe3gaR+vHcf7ceLbGJ/AFrgS2+JTaDnuuBWfxotYgMp923N4Ha7FergOG+B69McN2Amfx2TciHOxEBfiJnwSN2M94rQFW+FWDMcXMQm34734Es7EHTgHX8Mt+Dq+jW/gZdyDynn/Js7DvbgK38I3cR9+hvvxNL6NCT7UZzgR38Up+B6asQjn4odYiB/hG3gQj+HH+Ct+gt4VqYuxJh7Bh/AzXITHcCl+gWvwOF7Er7EGF56TOAe/xQX4HS7GM7gHz+In+CNW4jj+hDfhLzgEz+Mb+Cvuw9/xQ7yEh/Ayyv2StHnnWuLueUm1nvFzSJHTesb32YQOsl4J92nRBLOs10DOG1/lPJf17qpgPW/S5XqWgWGYiePxbtyC07GmUg9ibbwPJR7Sxplrspv0+3WU9dykP0q1nnH6cx3rGaY/ykva3EKOXNeV58dwOV/3Sr3xFlrGA8Hh+DZOxHcwEw/gAnwPN+L7Um98gAfxQzyEB9GLbX+CtfAwJuARzMLP8D48hovxc1yOxbgWv8SN+BW+gSdwH36DR/Ekfo7f4k/4HZ7D06jUTd9jVTyDTfAs+uNPGIW/Yhr+hn/HizgbL+FjeBn3IWnIOYA++AFWxENYSZ4HCwlFkv+ZUq6ULnarJf+fU/aL6zAC1+OduAGz8HlcjoW4BV/AnbgJf8DN+DNuxTps/0VsgNuwJW7HQfiSzFOwA2NxJybiyzgZX8E0fFXKwymTtFnFvfI8qdw/HpV458i8C7OwO87GvvggJuJcnIcP4WKch9/hfDyDCyW+i7ARPowtMBeD5O875O+xuBhn4BL8BJfJ8X1Eju9y/A0fxeuI6wqshY9jJ3wC5+FK3IhP4RbMs9+XS9tV7KZzX96f9WpihNO8E20xEkNwCHbCKNneBUKObO8HOe7K9e60bO+4F+nGUxiC3+JA/A6H4T9xCp7GDPwepynbwvvwR1yDP+F2/FnK2zkMYH/nsR3+ih3wN+yHF3Eg/o5342XMwiv4DzRRX61GL3wVK+Br6I0H0QcPYSU8hlXwJFbFb7E=
*/