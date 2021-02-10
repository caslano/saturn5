#ifndef BOOST_METAPARSE_V1_INT__HPP
#define BOOST_METAPARSE_V1_INT__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit_val.hpp>
#include <boost/metaparse/v1/foldl1.hpp>
#include <boost/metaparse/v1/impl/next_digit.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef foldl1<digit_val, boost::mpl::int_<0>, impl::next_digit> int_;
    }
  }
}

#endif


/* int_.hpp
AwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyNThVVAUAAbZIJGCtk1FvmzAUhd8t8R+uMuWlKjNUnbRSkqnKqiaa1kQN67tjbmJU8EW2E8q/n4EsabuHvewFbHN07neuL6lD66SwOGVpobfkXy/YNmRyO2XzLFv1D3i4z4aFwboUEnNQKHI0lkmilwItU87VpMuWpfxskPLBk32CNZoDmtAWObK0c2n951w4MZTh8ecIrqIIlj/ANlaWZDFg34XDBLI9XkJ0A4908JI4gvg6ub5JvPjhZxawGWmH2oVZW3uxw1fHlavKgK3RhbMeL4FFKKqJQoO3kFMlCj0pSYpSkXW3AQvYhsjTDjwpP/J57FlZdN4Dtuw3XmD7MNM+tJf/2UKqRYVDoEvYW4Rjd6ApnIJTRS/kgxJSSVUldD54JZyP58t1tlgl485ktXzKeIO8Edrx+OrLV/iX6puiHU62+52AcAOadIivhXWF3kE4h9HcV0/OICMPfwLwy2M+n/sZTbFtoWsIiK1DA04hdMMCSljYIGoYWUWdxaHXeoPakCNJ5ZT5eYH34MdLjgP2gSFgv3z/wrudL52A3JuSj5/vn9aL5WPA7qTE2h9f8Ivult7avkn6H7z/mpOuXMrPiVJ+isnP
*/