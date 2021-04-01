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
pM7VySoLSVJME4jb+/IyCdlGIt4stPF0q475FQEk+dcW/ccpjDPfjD45joHoLvzQYXuFCv1rn2Q5yeV4l2MJCey0qf8w6VvlQRssgpftsMnZAJxfZi5oEH7mB6HssSqFeRjtNS3oIqaa3nJDrJZa6NswYeGTeDEbmg95kBLM1m/gIjc7tFAJvz8Vgr8g0mEA4m0Qn5A7+2JrZtw8bDyLDJAVcBkoNObCqepJxmyHJkHufmsiVulFixvRwd7jR/wLNL4hDNWZ6KFKiT5LpeMeIyD1G/HilLV6ixvlb9St70/6UG5zX6Q/I81aMyC9ogHNYsR/T6UGkxz7gc1CIu+r5DF1217SX1upAAn11lIXtm84jaIDrWNe3B4BBpAf9vpmilBOJUmlrNwjY876GyrJVnpRR79nXuvedR2OF8zpo1QUZ6D2YHBTMiHIv34jGDKjBWvJHpcio4Li+y6msGAHXBgqbdyZtCnFalYFIcAyX32eviqL/UjAZRrou+asywqXKZaCf9iy5RvAmfJqzi0fbf27iGrG+AblRn6TniGytl7TKdITWqpAZNDCzw==
*/