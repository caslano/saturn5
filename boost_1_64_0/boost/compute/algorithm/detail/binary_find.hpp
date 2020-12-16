//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_BINARY_FIND_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_BINARY_FIND_HPP

#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/parameter_cache.hpp>

namespace boost {
namespace compute {
namespace detail{

///
/// \brief Binary find kernel class
///
/// Subclass of meta_kernel to perform single step in binary find.
///
template<class InputIterator, class UnaryPredicate>
class binary_find_kernel : public meta_kernel
{
public:
    binary_find_kernel(InputIterator first,
                       InputIterator last,
                       UnaryPredicate predicate)
        : meta_kernel("binary_find")
    {
        typedef typename std::iterator_traits<InputIterator>::value_type value_type;

        m_index_arg = add_arg<uint_ *>(memory_object::global_memory, "index");
        m_block_arg = add_arg<uint_>("block");

        atomic_min<uint_> atomic_min_uint;

        *this <<
            "uint i = get_global_id(0) * block;\n" <<
            decl<value_type>("value") << "=" << first[var<uint_>("i")] << ";\n" <<
            "if(" << predicate(var<value_type>("value")) << ") {\n" <<
                atomic_min_uint(var<uint_ *>("index"), var<uint_>("i")) << ";\n" <<
            "}\n";
    }

