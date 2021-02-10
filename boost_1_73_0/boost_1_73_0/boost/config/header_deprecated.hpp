#ifndef BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED
#define BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_HEADER_DEPRECATED("<alternative>")
//
//  Expands to the equivalent of
//    BOOST_PRAGMA_MESSAGE("This header is deprecated. Use <alternative> instead.")
//
//  Note that this header is C compatible.

#include <boost/config/pragma_message.hpp>

#if defined(BOOST_ALLOW_DEPRECATED_HEADERS)
# define BOOST_HEADER_DEPRECATED(a)
#else
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
#endif

#endif // BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

/* header_deprecated.hpp
uMAB2Q3tznARnAdIPg1Ns2inmqtODHY8nYI3i0OcIW/mj3MCNooPK/ioztsN4/Z/KVtEZuZsTf8GUEsDBAoAAAAIAC1nSlK5B52fEQQAAP4IAABCAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fQ09OVEVOVF9MRU5HVEhfRE9XTkxPQURfVC4zVVQFAAG2SCRgrVVtc6M2EP7Or9jSaWtnCE5yk7leLr0pZzsXJg4wBl/qGc8wMoigHkZUEnlpc/+9K4Gbt7bJhyNxhFe7zz7afVZxVzbsfLPHcjUcvPik5pPig+s2KBL8d5qpfw9I0zvofjBwhesrUo3gPuouHcKrou5gYKLSPtexfk/TV6RbaZL6z0gHr1L9ipYuso8f8+ZWsMtSwWA8hP13736GXTjYO9hzYEJqRiuIFa3XVFw6cJwby68lublxJf3gAFVAKvcRYFIyCZIX6poICvhesYzWkuZAJORUZoKt8QurQZUUClZRGIfR0g8+OXBdsqzscW55C7LkbZVDSa4oCJpRdtXBNEQo4AUiIH7OpELMVjFeu5iegqJiI3sYTYJUkgO5Iqwia0xHFJRKNfJoNMpaUeFJRjnP5CjblsIt1ebJqZbIZkNugTcKFIdWUge0
*/