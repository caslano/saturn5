//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_VECTOR_HPP
#define BOOST_COMPUTE_CONTAINER_VECTOR_HPP

#include <vector>
#include <cstddef>
#include <iterator>
#include <exception>

#include <boost/throw_exception.hpp>

#include <boost/compute/config.hpp>

#ifndef BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

#include <boost/compute/buffer.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/copy_n.hpp>
#include <boost/compute/algorithm/fill_n.hpp>
#include <boost/compute/allocator/buffer_allocator.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/detail/capture_traits.hpp>
#include <boost/compute/detail/buffer_value.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {

/// \class vector
/// \brief A resizable array of values.
///
/// The vector<T> class stores a dynamic array of values. Internally, the data
/// is stored in an OpenCL buffer object.
///
/// The vector class is the prefered container for storing and accessing data
/// on a compute device. In most cases it should be used instead of directly
/// dealing with buffer objects. If the undelying buffer is needed, it can be
/// accessed with the get_buffer() method.
///
/// The internal storage is allocated in a specific OpenCL context which is
/// passed as an argument to the constructor when the vector is created.
///
/// For example, to create a vector on the device containing space for ten
/// \c int values:
/// \code
/// boost::compute::vector<int> vec(10, context);
/// \endcode
///
/// Allocation and data transfer can also be performed in a single step:
/// \code
/// // values on the host
/// int data[] = { 1, 2, 3, 4 };
///
/// // create a vector of size four and copy the values from data
/// boost::compute::vector<int> vec(data, data + 4, queue);
/// \endcode
///
/// The Boost.Compute \c vector class provides a STL-like API and is modeled
/// after the \c std::vector class from the C++ standard library. It can be
/// used with any of the STL-like algorithms provided by Boost.Compute
/// including \c copy(), \c transform(), and \c sort() (among many others).
///
/// For example:
/// \code
/// // a vector on a compute device
/// boost::compute::vector<float> vec = ...
///
/// // copy data to the vector from a host std:vector
/// boost::compute::copy(host_vec.begin(), host_vec.end(), vec.begin(), queue);
///
/// // copy data from the vector to a host std::vector
/// boost::compute::copy(vec.begin(), vec.end(), host_vec.begin(), queue);
///
/// // sort the values in the vector
/// boost::compute::sort(vec.begin(), vec.end(), queue);
///
/// // calculate the sum of the values in the vector (also see reduce())
/// float sum = boost::compute::accumulate(vec.begin(), vec.end(), 0, queue);
///
/// // reverse the values in the vector
/// boost::compute::reverse(vec.begin(), vec.end(), queue);
///
/// // fill the vector with ones
/// boost::compute::fill(vec.begin(), vec.end(), 1, queue);
/// \endcode
///
/// \see \ref array "array<T, N>", buffer
template<class T, class Alloc = buffer_allocator<T> >
class vector
{
public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef detail::buffer_value<T> reference;
    typedef const detail::buffer_value<T> const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef buffer_iterator<T> iterator;
    typedef buffer_iterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    /// Creates an empty vector in \p context.
    explicit vector(const context &context = system::default_context())
        : m_size(0),
          m_allocator(context)
    {
        m_data = m_allocator.allocate(_minimum_capacity());
    }

    /// Creates a vector with space for \p count elements in \p context.
    ///
    /// Note that unlike \c std::vector's constructor, this will not initialize
    /// the values in the container. Either call the vector constructor which
    /// takes a value to initialize with or use the fill() algorithm to set
    /// the initial values.
    ///
    /// For example:
    /// \code
    /// // create a vector on the device with space for ten ints
    /// boost::compute::vector<int> vec(10, context);
    /// \endcode
    explicit vector(size_type count,
                    const context &context = system::default_context())
        : m_size(count),
          m_allocator(context)
    {
        m_data = m_allocator.allocate((std::max)(count, _minimum_capacity()));
    }

    /// Creates a vector with space for \p count elements and sets each equal
    /// to \p value.
    ///
    /// For example:
    /// \code
    /// // creates a vector with four values set to nine (e.g. [9, 9, 9, 9]).
    /// boost::compute::vector<int> vec(4, 9, queue);
    /// \endcode
    vector(size_type count,
           const T &value,
           command_queue &queue = system::default_queue())
        : m_size(count),
          m_allocator(queue.get_context())
    {
        m_data = m_allocator.allocate((std::max)(count, _minimum_capacity()));

        ::boost::compute::fill_n(begin(), count, value, queue);
    }

