//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2019 Miral Shah <miralshah2211@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#ifndef BOOST_GIL_EXTENSION_NUMERIC_KERNEL_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_KERNEL_HPP

#include <boost/gil/utilities.hpp>
#include <boost/gil/point.hpp>

#include <boost/assert.hpp>

#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>
#include <vector>
#include <cmath>
#include <stdexcept>

namespace boost { namespace gil {

// Definitions of 1D fixed-size and variable-size kernels and related operations

namespace detail {

/// \brief kernel adaptor for one-dimensional cores
/// Core needs to provide size(),begin(),end(),operator[],
/// value_type,iterator,const_iterator,reference,const_reference
template <typename Core>
class kernel_1d_adaptor : public Core
{
public:
    kernel_1d_adaptor() = default;

    explicit kernel_1d_adaptor(std::size_t center)
        : center_(center)
    {
        BOOST_ASSERT(center_ < this->size());
    }

    kernel_1d_adaptor(std::size_t size, std::size_t center)
        : Core(size) , center_(center)
    {
        BOOST_ASSERT(this->size() > 0);
        BOOST_ASSERT(center_ < this->size()); // also implies `size() > 0`
    }

    kernel_1d_adaptor(kernel_1d_adaptor const& other)
        : Core(other), center_(other.center_)
    {
        BOOST_ASSERT(this->size() > 0);
        BOOST_ASSERT(center_ < this->size()); // also implies `size() > 0`
    }

    kernel_1d_adaptor& operator=(kernel_1d_adaptor const& other)
    {
        Core::operator=(other);
        center_ = other.center_;
        return *this;
    }

    std::size_t left_size() const
    {
        BOOST_ASSERT(center_ < this->size());
        return center_;
    }

    std::size_t right_size() const
    {
        BOOST_ASSERT(center_ < this->size());
        return this->size() - center_ - 1;
    }

    auto center() -> std::size_t&
    {
        BOOST_ASSERT(center_ < this->size());
        return center_;
    }

    auto center() const -> std::size_t const&
    {
        BOOST_ASSERT(center_ < this->size());
        return center_;
    }

private:
    std::size_t center_{0};
};

} // namespace detail

/// \brief variable-size kernel
template <typename T, typename Allocator = std::allocator<T> >
class kernel_1d : public detail::kernel_1d_adaptor<std::vector<T, Allocator>>
{
    using parent_t = detail::kernel_1d_adaptor<std::vector<T, Allocator>>;
public:

    kernel_1d() = default;
    kernel_1d(std::size_t size, std::size_t center) : parent_t(size, center) {}

    template <typename FwdIterator>
    kernel_1d(FwdIterator elements, std::size_t size, std::size_t center)
        : parent_t(size, center)
    {
        detail::copy_n(elements, size, this->begin());
    }

    kernel_1d(kernel_1d const& other) : parent_t(other) {}
    kernel_1d& operator=(kernel_1d const& other) = default;
};

/// \brief static-size kernel
template <typename T,std::size_t Size>
class kernel_1d_fixed : public detail::kernel_1d_adaptor<std::array<T, Size>>
{
    using parent_t = detail::kernel_1d_adaptor<std::array<T, Size>>;
public:
    static constexpr std::size_t static_size = Size;
    static_assert(static_size > 0, "kernel must have size greater than 0");
    static_assert(static_size % 2 == 1, "kernel size must be odd to ensure validity at the center");

    kernel_1d_fixed() = default;
    explicit kernel_1d_fixed(std::size_t center) : parent_t(center) {}

    template <typename FwdIterator>
    explicit kernel_1d_fixed(FwdIterator elements, std::size_t center)
        : parent_t(center)
    {
        detail::copy_n(elements, Size, this->begin());
    }

    kernel_1d_fixed(kernel_1d_fixed const& other) : parent_t(other) {}
    kernel_1d_fixed& operator=(kernel_1d_fixed const& other) = default;
};

// TODO: This data member is odr-used and definition at namespace scope
// is required by C++11. Redundant and deprecated in C++17.
template <typename T,std::size_t Size>
constexpr std::size_t kernel_1d_fixed<T, Size>::static_size;

/// \brief reverse a kernel
template <typename Kernel>
inline Kernel reverse_kernel(Kernel const& kernel)
{
    Kernel result(kernel);
    result.center() = kernel.right_size();
    std::reverse(result.begin(), result.end());
    return result;
}


namespace detail {

template <typename Core>
class kernel_2d_adaptor : public Core
{
public:
    kernel_2d_adaptor() = default;

    explicit kernel_2d_adaptor(std::size_t center_y, std::size_t center_x)
        : center_(center_x, center_y)
    {
        BOOST_ASSERT(center_.y < this->size() && center_.x < this->size());
    }

    kernel_2d_adaptor(std::size_t size, std::size_t center_y, std::size_t center_x)
        : Core(size * size), square_size(size), center_(center_x, center_y)
    {
        BOOST_ASSERT(this->size() > 0);
        BOOST_ASSERT(center_.y < this->size() && center_.x < this->size()); // implies `size() > 0`
    }

