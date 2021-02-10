/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_0128)
#define FUSION_END_IMPL_07162005_0128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::concat_last_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.concat_last();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
DgUCu0GjOoZ3AzOJtHB6AwODGGjcx27vUzcea1zR+SNZAoMyODO9wEDRU8uMZU/EINgXko1HBD/tp2oFMwh8YHV3BLFT6CqYKT1MA02yWIbaHe4zU+K8JzQ3G3mQgFg+qAfWCg7yXIts4ifKwn062MC+cql8QFahNTNAulfhlPYE5TJ4KSRfkAhK8Dh/WJNYJ6RCFqekAh5tpBJhGlEBzowSBdxJGKEJE6+QjZbRAvH0DoasV5DNI5ryZSoMmopVvnr2uLqBw/Ahw/VdMmLlMANG3N6kogVdrQLujY0NBEF0WCa+ZelBwESJZalzRkNOQ9YOFFr0QC7Ykwr7VqXcYkRwERsjxzLdxZy3qB9GEq9iV0oY74zfBVjA0L04PWVDi/RIMTwQBNWuvNGB2lKEMoN5Wf2Q6ybikRPa03PjrHV60uufgYc/pjko2bnZaezQF4raDO0R1VSK0kFKDDqZDnDKVYFUGvLz0dT0ySbQxpBj87hNgI4BRw1uCjMr9DGUm9D+3zt/koMD8tx/zpgq9/p2AHOvd+/Ib9TbOuCc4j5PoE9d3UczrP0YZ4PhvM7B+SaNs7EazhhpkyG9yUH6Oo2U9wmeV7nta3upqxoNar1qqIMcSljHVKfVeA5CpxlwQuq7xVJ/laZg955S
*/