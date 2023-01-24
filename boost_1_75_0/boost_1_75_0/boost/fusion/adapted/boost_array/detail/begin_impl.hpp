/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_27122005_1117)
#define BOOST_FUSION_BEGIN_IMPL_27122005_1117

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
9WcRNrj/XzQPYG95Ps0Rxuhtk2jgyuPomTHOX6dHiHa2vYlqe0Nvy1yBtkyo5mBgDrT0Hm7GW5aVVg4CnKw+fl28UMPKmhZvERWTSu6DOyLPNi1L+RT8HqVd4XC3wvXSv/DuyD/MAXeIvnsLspTeIAOHy0q1POyLTKnCwv5irc5h1e6usqcq3MmWYE3O0ip3nGa7+0IwEm9Kp6sodeX18ajkgNsLHzkiUBVGXJbyMB8xUgnsb/IB5CSHqwLloEJ0Pp0qvBwBN5lLyUHE1DzAo0BcYbg9yE+bPyjHfQsiJ0POF5ly9ssKIVSC5QU5VVgsFuMW+r0LzGrTbH5fwQKQ45sLDHdgCgsU+MDYFw/4fcb2brdAQPM5mi1P/z6J5zheD+mNYqi9kRCqH+ei/cfvxEcriI/ydPhgsNPMITvNnCB66Po6n1jpndfN5k7HUQU7yzuvMst3TSUQv/18MyNlKK1wG8n6ajwqNQ3JYvP7sDqpwsr6PTLGMaxe9HuV+2DpThy54Iw425dfCKvSNbl6pyfzhWrGVOiYZXqXAxSew7Ndy4cjIZn3lWzq9g2vRODBRrayhHpritHzH/Cel90TOU9tU0eYCvDLDQqwB2TEZuliozPXDxP9cam+Qnl/mIGMw5I8O0yYPMrBTR7RpmvwEcMVbqA7Fxj/42mfOt5PV96Esh7xmiFAXaCX+Q2tIBDFQ0cIP3MY768YikDs
*/