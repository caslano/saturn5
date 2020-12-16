/*!
@file
Forward declares `boost::hana::product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PRODUCT_HPP
#define BOOST_HANA_FWD_PRODUCT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Compute the product of the numbers of a structure.
    //! @ingroup group-Foldable
    //!
    //! More generally, `product` will take any foldable structure containing
    //! objects forming a Ring and reduce them using the Ring's binary
    //! operation. The initial state for folding is the identity of the
    //! Ring's operation. It is sometimes necessary to specify the Ring to
    //! use; this is possible by using `product<R>`. If no Ring is specified,
    //! the structure will use the Ring formed by the elements it contains
    //! (if it knows it), or `integral_constant_tag<int>` otherwise.
    //! Hence,
    //! @code
    //!     product<R>(xs) = fold_left(xs, one<R or inferred Ring>(), mult)
    //!     product<> = product<integral_constant_tag<int>>
    //! @endcode
    //!
    //! For numbers, this will just compute the product of the numbers in the
    //! `xs` structure.
    //!
    //! @note
    //! The elements of the structure are not actually required to be in the
    //! same Ring, but it must be possible to perform `mult` on any two
    //! adjacent elements of the structure, which requires each pair of
    //! adjacent element to at least have a common Ring embedding. The
    //! meaning of "adjacent" as used here is that two elements of the
    //! structure `x` and `y` are adjacent if and only if they are adjacent
    //! in the linearization of that structure, as documented by the Iterable
    //! concept.
    //!
    //! @note
    //! See the documentation for `sum` to understand why the Ring must
    //! sometimes be specified explicitly.
    //!
    //!
    //! Example
    //! -------
    //! @include example/product.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto product = see documentation;
#else
    template <typename T, typename = void>
    struct product_impl : product_impl<T, when<true>> { };

    template <typename R>
    struct product_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    template <typename R = integral_constant_tag<int>>
    constexpr product_t<R> product{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PRODUCT_HPP

/* product.hpp
FjtJEdkBo5dpQNzix9DZf3SqeY3F7LRCSHFaeJnthJdhdtoZXtv9RQbqTtF/VinRD62whqCOW5MqZheq1SJ5HvdThoesAX2zV8ydwQWYvTkTQNnGauvRW+RUeMi5CI7Tg1bRk4KlHPSIjucSxPx5Z+4SWeHLhSEn28emjddInLMh6NL+0DkVmOeC8ELbjVcqdh+WDTx1Bf7s05Yl79OPQ1OU01JdhtOvJgMGOXKmo+XKeo9YMoc7BlgBVKO/bcH7pNyAd44Ob3Ar8AbOMa4ShErjwJ62vrcBPqMFKclhc0yZ2PsFbQZJuMO++dBtM8Moq2YViD1MTdXQHb+HZ6vBnV1bi8HZ0Hm0NdB7/XbcQ51qHj3JHOgc3JoU3JK0fnvgvcItkRT4Ad9mJvGVN9r9su/3sctpMojgUjuqtW4Mm/b2YgbDZqKP9sydxfWaO0uvYAzArHlnfT+d8cEwGr8GZ9e9tL0ZqbCe1ynVLh6/RF5dY1x5qzVsq+QlfvQUJfEjNog9ijKm+jLE8okx5xtLaOzC0w0Lbc9pDSpl+JvmSnHJRF2JA6U5IUinTdint2XQTjGrwWlhuccaK0+e/B5KLt1T26WAaE/ij/hDT4bCqv8QCj2C/Q97gNXnzvO87tlJBHJGnAL94u1PwJ1cWkkdPHjaR3fBgL+IAXeZR0/HgGO0g3VJ619MHPDpoWnkmHgk36DwF+j79Q1dRtsDfTj3dPNolzlgQ1YAoNx8KNxnyzzknwtMLplq8Wew93id0TlT2awx3uy0/FzM+uiFoSNi8BAe5Lq9SYUni3sbZ6A348O7KxLDA89LDDsuSAwHMxPD8y9ODC+6PDH82wGJ4c7jEsP/6JYYfnpyYviOFvV755wW67/zZHuDKywm+NFng4tX90jcQrE+ZPAmC041qtlt1vVWCAxGVOiHLcFPzCsqPIj5O6M5mx0zSPY1ucC8P8VioBtOMY/GcHF8LtNxQFn5l7mVIg1t0x4zMhSKgZS+VkW4RVdOnzWv/UcSHt9MbdttPBMPlMVm4lByC+CBQlX0BUmAMn2zOJ1HPMwsZQbh3unZf7W/MMORUWZqH3tDqWUvappwb6Ct9GP09LeeKr1ar/p6xG1dsAKu0mtp5VradZJElT1N/VxiWpdWXB94tWOAx3uYzSWxo7yLxbeBt4OjNpPpIpqngSxWnpNducS3wtdZHDnPMBKq3WV8S+Jvb8a+eZReS6YoMEm9lqpiXa+lHWZEpb/ST8Yk+CtFo1yEmK5KhAoKDyA824PXYjBX5VYvhG2ZdKkIMaXieQu1ipYsNKsv0FHVNM23EjU9X9a0UUtC/GPqo0bLkOg1XhmzI1BFLPZ/3Mhfxvk/K5D5c5EfGv29FBubxg6oIy9JJYUfDFCG9PIZyl8NKNcxlAd1KO/Kq/X2Qukdgg72azsY95jLLfi6zJJ8WIsiHXuH2JpqEl3RnaGtW7+DSBaxhV3mDdZSrLfNec+Edgf44vdQC51IomOyweV123BpanRdcyd/yrrmjoGUSdg9HcB9ClvJM4F0PhKkdBFrFMKCrZYCrlDyEXUxIhg1r8onZUS35eLkXWS2yjI+298b0Ws6wmZVlIKB9GkMpzGQzOLOqoXJXPPCqMeNkSgWF6bSyYqYZpUHxHbcuEGZuRsqTbZNzzVZJlltVRciy7qjs2xVQUAKTzRDbJHNySvdoePi2TS8HgSIDCvLijdY1zXP8Z87f+P67bb1S5LJcJptvQ9P4MkRcadK/TZeUBynDrxUGQbKoAddPgzdISt/4n5O5lEoQmVpxz07V79/hyrmU2vuTOLab+nfIn4t4uEdOnFoXzhXOXx2hICXISAiXHunga59Q6VkPZ4=
*/