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
vImxTmQE+nZFxrtBcazISZcqMv0NellvjKZQj64EGg0nSpoycdm3hJy19pGS+bm8efPMwgYD5Hk1t6v1HboEsdTMFh4mLfPqFy1y2Hjz439Zu44u95t1Qq6OHy2t+Uus9X58Ul0LER6dpIMp26OTkryjpZx4jEdOxldLUN04QlJIvtmWbyL2ND699tE0ndck68JGwSwTQ0NeWnisrCMGOc9MDMTcYDfX6+ELr5LGVrq/MYfxmhzKQb8pFyEPQWfQZDLUvTG2Q+3mhTqvmzhyfIHNxWTzfOsJkBH3g7bgf8KAJgtdnkS0u0MdJdz7uiJj+GvQ+dxURT2U+QiNwlZqmqH2i21lOfw74cnCygw5nKFGq8phUZApULMHdQ95FzW+0zuoxhcTjwUx3PhihtudpGy+VQbc6IY0TM404g+E849fo6ixo8pX+1eiYR1lGiTtBU43uqNLbZtz+MYrIYXXLagCNASVYrr/FsTxkcMVd53oHCAbTbkbzXxG7SZohRQ8bmxP0+vDK4jdAs0RtmdtNKPzaNuZCgM5gxcj5Gxpyjt4CghdRBO9Pht+G81EjxlAIq9JnxFOtZ2BiT4kN+iz1+JBMLpU3+Y1iBzb87XEqEPcgFEJopQqTNcRC6L0mCn3MUTpsSEoFSgo3ZH1mBkgtihgFC32z/8OxWqeJL49FKsy/SYNWknEmaY3h9NseKeGoZaDmNlUzFLXafc4
*/