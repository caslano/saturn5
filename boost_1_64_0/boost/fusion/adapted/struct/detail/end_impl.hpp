/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };

    template <>
    struct end_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
qRmmxfEzGtmrmvbpumZgOw0a4k0TLh+xhLLATo+ObZu2cOb2ZMx7Uq4KQR6qjCD6DlzUjoZQBvnu7aY6phz301atPXcyhL+Ok6e8krzQcwW7aFWqcJUXUBGvG19hkaaG4PDgP5wLfJSx0nVLByQggY4TCtLBiFI0bsmUe/q4yY2jQGELLFDMn1CNFbkm+LstQFU5EXWM94KIJiXfsimcrDxMTmVQqj7SaW+mCg1Vwi6VOGyIIbGKZzWI1nAahMZF7nH5lIpeKLyKliCdbqXBi0OAVC5IvvyYrWnFMcZNJMYhLySYoVmiez94e5gXTYE1e1NN30Hgp2mfHdLBcvZP2ikgJ3SdawDZQdB21Zp3si6XmgmsM6xOpfZHEr8uKHSW1jONkJDW4PXasXJJwznF1uJZO9iAyx0pS3FjY2b3n+/dTzs1jtYpBIZrJWdD2orRU1H5fUmzoIyE1UExdkpnG0yoKr+JEEvZLvQ4xoQSFWIUVuIo1r6qhAtLoecosaJZT+8om4XiMLlsj+S+JFfx/+yjN3iDDsLPrjCNc540+6iNzugvQOVp9IoaIg==
*/