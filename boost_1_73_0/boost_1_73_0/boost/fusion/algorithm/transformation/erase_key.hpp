/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1851)
#define FUSION_ERASE_KEY_10022005_1851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct erase_key
          : erase<Sequence, typename find<Sequence, Key>::type>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::erase_key<Sequence const, Key>::type
    erase_key(Sequence const& seq)
    {
        return erase(seq, find<Key>(seq));
    }
}}

#endif


/* erase_key.hpp
HEA/w9OcPO8JtV7diyedZE9LMJFKv79HnlZCrdevi3rMZE9r8rQiTxswFQ3Ps8ZXbrKnrbD3VxvytBNqvULqVDvNnvZg6ivlaUeeDmDkr3JLgfGdHY7rOoJZqulHrvqr7J73waQvgjh+/qfq4Kzs6QRmh9Jf75Ons1DbOebxWw77rw/AFFHGT2fydPHA0xXMM2HNry7k6QbG/Dve20fXY8+Hwj4vupGnu5tn16Mng9jTA4yf4ulOnhgwsiXlljU=
*/