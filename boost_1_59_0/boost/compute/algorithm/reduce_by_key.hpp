//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP

#include <iterator>
#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/detail/reduce_by_key.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// The \c reduce_by_key() algorithm performs reduction for each contiguous
/// subsequence of values determinate by equivalent keys.
///
/// Returns a pair of iterators at the end of the ranges [\p keys_result, keys_result_last)
/// and [\p values_result, \p values_result_last).
///
/// If no function is specified, \c plus will be used.
/// If no predicate is specified, \c equal_to will be used.
///
/// \param keys_first the first key
/// \param keys_last the last key
/// \param values_first the first input value
/// \param keys_result iterator pointing to the key output
/// \param values_result iterator pointing to the reduced value output
/// \param function binary reduction function
/// \param predicate binary predicate which returns true only if two keys are equal
/// \param queue command queue to perform the operation
///
/// The \c reduce_by_key() algorithm assumes that the binary reduction function
/// is associative. When used with non-associative functions the result may
/// be non-deterministic and vary in precision. Notably this affects the
/// \c plus<float>() function as floating-point addition is not associative
/// and may produce slightly different results than a serial algorithm.
///
/// For example, to calculate the sum of the values for each key:
///
/// \snippet test/test_reduce_by_key.cpp reduce_by_key_int
///
/// Space complexity on GPUs: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see reduce()
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction, class BinaryPredicate>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              BinaryFunction function,
              BinaryPredicate predicate,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);

    return detail::dispatch_reduce_by_key(keys_first, keys_last, values_first,
                                          keys_result, values_result,
                                          function, predicate,
                                          queue);
}

/// \overload
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              BinaryFunction function,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);
    typedef typename std::iterator_traits<InputKeyIterator>::value_type key_type;

    return reduce_by_key(keys_first, keys_last, values_first,
                         keys_result, values_result,
                         function, equal_to<key_type>(),
                         queue);
}

