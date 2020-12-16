/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_BASE_05042005_1008)
#define FUSION_ITERATOR_BASE_05042005_1008

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_root {};

    template <typename Iterator>
    struct iterator_base : iterator_root
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Iterator const&
        cast() const BOOST_NOEXCEPT
        {
            return static_cast<Iterator const&>(*this);
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Iterator&
        cast() BOOST_NOEXCEPT
        {
            return static_cast<Iterator&>(*this);
        }
    };
}}

#endif

/* iterator_base.hpp
D+Plt+8uBOMJHNr5ebjJ43j7SB+HxcI56J8Us6eg4Z3NXQm+EzKkz96N0DHDB3b8lN4XLsSN7k5wVLCoP1KKI22P/kgJBoXKSWfqngSDQkX0/ntgluAumMxF9yI4oq1xcW/wca4c4pi8x70n4PZot9mjE7FeP1yajPPyPnIfH0fl0mLfPhFLimnzv6+HJfJ5vMv/fj5usozavny/z4Nyim9c7u9hMHOM2+ljPHlFP+APoFg6GdK6P+yBk7B+H33Mx7myi7jHP8jHofw6ZfyqjyMy7NohqQdr7Kj1DLBN7eP/8B/Orhs4s50K7yPnHJacc9pd1mDPAKt8lSXwAksYwNgGG7xrY3vB5JzTknOGGQoKCpihoGAYCgoKZqCgoKCgoKCgoKCgQPr/e8/VudcmDTzD+3WOPh3pKFzpBFy2vTmxYXrHU1D5YeEdczA/B+cZMY4pzezCLrP8446KB+SLD/dGi4PmW+FnmDd4HlgSEvHGm9dP5f11yxuJYTYFKTzivVryPbXMkC+15eWeJE8Z6/h/ndN4v1gktd8898H210YnE6NVY1vMIhdK25TL8L7S8l6OSlq38Ph4DjAvWWrcH/qMc+cSX881yvNLDJc+8YWPmx9+X9igiMVvrxp+S1EWdVj8dg3oXuSNKONbfuPDby+SL0lOiv5JfYH3fMAzsfOlmvW8+P1FLd76VXr1xeuL+regrkJpRNUvOPf/YGFHV3vu1Tf2b2yiWB4fuK2UV1s0XA76d/52y/LDVxcrkfL52fL+CsoWvBubN4/3X/e6sfzk9qi8aMXuVsuv7wDlS+zF++BYfu6OUI7a9thBNlxebFzeXBx4ixN5g/GjO1WakR/84Qb57ozLe980KD9elB+V/kNthBgI97lLKa9vupRzub7+aiHX+YtMvmpSRDFePnE23Sy/3K8v4ZzCIWdmtPmf50jVl1e2elHNmvrfXzL+/sJW7+Sod10s2vUiufzdAv3SvGqgf+PwO6PrhlcQbGv4/dsWpeWmenezjxE05ii4HZQfbr/pZolE2lM0Y/z4O1SaKlFvjLG1vbf9+rJlbDW+olOa3a2jdgx37ojL+0ScUH71TlBe4rFCnuDRNuDOp5UXT7qmnQ+4C9Bc3zje3OkxqsKPuTHvCjRFXowF+QzvVmiqnkwmfx++Auh+fwZdr0wwf19z90IHNgc1Y8JY9htUhuPwrN6jLSvg0J/ld1Q2j+Hz9HtC+SwP+I+gbB5349ZE7xUXWWj+X9vVtHq/0+p9iuuy//017e/sZSUhHNbX793WrKLLoYSzwTtum5Yf1cB8b+191oCO3O4Mukk8it/2dDA/SlCKadzAa7c/jabcrh7f7HW8P6fdAdMtFKv1d74jlO9uLQKH4PzTv7gTlJe7uaKePc1WI9flOxcaPF93j5YajGx6fjSn6+vc3L9543iM23GXOd2IPfbTj1u6o4Ny6bfdh9EpNIOe37XQVL1qNt5ebYHm96fR9PPlqTD/gAbPK7AGGufgr86g7VUe5ku+e6U7O17Wj6B8Hqfm/D2gbDaXvgxlMJdGm7JnovtKr7k2KVtydHNzc/vo6HU3J7ExTlp6xgg3KQmxiNO997r9w+vbW/0QTXJh3mr5EjEh0OwVI4so6eWpeHxKGXNhfrvlWZWZ0ZCEIseHb93baOORwPtiSx+I4Z2ninJSNK82avdwe2vG84uWJxIVNTOqU31+uBLs+m3ABHFXftvyXBbC0mqkQ16/v781yzV44ZXnWnsWo2jHQgeRtbHtz7Pwm2p0jlUThE3Ky1X44X55B9qe3qd/pOVhkkTLTOpUc7jnY/b9KytGXHk2WLOyoZ8ndWiRqVehqUNvHO1cWaEQ/Xs=
*/