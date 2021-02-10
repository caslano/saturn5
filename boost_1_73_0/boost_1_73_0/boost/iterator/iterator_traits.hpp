// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ITERATOR_TRAITS_DWA200347_HPP
# define ITERATOR_TRAITS_DWA200347_HPP

# include <boost/detail/workaround.hpp>

#include <iterator>

namespace boost {
namespace iterators {

// Macro for supporting old compilers, no longer needed but kept
// for backwards compatibility (it was documented).
#define BOOST_ITERATOR_CATEGORY iterator_category


template <class Iterator>
struct iterator_value
{
    typedef typename std::iterator_traits<Iterator>::value_type type;
};

template <class Iterator>
struct iterator_reference
{
    typedef typename std::iterator_traits<Iterator>::reference type;
};


template <class Iterator>
struct iterator_pointer
{
    typedef typename std::iterator_traits<Iterator>::pointer type;
};

template <class Iterator>
struct iterator_difference
{
    typedef typename std::iterator_traits<Iterator>::difference_type type;
};

template <class Iterator>
struct iterator_category
{
    typedef typename std::iterator_traits<Iterator>::iterator_category type;
};

} // namespace iterators

using iterators::iterator_value;
using iterators::iterator_reference;
using iterators::iterator_pointer;
using iterators::iterator_difference;
using iterators::iterator_category;

} // namespace boost

#endif // ITERATOR_TRAITS_DWA200347_HPP

/* iterator_traits.hpp
To3scRC8O7uA/lG1Gz9mq449ZRXPgP2BZsgQFiLtw17iIEzxvaPO5WPJRq5jYKdBjbMsrVioCixrVwaSBNkvMwVXCNNfSbI87zznUagsZyZAlbGPE8p8HBfF69WkXpZ+gFZ85uxpgwY5essa8HkM3Ya5nEyUEDrI0ZtdDNkcy/lboBMGP6XZl23ZOx/J9m7vMf+WafZVgEP2GGUulncUH6dU+7xUn32VdtjRbzqDjUam5inx7xlN5EmHP7ytwt/gKYMY0IY9O4IWvhWI+X3FZm0ykEvOYjS/b0qQpE01pB/esrenbkytFLf8o7dSARJfVtDIqr1KMmNL4EfnOPul2fkpxh6D+QyAd7zBweAFODxm4yds/KQY5OIcsckCj4C4PziXtoL7DbyIBIN7QfOBtMe42SqvDxJ7yEO1ofBP0B6/PsyQklUGmLAPMdPC32Xp/1BLAwQKAAAACAAtZ0pSxvrZDRoQAADnNAAAIAAJAGN1cmwtbWFzdGVyL3NyYy9NYWtlZmlsZS5uZXR3YXJlVVQFAAG2SCRgtVt7U+PIEf/79CkmwNZaWT+A5TYXsne1xjbgYIzLNgd72ZRKlsa2giwpkoxhc/nu+fXM6GXLwC4XcjlrRv2anu6e7h7d7p//uD9tlz37Z4j/G/jD
*/