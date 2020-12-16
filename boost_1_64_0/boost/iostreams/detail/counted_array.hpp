// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED

#include <algorithm>                               // min.
#include <cstddef>                                 // size_t
#include <string>                                  // char_traits
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>          // streamsize.

namespace boost { namespace iostreams { namespace detail {

template<typename Ch>
class counted_array_source {
public:
    typedef Ch          char_type;
    typedef source_tag  category;
    counted_array_source(const Ch* buf, std::streamsize size) 
        : buf_(buf), ptr_(0), end_(size)
        { }
    std::streamsize read(Ch* s, std::streamsize n)
    {
        using namespace std;
        streamsize result = (std::min)(n, end_ - ptr_);
        char_traits<char_type>::copy(
            s,
            buf_ + ptr_,
            static_cast<size_t>(result)
        );
        ptr_ += result;
        return result;
    }
    std::streamsize count() const { return ptr_; }
private:
    const Ch*        buf_;
    std::streamsize  ptr_, end_;
};

template<typename Ch>
struct counted_array_sink {
public:
    typedef Ch        char_type;
    typedef sink_tag  category;
    counted_array_sink(Ch* buf, std::streamsize size) 
        : buf_(buf), ptr_(0), end_(size)
        { }
        std::streamsize write(const Ch* s, std::streamsize n)
    {
        using namespace std;
        std::streamsize result = (std::min)(n, end_ - ptr_);
        char_traits<char_type>::copy(
            buf_ + ptr_,
            s,
            static_cast<size_t>(result)
        );
        ptr_ += result;
        return result;
    }
    std::streamsize count() const { return ptr_; }
private:
    Ch*              buf_;
    std::streamsize  ptr_, end_;
};

} } } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED

/* counted_array.hpp
4Ap4EHwJjoPr4cFQyqxXohmbpfUKxmaBBBJIIIEEEkgggQTyX5AtNP7Pnzypdvb/J6ZFv/23Uu1mt6L10WXoOc45fUeZcT7Pda3//mv/W8BfJfxAXxs/cfnb+HVcmi9juv6+Y3691zvHUOq7fl/D+tu2fezynvBJxlbMemGPnfgwSVeKcQuj88WtubEPJ0W/L2i11DF7HQlzEOETrY64jrRCxsadJH598WkXY8Otk7axDTf8J224Ou52x+elxn7rY39tFGN/zYsZi78gY/GPr9/xqlU/Jj8/eO656VXbXPRtZCw+wZSftB2RrdCRqKXnjdeHrWAqbA0HqQ12L9gWFsJ2cIbaXs+CHeEy2DnOttkjGD8HEkgggQQSSCCBBBJIIP8A2ULj/8mTaun8v3qe8f9yHXCuCROLclE6464yM/7nuf7jf+967u/L5RucCTP5Sqpr/39C4si0Xdv01zOd6+yQa/cefTjXZETC8383zozayVM9/j5zCqTPZ07Bs35/2wrHfxs7idBnWrnGnn6u4+45q3/oLNlfYM6Q6yD+zheow8bm/qg866xw89AEv7RzH6f9y31d9CwE4+83p0Haq99/0FLS74ZZFC63XrBvDb1gNQ7nmjjU32dexGeew7esdK26fvNug5T7gNDpdoVZv75O3HJCB3vK5j6J54Jwh9AorWOTT9/9CjzXfz5Gn51mwswPzbBetr37FLxpZm4CKZMG55130f0BZg3Ht+WxazYayvVH7MO+3dRlttT3JE6fvEvbmdvuemgYVnlImEftepyG2EzrI0Ximhx+wc4Npep3bsdJuNfsJ2krdezFnrX8FdNLulnme4wJEi4jdCvtsC+77t1veA8Q96zQBruN3qv5zLRMe82WdrWTmSvrU67fbNY8hiTtoxK6k4br+dq4exbHVIn7Jp7lySPvZg+rnDDefFJemp/J8qwU+0UrJj28WJkmPffIPenm+73PSj0tDR/KfNfFdpjdJ8/YO4V7mzxuiPyOhNdTbrFxdrNaar1dIM8dYrWndruiWWiqPm+13J8UOpRVFR3suaYcHpN0aBz831qJY6GVwMxafXQ7Vmu4dXej+D3BeZdtTLtrKuV4SPhl0hVTb5mWefavUmYtQndS/tSbubejPHvfUNNQXL11i/4e9pP4hySM4FRFd+5vgKQjl7Pu3O+EI/KM0QnN5Fuu1J++a4XyjLv0fYzWX0+rTMO49dfAvMfzJf4vqPU2xH9g07DOLer8opljTK5+bQ/5aeBA3+vodZZeN7MSm34tz7HaDxvevZulbuuibpmu21rjtnNv1+31qFuW6/ZK1K2X67Yq6raL6/Zo1K2n63ZP1K2H67b3TOO2s+s2OOpm0tw76mbS3M24dTNp7hJ1M2luE3UzaU6Nupk0N4q69bRqMIfrvw9H10/Fze3G78Gx9P60TdhvUxT/3Z76lkiuTXxwGDydsMuOMP2BvHyNTOa+5e9JnvkNvl/CNTXv6UdHyjvk9zdc47Q3Wj/ovi8Pif82/Do+4Pt31Hu/nksr9e2+Wy+Jf7o9DJdPucO7Z83tk6yUMBme82TLzG/dD+JXz/yOt5e87Et5pfOXvoP3uZnuc2XeXO7bjr8IKfxdqOtd12d+Hy6TuBpbdTxn234s96XaUq5xf9tWiV9DY295XNPmSUN3y7MX8HXxT+E05LbW67Hhukk4jecVCdfcnoHLN4SLrg0sNnlqBjMlvaP4vUjj97mFKZN35P66djerlFrKdvIi7Wu9uDex/2hfWiN9H2hH5ryWet61hXHtc21D/S6pts8e2j4nzDbtk8Zeffssmh3bPo8UG8a2fu2TOH3bp7l3T7m3q1/b5F7ftmn6Jic=
*/