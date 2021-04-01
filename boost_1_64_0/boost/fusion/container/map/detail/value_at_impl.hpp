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
HL99GEIhtlRR3Dr3YNR0FrJxkIWkYauUwtthKLGa6Vdh9Ii2/CHciT2Q+24TIJg98d1mz6kiPLBMWYfybs/FXzOmhOyIxD0tu3PtwDhG/sjiCiPXLR+btr2mBn/iDlg47hSvRw//LEBrZi4S7YImXkI92pMp2SXooat1fuZHW9t057CFlEwd3yoK5J1s90qd8sYxkGthMqDnEbu23z4rQS7Ieu3UVTegGtHAhVjLmg1ysYmBlbLhiSzFt850bjIdSUU/duajJoV77qXcR8PAsA0u4Lwr9Orx3KgM8Vc7z2l1ZaAIoY/p0jWdFjMXthptKGVQ8HOO7450kFxJ8OtWY5EEcUm4Jb8KmrPwLAf5qYYlR18IVcnXYR1MDzXSmW6jGW4mtIf6LxvC2nqm4XM7b5l10E7DtX4Gzdh62R2xnfJZlt0LOICg7PZ3vZTYlJXpJAUKdQa39DevtKXuBZvs8p5+RxTAzwrGM/ghOPDwK5DuuyaKx+TqNtfW5TiUb0Poo3TUTLxIfKPKEIdGU1v+8v3OJL5gCSOOfnE8QeEOXkJPyBJmGsbgPBefdQ==
*/