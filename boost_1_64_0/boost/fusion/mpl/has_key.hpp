/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_10022005_1617)
#define FUSION_HAS_KEY_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct has_key_impl;

    template <>
    struct has_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply : fusion::result_of::has_key<Sequence, Key> {};
    };
}}

#endif


/* has_key.hpp
tHGut2PTNPLdTRkNz1dzr41wDhNj2YZh2FjkOkbh8SHnMsRp6ptwpKFwmvKvCzg2kir8wjjDBiLe2evFWTYQYnEP4/UjWWkgq7Bpy0vj4Pp6bMjpN1uapuyoQoW+yTqJU9OHj+m1uMJjjU4RiHV/8/s0AtTx64VO7jXNy2WD4f1yw6HBlFEmbzAMNxg5njwh5PSd4a4JRzcY+P1RzmHcTxfeGGVkg1lAnxdnZYNZwHnY0axsMKtZ2PlelOcGQ/4Q5n+2fKhOeQ1/3upUp2IN9ZuhjvXsCr/1Khm31prW+0nafaq1uK/afn/I6bpqfiDUUwdprbbmppa8Xmq5k51OE3q+b3RqfsK3tHrdhX9tzG+iumsvPOf/pGXkPkDvU0ZvU7sjB/p+vD4nyp6GsYPnzfEmDMrsMRFG3kuMhBG+R5Q8UTET43PjZq1h6zGWkXs9xUgYFA2Xh9YxEOH3jw11Cl3m82ehvrbQqZyE3gvD95nEXOkXoU7F7cwnuPNf+uUILt134T5Kx0dLRtnyg7hT8CTLyDIrWF3Nk5vfsbo3rjXM62UYJ47dZXIC/Ta3gcfEGL3+tRkNR68FD5ih14JP0Gz36LFs8QNj/ZMjjK9LjL1RhqISTEkw9GgweTYzKGCU72MtI9t+NxaGb/t4u6THDK0WH500zj/3Y70oy74M+t83RTg9PFXg5z05xmqfZvPZEcbf6KsKH2Q+Gq8czjgv/SjLPhB8lTeP5KQftJrxpdE8D23Ej2V5i/N2eBPlux3/jRziuK9+TIT1fhH6v26E8b4R9u3fAmahUqk1h+/bNGmbq9ZWd94Kb2WOViWG3yBe7zSWloL23ed+ZpGeFqqkTa5Sa4n9q8FbY0y9Ua/UuF/7VYxxr5+vt9XZl99qzi+SddAX/VnrfoGM/agvQHeJpIYX9A0/UrpPAf3TEmfbv6SZToOCSVjPv411t87vs9pGmT070GmTe6VKt5hEGKW3M0N7zD4IzueW0FurGCY66L9+LPXscXrKBsWBtYQvg6FioPUl8bZ+8nup8a1bhP8VqdONtvVaKw2C89njMBr1GnkEPhxZVn0Oh6570cMK663hnBr95/OgUwDrdILMtYxhIG2ssT7fMNwK5X3Kd1qOWyJzg9+HHGVw2NBqVRle8oeQ8/n0tgtbMpwsDxHeCwznfKlsyGYfwXD6nlfyT6N7K+AxO7/JDHUAmUO9BD9H69n97SWM1y+2emausMWXKMbnVrzzF9GHldYW9h5hqPJ53HtpRG+26D5VpUYLl6r+mzHWlRyluiXWLJqoL3SO2SrrOuZbL7WMG6HSXofDmn+Z5Xwx8Zu5Px7F0D9yXgFfm9pFvUp166YLrPc/bfS6nE8kn7E69Rooy77UO+SYnkV6sEqL/L+MWdpIW6350vQd9jL6U7Y5suxy+3SFHl7z5wDQFm84ZEqT07OzR2mfe6ZMqRNttWd0qoyqmNstXUroU9NTfm6MNmT0NAHwDZZD3V/bpq/NL7unnFIDXEB6PrJb8Efv5F0iLuePhXqDNjSETxjVaZxdTlYQR8D4z44gDYNA9z7lAvqwj2vdPx9+pp7ubjbRpkJuhWqbuk2k45NaD+dc+feHeqOatt42n4kYzQwbMNYSPhDj1tsLy54W3/nM9UezHDL3NYVPh/z62vDBojbPZTcChpoZ7RLXaB+I12sKnwmYtixXYasf1JzPwBnE9SGti0Q30E5MXJ3WyYU2WSGP0/mbXkUwC+3K2Hqd1tFPov6eKsOgLuws+YykY/63T9oWfWBkjJ5Uo3hkHJsHrigYt71HbUTctd54mozDb/9J/cHCvrxZJaRj/2VD6tUVCnsZ8+k7yvQtr3VW1tTd8n4=
*/