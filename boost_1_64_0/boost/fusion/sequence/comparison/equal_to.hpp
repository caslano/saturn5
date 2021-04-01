/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_0431)
#define FUSION_EQUAL_TO_05052005_0431

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/equal_to.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4100) // unreferenced formal parameter
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    equal_to(Seq1 const& a, Seq2 const& b)
    {
        return result_of::size<Seq1>::value == result_of::size<Seq2>::value
            && detail::sequence_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_equality<Seq1, Seq2>
              , bool
            >::type
        operator==(Seq1 const& a, Seq2 const& b)
        {
            return fusion::equal_to(a, b);
        }
    }
    using operators::operator==;
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif

/* equal_to.hpp
Qas5ZXnjCRJdxEb0QTe20PYTHnqB475D9lvJ2BlPjMyE4hhWPNFWR62fJVtFQ+VgATPiImw84NYulaw5K7p+tkpu65VnzXayDXrn/X39BKHhLZKBSszNyNyKBKQRAZSr0WkW3kkokVTCh7Rd51WEUV79ODYmwMgCLSSs7ZQXaOIeFthtv3hptuUmeq56Em1b/eyRskQBs110cTNJOReHiXsbLqtGfjwWdgKMsx8Br9gVZtzaCIZMSnQewpVQ4IZ6VZhJwki2JrRvswYwUAH2K43vb3RUTzHAgX0PAK4szUa+mSNwsUpHSKc9oLlcckeXvv1YLnZMZu2D1YCGUOungVbH/5tg3EhPhliMyxRDlcRsZzoBOSUA54fV1LBMkGSj6VRx4FmquvOj4dKIHtwBNZeCvih6w/57qiGrd9Gdjzi3oTRvpuV5YDxKypzMI7MyzcISWTg5C/Ur/JSZPJxYamYBHkerwA58wysfgms6leihTghrbkPgncZTh3c7Xq59UzM5L/r995mQPDuM89NNIYTESRyC+axCtL8o0APgj0tlHP/WqJ1L0tCQdg==
*/