    /// Creates a vector with space for the values in the range [\p first,
    /// \p last) and copies them into the vector with \p queue.
    ///
    /// For example:
    /// \code
    /// // values on the host
    /// int data[] = { 1, 2, 3, 4 };
    ///
    /// // create a vector of size four and copy the values from data
    /// boost::compute::vector<int> vec(data, data + 4, queue);
    /// \endcode
    template<class InputIterator>
    vector(InputIterator first,
           InputIterator last,
           command_queue &queue = system::default_queue())
        : m_size(detail::iterator_range_size(first, last)),
          m_allocator(queue.get_context())
    {
        m_data = m_allocator.allocate((std::max)(m_size, _minimum_capacity()));

        ::boost::compute::copy(first, last, begin(), queue);
    }

    /// Creates a new vector and copies the values from \p other.
    vector(const vector &other,
           command_queue &queue = system::default_queue())
        : m_size(other.m_size),
          m_allocator(other.m_allocator)
    {
        m_data = m_allocator.allocate((std::max)(m_size, _minimum_capacity()));

        if(!other.empty()){
            if(other.get_buffer().get_context() != queue.get_context()){
                command_queue other_queue = other.default_queue();
                ::boost::compute::copy(other.begin(), other.end(), begin(), other_queue);
                other_queue.finish();
            }
            else {
                ::boost::compute::copy(other.begin(), other.end(), begin(), queue);
                queue.finish();
            }
        }
    }

    /// Creates a new vector and copies the values from \p other.
    template<class OtherAlloc>
    vector(const vector<T, OtherAlloc> &other,
           command_queue &queue = system::default_queue())
        : m_size(other.size()),
          m_allocator(queue.get_context())
    {
        m_data = m_allocator.allocate((std::max)(m_size, _minimum_capacity()));

        if(!other.empty()){
            ::boost::compute::copy(other.begin(), other.end(), begin(), queue);
            queue.finish();
        }
    }

    /// Creates a new vector and copies the values from \p vector.
    template<class OtherAlloc>
    vector(const std::vector<T, OtherAlloc> &vector,
           command_queue &queue = system::default_queue())
        : m_size(vector.size()),
          m_allocator(queue.get_context())
    {
        m_data = m_allocator.allocate((std::max)(m_size, _minimum_capacity()));

        ::boost::compute::copy(vector.begin(), vector.end(), begin(), queue);
    }

    #ifndef BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST
    vector(std::initializer_list<T> list,
           command_queue &queue = system::default_queue())
        : m_size(list.size()),
          m_allocator(queue.get_context())
    {
        m_data = m_allocator.allocate((std::max)(m_size, _minimum_capacity()));

        ::boost::compute::copy(list.begin(), list.end(), begin(), queue);
    }
    #endif // BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST

    vector& operator=(const vector &other)
    {
        if(this != &other){
            command_queue queue = default_queue();
            resize(other.size(), queue);
            ::boost::compute::copy(other.begin(), other.end(), begin(), queue);
            queue.finish();
        }

        return *this;
    }

    template<class OtherAlloc>
    vector& operator=(const vector<T, OtherAlloc> &other)
    {
        command_queue queue = default_queue();
        resize(other.size(), queue);
        ::boost::compute::copy(other.begin(), other.end(), begin(), queue);
        queue.finish();

        return *this;
    }

