//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for any of the elements in
/// the range [\p first, \p last).
///
/// For example, to test if a vector contains any negative values:
///
/// \snippet test/test_any_all_none_of.cpp any_of
///
/// Space complexity: \Omega(1)
///
/// \see all_of(), none_of()
template<class InputIterator, class UnaryPredicate>
inline bool any_of(InputIterator first,
                   InputIterator last,
                   UnaryPredicate predicate,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(first, last, predicate, queue) != last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP

/* any_of.hpp
5UsvFck8yqSEeEeny+6tJub0cN60U/za/XQeSAJSutED7+LHCmlz1TRlFXzcXEk/7/SOd6xjl+0V/KXl5xA9Dz71XzyO2nP03QAL67wxnXPm9pdUiOOFedW4DKU5C/w3GkDLBgkRqE45Ts7oH8NW5fd1lFk9OQHrMB3XHA+PhG5GDwgJH75HxDXOGDZagJl+dVvoq3qbSnJakPR4tpIFRgmFLIJU/o6l3priV7HpIw1d7PPSw/kkJQIPrvgqjUxHgt6m8ZZGal8i2yjVAo1qd3eJs+Fn+Um8NXBxAVxc48sljMOJLiLMglSd1RVvfdFi5rB056r/393a8gD587/qWOCG6i+j8f4j+ny0BSmkvkoihvXyhEqYW1TvGM6keW4HSQidpPpHt/3SCxs478Qux7fuklGYc41AO9uBjoYsr+WOi+OjP5gIGyZBVPxWG6TXtkm7UK0LcACtL4BipVrUm4IciHg8bW/Hx79n0JzZWf9rsey1DQLY2xt+/JZ04xy7wgz0XCP0vMahN3dnbs+Vk6qFm+KYwfsMYiS9A3iRAF0xxh3QZKcYFZIGHg==
*/