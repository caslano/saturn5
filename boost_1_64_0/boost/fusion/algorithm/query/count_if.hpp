/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_IF_09162005_0137)
#define BOOST_FUSION_COUNT_IF_09162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/detail/count_if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count_if
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count_if(Sequence const& seq, F f)
    {
        return detail::count_if(
            seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* count_if.hpp
wjxT7vARJeXFsHKqYuV3zQjQrJ+2b9nlLwExbGfnOMpCi5hTPWeGex3KGq5YL7WEiLyyZmcCf6iD6Pm8LJmRUSie5JRbCrYCdL5ef2OPPUMZqOAnSXG63YXN7xDXQ/4jkSMcQ8BtWBdSmsXEpKv4zkbPahez0H4yOTmS0gDSYtiqSvv09WuMgOzcjx/Nj3aEFHRy3Trgs+9wVKLiwapD4BOJ3fvABQDX8PoDTEgWBNKQ0O3kno63aWc74foc+CLXEoiHFeriV5fvko33oD7M8caw1Fl5cYpchkdSf+nOjylPu8yo/vPZY4sDzVLS95wF324QrYjOtAP1R979xlbk1wGvgPevgkkQpfbl+Y7rZ2EMedTaaogReo2bDSP2qGI76AJLVA0JBoImAP/zMMYqcw2xMNaKsKUtwaiyPRt52PaQXSfWMuQZrRLtkWwSCFLMHpyGPbVFjzncXNHxwPRk/o29J9bDiANmFf/gYo95w7c0SV+jCp11XM89xgqS1FqRPyFBaQOFqQafC4pnuIRJHqGWkiU1IPQrWkhAJYQppTjEyGOsVNVLYAcjkA==
*/