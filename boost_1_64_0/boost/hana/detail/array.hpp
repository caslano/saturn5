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
nbuwOqi31DcRPxeTHYwNbSD5hJmR+brt2qYsBMaZb3462V92GsbzO1vxaQuZLawsWXLvgRclu7ASZP3WR3+W7GrP+Vuhd7Vkp7XnfJ2VcEdZtvacQ0usk36+gvFONxj3ppFkfpJxPqc1qbBQejZJy+edjnJNX5grWdnEdvdlH2BWZEER1u+VRcJ8OWdFbXKVxcMsOfMPnkl9iTA/snP1AuVcuvacC9ZNWyB9gdUj2+TW66XsdDx+X0AWUDZkt9QAs+FcLw6UOUTBuIaB61fIcybADGSXkx+ckLnDKpC1Xh9bVWYL4+zeyxg1R3IN8yIrOfTqF5nRZOPvDL3n/mkluYZxzsqPy2wu9cF430t5TEmVOcD4fh55Ib6ST1gZss9T3gyVGmDWPPfZ8TKHHBjv7a8pr09LfTDO9eLKRWcoK4DxbOMXL2iizGyK8bku68tPltnCOEvXejilKXOHOfKuTOz6SXoGsyM7/OBnmW04zJ6s4b2eY5VFwzgv0UNfvJJ+avZoviFOMgHjnu1xyCosvYYZyMKil/+qLA3G+/5H7INDynJhDmQdJtytI/2EOXFetm+cLz2bavwsDks735SewdzI0vo93KAsBFaW++Ji3k52BcZzuPliRCFlMTB3sre/ecmOJcJKk1WLLi33S9WexaFJ48Oy75o1qnUpXnIGK0rvwSnFmi6Vvmi1H2k6aKTkbBp+liE7NulInvQFxrvS/IbrGckLTP0zjW/vszrHm0t9sKp07k6vfY+VHYUVoee8fWtuXdkxGGf+aKM2UkM2jOszW7hmkeyfds2lLbcekbzAeB9uz52+6j/W3aQAZvjvnxP+AX/99X+Sl+mmJhHfDD9GKVCzhSX/t/b+X2fUf6KbnJthajLq27nA/zmXALMnY1sBiyhERpafgL789znba1bw/w0v9v9vZrpx7TCn//bz69+zXWn2RpkvzEAWaWay4z+G/1YlmSn+zrq7U3soC4U5kW3OC3VTFqWda/1D3xPKYjS7+di1irJ4mCWZa/dpg5XN1e7XPn/EZGVrYfZkk++ecleWpt2v0PyltsoyNOtbvmKOshztmg8vPtmq7LFmybOvZiszmW18zTUbDRWUGWZr9XWpUleZK4zr67x/pYOy6jB3smmX3hVSFqHdb+OSix2V9YH5kll1/Bwm/dSeJa5CQjllSdqzLF87oJGyVP1ZiqwIVZatPcvBtTaWynK1Z7nc7elSZWZzjM95JcyZq8wJxs/56e/Mk8q8YF5kJ/y7/yz51K7ZaV3nzcoiYTy/xvELHisbrNnwbb8Nl3xqdu3muBrKFmr3WzqodWvJp3Zu/dwnUyWf2jlT378SJZ+ajc4xWyn51Ozj0d2HlOVp9xu4ukueso8wJ56R+9gEZfZzMQuyfkl7J0o+YTz3AceLxSkLhrlyBl3rS18iYXy/A4/XHFEWA/Pi2g3Jq6Wf2rNcHvBLhLIV2jVjo7N9lO3UnmV24p8tJJ/aNXuPXXhE+gnjfjbNbTlU+gnjfrYvYtVb+qndryB0updkd57xNfddOrNWmS+M+xlzaqibZBfG9c1yd7qsLApmz9dsVqWNspHa/f6sbmGqbJp2rmbRj01l3zUr0WuMnNukXdO0UL2Xyg7o9TXsW1tZplbDoWXuY5Xd0c4N+jPTVdkrGPezRVezecoM/zB+F1TeejlT8gnjGpxm/7FfWaB27lLKyDTJLoznUD4suLuyrjAD2Q/n1zeQ9wSM67v7t2+89Fq7ZkGrptPkXaCda7JrbD/pp/acgztdkOfM0Op71NzUT9lVzZqVPhOtLF+7394z3vnKzP5pfC523cGfpZ+a5az4/Lv0E8Z9qVjTu5SyEM0Cf/I5piw=
*/