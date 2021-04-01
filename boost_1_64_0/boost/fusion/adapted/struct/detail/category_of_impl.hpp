/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };

        template<>
        struct category_of_impl<assoc_struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef assoc_struct_category type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
mXlD9XJ2zd2rWJZptBnUTV1vdVLwxi5NIDkLYnyphkhyyfV63DxSXT6Qt0L9xzn2dRSkin/7fWRI8tVPFtwa6+yV3SDAl3ExXI4gmFh5JMplswkCql0beNYOQ9EZAlb3JOZKbPgXy4yS70p4NN15IgJk9EQWQC7gP8i3U9N4tMPvbKLBgoP+EcztNEoc+EwseNnPs2uVkQVb7OuiI42P+t6Cx/FpfowsKwDCXZTbd41lacSIeXeq4NTXEepIp8vqCfMe9fXlYuQ/kfoUnSfSK0XffOt39Tg3gjAMlm8pcHscA84iBgKmtyTfz3NvHAnxPQbahgLavdngHtkEaet4lZ5pexhKELjqrQk5jsb6Ujh/F2/GPNMpc672XgBEpmk0EJWsw5tau+kF/pi1/KJJzr9LuQjojd1BTfrL2oux8LLairUEkZXOM6RtXQGOWWiYj52Bog/oWCKoX6QNUKEV3qtXlXJyDWQ7GIhSbgDhMbHS0M7OThjv0sb1UTaNpe8sD0RUqRdmZNr5HUTdW6gC7AGiEN86Fv1P7VLx+j6Gjzivsjl5g9MPfvlRLQ==
*/