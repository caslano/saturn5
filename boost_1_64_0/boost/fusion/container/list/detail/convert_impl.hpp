/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1215)
#define FUSION_CONVERT_IMPL_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
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
        };
    }
}}

#endif

/* convert_impl.hpp
fBA0XA/6jyk3Dn2f5VGslgtdxx+mK3e4PnG58zsolJ8Ky81i3yJ8n1Ko5+qnLMb+1qlW3Wc8eFwj2feMfMNzwIrc/53tOxkNHBN1yNRYYcMovdKBGAjk0KbnpeRodoHM9jZu2J55c+tKAkFuzlM5sQT09HSJ5MyqED/o5lvQoGRoRfP4x1BEkFiG6RW9SQcN9YHgAE5frjWKMEMk/QK4ou4x8oAnBXfaYhLI/bM4lWik1K9gNcYBpa02U1RXyMOeyTYO9Kw0LkSGhvwYZn0UHx0vXmRFVDAU+N6G6WX/MaCKmgFurIEbVN1iUi8QBektaF5ahsEF826MpG7MTAZnmCCzHB2vmkwfe2O53vyjCC5bNjTwZtPviqn9ry1f+ItK1C5eGVW6ejOVdnYkrGAUXlbyDGqAy3/RwGwuV+z65mvrfsARJNrHsOLGbEyC9Ao2VsjHCOR5OCgiZfWD2KW4tsTnrlkL4s8IWLZaW8s6fugZ4aI2wv2qy1+JDdHGl0FI0WP17+cuUtVuqPl49QNZHWaCde6e/xvs9agZfZqj6pMlRP2YO6z/QmV3gg==
*/