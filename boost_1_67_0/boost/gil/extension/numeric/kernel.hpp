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

} //namespace detail

/// \brief reverse a kernel
//template <typename Kernel>
//inline Kernel reverse_kernel(Kernel const& kernel)
//{
//    Kernel result(kernel);
//    result.center() = kernel.right_size();
//    std::reverse(result.begin(), result.end());
//    return result;
//}

}} // namespace boost::gil

#endif

/* kernel.hpp
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
*/