//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP
#define BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the inner product of the elements in the range
/// [\p first1, \p last1) with the elements in the range beginning
/// at \p first2.
///
/// Space complexity: \Omega(1)<br>
/// Space complexity when binary operator is recognized as associative: \Omega(n)
template<class InputIterator1, class InputIterator2, class T>
inline T inner_product(InputIterator1 first1,
                       InputIterator1 last1,
                       InputIterator2 first2,
                       T init,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type input_type;

    ptrdiff_t n = std::distance(first1, last1);

    return ::boost::compute::accumulate(
        ::boost::compute::make_transform_iterator(
            ::boost::compute::make_zip_iterator(
                boost::make_tuple(first1, first2)
            ),
            detail::unpack(multiplies<input_type>())
        ),
        ::boost::compute::make_transform_iterator(
            ::boost::compute::make_zip_iterator(
                boost::make_tuple(last1, first2 + n)
            ),
            detail::unpack(multiplies<input_type>())
        ),
        init,
        queue
    );
}

/// \overload
template<class InputIterator1,
         class InputIterator2,
         class T,
         class BinaryAccumulateFunction,
         class BinaryTransformFunction>
inline T inner_product(InputIterator1 first1,
                       InputIterator1 last1,
                       InputIterator2 first2,
                       T init,
                       BinaryAccumulateFunction accumulate_function,
                       BinaryTransformFunction transform_function,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

    size_t count = detail::iterator_range_size(first1, last1);
    vector<value_type> result(count, queue.get_context());
    transform(first1,
              last1,
              first2,
              result.begin(),
              transform_function,
              queue);

    return ::boost::compute::accumulate(result.begin(),
                                        result.end(),
                                        init,
                                        accumulate_function,
                                        queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP

/* inner_product.hpp
EWolOTN11nAxYjH0caOTRqyMFHOCq1snz9iFxKqsf3BZgpInxU4EfdicbD8Fo81/SWK0/Ql97V0GynlgM3GZC5Dx0sreRuJUTgeLLzZEsON71X+TnB4Ba+10iqRYmGvXBiJQAODvByDwhJ6ui77vl0j6NrP62B3CNBbZsHq2s55CVpAbTIu4O4pE0YpXcEYsNCPm/jTnmewTMJ8LXgRG2QVL6zXgmk/pD/Jkam9Ror2F2B6U+Kjo/O0BR64D0VsbSwM7KpGnvnATzqCO4TMuixlz/5SpKa7CRw8nx7niF8lg82WAxt4XAJh9uv/UBoUW5x7MIyfBPFJTsjAaa9NjhsW5mlaWul0oB/iAXWOndU2z2DFl9UNguXuEJqMUpsx1R20ShN4leiL0OJjrMy/qaUqks+gavNCMxXTBlAxJsElXF2qfv8K1VQzap+ruwiWFuWCUOjAS+IqV3WZGO2/9fWT8BWBy7Gd4JT3JlznKe2QraEiRxxNaEOp7XcpONnWu6uqMjYIKymA2tdh+Bh4LdHCcZ+VcfrQTEGcjZwLgAhQjVKHqdwJxSpRHXN5lDaP2234vXPjOn/bzzRTSRMeCz+9lp/lbPX3COH0CarLFY5nb4jxnrdhAduZYVndFDdjeaWBohPRg/zPwga53HFysL5b72Am726JLHzdYr+4O1R1X3Z2AGSRNwO+meqO0veVgjs0Y9WxvFn+J7rLH7qJk6fPugYjZ7OWWkJaG3p/j/PqLSD8Q/ML8fILaiFmQRJLHpLDPFLanCyza8MJOC1YJYJeGtqHol/zaPqpK6hr/ZCL0QiJf/0wVbL1LvjysLaZ84p2jALciu+4434gPCYBT+k/sffEz0CF/nqu+geZyggzn1STJcOEiHYvX+GCh5/R723CZYYLxPo0yfdXnE9t3SssEw4GxwEqZHVqWK8le4LfrcIsOplt8H5G6iieUGB2Gv0WTMHy9MKlygIqHrA4df4nNO4k9NtiFblGMQ4lW+W2SFF5LNGANLc7VFHSWtLzZq8Vs+O1xfd2+5iFe2e/xGkCQFvR7+PzfpR1YRJgfKXiTyxxZMJMsAXvDTkehTb7c4bbBop3FHU+R0TICrAj1bjPLn6uifZIOun+SYt5fn9hHQ5sLtHXocQmk67pHMjG8FI37lusw3P6mRQoUo8Pi4lJ0qNQDYJjM2+Osl9P5y1/C+tocTZhPGKj5/Kv+QM3lpf0+mO8rLmAnkYMQjXAcnZiRe99MzshcBZZ5l/0MMKg+eQhbhYogRkSBcV/2117NFzC0AvA/NqYksELFKSrI3LNihwpuq9EWPBIw3wvNDVdor89x1dXG8zfohPQBc7eBcmnGwDbt0lDMmL4zmrzD0NGUXsps//ypdCl0gLTh2XIOBjJRZdF9cZgZ0v4PVGEOdIm04JOSrliKMT1RnRzTGhnHBGSiAR3upwz75gehXJZ14rkA9QabF+mvSxJp3shUfdwxSKMIKjqZoVt+6X7iqgobijl4MIYhPv7PUeQFfGDlEcmmaVVfEcLY0YvP8Hgz+i8KrBtqcN+peWXNcHhXRHhDVTOyHwPz7FYAayxl0d5tw0CTOXQVPjw4IkOKWbY3fowqvGxUFxRjUrgyODS0CsakxawI81E+9kyf9jKWhMgZA2rbqoF4ePxQEg8Vj+vj/S+2h2bqjFwSWvaIJPtxG9ytoLSoBbl85hTyEB6+NU2iuONB6Xyp5LDQbq01SoKBsoKU7P6C/ux+Lz/UCF3C4I6yOJ/frafTeeYm18afn0mR3d9Rsdnp/l2x5AWsq0RvAgnIAVtkyT0gQiP/BeuedAZLvw7i9SeYAT9xBnUPZ7d8KzkM2pgLRYC7DTPhp+UWCUmAqod1v4tb97vbhNECkxIwpOlxAbJbUtnLzskkHmg8/1g3YM9cqujzAVxo9otdvt+Dn0aoLEokFKPYO89Y/P1jMSbGciOAjqOwDIQf/rkt/fCnpcLv42NPoDifjXb/3LLYzTr6bLopUbs0Q61cnJlwvzrIRSoPYKqTCvpH3fl06qh1qx4VyRf0YIKPKRbQlHzTvOoTZr5rHO4dmTIa4AyMuB2NDBMYfFJgZOLe3uC42ySns6noBZ860VlTPswedQy9AzGzPuqJGYoCWYm6bE4u3/7DNOCk3khhMW+qwPxv+RI2JRfForm/Uegg+VGZPVqaP6fk/ISnhwHQ4yxnqvS3HfcMhBqAgdcUeSJPo/OYW2KUZzCJ9gRS7FoYgWxWG3ua3MIu7nweqypmzOHdiHRLz+oqfK1rv/+SlOecZ/qn4QycwNlP70Rm6vxGvgMVcX32F/3L2cesPSIOnH0hHU/oE3lHPkhHoUvP4deuTZFVIfKxS7IJ9+2mCPDcN5Is5YZHdZYyOFSFokJS/htt5250B4ttPWJTwCX8s/d6NZiC74sPFFQl7dvu1L8oIjehqwfBDtXI/KN7BgEmexr6xZnFh6pNaHlun+ruUcxgFLX/HunMHyj+LMvGt/6sT7Ofmj37z+iecNbKWWH/WDlLGFJtaPgeQRbvH6ssgSY0+XG/0CT+62fCMHB+I6ZK3/0k9ob4z+eJA6hoELozLlLZTGu2s3+6ylgleh8AiAu8Xn1bJnJ+MF5E0MmxFd8rX4nO2qgz5ZrAIzwLg4H7fkoUNpRleHEbITDO3BiqFX6YaJ7bRftuYnuDhVWF6MN/bT+m/drPOPaTRjLch5Pb19WHAYT2i3EHW8S9W2S/8j+VJz3tUNTD315BnvYj5GnnzuOgl3/2QK/m2E8+1+HBG4uDWbNVV6vqbmv/GYppLfI0RhZ8qtKsKi386M8yJHSm86e6+/6FJ30VedKPWCsw7Iue9A7nEXkTM7MF6EU/Q170DhhtJVuFkaDQvDgifpSjIFfJCuwWoPLLAc46V1zPRNLd3buLKMcU0DP6bMFYdLxDq8Um1V0v35ZgRpOYqxlVXeZuAal9udPdtgwzT5m7NTLTYBCDActphked1cqveDQD+m+Bf83SmQIwrNKD5jmxacCCCszyRZHp49lwx+2dss0THMzHD8F4+TJTyFUP2hIGt5i7HgoyQ9E+Z/0y8u/i9qiCLKe7GftsNpS0hMrjkjw0MQH8nuWA/TMOpcMa/judBdDidCF8KJ+aDa5WVtImmg65WtNCtWnOI8vMDlcr1mhlqzCSppeUY4k+mPJWGI/fw30/Q6WCYz9ty8DUglVFfvjd6q1qqYn3PtGL+Rj37BP5GKaqR5CW5u21oCbCK2GlsjjlYXwDM0RpGG+XoRpIa8b+sHDrmtG/hC7TAEff7jwvJsi5zGpJD5D+Dxylk+V0YJ6xoY5S5OrTkatPnwiMmBWM9xQxtxk9ufztt6GvLrDsKVCglptBtP3SfsoenaqWmR0Fk/3A+kGRnIbmgGc8KCNiD73HRNgczKaNDy3ulAAHLPjTwFoY5KUdF+RZd5n5z2EsGI8cXfU8Du2p10XkrNV+qs7VPP7rkTbM8S3pAc65kzJ0m7n/Llg0ZI9jwu9nSGxT7kC+aUSWDkVGA+UyI+USXnCzOxQjsyB6sXi9lJjS/pyk7+ZEd/NP+siBvirJXBpRIrjaAEcBnXCDttmwCjBZpMOD1QrG59V4OK9PpIzH2T5UxzCPCFh/lki2w5MeMGju42sDONdxyi7uwCxy0LTjoZo4pvV+9ma3FhsGLbKFuR6fl946Srg1PA7NPKUVB77mzj7Nq+3D9ce6/Fr2UvRHE7U067jiG6AKq+OjAYu1/M2Sfit/8gDV7UMWQkXCfsavKoedR8rTVaUpdoEnwmhHwy13GGDgTcAAjIBEYOaidmhevaQqx1SlEZPjtcHKhcAzs9cAL921IigVw/xHlkpXAWWwWU2wptjbIW2otWI27pfUchdeGdIut1Z+SbmOV1grrqSbsfLikHaVsC1C2jj5UZ0hWMO3mc6z0TCcZ8Itxy+NT6Oc8jeRa/JLrwOFGJTeJg+yuAjbjQHh8kaeeZeIiGxCd2K5HiuEF/Z321Hc2t9VZzXp9ouc7WSNyEqHIkgksjCZIHQA+Sug4rC14jUjedYz2I1gIVnYn8jvDQwoZtRczc6vrRVoAatKPTsCansBW2zGzUbsZiUnMg0drxvpsBZlCIpFa/goSiLgeGeUEY4/IQTKmv4WnUqTsq99F67UvjnAeVLhHO5kWA3MDMBheCYeo+I6zEJNYttphUUAOYg9ZhJQ4qAK8VAZo+YmKP+R1g/ltgSUC01K1gAwMxBMZRx8A82MFiDqzI/66m8Ygf0Dc9Fup7WI6HzctKInQLXT7l4ButjzykIW8rFY11IY+09EhFpdCAP3BhKvy66yR0Pl5stg2UbuAGpyHcN8JgoH4D6jac4D2MLSf+gk+TJ+KTnj1oppCN1ID1QkB3L7LfhMcO3FOxFgtFbswkTOE/Kg22GYrTGjOqtZVzAy5vfvYDGTT3/A9tMr2T6KVMBbNGtxw6nYJ5rQ2tpxC/jZaWNRrWFH5aH+oMQvjmta++9xr57RB/qDkWgJQXoVsYP7VUPkkgTsFBGq9C20mJIWmncMZPYxjz/CMHmAy1MH0RyPI8cEIuVobKtg9JiQN21eP/jphoH6kZI1cDDWMDHNo/zLhn+h9OmBCISYuRqdrmPWCkxdRSlYL2c7/oRYV4bilhhxTgBmG9xEaVGDQSaqIUxwoRua4O9vdE56qZXG0JGZkfIWivi6Wp2u+NKJyMVdXcvHM9cxdlOWiAhlBg0UwYAP30ejtkXcUkOUd+VqZPm0kzhTJ4IsE6UYJk3Zr54UgYSgpeotFDSX/d4iqe44itEeGZPBNGVQZrT9j2hJTMFAgWYNr5fE7vTQvA6pLh0LO2lmesidFnFzzran41bYjMD461An1DwI7HTe9Q1mSLvN/FhNNxjVcFcUsFENlA2a5x70KWPX0TUWafYbq0dK0svYvLNmYYY6FO8wQFcT58fewE1DHLk8KEaDaH+Nx8Rc8XS0VDxC27VHed7vSYrqx2T4UEGnky8UMzvNr3k+E6ngVkeBCXi2QVuIEYpXXgItaplJApXheX+vJsIWrT+kkzfUQgvzmZi7i2U9pXrMcK+angpFTaQUVxVfh9uDcW1XdSMm83+H2aHQkSrynTO0dR4jnV+VyPFBsub3TcuUwHDbgnXI+hydjgnc+MjvvR3z+DEFGqRtmwhA1VIA6tOaXniznt4ombynr0d/BLsK6hZ6kvGv3f3xrx+TB79WtolIKUjgDJVSux1jPEikI+DdMFbP3U+S392olltE6jfUHG3dT7vvPQK0wIW4yH+eWBcEo7ZA3xSg7zKgnQLqoaV0lbGbraTjX32K3v91H2Yq6UdyPPxrIDuq5KwDKz4sUwOYXu7YgpWta79CNrFlAZU/gsj57elkuj1f+iam2iMQb+LOAv+ArQW40+nD2/q04IRIeCI8ez18zWqLFDpsEc8eAT5QAFWvo8IJKIsWmNQt91OPxfRiElxvwRfZfGdi1GzLHXD163seEAWFhIIAJcjP7MO9yCsPTcYEfdCt1PBDOM8zHIcQOdYwCh4Hocga/hh5P6FGz8K3VhzF13qKI4r11Kz8OtqWQAJlK31ZSNgDliw2MxwFinhEsPXkdobnS3E7AyLRQVayNYxmpaPcYg0fQsl6YCkpB+E9lMCbcZtQFTCwloBiK73pyBdv8EA2Lx9/jXgaA0+XEVUHcYegmJqaXtwDbl2NygXbQCR6V+edzhprBJWefOtqPKbEeXun9WlsbD4z3T5fDS9GtEXh5he4j4EegaJbdqKTQDyJNcQvxw3HOe0vGxIQyvP8frE/xO/lP7qGnIJ/uDZN8ngj7hV8zH+Btk64JWW0btnI/E1niezC7yqgv677F7tFxBYQykirKDJKsSV6H2IXRVDT9iKmvfxgtVHyYtp7/14M9RBuzuCvjyNQTnyF++lxEwcy5SF14c16Ner0fFs0Urpe8VujpBPOGkwiEts8gBvkfUrub5HWhTNBLublJgnslmlot0ybaG8IRxkRn3VTjTptnHqvZTt5g6PyEGfx2MfSncXjFtrOENka5UEr7yWJrSsBhtJk5sZeJB7hlsA9heIDs/6BAZ6R0vP1ZwkjuIf62cDAjSSDXh+4kQTMNaJ+65os2sE/ze8VzAaYDMy8Wkkafh0P7iKrL+CXBq3gX/+xW+P/LAKNHiSY/e94LMOrwlTqCBFBSPLI/lhoRAHN41ZkXRSfUcwiRKO6OG7trrhMTz441YqhmlzSf0qEsRhHtBpQgyixhU/Jo1hhrnq3BawS9XGMskSesJGsVjqYzYvnRM1YCqJlGEgkkL/QvHDfnLJWVOPMPDEWVJvXccF93kESsYP/+c/AwaaORSEKeB5BZUfAgtIeH8vLVoI05AdEVRt/GquSxOSbD/SKqHQeqKYSLH13nNww/Ib7KVCZxQbBF2CsxoFXYwBiAY3dxso7itR58VBdHK5+PuVAtzYbja6oLZimGrR9mO7h5W3rYbW4bThXcwDN7ASfiX9cnL/3ir7nBmNDBeOhp7TSWi8rHetny8axurzafEeBrfxG5yeLrmfTzawmNoSBvJQc99nkDKj8dSx9qvOThV/A+2Fs+ng+bE6fiLSj+TvMH5luUsts/De3GGC6y+YkT8VTzP7IElOQYhp3/468TPO8uP+h+GYDanaldGAdKgI3bQR5Fssnfb4Qcx5vBhz9CDe6n+APf4RfLr6CXQifar/EU9jEixn0YskXInkAw12g5h8Eq2dOGcWleOW9CcPRR6GRyM/xCKGa3QTJFX622KQPARM2eO1NBonUBz+/A0YC7ZT1h7dSG1ghGrjczyalfh/6d9+zWWZn0djHLnEWjVs0CrT4mI3VgCaUBYYGG+zwIJoblA57lOA+Pj0BN66BgxpJd/2oL0uyySIfJgpmhK6S/KzcYsTIHepLftyoS9BqN2jZudvIEnKEym0GOROuaXJ6cGhxbBxz9QCKL0ba3WWAVVB/sn1+aOm9fZI8KPaxvWG+aj3J1Qx7VKQU8mvm0uEkuD1ETwMT9sRghnMIcI1P5CuACuVTV1YhizQEPA+YbJHXUF0HldKj3QxwUa6KmpEaObR42YdnQri+LHougPwQ31+W6LEYZup+APZemmgP2AmdUHqbD9dKJyWgZqHuipQ0U6QaXoK6ahc564rZyCDuL9Bm5F/m6sH0POXTUHmnpNSUlgEO5uhnsp03K/3Y9efNSj9v3Zb/Rd2O/0Xdnn9R1wWqtQUnAOgmnW++B5A1y8xm5Hh9Z9/1sy7VbTvzlkG+CmoUHAACWs7OOrsfS2PfQKMY8eaL5/ZpBsWW16f8PTYWauWet9bMv/UkaqVu54DXpMa7LJRccQn0rk3gF+b2aHh0Tn5KIhKshwx0mPnZOflCUAmaXiZ6tPgiT6Mnj79YkgErpSy/NBnzZ9NNuM/2hd8B5xoGd6XtT+MtUbzYMk9Oe/6aEa0BOfOpfNDwLasNsN4wxBc0Vz2KUmXwdgtZOGjz8AlfECuOc9Pebs1+pgCd0aO/wF3xZg+Pg1gD6VP9j68xFpv7OR0tOsRH9dej3eKyaBOYEidP9xW13RoqotPjvGs3vjPzRdtJvNUZkATaMSW/zoAz3F4Jt/3bGPAtf9zUv43hk1u/E0KnavglvyelWtWAaiKnFz2c
*/