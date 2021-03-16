/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_IF_09162005_0137)
#define BOOST_FUSION_COUNT_IF_09162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/detail/count_if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count_if
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count_if(Sequence const& seq, F f)
    {
        return detail::count_if(
            seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* count_if.hpp
zdMOuoNkjop66mNZG2Sv9JJCfQHqC1BFlrLGHnj+9yWIL0EMtyUOgzgMYpQkqCXYIFuCXyjEP0H8E8RYo3bEzPeHKORXIL8CGdKuDWO+rxNe+PkQC4Agr1YH7SmmktN1zT5GClKXNFc56FYqJWfMRFsU6gioI6BmxaXaFeooqKOgqi2lp65jfQ3iaxDzjdLT2vHhCnEcxHEQDUYZaCvXOuGFnw+xAAjymuag3SK1A24WoJc2xOibVWUsG/qkfUo=
*/