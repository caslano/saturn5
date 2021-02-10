/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07172005_0824)
#define FUSION_BEGIN_IMPL_07172005_0824

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<Sequence> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& t)
                {
                    return type(t);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
jCkIiy78yEy4jUzWLNp78W3g9VJucZH8FVmYVvQiG2Itw4ZyMTUHXB810UBTYCaiP1qAZUx3DEJjUXkRrF8ykDCHZGhgSgrkkKAS9QRPo/D8nb0PSnchX+HhlKmVBJrfQTL2utf+ElwhwMs0v9FYcuuLiJWtBAmwGJKN4+oJR/MJ1aBVygVyMCdssk9sDofhGDzSaaQTjC6o6xcbBaxUgvbpXUKyNky40o9FW7vKVxpj7psF6NuLdpoCgltLdZxrK1uvVde9t8P1ONV6yRwaJ1f3sLNFb0Ug9WRvvtCVQ3DHpW68Bx4g3fG0zClRDfHmD1TopKbYVSGWpnsp9/SKCJYnioCQ09dR/AYTxxOkehDRZyUaSFIs0qyDefsOWh1sFUjtT6fhxlC7/vonE3prik5sp+bvSLDXfkit4N2ZjINgm+UkT/lBouF5fFnPDmXJOPbGK5mUs9SUy8/8RRhhrP/6Lb0pirwJ7sIVuE7aGe9kOi/LsErceQvWYIT14N7w+mfEbTkc03RuimR00QtTTGqQUyWDvtz+yp7T4xPasLvEu9H4enDOuasyRaJwTNf485RuOOmd9k7I7UK9mkRBzXvcPCTuK+8myln/kxacsVGXYmbkbFn1znfXAJmEmEaxSI7QBk8RAHKyf3ht
*/