//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_END_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_END_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/detail/search_all.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Helper function for find_end
///
/// Basically a copy of find_if which returns last occurrence
/// instead of first occurrence
///
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_end_helper(InputIterator first,
                                     InputIterator last,
                                     UnaryPredicate predicate,
                                     command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return last;
    }

    const context &context = queue.get_context();

    detail::meta_kernel k("find_end");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << "if(" << predicate(k.var<const value_type>("value")) << "){\n"
      << "    " << atomic_max_int(k.var<int_ *>("index"), k.var<int_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<int_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    index.write(static_cast<int_>(-1), queue);

    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    int result = static_cast<int>(index.read(queue));

    if(result == -1){
        return last;
    }
    else {
        return first + static_cast<difference_type>(result);
    }
}

} // end detail namespace

///
/// \brief Substring matching algorithm
///
/// Searches for the last match of the pattern [p_first, p_last)
/// in text [t_first, t_last).
/// \return Iterator pointing to beginning of last occurence
///
/// \param t_first Iterator pointing to start of text
/// \param t_last Iterator pointing to end of text
/// \param p_first Iterator pointing to start of pattern
/// \param p_last Iterator pointing to end of pattern
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(n)
///
template<class TextIterator, class PatternIterator>
inline TextIterator find_end(TextIterator t_first,
                             TextIterator t_last,
                             PatternIterator p_first,
                             PatternIterator p_last,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<TextIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<PatternIterator>::value);

    const context &context = queue.get_context();

    // there is no need to check if pattern starts at last n - 1 indices
    vector<uint_> matching_indices(
        detail::iterator_range_size(t_first, t_last)
            + 1 - detail::iterator_range_size(p_first, p_last),
        context
    );

    detail::search_kernel<PatternIterator,
                          TextIterator,
                          vector<uint_>::iterator> kernel;

    kernel.set_range(p_first, p_last, t_first, t_last, matching_indices.begin());
    kernel.exec(queue);

    using boost::compute::_1;

    vector<uint_>::iterator index =
        detail::find_end_helper(
            matching_indices.begin(),
            matching_indices.end(),
            _1 == 1,
            queue
        );

    // pattern was not found
    if(index == matching_indices.end())
        return t_last;

    return t_first + detail::iterator_range_size(matching_indices.begin(), index);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_END_HPP

/* find_end.hpp
eNtP3w/0i63/n5Q17eda/3+c3Jq1Q249x0zXDs3EiPD/cVtWxaWzpo8rYOEQ3/MnBvkOrd+jYiXOxfb6f7HHSvjl8Z7wkoD4DzT+jdXOFzmx15PwM0TIN4HQlk8WJGtVdsMTxP0zuQ9rzBrJpshaGkabb1QfxdjrI2PNWiU7j0PlGm38ZEFIlP1kL4PEv4XosFmCe3ex1xZ5iG+N2Qk9ezj/HLKRwoBv6bhJmtQFblIXZi0a5cWN8gbIEpeF6fdWvT/DMTU8a4OC3Z9ZHUPJCDR8M/G/QO6FXEvr3viHrLeD56i339r1JrL5vWLv7ndfzinrt9eDBam3FEi+TR051zOSl4B6G6uL8pJ0/W0bTB3qLfoJu95IvUPuODkXOmS9Ed6Uu4l3zY9E0XpT/xZm/eHH2ja6lmLNZrAycg3c5BoOOVFEhRByoifKICci7FnlRE/8NDmROUNb15If0jb7EqaJR07kzeu4/HykcOlZs/M1rwm15Lv29El2XjVsLSteZR93in0P8qIIawLGlhOQTrpDT4zGjTPrhFeI/Qk5wzYX44wrokUJO9l3XXLek1YzE1PXEdYpz1SZkYnTlWvm4OpMP39cZoCMm/BGxp3h1AeIyrA82qMdPikg/GTsZV0/42tv1DP3y1vP8dretP+YOox39itTPw1xH+1wLynbzTD+Wu4Sujy1fNpe2vnO7tfH8KAw+qiyHnkt2mvLRCaM92/XPCtzTVvRcM2s1rqub5fYK4Xdxr8fYL7GeNbQLcS8gylyu0LtB9C0GhuZyMNiTyZt7Pz6QuwvudP4enMv5lFMnCvM6o1ZgxnGoSCxZq3z+OwCb/cgvnccfUjiR4XdzNqoo5jPMINdUdZ1mDcxv3ZHqSzKl5dGjvU55j6pXsROT8qaFXccXyjHutYT1qdnaJaeGs21df3I45KeK2wZtf8O5lPMIJfbuhZzGHOT26FvzcjPnpV4nfzG/pmyUNfonBT/XXwLSuTb8WCzDuNOyRtpSp6ca22ekzhdnGUzfRF9eUHKZl9/ljl7fBppPSZpdbRai92+RyOYnd2DeQRTwxVu9cKsxqS6wwk7Jqay57u2PpfewUAxn8Z4zV/P/czS9WlRgGfe01wXxrJe7YOn5HezQUM6dLHU7VXbrZPPbYft1sHndrftluRzKzJu7bv63LrYbp19bq88adw0PfqlGaul3+CmfTJA526+Wf+u7dZ217Da/kr0d3Pv5LzvhloPW+MssY8MsM8OsK82dudzZLaui87HszlMhS0ZF4r32eNC7sycgmyHPlRpm6btEtbMSXNc3G+xt3fF2s9I1mBl503zm+t8LGF66DPel0Y3Xd/IFZ4RnbE8SS8KOp9KNXEuMOuTP9LrBtMjm23CtxZ7Lva3xd7bf20ykxznc4Q45rlQ6Hvui+4xndNov/9awjVwBZvbjcL/XW8d4e+Vh0eQNy5l1km/LuXtLvo9Kar8/V7ijFE3l7i1l3BHjc6zYLoSEyXMYN1f4KxLeyzg+jRLf724SyRcZdpHBZPWb8SNe6BpHRT7hVIPdT0ZlXtrmb0ox/dJeL96oKn47d8ZIfGj1e5Lry55GByTxjMqnA9ZnxMvKuJiM9/7Isa7Tr6uhulEmFOeMGEzoipUiArryb/6vGadO0bD+9IcTfgvPeGrL+ziS3NUQJi5hPnKEyaycIsvzOiAMBsI87UnTJXChb4wgzVMC+wR2L/B/hHmW8xpTDPMcyrT/1tMaca5CjHSFog6nqd7rGMMkH6nz3szN9S+pWtrg8zhZ1tOPYj63qTrVLTN65oU2qaEC5xvzpV/GT90TcVqTFPPfPNZx5qKDp6Ry+732HB0rA2V8I3MHrT1Yv8=
*/