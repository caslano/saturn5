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
8rLB8LsYwU4zG88WWUGw8M0ubZhbsDc/YfUnojkwtD0j5LCWRUFE8mflzP7H+it6VdMqv6sOSH02IerkPQz6gkilK8cVgaK4y6nE3S5eaRU6MPKl8vT9WGa7k/D9JmeTZIxYP/Mt7VMMtVhih8gXwaNkjHPZ5ZzLOQaAkDXjizwaQo5k9YBhqhF+31ZCw0+Bs1RFhftwkJ0F/Qygl49a6+7nL2QzR94fCLZd4vXTYg7wbQrQ1jLCjcPadPEiIx9YmP8q3ccTtfO1Z/jGEPtBK6TBpaFEp1yBqkTqIIGAll5J1BgpQutAXEZi5Ldw6vJc/6maSQSrddAT7Tq1jHvzndGGiCstv/NOQsAuB3a4YXYnK8RYxGWME4qqGhJb/k0kr4qvOUTsYAjc9D2dfZOapuculLybtkA6TfyFc2Cq4oYzpknm72Q6NhshH/dGgaBN2OirJmvl7xdS03zvEk2S+rNkzyJRNYt3IIRBCw/mKc8GM9cLG0S7mZUqZyycfNSNz7gPL+DxGAD7lsLnAPYDFXA3eEj9Q3CN0lEGQCfDcQ8kThVpJXnbVEVVpQ==
*/