/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace detail
    {
        template <typename Stack1, typename Stack2>
        struct segmented_equal_to
          : mpl::and_<
                segmented_equal_to<
                    typename Stack1::cdr_type,
                    typename Stack2::cdr_type
                >
              , result_of::equal_to<
                    typename Stack1::car_type::begin_type,
                    typename Stack2::car_type::begin_type
                >
            >
        {};

        template <>
        struct segmented_equal_to<fusion::nil_, fusion::nil_>
          : mpl::true_
        {};
    }
}}

#endif

/* segmented_equal_to.hpp
Yjm8+BZ5hpAB382Jj6fPQW6cOYQc723y4QbiFDzxtmAnE7viF1gTvYkn8J/0tz1fE1M3WuR7yOFXxBTOnFI7iQ/9kNlaez1kA0zYvbNPuP4E+c8Y9vFpD/J1cKAv/VkRZ01D6aFSi9s9wPfINdNF+ANqjQru4fsTgrOGGHmk2MJadpx4mBj63Wh6ikX4H/J4H7lvJ/zFS8i+J/5lKLb3W/aAnL3wOPU5OWAD58PgZQZgN6Xkl/SlE5zTZbqTyzyNXW4nV17KvU3Ek98ih2/ZOzpvraZ2OQGdxG+lG+DlPVxPwO8jLeygBB8wnve/4Ov3IPOeg+mfDyFPpqZYiGxPHI+/GcD+0I97LWIcvYA+2ODR+JILyNF4vtrbiN96Bn09h1x3tYczHnKce1gPX5VcQl7Ug/g8EblciI4uhp670c3z2X81vI1hA1vJF/DLYuYY+I9POYT5TkYWFxcTE/Edd3GmdBUyJ3aLRegP18QT+APoC13ej945v+i25y7mHcd+rhyJD7Xov+KHypFr3RhwuH8udE1H/w8ayznrYGINOdLz5BcHsy/2Yh2GzW7CFx1l99DZmx/bnwTOo+gzZzwhZJXEd0Shz7qrF7k49zJvaCQ59P6sg6366PdXcc3LM6UpcNMh4i73VdFPS5+NPrwIP5gvcyF8iMATzgO9rxEvwUnan48cQR5EXH8c2R81Ar/EnvuSQ5cXU0eh+8RcK4Hc30efbiyhJoY2YnlqIPnWBfAgxZnO+9jBmdTkB1jk3+DfwnqcF3qJ3V58TNVHxMKl9Aqwad/V2M88bKK2L3ZGblfhwafDI/yXZyd20kQ/+mn8HXOEvsKf4efFfQPpn0FrC/qDP0vHoYe6TJCvJ6eia/ZnfGaI735YKfzc7+DjlB7Qh47i+2Npcs4nyWk798X/wo9rsInh+L17BxA/uHc4vvRRfM6pxM5r+XwN+dud6Plx6NEA9GUUdnIhcYv1Lb6H4X0P2nfBjxPRuTj+kHgSrcQW2FvCM5BYRv7L31ELm8H2Lf72k/d7GNP3oF88QxQrYc+fYHM8H5Ca3IszDdYdisyeh35sSLSim/QQM3+mVqNOqEpgs9TA/l/hk/lORXINsr2MPS3F/qEj+Sn8O3YI70PAL87AfkfTS7Hlkca2hrE/6mX/DcjkJvwIcc17A75oI3nbF+jBP8j52U8c3gnbdhLQtQKdoz8WPRWd2liCXpLH0oNKUrvEVmGTrJvqij7Y3zP+BTy4nroNnUsuLKHfy31Hsf+rBiBj4h96k4b2ULqY/Iaex8H4ipd7U+OgF/g4Ucte2UPqNeou+u6pOYzQ4+0Lr7ApzwT08Vx6RPQfBGcTmQnE2Unka+cPJd+Bl8QIfynzP9mX2EN8/4y4MB3dIuYl7Pyw2OJ5bnz9SGpArkXjQ3hutQj/jO1UsZe/9KWGIb95Et18DB5dDi3UgR78cYJr8cfRYdsO1pHj+fCzz4DzAPH8cvZaX0KZSR5xP7iv8fv3QdBHXnkOunUjOfEVyD+F/+qFvP4I/v5j0OFB8NIitx2FfPGtX/DcSZJc/FvW4T3SsRS90+3IYoZFDww8W9/6wItdyPtsD3ZBnSbIP+mHib196I0h50QJ8Y0exunoOLmB4Fw5eQSyPRX7uI9c5TeD4DH3doH30OEfi911IQbQf8s0IvOP0JsIcWsQvJ3JfdQi4hRiNmvEjsBmuoODX7d+R6xcxz7gQYiY7Lf/Lcf7RrEWPOCdF6mz8X3fwbMV9Bt34aeeYx9vIgf8l2fNONbDd349Evsm7vF8gv8ReLYcvT+0J/eMp1ffiWdnsQdk6tuB3YaR0TJyduiI/wWf9Bm8e2gA+k0ORjxKbcQuNrA=
*/