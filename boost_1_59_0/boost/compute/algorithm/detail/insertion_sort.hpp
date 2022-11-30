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
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
*/