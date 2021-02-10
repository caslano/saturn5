/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BACK_10022005_1620)
#define FUSION_BACK_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/back.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct back_impl;

    template <>
    struct back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<
                typename fusion::result_of::prior<
                    typename fusion::result_of::end<Sequence>::type
                >::type> {};
    };
}}

#endif

/* back.hpp
YIbzTiAtZcVn3fLUrbZSM0gmFmZ8XmLifKFbEcoRuYduBVXoMEqubDwjZ3YX9nu2KCKjeu9q2Zp3IzYdNb2LfPSZpFDoKFFYd6qC0zc//WR9khZScJVkSQvB/J5dsEk+3FZy2ifIYTod/sBCipOhF8TlSzpPQly04YZQ+zHSrMMxa+oejuSpnRzDR+ttrjgfST+76TwO3OBPCBzVtQA4cHAEH2YDr3eyoRg9/cCVDOlwzIiCAUtL6+p9LrS2blzcNIeVIX09uGKYUjHgmackHg8lHjmXHFYNEiwXWJHCla5yWw6+ZY2y9Vhwp83RckrCzNYaLcfZyleU1bBkVODGQkxjvpod450eF1xsXygmxwyHf1qokY0lAqzZkAS3whFm0i7fs1jiyfVxEDCEoxjgpJ/gBZYunikLvhR4HNpNiiECPBdXxIRhTGxBBhFrIhvNIHQ5HgkLvpfIlT9L+8pnIOncuhR0pjviuRRjPFW6qkdOtw/rYBxyHoi3+wIOZu0IwjltB27sb15qfkthX+PhNo2HtzUeBo0tVt/E5OYnYJUErJJ4SP0VV7wFaxgPgboArDWJhzbHrsUeC9odWw5ahLQuWbqJqbUzRM2ig/4hiLejkjyIyj/H2SsM+m4r+3X/txc7yc6sP7a7e1v7
*/