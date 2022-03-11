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