/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_10022005_1837)
#define FUSION_INSERT_10022005_1837

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_impl;

    template <>
    struct insert_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::insert<Sequence, Pos, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert.hpp
C/t5yTBGcN4b5+mF3Q3aQaTGtekgbpYiycJSPpoECbFkG2omoZ6GkTDWRtt1hDiM5L3NKwSurf61VW7gL8UTUUO84qND5ye2qWvj2/SX9r0gNTGaG7ehQKXGge4j+nmaEMwW5+qvTJG97bLe7mgatnnsysEQ4lspkXBqe2pV5fEN1TwBPJXUphhehGD1/wG9kJcZDLEVhi9cEWB55DzLGHISSV5+zpGfLAqh1Aelw6ThFqQ3iKXC0rEnhTYQPxivDnHjGPRfw0ARCwZSwyaJWzLxuGu0iVBJDko8sWJ/k31/0NFtV46fXGiKd7s0+kdAig5KOMiUWHW5vqZXhw5nfjdoAYRSOaMgEXQ1HHJAH06kcHuABw9fmIeGcDTLFLQ7C5ptQHV8cs39jwaw+QD2LH8iDnbGkU05JnMuBk/7w2X1qFr1IDIAyXLuR79ib7BrIKgW6jL0E0XpDHIDTGHdU/NymE359lK+9QC81rwoh8QcnJJYgSj8ptuMkUUEpLQ0SFVGIBFOSiEthwSzOWFHpvYgfnRBfFCFy/3hYHSBUhiJNTy1haNeqtUmSQ==
*/