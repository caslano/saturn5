/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_KEY_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_KEY_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl;

        template <>
        struct value_at_key_impl<map_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : BOOST_FUSION_DECLTYPE_N3031((
                    boost::declval<Sequence>().get_val(mpl::identity<Key>())
                ))
            {};
        };
    }
}}

#endif

/* value_at_key_impl.hpp
SB5JjRJU5t0L6aw1CpJHUqOR8ubznc/uZmtETxQkj6TGIOWNsP9O9utD1KaC5JHUWMP7w9J/vMRWKi4UJI+kUg1vw7SEAZWI8rqT1GzU44b385sS2rBro24EeSQ1DilvDvB1yI/TiRoeQR5JpRl+roYznltA1HMR5JHUeKS8FZikSglLifowgjySmiCo0de/YPPD+xHkkdREw/vDsOObyhJVuRB5JDUJKW8u2u3augCi+hQij6TSBZU6+3JFohY=
*/