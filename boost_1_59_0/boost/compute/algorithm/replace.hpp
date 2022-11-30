//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REPLACE_HPP
#define BOOST_COMPUTE_ALGORITHM_REPLACE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class T>
class replace_kernel : public meta_kernel
{
public:
    replace_kernel()
        : meta_kernel("replace")
    {
        m_count = 0;
    }

    void set_range(Iterator first, Iterator last)
    {
        m_count = detail::iterator_range_size(first, last);

        *this <<
            "const uint i = get_global_id(0);\n" <<
            "if(" << first[var<cl_uint>("i")] << " == " << var<T>("old_value") << ")\n" <<
            "    " << first[var<cl_uint>("i")] << '=' << var<T>("new_value") << ";\n";
    }

    void set_old_value(const T &old_value)
    {
        add_set_arg<T>("old_value", old_value);
    }

    void set_new_value(const T &new_value)
    {
        add_set_arg<T>("new_value", new_value);
    }

    void exec(command_queue &queue)
    {
        if(m_count == 0){
            // nothing to do
            return;
        }

        exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
};

} // end detail namespace

/// Replaces each instance of \p old_value in the range [\p first,
/// \p last) with \p new_value.
///
/// Space complexity: \Omega(1)
template<class Iterator, class T>
inline void replace(Iterator first,
                    Iterator last,
                    const T &old_value,
                    const T &new_value,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    detail::replace_kernel<Iterator, T> kernel;

    kernel.set_range(first, last);
    kernel.set_old_value(old_value);
    kernel.set_new_value(new_value);

    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REPLACE_HPP

/* replace.hpp
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
*/