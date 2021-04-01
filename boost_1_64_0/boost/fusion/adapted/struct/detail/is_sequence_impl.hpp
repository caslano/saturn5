/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };

    template <>
    struct is_sequence_impl<assoc_struct_tag>
      : is_sequence_impl<struct_tag>
    {};
}}}

#endif

/* is_sequence_impl.hpp
mQ5q6HEzZm6rP9j74qJ3eoz33DtcnZXSHcb9uf9qL3SnsEDqgVE1EQz2SW21ydjQxfVfTYkh26HNDFhNBnHkS3JW2JgLyUvzFSt5jjjLbN/ptHSAbDF18UxaPdwBHxWke3VzgZ51d6ccBaHCN1vkFpS2ZOWUanOZRaXSsRDctYr7e/K/uqreNKdglScUwLMmnqpaehdSRYWwtxIliYEsOh5cxbvZHq53+WEyNtvmph0JrFaEzNAZfWYQj+fXLyCGpXzfS4taAh+rpRccCoSfMCx5l9gEvfypkceuy2SSelchsk6HwZwLQxHnMAkO7sT/0iYlANTzott1bOfccxpqTWD0UxufUTjyKfK9j9LbsRVl5ivM5EdiV/J3xAdxDmdL/XBMcGBjFpChXfgYPx7v1EqSD91iK1QS1Dq+Ix+8AWBINYtE+8GXivwUp3GP+g1ypEk6sHfTvhDQBbl2L15aPZ+ZuYTnepoFs9mcNZCtc3RD9sHzyqnGiP521E/lRi8yXS0RVXWcuBBgkDin7A3aWXNQtYShuKroenZHrN1z/K6Cv7GUnbEXbiRJYA==
*/