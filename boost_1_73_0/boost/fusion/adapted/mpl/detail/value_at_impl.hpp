/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_31122005_1621)
#define BOOST_FUSION_VALUE_AT_IMPL_31122005_1621

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply : mpl::at<Sequence, N> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
5R64AVanHWDPp7liL9P2CLf6Yev+cwdPz8qMf/5+ommSeZolvwcRP3IfsoaArjhD7mchk/9mVJTNyecRNO9sW9/ZHveAO+8875HHsRvfJnEuV1zo7kO4X+xku9oo3usP1oq9FDVTg54tcyTi2+qmPWLeQ9TH2IvF+LNV/Mkz/rQTfzLc61CxTyCrY2tMvxE3PawkdZfudqd58MzYHAcZj2rj3IOvZlubGbKhTVUZO4IXVbvu
*/