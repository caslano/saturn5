/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332)
#define BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<1> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
bLpuYBZZmpva8fno5pUsCUz7zKBRHSlQRamdpw4pMClioTSq1K7bKoJq9EDtTgBTMfkFfBIfWOVa+5FBOg6C9zJOF5EvYDBwg1PYe+p5doN5trXR7eX6tl+zfIOZ3W4ZO7zN9rrO4/KsyKU1jSBAZmdJGkf5v7jNGLxTpdeUV8fiS7mG/w/vGMJ4QsDmlzwiXqg/FfVZGv8sTM6llGgYFtHkca7LmtAoytWNrwCJJphVWDR8yXJn4SypMCpKI6jksibyt82c9Cq0ErPOlEEojcs9CI76sJ1RQd5hw+0R2bIDDkaEOfhpcvxPPOm7kaRxyysUXd2g4W1Jo37GHeFzrsUw0N4JM4GRxEHlSjAySmMBmL/oPUUwK5JYiwqqIDW1RAo5bOLCCNF135iqcv1vVzLwOmEv75XgmhKIMr2Y5e1s/a1g1I0bjuokzmbBxxw5R/60blF4tdoC1HzjVKmcSIYOXVCN+ev/tDwt+d7rmIA6+1oNPPCJF5v1/cLOGTtwWjAOd8934cACtd06E0eqBWCGibMJvyrqIr3WyAfv0Dqy+wspGrb0tkzCZA==
*/