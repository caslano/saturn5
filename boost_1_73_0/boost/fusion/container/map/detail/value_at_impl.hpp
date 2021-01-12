/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get_val(index()))
                type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
vrbU2L7WY3bI14oWM9fMc0msjLZVfyLea8X/TRLv9nSLozyfiSlVU6YUzXbrC/Laq+pdyXM38yzJlLy9wNfpyerGl6m43YdLjlsPw8z84qLJbl1Iz0tcDe0H8CmyMmGRvTWEL59QbB+P0bWwS8KGKCmD1I1ePgk7ghIUID4zH6S0nK6qPJpOt66KY8Tvaurb2APu7wDqPkst5Tm6mXJ8tz571zi/cdsEV6m5C3MvZpOxR7+p
*/