//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_VTK_DATA_ARRAY_HPP
#define BOOST_COMPUTE_INTEROP_VTK_DATA_ARRAY_HPP

#include <vtkDataArray.h>
#include <vtkDataArrayTemplate.h>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/copy_n.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {

/// Copies the values in \p data to \p buffer.
template<class T>
inline void vtk_copy_data_array_to_buffer(const vtkDataArray *data,
                                          buffer_iterator<T> buffer,
                                          command_queue &queue = system::default_queue());

/// \internal_
template<class T>
inline void vtk_copy_data_array_to_buffer(const vtkDataArrayTemplate<T> *data,
                                          buffer_iterator<T> buffer,
                                          command_queue &queue = system::default_queue())
{
    vtkDataArrayTemplate<T> *data_ = const_cast<vtkDataArrayTemplate<T> *>(data);
    const T *data_ptr = static_cast<const T *>(data_->GetVoidPointer(0));
    size_t data_size = data_->GetNumberOfComponents() * data_->GetNumberOfTuples();
    ::boost::compute::copy_n(data_ptr, data_size, buffer, queue);
}

/// Copies the values in the range [\p first, \p last) to \p data.
template<class T>
inline void vtk_copy_buffer_to_data_array(buffer_iterator<T> first,
                                          buffer_iterator<T> last,
                                          vtkDataArray *data,
                                          command_queue &queue = system::default_queue());

/// \internal_
template<class T>
inline void vtk_copy_buffer_to_data_array(buffer_iterator<T> first,
                                          buffer_iterator<T> last,
                                          vtkDataArrayTemplate<T> *data,
                                          command_queue &queue = system::default_queue())
{
    T *data_ptr = static_cast<T *>(data->GetVoidPointer(0));
    ::boost::compute::copy(first, last, data_ptr, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_VTK_DATA_ARRAY_HPP

/* data_array.hpp
ue68Exw4YK7F5Bx/+p8uV2oQJTXN2DdofYNNc5qIVJu9cGql51rLfuMMlRtDzFBIXCR6fDzLM9VhpoozUQEyQwIuU+KF2as9zTN41iGxCJsjVtUBGabZxKiTg2aKtEGaJk+KUMoXNsA2pnEXvjOG6Re9G4a5AgKd2O/6vOf6IpAdtLZYdfZQqj8vuB89YpUIhfMtGt9MPzWa1n9HldAGl+C+EJcnSkWbQmPdUPXRdP5CWRRcTxu0giCKFRymd+msquZCvhyaZA82bf4nDlFAv7ZwkM8loPpCOIeu77OYU82At/P8LNAeWtjANkargrFenVKf5FphsDhw7YT1GUJgwCYdMa4KHAKBkPkiDPEKnU3QLnytFHVNDkWeB5lauTna2IbLdK4sSRYLdZL81BKTabTuf2yScY69D6TvxPpsyuaXvLkZpJx32dpbhRg+KeK7KWbI4TvT14/FEY+C6Duf/Fb0qURI2DGCVxzod/whGk9EYsAvhq1n5wf81tlL1bPvJ6KiBrIssr2IMO458nqW5zxfVS2Au6D4WLOi2DzCNL+1CnapE6CI5OXIew==
*/