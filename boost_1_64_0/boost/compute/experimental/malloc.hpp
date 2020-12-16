//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/detail/device_ptr.hpp>

namespace boost {
namespace compute {
namespace experimental {

// bring device_ptr into the experimental namespace
using detail::device_ptr;

template<class T>
inline device_ptr<T>
malloc(std::size_t size, const context &context = system::default_context())
{
    buffer buf(context, size * sizeof(T));
    clRetainMemObject(buf.get());
    return device_ptr<T>(buf);
}

inline device_ptr<char>
malloc(std::size_t size, const context &context = system::default_context())
{
    return malloc<char>(size, context);
}

template<class T>
inline void free(device_ptr<T> &ptr)
{
    clReleaseMemObject(ptr.get_buffer().get());
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP

/* malloc.hpp
Z3CcMyKa9J7v1jMc/iFg0bkszjxf8fksTjV1XtnI4oxXNMP33SEH5TSXyJzz5QFWOZjM+jPcrMySiBPLbCaDZ2VWizixzGYjPJZZPcJjmc3FuMpM23GVz5nEn2ItRv34TIzjIZu4xCGCI27WvO4pMcFSvV7atGWH5/vnVi/ysK2bu89QrONzR3hY79mbdpyqMdUbvbIkvtS69n/Axxl0CJdHpxTv+pyPa9wl+nObh6exhca1P/Ax1ij4yH2/DLBRRivBar8OsETXE/j80cfGWdVjdPXa0/tPH3chpMq+WFOcqdGk9MkH5Tr6oGv4hQ8F14v+PKdL85oeHyxPpZqkMWlvjDc1CX/m29+M5u/0TGP/D4cYhcv8xTzAYnbZcAS33ZxgGPIWv+3KZ0xJvDLnOuU6LruK+HScXtB7qlOpeVZdfl3XCDZdGdHrc3odU9PrHS9015uC0TLqopMVq5F6T/JhxdBGHUs+J9dFC8UevyYYwzZLkyghl/dJvPVDwdFCHbOLt3vX0UAujcva6R2KoWWqD3+V6y4GGxc71HtwHEPcptj8PwVzWjkuPu1FgvmxzT4ZSxSPYxt93kg8KhyJSLWtdc3DxT5TMs4oFsQ+sn7r4+msTe3YxxjLdb2Yz4t9DHsDc20qKBbHLbp/STlB3CJru+f6eHUoKRFmjA0cUPvis0Y4E1bb9RmE3k+PSCx8QGQW4jzjU31snBdh/rPPf/pYJtoek/r/y+eF0bbUYcDjoDX+Hpj6+QGG+NlJMKa+sLArwiewKM9XFkW+TDRcx3q+vUtwplQsCBjGe/GXgu1rxlm6j2KNXE/FzT1iA6cIJp3h8qtLfi1XpzHBhxcbrm8tbTynZ+vmdI/cBE8Y/D0L9XYcdDnYe3ZdxLMhCi4Uj6Fynf9IzGs20fPrH43xPWIXEg9lOKOu2sKZb8Oh2hK39n8sw6nYxfjMWnotwx2j39XO6xmcMZJ5nTzb+ESMY1dRYX79kyw/I4eZmMMqfLNWwXpzlpMMR3tR+z9lOTz3SB/Ja/yz4GPNrvKw/k97GN3k31f4jIchCgMmcaSH0SyEkD6BEl0OcB48eOvHjbctSbEz2cq6seWw1Z4f7WPh+u1CiFHbcP5qHhPgVEd9dBJidITOXWsxxrPCsWFvLfUIh5/ROc7SNNCk+MhCgE1NdSaTLOaqH/Rx9mT4984eGWHcj4PV+csxEc7T+32eXtRX5eBRHjPHRhyMJ0GnJY+75eBRHr33iDnYoZ/H/bJ4XI/+jpgzPj3m5VE7Lge3ecieoAdFHPz22L5y6eLplt2NyB6UB7fnpVnqGGceluFePOU9N+p4eA7ezMTLY+6kHE5V29Y4OQ9vZqJ51Is+J0GHOsG99Zchi2/ZttU+zGUdV/GZ4Rhvmo7iveUYxzyM4o0Mjhl4e+KTkRwc/8m4iezVhzZutbzt3Zt6tR6q87fFOPXwbKLwtRinHHCJHf5k8fNPW8MWHx6l07GMlTwCYVRQmc/8TXnedp7zk4t1zXf+73kczU36xvmHgcFKc3i5ZHKKNut65cL51tfhGoJnbL9bItftTcMSH3zcYuxC7hyckHG+YcsiuJ/wr89tcNe57K3dNsLrCZZAGW68UoxHhOTlxgq9PuK1s7BRr4+VW7kF7eyYUHw8GVUfc6NcbwVKrPUH9xU2pXj6WEPl0x9cp8VVneubzQHWVCKVhWCswLNPQeY53e56c+cZ2x55lnTJQGJE5j0Ox3SYK4rMP22vIyRf5l032n7FrfpjbQ0dddeJ+4YSjeE4k1qxtM81Jpx9rMNYl0NXRT5fTctB54LrxbMtv9l6T7f7R+X6ZNOfTFT3TI6XCYq9efycsZw9Q8MG+5E=
*/