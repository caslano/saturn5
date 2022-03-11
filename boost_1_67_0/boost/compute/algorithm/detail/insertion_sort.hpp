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