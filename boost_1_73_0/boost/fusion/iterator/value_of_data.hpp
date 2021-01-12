/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP
#define BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct value_of_data_impl;

        template <>
        struct value_of_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template value_of_data<It>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct value_of_data
          : extension::value_of_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }
}}

#endif

/* value_of_data.hpp
5+U+xyl0fbVdH15jfydOHDueZz5y3ObFOg+nWWfOcZ3JsL/NE8fu9n5uNl7G6zj311te8LlVjnlyo/uOW3xeM74u1Rin5sOoB7zedvtpt3XpVebFF5xnYfOWzzeOTPd+tvm+i42LiHHY6L7YvL3jR64jz7iOrfL+zJOzv+PvG+9RW6yLvux8Mr6Xj+/3LrJ/Fxmf5a7bGcaJ+/ydG8y/NcbXbc4v4/KDevtnuj/3/Ru93tFY
*/