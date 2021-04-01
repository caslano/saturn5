/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NOT_EQUAL_TO_05052005_1141)
#define FUSION_NOT_EQUAL_TO_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2, bool same_size>
    struct sequence_not_equal_to
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) != extension::as_const(*b)
                || call(fusion::next(a), fusion::next(b));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };

    template <typename Seq1, typename Seq2>
    struct sequence_not_equal_to<Seq1, Seq2, false>
    {
        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            return true;
        }
    };
}}}

#endif

/* not_equal_to.hpp
gzUJAb4INykwA+gw6P8SRjuRWQ/j6v7AR5WrtN4luisbyVg/yxFbLiay6tc0qS3XHo35hcbitGS7AjjUEmcgaXYdDXBsm4gbAgcU6w9Sif9E85tqKwJRja80TsoeVcHO15ApyuZIWNHc7KfXAhhj6q0YvIi3MtWp9gezbLv8azdgPKjZRDX9IirzleU3Vff36YhshmurEWiyzdRiyqGmBc/U+XxZJU2teFLO4Ap+YKDyIkY9y8+XfDR41PsNcTl1Sj0g+JdqLZntkub/vPGBKor7BbZQMhcP/S6Qzu81t7B7tOQ5vQNDWdHHQC7npUNFvYb38wrVarUSoThKSzQGnPM3/NDQHhlXnNmvgdDEKpMM1Jqxk2VsR0fRpaX826pnXm5ePecsEobLgFKqSm8VzAN8iwM5krz583FYd9+XnjYxfdykockVWbi/abJlN9cuEimQG3ST/gaCWVZO8sYNt4K/CWpn22F/JSfdYwKS2Moa3Eu29Mw9cz4DnzGpZj9nqV2VKArm2nh4/D2qlyI1v2drM05/IpXxstbviV58UimdYVAzkpir0AHYLA==
*/