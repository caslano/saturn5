/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1215)
#define FUSION_CONVERT_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/container/list/detail/convert_impl.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_list
        {
            typedef typename
                detail::build_cons<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                >
            build_cons;

            typedef typename build_cons::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Sequence& seq)
            {
                return build_cons::call(fusion::begin(seq), fusion::end(seq));
            }
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_list<Sequence>::type
    as_list(Sequence& seq)
    {
        return result_of::as_list<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_list<Sequence const>::type
    as_list(Sequence const& seq)
    {
        return result_of::as_list<Sequence const>::call(seq);
    }
}}

#endif

/* convert.hpp
8Kuzp+vJNVKjpTfdsg0O+PYfed+h36ROWbijqV9U4cMzkLTWVGMEH5TbH75zqn1CC+uA3TunYSm9v8+0ML4oe4NT9oUeSKlCNiQLbdAiLhwDnolkQiX5RnER71K6fgKUZVCIgGgyipTsi3kUAV9UjoWVTmWd5U26BgOHU65MIKjyOzC0iGimSXTxrJEhwtAm8F6SZMKoBy+NHevwmCAuYvpAuUMcW27EMe+aZKqvUijSgMLDvG47SuLGlDLkeM/jrW3QpcHnVxORbY3R5vYpo99xblVJGJrzsryv1dcuWZziJLSqRdflGcPvy4eecyCoIDHnrP8Wnz3sVcocb/WK1F+mbu69QlGhpqxHG0mfq1RcfrP7NY2yzvR9xgt7NInrKr/n1e+XdZQz3pqG3pi8gJxEVnueTIJi6stZvs1m7hn6yQ9pSj/X/a+yYMd5Uyz05E3kn9wsfnQsNn/PpV0LGLg3pJKhFKptpfALyPwTEtAFEm+Nr5P22XPBNbV9zm149R/Ga7MhvWJBbstCqkDxtRuUHa6z+4w/PfcPUYGa2U3DGtKuA7rbIUAxXA==
*/