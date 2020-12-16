//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_N_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_N_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Search kernel class
///
/// Subclass of meta_kernel which is capable of performing search_n
///
template<class TextIterator, class OutputIterator>
class search_n_kernel : public meta_kernel
{
public:
    typedef typename std::iterator_traits<TextIterator>::value_type value_type;

    search_n_kernel() : meta_kernel("search_n")
    {}

    void set_range(TextIterator t_first,
                   TextIterator t_last,
                   value_type value,
                   size_t n,
                   OutputIterator result)
    {
        m_n = n;
        m_n_arg = add_arg<uint_>("n");

        m_value = value;
        m_value_arg = add_arg<value_type>("value");

        m_count = iterator_range_size(t_first, t_last);
        m_count = m_count + 1 - m_n;

        *this <<
            "uint i = get_global_id(0);\n" <<
            "uint i1 = i;\n" <<
            "uint j;\n" <<
            "for(j = 0; j<n; j++,i++)\n" <<
            "{\n" <<
            "   if(value != " << t_first[expr<uint_>("i")] << ")\n" <<
            "       j = n + 1;\n" <<
            "}\n" <<
            "if(j == n)\n" <<
            result[expr<uint_>("i1")] << " = 1;\n" <<
            "else\n" <<
            result[expr<uint_>("i1")] << " = 0;\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        set_arg(m_n_arg, uint_(m_n));
        set_arg(m_value_arg, m_value);

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_n;
    size_t m_n_arg;
    size_t m_count;
    value_type m_value;
    size_t m_value_arg;
};

} //end detail namespace

///
/// \brief Substring matching algorithm
///
/// Searches for the first occurrence of n consecutive occurrences of
/// value in text [t_first, t_last).
/// \return Iterator pointing to beginning of first occurrence
///
/// \param t_first Iterator pointing to start of text
/// \param t_last Iterator pointing to end of text
/// \param n Number of times value repeats
/// \param value Value which repeats
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(distance(\p t_first, \p t_last))
template<class TextIterator, class ValueType>
inline TextIterator search_n(TextIterator t_first,
                             TextIterator t_last,
                             size_t n,
                             ValueType value,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<TextIterator>::value);

    // there is no need to check if pattern starts at last n - 1 indices
    vector<uint_> matching_indices(
        detail::iterator_range_size(t_first, t_last) + 1 - n,
        queue.get_context()
    );

    // search_n_kernel puts value 1 at every index in vector where pattern
    // of n values starts at
    detail::search_n_kernel<TextIterator,
                            vector<uint_>::iterator> kernel;

    kernel.set_range(t_first, t_last, value, n, matching_indices.begin());
    kernel.exec(queue);

    vector<uint_>::iterator index = ::boost::compute::find(
        matching_indices.begin(), matching_indices.end(), uint_(1), queue
    );

    // pattern was not found
    if(index == matching_indices.end())
        return t_last;

    return t_first + detail::iterator_range_size(matching_indices.begin(), index);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_N_HPP

/* search_n.hpp
3xjIcuZXZn5NyLHkWQdyY8j1Pde1RWx3jRzXtVE8b1bjdbMa8glPjMD8dfAueiRvvPPzyP+CVLsuYosR/9sK6SBdg6RjoZesm46H/g5SxUPvj+QgzZ+AGAEkbyzByHGDx0Zvy+/nn6PjCkqgRzXfia8S2siOk16AlO+7+pYF3SGbUM8bYzAaKTs2+mV+a78NZVVc9LKSwWOjwyir46PnjlsxRnoBfjsR8nrVJtK261VaYaSFSPcjfY5UMR52QQojLUB6Amk5Uu36lVY70jykm5HeQhq9QaXVhnQs0jVI9yMt2cDEVxsYGBgYGBgYGBgU6v3/vSiER4u9h0n0/9+L/Vf+73vUW66PxsgiS1BC/YvpV7b/Ze7zQZJ3wJ2uI5TpsTH4ey69/jQn5uGamZcr24vuz/F9nYfv0MH5wvZf4LumeEW+lSdZVjgPX/aTV/0cTPy2rA5VqCcUdZ+3sp0SeVZfMQTd9HOkOqQ9i9z2Mvy9Dy3JrXP3EHV2PZ0G0b07AN2X5NB9+9UtK5pbdzwk7nQfE4ufGk6KqO3Y1hD00c+3apBWvVGdN+MuOmKH6GsjJv6QGvXCWQvPqnefW/DcoV7Z+yTcb18NUuk7GlLXmzlAvfVYbzzrre+pd+gA9TZivY1Zr9ZTLzxAvTVYr4b11vTU685Xz/s8gfXW8dSLDlBvM9abwHoTIceq/EbYo0Cai3Q30udIYzfGfszGZk/CwMDAwMDAwMDgn0cQ7/9j/D8WpakjnHjib78HIKi4+lPlG3/0O+bau8LzLf7la1mWc4EnTjpsH9Y7axY877vjce0vPXLF+K1Rlq5XMZT14xTv+hHteeKZMn1Udx1mCVr4Hb0GyJ/UAkm45mH9qIPa+c066Fct+qmIElc3ll9D8uKLIvkdoKP+xldfKNXf2YTSJuZYrt/02RfKN1iYL7IWSb4CfaBP6QoxtbtULYHuVwnPBkVjUG474dH+mB1oPzlHyjLW5UMpuzPziMQVjvL++Az0CXXi0Y5EJzKuf/OLUu9+6UtTowW4cVw6vj2FH+W4NDG+bcOsckm8OSEZTpdp4z7B9pM83wYiXxXktey75F1bVEm7Ixq1nvZsh61q7q+FW9vLTqkAgkiqG+buSoZ6bLHZ0mEW+32F9LukzAK6Q7FwFOXCISdkSbllnnKjlG+2inUpga/Xlsp3eJOMeNt59JldPGygOJ6qqufx92oZizJ2oGuVHEPou0Ks8njG4sHe+FtOe7uxdxuyTLat8XexyQj5e5bNWH+py7+ivaCf2AE2wt+zbbRd1aMyLiwr3JjOv8v8LObHXZjOH868wzz2ZyR/AfMH8e9XMr9rY2b8xXLadUekcvrv7ICxU3ORd48HgRsdqW68kaAP7wWAQFwUY9InyDhjXIZEHlo6NkmO24KB49ykHNqADTLaEJ0bLuK3AiZlxu3NLMu9LxW+KE/cG7ROOkPbg9IcTeX9350qVceQe5vdmRypjp5QDGMLO6iJhI4NbBSbhOMpb0wVfcL7pP4wN+bpWMk3YUyuKeftJKmbsFnVvb6cK+U2Yl7XKx7Un1zZMUY7jhyfGcP2CPu4KiuUM/7y5Yw+pmy1I5keoeEVoo+HsrendHjzIj0eM/d0l1RYgm2RSimbYINlHh0G4x/lxvy6ZzDtrdupYR4RIQv6v3+6y6Sc11HX5l9J3TWY13WLXX/+s4fgz69iosYt0DGG29C/X8fsan3/Hf79LbLv+swlt+5xY1Vrxe+Pf7PXIYsvbzX+/UH49/OEkXvebPGr5P62notBVmT7AdKPU/thlkMey/3f2915ksy3pN5qSFBNcAL9L0+mv+Qp/KbKGfTnnk//2Bv4baSbIPeGvBU=
*/