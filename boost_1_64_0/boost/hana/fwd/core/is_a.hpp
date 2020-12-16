/*!
@file
Forward declares `boost::hana::is_a` and `boost::hana::is_an`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_IS_A_HPP
#define BOOST_HANA_FWD_CORE_IS_A_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Returns whether the tag of an object matches a given tag.
    //!
    //! Given a tag `Tag` and a C++ type `T`, `is_a<Tag, T>` is a compile-time
    //! Logical representing whether the tag of `T` is exactly `Tag`. In other
    //! words, it is equivalent to
    //! @code
    //!     std::is_same<Tag, tag_of<T>::type>
    //! @endcode
    //!
    //! For convenience, an alternate syntax is provided for using `is_a`.
    //! Specifically, `is_a<Tag>` is a function object returning whether the
    //! argument it is passed has the given tag. In other words,
    //! @code
    //!     is_a<Tag>(x) == is_a<Tag, decltype(x)>
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/is_a.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Tag, typename optional_T>
    constexpr auto is_a = see-documentation;
#else
    template <typename Tag, typename ...T>
    struct is_a_t;

    template <typename Tag, typename ...T>
    constexpr is_a_t<Tag, T...> is_a{};
#endif

    //! @ingroup group-core
    //! Equivalent to `is_a`; provided for consistency with the rules of the
    //! English language.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Tag, typename ...T>
    constexpr auto is_an = is_a<Tag, T...>;
#else
    template <typename Tag, typename ...T>
    constexpr is_a_t<Tag, T...> is_an{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_IS_A_HPP

/* is_a.hpp
qhsp+FGKGZrFUwnFXGjEXEoxyy8jlsvwe5z8bqDUY5jHm0Spv72TnOMp9ctGzI0Uc8RlTHtM3lvIuy8BeIfJ32kEIGs8s1LkXM3OVHJWc4Rkcu67ipwHiaL0YE7tB3LuYaZKFLJI5jfq/165J1sYaO/fBlS1EruGExe9An3E6QvkMW86An1y5NTIpbbIDXaHM8nRzupw5jkd7XKceKfhDVE2X669rujQa+5Ad86HpVqDf9fwGLq6PyD+u0e9b1e9b702Gth/bmg/WC8nyjciotY0qXSbacQuzYLa8EqBddDGytECe/+x8B4Nw1to37VJe/YtuJ+jWXvlLbQn3aQ97xbYD/YFevlToqhgl/j2ZmNTN5QA5RHSrbB4YyrWPvHErboqXfAMeDi1vFR6wdqxbBc3LYfp51MHKeHZmsX9kB5EcdUyFhyBPpwfLrAKSLl8VQu0dE34xl2uvXYxo5eKfYRnPQSu/mWY6j6oJNiIzcbxN9q24/z92fgjzirUj79xOdBPo1vowD6J3PdAqtQaSpnn23E2PknLpjV2WxQ1kOATX41UyaZAap8idl3MK+iWFIXlrUnA1XRntG9J0zOkV16QTLk+S5axhtsoo5lsT8+ldQSS7edG5QF1rXVWgqPsRLjIx4b3SDF5IqvRuPlYSbCXV0y9QIl6ewa8XBPyKBcJSwNJ4v0gtzDrlFVGzxFHyT00bRvpt5BpzOg5XrFzvKFlFjolUNQQSjmgeEXtVfoVj2yRClQqKavKURaWNgGPBxHAq3NgOif3UDWezpvRSg/wZ2zykGWEgSFveHZ3S/AibWhqYCb0qThBtLi7GDBXVzGlPc1egRLZkXOqT4fwTJ0SW6ANBJZlgWs5kKX21Q6Ea3mkp3KCD4p/rf17CG2Q6l2DdTHm7OTwnoOOuT9B2VNHI5hcNI4HEJ2pQE9xRrccpiWU3+ah8RyRNDO6U/WnVRdxK1VPg+DYHDmmzyNP+YbPs0jrrNpQG8lqPeLKfNUd3HxjlKzCkwPXohWrpnJfoI0I7oVONGDrkFMblxKw+cQXw7nPY2Bv94mzgIDD2RqQHO2SfnCUDHVOdGzNUy2pS/rCs3HC7UQtSW959MfcyDh9EBWnUAd4/i3Wu0VDo5m1odRCEHntPE9qiFGLhYb6xMZh/M26spX+DxXWHvHyHFN/eNi/3ShPDpfn5+u5PDIdoeGmW+4KmXzZyW+cVAID0JeMpNdx0pdl0pYoKP3Khy/qtgKxEzGLEk0107uR0S2Zb0gzAPeR6Zwm7POLFRcqOisJjHZVkwQmRv53lzaY3U33A97At4peEp6RBtvFRI3uv9W4kZgHRBoPCI51ZngGxmsPPtF4MvWVoBH3WC0pcDznqJPOLIladLpTtMkGMZ+O+xdpLwtziDai5WqPJnopL/8TnRfqBi/l1frtHDefx+pZ8z0f0KZyeV+8Cqvm1VqVjeUfdZd4/QaI8yPzPk4gy5iFUsFg3v0JFGcn/jr1vSB8fpCgEm/TXUQQyJZweQ42sdsWO4oiiwBHxkeQpKtEkGEHpiOfctjjLK4uijDk8kFWxGFN6awnySP0D/auBD7K4orvZjfJJmzYDUSIECTCosFEiQYFXJCEW0XYuGYXyxGsFLcrVsQNR8UY2ASyfKzaWlttrUdb61mLihCPakI0AS8QrcWqiPeHQQ4RCOXY/t+bb749SCAgtcevq+H75puZN29m3rx58+bNmzycz5X2WxU9cUSRzrXCpmr5Wh4oDHYqlTlVh5ztvJez/sKrPi+zBpa6RVZ2VaFOiMlNmVkL/BXEx3AtccJSV/jWVsQl4x8E1B+ViDmB8YcJ32TaVz60Mc1uRhO6306zv4m/AP4=
*/