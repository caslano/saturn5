/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_31122005_1508)
#define BOOST_FUSION_SIZE_IMPL_31122005_1508

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct size_impl;

        template <>
        struct size_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::size<Sequence> {};
        };
    }
}}

#endif

/* size_impl.hpp
XsvXMZJvWNOaXrtu2XiSJb9lBDIEL4PLnf5LidfFMkVKl4W49pVlrCy/9vqZVmJ/qd+zv7LIs7w05UOJnD/W71FOGrf6HUv3uiTk4HvkeYjMnxvv4TYh7eBrudxrlbLd400mTrzT0h3nb2ucP4bYyCbE2ddk/SyJ85oluhV0N/9yzyTTH/Sg2H2YWeyU5IhXvIt//NOxNZP/NxzCmqy61ux11HtYP9mSX64t98AMpJp9k8qL
*/