    template<class OtherAlloc>
    vector& operator=(const std::vector<T, OtherAlloc> &vector)
    {
        command_queue queue = default_queue();
        resize(vector.size(), queue);
        ::boost::compute::copy(vector.begin(), vector.end(), begin(), queue);
        queue.finish();
        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new vector from \p other.
    vector(vector&& other)
        : m_data(std::move(other.m_data)),
          m_size(other.m_size),
          m_allocator(std::move(other.m_allocator))
    {
        other.m_size = 0;
    }

    /// Move-assigns the data from \p other to \c *this.
    vector& operator=(vector&& other)
    {
        if(capacity() > 0){
            m_allocator.deallocate(m_data, capacity());
        }

        m_data = std::move(other.m_data);
        m_size = other.m_size;
        m_allocator = std::move(other.m_allocator);

        other.m_size = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the vector object.
    ~vector()
    {
        if(capacity() > 0){
            m_allocator.deallocate(m_data, capacity());
        }
    }

    iterator begin()
    {
        return ::boost::compute::make_buffer_iterator<T>(m_data.get_buffer(), 0);
    }

    const_iterator begin() const
    {
        return ::boost::compute::make_buffer_iterator<T>(m_data.get_buffer(), 0);
    }

    const_iterator cbegin() const
    {
        return begin();
    }

    iterator end()
    {
        return ::boost::compute::make_buffer_iterator<T>(m_data.get_buffer(), m_size);
    }

    const_iterator end() const
    {
        return ::boost::compute::make_buffer_iterator<T>(m_data.get_buffer(), m_size);
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

    /// Returns the number of elements in the vector.
    size_type size() const
    {
        return m_size;
    }

    size_type max_size() const
    {
        return m_allocator.max_size();
    }

    /// Resizes the vector to \p size.
    void resize(size_type size, command_queue &queue)
    {
        if(size <= capacity()){
            m_size = size;
        }
        else {
            // allocate new buffer
            pointer new_data =
                m_allocator.allocate(
                    static_cast<size_type>(
                        static_cast<float>(size) * _growth_factor()
                    )
                );

            if(capacity() > 0)
            {
                // copy old values to the new buffer
                ::boost::compute::copy(m_data, m_data + m_size, new_data, queue);

                // free old memory
                m_allocator.deallocate(m_data, capacity());
            }

            // set new data and size
            m_data = new_data;
            m_size = size;
        }
    }

    /// \overload
    void resize(size_type size)
    {
        command_queue queue = default_queue();
        resize(size, queue);
        queue.finish();
    }

    /// Returns \c true if the vector is empty.
    bool empty() const
    {
        return m_size == 0;
    }

    /// Returns the capacity of the vector.
    size_type capacity() const
    {
        if(m_data == pointer()) // null pointer check
        {
            return 0;
        }
        return m_data.get_buffer().size() / sizeof(T);
    }

    void reserve(size_type size, command_queue &queue)
    {
        if(size > max_size()){
            throw std::length_error("vector::reserve");
        }
        if(capacity() < size){
            // allocate new buffer
            pointer new_data =
                m_allocator.allocate(
                    static_cast<size_type>(
                        static_cast<float>(size) * _growth_factor()
                    )
                );

            if(capacity() > 0)
            {
                // copy old values to the new buffer
                ::boost::compute::copy(m_data, m_data + m_size, new_data, queue);

                // free old memory
                m_allocator.deallocate(m_data, capacity());
            }

            // set new data
            m_data = new_data;
        }
    }

    void reserve(size_type size)
    {
        command_queue queue = default_queue();
        reserve(size, queue);
        queue.finish();
    }

    void shrink_to_fit(command_queue &queue)
    {
        pointer old_data = m_data;
        m_data = pointer(); // null pointer
        if(m_size > 0)
        {
            // allocate new buffer
            m_data = m_allocator.allocate(m_size);

            // copy old values to the new buffer
            ::boost::compute::copy(old_data, old_data + m_size, m_data, queue);
        }

        if(capacity() > 0)
        {
            // free old memory
            m_allocator.deallocate(old_data, capacity());
        }
    }

    void shrink_to_fit()
    {
        command_queue queue = default_queue();
        shrink_to_fit(queue);
        queue.finish();
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
        if(index >= size()){
            BOOST_THROW_EXCEPTION(std::out_of_range("index out of range"));
        }

        return operator[](index);
    }

    const_reference at(size_type index) const
    {
        if(index >= size()){
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

    template<class InputIterator>
    void assign(InputIterator first,
                InputIterator last,
                command_queue &queue)
    {
        // resize vector for new contents
        resize(detail::iterator_range_size(first, last), queue);

        // copy values into the vector
        ::boost::compute::copy(first, last, begin(), queue);
    }

    template<class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        command_queue queue = default_queue();
        assign(first, last, queue);
        queue.finish();
    }

    void assign(size_type n, const T &value, command_queue &queue)
    {
        // resize vector for new contents
        resize(n, queue);

        // fill vector with value
        ::boost::compute::fill_n(begin(), n, value, queue);
    }

    void assign(size_type n, const T &value)
    {
        command_queue queue = default_queue();
        assign(n, value, queue);
        queue.finish();
    }

    /// Inserts \p value at the end of the vector (resizing if neccessary).
    ///
    /// Note that calling \c push_back() to insert data values one at a time
    /// is inefficient as there is a non-trivial overhead in performing a data
    /// transfer to the device. It is usually better to store a set of values
    /// on the host (for example, in a \c std::vector) and then transfer them
    /// in bulk using the \c insert() method or the copy() algorithm.
    void push_back(const T &value, command_queue &queue)
    {
        insert(end(), value, queue);
    }

    /// \overload
    void push_back(const T &value)
    {
        command_queue queue = default_queue();
        push_back(value, queue);
        queue.finish();
    }

    void pop_back(command_queue &queue)
    {
        resize(size() - 1, queue);
    }

    void pop_back()
    {
        command_queue queue = default_queue();
        pop_back(queue);
        queue.finish();
    }

    iterator insert(iterator position, const T &value, command_queue &queue)
    {
        if(position == end()){
            resize(m_size + 1, queue);
            position = begin() + position.get_index();
            ::boost::compute::copy_n(&value, 1, position, queue);
        }
        else {
            ::boost::compute::vector<T, Alloc> tmp(position, end(), queue);
            resize(m_size + 1, queue);
            position = begin() + position.get_index();
            ::boost::compute::copy_n(&value, 1, position, queue);
            ::boost::compute::copy(tmp.begin(), tmp.end(), position + 1, queue);
        }

        return position + 1;
    }

    iterator insert(iterator position, const T &value)
    {
        command_queue queue = default_queue();
        iterator iter = insert(position, value, queue);
        queue.finish();
        return iter;
    }

    void insert(iterator position,
                size_type count,
                const T &value,
                command_queue &queue)
    {
        ::boost::compute::vector<T, Alloc> tmp(position, end(), queue);
        resize(size() + count, queue);

        position = begin() + position.get_index();

        ::boost::compute::fill_n(position, count, value, queue);
        ::boost::compute::copy(
            tmp.begin(),
            tmp.end(),
            position + static_cast<difference_type>(count),
            queue
        );
    }

    void insert(iterator position, size_type count, const T &value)
    {
        command_queue queue = default_queue();
        insert(position, count, value, queue);
        queue.finish();
    }

    /// Inserts the values in the range [\p first, \p last) into the vector at
    /// \p position using \p queue.
    template<class InputIterator>
    void insert(iterator position,
                InputIterator first,
                InputIterator last,
                command_queue &queue)
    {
        ::boost::compute::vector<T, Alloc> tmp(position, end(), queue);

        size_type count = detail::iterator_range_size(first, last);
        resize(size() + count, queue);

        position = begin() + position.get_index();

        ::boost::compute::copy(first, last, position, queue);
        ::boost::compute::copy(
            tmp.begin(),
            tmp.end(),
            position + static_cast<difference_type>(count),
            queue
        );
    }

    /// \overload
    template<class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last)
    {
        command_queue queue = default_queue();
        insert(position, first, last, queue);
        queue.finish();
    }

    iterator erase(iterator position, command_queue &queue)
    {
        return erase(position, position + 1, queue);
    }

    iterator erase(iterator position)
    {
        command_queue queue = default_queue();
        iterator iter = erase(position, queue);
        queue.finish();
        return iter;
    }

    iterator erase(iterator first, iterator last, command_queue &queue)
    {
        if(last != end()){
            ::boost::compute::vector<T, Alloc> tmp(last, end(), queue);
            ::boost::compute::copy(tmp.begin(), tmp.end(), first, queue);
        }

        difference_type count = std::distance(first, last);
        resize(size() - static_cast<size_type>(count), queue);

        return begin() + first.get_index() + count;
    }

    iterator erase(iterator first, iterator last)
    {
        command_queue queue = default_queue();
        iterator iter = erase(first, last, queue);
        queue.finish();
        return iter;
    }

    /// Swaps the contents of \c *this with \p other.
    void swap(vector &other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_allocator, other.m_allocator);
    }

    /// Removes all elements from the vector.
    void clear()
    {
        m_size = 0;
    }

    allocator_type get_allocator() const
    {
        return m_allocator;
    }

    /// Returns the underlying buffer.
    const buffer& get_buffer() const
    {
        return m_data.get_buffer();
    }

    /// \internal_
    ///
    /// Returns a command queue usable to issue commands for the vector's
    /// memory buffer. This is used when a member function is called without
    /// specifying an existing command queue to use.
    command_queue default_queue() const
    {
        const context &context = m_allocator.get_context();
        command_queue queue(context, context.get_device());
        return queue;
    }

private:
    /// \internal_
    BOOST_CONSTEXPR size_type _minimum_capacity() const { return 4; }

    /// \internal_
    BOOST_CONSTEXPR float _growth_factor() const { return 1.5; }

private:
    pointer m_data;
    size_type m_size;
    allocator_type m_allocator;
};

namespace detail {

// set_kernel_arg specialization for vector<T>
template<class T, class Alloc>
struct set_kernel_arg<vector<T, Alloc> >
{
    void operator()(kernel &kernel_, size_t index, const vector<T, Alloc> &vector)
    {
        kernel_.set_arg(index, vector.get_buffer());
    }
};

// for capturing vector<T> with BOOST_COMPUTE_CLOSURE()
template<class T, class Alloc>
struct capture_traits<vector<T, Alloc> >
{
    static std::string type_name()
    {
        return std::string("__global ") + ::boost::compute::type_name<T>() + "*";
    }
};

// meta_kernel streaming operator for vector<T>
template<class T, class Alloc>
meta_kernel& operator<<(meta_kernel &k, const vector<T, Alloc> &vector)
{
  return k << k.get_buffer_identifier<T>(vector.get_buffer());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_VECTOR_HPP

/* vector.hpp
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
*/