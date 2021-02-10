/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
/JdOuuPnVzBezON0lhf5PIzi6XwS5iG8BvfsDYTdjZH2Oxfcmq9N7+Gt/8cb/xUazFvBiDoUimnTZbxRUApjZleQhNdT56nAq5cw7pTG/jSSC+QbtalU3w7bgRZVx8UNVIxgVxSUpK7XpPzHhs2WSTrLosz5jYuy7iiDC6vI6qNjs5USTY+RnZgvMKpQKzVK5glUHuwkpzBClbaUaHL6wWabTLPxPJrlUZq8dyZo/xczgl2zR8iv8nzWw8cNR9SoN1HaQRsiXoaLOHeSRRxbw2ye5uk4jTPHuFvT9Ft4PYunji82TjCCUKluawjZs36uia0A+nKOx0KFL7AjLTcD68MocBxUZIdn8fXBIjdlfXCc/3FjHH/AyYsjFRvuOCHOLWq9lChJhiPKbol5wkKFoWIjcYgMmMGuAnNiFAMdyh4QtrrwC2YIP0VxlC8dO0e9bmCPxxShtD/p/iM1O+K4zQwFExr4pmdadU0j8VTDT0yYqqmN72bTKYRxlqIOP80fF3a5SMamneCevD71wHW+A1BLAwQKAAAACAAtZ0pSW/ObbjMGAADVDgAANwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVFJBSUxFUkZVTkNUSU9OLjNVVAUAAbZI
*/