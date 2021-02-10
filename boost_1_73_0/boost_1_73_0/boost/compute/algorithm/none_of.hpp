//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for none of the elements in
/// the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see all_of(), any_of()
template<class InputIterator, class UnaryPredicate>
inline bool none_of(InputIterator first,
                    InputIterator last,
                    UnaryPredicate predicate,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(first, last, predicate, queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP

/* none_of.hpp
tkgkYK1VbW+jRhD+zq8Y0S/JieBcTu31rtGpJHEbVL/JkDtZsoQWdgjbLixilziW8uM7u5D4nFa6+3BY9sIw88wzrw63Prz5YZcXWjj45pW5b0YXnc9Gq079jYX5f4Mse4LhQ4ZbOr/D1QQOVk/ZKXyX1ROcOKts9HVp77PsO9xtLUn7M7HG28zekmSwHO2vVbvvxH1l4OT6FN5++PArnMHF+cV5ADesESghMdjk2N0HcMmd5PeKPT6GGj8FgAaYDI8A00po0Ko0O9Yh0L0UBTYaOTANHHXRiZweRAOmQiiFRLherjbx4s8AdpUoqhFnr3rQleolh4o9IHRYoHgYYFrWGVAlIRA+F9oQZm+EakJyj2Cwq/UIY0kwqRWwByYky8kdM1AZ0+qPk0nRd5IimXBV6EnxnIqwMvWrqDbEpmZ7UK0Bo6DXGIDVD6BWXJT2pBSRsO1zKXQVHGiRw4ZPVAcapRzhyFSgHkJASMZsBVYTWmIvjD20arT1tqtUfaRIaR2Byr5ryB2lhfS4osQH0DccO6fvEvHsZcyyS/k3SnbgzkE1xAr8KIE48SFnWugAvsTp7fIuhS/Reh0t0g0s/4BosRnx/ooXN9Qbgrx2gI9th5pYdCDqVgrkR85/4KSnt2DrmdWixqzsEOEd
*/