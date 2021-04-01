/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_03202006_0048)
#define BOOST_FUSION_IS_VIEW_IMPL_03202006_0048

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
S6qEAGJNisx/6jPLyIYzgLgcBz99e91fLDeYNJDtxTULXcwSzy4kUvdorIfFGwZHArL7icMe01oxOX1t7bo+XxkmneSC69Jgl+LgsOd8Xny4swFsQhRfEX24PwuLlCQ0ezGXE+c32yCQevaDLAnC5n6uUXnKHFDWAiswYvgAfiNPBKKB5tBdoUAzyzrSPVbmeLviFs/xmBNc0OBj2y34IhGHVecQzV03K8Ye633rPq2bGTzNZDh+9mdx/zavrRtleDWnZ0wGUZBYJwvRLhqDqnjS/lMz/2QIb2YqREVLreJPT75XTsrlq3onc3yToUxFplgBist6P90t07Xg9wKbY6Pg+scNJH3O99L+h1HT7HA9JmHOSCKkpSWE8fAjJrppfAij6fFpCUzlpkCWEzmnnbeu0ETu/n7GtmABwzOKi/IRyeXIEJvWi/WQ1/oGPDKkodBSJ69ozgJiTI4W3Z6md2WmPELAVnupq7O+z/tgOFs5Tf198KtgAZ2ZGCHpCFWwaALJKcNTYjSE0tVJAYD7Guxso94fssQ3z9t3OQ4ws+9VmT6NsTOGy06qVg==
*/