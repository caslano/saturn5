// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/key_extractor.hpp
/// \brief Key extractor for a pair<Key,Data>.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Key Extractor

template < class T >
struct key_from_pair_extractor 
{
    typedef T argument_type;
    typedef BOOST_DEDUCED_TYPENAME T::first_type result_type;

    result_type operator()( const T & p ) { return p.first; }
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP



/* key_extractor.hpp
FSnueNjbhA/z6Pu/9u9tBfTLzGAqreuv8CvlZnVF425ivsunmG/45OWCvDl8WrXX6BpidE70NA/Wq5zlU7PitabTSUZvsIeeFSsaXTO+Kdqsd2XSECsbBnlG73O+0bUmpdPNWPGedHDuRPcWJKNDqGj8dD3jyab8Nng8WQ7+N5lxWjof+OXa3w2rQsacUa611vA3ZRc8zkHzCLromyie5qNJ/o7AGqQYADB5L8Gf8jeFpLogvRj7e+eOxPq/d/rHdhEfafLGp7FWStMEjZO/WHMbLkDm8ePwzsDYi7llQSYqOL7SF/hWK/3O9vjmls/hpnd3Ov8D+rPsscLNTXihlUtaVH8VR7zGQJo1qCT1j5NoF5TPmcadYbtnBeV5u8bqv608v4hcyY/dOwJ5nl+2uJZdjlfMN+gKPqMExpP8zezzKyuO+K9HVB6KK8lxLovK58/Vt2uFO8eD/9W4r6BP22OPkVy0U+fbXudspn0dSDJhU+39y40702qGj9Gx9z8mND6HHQvXdbpg/eXtr1eUCeVLmcgvUObe/GoNXpV7teYm9FFEvVX/1wbKfW7JwoVcU4OKPlx70H59HHY9NBZTa/bdacJ78u3O0+B5J6HtZIjSvosCM2dAY5TOQX7iTfsjdtpNmrEmM3t+QaHqi51mu97fb/QnWoP4r3wojljHuK0yM4BUdUXhnQPjn0LGIBcHdMKWxcMm/BS+x7ZQ+yJPib4xu+92qv8aqbFFOt/Kk8YWVRg/k2aNj7fH2CqdwWV5S4va18HLKcvuj4aUZeE8laXr+Zd+jMaH1Co3hXexr5cvfMXrpWOMiPIZnJ8DLWuPdVnI/pkh+dGtPty9XvrdXPObbYfHOOpBybyCQmK060FwHAtMHCzvqfBJdnhH/3g0u2yeaUTZBO6LKpuQ8ooPmkthp9GuLwuMLukKqRcVGmd8pb5B/whex4/djwfKkQPkza4oLyU4tI2pHKVPW0jStfHPxj3f05//o5B9yEeI47nIPg8cTvt3dYyTZNTcQNLvK2OFJ3nmWleq3LkDPGHWwtV4QO2TpnK394k3cUzG/a5xR3vmWJXo4OeMQ+miFs0rKeC4Wid4swlfz70m1aFTjE5gzlD7J80zneYieLTPHVyzrjb7nGFKemYp+bHL659Gp4U5TobLcex90nxpSXXRcUvvJF+8nkLr+rDpLTc6IxqV3mlGp43SEnQc1/RmhOikUedb4zeYwR5HqMv3cJK7ss/n/O4GX0oM9a9/ToJ5ZnS5PuY6xm4CPTdC46d6pefGJs3llxa6r8pVbY384WfKRG0y4FfXvqku+yo+7RvcHu/UHXOXxho9ARd7r2tPB9ojD/y65YVtj9LvbD/Dn23cNZ5Bes5f5LvWkRRd6+x9jrP8a0e30HXM/7xz1nZv+AOMM+DMsERogk5GvtnvB1a88fMYvxXGb4lnJ9qh84Vi9S5UZXRWeeL5H9DR+4/WlL/I6Kww71PNTdmYcbd2Pt834R3sscFu84jaBfzmWmy6DrvctzVv2MR5jSfaaulM1xxuq1prODhdOTEmnJOpuU4aN53p8+d0mVNjP0duN/tmeIbTJtrh730/a0Y6jo31PR905vcTpPcDrVebh/C8YJ4bNhB+Ce7msb72kVNn+2gW8545Z1Zywfx5hZb83pAfuebVy+f3uPyoV/Jj3o5L26rCb1EH45dhz8sJfv+yn1s4X/Y46ZB5OLov2e65issx98eUt92Gckw6TBkHtZftsZbZZpP4bnAivIj0VT8T3F70WGPO5xJH3Vc9kv4Ae57dRuPu59FzQa1nyntN+D8ZMzVS7ccfR397bti6Z027sOtCC0tjbx1t6jmzT2fPo+zlbFM=
*/