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
09B8AmcXtThpjMngyxrHTMyGpCrWLPYtFmR0fsWifVn3o0q9KhKp4V/LLpiNtT1qhyVTFWyIpkfWR7hX7/Z6ji3eNP08GwDApuu5kDlEZdvU9hKnTP+3PVzWT3kmX7uJycbKXv0qKBfoETLw537I9X53JTiKR/BG54MvSkzG58PrU/Kq6oS8ik6hfQXX3dGympndZZ1/K7SVtiPYmZjewRLFecZlbPmdHLHLXLGHXENdz21IE/oNdVcwRpWXFS4ul2Pv2jeE/MuQX4FkSEaK/ZodiKPRfihB5wAxcBdjBgw7kI+trvxtCK2+O6X8KnZOdXPpiYrYip9Q5Nt0jE1i2Hsiee0OtJjvItUBB+/wytMcEciEszAnaZkRRPQ9pyEe16Fy6k378HtUg7KKDVeWFAd+FYz6kFL3gVzjKQnxTg/tZLDUCQXshgo3XUvQ3EzDELUADxQ3TJisF4ZI5vNVlH4hnXs1bZYdSPhnPUaZ4SJURHDQdqt/03oQ5sSqDJ4lfv2zsaAPjGnU4QhnpztEa9Dh4rB3v3R2VorF8yP6FEHyJvUP5q9Gy0VUjw==
*/