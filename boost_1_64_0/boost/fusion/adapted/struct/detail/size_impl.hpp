/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template <>
    struct size_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
          : struct_size<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct size_impl<assoc_struct_tag>
      : size_impl<struct_tag>
    {};
}}}

#endif

/* size_impl.hpp
U2jPF2ChP2GPYQtIl41uo8VQFA1iuAzxQAXfaBkN1ipSwxTT6ujY8SvwZyoPvrBTCqSDVLwGuv9VixNrMPXRBNcIDbgsItw6GmNu+nsocIwSGUzUL0WrS9eTCQFHasDgTaIqRcw+U238kz8VPkMonOZCVUyvmeyJAbH8OpncugEmyKqQgCqIDi14klMgHksBaqPQ0th/PQFTBuq2hGSFTSZOBnriybLOCdE1oewDSW6Rr/UyJGkPV0ZuD1PAuDgD+UtBlVmF34UVlNQXUG6rxNFwwnnHBoSEQ5OBgF/N+E9h8VF9U6mwwQypmJWz8lcJkjuP6Ks5bAigAmpxpsnTRA4fvB4j+QbAvNzvBlPWKVgzAXzTwo7hdmKlRyXYcLUX7mTqUbe09hUjj0APer8n4+Z0/fZwftyuZ55duAxldL5h+zv+vKUPzUYuIvpui2FnDdYAn6UQ6GcooH6Sin7Q9pQnJ2Hi0Exf2xg/ZXkDB+xseOo09LmSHCaoKgEv/utS/va37Sns8vQl/kG4IRSm3yq6sfAMpNFbNMbu2hNPHTH47A9y8csGom70ZA==
*/