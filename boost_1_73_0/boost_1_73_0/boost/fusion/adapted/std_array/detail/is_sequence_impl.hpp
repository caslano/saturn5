/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
7vmPaxEvVtyJIx3mGE2FFsvBuML6N8G2g70K9gHYBc0ZlgQ8ic62QjcLHdlsR6FbGF1ay/M4R53O1v6KX1C/TdMdhe96RBK6iiSc3wTj8ORa8btIH0qlRIQwmtiBz6up1wB7iG1C+jDNK44zDcfpIVpwch8OenjtdKztKo7A8090Fb/DerJH++yoL4nfPc3fugjtOPsnC6o4HnpDbD9D66u1sxwvPr7qZ+J3ICHg4vXcTfucWL/RNvjvkxz51/o=
*/