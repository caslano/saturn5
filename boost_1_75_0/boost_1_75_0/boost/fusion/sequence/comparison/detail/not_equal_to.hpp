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
Bz0tqhIM74PUnTUTpqh502h6KnUGh44AVSBLX3Z98R+eXyeHjeNa05tebkwYKgU7yWVm7G9u2R5Nlu2YocQtqCWo8hoZDrXcj4ozHlO0k5Cd+Kshem/9lcvZqL2scDSO3/a6PnWiiDPbMS4C0P4B5OSmR2E9KCG7XPIoq2qfKxG8wqK3aSu7igwgu5QvSGg10punTHxNmgsCtyBOi6G7xymst/GIgZSrhszdFyE4GCpx1hMSuxTUs7bGtTrlAaLepXp9I7X6oLYuQI5WxvMqNyIn5N8Oi/zg7Y2UlFjYGp9kGBALse/amqD1FV3f40f0fQuzk232sNq8wkanMLagMTCr2Tw3WQREYZUQ7gwaEZOOi/k1ZQMWtAB0BXMTKkymVFMkgYX+kL15d7Ml5Ga1Yn6lU/BWwlfK7/mMSfsd56//sf+6/rHR+rndmnJBHND2X5x5w5PL+rnKK+f2AV4SN3ABT8lQ8fCSvsAlq7bym5lMPhdST9y56vlbq3o8bDd8N6uQjMVidiVai0eIaqUoF6O92JlfNW+wyEJsO6ZGwEIqHtvvgybink5ZTHOz0cDBnUX1FmrLxg3ERFU9Bjpf1/lTACI370hJTfdSLiwSRVQ0i2zHXlyt4nCgQn29o8yms67j3ZP28y0TgN9/ufLyz3z0dmjGo2RX79M039nN/uPODrvYbG5yfoG8wcTj1PlitrsVhy89jQ6igjv/
*/