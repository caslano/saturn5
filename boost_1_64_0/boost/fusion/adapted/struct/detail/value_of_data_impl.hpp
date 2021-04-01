/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<struct_iterator_tag>
      : value_of_impl<struct_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
e294tgUB5+2gXmO8hUVoHw3ET0T2WqxNYS+cycikUpzQm/MHdgq5mIj39DHDDBkQdzTc8wRLX22nFkHJwJ3rne8lKUXLkQYWHJujsaS0EJJc6cvjrwC6LTBCx+wdPWf4LmwoCGV2lea6SLFtu+qDwN2a+EW8iTFD8F465feyEwqz+yktgduyLksO5Ya7KPFOUvQWQjuaWMew3C2ylE19fAF9LVv50OtbneWDViva8oE210LTeDDkZzwJQdHVuqeyucDNtpZ1f19Y10+c4dQHJWx16UPXCTClzmcljEHq5IVjwRwLuWBri5wAWT1SCKli9NqySMHRakRHh8yxcOa4Unfvg7wZAPtjm24lRXlIEtY4gkMiIuroHS3t1SEMcvZxeeT2Kz8PdATUTfbJqXy4vzy8Qd5jte2CoRuCR1GUVv/kbEzGJZThiZt1n+2eyVUvrDeloou4YGlZ/8PWJflLAtr0MxBF04gmPMG55nLEhl2McUykqAvQdV+FzkSSBdd6EDlh6AbVdOqFd6Lqa1i/vEg7jObkgrllQzzd3m5sQ0IgOz1e46cejGUt1w==
*/