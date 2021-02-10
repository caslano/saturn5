//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/replace.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies the value in the range [\p first, \p last) to the range
/// beginning at \p result while replacing each instance of \p old_value
/// with \p new_value.
///
/// Space complexity: \Omega(1)
///
/// \see replace()
template<class InputIterator, class OutputIterator, class T>
inline OutputIterator
replace_copy(InputIterator first,
             InputIterator last,
             OutputIterator result,
             const T &old_value,
             const T &new_value,
             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    difference_type count = std::distance(first, last);
    if(count == 0){
        return result;
    }

    // copy data to result
    ::boost::compute::copy(first, last, result, queue);

    // replace in result
    ::boost::compute::replace(result,
                              result + count,
                              old_value,
                              new_value,
                              queue);

    // return iterator to the end of result
    return result + count;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REPLACE_COPY_HPP

/* replace_copy.hpp
+COS8+HFx2cYOyt9GO9Hi/N5Plvm00l0U+VPHLw4vqlmlI39n3TSiDTpgIQRFIShXq5GnOIgIeSYtWITRnlfGY+C/jY8stFqoZwHNImrTsoBAVQoRjjzTOCD8QYIgGpzBjgJNHdrHlH1UXdyNR7T2/BGIy0wQHjdCt1Z+YCT7VhBw/BoB6MgRnhql/LxM0hE1AdEuSX41YVUMTNdCB+addqwDadAIssqLikeDEByRryGyDa88wxXYUJQMClTWHDnyBPbFi3U5Q7ZkLzfMinK15FWaIzc4brjHmHrsCEZtRlNkbThjglFoxPlodpsbblCUzjcbC89IhBRgeK8xHh6U63RThdagm15ISpRMOJKm0QMCblinXR7Fmj8eejLzoLv7b17HaVrEw0gr8IsEH4KnC2kp5ozZJ2EmDHQsk8o7RVYi5Mf3A4rbZpByRwD/CJuuVguZ/TdIEKsS3c+mG+y628JxRofHXpOfFAHMTv2D1dQmZ4pHzUiDBuvH3ScUKP2A9GF426AgOCsoUT7WmwD+EDi0OCO8PMX8PG4Hjbi3nOZF6bqDFuJTaKbTXvmKxAdNvXzmH3K8nH2Lh/ny+sowztREzIsXUUEIrzMlG8llSKBxSUWBL3nl5mfPK7o3ipTyMoyXJ2BvILt+Wh5
*/