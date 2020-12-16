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
ne1Lz8upmI6ln0b0/d0Blaew3MyxEzcs+fbWKCf2nYffbfhgFoVdxaVnnTa2HDXjqtwXRirfiSp1qyCqOBOibZ2HT6qWhm/lrueldkjw9vbDjJ+zrPF6luOxp/mignjNbUkrfs5z3m3cO5ZhEiZFDl51u2L4rL/ZyLOfhg57Yk3n7c7zJ4103awoHb/MiNfY3oAZNlBX9HbPKi8uc6ey9F2HER9C5SmtIvTqrqrNuDULzk6j79HOThWlEYdeYDUzsXF24Hik4Xs0hkrWhJg9kS3cmx16j25DmJeeG3ueY9UKQHrK8/HifVMKDjEzWOg4h2yBXc979PNRXNmpawfsIfDZwbr0jJ9eeexAP1fNGXxu5DuFkzsa3/A8jUbdbvPCewxbhTwv3CzNuCe7KO3Y2TV6Cxe+6HOIb2Pwul5V+V4VKgfTztgZF1tpZmloV54l0lMKiTQl7yWDt/ArJ3HCALxKQc38Xmmla8dJlXnW8MnDg9NDpq1BfrUzq8GXOXHsl6XL+WaJsYdvz3v1O8nMpp5U+JztCfNLTwKTYUdw6L36nBoFAc1waaC8Vbi0SIcd6kish1HP0m0jIo0/s1ynKtkLfw0/qbholPH0F5dEeAkug+u2nnFHGtsvrHV5ihc3P8M+8iDV44tAUzy4lTMhO683PtwElB7cij/rRd2PrKoCP4788L/VvaxSYEnuR0b6s9O0n6TVVF6oVGJNZU+PsZxzzFQfZvnJwEx3YvjazjD8bvfxhDn1cHKZdnQftp2b669yMeHDTtmfvXZrgzHPddWOhoY3/Az+S6MNhohDulwFLdvZ0PiGVuHLbqzQ+EZWuYfdS7SOt1Sqm7LvC3OoCVERpv/QgX3dONNm7bPdOFkM2MG9/GadOLxGocqcuznDdrUW1RzD4e62C4dMIu1f9eCwQ1RjOO/vxpqxnv/RhcNukHB4g68bZ9qvXn2XOmYqqwzDJHC8/9p2ZnVIP1Yj78BFPe4dLd1+FdM8PD1kDYP3tAfcinlmdZ3fsTgTB72C7KpOZ/yiQ5EXmfJIpRkmqdMtj94L7ZF3KxpnV2ic+ZOTU/Hk5Gn/5NQkXTTY2UhNe/rd+Dj1H1pN5R6GcK1j/zYbn5NT+WQ4FecV1eKpmucVGg+GNL9T/b5Iiwc2iD0+zv/K5dRvPt2O/v0hwQ9YkzCX/1kjTzT1IE+PGWOyxGUJiwo2Usv8YksmGDn9e206Mg5fcHZHvJmki/BuRjrArW8ROFAn8XTCUMF5W03cw5lqTypVMGeNbmvh8FwB3hPZ3sJgboAuowMzb9zfv3xHG0PDsvHjHG3TqWytNzmuduNQNvjl3qAbN3++NslD3d+wG8dfuFHuNZ66k3AdMdZxxninesaIgqjMC58i9NKlOUInwWazxmKfV1ZFVaZhJtEPI78Quj2V+8pNch+8rPLdz8kjJ7Ez21phjhLKe8lDmacLWp6cvMp836GbgGl+E6Dn6cUCC5vV0nbLwo6s5qWLh02vLILvwfLsofFFVhIkNAVFicJH/mJ4hxnxlmUeP/tO7U4giZLY9j0W+c1eEEkVeIu5xuIOpaB0gtJn4JPqw8U4n6j40sp9pyjcJGJ45scZLK2cnxYsuGu+9k7jjOm5eex4lcUenKSS2E+kyY9dtRv3LqPv0vliO0gdN7SZ/fzMzGCZmrVSgkdPwM5Y4/Otws3soEoDhQ+G8mas13GDt2IxQ/0gYYG4mfNbK7tKXKBK5S2t1K5c0k5UbF+7OjgfqDHjBrBHN9auws2LOEz/a3s/uXbh7PHUTZp+JCgS3w1cXOvXO+ujsF0+IvnUfBSWl9iOU5aRsrVG9FFL3sF/UvODiCMnopzTXd1h0R7oz1o=
*/