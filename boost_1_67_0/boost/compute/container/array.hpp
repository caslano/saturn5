//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_ARRAY_HPP
#define BOOST_COMPUTE_CONTAINER_ARRAY_HPP

#include <cstddef>
#include <iterator>
#include <exception>

#include <boost/array.hpp>
#include <boost/throw_exception.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/algorithm/swap_ranges.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/detail/capture_traits.hpp>
#include <boost/compute/detail/buffer_value.hpp>

namespace boost {
namespace compute {

/// \class array
/// \brief A fixed-size container.
///
/// The array container is very similar to the \ref vector container except
/// its size is fixed at compile-time rather than being dynamically resizable
/// at run-time.
///
/// For example, to create a fixed-size array with eight values on the device:
/// \code
/// boost::compute::array<int, 8> values(context);
/// \endcode
///
/// The Boost.Compute \c array class provides a STL-like API and is modeled
/// after the \c std::array class from the C++ standard library.
///
/// \see \ref vector "vector<T>"
template<class T, std::size_t N>
class array
{
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef detail::buffer_value<T> reference;
    typedef const detail::buffer_value<T> const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef buffer_iterator<T> iterator;
    typedef buffer_iterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    enum {
        static_size = N
    };

    explicit array(const context &context = system::default_context())
        : m_buffer(context, sizeof(T) * N)
    {
    }

    array(const array<T, N> &other)
        : m_buffer(other.m_buffer.get_context(), sizeof(T) * N)
    {
        command_queue queue = default_queue();
        boost::compute::copy(other.begin(), other.end(), begin(), queue);
        queue.finish();
    }

    array(const boost::array<T, N> &array,
          const context &context = system::default_context())
        : m_buffer(context, sizeof(T) * N)
    {
        command_queue queue = default_queue();
        boost::compute::copy(array.begin(), array.end(), begin(), queue);
        queue.finish();
    }

    array(const array<T, N> &other,
          const command_queue &queue)
        : m_buffer(other.m_buffer.get_context(), sizeof(T) * N)
    {
        boost::compute::copy(other.begin(), other.end(), begin(), queue);
    }

    array<T, N>& operator=(const array<T, N> &other)
    {
        if(this != &other){
            command_queue queue = default_queue();
            boost::compute::copy(other.begin(), other.end(), begin(), queue);
            queue.finish();
        }

        return *this;
    }

    array<T, N>& operator=(const boost::array<T, N> &array)
    {
        command_queue queue = default_queue();
        boost::compute::copy(array.begin(), array.end(), begin(), queue);
        queue.finish();

        return *this;
    }

    ~array()
    {
    }

    iterator begin()
    {
        return buffer_iterator<T>(m_buffer, 0);
    }

    const_iterator begin() const
    {
        return buffer_iterator<T>(m_buffer, 0);
    }

    const_iterator cbegin() const
    {
        return begin();
    }

    iterator end()
    {
        return buffer_iterator<T>(m_buffer, N);
    }

    const_iterator end() const
    {
        return buffer_iterator<T>(m_buffer, N);
    }

    const_iterator cend() const
    {
        return end();
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(end() - 1);
    }

    const_reverse_iterator rbegin() const
    {
        return reverse_iterator(end() - 1);
    }

    const_reverse_iterator crbegin() const
    {
        return rbegin();
    }

    reverse_iterator rend()
    {
        return reverse_iterator(begin() - 1);
    }

    const_reverse_iterator rend() const
    {
        return reverse_iterator(begin() - 1);
    }

    const_reverse_iterator crend() const
    {
        return rend();
    }

    size_type size() const
    {
        return N;
    }

    bool empty() const
    {
        return N == 0;
    }

    size_type max_size() const
    {
        return N;
    }

    reference operator[](size_type index)
    {
        return *(begin() + static_cast<difference_type>(index));
    }

    const_reference operator[](size_type index) const
    {
        return *(begin() + static_cast<difference_type>(index));
    }

    reference at(size_type index)
    {
        if(index >= N){
            BOOST_THROW_EXCEPTION(std::out_of_range("index out of range"));
        }

        return operator[](index);
    }

    const_reference at(size_type index) const
    {
        if(index >= N){
            BOOST_THROW_EXCEPTION(std::out_of_range("index out of range"));
        }

        return operator[](index);
    }

    reference front()
    {
        return *begin();
    }

    const_reference front() const
    {
        return *begin();
    }

    reference back()
    {
        return *(end() - static_cast<difference_type>(1));
    }

    const_reference back() const
    {
        return *(end() - static_cast<difference_type>(1));
    }

    void fill(const value_type &value, const command_queue &queue)
    {
        ::boost::compute::fill(begin(), end(), value, queue);
    }

    void swap(array<T, N> &other, const command_queue &queue)
    {
        ::boost::compute::swap_ranges(begin(), end(), other.begin(), queue);
    }

    void fill(const value_type &value)
    {
        command_queue queue = default_queue();
        ::boost::compute::fill(begin(), end(), value, queue);
        queue.finish();
    }

    void swap(array<T, N> &other)
    {
        command_queue queue = default_queue();
        ::boost::compute::swap_ranges(begin(), end(), other.begin(), queue);
        queue.finish();
    }

    const buffer& get_buffer() const
    {
        return m_buffer;
    }

private:
    buffer m_buffer;

    command_queue default_queue() const
    {
        const context &context = m_buffer.get_context();
        command_queue queue(context, context.get_device());
        return queue;
    }
};

namespace detail {

// set_kernel_arg specialization for array<T, N>
template<class T, std::size_t N>
struct set_kernel_arg<array<T, N> >
{
    void operator()(kernel &kernel_, size_t index, const array<T, N> &array)
    {
        kernel_.set_arg(index, array.get_buffer());
    }
};

// for capturing array<T, N> with BOOST_COMPUTE_CLOSURE()
template<class T, size_t N>
struct capture_traits<array<T, N> >
{
    static std::string type_name()
    {
        return std::string("__global ") + ::boost::compute::type_name<T>() + "*";
    }
};

// meta_kernel streaming operator for array<T, N>
template<class T, size_t N>
meta_kernel& operator<<(meta_kernel &k, const array<T, N> &array)
{
  return k << k.get_buffer_identifier<T>(array.get_buffer());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_ARRAY_HPP

/* array.hpp
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
*/