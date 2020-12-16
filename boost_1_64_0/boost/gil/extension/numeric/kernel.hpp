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
P0QBgYvorACDuI/rCJBMMoL0+lLsw5PC/VDKh99CRAh5weyFUvn++V2qB/C1CtDeaarvdEi0jSZCKMXOUeiZegr9ZQX3Hr5UUZPi+Q4T3QsgJAEluL0s5plLazU7otuFFmDhzRRQ0quedZCtwkzJFkaunJeJBK07/U2QucQ1EznX1KYdRCRs+iNqYulGXICe6Hb1P+8flivGIDCuTSYS5UPhSXJ7TadNRDvSBNHqaM0WmidWWJKREStsLU31FJtCeHAcgBUg44qzgJa3OB2Xb3Y6bmrndHSE6wDXDc4D1xBuMBxu2UdERkVXiPl//quIf7b95jTLGp2HPaRfvn1esLWRnhfguLGxmFa40MdvYPM82f+DyfiQLYXu+mxN2ouYoGddbQENlorizpfN4xAHixgVxo8CxMVHpEFQSumIX7231xAxQODbzpHWxFhaqxaVtFUlvCNGSJlSWPpKmbIflsOzWnusNHM+iJDfyaBEm4WXx70VerhNXjcylRP7Jw/H+AF/CxKmNY+70CZt8jzdOK09PSYZb3xvTIpqTMkaTY40ZjKnPxJO8SVN5i9WMgOQTGgx9SwsQIKkK2XBr1U2P4utR+mNLcnXkxsjKPFi3aoRPKg2Po86RsX/iT1zZaI2bpB28P8Wfw6pFoxjvy6g8Og7s+F95BD2dSx4cK+8vJMfI+N/IyBcrpYACUCwuACutYB+AL92KnqEt+3UcxK63Ap9AqFcjuXM0IINLhcjKhzjWSu0S7kYPgvWwo6RdbzYewMiMFceK7AyAvVK5CALUvIeCqNX+++2QD8BhM+llfRzz3tXclaPW4y3/Ui+bGC4nbnbYrRsk4JZ660dRyB1c4q/ROR5blHE9of8Z/lC0BFz/kNltTfrFQAbJ3B3FXbP76SbGy7vy4BgfMiKiGT0OSyAktGdMx3l3w8qI+PfABrYflY3c+zh4pp+DUWf5zbGeGviBHS6Q05AQx4/LHRMd/6buNeYtA8t/gLBAY8TFdPzOUyLe3A+JUJKxV7tcujW229MMyvG2/+OYDUThWAkyMxMA8aEW5Tq738D1cyrqF5rUy0233ygVO+WPf52dMBrcbqvKiO7l2MSLgldQxk/yTTDd2SJVUCn77Fk/ydAVEHpiTudkApMSPTnYRh1dDu81brZ+7+1pbkd6/qKyc1H5meV9JtQn3Z3KuqCtv1drkd76H1IkksWvaGXb9PgFe8yyVAvD/iDv4l93WQ5qB+Ej2RXUgGwiZYNNCtfkeNq23ppiUp3tJj583r9FxNzLIWrFs/qcH8L8RJztiuwugC3oeFMAPAr6xhVi2qual593+47s36mjLV0Avv4zgqaXSfiyfFNqIK2f7JfO5Laba8uyX2nyb05VvPQRID7FTiTQFRnVQBRlWoIUpeZIXk6Uq6Ehecb1NB3OLsMAxLuzuHkZQautWf+HXXtmR/TmfAII+/Ekv5xit7FWt5fL2iqfSUIOEvHVcL6OxwW7L39TEBCfUGuARlyNdHcO0j1l/yq2vPqleNFrZ+Ikt4RVKx5zyEEbi7NCz3I94r7IOn0O0ko9CTW4GH1KoieRnU9d81ZaltbuTt+x+cROKw23d9ClWBOkOcFYBGFheuG9Z/rPiIjPbGNaR7m/hfRyz3a6Zr6pBhT0ayzi85AFehM/o9cmclZV6jNsn9/JkqJAr7adaUoJQMyD8NzT9FsAMMtL0aVqT7tFVlK3L4yWcqf6d/qBvLtNdbkhtZpjSoilicw9nUc79Kb4A9hxVWVWf9ZenPkYCvJH8IZnTF9VQE31RxKkcYcK4feiet56F1xTFD0YBvfYevBdkrSKxLfmvbiKwrlmxuS7APrNg1L9XQLluddAi0=
*/