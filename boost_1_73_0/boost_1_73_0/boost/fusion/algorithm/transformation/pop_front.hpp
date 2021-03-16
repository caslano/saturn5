/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_FRONT_09172005_1115)
#define FUSION_POP_FRONT_09172005_1115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct pop_front
        {
            typedef
                iterator_range<
                    typename next<
                        typename begin<Sequence>::type
                    >::type
                  , typename end<Sequence>::type
                >
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::pop_front<Sequence const>::type
    pop_front(Sequence const& seq)
    {
        typedef typename result_of::pop_front<Sequence const>::type result;
        return result(fusion::next(fusion::begin(seq)), fusion::end(seq));
    }
}}

#endif


/* pop_front.hpp
ycvY8wiMj7f1WSMPyfMYjLmuxgfFBrPnCRg/zSrPY/I8BdNA6POra9Cyxux5BiZSGYdPyfMcTEujPF61zj1nzz9g5Hek5jA8z8nzQqj91XJQy8Ps+VfY+/0FeV6CMc8vogJDHNr5FRh1P/iSPK+F2e/y506LwI/YIwP3+1+vyaNpZjvL9hm77x2H5wG8NLOdzf2pptk93prazic2NHY4TsgAJklpZ2/yZAST29i+ddorb/Zk0uztnJE8mTW1fbY=
*/