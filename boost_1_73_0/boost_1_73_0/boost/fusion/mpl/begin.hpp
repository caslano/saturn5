/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_10022005_1620)
#define FUSION_BEGIN_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/adapted/mpl/detail/begin_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct begin_impl;

    template <>
    struct begin_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::begin<Sequence>::type> type;
        };
    };
}}

#endif

/* begin.hpp
7VDfkdxB8nuSH5HcQ5LaHfUxyWMk/0XyBMk2JPn3SNYXT9ts4TTTNvnMpyaATQKbBXYnWDXYfWCrwV4FextsK9gJsF/AeJazZo0chqWDZYLlg40CKwErBXsE7DGwTWDvgH0IthvsANhXYNzH1qyZ07AssCvA8sCGg90CVgZWDlYJtgzsabA1YOvA9oLtBzsCdgyMh5M0c1mGtQU7F+xqsFywMrCZYAvBFoOtAFsJ9k+wN8G+ADsE9hPYSTBeaKs=
*/