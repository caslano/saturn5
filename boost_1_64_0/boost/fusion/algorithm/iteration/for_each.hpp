/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_20070527_0943)
#define BOOST_FUSION_FOR_EACH_20070527_0943

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/detail/for_each.hpp>
#include <boost/fusion/algorithm/iteration/detail/segmented_for_each.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each
        {
            typedef void type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f)
    {
        detail::for_each(seq, f, typename traits::is_segmented<Sequence>::type());
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f)
    {
        detail::for_each(seq, f, typename traits::is_segmented<Sequence>::type());
    }
}}

#endif

/* for_each.hpp
8YaIXuLL0Bl/BR8WhvBibL4szAS1nlO8VPnH7pDj6+qmtWhTpXvtchKdnqcdHJ7aDoM6yQzK9MVqnqQlTzNmn5HefM+7lXd74lKTUEpIq4booigywnoPoCYjnAKRf4C1/Kx5jJkz9FJOdDH6AbSkfOx+MjPZLakYhLxqrBpcXyWbeXqVOP3KQQoyEgHlQz6OhDD/DV54codnxhwb9XNT+TvDfLvyisJzL4eZSSKkWEdt7qCx9HSiTfCEC9a8w2ScVeAC8Qv0sPeE50uLc41U9pgc9g1kwZeyc853giN9zANAn8W6QQYoMRVj4xaWjI/wySSOCSs7MWqgiH/sQbBWsq797k+es5zWJ7a30e324zTnKaA1bwdHSli4v09UtpgGL6vFfx7BAB5OkKXPrzkEZN4fR2Ie6LiYv2G8OMT/m5rcuhKGv4kiteJB6EfUDy8JbWcT65kgJs02UvKZckifV6/qq1VSj52rpsZfcvpBRQnIGOUK/chKQ+BydEtlKYE0Q1qmF3yIceN26S9zviOqcbU1UqQ47OZjIgjTz55PbDr9IgLIPBPu+Al9Mw==
*/