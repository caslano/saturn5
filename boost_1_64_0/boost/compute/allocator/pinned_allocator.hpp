//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALLOCATOR_PINNED_ALLOCATOR_HPP
#define BOOST_COMPUTE_ALLOCATOR_PINNED_ALLOCATOR_HPP

#include <boost/compute/allocator/buffer_allocator.hpp>

namespace boost {
namespace compute {

template<class T>
class pinned_allocator : public buffer_allocator<T>
{
public:
    explicit pinned_allocator(const context &context)
        : buffer_allocator<T>(context)
    {
        buffer_allocator<T>::set_mem_flags(
            buffer::read_write | buffer::alloc_host_ptr
        );
    }

    pinned_allocator(const pinned_allocator<T> &other)
        : buffer_allocator<T>(other)
    {
    }

    pinned_allocator<T>& operator=(const pinned_allocator<T> &other)
    {
        if(this != &other){
            buffer_allocator<T>::operator=(other);
        }

        return *this;
    }

    ~pinned_allocator()
    {
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALLOCATOR_PINNED_ALLOCATOR_HPP

/* pinned_allocator.hpp
8m90xtf59xv6xFLw80Hw3RrzvlCefM5634XsSB/iFPpfW5m6ZTM/6ZsQjM934t1+ePP34DrV8+D6+XjaON/7Rb58MHjf7EHs9TO6hXFZv8S8p9MFxe1B5n3tTH0b5jftXfHtdvbzQoT9KMTrNvXoj/GUfPrht/jqDeouN8sX6uclcEXMDrzhFtf38zh2Vcdus8pD/RMPmS4Ofws3043rjjHvJ5jnu+RVOl7tUfLVLjxjA/we9kU+hmfgw80X6qf/Q7/QIvpGO3Fwpbz2FV5mH4Pp/2VX8nNbd7piP/W4/vDHU577O9f9Dh9fq17eh+6ZkRBcx/1SMtj5cHWdM+CjU/Cqz62v6m0918v0MDhjxWj768D/ufqzZl0pjp2or3w1ux0s3+XKW93wnQvp/XX2nxC/tlbJ3/LA6DfUAdhvsvy+djv9dqf48zcc8Zz+vJvY73lwkjiV+6x1SLX0zEK8MEn+s75qxRTXGUqvD/vZ1OvrR7veO/LW/Bh6kv6eJXTUGPHJ+5br38t/yn5U36uzT5S/V+DXj/v7PvzC+DXIL60XylsLjO/JdOrz4P2d+q7oZ9X3+t5Ez1PuvdLtV0HvqfmErnmp+sMPcK99vVLuwhe2000X06M9R0q4bvgo+fKAOu0KeHyLdYuz9IE8j+cmyLeH8+NkdZQJccH3NuJz9O7pR9Ot+uEJ/4a3vo0Orn883HxJ8PspT9tvQV9DIxy5HX7NE9fr7Qe38jB453B2v9J+fnfrrxInpqTi1T+w93J602h+eJR9F8L+rw7mrSaC7gB/0aviVsO9pxlP9fGa8cZzi59fJj4163+9gE45K/j+yCXhuld9CheJ91vF65H6EUoj4QPr5P4rD6SLS7Xy2FX0yXPoqf3w2Xf0A/+ET8SLs1X8/Wt1BPgwNcM4HpD3zwrrwfTel+mL9gsofkcfc6nx/Fl90/zl65vN3UTPSoQDn4MzztF3bJ+o2qX61hrF+zn2Vwj3C7hFv88p4frPSPqXcY+ACxLh6Sx47NKwjqx/rknfTbFxGMGfD+AVfSLxGXjzNv79PN3g47Dv1/MuFN+vgLcz5bGhUeI9vWcRvnmu+O+5N2fLUwPwkVK6UKxxqbRelx9Vz2Cfm+CaS/j9cnYV9tEn0NkHsu8M+OIXfk9XbrWvV+ZQ61fHe98Z6ifHer+2kJ/BE+wrL05f+pK44Pn+K45b55Pj/4V/i3O30vVb8J1+8gHdIG4+f5vhucfSJfl1Uxd1qOH4/XL8UN9pbl991IfYB+NM11NHK/8QrmzAZ7Lhg87ixizX7YA/Hivfhet0rjXuE+DaQ+CkN11npPg32P3hrNqv9OV96j1vVRdrdN98dTXxceVU9R74oVUdL1nfTyUcNHOxvAFn9mdHi27WDzVAveKxCP6qP2aFPH+2etZh+lAe8Bw3hfUw199Bhxkch5/Fquur3yXCRUeqF0azo8n4xx3mv0s7/Z5wMb636lzvuwO+xrMazvGcnr/pdffpl8D/8MBeeNwX9Fo6ceNM9jean0fSSz7m71fSx5bpE3kO/iqHHxrgHNdJ3yI/x8mXdP6WDnhrhPXJ5bHyrefpA5/xn4L3xNEl/PQez4ePtNwhLlR6zo7soNjzHSL+Hem+XSPwU+97p5//FGXfNrxsjOs8Sc94iT621HqhKDx4mTjRKUp/k340uKBgt7z9VgSeCEd53pR50frj+cUa9hdrHZP5S43RJ/Cm/PObcZff2j4ST34wnjvhhgp4XT11c7J+kD/h7hn+Ltd4vub6S8QP8X9zq3h6HNz5AVyXQResV4eJYscH6d/upg5Ghylkrxl49vZ/meefjCf+VfWS+sznwXOUV8Ezf+DxC+SfKPU=
*/