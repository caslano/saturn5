/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_PRIOR_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_PRIOR_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/prior.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    template <typename Sequence, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::prior<typename Iterator::position>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* prior_impl.hpp
6tl035oj3hrl/cOlCR8k0eaWxTNX+fpny4dHuyln0CT/xdyVOV/BGs75lgEDEYhl4pDlNfJNz5YPPhy6mpCPCoTxAoO85l7WfggwO4M0HyyUc7belrz3Tr4XCAOi8k/TX9tJm1YBpop41fXfUj7XkLLixL9dkB0ag76JOtnPXL49aSC6qMHX1YpNB+WkwXeSjcc+mAOEikXu//Xy56nY3pJ9cvzWypJMYc7gXvk4mBpbxe3n84L0gs9rV9beyKlPU9+Cww88H11q9E44XjW/VKecEX0+g3ySTf+S59t5M3wK9aNdkcgp35Tul/srvlv93NlxsGrUV+cwvy1ZbtbjtFeK6syivCs2fVq+8tnyVUkDUjUgV7Amf6KSf8Wpm49sYxvgXslC7jpr02vkqz4D+eBpAcVDP4676OiGncKoK7rZwKeOyh6QdWhfI1/9bPnaoF+LHqlSvpTzz/bRxxT1Uh2GCw3cTBNwFY+vka95tnxEb2bMRcON0cr+mrWTGIjqTRGwb7RpLZ6seY187bPloz4IR1KlU2dmlCb96yr70Sq+7ILc3Zb8P+ODn5ave7Z8rARf7qb43Mzm5GUcw3qmAPk0KhhzsiDra89f/2z5xjAbRSdfno5A5zvJ6k7pXTp/DxKOHPmUdG/9GvmGZ8sHEpfebvJrnbxV29893C/uTmV4QazXr/2XV/nGZ8sHCx44m1K+qDuvyDAuur+T
*/