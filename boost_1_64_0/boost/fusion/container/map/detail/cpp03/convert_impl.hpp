/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1340)
#define FUSION_CONVERT_IMPL_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<map_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::as_map<
                        result_of::size<Sequence>::value
                      , is_base_of<
                            associative_tag
                          , typename traits::category_of<Sequence>::type>::value
                    >
                gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
Lc8POmwo5itOEYMxYkzEmZ9Pje1KaSRhXGhWhFVFNYqBAwoQziPn+xk1ScDVKVZ+n3DfrcyNQTfwEdcuUAl9bc9Fkb6R73h5qqUJB6QK+FT+VvyjuLqoENM3wrrKGvcUGz/Ws8X6t6Q0ymtPDjBSJO6LcNF4Az42h50h4P4qZe+0U92VRLFvkZrNrWnoVNdmPnQ1xS6dmu9oiQGg1S61rJKyuHP+eo7vSWf8PE4OV48Wcy9wZ84+DlcNTananPrzlhPuZerHHXbovRs6zEjJBARCmajTpXubkHwG3baC6xztem2FqTmA2Cjq1HRa5YP2e/zRaHmPpQxOoyaxjdQzRipdAu4cjWmdGi3AKfjYmhf9lVqohTPEdqnPf8wBfnMSz7CWESRq3cW9FaEeOD+PwWn9inYd0XOwVCS6wa/9ksFLI65jEHpc2XsTbc7URPVwWyttAyIwWc0Pde9TijY4n4DZ5O+fNJHTANmB48PMcUEp8rZHpsTiyxSOQD+6pK4wh7bIKoTO/YxIxZtDwQswW6TgOINmJ1H4sqaEx8ByCAkWiFwWIsojJzcvoQ==
*/