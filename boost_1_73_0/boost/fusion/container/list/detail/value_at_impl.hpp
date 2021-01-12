/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_07172005_0952)
#define FUSION_VALUE_AT_IMPL_07172005_0952

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<cons_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::eval_if<
                        mpl::bool_<N::value == 0>
                      , mpl::identity<typename Sequence::car_type>
                      , apply<typename Sequence::cdr_type, mpl::int_<N::value-1> >
                    >::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
dVvzI9HK89tR89tJ89tZ89tF8xul+bGt+elvEewekN8UzW8f2AkWwi6wCHaF+8Just2YX0Ez9s3U/GapfQepfQerfQeqfWyb/Iqaya9E8yvV/Mo0v3LNL6z5sW3ym91MfgWa3zaa33aa30jNb1uYq9um/TWT33TNL6r5xTS/GZpfHczVbdP+mslvL81vvOa3t+Y3UfObAHN1u5eO33ts8v9zrtcSyv09mj0l5AxER6MV6Bz0
*/