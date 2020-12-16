/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_KEY_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_KEY_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl;

        template <>
        struct value_at_key_impl<map_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : BOOST_FUSION_DECLTYPE_N3031((
                    boost::declval<Sequence>().get_val(mpl::identity<Key>())
                ))
            {};
        };
    }
}}

#endif

/* value_at_key_impl.hpp
KyXLRY2PGx+v7C/rvfzjZLkaNcz7sYfsx2zZjzkEZcZGwm/Nef2+dT8qXyzaA0xX8mdZxv6w7D/rdi0298mSz6u2bH1VZWs5Rn83fSaMms+Dp1QNdCLcSWhLqF2T74PV1jw/Gi1fLo6MCaM+rjMk7j4yNkZPwh/N+fNB8bj5aop35PxuOb+m1VT3PZO+bRUs/cy0+yWkEn+kD0djwgDCn+Qjwl4+TCf7ssuLjIHDcto+dKGynKU/Hnm2tlHkSp5TZL9MJsysyXxtnhlkQTJu+W53sAx9tOM9aM+Rlc0L50rae6SzpHGNOm0O4MikaEeOCe052bSa5jjJk/QWyudmgXxuUj+0psfGaT42N/WZ8XfgMyOfEe3vhDvMEadLecyUfRG81po/U3sR/1h+GpVYJury3i7xd5PvpE7K+2TGY50mfonb8f6oln6Xo1G+l2T7iKlIHryrmCNoL9vYWs4DEYV5MEZHjzXvBAf2ubr8MiXuXnIe6C7ngYziccsHsOT4Hf3sqc8DYXdKX1I5DwTKeUC33nY+5ERQZnkpzXnAUnbZd9o+P0cUyXNcZGKSo7+Z1GUSWNX2OTrLdvxSMCWP4eRomSh56Sd5cbvL9nnaY8MN8iI7ydHzkCN5Ks1+snx+kiTvJ+R37RFpU05V5X28MZzm5HGRCWMdy6v3DX7HBsnIc8uIvBEuQjelX/TGwvQmluJ7W8pGe87Q9hnnpwvHnmbcJfN1Iv9K+RTvEx6h6f9td7vkeJQvAKbv5N9v5bvg4ibrdpkT1XwdlPVvqIQiv6Hibvgbyih5Lk9wk1CXfe+9RZXnceMnRZu/MkscN1ApI3dr2sZYQ5EyOi/pVVDSlFCPGPVF05M6B0nW4XTN/b0NE8eNe1xzLppd3bzwcfmeOqSkTSEFFKbLMwxv7nrZWEH1WSt+r4LD13ntLMdRDQJTjJw3o+Q7OyJHk1flw+hQHoscs5pySZO0dku57JDv74uFaU2MV3+Dl6Jcin0eNd/h2nsE3GvaGWNy6+29R6GHpF+lloyZKedAV8u1/cem9E0VguHFqphKftalMn5nBeVehy3K9TMrm4+wpMjRNq7/pQ7KR+q9YuU5b1XIhzv5m8N7q835kWNIW57KsitZ1o1l+/D6nGpZPVY0PzMwOlHGNiNoxtmMkzLoL8fdfXLcZW1T4rFVgVbysWC6LpD4D0j8DSR+T4JSxh7bJX47FXSO3Bei/vz41Zb7TSQdvaQTYE6HREz1NPETjY7Fazl3LZZ4e0i8XSTe9MJ4DdFx0Umac5eDvwe9tdcYms/GNUnXW9KtL/slT9K1VlY62MfLsr/D6tjZHztU8d7EfrD+/pP4J0r8Rst+sMZvqhlVd1IrsayI31r/GiAngQ/k3PUewZ3M5Vnjv33XHpYyzJE81CdUJtQjVPFl/ieWPEjypi+V8KhxxpK/y6rKd1ll38LnbHpYX4/WpB9S17xiuJw3Ryrrs9xF2+krVezm86cD9ZKSvqkM3OQ7XT2+Ksi8OM1+iagnv+9c5fcdKgVv3GnKU2F9xaTIuInRJV9var9PYuOjiv2+SxpvlHnBNn4jh9r4jRxh4zdyjPY3stQ1qLa7VHW28gxhKYtRsn9CCcoKObuVsrA2bihlwkiZ40osC/ntJ/vGIPmx/rbTnG9j6ptXbCnXR80INVgvYI8p7biYcHMTxZD7B/UP79MrpJecvm78OffWfFbOmtKNo+jkmbaqvKm/X/MkL42lHLwItVgu1W5elFPDzeVDXQZxXkXLAIkwy266sfGJ0QlJt1oG7I9iZVBgIy/1SeCi3bww9G8p8uFpKveYMfGq81Zd07wo5mnLZVoD28eGfq+9vHD80+o46SY=
*/