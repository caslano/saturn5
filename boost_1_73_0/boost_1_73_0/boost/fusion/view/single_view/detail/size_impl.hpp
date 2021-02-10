/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM)
#define FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM

namespace boost { namespace fusion
{
    struct single_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef mpl::int_<1> type;
            };
        };
    }
}}

#endif



/* size_impl.hpp
MdT2dEek4ge7gh2Mpdl96QHSd+TEoq/9p+8a4Tel1uAHlm3BqLdoVDIAHO7LGR529hwzAsv+m6imPCLCWrsB6sRSD6hRnWzXgJiFTwCj9gxEA3T4aBR0J1uEQNVtNA3ryXTHaakBZM+mz8DaE5vwo9/3B8b4Fg9iAAXLQbg9EjAOKoHvdrz2CxpZOLe2p4NoW685AQVV0PuBZTIbU0oHcimTlTW/03tRwVmFiwMLVuwtiBuYoRvdtfmuP+sq0quR1777ZL5huLrLROK/klklTasmR3p1GZ4+D18OX56evzGkgCMxPVs93RvnvlGcuDM3ReFtXTVGSLL1o0WkDj43xKAN37Wr9q8x7oFxEuRrvp6PmjMvgKPOEf42BaYjVa6aUTMpr0F7jm457sIuMuvJdbxfxFbLiTKYeGEJZ3GwIQba1FcoxmxJFGV0LSnWzQk09+irDjAfKt0W5x98G932fldTu4tqsU68/O2znQeoiBxGVGzV0cBGjqWj3TS+He9qENRJM4MWgT+ncTCjfqxkOsEKmD+1DwxZEclo6rck4/njiG0pLLM+JdbiY5YzT40rqBVWgY69ohdK72Fu8n8HL6A1QphfC+3YYPgg/fOlhLLCJDEyXWPrFQSea1NolFOE/d2OvtzFc6Ye7P+h
*/