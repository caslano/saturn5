//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COUNT_HPP
#define BOOST_COMPUTE_ALGORITHM_COUNT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/count_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the number of occurrences of \p value in the range
/// [\p first, \p last).
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(n)
///
/// \see count_if()
template<class InputIterator, class T>
inline size_t count(InputIterator first,
                    InputIterator last,
                    const T &value,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::count_if(first,
                                          last,
                                          _1 == value,
                                          queue);
    }
    else {
        return ::boost::compute::count_if(first,
                                          last,
                                          all(_1 == value),
                                          queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COUNT_HPP

/* count.hpp
sOvHk6T9ZZ54bzIOa8ITqZ/IRsqsEfOwLbl2EW3zDxbvxGOOYr4ijAZ2M2sAaX7Ux3yNuRc8rbVehNdVni1ldr7dwXr8RPfEzDUQhq5j0j0MRXa3r1zzO9n4v8fX2Sr3ea1pvlFkbvE1tjb6Wupz8xFx2+QbaPnsMfZeVjAOtuaT/qxImQXnz0MFF33WkPg7w9/Rb1vBPmY9Dei53oyP5LnXLZBSx4p77mWqXHVv/IfWgeWb3zUxMg37eK9naqMyFcgUIOPf2J8l0Y0wWWmdmDBoFLBc+4Fg2I3xU44Jjes2nu92nk9TDT+/L+mS/Gx8ONAtJZCxfpvJ0zm4d0duDWENQm62yjFjUc+fkpThr5uUxUFbfFm/PikpuHLOuT47S+/JHwPSfrCncOe/bdaP+Orijpvb78nj4oe9yuLbjk/bieYlUp4L+4bLfGO72DIP37+O/TS/PTccILNPROe1MzIlhNEOmdmy7u5AWoe4rN4oWXXLp1/S/GtGZimMBm8w+ewU8M5nW9d8PkA++9qhfqHA5FPnomW99yw105ST9Dvkeu3WgNezAjixHlTuB3WIsdfrafK93cTJvfMsdbvNuPXqE3a7LuLWK+x2RcTN+B1o3Hoavw0jbuK3Hm5nB8yYT9emO+bLvdacyzjunjrOcV1mwGk/HHD/vZ4/yJLP21zsodxF+JX1Qs++VWUVpYUry8tKK9yee8MzOsIXRHa7bX7Di3153Pwm8pL+p+T6XSI/wciPNvud/l7sW+2r2bNvqt3XrBXrkO4z7w39Sn5zy7puU59eFH/TxV5gwh1hdMI9xH9Tr2ex0TFTt3X9d6g/nEtYn0tYa9FZpkTGdFFzsFnYPhWZdXYxccWtI9c5Nrt+UCbJjBGSxX6+PcVOiop7UemKlRUiU4jMcQl3tT1T9Y/mXZOo/voJkamyr7UTonUBwcjNnPXTInOHXWn749bVZem8bQdJzwR7vPVTEttX3bmb4r6f32TJXEmRZ8K6/qwdGsh5QTKHUBbwp0SeCR+G+3KVG3tGeO53CD14Ylpa8snnfv8g6e3oOs+bBffK9VyJJ1PjKSOeOaFnz3Pxc2oqcyb6WlnX/SLbg/KiTdpiecPG7f2aCsl3Y/0dGi6Huy0/br3puwZZ7V3fsVkict+knfU279jsELdiK5G1GzPd37Ex6wxKRHab2k3d93y/5hKRT/a6X44yqjzTlFGqs4yc/exEzHmq+ytzvnNjdH75J+ln87hu1g46+jNdy5AQP59eiRvtGzfat/Z7eXH9nrMf2z8ofl/IR5CvTg/vCzl83JSo3xzb4vaDVFlCiKxVrvl+j9t0v8dY/VP+4Ph0HUI2PSM6XYwh2UyzrCyq/dRgr0lH/l3ieZB48pzxrFqi7W1nfP6RPfX9Ond65L9qSHy6foFsgSNdHFp8knuDvDmzmDrodmYxMqd+ZjFxxp1ZTDxxZxabs9iHxufrfcIod+Zr1coSzzypbFbUc7Xc9H8Toq6bNnqK+dH9R7XtEUdM3RmbH5+Xh/Ff6ciLzDF51B2V9d5LleunvpfqzhrspWrO8h4Wn5cd+K8yeZHVxWNHDRs5alrUvM9NLnnCj8nTJ/H3x1w3cy21yNNNLnn6xNwfZ552u+TpPfzvdc0TfYnOKQyVeRVWOzEKKI5eCxGT7hk1SHe4DyZM0qhhxpxTvn14fDrvDPbBbuk0bd67/PFn2vyXHm2++p9o8ze5tHni8TynfM0I97qVnumaP9q+d97w41235Pqpt/3a1K2JI+PzdBv+81zzFOkDtsflSf149wFcP/U+YHst+oCcUfF5ug//Bc48FQybNmySdgGS5svj86R+snSeMu4+cf3U+4DLXfI=
*/