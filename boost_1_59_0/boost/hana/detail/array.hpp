/*!
@file
Defines `boost::hana::detail::array`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_ARRAY_HPP
#define BOOST_HANA_DETAIL_ARRAY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/functional/placeholder.hpp>

#include <cstddef>


namespace boost { namespace hana { namespace detail {
    template <typename N>
    constexpr N factorial(N n) {
        N result = 1;
        while (n != 0)
            result *= n--;
        return result;
    }

    //! @ingroup group-details
    //! A minimal `std::array` with better `constexpr` support.
    //!
    //! We also provide some algorithms from the `constexpr/algorithm.hpp`
    //! header as member functions to make them easier to use in constexpr
    //! contexts, since a `constexpr` `array` can't be mutated in place.
    template <typename T, std::size_t Size>
    struct array {
        T elems_[Size > 0 ? Size : 1];

        constexpr T& operator[](std::size_t n)
        { return elems_[n]; }

        constexpr T const& operator[](std::size_t n) const
        { return elems_[n]; }

        constexpr std::size_t size() const noexcept
        { return Size; }

        constexpr T* begin() noexcept             { return elems_; }
        constexpr T const* begin() const noexcept { return elems_; }
        constexpr T* end() noexcept               { return elems_ + Size; }
        constexpr T const* end() const noexcept   { return elems_ + Size; }

        // Algorithms from constexpr/algorithm.hpp
        constexpr array reverse() const {
            array result = *this;
            detail::reverse(result.begin(), result.end());
            return result;
        }

        template <typename BinaryPred>
        constexpr auto permutations(BinaryPred pred) const {
            array<array<T, Size>, detail::factorial(Size)> result{};
            auto out = result.begin();
            array copy = *this;

            do *out++ = copy;
            while (detail::next_permutation(copy.begin(), copy.end(), pred));

            return result;
        }

        constexpr auto permutations() const
        { return this->permutations(hana::_ < hana::_); }


        template <typename BinaryPred>
        constexpr auto sort(BinaryPred pred) const {
            array result = *this;
            detail::sort(result.begin(), result.end(), pred);
            return result;
        }

        constexpr auto sort() const
        { return this->sort(hana::_ < hana::_); }

        template <typename U>
        constexpr auto iota(U value) const {
            array result = *this;
            detail::iota(result.begin(), result.end(), value);
            return result;
        }
    };

    template <typename T, std::size_t M, typename U, std::size_t N>
    constexpr bool operator==(array<T, M> a, array<U, N> b)
    { return M == N && detail::equal(a.begin(), a.end(), b.begin(), b.end()); }

    template <typename T, std::size_t M, typename U, std::size_t N>
    constexpr bool operator<(array<T, M> a, array<U, N> b) {
        return M < N || detail::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_ARRAY_HPP

/* array.hpp
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
*/