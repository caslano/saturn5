/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
SoU0ORsSMMK7XBS377STKPItjI5gSfO54Qk14ilpRrnQFO4Spa2WRMIUTfoSt6ItyRZZSRIcnVptcy7tm0loDOo3f+aF3tibBMZVGPomXOqfWRj4TUkv3YlT2zl/29e+3hep0UijlvIfT4TDC666pACedvVhD/414Htd6YO9nmgxobO7HfGe0cSiFYtVh4DIvX+ge1yxcgtDk5I4GuiyDI9PTk5Ho6PBAA76r5N8J9ruXo29PdYjo5seXutLlhRyGNRKqxu2FHetvqSiON9M/Sio5vjxLHIvr72LwJ2OnUdqH0ua4+byLfFbhVK95Fk3Jk2N3xv/GVbK6xbZX2x3Yn90J244N+wkabTfXDZN62dOeDObQl0LY4aK7nJZx+RE3ufaohM4DtiTwKMr6OPsx2lAh1RNXfvO4un9tLP5H1BLAwQKAAAACAAtZ0pS5U+6kvgEAADcCgAANQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVExTMTNfQ0lQSEVSUy4zVVQFAAG2SCRgrVVbb9s2FH7XrzjwHpYUjpw0aNd2bTHVdRahimVYSlsDAQRaoiqutCiIVBNj3X/fR0rOpc2WPtQ3yuQ537l959C/GNGjn/byfAtHD74y983w
*/