/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_KEY_OF_HPP
#define BOOST_FUSION_ITERATOR_KEY_OF_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct key_of_impl;

        template <>
        struct key_of_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template key_of<It>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct key_of
          : extension::key_of_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }
}}

#endif

/* key_of.hpp
YYboot910csoZZZo8b3tg5Tomvcbm9+sCnnmSNS8R5YS4RHp0UOBGk2/tQ3DlIk8Ki8MMk10Tr2QpUL0MfmgjwnC71aFdjLM++7xtMfwe6/RywSNDznWA8ufwygPJRrvl18GGadK6w+9xghlQslrHKZX/dT/ba2P/1jPZvn1YC0eYitWhn4Wlnm97UfyxhTRH68KHfQzRfwn2pMcNRJl7cY4i+z9qbSZJXGv9xhlnr33iQ1KxCrq9/s+v5mybc3vph6xTgxTVAm+K5kk/h11R5YSTXepaw79yZoaOXVynXKPcqp0hxz3plVh/9fkl33+nvBYJ7P899Xysexm5bjFdvRSYI7mvHpiiCkWaf68tMgyRZ3kF9QJ/UxSp+WL6p1hZmgYE3/0MsEiqS+JR3KUidyqjeljkiW6v+x9KsQK8sgAUyyx9zbPidxuX/opskjLV9Q3w5RpHJdPBphgnq6vag+yo6i78hXKeL1tPqcuiV9rG4aYYoGk7Q4Rv0p6dCxTj3vV/xhVDvntWo/jjFIh3CCO6GZpRIxe43j2a7Rfho4rpZNV75fZ5qPeo076Y/oeszQOaEMyjDNH4lLxQD8T1Gj6uP367f9BdcxURv0T3q89+2xH+3sd5z3ycZF6vdA2b/X+2/QBuskzT+rt+jZjVEl0KxtDTLNE2/neo/Ed6v5q/cnjKDPE3qle6GeSJdrS0mCcRdou0OZMUif5LjHNMDPE361+GGSaJRbP0b4HbUeWBVperXzUSb5GPhlikeS5tmWYaZoPqTf6mTEOFDzWiL9WWmQoUKPxdeqdg6f6fYnHIgskXy/ts7VNh762Xzr7bPd8sUOZ2InilQxFlmh9gbZhnBpNe+SDAYoskHqh+iFHheiLHJd+Jlmg5cVimywlGtptQz9F2l8iXRZJvVSaTLBIPhfxfQzPCXvtxyQHb4iEyEnaiykiJ8sXJWIv9z5DlGm7JRIO7JPOcfJAlZZW9fdcx2P6WMd/Fsd4j9ZniiNmaGuRd5aeLm/N2mKbfeinQmK7NmCACpEd9qebYaZYpCXhOIwxR3Kn52SZJLJL/uhlnOxG6d3kO+ce6xze5DUmaI/bjjyzxDZ7jR4itt3TKE9/i4RBikQW/UaQcRZo+7vfijFB+IfnZCjS8E+f55OlQmzJOe1s66ctP7LEnn85HuPM0/Jvvx8iT42m/0TCQYapsD+oH0pEVygHZaJPkmcmCSvVK2X2RdQvUzSsEpdkqbD/CH2LKRZpebK6YYQKDQ3qggwTLNB8pLpmmDKRo7QrPeSZJXq0YzNIiWjUcwYpEV0tXwxSofEp+iw5aiTXSIMRqiRjYoBxFmhda8xkmDKRdfJAD6PMEV/vmEw8EXFtrh7/pF3+GAlz85EQ/0PEPQSvz3n9MW33W/Xvf4gtss9nH2NE3ONKcYgCcyR+rS0YpEjK9slf+G3VwxHrUmjPhyKhndpPtfW92pbDDFFknvh9jnGP7b8rbu6KhJlCJERvsy2HmfGbwSGPReaJ3x4Je+ll5gti4It+O5+PhNHl50S+Ih90MUyJRZLjYumbxmSPWaZYoPmrkdBJliIL1G+R77z0mWKRpDUAOshQJSbtvfQyRoN8tNLFEOOj1p/TxyJjXqfzU15nmsinHZ8MRZbYc4V6Y5IFWoYci1GqNF1pnGGQacJV9iHDJEvsuVrfoUCd1LDnFKjTfI0yMcocLZ9R54xRJ/VZfY0cVRIj8kCOKonPaX+GmWaJ1mvtwwizdF3n+FSJ55SbOVLXS4s88RtsT42WG6VP86jjkKdG/CblZYBplmi7WWxSZ+Yy5T5+ZWi+XJ4YZJLGrHhi4aOO/THvedw3gO0Pf9x7H3RMyoQPyRc=
*/