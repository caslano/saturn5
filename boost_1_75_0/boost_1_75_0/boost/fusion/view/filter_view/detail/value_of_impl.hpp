/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05062005_0857)
#define FUSION_VALUE_OF_IMPL_05062005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<filter_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
ZzOjik0DOs2JNJ75nOhLU8aZydorP4ex669WXFdP8fwxPV6drxU+nhzL9faJ5c0k3m7gxGcw9tY/T414K10ToaNARFoqqZ8B/Z6tzZ5PiXDS1HL7InrXiqi1m8n6Z7T/fykh+WNv9JYaTp/pr2R1fFILN+cTum8Adc48+ggzva9jj07R99zG1vzjtXIsq1I0C2Cs3nAY5xis9a8P6vr7zPWtD6d9ZMK/6xjru8RP+Hcl3vTv6hmReNO/a/JfJN707+r/u8Sb/l0HX2V9gt+HbX+A1brIgnBf5oWpc7EjMKGRilzRPRV92Npr134Kyr9rP4WUZ9d+ishv134Kid+1n0Lid+2nkPidtZ8i2vht2pxi9ceu/RUSn/j+imjrDjM5vRp7RhV/fh6vfMdE1oQWR302Nzz3FBvX7EodvwY7vn3/E/WKNr/d0fXb2ftzPmj7WXR7QjT5F82CGav+k/b0qas+qv6x5tYzscRN1iqanda6fNO/b12y2BaBaGvG5gqH2Kvtr3BI+0+3IoutdsnE7gLdLjduGxfL6lGOI6OccTH9Hh810U7m/oiCSNnH+aMsqm3JqnwmjezI9p9Jq1r7DviixlOSxxcnKCa235zoZdZ9u0R/Rzy8RCuT/OZGylPmEK/Hixz6aah4fgfMcqrdBiUT70fjZ/VN6W/lYWZlhALs+Q/SU5VMS2ftT2CyhGb7TU1xVIQj4tdX1gSm
*/