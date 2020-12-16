//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_INSERTION_SORT_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_INSERTION_SORT_HPP

#include <boost/compute/kernel.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/memory/local_buffer.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class Compare>
inline void serial_insertion_sort(Iterator first,
                                  Iterator last,
                                  Compare compare,
                                  command_queue &queue)
{
    typedef typename std::iterator_traits<Iterator>::value_type T;

    size_t count = iterator_range_size(first, last);
    if(count < 2){
        return;
    }

    meta_kernel k("serial_insertion_sort");
    size_t local_data_arg = k.add_arg<T *>(memory_object::local_memory, "data");
    size_t count_arg = k.add_arg<uint_>("n");

    k <<
        // copy data to local memory
        "for(uint i = 0; i < n; i++){\n" <<
        "    data[i] = " << first[k.var<uint_>("i")] << ";\n"
        "}\n"

        // sort data in local memory
        "for(uint i = 1; i < n; i++){\n" <<
        "    " << k.decl<const T>("value") << " = data[i];\n" <<
        "    uint pos = i;\n" <<
        "    while(pos > 0 && " <<
                   compare(k.var<const T>("value"),
                           k.var<const T>("data[pos-1]")) << "){\n" <<
        "        data[pos] = data[pos-1];\n" <<
        "        pos--;\n" <<
        "    }\n" <<
        "    data[pos] = value;\n" <<
        "}\n" <<

        // copy sorted data to output
        "for(uint i = 0; i < n; i++){\n" <<
        "    " << first[k.var<uint_>("i")] << " = data[i];\n"
        "}\n";

    const context &context = queue.get_context();
    ::boost::compute::kernel kernel = k.compile(context);
    kernel.set_arg(local_data_arg, local_buffer<T>(count));
    kernel.set_arg(count_arg, static_cast<uint_>(count));

    queue.enqueue_task(kernel);
}

