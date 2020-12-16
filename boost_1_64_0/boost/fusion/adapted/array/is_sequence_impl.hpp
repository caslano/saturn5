/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };
}}}

#endif

/* is_sequence_impl.hpp
UHIQNjnCTmzcv2B+KDYIGxthvzAANvnBeRy2wybWenEk09DYBtDf13FpPKMn0hyKMsAQxqeDeoVSpiUAiV26TL2MY2T1TqM2TcE9Nlh+LQrNRhi2e2BlPjai4KkieHjPtHkhh0hzovx0bYQsfDiBtqE7h0S31ZTxfMW0ZcGF9hBUTsK74xPHGwvm3lEwykecqAA2ElFeAsNHiSYAe7PljQKCiGD3TzZNxY7gPMH8rE9A6DIIkXW4GNHxMgRW+nP75pZ9EA+cfGDU6aFbaoiyHosT5wHQzwNAkIeVqJBn9cBKbe8cvWjkAYgwgb2I6ZmZQ8vTWLtj0u/SJgEBeq7dbgx6KgHjFqAYxijd6zY9PCpWpXNV6VxVkCvsvlSSmW7gbMAEOPaV/KGqly/qWxy7CXp/OUaUD8HuLYCy8ZoQ5h31hgcG6YCgJ+HybAiEreji5Cy2G9telPLgN2xufNrb48AMscGBGY9TClmnWQASi75U52G4W8K+PoSj6e2uy9Wf5seA4IK60HbLy8fs9xJkt3W1AmNcS5PiRNpE2+h1EMCDK/tq8weXls23rUMI1hhFQ/MWD/tS+KbaCGFYXgCRyYQMVZG1oqzxjpqf3n0RGSS9g+wiqFoZBGqrBdoLowq69fDKjIPZnOJXkWMUAk4ArXoBGazo3eMQxDP2AFIuDU3guyRQgp8SS4GGWxNjzbBEC9LkpYTQOiYYa1UltKHS5auwfJUqX8Xloy8iZJ7r4rVaja8sle8AYx3R7mCGVjzNCJl6Ch+hm80QMqK4cNnuBEA75QtmIY4uM4wlgO5cOvJUxCBvReiWHouiBb4pZNGEGPNLj0leJODEzoR4kUOp5MKphCwz6S0UtRUPRt/1msjOs0nScsZg31OzOLpyGfbbcKNCAuAws+OtbokkW9RtzaArAKmsnkpkZdaBVvQAt8uOkEFS6lsb9JMB1DeAimqHGOq0LegscQRThSRrCEsKGdBJAJFqQgZpaMJ5okaumbDAPwO2NfVo8tQExsCG0+tCRlhE4L2rWHDhISv248SPnHnMgUdP4Z6qYt9OPHLwEUpzCmLE7p841i1EMHpgnD0mCz7m+3DgnqmAju2EUFXVWGqLuqtk3VVV3VVl3VW67ipVdxXXPRi/aNRaIQ9PeDxIEV6+Gemj1rYJKlZoAQRNW8T/MkcMJwsHbvUcc/D2W+GZzHnhA/sWgzk+7NYFjqzWZvcYb61vVjJYUR0TNutPj2/eUSwpZNA0Yb16njhkb6c7VF5Ph5B9bIXgodX5A+WdkSFt9l4A09eBfaxwkz5UfoUH1zuigTwwiDiC7IXSDVD6cIqFUQ7EqDE0V04CM2oyW5kAijMr+LVfxCYOvGEkNLBQaECR0AT6ESMZiybCr3m+VCzXDNeivdEQGQWo+RqRT0aRsM0aYr7e4odlQI1zdCMVlTHGrKEgfikA3mwfb/KGKCzNoqVExVYgIJMROMV0DOL5IErF+6wR2oMVBmDZ0NTyvTACmr8Zpiqs3QNVShSVFEWlRFEXJIpKiaI8UeBlzI+jaWTawAoXQcRONZ3ymg5kwLR28z/2ziM2eiqKwiB6nwUSLFhEiC4EQ2dBCf0PdehlAQESyFCHTAKhD71D6B2G/tND7xB6h6F3GGDDMhIbNkjc+Jz77mtDFUKAnxR5vnOf7fuqfW3HlmcO8QI4dkHjum+FG7ttXTwPcyB+Ncbl155zBnbZvrbTTtvbr/02r/NLc6bhUqExrhYaMj+/kCwPYcz+J0QxnKXiDsrpR8QGjT8zen4FET20rxbFoq1nmlyYGQs120EqyiPkvs6Dji/ZqsbFxXBPk3MXH6UhIoxXqK/tY+rfEZm94IgSC9I=
*/