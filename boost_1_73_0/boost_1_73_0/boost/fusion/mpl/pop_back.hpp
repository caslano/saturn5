/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_10022005_1801)
#define FUSION_POP_BACK_10022005_1801

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_back_impl;

    template <>
    struct pop_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_back<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_back.hpp
t26NhXcm0gSAEQftkeiNDsQkzKO8JT73xh8HN2PxuT0ctvvjL2LwXrT7X3CwH3v9C9j6CCbLhPy6zmQOk2ciWq3jSM7UnP++n9O9vT9EyTTezKQ4wN0Lclls1ifLg729U1reSErA82olkwLJi9qs5CrNHk6WYp4ykgDSOExCpBdDRDkQdPEgpks5vUW4aar5TM5F52Z4+degPwiuuleD4Zeg0768fNfu/Dja+4PMMhjyII4mOBFQaxjHIkkLIe8AIRMpJpsoLsQ9IGj7MMAQ8yiRswMYLwGaMhN/bH/qBv3uuAf/B71+8NEu/vtEFtCnOI2Sk+Vb3bHU7+JductssqV1e3jdDmget0eYrcNTnGb7HEHvfXmS02i+pf3oyyjoDTrjS69L/pCfRum0iJ1elW7X7WH7qtINxEC48rtp6oD9mIVFiKRh++AuMddjH9O2yMIkn8vMa3xwV8T5Kf7yH1Nv98ECt2Ke+g+XaV5Ea/8ZkEcmS4+KbLYpNVtn6QIZyX8qw/wBEes+W23iIio/BGkDqqn8LJlhM3F6REwwB2E4B0mSTIkHYMYiLR7WEsneYbA0SXgo3a+D7ATrVW9w2X6XHGRgae5VtCotOlxFizAtrS9Jk+Mwn0aR/xikVBJXkFG/8Gixjtalue7y
*/