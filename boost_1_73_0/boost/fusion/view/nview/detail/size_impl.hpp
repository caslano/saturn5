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
C/pevB290V9rxRN+7D1cfhmmOM/r+lz+frF2uwLw4g7KtAgTFyU9NL++tAAXHjr5eXhUlCIdzXNjwRNZKZpu5NqwaIjfU1ecnm03Mw2oFpRJcfZ3H5exx0tsrI+KUs+EWVpWJy005TDGGyznTmuXSOugSKvECr8qEj3xBdCk9cBOWpWNtXYQB+dOa0KkdVykFeduiqluoWe6rFwXd9Iqk9AuEfN87rR2i7SeJ9Kq7Dwt0yzW
*/