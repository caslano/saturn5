//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_CONVERSION_TRAITS_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_CONVERSION_TRAITS_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/conversion_traits.hpp"
#include "boost/detail/workaround.hpp"
#include "boost/config.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct conversion_traits 
    : convdetail::get_conversion_traits<T,S>::type 
{
} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* conversion_traits.hpp
/IzoJFJfXdhlrfMok703IWLCoeCS49mt0CbswfnRRdEenLtIdHbnPljo4w5Rr8HzdahWbnnCwPZwaniHu+VJhVE458ayrEGyiZt0j6lFY/kOR9sY5f7Fd2SDV8FAc+viPLaO4rKb6dn1hcz+PKG1XQvbn6FtKbR9xYmKzjRsnEuN69zKJIt0Yr808JA0/ABpLKJV2PClUvY28AyfcvNcApGrcL9lWGch0u8xQe83lfrVpOEniWBgv7z2O/Zbxt5egInYCzJ4RO1GQmrdDyKTsqdokRe7CALnFvRk7ozWqUaqL1Ij1ezs6N8ZDnbldi3n8oizV2wKdZCm6vuTHev5vszAta4/+/sOu/0G//lyf12nJhuy90jaKp77gKqy0I+Odo+f486lC7v1wo66sHpS1jOiTK4XmnXHSO66gG9cdeH5aMVulGO0Yl3WGp4eO7JYQbZhdLSXSpb8K6krgjS44NI10cO7GIaXe8sC30hJnkyb/Qbc7MFbAKcm016/Afe6fCx4ywIgRz3CM7l3dJfODxEXEZrJY4926SMZA2PZdC4Yn87oDONXOYwDH+NJIvh7u7KrcQ2Ze5FmPTA8CuSfZJwPyL8PdgB5B/uX8Zz2r4yz2b8Cr+NYyeA15rzGcXOncXSht7nRGK23aXHJzczsKHFdC7dnv08sc0flzZpR0fbFIvlU7ouYpMLXB6SdwWEVzF9G4WjzJaBmaHxQ
*/