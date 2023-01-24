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
PU6XMuReKSg0bw5i+lHTp9jZDj2OgffchqNRizEKKSpx9xm5k1MvyzuNwwlwK1VawN8cxv5d8LN03hUe00GiQZqiz9yUlbbGl6NoroMj2eXyyK7ow5UlgySK15sUwB+g3zO0o6gze93drpGkV1M7r9zP79Y9rtkO2Cm4QzUOLptilSLe/umMeyOwr+fQlBfJS/cDFEQyl0ZpV2G646MjxVferWNCWNM9pCBoJt860Rv6nl2eYaYrbN9R8460PL857fNx3aHrA01lP3hkE5cvLNOW4wwgG+C+SRo60WDqiJkDh+AMRrAMxdvQqozv9qYrc54PN/PRu8wLl9xqrfM3ecv4mUwWdcEDTin2qstrqjdelmd8I/nNdJceRUNwrsoww3pHffMzxsedAgu9M1yAO74nhOFE5rlnD9uo5l5luBm4HdeKZg8ATh/RA/kMRtx5JrfgogX5JYOr6I2mLG5ABS0Nx76Br0rfvpwI1jO+uBW+fX0zzfgDRDiFvoWHJZQu8FSO7i4/Rgcco4GV9zVtnk+SqUHpGns8DwiM8GYQBp8FHgwZNJcx/NBj2Sy6Kk683LkAIRU/riEIUxPJhc9cuAJb/xnm+zQkoqOcLp0oWWHoW9px11K2O27sJfEOXXBxDT4uza4gXARc3jxa4C+nhX5x9GW/evUOcQK92nTO8fhNscjE7pICT1TcsV+REN513+jst/g00LlCThwM
*/