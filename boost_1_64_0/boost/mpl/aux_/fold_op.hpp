
#ifndef BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

// hand-written version is more efficient than bind/lambda expression
template< typename Op >
struct fold_op
{
    template< typename T1, typename T2 > struct apply
    {
        typedef typename apply2<
              Op
            , T1
            , typename T2::type
            >::type type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

/* fold_op.hpp
3r2bFlKOIFC8n9ZwGHbOqhcH6blqpunPx2s1LvyBvyb5n246DyV0/JWdRe/Az409b2DjP8gbfwGdW760Kpo3pH3NZRnSTnHaDGnfRIbUmFMh2husEO0NHKK9Mc4CRGDR4n+doAHzF7s/YMBtF0p15VICmmUFtRzeLqmCGAYEZXJkMZsdWbC9DXlAE28AAf/cqmCyYHIWkUOuWmHNVTI5cDUmDy8yev4N6q60+clpsPnJabD5yRlaIwqnhwlnvUpIRprEpAVKYoA6iBsNDxQOysFwensbti3xqZjtN4qFG6FbYUxnUsC8utOlfcohxw9tNIf4nm9E24eZkYjyf+5oih7cKvLNbj2aw28/79TYvmtYUuvnvVvHlvn/Z9W1jA8WeZrHN092aL3/nKbrr83E/eeEfhfrCw1u8vwAudzTzzo/Tj4/jFz2UwYbV4GDyeE4Guh8ROn5HMS2Dk6nJHgSHC10YA/C0/agoJ/zSxuGBDuouJnKyzEc6cPVX/BojaVQVYQAEW5LqcMw8c+U4+4sYYlV60Qb0jAXbvj3wI1fV7J+AxNfYU4qpJzImVOhYlBQzRYvPuh2AMo7DuHQyOdIUmjf927yoN9X3xIhbH9/YIH0M+SYwHGGf4e0ybkm0R5Ti94CtyueSK9AFophJfMSo2JeucJXBQYjN+A133UhzwrOew4RqcJFmN+8oS/8mZU5kSLyRtMysCcqKJA2kAM/XBz1ZZM88qEnns3L+2q6X6t5BkZSj6BHf0m4Zv3nzDQZhURQJ9kmrpDAaCRBYD9AJmUjCTdZilnzPal5EvwBuR7ijjAWVkrbl14H+LZLEbS7UaQsidofkLyytrb3Rg0qasXpJvQfidoUNZWG0hmSWDVfr4k1hhsaRbzP4aaFg4gXqCKABjKyigcbJ+HXTDyiFG4d9aP5kWcHzkBfyh3dldxd4EykSg9i5k9lai5SZYSz02TiFGtPD2sVsjHvodeJClb+6dVjGY4wCea8tRb8XnEif2lMQj8HSTKoE8828hSkztWJpxhnq505QScONM5T1QfrxBTj4VNl9VSVWNiN3t9bXMIcG4sIz9fYPahcd4s1oJ+pvj+4xRrQTNX35lusAZldZd9/vsUakKGqL73FGtCqU2X16zmRQ2p7+ejyrjrd+EDtkYARuELc/3U18TuS+2AP8OP3cA5bXe+938j1Brvs+XDUqTghPt+B6Wr4YZhikLa8q63YXd+nuTQeee0Y/6APaytXRrCVFcnV0/gW2YwGLyeQPwumlz/0I5dA8lVOhfJhpAzPvdVEiEZdzPU3dFlcEEl+MSci/NidK6SnL+ZGSr/ulLxwMn4UREq/SUpeOBayrqqyHHELOgVVuceVvPBpsRd76kqjCydTty72MrPZ5UDcoTkZuPct766dnWrUszDqBDnqBZSunAzXhX/GXQ8qnEaj3YxrnPSHdFvUAW7yOtloakyjf/qUGx1E6WwPDouM+6sYXc5Srf9CwsnWycu90Qk/F0Tb/XXbl6PtfG4bwSArQNya7CdnPLcuYa6HGLoRLnXJWC0HELkouoM0Y0RMB5/VMul8VQVs4U3WN/voLzz28Rhlem87WKmRMTEQWCUbGSyGKGNhL+MmjPGqLMy+ffuQKvxZHGfkqCzaLPnmFzwjGI5DbeGLo39owvw7+rP83xOzG8dr5x7FnWcxM5b0i+el0P2gvhcf/VYKuu/yqVexcVEfB6PNAoaPUXGUg41h3elIaCv72ab/+KW8v5PWiiiRIfEwB9eY7cP23Cj3gS88gpKdV3cUNk4hQTSHibj1MbGL/e+ll+LQ/TraAJoLj0KlHoS2Egp8yS9OiBBy76Ca8BEchI/XaLvPqVA=
*/