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