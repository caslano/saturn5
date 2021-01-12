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
NHKrjt2275VwYWHcxHON1d8Qs9e7hg13Iu6TlrvfTH/3JXl+k1v/3tg1fdyIOP1Anl9VZhuW9KFjpqIp85eLmj4i/bHx2NmKoc+Ig0BUDkd+xQUCMZbJ5wfQL8vtLuJWhUi3pS8TTK9PtH38HDl4Hm1jeB8Gf7mP4cPrEo3P8LK1SjvGLKVJmlaH92N//IcmTTOzC0yylpqu08R8gu2aZ3kWfl8E6UoVFXbNM3ouaYq9stN0
*/