    kernel_2d_adaptor(kernel_2d_adaptor const& other)
        : Core(other), square_size(other.square_size), center_(other.center_.x, other.center_.y)
    {
        BOOST_ASSERT(this->size() > 0);
        BOOST_ASSERT(center_.y < this->size() && center_.x < this->size()); // implies `size() > 0`
    }

    kernel_2d_adaptor& operator=(kernel_2d_adaptor const& other)
    {
        Core::operator=(other);
        center_.y = other.center_.y;
        center_.x = other.center_.x;
        square_size = other.square_size;
        return *this;
    }

    std::size_t upper_size() const
    {
        BOOST_ASSERT(center_.y < this->size());
        return center_.y;
    }

    std::size_t lower_size() const
    {
        BOOST_ASSERT(center_.y < this->size());
        return this->size() - center_.y - 1;
    }

    std::size_t left_size() const
    {
        BOOST_ASSERT(center_.x < this->size());
        return center_.x;
    }

    std::size_t right_size() const
    {
        BOOST_ASSERT(center_.x < this->size());
        return this->size() - center_.x - 1;
    }

    auto center_y() -> std::size_t&
    {
        BOOST_ASSERT(center_.y < this->size());
        return center_.y;
    }

    auto center_y() const -> std::size_t const&
    {
        BOOST_ASSERT(center_.y < this->size());
        return center_.y;
    }

    auto center_x() -> std::size_t&
    {
        BOOST_ASSERT(center_.x < this->size());
        return center_.x;
    }

    auto center_x() const -> std::size_t const&
    {
        BOOST_ASSERT(center_.x < this->size());
        return center_.x;
    }

    std::size_t size() const
    {
        return square_size;
    }

    typename Core::value_type at(std::size_t x, std::size_t y) const
    {
        if (x >= this->size() || y >= this->size())
        {
            throw std::out_of_range("Index out of range");
        }
        return this->begin()[y * this->size() + x];
    }

protected:
    std::size_t square_size{0};

private:
    point<std::size_t> center_{0, 0};
};

/// \brief variable-size kernel
template
<
    typename T,
    typename Allocator = std::allocator<T>
>
class kernel_2d : public detail::kernel_2d_adaptor<std::vector<T, Allocator>>
{
    using parent_t = detail::kernel_2d_adaptor<std::vector<T, Allocator>>;

public:

    kernel_2d() = default;
    kernel_2d(std::size_t size,std::size_t center_y, std::size_t center_x)
        : parent_t(size, center_y, center_x)
    {}

    template <typename FwdIterator>
    kernel_2d(FwdIterator elements, std::size_t size, std::size_t center_y, std::size_t center_x)
        : parent_t(static_cast<int>(std::sqrt(size)), center_y, center_x)
    {
        detail::copy_n(elements, size, this->begin());
    }

    kernel_2d(kernel_2d const& other) : parent_t(other) {}
    kernel_2d& operator=(kernel_2d const& other) = default;
};

/// \brief static-size kernel
template <typename T, std::size_t Size>
class kernel_2d_fixed :
    public detail::kernel_2d_adaptor<std::array<T, Size * Size>>
{
    using parent_t = detail::kernel_2d_adaptor<std::array<T, Size * Size>>;
public:
    static constexpr std::size_t static_size = Size;
    static_assert(static_size > 0, "kernel must have size greater than 0");
    static_assert(static_size % 2 == 1, "kernel size must be odd to ensure validity at the center");

    kernel_2d_fixed()
    {
        this->square_size = Size;
    }

    explicit kernel_2d_fixed(std::size_t center_y, std::size_t center_x) :
        parent_t(center_y, center_x)
    {
        this->square_size = Size;
    }

    template <typename FwdIterator>
    explicit kernel_2d_fixed(FwdIterator elements, std::size_t center_y, std::size_t center_x)
        : parent_t(center_y, center_x)
    {
        this->square_size = Size;
        detail::copy_n(elements, Size * Size, this->begin());
    }

    kernel_2d_fixed(kernel_2d_fixed const& other) : parent_t(other) {}
    kernel_2d_fixed& operator=(kernel_2d_fixed const& other) = default;
};

// TODO: This data member is odr-used and definition at namespace scope
// is required by C++11. Redundant and deprecated in C++17.
template <typename T, std::size_t Size>
constexpr std::size_t kernel_2d_fixed<T, Size>::static_size;

template <typename Kernel>
inline Kernel reverse_kernel_2d(Kernel const& kernel)
{
    Kernel result(kernel);
    result.center_x() = kernel.lower_size();
    result.center_y() = kernel.right_size();
    std::reverse(result.begin(), result.end());
    return result;
}


/// \brief reverse a kernel_2d
template<typename T, typename Allocator>
inline kernel_2d<T, Allocator>  reverse_kernel(kernel_2d<T, Allocator> const& kernel)
{
   return reverse_kernel_2d(kernel);
}

/// \brief reverse a kernel_2d
template<typename T, std::size_t Size>
inline kernel_2d_fixed<T, Size> reverse_kernel(kernel_2d_fixed<T, Size> const& kernel)
{
   return reverse_kernel_2d(kernel);
}

} //namespace detail

}} // namespace boost::gil

#endif

/* kernel.hpp
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
*/