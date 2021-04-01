/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM)
#define BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/container/vector.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::deref<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_of_impl.hpp
lzQ9HqGN3VWdVtr2mQPCjXKv+HtdOVOX8nAZtrLB/Ety+25IZVEUMxzGAijmEQceCMOSLIAXG6Fy9074KOCV4WV+zRwMGnS7Y7TExj84Dmj89Ylry9b/nBzLZZVxJgGB9N0VKATh16S58jGLwZhRAXn7/hAhFlZ5yu/eTkDbqO30SPJoGVofSIZrNehPYWbg27hLKOvbwiiLMvM3ij8RuM8gzIWv4G8n+9vYjkWelwoFLaGlOfs7emdvFqVzGpbOGx215QTxCGu+9ooDffgdtSSND7DwVytq5dWykR0giK79mlTJobX18WQs/m2fTMo/pJwEKD89+cARkfWtdrhb7knXdAgf8VECr/OlC5ytiEgAUi3WVJ7LoctnJSZLA7EzDHLeqc4DgmFNlWVkeiqP7BIX1XYSFZgrMEK6StHhthx3izent6dymSTvYcxBmeepRfJQosCI+KKw4hn2k1ZW3tYJMlcZYTmkwGTaQbgSQlYCR/xukWHBDJvau1y9xIp7ItPLo/NQjWbsc/gKxsmLglB3+eU3oKmugLA3/HXs0oCi3xiDgJL80j9TmQ==
*/