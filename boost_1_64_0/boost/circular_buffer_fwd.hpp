// Forward declaration of the circular buffer and its adaptor.

// Copyright (c) 2003-2008 Jan Gaspar

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See www.boost.org/libs/circular_buffer for documentation.

#if !defined(BOOST_CIRCULAR_BUFFER_FWD_HPP)
#define BOOST_CIRCULAR_BUFFER_FWD_HPP

#if defined(_MSC_VER)
    #pragma once
#endif

#include <boost/config.hpp>
#if !defined(BOOST_NO_STD_ALLOCATOR)
    #include <memory>
#else
    #include <vector>
#endif

namespace boost {

#if !defined(BOOST_NO_STD_ALLOCATOR)
    #define BOOST_CB_DEFAULT_ALLOCATOR(T) std::allocator<T>
#else
    #define BOOST_CB_DEFAULT_ALLOCATOR(T) BOOST_DEDUCED_TYPENAME std::vector<T>::allocator_type
#endif

template <class T, class Alloc = BOOST_CB_DEFAULT_ALLOCATOR(T)>
class circular_buffer;

template <class T, class Alloc = BOOST_CB_DEFAULT_ALLOCATOR(T)>
class circular_buffer_space_optimized;

#undef BOOST_CB_DEFAULT_ALLOCATOR

} // namespace boost

#endif // #if !defined(BOOST_CIRCULAR_BUFFER_FWD_HPP)

/* circular_buffer_fwd.hpp
+p83RrkS0skisf9jtymdPDIwKp1MQkfm+iM3pI/kjgk/fSoRkomSZqcK/vGgR3oR1K2x00/4oB7sDYHGp1Yo2cmBTspcPSquKHpNdnLwM5iYDvSi97Qv4rVy+1wZxY2KTRRWhISib6SwwoHlByGbQbfNKRxJ8EtwzU+xI9MSfU4nYaAkeNnd5MYSEe569QIkRq1Z0DxAuRaS9wo1nQev/aY0V0k2vrJ07PwTcc9aWichUPH9FpGEx6HwBY6bHQQSeG468eKB2/7Fc/V7f/Obbq55j7MAr4heQXAHbXw9h6EmNEqnA1h63gzY36QzJBEh5W0BzMDblsnABvb30E0Iggu6NswI3WUllFGLe8ZSGkGrkzuDFJ2LlpjVJqRnuEK/ZGpHEQoV6F25y25gsRpYfmuldSSSuzIyR4vkzq5/NpJbA9e2rJ2AdxU/ZpQkBUaCiDe+7P50330H6iK5HSif1VRqveyNOTPTs2d7vBQl/Dm7Ap08kaEzsXEOQ3jdx5Ao7voKKYelKWWzJRuK8OcQTj5Ue+oPZLN3iaboiHJA8eGbuKi8SGaqb9SaQO+9EG5dxfsRNqTU0VvRV2MFwmaNHTw2iZDimG8Ep8+p/CKBIDK+zs9FgrbzYd5CtIsScXTJcafnuu75JdHr66Dfm93DF0nqYKfLKpJFfNakIkSUKjri5vxdQWi6t3CtXgWsbeoTVGKxv8WhLcbGXIvR/mzyuvIjcq/fcDHeQkJ44fc48T2P3z35fYv4xgBCq/P7AfF9M5nvGyTz/cBHZL6f1q6AOSvarBOVst9LOS2IaLSvdgaUy/UjTADSo0ckwJUGgBUA7LtNm8U2zcz6fszvEpHfnTH5pRv57Vkj4R8DPH3EMK/Irsve4Lzjk1NRMgVTWPdJ5NlvqBc8+yLJs4//X9wz+H1+sAcI9c4kEtDJ77Qw/u3zYOwv3MeZTIZL4wv4BuoR3hGTXodaVoGTNXyP11kltZsgtP+gUGQ8vG6aYflnJGigWztzq7B7ZsJg+8Vmobqm8JvoU9trfZ9r0mHngskLWlp2L4/fmEQp6zoaYFZBndCDiouinKJgW+DIdWffrM+6UK/AhMpZPVMjxeWyS4Ttfeql1FPGNwxLswaHar6KqBPioLptHFyvGXoBlzSTr9zTbPrprE2vwcRnCbIqYspAlRQHkU89n5K73L5xU6o//IvUgpIPA20GTe/sivxKjN8zrcAU/kVnDPcbgZnDveM+FmEDQkbv4dJ9Fpdu92MmhQmORykGIYaFyrWyhDHGzY9XR42blwaEnfjI3+QsYDnYKSwan7INWjdfaESa0y/2crIo3QfxUIfP/eGbUsPTO/vD56MKTsPOeKkPjvPYpPtktIX2yWn48O7YFhqDAsU0zsnyFP/KX+z+0Ht2GPyBTZhHKJtQC0CzCik+WflxYpujtJJctKSFlaQdrCTj4gMXKGUB2SbhXbK/3uOIuj9q/Mhe1dRyfyh1EpOIN5td9+QTgmViP4q97IkC8uQ3nsTsF5OnhP5tu8n9PNavWTfrjYxnDemUKybxfsGA3ZlqwXzGK3bscOYsE6Omilu2SEEFL4zNUiO1WZtAnhtDjSNmXws/d6tStpxToJAD+e73sYDOfTjqN9JXsO8mLiCK1Zy895Ggwiwoty8hWwxIhXrHWq3bJkHawRPB47CNXCZuJfKDNVQPDu2MSK86NhWOv29ByrZX1z/o5r77rdr2Gi5C7EK4naZEtzPufU/yvA9/hsLX1N1EHWiZQ8Y5ifgxpKub8IMY8TjeUs3zP7Y1u6oIs81Mb+iOVEsgqI7qjIn9Ftt+ZrpXm/wuG9mLKTgc7ERgqFfFrrV4TjY1v7PkWvPYJXk=
*/