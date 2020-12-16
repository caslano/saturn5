// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/generate_relation_binder.hpp
/// \brief Define macros to help building the set type of definitions

#ifndef BOOST_BIMAP_DETAIL_GENERATE_RELATION_BINDER_HPP
#define BOOST_BIMAP_DETAIL_GENERATE_RELATION_BINDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/apply.hpp>

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(                             \
                                                                              \
        SET_TYPE_OF                                                           \
    )                                                                         \
                                                                              \
    template< class Relation >                                                \
    struct bind_to                                                            \
    {                                                                         \
        typedef SET_TYPE_OF<Relation> type;                                   \
                                                                              \
    };
/*===========================================================================*/



/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_RELATION_BINDER_1CP(                             \
                                                                              \
        SET_TYPE_OF,                                                          \
        CP1                                                                   \
    )                                                                         \
                                                                              \
    template< class Relation >                                                \
    struct bind_to                                                            \
    {                                                                         \
        typedef SET_TYPE_OF                                                   \
        <                                                                     \
            Relation,                                                         \
            BOOST_DEDUCED_TYPENAME mpl::apply<CP1,                            \
                BOOST_DEDUCED_TYPENAME Relation::storage_base >::type         \
                                                                              \
        > type;                                                               \
                                                                              \
    };
/*===========================================================================*/



/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_RELATION_BINDER_2CP(                             \
                                                                              \
        SET_TYPE_OF,                                                          \
        CP1,                                                                  \
        CP2                                                                   \
    )                                                                         \
                                                                              \
    template< class Relation >                                                \
    struct bind_to                                                            \
    {                                                                         \
        typedef SET_TYPE_OF                                                   \
        <                                                                     \
            Relation,                                                         \
            BOOST_DEDUCED_TYPENAME mpl::apply<CP1,                            \
                BOOST_DEDUCED_TYPENAME Relation::storage_base >::type,        \
            BOOST_DEDUCED_TYPENAME mpl::apply<CP2,                            \
                BOOST_DEDUCED_TYPENAME Relation::storage_base >::type         \
                                                                              \
        > type;                                                               \
                                                                              \
    };
/*===========================================================================*/



#endif // BOOST_BIMAP_DETAIL_GENERATE_RELATION_BINDER_HPP

/* generate_relation_binder.hpp
SNgjS9sIpW1duneZZcanTfKY3unJPML0hMeAHdq38jCmm847/Cd+86LTs6BssWPJq4d6LqVFfvu4srVnG/saxpM0ay9KqFlq74rC5Jow3bCfbuxfdAqjxkTSa42Jk42fGkabju6Y+OfDHBND8t6hfEh2UvsPTDqj2vkqTdN3UERB67+C6bs/qoxq7bHG//1TOGLLdvfMuKEkF+n6aXH92u9oDvcy3b0TbtxR/UmTMrNaY/9VmA+C7TAuT8M0Tln5iamXj5kwn3NGE7/yqHi6e7aZsbgPMO7dlN+w/xxTJtWkm9qYX60Hh7+bzjZ+phpZ0/C+rh2Sry5pRd3bZaW6t9tDVN2v7Rhf94F+jDUx5eQxdnrW/U7Vaw7uNxl3O5glF3sE9Z+r+r/J3LPjj85beUZ83tqQt90xefMYfz3zttvK2/XG3Q5mnbl9FPJG/Nyz4o8dwzvF560tedsblzeN4YnGS+t9XWncFcTNE36OIE/h95W4uae4o/PDg5QPRdYOk96PeGLy05LxPxSmvW/fLPfDyku28uLXl+45zrtenAdi8hH7zeCdF8Kpzbl1YwdT/Rh/h18/uVH1Y8cf/d3xzPGxecOQt8wEedN3h2/+MpXuXNzXG/e4oJE+9Ajy2Ft5XG/uxTwjVq97pncd5sXmU98w3nmTf2LBXXVnvEf2DB9BfrKj6szE68qYlwf8ZbG9ZYpbL+vdWllyb5nu1stuVxj9b6emvdS9Zv9z1cveW/fpnGU/fdFfNtxbdttPhrr1stJvk85qR3Mgmkf5qbZvllr6y3PgYDgEDoHD4MnwVPgJuBAOhZfDYXAJHCmZx1PgbXAEfFz3dRa45iOY29Bz7bPA++AvyL7wBNlzYD78GOwHz4QDFN9QzDrF11bx2WffTld8M2AqnGmFa1S4VI9wn1K4M2Ab+GkrXFOC5zUo3DV63jIr3M4E4RYqXI3C1VrhdicIt1HhblO4TVa4vQnyd6HCFSp/k6xwBxI8r0zh5uh5c61wzjb/cFsV7h6Fu9cKl5kg3A0Kd6PC3aRw5Zg8hXtY4TpgZirc8fjLhZnwFJgNR8IucDLMgdNgV8ls94bzYHfYAHvCRt3X2an6/uc5ep59dmqR0lmsdJbA9nCWld5MhV/tkd4CydCfrffsHDgCjoFT4LnwEjgRlsCxeu/G6b2bAK+Sezi9OxOkd6XSu0rpXa30Xm+F350g/GKFr1f4JQp/hRV+b4Lwdyr8XQq/WeEbrfAHFL69R/gpCn+x2u8lsB2catfXA/7P/5zCz9PzK/X8+Vb4zAThH1D4Lyv8doX/ihU+L0H49Qr/BYXfoPC3wOUE2nFf6858sOU892Mkzyn5zXjdlFMkl3kI2vKW2zBNYVlK/q4/O16nZAEmpEsSSrbxXUzsmQqSU4yVS3T1QRZiXP2P3nofXbnBiQl0O84cS5zI7R3CdF7a3hmJmYZpwGzDvIDZj+n8ec7fwBRjlmIaMTsx+zCZV3FuJ2YKZilm21VJOcDklbySV/JKXh+965is/1dWzDoa+v97OxlmvWUQGwPZgVE2p2RRZV2RpjSqSo18wJIe7EcKr4FJPiAX0wljdNsQft1d4bmQWRV1mt9ZqzkQ60wA+ctydWQ8q3nsQS1YG1+r+Q4nZn5mUIrxy53IWtOP8NsUTpNRZ1fjThRKZ0JM2uTffw1H7iktnp/hGUqv7zyhW64FWkffh+kq3kYedrp5MGIJTgc37TWuTMJrxs8PlI9wmFzZ0VGxGTv/dXB1S1TgNtqU6dvG79ed06mPTtj/RUbvzua3axd0EvH3CZ2jTUmmbW+ZbMNxofpTedTIHi6LCqM/qJNJI204365b7CoXytNd6nwFPwc=
*/