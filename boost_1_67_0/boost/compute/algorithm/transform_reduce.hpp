//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Transforms each value in the range [\p first, \p last) with the unary
/// \p transform_function and then reduces each transformed value with
/// \p reduce_function.
///
/// For example, to calculate the sum of the absolute values of a vector
/// of integers:
///
/// \snippet test/test_transform_reduce.cpp sum_abs_int
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see reduce(), inner_product()
template<class InputIterator,
         class OutputIterator,
         class UnaryTransformFunction,
         class BinaryReduceFunction>
inline void transform_reduce(InputIterator first,
                             InputIterator last,
                             OutputIterator result,
                             UnaryTransformFunction transform_function,
                             BinaryReduceFunction reduce_function,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    ::boost::compute::reduce(
        ::boost::compute::make_transform_iterator(first, transform_function),
        ::boost::compute::make_transform_iterator(last, transform_function),
        result,
        reduce_function,
        queue
    );
}

/// \overload
template<class InputIterator1,
         class InputIterator2,
         class OutputIterator,
         class BinaryTransformFunction,
         class BinaryReduceFunction>
inline void transform_reduce(InputIterator1 first1,
                             InputIterator1 last1,
                             InputIterator2 first2,
                             OutputIterator result,
                             BinaryTransformFunction transform_function,
                             BinaryReduceFunction reduce_function,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<InputIterator1>::difference_type difference_type;

    difference_type n = std::distance(first1, last1);

    ::boost::compute::transform_reduce(
        ::boost::compute::make_zip_iterator(
            boost::make_tuple(first1, first2)
        ),
        ::boost::compute::make_zip_iterator(
            boost::make_tuple(last1, first2 + n)
        ),
        result,
        detail::unpack(transform_function),
        reduce_function,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_TRANSFORM_REDUCE_HPP

/* transform_reduce.hpp
8WhF229fld2zuc1k7F5Pa0Smzmr6CYGlmK2+FvY6nRmU82vU23dwlObIEedU3CdGyXjcssW215ECQz13AddvjrZvH9tfd+9Yf/oUloUW5nu1Avg4wSzp9dSVJh6lmvorubm3wtyrlI32+VbWkp6CHULX7nrekQ5nmRQSs3U7s9yPNJDQZKJEuHSOUdW8NPzIruYeMq7jrcTdqNivtzDbLes68x3l20PqhT/A4mDvjiWtans3cG6MJSSdMAKLPsa1ovUrX//TJSS+TQxUKCdXPsMTl860B18SjQ6yJ3Qw2UEdqeaFjtGtY7jov9oLekx8ffxhTsout5JnhcaNKHlLi1x5snbFbK4UiWwhw0I4HfRW+1wQhCpaPrE3VosM01Pmg/dL51/rQGYRmX/Kg4EilE4h7JiDycalQIfX8bjUWI68Vifgdx+98/t4P9nMPNnkVq/Ej7HfgSNC7q8VBVsHu35UR5mOUwEg4Te7yX3OukDzNBR1YppHWF3to7xaWVbTZ+bsFAWln+Ppaecs/Kw9Sq9+AxKwaVdjkhLA1zn2NRWTeiegbM7fBmF5jPtcN6dli0+eyznjsRM2mw4kY8FTUv/0/aiqMLjQqhQ5RQCr37ihpD0QgSC/mZjMdivAmDEGW/XVjy/6nZqf+Pe51RbHqW6c/jx5rww+Fi7Z7+Ebq4RmOsKhwriwxDLpvOFWPkd3X/5AdpC0JlSnGuZwAjiRehS/yRA5RV+rR48HZm56v0RczH31bj0ztxmWVO8Fb3PLM2z7jXspZ7Qh6VEDCxYVT8M6iELgXFtCpXcDAPhWzYAfye9TutCqbCP7nPIcRT8b894zQA3vbT4g1djiiOr6ODLhSaSnbuESAImAkrXzJUv+Ptx9EUwIDJX7qUznSsCHn3deRT7JiVsmCMjJfSP2Yq5a+nc1DlO2B2R0Apn/sgqIqTVeK4iRsWNWIAWBUACYCBRn+RVYoD6wZ+NOlm9W9jA2RqN4s07mYIP/EnuG1Q92EwFY4NgKR1KWEUUirLPGbqnINoVnoeVBHGnq7F4tKtV+mydC7/2wmMyw47t8pdrhZmrMhADlWvVk/7pj2dV3FfiJykwf798Ryxn+NRF7N+D8f1do17XPzobcP9ne1fM4zpZzyOw4QI0JlZIJ/D5u8P619quw8JeHOz6+eeD81pjkWy14wfITHbt5Nq1b5MW3MbhPouqudXpQ3fKpNqSX+R11zQs7DOQWHI1157Ox3GQ5vQ6cwapAj5NhktJ+IyM7ciWvZiNXmC/7C0n1vP39HvgOqi56jVyLH7sXCzWFRJ0uhL8VQk61cPEdYcTLZzYZTs9CaDPh0QvFoLB38mAGiLJPFkvVSx/6TL7ngEO15JogoGTNFHiRJ19ZiUqV8eeKZddj+7zfMmXkuZOnweaQaAKFSykjyIRua2imCkDfWO64k9WEMXX0IjhLi49Nf30PTTQpsDldkewak3F3LX0cZ5IU/mCy+tCbtyvJRndxY5Ea3pM4YhZLjx08GyVT0PzlLi9ZBLc9Rasdgeb3kk31ilXHSGRpYX5MMnw24MMjGsIb17xLH3utp53Of5+xWEpkYsleFPPLDZiYehX4St+cb5951G3MOhAC/VwAE2cjcYDEBDVFPgaTD+B2krM67LFiBa7nB9erJbVyKb5p8nzxEflyNzD5yeK9JW3vkL2+IrWi+yY9mdmnuqy3EZJxQx30CppOmBkkIXBjuw0cnWODD0/1JTVvKnN6+VUWofAd9hgiamoTTaSLe1YytavtlvBwrifL7N0L/+X20LlRRpnTkHS1syRgFY9l1JRxI0G5MhLGRSbUwTuD/PTkcPcoMMGMpdbIIjGUrBrJmHj1NVo6ryrVs8PGg7a8wilj4VHzwv3f6gYnLZ8ih0QaVPLqXxtZQG6nvRLPGE59b8lzeJJPA2ujrE9VuMVEI07mZ1EjUa6W5fRNXD0zcPUlRU5uRO683NCBiIirzecIUw77/V0V27kNarW8Xl4K6pgsqHMMd8RtubkOejabhLW7+tlq+qZuZxn5Np6pz93wgFUu2WVFvDy9gttHjNmKbzSv3qlzIA5Ai/gqQFATmJHRBjHrPo6HrHdE4WK0KXOSkoxyctsh8ZuvH34KMNqQHTT4rgqNMpdFVQbFJJz+wJB3visn8EuPdMblXNCzgPcn8agTHW2hjkq7+kkPHH0DYST0ZYH3FXOedq4yS1TstVYjn3TlePE0GuituNiM8ZSoLBY7OAjbrLmJfZ56A6w46ORbZwT/uO2goPXJNQTXXLR1HOEd2HbIm2jyKeQqCz1UHi4lpcpVqtbB/rbKbjP03XOvKLNT6ZcTp9byP3jiqpu6h/LqHHaQlt9IyCPcR+U2pUpeTh7TgaWNLc985x1MI9z5b0iQ6vE+0T8g8whE8HSNiQm3cN2chRiu7ZYuIuuM1Dp1YOG+ub/unXAAdnm1eYrwLWpr03vu+WTOkEBD+ByVyA5YOk6zP+2Ue+PlK3JECser/ZMgmqDgFjJ6M3qrp1K5X1er5R6B2x5JdHGkW7GmvEzj2+PpKgkJ/VKMmoCXQ1BXXv48ng0z6SoJY1dRKRD2liB054WbEvectO1NLU10M1n+MJidXFwqDsGNhMZRV90MSFEsUb5f1+K7bgNoi02BuvWrNWaGEj2U4UZgfsEZePzYprTONYLeybK8dtg8Wg0zg6P6nbgyp8kDfKyC8LWHmTcaca8BlriVEWm/9+t73vWMgA/ju5irwCYhqzn9xtNbp2pUOGjouaMjpSonWjTjRhsD9WNX+ALloYNVv5PHuYlJBYImXeVegCuBpXex6EwEWipYvxT3dA9lkwlhDTDA+sZCNXqWqiq3NUmWBkzYnEBwE8GHJ/pdSYWdLLbrP6htXy6os4tQki7u3mKwEojJd3eigsIFhMeaKnKvzUTFZhKUImqks11Cd/LEwj+MQ2I83zQtuFa1spGK9rT388OeQnDV5FYtjoSTsnjInAVG03JyBSs0Tc1R+nGHOHSBG9v35X+U/CEjndwPX1OSpINmUIfIM8ik2+JT0lrXkHfcRo3l4mD/hKx+17W5YyK4cJ+YCCss4MOtNuw51Ue3mJhDFMmus/PdqUpV8eaiV2Z8q+CkW9TXxovymZyedID+UNvBqXAKWT+t/KRJWhorGDlpC8inpplCH15du92Rz4Ei29ljm/h54GkC+/BUNB6qNVr4Idc9Ltm+Hh/XIX6ZctMcnskqwDhJa3e1YENPv3oLCQQwkr52Sxx/ygJnXPPZZyS/ITFGcT1qJrHP3VI3tkUjhL7wsEkVcyZNXUd7kQMi0yyLMi39VjsdyMvk/m3rVK0pmh7WimqfuDv230aZQiRC2ig7Ojg+rvA57AUBxuVXyEJv2e1KSXiN6PCNMuG13u9WYSnYrYNk0IjP6zhGfO5PWN2Pq+mt3GZaO+Etqi6eMiUgsDSDUsy56wh7R+URaOPwcoEpMa/+i9EShd2aCCMM0PqmYUqd0SyWJ8kix8whPj/CYOl3dZokQvHNFplSOWRtYkmS8+zecYGVRrcD+LeATIboaXOQxCTNzfpE3Tjr77Y/iVLmMPKfkcut4P0INo4M8Vz0PLt9vnI0B+I7T2I82vQzxSaaCAKE8xqaO2PlhgnHf4wIjdAr3VZUX1rupM1mk7IDzDI3F9gJcPYZCK3q28edVq4NA7OvfJttFb25QFdDzK4o8boZrZQvxeXz9hQR+Rm7n6aQd8kPXys1vB1w1op5wLc6VdKLgyVLYFvnqdznnSCzcOt4vXIZb6MYgnzOCDNrbmHVGhmrVxpkn8HyfB7LG9VSrtPY00MqFpg7HzVPRqdt5Lm6Wud4Zr6CR2VIavVEOnkmR2HTNQjWebtjUJGjh/2t3LCflgebjoSIPT5ZROUn0RdppDfOzbO1z/gNQw/r3i/pmo5K21Oq0xnMnXC2zSM81n3yo1asb7kM+BHOr8Ei2V8theZvxjKHmNMrIDRPaCS+Z7E5zdJ/ePw1aDbhaXmLLaRlT5dP6SrjN7b4BBtdN2r4Hkud4SNv20eZwvH3A/ElqXtyb13j6DcJylrovMMIAlbOaknIVTz0sJ2NjzXedoJEtn6Vvb+++/C7isNp/+q8vWD4mFrFGSOUEhB4Hi/ZqtIrPtTcmwR7683DtparlT+mptvK0zp23J+YxcpXv1klGBGyMCLDLGHnJnMubcgHfDa/4kOXl6bHRKeGzPaw88B3ErT1Rc+vJF+tJG6FcqqdIGAgH/9zCK7jceUTCw5727LQXLlH3bbLGSvdYQDi8CvMc50su71atZSey5PLGp3Fsvc0dm7uSus2SCkmaJaqB5c6W0vfg6PrFwG/28y3DvJwAjKVI7KAxPX7YXNRzzODVyPIwz0STboIJBfHPfiDhq84lPdorPF+Ke6oLxjgnXL1d2ArsgNktUiSKOcZ8Fq9AqePocePHbJcvMO5Uy6G2tQVPubNCWk2dEyzt0zUQTZ2Ljh4k3ZYq7MURA3k0fhTVkREmZLrDdv+5O438bHWHHzgK+8WsV4vFAlODdGNO8cxYjh1qyXmemxqLAX2I9UBQLTQLHEsCMpdhmx4McKSGOewiFLvpOeWwjOZeeD0RNeIZPQzEE5dSw9o2jpXwL8xT8+Conm/VNxPd236tBgJjCwab4LXIZSfegTxHRQVXzaDx2Zhi08P5tyfVQzghWfmCoakf653waAPdN+7F1ftl0U8MnF8y6Gc1JzeqrDhnf+wqcCXztF89jOIwfEPm5KaE2jvq5QZ1zu1kIG+PU4A82UnVlnnZvIuC3Su4GAVYMxC2jsXbkiKjRvnWGEy1CoXeSf4T8XwkVSzXyCZTjft5jefICnf+IGEW331DrtD8IxrMv02ekFHJqXVGRhjfJoiqWLY9bSxW1eKHARilc3fWP66ZuQD6zQm+b17TOd+SvfbjbyV+WuOrtfLLgoBLHAfzukMUVOYSRtUsXzilWKJvftr+mDIiykmaMC3PFIWkqQEfwF0fM9dKNWF7JAXTrml0CR9zU8zW9slvylEcyin1v3rk8oW09SJzTv9V7Fq2+C5LqryblYX/sbO2Qm23cA7+exeV6WxmcGOT9dJjM3fwDpjsrDrvSzUe+xBIHAR+m8BcKVVuXAZXuTJEFaVeXjA7tR1mmJfbNjQ30Vne411R2XUX80+JEK1bD6faXSVFAyX1SJUwf72n6RqPYLoJcFMiu8IlZJj2emyZ2poLZPSV3HqN6718Gx5psGtaXt4MqIli7z9jK59Y7N6sjgEgBt4+4hW+Ezr5+NgE2lVuXdf5ndIxKf75bRobbgpkVsntKneUvXuRJKc6veLtg2XnOxr2kKXxHr6PGwI26jCxz69OA03sqCHNoVaNTYBACm5pF6q4FVcs0WyvKV///b93hZKwLMsaYvhwiNNF8giIgBoAO67Cqfndj6CxfrCmGl7bgUW9K197CMIKBPcFC5Vk6Q5RzsEJAsOqOWJ79n+I0YVdHn8T7K1RJFfqJdzn9kO4Rh0kn56y0aJjLzRckNPmxy/LlFRi7YopucTJAYEvaqpDhF1ZiFxcG2QLXhKq6TePoddf0aUtGH7/IyOzP2wmgH3EQKPceNGQmy+REPC6ZEqoEUKj8DVTvs3c1SPi/SlECEaPVYAUqXS69npbjPopc9TS6LLXhoVe+WTLgE/eDU9y7mzWIkizU0y/rCN4zv4UMvuysCqKnPvoEBD3xiumMLk568ORNBfpbXechzxkprgN4H3f0uX+sGYo/kV8Z/eYQ7hEbFUMMYXQnyhkrww56DHZ+uNhy7ayHEbEQeUXkFdHFRr6WC/NjUJHPZ0v0axBFMWcjvSvR6id/M0yCTRDB8Wl3U9c8ixvN92+oMljvi0epFm8FzCtqtEba0Cx5Ld87MMmMyaG71VUpHa9iusg0ITt7NrrVxpzDCG2v7+MxE+JbO1NVVAVs2bi3e0R2wa/eeofs/Ee8cKIRsVCZU+F1C4tZogDU+N8AsGYhVQCbV3DAxnnZ+88IoKHmeMZyPqEDVaVhTqYI23+MGRkSsKpyxxsY0CNih9v0yAs91Ym9O3UYYbjLA+Ke+q4LmKnJG8ZybM5+tqwNttc9IxVUfRQbWpWRIwZ61bhNToYoX1OEbaELWJ+r+Kfp7Zsm0XemYokaH/0XP+vdhb9gFcllG3dGbakFv02PSwlj0JsDTjjVeLS1nWmzHBParmoYdmMc9XJo7h7Hq8QTFkmqrB6bYyJYqlUsoDA2hDNj2+Gv4qotmCbRUzLxZBJnC8i+nitrfgDQBZsdadbKNduJ65xya+6hqcHl+b4xQHa32Ti2KztGQXGjB3F8wQaMrBY4+/TDmVpaVv7LZtbPE8rLBjbWPzVgCRGx1WVPhN6zz5TL5AXnKTzI8l9HPuIqoLlzZ8pft7nnZRkj9j67bzvuSZJWBWMKKVTgHXZ0Qr0L5WAM2AAIGfFsivWlAP4OZ871UsgdO3IelyY68W8vcZQ2/J3bom7scOlbL7cqJ7F7FDLoQvdDxlZr0nmXDYfhzDLgIM+n61PcykeiPhqRORtKoZfQ8P2/LTiJRTjyfSoWe2dB5TDKt8dmvFxccMou4LaSUAvs0rVR59acIPOm7FaFpo+TUAGG3rj0l+SO1JTBgTFr2lVHmdDOUxpXOhUWJoPnu9DEd2NCd9We39I19a/7rtrcUFF9kAhtrtJxwKGgIXWAKh4hz6+VnaB/4qWRvbzU9wJzWpMeqX01WyvCXbzEzf8U5nGLli86tlUgpSrOmxQ9omyrZFspUZ2IKY43EVGZvpvBFlv2iVhhVLZIyxOhI/N+zhcRR53qLTdn/ZBWcgb+USoKJUOs6kis4frEJKoTcrnH5YZJLJhgzwqE/argNhDWbxjJi0qnb7WLd6l2CFQIeS8mfWC/6SPX6sdaeWz30LDml0UAyqtRPsvjHTE8MgXktebQ8imNboyCkOdLa04rfD25Cd5WoQYt3B9Zs4wklDOpGcXEu+j2mxxN3X6cTwUddTErrLndokXBH6mb8qcK6CGZY9tRdqAmtj5TCR/rjJCANE9eK6lgUv55qa7j/yVFTv4NIYs8bSSy78it2akJ7YSnAPNMTHEK8enO4HCQmeDZKp7zaZ5XFuf7FR1xZL6o2pOTgVb7JSI17p8miQHYC5uH2aYOkUFrqCt4tkER5+0ZG53bzGakBQ5yj4Dfji/oI6GUL3NarJporno0fJP1s9vnRxkw54xfEpPZk6Ms5dIH5j6LN6dzi/3i+xyM77mM0vuhXIlSw0BmJ41WZNeiebRXNz0z8NDxyamDxh6VMtWY1cKFG+diB17foFbDJ0zcfK09Kfy3FJgeynCj5z17A4MZQjE1ARPsyNQ1g4TXZ9NGeFOUw0eJCOP+xc0IiIoJInYYEmpVvi2L0DEUoP09QtyX5RDUuX4/v1gNK8xfCbMXKL03VhSIWu55eDQlzur3m8HT361QT/RdbDujaLiR76PJiYUpE3Og45GsuUaLS9f6pv7LCpACBEv9z5J1Ovbo/nmsEKj3UQtqeeHCmn138HtO2fJSf4Y9qtzVRZP194AGCo4mLkA/dTp7gkarOGMxzpYSlVphfrL/vmS5RlAvzrpDOccQZcLMorPxewltDflokgI8c5N2OMxWDpjPLfFAAET1Uokelvvj0+aQpr4yEV+KU34DXA/oRv6fmLzZfRA1ZyPLs1L4H1tnd6syn7dk04o1iFUMYiSbFeq82O0dEjEPBl9pbrw94sXYKuCcb29dyHdf5LAjdl9CjKM8m7cCQiAXmPC7DAv4cLC2UZFOI0F59zOgAozQjMQkIxMX7AyFAbUUg+ohW7Xq9TVjNltvetw/IHR2k10omvwCd9OewdBrtDNKmyJ7z2TpHDt/rE+2mFcSpGJOr7Ojq81fn0wSsEY4/kM5xZe0KJf5Pk5prTSdr1PEb7pDfUNzfH5s+E4U5Dnnsv2ZzCdIMh+2QCWKObxErJ6bD3w1ZKLmDRe7AS9ugvLJaC9ao31LtyNZVk6CKL56J7Po1oRXd9yfg+aTqf73DWa5Vo0sdf+JX6JaFMP6+YX8xRgLIN9Xju7GGMS2y+pYtW0+8htwrkhrBqibJoI2Q/wRXrncgpBf+mF9E4YHXuJF5TAq6hsZmRnyFIcffTWsU6qqivAg3hphz2hxNTS59P8ZEuDd261uEhngEye8IVmdyUlRCLu6bV7CBzHhPIhup9/k9ai6OTtZJJjODfJD5VphcRhiAou7D7UyyiqnLPzQTmlmtCHDbWK39XjrrHVnONd/cIaeaXbaItN3QDcSfDigd+89SYQEnzsUbwwQcgWZVKkiBs/5bLaNxhvuYKxhGQ39cowY+s2G7V6y98RQnTMm852JQuyarc4hOs9+x9o0TommiiVMe948A2v3sSZtI3UGD7Ff044dFRgkmiP6NbRrfqJkU2icHCeOXke4s4qlQTpdZNAA92r7QRlNRtcY/9TKa3DFoSutmhAw5jJe0/uUpnnlbZsNMIe9EQZsrBpV2rmPHjC8E4YHfmnjCQKniIuoI77CquQ95NmbuYrfhZMIk4k/TASmJp7k8Xzy+dhDU/g359D52Y8ppLhO8tywMoeymYzak7U3Ps5ypvRq17OZQwYhuDWilWbuit+JSkpomGUjvyHhwirWkKp2cIuU2xd8/une2EC0+XPWV86/5D+CvFUi/RO4h66q7nLs4so04tXzu4FBljaI2zUQkmDJYSpXZJQPLxdk0wSlnWN7LOhU47Xfdp5ngjtKCu97SgsnTwZ9dR8h2XqUcIhzrHmXiyCOegZ/HMOGRhD7kdk3l70rJM+A9jbM60czPVR9oYgAQUyOnfr9yuQFJx2YnguGH48CmR3aytamiVcCCGxZnnUho+VWR1vty12q2811el1FK1S1LLKrcGNQUj1VgGorNEobeuYLOwnDYE0r+ORti20956n8uj+jaKkaXCFPiVsnFjnNVQhxGAw3ml0m8pS7iQQ8dx+ZDg5X18wC8YLWdYCei6nBTCNUtWARz+dl2wyXjzlP5ENGltKKfwc7VQbG9M25Bb6/yGrw0NERolttsRqJrGThqmZWwomZDHkZ6RZC+KNa0aHKsk+OPEDuFcz2gfOsH6pIVD6fRQQPg5kIPIDTnmu9/y4RwH1kZgn4DaZJOo05l8MZz1esZ+74DMBYbwmEt8c32AE8bklscE1Wo=
*/