/// \overload
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);
    typedef typename std::iterator_traits<InputKeyIterator>::value_type key_type;
    typedef typename std::iterator_traits<InputValueIterator>::value_type value_type;

    return reduce_by_key(keys_first, keys_last, values_first,
                         keys_result, values_result,
                         plus<value_type>(), equal_to<key_type>(),
                         queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP

/* reduce_by_key.hpp
ufoJdlo4WSuZrM9ghwAz8rSSvMgKp43gcAbgcEahPjpgPAOVvOiMicxeXrc4jrMcKHfMcGslbn2Gl8TX6IwbmN308lf2STBjfOShHNsCrWS8VP/GCXfzWC8I7Uyof7v1ShL5vXB0m0PMVVlWQJt5FwkimrpSYwtN7XdsJzf5C5jgFMXVwQTWbF8bc8MjI/uagFNG9rMgmSQzWEmbMtJX4lSHkUApvvmzM5ZZIXvt08tWRmtaONLYRt/UUiVbZK1g9GK7uySGjZD+OLSGUr5HZXNS4Axvmgiavct64ojco/IQStzfoteslA45aIuVRpj6jIkR4S04GZCO98SU+03Yb5BmRwzZUTxLDFDPiBfeYQzgRPG7VwcigUxdSlkSjszZ47p+QNz459OGb6lLuZHa9C3uVSb4lmbDljhLvYwEqr9/AX0W5AXljxw/S6yHo810Zj8ru+iQkkNZiYfyt+X7W0xDaLZYJo4ydi2+DcE3dvePoKAp2eBwMUvNkN/yMfTlhmUInc+LFnbQfOlxGSwgn6t9z+AplDFx5kkVVd2/0rfYpQT1Yh7BndQrHsDtiM9kLIEXhpcRNT1LGWNW5a+PfO4olTXR/n+R2Sglv4F6HcXmp3bYVE/1qdnqZIIBnbaHxYTmN4hRNcTqLV6sXGWqfI41VT5HU1dOFefZbJk26TwR/J+SYXp3M785bIoPVRaKQ8u5GvUasXe5xW0fT2NRfcwMQwaX8Heg4+mGn8iTUYYOqVniecreykNhBnPxMjVDQgq1oRfnSd+UP4N3N9X7M3bkNoha9NS3MNe7Uow8wfeb9SPA17Jpqac+g10lok0fh8RRbpM+NRwSIp/HgjgOO97Tyo7LcCUEB3DDfDyA8IbsOjCozRXi8CNptq63cXtl6pkt5ioxA8oCg9+iM+yW8TytHHawYlCOYskKVugcwCJsr6ioCOhcQPYhIPXSHNIvSFA81EJg9gaS0iJvIFvaBeuTmiey0or/rs4RLbBbmGzNLCYNunfm6t+HScO7DFTv43n2NBSY07rjczmtV6ZM6xh+5gldKCdUTvL/67QuC9O0vouumGDktHnqVQO9XWz2tmtRcqZnUTYThL46I+ZcWDM8P3U2eMlbaSZwNxD5PE1iRJqPB6wM9ql5JBDvn0oC8f7zZ9vBfoRS5ryiotxsamAroaD4+U5z9U1iM4ow2FN/DWIxlE70PdbrqR8LxoLQzzxfK06er4kfPGEenK2sAMrAu7g+kogZLGlLQDkDYkilRTEVCWdRlWTF4yzlLc7GlthwUqmK1GTZlHmRKWBfaGI75AqQGAmeKAWDB8vn4XL69dKFek2b3grLyRbTbLIdN35On5WAmIT3EEf7838wn+Z7pZBEMUlCM7jRoTrvRY42O3FgQ6yVt5d1mK5Gy9qJE3LABJzjVrU4qX7ZCSgxEZdXk6X8B/XY7u8sOqXchKlcVqpcI55cJjem6akbk7UFwWL/OO077VCkmjIeFOti3xSca6ojrI1BeqxfThKHHpV26mi0axHUEJJT6D/uIDaSPVLoNR2Omr0g1G0c+ATEGWjxXl9+G+xEW/N5r3GckBIlrvZ4U9LU4w44at+JHaxCtqvVdIr3mvsQZQh7GXfl8hfkxsbfmeaJT9b3GRXW1saZ1lMh0/nDmm3AOB6dp/7n/IwReho2YCZuxhn2eRYOcPn+gdwZigOmroVZ79ENfeaOpI98JzedJNto2REWMA+wn1wImVQJ8wqyHgn5puK9WUvTBubmTGefDjH2O5hd5CBWkxX41pfHzfBh+tRefWQoqh6pCJQDoqt13rw5Wa9p5zArUfV48iszKFNdDjtcHd28BTHYN6ILNp7vfGmWzN0xPgiE7WGbBA5h95CAusTFzoJgqJqV5AlGDDttTrUkQI6yzihvyOXSTwANXuS4ThuOmk79QEimiY8ccKPILStDTZp7QLQOhaHMdDnytFZuYt1xYuj+vsgaMdjt9YG4EbtEDpWHyOMdME4lMV028ShlR9CcbLWCmCe+egrMoTGU+tRcZRrxpD9jYjFILFL7aSOJjWTfKJQ4yqbmiRAS00zWzjpeWokDqMTpk+wJepZGTYl104kxzrWFXc1PfQP+/6fJu/OJenEv8QNLfSW5yv8S2zWcn5b1iKdCNLTHc9kZo2hZzb4rSyv4UyGJFfT2zbAtPBjv03/IFoTKhOIAiyeU9OaLkFZcgciuicy5n1gYN0yh5PFZeOzB4yOzpJ3Q36fJW32zZ45plis/p6eBd4uSXJIqmt7BI7O7JE8NC4h5G87wDdbrfIOVq9e6xe+6oD283Ct9EjD/3sXKsf0yQHK0dqKeqVW5W0tcvDXO61UXidbV5ph/XMFjroCw84dVMKVVpskhT703jrebg3LEs38gRzwuOeJ3CJ0D0nmhcCRHu3pmYrQ19CiM23Fg4WyeD3ng4tsTfhv5bPXW1eZR9gjqSAH7E8lfbZ5nG3PjhlY7R6uFE3et9j79EHsaql2o1VaLv3die4DCE2QaXFflwpPPIZJtxLV/Yf8+CKLQfISdlVAD7+Hklm+sZuH26g7cKuXw5V6kz1AvCYjwLr6L+uNuvouKTdBnFoZwt+UtD4iZ8tsX9C1Gu9Rt8vVXnLVQ3ycuoWEhkHNC5jo5I9tOoHZYWRwtySWp7lES40ryEGZgCh79LjzexKkT8XhwNWI9OPGYw6k5eBzOj5w3gx/deOxfhMcAHnsWsb9+PlZbi6WPPQhB6MdIfjyPMjxNT5FalvLM0wYUe3JRouHbVyF6gpOeHuJCOfQ0n59wYzqbn6C/VMpPKHErPclLg+os2l2aX8W6/qIYCj4s5/XRIrwIy1XRv7PfFIkC4qa51sbeCZ2O4l6gGSHhMpJOCbMeA2wtEtc3Yu2j3ShtmxM3qm1snNtzlp3p5jKo7axnzLw2PBiOcflTtKGbLWdHN/CnEeZ7NIq2xHe+DZKFFIsO/eXOOJF6fMTR4Qz6Hr6KHm79AU7bsqo7aWcTr6DUAfEMnIW1NxxTApEnc23KHWJNQ7KLlUHK45Av5dQ//QBvLmsXc6+RGp3pCoi/3nd+BxZSB/RZi0Qh1y4myToF6hxEdWK3oSanh+3BaIMwBy+037Ev5ssCuoNo69pFMBxO+Rzmz4rHTIrOdItH72NlMK0qt7UkO58V43NsNq/t1Iw8eG/GxWKO13onIHEMqsrh5zSSfiIzc5yxzLqZOSuZsGJFCYSjS+W9UWCjmJdGnedOA9efvgOD7DTfInjbI8bcxmrkzbYXsrygAZ8CVkbfatIAcfOLuJpszcijz6s3YK21DTfwbyH/TuJfdu+wsxjPl2kLnNoCl7bArW0I8Mc5/DuPf+cjY9NyjsJ0ZvWG+zgRayHqZmXYKqJNR+3sfNUu/paWaQtnRBtXQ1EURvzaPJc2z313OE1rykGxJhgQ3B3QmsbzWx7/5nKFWfzrxfle40SoVa6w2VZvuD/RA9kbeese0jYs5KT1aGjDy/y7Lg1FlyHe1D0wupKsTbHWCFNwrdHFv27+5dE1ypEq/FvNv1h7IjuvTbGOqfWnkQl00KtrXKrUaR5R85z/ZHKC7mKy9cYsPp/ky13cMAfE7DGDbHfLKRJDaHrkRMrQqTMz2DcPochv1yEsR7JZarAum1v2anU5/ODW6pgT8GdpdZi35GW436V7tac5e8ClPc3ZA07tac5e7Layp14/MuNT5sKB8dq4FLHzZSrIHiV65RX56AGJ8Fg04MKQ68Ot1Alcw2acV+P1+JKBL4egaGbVmX1e8sBa3SnUXj/RYCgPB0PVxW8S5cg/IT3Tu03vmnybsdYFnWdJpzHcJnbpObruU1uPzTbO8BjGkLbIp+fq9ts8Nhs698xxaYM+lpiktWuB65T4bAc9sBKOy7p8pUGvzZPjcOsr2dSvEeCB6H4cGL4YeTE3a7OoC3sib6NTNmWkXse984ZtLHAsozqSca6yUrzUVxBb65JXbfpHug7A3Sh+/TkhP4LNlwXFX8v6jbv1uCRL69DVt6cvyvaKl087bGGw3t3l7KdAY6BHlzENNu60OhQrJ68BWmJp+r6EK5I3huHOxivHGSaWTB0Mn0Oc2RqxB92nbzwA1H2oqmvdN08bpoJriM945YS3M7vJVFNXXdSwTyYAoegt/9Qe0B8lzcigJ6pdcRglTnp08uNMFz265KO77s92W7EtUuO2KVP1VYBne4a+ClBsL3HqqwDXE0pc+qo8fnDX9dsou+qnvfO5wbRB7SHaWuLqixVGMjJj15sFM8yKUEGeVUHOgAqckRJnJmuXJBY/tK8RhMdurM1BkKyd97HYO9UYtQkBgHii9zVyorHWDQBsVOzynIrESecmvid3G9sUJlgKiZeRn+LZtqAqBb8XpmJlZErnfhK6qXW1IsISmk0tsxDFWNspF7XI2Ibr5+qOHYQPl/zztNSYyLK0LoYQJVlWxnv1cJQdzUgWMJ6ZnsZaLkntt8hOUEub+l1Gs8yw3dgmsIIkOIyn0heTzNwEhU8G4U1psNtGKKeraBfaKeG8QJdYOAnTIYFnEyMgUgMVxg9BmvUmGGY27FfSxeuHMfwBOhF17vPoklX3SLNurwWC8EhR47KBxkggX5iWqrYj9X5ezSUZl+Zr7Xq5FtMkWbhPvt2sN2EL1Bux+emjQ/pO7H/5O7Ej0gCcofxdAWMb3sq5iWfgotbssD2FGAzmc8mf5NJbqr53hf6R2PE91M+7TcTJbfGeE3HxMwYb1XnPibgZX5lW8klC41FmOnTeJZaey8COU7cPu2h0O375kGHlOu6RFsHfe1P1RNa2yzE6WdGCR83kQirffBmTcKJ8Ko9U0Yi8uKzaY13c/vHmQbbq16heMezoV+9uXzhFDNRTt6Te3fbHk3e3o472DQyaB6U6E2lCaik62CY7ONlaP0wmUTbu6lZQ1WPT6veo+Q2GenUycVOaMkTPCOIVJJaA+6HC04ap0y6zAT2p0MiUbJfvBOTF3pNkCLAQLNqjTiJ+OFrmLg8QH2+MWilj4dH/Mveu494hu6AkVG2Hg/Gl9HkZYbDkLWJPy3ZQceSnSLF1PWkYlq5K9gByTlTcYUHKyu08fD0uQ3lIylFXwyrQ+yKSnozXIxciG79OIRuvMtlAtdgDQGqMJdRBL+UNiHMFxN7KLSHay6pNw/WVzbLGTJKjpodoPXjzkLPpqefwGJHNkjS7fZEt9ORZA0cR0V+vBnxKxQ8qf0lqQWUoiQQ6+BYRuIOA0xF5UHCHMP3EqONald62MJrSlx5PA3seh++whIu2ZyE8f2meHzuIq0g3dV14AzywkdgGaiD2H7Tl37FyO8ivTZ3Ky7FFKh4V0hJSP3gRl3ztIqalLmLscl0HBdoX4fqIEA3CviZ+9z575RgjA0/IffH5TKnLYC5tTqoakjtYUXAsUuNNk1yJ5u9Ur9d3QhutqF8dBwBP2Z7tXzpsQUKBNvHW5RwLreszya4Ya+t55j310GOX6qprV5pJO8wJ0yq7tcoerbJXq4xbDsC6JdQquB/LYO1DIfceQFrRHmWwZ9vKH7GBjAgGw0MSw+f9g7kkJsZ+L5zJXSVJtG6Pzu2ejRgYaxfDz0+lUCZIWO8B3F8aiTuVdPijG2monWaR4UTXn0FuOK1ONtOFgEMpzs7uzEiZyXIgBhGpgmNB2V+cr8QtEC6CyTzMPWmWufFsjKhfKaFp8/ndqsvH/LkC55BjAkHMGDMkxCTY1cvlR3WQPitXa8JjMDhw/WGkOpiZV/GHd89yhA5JNpiS3rs/ueOzzwJjbUcKI2US/LF6E5ib8De01eACI/uNcvpHWdpEN874piyGfgpQJGzjZdpBa2bu85HuQCqFAIEgKFgo8W+ERLFqEwB+ybiElDYzZT0CBvs7Ck4C3jW1A0Y3HB7MBIUEXwgtH+rOJ1+SnO3fEdDUHRqcnZ8BsxJhGc6/V4+wEAV1t70SfyZDv0/NBv66GH9b0mS7edQuHEz4DybOhaEogNMVCeFv/9MBIiDR12Whr5dpulbT3GB46v+cZo0mBTP+9rmDVi7broyheR0ZmbLjA7A5g2U+0JK61oNMi7Cf8Z6nNuuOAoN21wMSNHT/Dqmlpfm3QnuAB1IMSknVqvcSOdhK5GCLJAdsHiIBYokJEKlTrkyk1cArY1GrcimVpNJzt8By493ykCy52MKlJN1tvO40DE40f7NY2nbWkP5L9QNUxXB9JHFbgC5tO2s1D0EUEIcEOHOPUuyWwAJqQF0ID4eqV/XKt4h7od4UMhWl0VyaQoLtUANlTHbT530lil1+3JuYZmbGR0ba7Lj4kUIOpyP/ypocmzIqZbSSETholy15GnZb1PrxXFhX1fQgbmxN3ISzC4PQ4yYI6XP36v7eoiMr0ovmdtd48/3duPw48t5px9xuDd/aivxx+ujvqcmW4wY6Ic/cvbgq6kFgjLId+e/qc1vyj8wul7sG7mSkB8dwVsB0t3jItP4NiSU2mLjv0BrzWCJu0RpxnsDDDIeB7S1Gn5EEv+o35VUFdOGo15vhGdNRvWjcKK+Vg7Dnl58x4zwqWUz3hjBNOxJzedTaWw+J623s0S9B80J20LxE6N/xqbtHdj5R3gc7bdg1g3plVn6lm8OT1biiZZ24sAcnSMgtmUGwXd0apqVX88cHEv+5vboax3lsWXb+3O58tSff784v8+bvzj8UocFrmdosp/pYUIwO49iw8+6ifTUT9LndepkbS/SeMgxhDQbpbfmHtDJ3LN3xhaZm5fuz8nc7dmmZhtohPn4YBQUKXqPP7dHLsAiyYLZV0CsL0qiyueAMp64eh+tR7qdEkQdg1Nkm7vq8z5DyAbZtrP0NHJvwDMxxMG25NkxbzgU23aAUxIy1YP7hl59BZzmKV7qY/4g3HKvN0v2dIFlQgy7as2IMLhpH0fhpGHcXxWsyT/1JqxGImiP+3bSmyAm6Xyjpdn9vzGH3x3GiIbjbNnBeqhC/q0b8q5ZaX6ICOd4l1/B45/8zOd7uxHipoGzCCRLvFwmgucJw2fZf8HCgoKXivO7qJy7cYWW03sQiDeEISziEKUW7avJS86gX64188VkWz2+EiJNf1lPUthwnA4UD6sqS4lF+o6yo1+Hvjo2QZc2CfmAsR/yqEg+co+7v+erSVYS4vwXG19ATmtVOQHxNJy2OBPpkLxZUsUI3Y3y+vxNGu6AC+TxtBX8Q/zx74UYts1s9k2ovOFauH4ZSXqVV/9wsqEuVdeYf0cZqVc6i92rSCXQJk+ZmQ5WvTOQfsdKyeW2X5g7kxLjn6FIv9YPQboHDn1XwBy0D/nXRQ6/Dnw0FsH1V94o70Efr3uK8Qx++jtqAzUF1brHH5lhk9yuNTarMVj2S8UIeYesm2DJZt8SCDZZ2UmXdMRchOZ56POvBiTF87T6T0o/ycjQeivJJcDAJS7fSzP8Q1QXCbHuI1/m8rTj8cTBrUwDimpSbGQgc/jMaw4TxYUA8cTWTzZFcI70/fDVjwuxYHyS1/QmJMQVZSmSWP8X7oJRTbKNtMxUIHacq4Vegbh86KmOeYTeoShh1MEcZ3YnPoeQ4Mh1+F7p76Ve76za7+58B8e5VsrtckN5/exX35dW/9xmJIyDr+BGeZt+8wWRFjMeS+78ss4XLSKE3
*/