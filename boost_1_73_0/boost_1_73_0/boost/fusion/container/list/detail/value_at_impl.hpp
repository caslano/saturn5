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
H6PJM3couxg2smfHWuVLuphtxPexe5zyYe8IlDcPl8qmAt7Y0fZwF522CdwFpfTVfoWYASuKO4MLFopahLo76Sff1I2AbPq85/JDsB2l1OC1GNU7S7RPqfUSDFmHPKPJ3/yNG4qaPpqYZSEN71Boln9Q7HJA1QqyB5J/oEMLG5k2dKnNzYidrLw46fFNiPzktlKl5eboYyiHvxaiDp8yfHp0kpXCKD+bdKqPYHia7h2VahMgUqCZQAioKwK2znM=
*/