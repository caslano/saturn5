/*=============================================================================
    Copyright (c) 2014 Christoph Weiss

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HASH_23072014_1017)
#define FUSION_HASH_23072014_1017

#include <boost/functional/hash.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace hashing
    {
        struct hash_combine_fold
        {
            typedef std::size_t result_type;
            template<typename T>
            inline std::size_t operator()(std::size_t seed, T const& v)
            {
                boost::hash_combine(seed, v);
                return seed;
            }
        };

        template <typename Seq>
        inline typename
        boost::enable_if<traits::is_sequence<Seq>, std::size_t>::type
        hash_value(Seq const& seq)
        {
            return fold(seq, 0, hash_combine_fold());
        }
    }

    using hashing::hash_value;
}}

#endif

/* hash.hpp
P/BAacGARPpAQwrxgRZDoeKYg9ecB3wJrCZ8G+CHh4zzq6fFq5WRy2k4YqyJfbzoN5xdvsQyao2hAELXKE1vtBmKx+7iC8jVbU5LcD8Oin0XI7daLwr2XhS7KOBD0YMpL9ovCpTEN8iT6c6Rxorgs+ho++l1zE9WRxEX0h0HL2RFsPiNqMgZ+SysCIade0Vw2xt8RUBptmgIkW6h2g88E7McgOaVf7wew+YEpBJ6vc1y4NM7uQAjfSK6LDDikOr+4caZondS25wpOkkdBR0RZed05bs1xLjykMEuzRNW7wpDxY3pCw85yipzXo/2xFBAJpKqCYF9qv340wZyVJ3StEZfAOjHZY7e0eq4DDryZJEFQV/b6IdeeGYb6yHBwAR5xgmrm3S+unGyTzNRBiNur2fmkCLFz0oArlE0MX6kcuo1pDgIS9kqOS20dkAVylDpddkZo9HTl3sUeU0UXS+gF+lLFhIP20lLHFj/YGD7LLbPiQir9u5PcxOwbP16hKFhorb242vaRvByQgT74rvbiZwVrQ4NYDSaNmvj1oKqrkusoBJZs2ZdaSusEl7jwqrvbSM0YQXwipu4tHLnVwtLXsPFEOr0ctcynMjF/PoZ3cXsev79qDdxzx9PEsXM5Rg0e+QKlFmRydoJLliSPPS0IW/G/k8TuyZJXuC8Fc9qIi+gNBEt1a3Wk2v/1EacrClut5y8c6JhozGGw0sp
*/