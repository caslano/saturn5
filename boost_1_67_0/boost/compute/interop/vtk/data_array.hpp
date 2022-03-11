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