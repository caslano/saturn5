/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09242011_1744)
#define BOOST_FUSION_IS_VIEW_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
U7344rPUJCctTTARgsyBIDaCBgJ8AtsgkGDozQtw2pa4VgwFRRkJ8X5ys3BWQDiHOi44dpBhVUE0IvyOp7oyNAZ3D0yn1a6pm6NiEosXF/UoRa19JxhKLK2ikrlqyYC9tY+VvTUCU4UWqESsIntsdwCKv2tue8T+bN1M03pDCb3owmY0x0rFDEOYkAjTBKG/DGGdTEqoDNXYcQVIzmZ9AdJ+R7ckxAJ/bXUcpzDwhb/Jf8fLd0Gq5FvVQleNdRExZi9+wLhNmhTtH5XU3GkpVzgpNXdVCDFq6rHV1fSu39H6CsZ6HBZOmo2Pi9ZWg9VAUCrIIiLBWyz52GwMdFpSdWk4CNM3Wt0aQH2udXtXS9INkuvWyyIHQEuQD+3xLszcd3BjCegJScve/FbK1/aFry24zayy5+78Pn5HShcETcpIocE6vzlSelFiOJ2+HB7vd5UxTS99bm2krAW1BCbs+cPlGCNn4+aqo8AbrRVXFvRxyQJSO95i7UhKOId2nNhG2pHhbasvIFyskZhiTkhyXoZ3M6L/4eqKUF3E+FqqqPPqUOJqi1DRhTilcKx7jwT2s1BTYD8KJZmcb6OkuT5Hr5U0HsJ7fsdkfsUXSh0Xb9nf+Wx/QQRhfY5SU16hsHA3Z3sVeufOM1qviRYr9yp4ZT7ZxN3fxOHzbGPcYmva1S2UmnE+8vz2JQEhScM6B4Sf3daZMP8grw/kP+oc
*/