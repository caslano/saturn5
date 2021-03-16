/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct at_impl;

    template <>
    struct at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
        {
            typedef mpl::minus<typename Seq::size, mpl::int_<1>, N> real_n;

            typedef typename
                result_of::at<typename Seq::seq_type, real_n>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return fusion::at<real_n>(seq.seq);
            }
        };
    };
}}}

#endif

/* at_impl.hpp
IPxusVISOshecQORcbSfJU4a4WP7KOMHcKt1KUS/A78vFG5lQFciaTDMS0sQS4MTpRY+Bl93IEU/YaE7wY/g9x38gpalhsIvbFkJ8mtggnQzs8BXU4qboIVnyH6cT+mOD6D8u08o5UqV6iIRMUecF/53SjdB7h2VcC9KjjS5t2qFJMxLSFgBoQxRYhdXL4kT26xnj7b42qLvr9RZMuLDs1J/WVUjr8r2bmfAa3WTnoGF5UbLjOuWAP/UjD3dcZ0=
*/