/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_EQUAL_05052005_1142)
#define FUSION_GREATER_EQUAL_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater_equal
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
            return extension::as_const(*a) >= extension::as_const(*b)
                && (!(extension::as_const(*b) >= extension::as_const(*a)) || 
                    call(fusion::next(a), fusion::next(b)));
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
}}}

#endif

/* greater_equal.hpp
7c866mMINIcD6FtXCKrODXmjbT74SS0T8qTjc/KDEupWS22RfmdTCLTcXbqGHJ1+OEs0mc8pZyR2rYe1AP3lu6H1JPagjY9mbcwCSjUeZhPVizA3J4zcWfk/C57TgWoYrdWSPCvNdzWOiu40JChH115lzUCNt9+EC2X7QIO3MWC2GHzExjEZQZgkc4VYR6aV4HEHb4rKHiUxFQf5Oce4xK70sEOgOcoTERknm25gg8cskDUMbJopkiMm+nTmn0BMRMFzQt3qmbTVa6mMxUob6DuzNazq4UL5NdvA6lu4dAVn/hdYDc3UY5bro1e5SgDkSBEDblBLbHxdguEGDCVCtTuLaMhntdbpmHXguGST4+Bas39ooMYctPaCW9WegIXllP2TzaalveLGYbDtlMitGGIwpVBCXcT6Hdwp+9NxqP9AL4bh+7Vx/rGBmrhq60m44YdTUv4Kl0HrFipkfX8yfp1SzevK5XV9iHfBXpuxYK8ddDPsPax/Vnpbad0qD0pMrOUSUvkP8EnOGSwrVtLI3a8Gj30jrcaQADMZvO6qr3YVxpMf5cP74X+jcoQOENZQ6ay2pRUMcU7TYs+7eFRYYelMlHeydQSiJNt7EkreZmXSL0acdEWJO0Y3Rc2xWrmYXd1qEBY1Utnv4cO/4zqBnZFk134ewnZDd+hH0mWLFKk6BH06X7XXFJpNTtaAXo1fImsWFcJSbulccmue
*/