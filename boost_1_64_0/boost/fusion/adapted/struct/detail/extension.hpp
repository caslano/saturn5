/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_EXTENSION_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_EXTENSION_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    struct struct_tag;
    struct struct_iterator_tag;
    struct assoc_struct_tag;
    struct fusion_sequence_tag;

    struct assoc_struct_category
      : random_access_traversal_tag, associative_tag
    {};

    namespace extension
    {
        struct no_such_member;

        struct access
        {
            template<typename Seq, int N>
            struct struct_member;

            template<typename Seq, int N>
            struct adt_attribute_access;
        };

        template <typename T, int N, bool Const>
        struct adt_attribute_proxy;

        template<typename Seq, int N>
        struct struct_member_name;

        template<typename Seq>
        struct struct_size;

        template<typename Seq>
        struct struct_is_view;

        template<typename Seq, int N>
        struct struct_assoc_key;

    }
}}

#endif

/* extension.hpp
+xckEGXD5Q/8sKaPqmRDXMtBfpA9f3vdZVWZ+FRQHFtZZb80fhNTzTSSGBWUeMQ4nvMYrGq5OkWHg+L8TjUBDMACKEKgt5pmE2M3CKPrnkDEmqg1fwD5Xtg8aHaf4mIHqcq3Y627RwMuz5J6FUhaAwoPsNPOvsL6jPIU0ZDgzn1uAzWimEtTJLw94xYvPEPblHyghkJApWjXySDa4U68iCFMT+qwOuzaXANh0NN5iBA/PKvhvYMiVWntNm2czHQhyuLusk0IoBxKsjlnkO0Ec0DERnhlCugVPESUGo0PIjKf/aVMrCiZz4gC2GzZNIK5+y32MZYTIbDiJHYDZ27BRYiB7cMH5eBsOaDo0lEosymlUAuHORyRte+f7RC0PRStqrg4yPoVlcvXecX9+pnxlNQBbi+6ZJCB4lJrp4uWGzbgBPZo1kEH5ZXnEdr+eNuQpqmdlXHEadM4jDy5efJgx28eaATUIKRKG1lnc6K61W/j0HCjWZN6uWyP4Ggi/nYD8rDddYSb2bMfIdEYv9x2K6o0RxuRqhGf18bS/t9bWaSHLSBdsHvqJADK3g==
*/