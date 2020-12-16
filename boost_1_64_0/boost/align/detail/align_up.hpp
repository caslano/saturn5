/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_UP_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_UP_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align_up(void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return reinterpret_cast<void*>(~(alignment - 1) &
        (reinterpret_cast<std::size_t>(ptr) + alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_up.hpp
U/gsrh54nAnY6aoYjJr2tDD3j4QREdoa94e1ogCbpxVg618OWDmS1m3XO1z+Nx5xCeP8GwcvxymG/NqN2SRiJS/Cmdd9NPvC8DDl1nFpVFnfxRLoLTWq8U9z+U7q2LNEYwN+11J3NohCYiniUdZVyUkbq8rzL5Ibaf4HI2Le130sBP8j6fRI9u6NJzAnM+0fOb/c/C+qSOHbnLe+aS14YnupMSHK71zU/PKJIcpPb177cv5Zo+1LXggcX8Z/Vtcs/2OCzg9KeZcfjgD4IiPbHtco7+uMA8RqjaNJ/+unfLIh1wCDvbRt4YHxFDf7LiWYjY0qk8SYkpK4+Y4YOna7SyuRDhllteqNveMnuWMK8f7JagF9G4S9EI6xuiaODBFVyguirRG97Zn/YO9KwKOqrnBWGAJhAgQIixIQMCJKJChJgzIDE5hAkCCCEVRSqRoVlOIMgkJYhgjjcxAFrF0Qq1ap0mq1tYBbQoQAguAKuC9VXxwQ1BLixvQ/59z35mXygKDYPd/38ubdfTn33nPP+pgoj51DymPdSRaNvRosQBkwVlBOq/Uy3ox9tDmX0PdP40z1MS8tld5VhupmGkVfydFpFH0aRTevohq6ilbadSLAMz7MX9M5qV92+KqbWsStp3vjupbUgax1wvyNW7P3B1tHP+L+t824H2cxdHz5SJRe1P6sFs44LQEj0hb87/zNvtbakCRoyyRhL/sc8k/ig/Lo5Y9D+Y31dzJFtrKBvrwIiGluYKAJ8J2N3yF3dmEQFdjTn9T9/4WG7a+tibn/x8SPWB8j/xoT3yYmfkVMfOZ70fFJbuOI8V+YZth/kFxiXYI4xSd93NwZR1LyvQP5cb7uLM/Ujtmv2O31v6wT4xkdCENBAv+HQiZWmguURtupt0bX2Eq1fucyk2L9eiA3zf8SMxC1MQB/Mk/3GAC6SNmqI1pszhaPFqd3fpPNaXxvdQh1/9165Pl8abWN/sPWhvozl2Ip2NNH1f3XTJ/G6S/ZEqXXpP62Gcb76PvVR1sUf1FnFs/neueV5vl7LpbYZTfK+duNz99y4/x95i9ilebSN49iPsiVRnaQbyQMsDezdhixhiUi/c9LhDhIPqkx4mkGQ3fNpngWY7ptl6l90GEjH5d3UvDad+WErVBxh56Q43x6JMLSUB0gtaLMyXzzhkRdRFFade3FJ1yGQ93/N/P41bhbUedEhPkVy7QelV7sOio9OyTrN3a9l5jrHQTvhuu9uDF8JG826HHz6LM1cGFts0jyA1uyOf9qVPoWnCgVn01sr0ut5WU1lrVsyEmSPAmzcS52efPf8J0Ehw+6Z425KlOxZF36tw8S2jbJhSwVbzLbx7missmrz6i/3dHrzzXrf/6RBvXn6rOl/tzvV7/a/zY1Xu+BKlnLWe/Z0L9s0xfLWn7ARv/JNr3Dm7/VJzP2zcomaqwo/G+jXXlewd+x3OzlqR+VXIa5M39qA5loEDEwwC30xF/sjYSGx3trEuNi1KwDuGmk6h88b6DpvucgMKPtsuhcj0VcU8a710aDfpwdH6Ufr1b045rt359+3ED/9XkFU50AVgRAXQiAAsJzUeLvTn3QA9Sfbk0EHzX/UjLI7TjdhORO7Jsjpj/bkv69Tzg9oVXHkn+vNkSNQakChiV69PopII7WVSf52xxaVElThLQMOv7ktYkNZ6wJ+G/U9u4dRm2/ykJpbo1s8HswbkTl+jUSEH8oJ8L6BNoh/a2lzIoeQKFAe4eyQO1m/WfEksyv8U06d0kiWtTMVbcxzX8BJYKw8eqlLGa1DVBDxRTqv5BC+jMY6ZFXpIxMVUYPaxntkSZSo19BRdTPfpH9hYZzxZrhWUjh8PXm4WE=
*/