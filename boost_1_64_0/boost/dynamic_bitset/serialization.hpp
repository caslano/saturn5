// -----------------------------------------------------------
//
// Copyright (c) 2015 Seth Heeren
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_DYNAMIC_BITSET_SERIALIZATION_HPP
#define BOOST_DYNAMIC_BITSET_SERIALIZATION_HPP

#include "boost/dynamic_bitset/dynamic_bitset.hpp"
#include <boost/core/nvp.hpp>

namespace boost {

    // implementation for optional zero-copy serialization support
    template <typename Block, typename Allocator>
        class dynamic_bitset<Block, Allocator>::serialize_impl
        {
            public:
                template <typename Ar> 
                static void serialize(Ar& ar, dynamic_bitset<Block, Allocator>& bs, unsigned) {
                    ar & boost::make_nvp("m_num_bits", bs.m_num_bits)
                       & boost::make_nvp("m_bits", bs.m_bits);
                }
        };

}

// ADL hook to Boost Serialization library
namespace boost {
    namespace serialization {

        template <typename Ar, typename Block, typename Allocator>
            void serialize(Ar& ar, dynamic_bitset<Block, Allocator>& bs, unsigned version) {
                dynamic_bitset<Block, Allocator>::serialize_impl::serialize(ar, bs, version);
            }

    } // namespace serialization
} // namespace boost

#endif // include guard


/* serialization.hpp
mbsoB7+IkhXU/atZYp9YaOiFxEKxrn3wfJICt3xHBsoLwQJpVBBAMSQm7dw+QxuiddfjhugG3BDdxBuiQeeLnc9EQmBdB5gP0OooP1XAU5Se5NhIAvv6RYi0Y/pJ6xH00P9dYLeXN22OPMfs5f7BT0j0Im4KRPyknvomBkekR8AbhjwgTsBoWdKmdo4Xfd2rD09H1ZwrLuNJvy5hXoD/biKdPNOEdbDtzhbnQEyVPL4359OO/hNqRf2pECx6ZNdto6uuxpEkW3IFLNgOl8j1FPtwFZ8TTpAWBVrEgJXsf5RfcwE+YbY4s6dTwMOJSxeu5TP7mcyls4GjhZlnznriVLPuze2BRFvV5mE0k40FAGH1ZIJFLopsy40gIlFBpMpKJB+IdF1QIylUk7lWKdIST1XAGsJu6xfh0X0l1bilSd6TfUnZcWVdrjh3FvjQi8tkhpLdFE6Oqx4aK4oUuvw6LPY2Ira7QSwCsT41ANvLjyO//rbJkV+PuNQLvx797d7wq6M+W5u4/2lS9+vxBZpBI+I2Ogwcy/Z5XlzhwK7XimScpu1CZlqU5VQCcosKlb41s+8hfmkkgvPmXMqKXUG/hnnu6RjeeAQHnAYB2L9S+nPaNM73jK6LTPKlinc49/uzNOsXNERZZqpCSDhVSF3i4+DnwnmCucTawBAPAwQ7MsdaiQ3Vqa3hR6tJpCtuKlWGwfjfMi35Zrw6CV5FqACIz81jl/oWy/uKcLoRvrAENgNC31n2eTEg5MhPm8X8N1/x0+5LHI0U8ESoK9xvYz/qwlMmd+xTJ4iOPwz3XpVW7flhE6WEDSrvp7+v9WOq4Xxd3kKenhxKs9Wt3+fZahbPVmdNE6cnuBezat1fXqWPxahZDIq+80Rddz556q5ukVBw1osAwnb73zxdSU4nVf2BH1XsaxdYZleo09X8yrLpOMHaga4FXHM/nNi6qztS1t+3yqxVrVhsVt3HWiQV31LSJafLpENUbwjb6jS9cqqprTSTair08Cb3eVShd9yfbBBTxVzFn8mLdSV0Z/5kjmTd79hXbByZ5KjrqyVHHtuDI/8404EjS4kjEyuZIy9kjnzym4IjURhGVydPpP423pkjkxQ9uFrnyEdO1jnyJ7J2yCHEfZ0sUKJxX6DrEuruKy6WTHE+V/GKK72x3rTlMusIZD3IrU/H6JG4w6LkntpznCh2jJ7ebWE+YzX0uYs/B2roHvTD/RcRf9ErwIHynSUGAgpyx+9Tl2zzRmAjdhATXHYNMsF12Ir1zASPn72rmwxKDfGrO5KmUmTHRpH3V5R3gsi71pq3BfNih+gvSaTMHEADMG0cigJk1ZPl/MQnzqKHO6W/gxVI4DYrgSPOFi87i6XVlkEIRko6yuJ+13Qt7Dhjrg7ZKiDXWSF/c5aAHK5KSw4blHXZettGCS4lP9mXpKznBaLDI9/x3OFi1N8j5f6u5g6/ihvg+TNlh5OOa3JrXPS2BiTNSVL7juAIag+M5LlhcZgh4ONtm9i7/euQ2R5qvtlk9VK6VFzZyjW/nmv+8lTF6nk6qwcVq5dR3iki71pr3hunKlZ/2gOrT61xZPUjiMDfrmJWNwmMnSr4ssGF1adYWV2HXC8g11kh07UC8kBV2h68vflT5W2tV+MXeu5Vwc/bpR7jcu7VH3Atc2p78nPQws+b3Ph50yfGz3ZWPnmWXunTzUonelS6TAtpEyH2gW5tqnZzALxJTfW9Fm6qddxUL52hBsAL9gEwiZ/89DZmXwe6CHe0wF1rxV1yhhocCxWutDdTixelgKFau93S2mT3CQ0Z4nNAvbPF/Lo1eqrWP4j85iuR/A+s5P1Mfg88Wg69alHWiSrwESHMFwg=
*/