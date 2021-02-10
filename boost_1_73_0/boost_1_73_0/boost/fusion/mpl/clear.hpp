/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_10022005_1817)
#define FUSION_CLEAR_10022005_1817

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/mpl/detail/clear.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct clear_impl;

    template <>
    struct clear_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {            
            typedef typename 
                fusion::detail::clear<typename fusion::detail::tag_of<Sequence>::type>::type 
            type;
        };
    };
}}

#endif


/* clear.hpp
C1BLAwQKAAAACAAtZ0pSSXsVcQwCAACEBAAAGAAJAGN1cmwtbWFzdGVyL2xpYi9kb3Rkb3QuaFVUBQABtkgkYK1UUWvbMBB+z6/4aF/a4MVdn9atjIWkW8NGUpKUEigIxTpXGo5kJDlpID9+JyddGXTkpWfZJ0v3fd/pDvvUlFZRidub/vBmKgb3019iOJnzELedU94xlt7ezLvvZx10cdREews29i3izrvfVMS3o4XYYX8x6pH9MZEcr5CdOMdxyA5nLUQcVK7TXIhjQo8pt/TIE/JRpCmvMCwhB67eevOkI84G5/h4dfUJH3B5cXmRYSitoQqzSHZJ/inDtWpXvmn5/NwL9DUDRciqd6CaaxMQXBk30hN4XpmCbCAFGaAoFN4s+cVYRE0oTUUYTO4Wo/GPDBttCp1Itq5B0K6pFLRcEzwVZNZ7jlr6CFcynMmVCZEJm2ic7bE2IZJfhcSR5GUVHORamkouWUhG6Bjr8DnPi8ZXnH2uXBHy4uX4PR1Xf0+y4CRWcgtXR0SHJlCGFJlh5ZQpk+eC8GLdLCsTdPaaDUtZlTuPQFWVuBhnKOzTJswO5clSGGrO2MTkgrMhSW20W/0TyHVMLGXjLQtxHThIOS5zhoY/Jd8Gtyd/kTjUtC3wf1vzmq+Cs5wM
*/