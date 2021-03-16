/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_10022005_1617)
#define FUSION_HAS_KEY_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct has_key_impl;

    template <>
    struct has_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply : fusion::result_of::has_key<Sequence, Key> {};
    };
}}

#endif


/* has_key.hpp
y9I54f8wwTZIsI1J0FcuCdLTpH73NPt2K0svsxNYpv7LCQT+GwnoVbA6meT1BxOqxH0eF+aKZWX2zUrRezDZtjtGF9xQy6nrprMDnelFDNwgnCWMmwL6mqKzLGX2U8pVZhelIfT/oIPZ9crsXFSIq1MR33yOQc7YaEALie9BpfdYckkDoWN5gc6OytkapexdmTYi7DY6+0aufqLMRP/P6SxJzr6is/1ylS1L6YafbcFpf7wMP1nO2A6c9nce/GU=
*/