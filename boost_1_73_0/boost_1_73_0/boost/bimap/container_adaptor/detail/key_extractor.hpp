// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/key_extractor.hpp
/// \brief Key extractor for a pair<Key,Data>.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Key Extractor

template < class T >
struct key_from_pair_extractor 
{
    typedef T argument_type;
    typedef BOOST_DEDUCED_TYPENAME T::first_type result_type;

    result_type operator()( const T & p ) { return p.first; }
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP



/* key_extractor.hpp
jHYstSvN5pNAyiOzFLXVJER5oKDcUJpjqHWONgSHlbcSh5yGBP9naY5+czCazEBntIC7RQdWwkkXw8Pd8rfp/RIeRvP5aLJ8hOk7GE0emez93eSGSi9JzAI+VxYdiVuQm0pJzA+aX+9Koijpw/DmdjG+Zv3ZdPaKdAXJIaeDKuDDyjOjqVd9yISgAkq1Ms+MGCYtmLi+lTpTdY4wdD6XZlBen0xxczQdQtMsGzJHXwFOBsFWuHZSr0l7xdHfu8ZVJiqxkkp6LvmJtaYRvuCuLdDEUOf4UvimuVsRi3/VkvLb6sBPg8uLwQVnW6zMNtSXliS1Z0Ld3RqZ96K/I4Dx/fwD9BlzdXjKTM6EDt6Gx9t0+v4qoneB920YUhRun0otfbfHMFl0eboHzEhHVh8WtONpO1gtNti0sHBuZ2zOPjjmSOPQ0/4JBHFQnM6W6f3idj4Z/X4bQ4dpOkHmLGo2WiwepnPquo7DzKJnXGspVGgnlWqyjVu0e9qfzok1tntiTUeIbnP+f63OP5BeZapXdGjQMDgUZZCZzan+DG1hbLNrg4MDfZPqo0jVxDUZPcLHJWZ/Ar0BtNZY18Ip98zwzbFavag50IvKUsGLLrUvQcjj5xo9KGitmL+B79yT7sTRp/8STlbubZBlrd6J
*/