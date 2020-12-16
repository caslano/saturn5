/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find;
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq);

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq);
}}

#endif

/* find_fwd.hpp
Zb5oqXx3CKZQRt5dlHr6e6JFO3XatOlk+His532VzDE21NdE9fMC1+c8hzrHXepTPkt9llvUZ6ZSL7r61N/fnpK6e1DG7G1Sn9F3metOGfUDeV9inEubqKsH6a/e9q1rU8e684fjVbm2voQsRK+GDWa9eMgLUCdvG0rUP1vaz/m1aC+ZNu1FxiD9HpQ25VzXgz8c34j9v0CuU8q50VxO7lB8Pr8q40jVnbpxRN7TmcueZy6nPP+L7oa2ktzTnVGq1Ml0pBBdw8z93P1KMYBnvm1h+jqI0bcf/bxt2nI2TVz7Hq6f6/e5SvZqHc5z79FLB9XNPbaZ0xv4nOSWmntsPXfXbk6y3dzjwON+BjpH13ourt2cZLu5soHPSV7fT/n+uvnb3gp7eOYfK76ac3rNhemvtNxcZeu5x3Zzuc/+3GO7OeH9XHOSnyr/bOMHF/1kUtbL+2bMWPN+qO+5x5XrvXNi9xvmKo3TxuuskjnKFulGaON1NpJuuDaeaCP5DlPTib8O9vZxvpoq+/PFa+OTNqJfura8d9unmyXpMpE4SVci6c6FaZKuH1MZesFL4GDYH0bDATAGDoTT4KVwJhwE8+FgWAiHQNFHfExSvkb2y6uXdL3t9Wauq/h5xP9DOte61DOS7q8y9/QzOBB+DsfBL2AC/BImwVMwHX4Fi+DXcBk8DdfCb2EVbE05RpNZOzgVtoc5sANcAM+DS2FHeCs8Hz4Ew+DDMBw+CbvAZ2FX+ByMgK/CbrAORsJ3YQ94EvaEX8ILYDeljPAy2BtGwyjonqMo/h/xC+03zFH8rcyN/AD2h7+Hg2A9HAM/hFPgR/Aa+DG8EZ6AC+Gf4Ab4CfxC4heIX8dxn9h/oHsutetYJvndBIfAVTAOVsLJ8GbJZzW8Aa6By+FauBreBu+A6+E2eDt8FG6Ae+G98LdwC/wT/CH8HG6FX8L7oNJGHoCJ8EE4Ez4EM2A1zIKPwCK4Ay6Fj8E1cCfcAnfBF+Fu+Bp8Ar4B98CP4F74DXwahmKDZ2BHuB8Oh8/BkfB5OBv+DObCA9AJfw7LYC2sgi/De+FBqPaHrTK3sZH+QDr8NZLOxzhTKemG+zhfrSmd+XzlDvFFiI9iv2Gu6iFpB4dhH/grOBC+AafBN2EmrIPr4duwCr4Dt8Cj8HH4LtwFfw33wPegZ9/Mesm/j+Sv3TfzZlkDcgvsBW+F7t/Ju304wOJ3a+V3t8G+cJ12bcX93vzQSWeXqhCNnSXdQB/paiVdN6SmlT7dndpx0ZNvo+nkHTIc5CNdsp/pqiTdQB/p6rZ79QsztJcp3nR0Silvo+mQB/w7X7KkG+QjXZWf6eok3fBG08m7LDjQPh3jDPpJujQZJ4cp76RknBzSinYGh8KeMBr2g8PgEHg5HAdHwHQ4EubA0XAJjIG3wFi4AV4Bt8Cx8EE4Dj4Kr4RvwPHwBIyDX8B4eAZeBUPRaQI8F06EvWACvAROgoNgIhwNr4bxcCqcApPgdDgNzoPTYSGcAUtgMrwTXgPvgSnwcZgKn4RpcB+cCZ+Ds+Fr8DpYB6+Hb8M58PfwRtgKW2bCc2EWbA/nwe4wBw6A82E0XAjHwAI4FRbCGdCztiqylbzbco9F1JO7jjtIPX0i48FJ2BN+DvvBL+FgeAqOgl/BK+HXcAL8BhbC03A1/DvcBL+F2+E/4A54Bu6G38ED8J/wVfgveBi2Qs/3YAj8CwyFn8Fz4CnYBvZA17ZwJDxX6qmd1E97WAjPg6vg+fAOGAbvhuHwEdgFvgq7wsMwQnu9l/vdnRbX+ztlbv1dcBi8B46B28QOD8FkWA2vhw/DHLgDPgt3wZ/D3fCX8En4LtwDT8AfwVNwL/w7rIE=
*/