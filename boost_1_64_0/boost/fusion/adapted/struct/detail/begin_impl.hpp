/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };

    template <>
    struct begin_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
t/9tnG4aEuCygADD/Xvp9Y2zCc+rHQg0Yis3NdHp8nu9gBudoclw0wn0f0NEDcHac1LWXi4EhtgaQi5aQ03A95zfirFDnxVxy9SiWUBBxq2UBQZ0LdXzZB2xrmkqRl8klV5qC+emC4det6qKMx0hcMtQ24tAbyk6aycOdkS+9k/gEC60qziACbmzXDccfqyJ9dPhX9bPDPzKui+hx7049TN1y0zydHel0XdSajBqtUVm+hCN6kcoF+qJupLW8SQXVF9cmIxVY1mM5IPX9eGH77JlDGG2Ew7KClsttgougdZikzlhfc/Cxs74loZ5MnoEwBuJ8mIMskbfsQeveM9EojbdiAOeB5yDmtW9kq4MtnBZ3mexclpQe64cY0y5Ab9xES/0hujjAnExytn6xCZlppA13owVbXp+++ZG7IdQzCT+t07h14iTh9qVFk/i/6GRoh0PttICVk7P7RFpF0HmYRV3/ghXxHj5h6/TcwkpOlubQRDWh1UUvZnl1N6wHPB9zd+FKG1TCAvgqx8pRrVJG3zdvPU+fZArNZmiPs4x7GCC4PMmgz/n4uEWMA==
*/