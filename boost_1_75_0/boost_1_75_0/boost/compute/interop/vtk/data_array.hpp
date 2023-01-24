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
yBeTH1kQaiPTvWofJn1uT6rjOFn76QWFdiIC5IXUtyqvm8CW7njkboBn1K+UVR6uQGjdhFtNTQH9BI5WoylfO28j0qW7M2Fko7bXjre1qKyvHaJ+FyW4/WWqHll/nN33YU41IMq/uvuX0drgi4XgYvqoP4wdlxmgzwIX5c1iOB3qSKsSzGw4HUz08FbBargxrn9DYHOvr0lLZkEqsDYr5jVU9SRZe/7z/jToRwrf8TtpmD8C2KMHvTbGj1V1jr+79idaWuWsEW/ChdgMRSBLQnRL58QEBNKbt1eBY4bXP7ZMmG/+eoLP0COWir9Lk5JUjKZqGPE7+ybldLtPDDnilwtcc8sKx+RdaPq7NobJNRpTpSJOspwgYxwH78LBhnYpEtk2A1LgKuYcBQzwR2ieXXcEErzitfxVyWa2BCamPsERvktSHDsdH38hLYrqKpyLi1akfdTl0+4tW/IElq9NjPJIOtVaPPonuW3UrnLSFRcaXrdh9bZKk7MNteH3BFM8K1x/SXnZar0kHTjexyuDWAtadb7+sSsSld8l8vv0iV2vwTcBcopp2+Wujrl+lHV0ix3S6kZZGbbg4Eruy6sPNMbmF5Fv7dvdnzYy/WQ4ph0Q2QS/HylSYDe9J4+uppRb9wo9qmW34qAz2qL7NQY/alLGKg046fjeOR0Kaec1JSyrZJMkySpjKWcHUuTsoMyBrO36fV7ylw2FbK3C
*/