    size_t m_index_arg;
    size_t m_block_arg;
};

///
/// \brief Binary find algorithm
///
/// Finds the end of true values in the partitioned range [first, last).
/// \return Iterator pointing to end of true values
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param predicate Predicate according to which the range is partitioned
/// \param queue Queue on which to execute
///
template<class InputIterator, class UnaryPredicate>
inline InputIterator binary_find(InputIterator first,
                                 InputIterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    const device &device = queue.get_device();

    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    const std::string cache_key = "__boost_binary_find";

    size_t find_if_limit = 128;
    size_t threads = parameters->get(cache_key, "tpb", 128);
    size_t count = iterator_range_size(first, last);

    InputIterator search_first = first;
    InputIterator search_last = last;

    scalar<uint_> index(queue.get_context());

    // construct and compile binary_find kernel
    binary_find_kernel<InputIterator, UnaryPredicate>
        binary_find_kernel(search_first, search_last, predicate);
    ::boost::compute::kernel kernel = binary_find_kernel.compile(queue.get_context());

    // set buffer for index
    kernel.set_arg(binary_find_kernel.m_index_arg, index.get_buffer());

    while(count > find_if_limit) {
        index.write(static_cast<uint_>(count), queue);

        // set block and run binary_find kernel
        uint_ block = static_cast<uint_>((count - 1)/(threads - 1));
        kernel.set_arg(binary_find_kernel.m_block_arg, block);
        queue.enqueue_1d_range_kernel(kernel, 0, threads, 0);

        size_t i = index.read(queue);

        if(i == count) {
            search_first = search_last - ((count - 1)%(threads - 1));
            break;
        } else {
            search_last = search_first + i;
            search_first = search_last - ((count - 1)/(threads - 1));
        }

        // Make sure that first and last stay within the input range
        search_last = (std::min)(search_last, last);
        search_last = (std::max)(search_last, first);

        search_first = (std::max)(search_first, first);
        search_first = (std::min)(search_first, last);

        count = iterator_range_size(search_first, search_last);
    }

    return find_if(search_first, search_last, predicate, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_BINARY_FIND_HPP

/* binary_find.hpp
1+BvnLfvenj5yHNwI3pzvI5M7DvH6xgorGC0t/k2+lb2ckOxZWWCw0YiN8H3HYtv7Tw2kb7Bt5xT8SMY7178GOvz735idKPP8TnCBgR1pHmMt9PH6HHyapXXsYDxAr3PI3eh5/RlbN4Z1P+QKxfU/7D5A8/9O8LSAr3voTfVc7qa8YL5u45cuzfOYRuxpazXu5VY7vB6PyWWgW+fY9+tPse/om8Tz/O36A3+1v5e5Op6XvYLy/nO83II33p4337H5uHet1g7+bvZ+1ZSWE6Cz5cywjJ2+fHKC8vcGXz/Jyytp9dRTVj2oqD+h96sSg47V1jRKq+jjrD04B22HtgAb3MjxnvX970U+4L1rxk6qnisFfYFWDthBcEZ0NX0LfByGcLyPvH2XQcHA33fnvC32Mv1wb5tfrwBjNfWcz8I+wr8XB2C3Dee+xFw0Dmo/yF3wOfVBLByfrwp2Bz+/V84ONfL3QcH/YP6n7DUS/xcmCssN5gLjwnLCp7xufAyx8fyOeS+8rnxEhzs8Tm0CLmffMzfIDeq+75vI1eyhMPeFRbum96HlwblHbaW8fL83NqAzWd7vVuQu9nLfQJXK70tu+j7sdexW1jKc57nb8CCZ8WP+HGD574Im/cmOuwgXM3zsTxKjIKa/p/YvNvzktBecVvv86W0sNhSL3eKsMKLfcxPE5ZXxXNaVVhWMy93Jn2f9b6dIyynkpc7D7lD3uYLkQvePxoKC2N5ibCipz2nTcGWJDgsHd+CPVxb9GZ6/q5Cb3A220VYxlzft5uw1A5ebw94Cc6KbsKWHI/1R0eQQ7cyXmevY7Cw7DN8HgwnbgEvo0/45m0eLyxzX0WHTRaW/mQFh91N3IKa9ExsHh/U/7Al+Fb8YWzu7Xl+FLlh3o+nhKUFZ9vP4kewlvxdWL5aV/8jRk293OvCCh70ckvBhnt/VxC3tBSHrSJG53pOP8Tf/T6WH2NLUAvfjL+r/Hg78COw5R/oCLBCxgtitIfx6vp4/IBcrrflZ3zr4vv+it6rPHYEP7r7eBwnN4ZXcliJKyW30fdNEpZ1uY9vsrDsLC93qrD8OJ8vVRgvwM4QlhrUPGoIS1/v7astLK95vMMuEDYg/Pf/GC/I08bYnOF1XC4s83Q/P1pic7BOthGWstXb0gG5G7xcZ+Q6e6wrckF8uwsrCDjoLSxnh5frR9/uQf0Pnn/yHNxO3zF+jRhG31LlHXYHeud6uTuJxwpvSza83OJ5mQan4d//BXvAz9VZ8JwQ/P4vOsZ6HfPRUd7b8iQ2H4w57Bn8zfW2vAg2K/j+T1ja7V7vYmEZLTz2FjEKcmM5eXWZ17ESmzsE9T/4O8vn0Ho4KPAcFBCP3z1X29ExwNvyGf529TH/Et/GBvU/9Db2fb/Hj5bevp8YL8H7cQCegz3mYeyr7+07hh/lvY74Dvzbwj7/SgnL2uTHKyesMNHHo4KwjPDf/xOW+4LXe7qw1I5eRyrYh75vLWE5wTw6X1j2lz6HGghLO+zjezH2dfX2NRGWX9vraCEs9qXv21pY5jiv40qwXh7rJKzoH56Xa9Eb7OtuQO7vnoNe+JvqY94XP9b48W5GbqCP0d/QEfyt7ixhBTlebhRyKV5uHPFd7rFJxLe2z6G7wIIcmk48bg/qf+io4P19kL7NPPYIuXGRt+8J4hH87e+n4SqQewG5D70tr8DLTd6W14TlnR3U/8i/4V7HMrgKeMmH++C71zVgpSo77CN0BOvpJmwZ6nNoG1wF78Q7yd3PvNwX6AjqZl/DQfB7gd+hY5m3eR/jBWvdL3D/bqLDfqPvnR77g763eb1xV8nmoHadKCx9vZcrKyx1j+cgBbl3fA5VEpYZfPM=
*/