/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_1142)
#define FUSION_EQUAL_TO_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2, bool same_size>
    struct sequence_equal_to
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) == extension::as_const(*b)
                && call(fusion::next(a), fusion::next(b));
        }

        template <typename I1, typename I2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };

    template <typename Seq1, typename Seq2>
    struct sequence_equal_to<Seq1, Seq2, false>
    {
        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& /*a*/, I2 const& /*b*/)
        {
            return false;
        }
    };
}}}

#endif

/* equal_to.hpp
7BPZb4QPrjbiVsm/eWyOe0fRGuoPRuHyHIYHu4h11P4XIWto2ZCoAXlPv6PoOSBihl+P4iL7EBBF9WS5UmKRGmj12vDru3dv4TW8uXhz4cI1KwTPIDC8mHG1cOF9Yi1dzT+4wA2wrNtkCVOhQcu5uWeKA/7ORMwLzRNgGhKuYyVm+CIKMCmHucg49Ma308HoxoX7VMQpJVnJCnQqqyyBlC05KB5zsaxzlEwZkHMMx+SJ0AYTVkbIoovYHAxXuaYcBM8yLYEtmcjYDIGYgdSYUv/meXGliL2XyFh78ebk3dTk25NMkUTOViBLA0ZCpbkL5OlCLhMxpxVrgcaymmVCp+6ODUIViScVaJ5llAvjBNc1bQ5BUx6X3KBExsLQomWhCeo+lfmBI9aRsswrVSAQ1gGdEolldqEqEq6ssz35BqKpqS3wk9Ls+CYgCyQDp34Ag+AUZkwL7cLnQfj7+C6Ez/5k4o/CKYw/gT+aUrI/BqNrlF4gmAL+tVRcI7gCkZeZ4EmD+XKP5zhnooizKuFwSupFmpuq7Kane3Y8Tsw0PzRypleoIXaIpg3cmWPN5tC7mwyj60Hgfxz2o5t+OL4NB+NR4DheB4ZSfqlKDRQLTTC1j6oKI3IOSEcbZkQMCFnhELCMdkjQyWyGVoyB
*/