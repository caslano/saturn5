///////////////////////////////////////////////////////////////////////////////
/// \file push_front.hpp
/// Proto callables Fusion push_front
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_FRONT_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_FRONT_HPP_EAN_11_27_2010

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/push_front.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_front() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_front() algorithm on its argument.
    struct push_front
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq, typename T>
        struct result<This(Seq, T)>
          : fusion::result_of::push_front<
                typename boost::add_const<typename boost::remove_reference<Seq>::type>::type
              , typename boost::remove_const<typename boost::remove_reference<T>::type>::type
            >
        {};

        template<typename Seq, typename T>
        typename fusion::result_of::push_front<Seq const, T>::type
        operator ()(Seq const &seq, T const &t) const
        {
            return fusion::push_front(seq, t);
        }
    };
}}}

#endif

/* push_front.hpp
bYGZM7s3+9I/laVr6wI80+kMmdq6Ocb9PZXlaOu+++l2jLJ8bV15i2dvKM+0dX3cZ+1UVgqz5LPDJoLMyNNw3e7rIQXUW2F8ncO48jqU89o638bXJ9Hs19Z9E9ivkHJCW9fpw5QFygJhvFbcJx+hnhykrSvY+GymslDNOvQZS/ceodn1zIALyqJgvFZObG/oQfkCM2FWx3clnSEeZs6s6PmrdJrTmsV8PtGa5rRmr3ddPk5zGlaD2a4th7Opt8KceDwdXq2hnIBZMfshs1UyzVuYDbNuse1eUx/U1jUPfUz906Kl4bozBy+upbmp2abe1wKU+cDqMbuy8+HXdH/auuk/zjtNNQ1z4Xu5Xu5CcwzWlFnt1hXdKGawtswG+R1LpnqA1We2zn35cjo7rAGz5f8cGaXMvpVhDpqfSe1JPbKV9rku58ECiou2LnlfEvUXj1Zafl50v0b9E1aDx3rhMXtlvrDqfFY1OvKNMn8YP4NV9JB8ZWGwxsy2jp64geIJ4/fee1+VVOp12jqH8C5TqWfBeG9tN/+rhzTDYXWYfT5lxJfKCjXr4TN3E804GP/OtWWv9w2KS2t8Z+bfLeZf20Png/F8WTC830uqW1htfr6r222VJcLceY/s/IhinQHzYFbpedmPcgnWkNngigF3qX964fdRmE2Y2++KMi8Yz5eJ+U16U63ALJkdrJhCsz8Qxu8htf/gETTjYDznX3Yc3ZLmEcyEmXHJEE+qFe19Z76qF6ssC9aIWaNeK/6lrFg7n82WL0Yrs2lj+MymfR90opyH8ZiN9D48lmY/jJ/hlxFHfJTFaM/8oHcp5UsijN/72NEmXjRvYRY8ZoezKdZZ2vuKemdTPMu1913YYOegzLStYVwGjzywmGYcrAMznwM+dH/hMP7MtBeTayqL1p75+Fg3mpvrYXWZjZ9jVoXuD+bM7M26b1Op/mA8LlN6535Es1/bi7/nyn2Uu+0Mn7lo37cuNN9hZsxWOZ3fQWeHGTPbvvNGMOU8rDqzVvOMZ1LOw6oxM4/MMKdeB+vCLH7YgbYUMxiv6a/rPJxDs1jby9S2n9PsT4DV5M/8dfVE6nXa+V5dT1pAdQSrwcx0ZbIx3YO27nevC47UQ7R1UzeOr6Ac1NYZbQupS/cH4zPuVpXHTyg/Yfz+3s68uJPy09uwZx0ctK0l3QOMr7P7vqUNzQ5tXUg7nwRlkTC+F/tBHanPJ2nPrL3V85/KUmG8TzSoO5VyvgBmxSzul1vhlJ/aM29/dqkD5Wd7w7wemN/4EeUnjNfR2fqWzel8sDrMKja0OKQsGObObFrtctpnDIzv8/tdTZdS74Hxfta2aOpI6j0wc2Y7Q81/pLkJ47m772g3D7p37X2LB6y2pJkDs2f2/EGb35RVwOrz8/0+1o56cgdDK7psnk05AeP5Oc5jrDXVJsyUzeLY3CvUd/00yw8YeZh6uWbu/2w5T1lQB9WTg/626oevdqcZDlPxNIMZjdrWj2Y4rCYzi0ftKK8TYJbMVvTqXE1ZCsyO2dBOo/pSbcKsmG24aH+S7kFbN2py7Zs0/2CmzMIf5DZUVtaB/s4IDDPnQv4kinVH5CdbV3AnMJpyEMbP1+ZQu5EUF5gzszuNZ3ejuMBsmX33MDeU+hmsDrPqF++QpcKsmdUM825P+cneZwp763WK7rYQ5s5sdNcnp5UZ++DnOcw6NKiyjGoTZsys08gLtM4N5sjsj1OWtynPYCbMFidULKc8g3lyi5hKn7OitHXm3vG+VNOwhvx8m6zu0LyF1WLWeHKL8RQzWDVmCevuHKQZAGvNzLrh2W8pZjAzZl8vm0LvK4E1Zlb42UTKJfNOhut86z+4rsweVps=
*/