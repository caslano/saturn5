/*!
@file
Adapts `std::pair` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_PAIR_HPP
#define BOOST_HANA_EXT_STD_PAIR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/first.hpp>
#include <boost/hana/fwd/second.hpp>

#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adaptation of `std::pair` for Hana.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A `std::pair` models exactly the same concepts as a `hana::pair`.
    //! Please refer to the documentation of `hana::pair` for details.
    //!
    //! @include example/ext/std/pair.cpp
    template <typename First, typename Second>
    struct pair { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct pair_tag; }}

    template <typename First, typename Second>
    struct tag_of<std::pair<First, Second>> {
        using type = ext::std::pair_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Product
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<ext::std::pair_tag> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return std::make_pair(static_cast<X&&>(x),
                                  static_cast<Y&&>(y));
        }
    };

    template <>
    struct first_impl<ext::std::pair_tag> {
        template <typename T, typename U>
        static constexpr T const& apply(std::pair<T, U> const& p)
        {  return p.first; }

        template <typename T, typename U>
        static constexpr T& apply(std::pair<T, U>& p)
        {  return p.first; }

        template <typename T, typename U>
        static constexpr T&& apply(std::pair<T, U>&& p)
        {  return static_cast<T&&>(p.first); }
    };

    template <>
    struct second_impl<ext::std::pair_tag> {
        template <typename T, typename U>
        static constexpr U const& apply(std::pair<T, U> const& p)
        {  return p.second; }

        template <typename T, typename U>
        static constexpr U& apply(std::pair<T, U>& p)
        {  return p.second; }

        template <typename T, typename U>
        static constexpr U&& apply(std::pair<T, U>&& p)
        {  return static_cast<U&&>(p.second); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_PAIR_HPP

/* pair.hpp
3wI8IImY828Ebg+Ckp66FTjIoqQyxCMNnrzShaZ03lV8gyH/THuYxn9HGd/m04TPvf/O91FitTm62306qjFaz/8AmlGMXSPoz6htjapA/04m16jjl8wxftZ0AZzHwVzOwGd1BS5J29bE9PBiwFsL89Yw3havVr+tQPHiTuCeBF489h44/yiyXbfKnBvfMN/Bjltl6D5LsAUCe/VRgNXExwp88JAtsXRJaO1djPqhuPQrepDJUpl81qXAUbxQyJzOqF8l+R/ogtbY9pYdR9MAGvMWDLgiQm8O9FEMaJmhyUwiEKevKo4Rhul0hIjpnB5aiTaxA1+BpkVoz41xI+DoqoBV3A3sy7k1oymGj+ds7IIfB0nXtq39TM7LXGVs3wnvriFe304HjaQPYK1y37VOeKTfp5D8Ic1TUPF6dy+my8bvQjrbr0NetY/w5wKfK8kKhLUc+2YVrnu9lC9U5Epv3rsQnPq2yj7kFuRsDSgfoBGkjfsDZw3sLLa8C3nLI+7DRuFhqqtryM8JbqP6y55e6+ByeHwXgoqQasXlTnr46VL8raP7AL+9P9XJ7d2Xyvh7axcBh/g4pngpR3DIl7z1LnIX1b8VcNnpt212ATZVmcBcdfOtBzA1QBLYl91sissLD9QSyfbKvZdF5fBxktyjcmP4ey5GWb7MHQs3+OOXh9DZFEOU9ebwBJltUdt9hMNx7zKsY+mBk+9+olE+Hz9IxuO4M/p+cSyhCmaQJmDbup/MT0Ujh8Ilx6RCck40ck0AteHVMTM17a3VQ9RX6YW8kUk5m46mWX+Q987LLsbnMsW83sMsYbU8bPu5J0EzM1nJOL15kupnHv1HITtZJG0ootkb6WdU4jKS42eZoTP5XoNcK7QC+xyXrKJ3kCGM/E4n+qfhFfNMu9uDkL5rW8fIqv2uBwoO75LyMFt8mvDOmHH9zXB/MDTQ8LP8ZklWykPF+W1YvuSJhtthG2aCaPznoFj2C9Qf6YuNDe2v3hd7dm4d0Yb7FL/7cAp0ovrT0brMc71I9UT7gLJuW5oS1RHJkIiO7fu0V09C1mi/rEy0lSPQzsRpmy0xlKJ/DvAA9xP1itq0+MNUV0hGHy7llc41PHBrziNjtoshmZSHTXjf9VGsD+xrE2JfoL6w3pAVjub8pauCd18ozWBt08eABrM8f0h9BcmYeutA6xri6Nk1vHkg6V7ht4Do3XL7duYq246/Cmtb8wnAXwlb84mwP88U+/NJgP0QsP55DvYUoXs10T1N6E4g2GWA3f9oyOMxDvZMofsW0T1XYNfXOdjbAFtwMnI0CPYuofs2wd4rfXkl1fdxKXtfovuiwJYT7JtRu+rbaorBV0RCQvb1TNC+/toqienAaJqF6HR4b5RDZpXgqgEtluo479W8MSCIW1kvw45Dx1xGdoT7lswXi+A8M8FZ4aG2vgecMnEQUtTPyS+lvsPOSZyr+gHgRSXFCNbMlCDLNA9+FPUhP6lek3JkqjytOfYYCorH/G/gEJvx8uDpniuxEUQZ2/n5W8CxH+tCddjW5np/7+Flw9bW+0eDH+4cUSUdv++wcClBPP0z8VT0lJ1rdwZsHrHrLM1fiEY0T2fKPEmDfntjCoMWqgssw+pB6/t6axPCdIfXaXK3KafNt1WwHcpvVvyNdKw8qjBZmjDalPdBlCMvTCjktBalQx5wwdjPmS+0HCPxbfiDXszNe++GTE3X13s0BmxNuZFfEc5Fl8dFiUVFxecsha5zZ/+gu7HCffMxrp5mkmT8c6I0U8DqTWcXmBYO6nRRZgBobH3HOhqLxRM7M9OqXlgBPMeOZ1r5Pnu+UnDD3cPDyP8XPtPd9ILHN5eMFaV8ZJjJOpQ=
*/