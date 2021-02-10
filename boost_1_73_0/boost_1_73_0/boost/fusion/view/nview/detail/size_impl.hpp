/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NVIEW_SIZE_IMPL_OCT_06_2009_0525PM)
#define FUSION_NVIEW_SIZE_IMPL_OCT_06_2009_0525PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
qTGNg08Ohoj+oRi4UY6UT8GbU/sfyMvT7yqM9mxUZqrSFN2lOnFwXK6XMILaXdgrtCvzReO9w7c68jUCVLSV5pYRMD3C/xGkIOfkdNRctvVHQzwj6hvaT40BLopZaOGZhLXwXDww6Bv0t10qwykkv31ZMBpB5NmRBdKGxNd/txsDJIqHHvfNmBEkx+r0PIu0CzYhA2QOe5+dViBpHkuylK0z61Sh6gxiFlTO9qByVkXlxe6yvKiW5eXuVF6W0CjUBo00xvpYKyFTe+AJccHU+/qoKa/mXpIUTOBJDgm+ASquT8lAnyE0NLS+0frUJi0nSKCIbMP3k7NT/qk+UAiWy/hp3qjgZKBmxUolSBpPFf7ny31TN3uCq2WWVa7j3o020vXr2aRmkERbNSN6k0nzoMlUM6e9sXEFoax6lGH2puYO41KQXkNqomkDawAmN9J7g7oxs0l2BMluMz+WTw3gqSr4xgJeFcVWvv4okWjf+hPLw8KC88Tzdw26SegFUIA6zUSLmq4l6wQP/i6ES/ewnrLHQroT2X20sANR9bpopI3fQKFVL3SrwGDp2QD1n5PJm6lhDUZCozxetn+UxlSYgVW75XjnDXC5IFXdmmtlmu0sU1IiU2NcqtV+eoekvjIsD2b1lNObMU1K3Ipu
*/