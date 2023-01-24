/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_DEREF_DATA_HPP
#define BOOST_FUSION_ITERATOR_DEREF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct deref_data_impl;

        template <>
        struct deref_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template deref_data<It>
            {};
       };
    }

    namespace result_of
    {
        template <typename It>
        struct deref_data
          : extension::deref_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }

    template <typename It>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref_data<It>::type
    deref_data(It const& it)
    {
        return result_of::deref_data<It>::call(it);
    }
}}

#endif

/* deref_data.hpp
A9ei96A2opSq+NlNYkSg/J2J7XpkQqxduMQT2qX0SmyXckSt6CWa9cl4bhZJGuGsWDKxxvEJycQ2488YFs1L49GqjTGYQir1WnlzpASlsDl2Umiof/5chQMMbZY/vZU3y+53Ysph5u5LxutmbR/eVZdB8XfUxfT3p/g3ZoOys8lJqsJE1EJoyvh0BRqrv9qUTulWAuWyYvsSE8KjB5RygH0abhqOKd4aED8ukvFveuBNegAzUVCJHdcQ7OAkdGYi7zugzziSB/j+vCtNaMtP51/T4Bea8efpSgXunlLC3Ru1ICYLYDsy0VqddhnCep5rQ5NP+ZTw1N3K+fCqEp9yEzCkzO0pmFFIfX4UKW57VB0PpL5ibvkXTZgUZXG7BsfNNe0ubT/mdoj4W9WPBpF6wtOqlLSTkqJVPZ6NpRvVdXCcFJeahzG07l9w9i780lOtVUz1LfxaVua3TpJqkhaWhT0lZaH266Sqc2wqnRi4xV99uuJ6qNkpKyYolA4DZnah1c5TErRp+7zau9iM0Ffmh7ZWtz1kddaY6VXXX2EyOTc04LSgI0AnRSa8OphW3eaUnmuI7q9uq7gZjs+wZtplxS+r992ALW9q8JSYSQs/GaqcI8MtpzoNbm10Ub56dzhYIjxSMK97B55ZXjUHrM4NH7vadlkCPV2hLy5BW2T1j4PxobZd5kA3+N0Op0GTKTJZqzouuXchOaYipk4R
*/