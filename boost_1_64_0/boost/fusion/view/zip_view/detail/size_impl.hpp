/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_20060124_0800)
#define FUSION_SIZE_IMPL_20060124_0800

namespace boost { namespace fusion {
    
    struct zip_view_tag;

    namespace extension
    {
        template<typename Sequence>
        struct size;

        template<typename Tag>
        struct size_impl;

        template<>
        struct size_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::size type;
            };
        };
    }
}}

#endif

/* size_impl.hpp
x5BddK+Hg/HX+SnujzIoTzD+XW15Znx1tGSxpqfvlE5oaWCOzCyaV+2ClgFmx9e8MHswWjaYK7M2c4bPR8sD41lftbj8A03xr/majZ4n0BxUYPbM1lX4ay6aBoxnHbZq8wS0EDDeX5eCJbMoazDe3z8vwvqgRf0rvlNq3yWhJYi6Gim37qElgjkwO3633lK0JDDeu2uNITdoDqIuqfb2YjQHMHdmlftu305Zi3NadqxN++WJulU6w3fK85X5592igUMj0QKFTVZPiafMwFyYrTbu2oYWC8bn/rHtrtZoBjDeX5/nrylPIxjvwclB/ZNyAXPmeT5Iu46WLuzR3IQtlIs459KozX0oF3HOlypLRzSb1+ZWImxhIJoGjK/517FbKWhBYDzrGroStKYezI1Z8cnD26HFibrVl873oFxE3aisvRUpFzAVs2K3Wu2iXF6LzIJSV1AuwupeX1aHchG9O9sfof1s3pifZV3YVzXlIszflLWXcgHj+42p7z0VTQfG82zSoc5JtFhhp9N8B6MZxH77h17WoSWBufO5OwWSpQlzfub5g3IB472f/F7Sg3IRZ6metOQo5fLW/Fk5sGDVErQAYUdqdLqHpgXzYJZTbcdh6l3Y3FtXhqAlgvHeZ/6K74lmAuPnjFFtuUS9g/E5JKQN/4SWJeoG7uplQMsV+3X55UJzV7wzf25LGjq7oqnBeA+e7V6dRgsC42s2XnOh8PUFjJ8zNlZzhXIRZlMvZx+aAYz30Om4/Ti0JDA+24YbV7igpYq6fXZtUtEyRF3Hh3fOo+WA8dn22Tc7hXLJM+8vvfbr1pSLMFN0pTpogWDuzJTrdrhRLmAqZld7X9tOuYDxXMa/KDGZchF1uwJdblMuYLy/swf961Au4pxRi9orKBdRt+nfZ9RfjjjL9hlTlqEVgPGsDbNX3kVTvRffV+6GPkULAONn6XWuczhaCJg7n3vWCi1alKizWLSkNloCWHFmqvT0IpSLsLiFigS0NLFmA8/yQWhZooedDq9z0XLBeO8BU5/WRFN8MK+70rPSAjQ1mCezHfMPHkILAvNm9kjTszj1Luq+Ho6wRTOAqZjphz44T72D8dmOatOwMloqmCOz65VmbUNLB1Mzi+nfIQstR/S3KvJwQ7QCsabWsvp1NJuP5tYkvjGZGkzJzNl1fhxaABg/y9HYdLqDWjDeu2LFtQDKDIz3vmua9jFaApgz32/Y0IloRjA+24zsqiPQksE8+N3V2I9FyxB1r7a9mE6ZgTkxm2vd04cyE2fJzPFtg6b6ZD73TfPm1EMLBOO5WA3d3xVNB8Z7t6yfMhQtFoyfc8uk3XR3DWAlmI07vcMRzQTmwMxwsN1JtFQwPgfj3BNNKRcwH2ZJRb8Z0PLEWep+cHRBs8k3z2zPw1GX0TRgbsw6OrrT/ILAeJ65Dyt9plzAHJm5demfhxYFxs8yyP/lFLQEMD73sl2/R6IlgfGsn03rY0u5iDVHvYykzDJE3c/jJT3RckR/jruKbEErEBZ253sOmuqzeX+HK1uHUWZg/Czlqs7vRpmB8bM0uXumOWUm6sbG7LyPFits9/NVDdAMYMWZXZz5NBHNJOpODYugHtLA1My6vCkagpYtznmo6bnC7wFgfO475v34hWbzxfx370UHe01DCwDjme2rWvwS5QLmxGxvqkci5QLmzuya9u4ntDgwFbPsM+voLiWC2TJbH6VdjZYkbHeE9jlastgvTZNA9/o0GP+N5b6h0xe0TGFDS861ojzFOcutOOpLeQpbPnyQhvIsMH+v8uy3Yi5aoLBB6W1moOnB+IzqBL2mGcWBeTLTh4YVRzOC8R4Ca82hrJPASvPvXDWNNmgZYA4=
*/