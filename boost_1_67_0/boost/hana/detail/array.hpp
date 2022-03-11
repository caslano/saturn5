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


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
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

} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_ARRAY_HPP

/* array.hpp
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
*/