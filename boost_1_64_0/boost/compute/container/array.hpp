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
4srv8vL96g/uW7ErFs82X3l0qSvlsenB9Xr1ocuuhqteirFfnHnYA+/XwrlvsOvw/OiR4sw8+tqX8v06/j9CnPgCTsmwrk5cGuR6U5wL3ABnbz8kQh2D7kH/y1T3Kv2O/XYSL/HK7fTnXPu85X1IX01yvV38UT5OaaRTPMFPvqObGZdEfDnnF/H9ePjoI3ius7yXbx3aE3DlL3T8EXTLZvHMPMXpUyhJcv7KNf6/Fe+6NkL/qPj3ozpKq/i7siN9EZ7t4O+8X76+xzTxPo89VMIFK/bgnWPwuAh5Lzx3gg659TjrNK+hV9j/sBDfz3gADs1Uf58Bt2fCCyfK22Nj6Azi3C56YbJ5nGv9up/XxIjz4TrweHW8bnSWRO851z51+vUif9LfHJ5P5znTWujux/t5izpEL3nh5mj7Wqr3qOtnp+svvoLffiGOF6tzPCefzo9QP6Xzx9NX8ZvpV4mvneEy18sN+WUKfnMpPjBZH/u9eCY9d1GWc/J7iJ902KSxeKN4s8I+ktkJ8uFCdb4I+t6F7PsQ9sVuW+mdeVO89xPwmXFv/Y6+nAZPzVd3rBZnT6dXOqehGc6viGcneG5FNn/nR/kXsa8R+jDT1OUuwSOTo5w7BjeK04Vb6CapdNCjvb+6YNu0SDoyHAmfzpyq7n4CXsvOUkaxe/s2RF7o/emTi36QZ2bYX/iDeOe84vFDrSd6Vl0yjh+08pdx9K1adZex8rF8v/IFv//E/0foA8MDp74HZ7VYDzyQP90ovugfLnhEvDaOdeJHSU86X4Bj/vnHDk/TL75BneIjdbUifRiV4sjz6nGd5Kf7XGe5+XIuRjqeUx9jn8SnxMsy8f4Wz/OSfohv8JO94rHnK7Cuf0qufo5b2dWX8NYe/lLtPd/Xv/yW61/PbtlbjfGf+oy41lXey4VD5bWsM+G+f6uzw9s15zr/ZFp4jjA9eBI8cLLr4DFT7DOYLo4U9oLTzxVnGti/vtHaBPy8TFzrp95FpyyOph+OgKev9V5rzPfdeJO4NP8OvPphevJ0cWmSeKtfLeYo+HJzBL+278NOfRVp+HGmfoDr7dcgzhR85zmW8Tt9Ra0L6Hwj2McGzz8swbmX7vezOlbIb8x74yF042h8+Xa47kh60pw4/bv6DXuxkxp1f+dV/1MWCf4+HA91i+Zj1SHpBIX92fMXcJy+n3H99InvMM8l/FncLz2R3XxM3zvW/N1tnWlPOEseG5Ts9wPoNMan/zD4P5p906sajoHHptGh9H0NusW4n07vmkiPWyO+9oEPh4TrBOmxUeLaRn6zjX3bt6p4t3VNZ8kPMQm+jx+9jP/qN8rcrU93qzz7G15xsLgx13rsSLrqTLradezlTrxghX7XSvP0l/HJx5feZtezxd2L4fR/ec4J6lTP0Jnvxz9i6XWrrNOAM1t/Z6fn+N7h6sDP0X/odDl17GeHOpFzBbIe1ffVkb31wGvh3Ta8fPYLUfiNvqIZ+uwOwztK4ZoPvOdGfRFfhOc86QOsNO/TxI1w/949fr7GuqvL5Af5a8Vt+PGH4tEv7t9VvP47XI8LHwyQn8SrFT319d3L3iapwy7kj+vhyBPEtb36Ti/nzxPkHevtFvU2zzNj1PPlhXf1KbxH54frevWgb14MT7tPivktGB9lH1HPdZFxnY4/ThWXg339/vlHZ6qno9lXs/wpdvwYfiOOZl5unefLcNZOeehoea2P3+ObMRv57cmx9q9mz1H6js+Ak3Z1oNOoP/UK1ynDe9vU0dbKixfYVyWrg31efd95/mvtI1kkr9TD/SvMb8pO40fHXFvFz8+Phzvh/w87wPN4yGXGYaC+mBY8JLSP7nHqPfJ9tnOdl/o=
*/