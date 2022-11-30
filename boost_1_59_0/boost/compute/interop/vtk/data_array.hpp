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
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
*/