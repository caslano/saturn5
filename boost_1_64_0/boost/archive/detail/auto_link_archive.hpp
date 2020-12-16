#ifndef BOOST_ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//  auto_link_archive.hpp
//
//  (c) Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------//

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

//  enable automatic library variant selection  ------------------------------//

#include <boost/archive/detail/decl.hpp>

#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_SERIALIZATION_NO_LIB) \
&&  !defined(BOOST_ARCHIVE_SOURCE) && !defined(BOOST_WARCHIVE_SOURCE)  \
&&  !defined(BOOST_SERIALIZATION_SOURCE)

    // Set the name of our library, this will get undef'ed by auto_link.hpp
    // once it's done with it:
    //
    #define BOOST_LIB_NAME boost_serialization
    //
    // If we're importing code from a dll, then tell auto_link.hpp about it:
    //
    #if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK)
    #  define BOOST_DYN_LINK
    #endif
    //
    // And include the header that does the work:
    //
    #include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // BOOST_ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP

/* auto_link_archive.hpp
cVhgrolbznjYU2jUUSKBWlAknVDfiJ6sNcNGUZlklZsOzuqkTlWIdTLJhWG1GwnXGGkXHMaM6iO8fYLoxif6RbpqeVSMzEg8OovkMvTjoTgVUrRbAMA0COPhJLJxvRwdBROVe14OJIzcK5TPlgoavlAtVjM55vLOtTO0YcIjI3yN8cdtEjHtnJkugs4o/XwEOVmJhkN6O85zU2AIfVVRwezYlXk4ZnoyIsvo4uSUrvb+A8r0+kRGb7yfJXrDfpnRS2I0sVyZaRN0IRXmk+kyC9uqyFh6XH0kmwGuXqOWhyolSaixLuLUQr2+TqfXxEglQkaNrlMtRIGq2c4Z1JPz0F0CSgYhiTq9X7h3VGikTxd+L6LS6fm+OjWRDc9L9NzzEjnMSHpSORo66awZJ5eIohLlIo1UjHLj3JcwN6ISR6kFcXFM3YV28Q1vG6WIETuRW5gkiTYy1KvIrZYO0A+ng/VlhyiBNE6u5BmxTxDFkhR1+UkQqtqyyXP14V3RoEmLZRsoVw/QUlhLlTpGauxC6TbTxqmwRJg2VCj3bOvQIco3LIjuNhxwniR5gpjTf5BwtFn/EJbxFFqWCRLRJ6AzFTG1ztWzfYUxPUmCm24oqo5V4vSoCEp316PJokglUWKlUleGjB79rLEwEq5JKaKMwfwHkygVj0IU6/SJCoZbSqKikpVy/GDm13R8UxhDwZfLpWKBzLgVHBCNFSsptVxOqRIFUqmOS4kiHvp4gYqSybU5kIgw5SOJlSAXhfzK6EqEEYJRb5ivk6g4NUBzrTs5Gdej1LXXTWQF5gTFKUKxWMStOGbIQwlkIjJnSXfx5BwqjUIhV6p1pnQtctMjPyj0sWqUDZk5glKnl8oFpJpUuBrMTZIQbriKjcdcPV1HgkQVj+twP0Bc2oYuVFx7HCkM4+G61kD0YF+iZsufSpSguNVCpiK44UCaXCgKFhWsEdKXynEofKmIjq3COYisVKH0NYmkCqUCZRxzwUxjYZSk5FknQXcbJ5BSzP2AzmesXImcGIQz7cYgnjAeZYJMKVVF9NxUuHo02pQisiSx8DqhNrBni9RAL8O/GELr5gENw1UoKYrtEI2Ea9C29WRuWqyeU2V6egXdYPBDICO9uvFwFYUJb3oUR2mHEPp2Cqaj0I9PMo7806lz9aQFG8vnILFSThH4cDflOLb8SBMSqIQSiX79MuGFrYUOJ01EG54EgkV0+6CYBkKaCpptrC4Nrp2uH2Ibtn44OJaoOXIirofQrGeHrp/pWPT0aNkxjJar1/WJBH+c3SCcuRMxBIvp5qofLqaD1KTT4OqZi0F1xEh15c4N18gkSUhNIDV21Vw7zGcwJkX0uiTRS6q5HT0pF5muSrlFpAs3vGcw+t/dT9ieghLLhVwZ148zGRavLpzkk5aZiyDtSXftXHsmnOnfOVCzPJLbHWPC6gEI+gSDfsR4eyV6VLJcExdPcR9neMaLiuhJv4oT4hxyiVBsGI55JQm9toROTpRK1qc0SrHxcI1MJFBygUc4Stvw3KQ/MX6TJY5pr8axJOEibWVQ8lhSOkzBFKknvT6eCR+oAQRiY/cVbrjRewo3nNz9kEHch1W0YaxEBxWxi8ddF0MKGXtquhCMM804ZuiMWjB61ybhCNTdn4zpySm1enW8mDQmw6EISp2cI0EmT5aR3kwdD1UizsVxpB81XvrE6Zesfsb0B0i4XONlqh+uN/mjkZERAqwJkjqnY+t3ozpiR65TewEG+kSxSiVAr86On+jxO54O4xP17dhipLNZRK8gzyi6MZdB+vQUgUANXgyT5tqRnoCR2bpnbm4U5nXRhnDfMEhfZ2csD0btuIGksLSjBxLC0f8mRW4=
*/