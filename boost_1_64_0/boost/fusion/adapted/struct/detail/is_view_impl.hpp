/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : struct_is_view<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct is_view_impl<assoc_struct_tag>
      : is_view_impl<struct_tag>
    {};
}}}

#endif

/* is_view_impl.hpp
5Pg9qF1l6r48l3aVJ9seY6BJKx9mwwLZxhgr/2rjVD9FSvdBUx9Kt3+SSdfua24nyC6uVQ8tYVu4Fdwbbg2PhdvCcbA1nAnbwNlwR2jS2B3eZ8oHn4R7wU/g3vBnuA9MJt994dZwP7gtbAdbwwNgd3ggzIQdYB+YBlUv0q9wr5e2jez2kgqN3LvBg41csDfcAw4x8sBRRh5o0jV94Eqlu6XqJUVjGnP90Miulx+hyesnOAj+DHPhL3AM/A1OhL/Dc+Ef0NSTpzH9rIHqKRm+ApvAN2BT+AfcDBpbQM1gM7g5tP3rSVdC+wXTg/3ryQ/eTvBIvY9D9B4OhYfBYfAYq4+y5cyFxXAknCRbGSfJVsbpspUxU7YyboXHOf2ldBz4t0t/OdA8VyMP3AcOhp1hDpTtF+kr8JvuD7b90lf3Z+n+Q2F32B8eCrPh4XBAY0eeOqV3sIs8nZVeV6V3EOxk4gbJk3pBdHnSdX+G7u8peXpJnkMkT2Zjp7+pVXrDXfqboUrvKNgLjoBZMBea/Ec66ZCQvisu6YxSOl5o4o6G/WEeHALHNHb6H5/SSXXpf7ZrZPc/rWFbuH0j5745um8Hl/t2JN7mcCfYBu4MAzaPdN+xLv355km23HvBfeE+sAPcF3aG+8PBsF2SzsxBk+aBUO+p9sPNtz/yPf0pyS7PL3A/+CtMg7/BPvB3OAz+AY18jZA7DzaG+bAJPBE2hafB5vASuAW8Gm4JF8GW8FmYAp+HW0PbRo320rXHPj3MRs11jezv//VwD3gj7AZvgpnwFvUvt8EiOBeWwNvVr9wRXM8n2/mc4FLPY5RPAewCC6Ep/1iYDYuUbjH0wfGwCk4ISt+jclS6pH+p0p8F28PLYQa8QvlcCcfC2XA8vAqWwasD6WvvGFa7pH+O0p+h9M9T+ucr/QtUP7Uqx4Uqx0yo8Yz2ehmbuoxnuiv9dNV7D9V7Bjwc9oQj4CHwJJgJp0HrGBjsC+fCfnAezArkq31ceK9Lvkcq3yHKd6jyHaZ8hyvfEXAyzIWnwJHwRng0vBWOgnfC45TvdI/2aOGHyrclnKJ8Fynfp9XunoGdYJ3q7xXV33JYC1fAi+Eb8A74JpwP34LPwLfhcvgOfMOUGb4L33eer/ZTKaPL822n7/SBMBW2h/vADrAd7Kh66QTNPV30ve0a1D/NU/o7ufRPSbzfzWEjuCNsHOzPVfcd4j7fUvrab4TbuaS/Cjm2gh9Bc+/HUP229gZpYy799n16Dg/rOTwCO8BH9Z4+pnRu8WhPz9S90jH1NVvplDeyx38+mA4nanxTofe7Ch4Fq+GxcJL6uRr1byfAU+FkeCY8Cc6CJ8Pb4CnwbjgNPgVPhUvhabAOnqHnf2ag3NrPg2e5lHtgksYF6ucHw+NgDjRyHKl6X0JYq3SKNA4z5VygdNKS7HFYR5gKO6t/7wJ7wa5wNDwIlsGD4TWwG5wPu8P7YTpcBHtAU78Z8D3YE25Gvr3grvAQuC/MhAfB3rAb7AvTYT/YB2bBI2F/mA8HBNqb9ui0JtcsxLaavreKt1bx2tUTT/tdnv3qiaf9KFf/xkuDbdg56a033sr1pHejE0/7Mkovejztmbj7S37MqT/2NJRvPfEWxhhvbYz5pl0eWzyf4u23nnjrGmktXGvjpl2b+ceaRhrP6f0o1LhlLGwPx8E8WAwr4Hh4ISyBD8NSuBiWwQ9hOfwKToRbkFkFbAcrYU9YBQ+B1fAYOAkeC4+H5bAGngBPgLPgFPgEPAW2bMTDM3LBU2F3eBocBk+HR8EzYBE8E1bAs+BMeA58BJ4Ln4Iz4KfwPPgtPB8e0Jjvukkf1sJMeCH0wpmwGF4MJ8NL4A3wUvg=
*/