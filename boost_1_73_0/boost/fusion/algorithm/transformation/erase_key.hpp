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
PCNkm7d/fV/eNt36+HxlfNmne+xolZd7B/SrlO3ZmG7jNuoL34WrrvImmjtTloyiXaITrKmL6MTzg8W5Yxdptsqz0jJcxjKbWjYmmDob8yjfGffRC6vttH9ySmJCfHqi/b2wGipPF3MPzmFG8pTIOZNF+watZidqFbVodYiXPXN4PVDvfwTz0t6431SykJ4WaJyf9C/kcH8xfudspaahYrZz6YxeaVLprlGnt8qTz9ivI1V3
*/