template<class Iterator>
inline void serial_insertion_sort(Iterator first,
                                  Iterator last,
                                  command_queue &queue)
{
    typedef typename std::iterator_traits<Iterator>::value_type T;

    ::boost::compute::less<T> less;

    return serial_insertion_sort(first, last, less, queue);
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void serial_insertion_sort_by_key(KeyIterator keys_first,
                                         KeyIterator keys_last,
                                         ValueIterator values_first,
                                         Compare compare,
                                         command_queue &queue)
{
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;
    typedef typename std::iterator_traits<ValueIterator>::value_type value_type;

    size_t count = iterator_range_size(keys_first, keys_last);
    if(count < 2){
        return;
    }

    meta_kernel k("serial_insertion_sort_by_key");
    size_t local_keys_arg = k.add_arg<key_type *>(memory_object::local_memory, "keys");
    size_t local_data_arg = k.add_arg<value_type *>(memory_object::local_memory, "data");
    size_t count_arg = k.add_arg<uint_>("n");

    k <<
        // copy data to local memory
        "for(uint i = 0; i < n; i++){\n" <<
        "    keys[i] = " << keys_first[k.var<uint_>("i")] << ";\n"
        "    data[i] = " << values_first[k.var<uint_>("i")] << ";\n"
        "}\n"

        // sort data in local memory
        "for(uint i = 1; i < n; i++){\n" <<
        "    " << k.decl<const key_type>("key") << " = keys[i];\n" <<
        "    " << k.decl<const value_type>("value") << " = data[i];\n" <<
        "    uint pos = i;\n" <<
        "    while(pos > 0 && " <<
                   compare(k.var<const key_type>("key"),
                           k.var<const key_type>("keys[pos-1]")) << "){\n" <<
        "        keys[pos] = keys[pos-1];\n" <<
        "        data[pos] = data[pos-1];\n" <<
        "        pos--;\n" <<
        "    }\n" <<
        "    keys[pos] = key;\n" <<
        "    data[pos] = value;\n" <<
        "}\n" <<

        // copy sorted data to output
        "for(uint i = 0; i < n; i++){\n" <<
        "    " << keys_first[k.var<uint_>("i")] << " = keys[i];\n"
        "    " << values_first[k.var<uint_>("i")] << " = data[i];\n"
        "}\n";

    const context &context = queue.get_context();
    ::boost::compute::kernel kernel = k.compile(context);
    kernel.set_arg(local_keys_arg, static_cast<uint_>(count * sizeof(key_type)), 0);
    kernel.set_arg(local_data_arg, static_cast<uint_>(count * sizeof(value_type)), 0);
    kernel.set_arg(count_arg, static_cast<uint_>(count));

    queue.enqueue_task(kernel);
}

template<class KeyIterator, class ValueIterator>
inline void serial_insertion_sort_by_key(KeyIterator keys_first,
                                         KeyIterator keys_last,
                                         ValueIterator values_first,
                                         command_queue &queue)
{
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;

    serial_insertion_sort_by_key(
        keys_first,
        keys_last,
        values_first,
        boost::compute::less<key_type>(),
        queue
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_INSERTION_SORT_HPP

/* insertion_sort.hpp
D28PYg/4rtbD8M1leDH3H3suvaqRJ16V7FPI4yz9TU+S0x54uTvOD97GfS/hR9/AO7XRy5g35r8IHraeUZfBWYv491uSMZ7rNOuNum3IfxO/fK0+rwNzyQlvhzca06YOcn5yPMYu/UnPygfEhcqCOD/qLKkcix7x+0+Lc9kHPL0h5fdnlcAHr+L57H+7/Kv0neR43K+c31vDzvIHqePiT9ay41/m98sJ/Z4pfhfDE+rijYfL9z9Rz/4AruJ3O/rwW3PxPy/G8cAb/OBN5O141VI8Dr85tFzd5Hj1qxPg0mXi/IXwV9SX4/vP4JuEH9s//OeR+Jsr1Z+SutaA2Hd46rcvx/F435D/343nf4B9Be8Qx7eqmwb/EPO3wdEr8vFy+mvxHYXBA8ZYT97PwGtnkUfEoxgDR4a8zuHvC8l/vDjCf2ap34/wPA2Xk1fwGCHXBvtND4YO5leH40H+hncosD+B12P+ma6jzzsvUMe9lnzqyb3dfPuq076FT+RHVk+BN3bk0Gv7NB5eupG9nIjH/1j/76Py7fn98TdwbDX+KEGTA0N+q+CnvfpM71GnvBW/G3xUnF/Mv/2JX9xf39LBePkJ/Hs/61lv/Qk/PCCuC3nGfFPwWvPz+UP8hLyjZAS+qdl+8ZetR5EL/rzlBn0Q4edi/l+R99H47G+qEz9k3pf1ld7JXpeKd6+n8+S6ruA59Wd8dO82PMCFeCV51ojEfvvH/eXzhZvwVLXqMuTSiC8ra06OhzyuVncarm837Dnk/zn5+kr4ZajzG933A7zZHfuoZ+Dr+NPOjezIe2Qtb/ArAwenfZPem+4+gv5+CgfCP8Xw9NDfZKfzz1EPnskfbEjGmDdX/OY32x9TDy/i94fgBclrW9Sd4rxyOPHrwY8k8/OPQ37M3q2nY2bKR68jv85WdYdved/4Qp+vwn9VeA771nObOPkFcapVPeNL1nc5/QrcE+cN81zHxP/7SZ73WLgteR+of8jvgWSeuM75zfd6L+h2fni0/TiMnc01D/6/u428fyb+J/ng3fF8g/SpPw1/fFO+eAw70rdUd53nDHwf44H8Mv6jPfl/TQfH/L/nj5vZ46Lkuhinep5u+Psx+/tr/mCQOP1f/P0I9Z2r9WVdgYevkLcGjxznn8q/3sCP54oT4/j508XHEfzKJvYQvFhch/fqXcAPz4GXAj/HaL/2/IFfuFi++it4vF2+UQYvzsWjDJCX/A4O8lxdz/OfkYfE8THwVS9+0HMMD345ztvFjxxHn+xPYSYuXaVumfk9qgPU+zfL//CazT148OvjeOSD+OSQf8y/RL78UHZin8F38a93wikt1rWSHE/F298Av9qv3NI0Pk5XB2sK/YvnWpSsM46rAy3qiTHyvDgePKt8YyY+Sl5f+Bvvl2/inx63rxfgu+TntR32pz9/QY4Lr6bHI9nDUHz73fIj+tgMxzZdqX/hCf7vKHaKh2/fi7c+AR7akKeupp4n7oyid0PH49Nvt375VdcBcMxL/Dm+bSe8VT1JfvYu3m8F+T3n+H3w+Jg4Hjg1kXvI/5vw4iJ5+jXs4XV812J88xTyXY4v1kdd9SO4ZbS4CkctiDpDjNey64vk3x2D0udUvyh8Ed92QRwPHCxuHSRfwrsP8fuUQ/X9TP+FuHGb/aS/K0biK9Znp/O8Iw/Xt9M9i1+cq469UR7RxC/xo62Z3wvf63u8Y9t0OL4FvxV94zHvbrj9eXpxbDLG9Q2OX88+/J/bnb/ER8N53c/h6x9X3x/GX2Rwk7roNjx4wxv2n54WVYiDeMLGpH/hizHfWvn/QPnqK/zNM57rK/DfMPK/Qf3pMriOfJvXqheYb8+JeINrxSl18VY=
*/