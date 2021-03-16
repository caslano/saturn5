/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM)
#define BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<nview_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type iterator_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::advance<iterator_type, Dist>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
mxrMXLFwK4VbLdxG4R4S7k/C/Vk4rGfM9daGgyEioxabgNePbi1G666f2g9Xlwbln8SNc3PWV384/y4YVhoda9boU8G1leYk1Zio1laeMtdTHK5g20d0Jd8ZnCpT4C8QXD+9d7DmhK7agvvn5uDqzyATJdy7HusW18wByphEhsFRJzoaI9z1yphJUFo8bpXBUaqnBh9QTU0nf1A8EiBOaqYGzystmVPhOKcYIwPUUF/t/YV0z/fRuVZZ/slV25E=
*/