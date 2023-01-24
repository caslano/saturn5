// -----------------------------------------------------------
// lowest_bit.hpp
//
//           Position of the lowest bit 'on'
//
//         Copyright (c) 2003-2004, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_LOWEST_BIT_HPP_GP_20030301
#define BOOST_LOWEST_BIT_HPP_GP_20030301

#include "boost/integer/integer_log2.hpp"
#include "boost/assert.hpp"

namespace boost {
namespace detail {

    template <typename T>
    int lowest_bit(T x) {

        BOOST_ASSERT(x >= 1); // PRE

        // clear all bits on except the rightmost one,
        // then calculate the logarithm base 2
        //
        return boost::integer_log2<T>( x - ( x & (x-1) ) );

    }

}
}


#endif // include guard

/* lowest_bit.hpp
uZh+utLP+fxqHP/mwyea8Cci+c2TtXR9bCt+stb8eSs9OFiLH9lHPzvoZ3NtG1kDK0EzT+cIqfWLC/Si12CbzvZ/g7boHQ52tu9kxweU556aS7Qs61+QUKUqcqi7PZL8VEgPmfwCGgBiySx6w+42qoxzsirjnE7ZVtCo1izornqdbP/pnGm/a5Vb+onOE3+i7NP3TLE3BZcpGUF+EljHWMQnoYAMfMsyCuw3pAcmQTYv9gCZuFR0EzgfaJrYuy3AO7KEqnixGydVEIoBblkvemo8vI1J/c+XzYAz1MVS/S78Pt73/wkf/MQwDMvbQU5LieFvG3SkHz37mYnpvqrRYXgclrWpecxAG3I0SvTDudQ1wR9f2QWGaioLppMylOxfTxZ5waO+nxSHpjr8PFecBjbFulCrT6Uu5PwU8KbWXLyVwjcWbSY8mrcVMeffmzUbu0AZMbPIVxMVyiT7oCoXuDMgKGcKpDfA9PcPknfTR/JAEmbRIDtvyUSQYSFeGNWjnV7SLMGfcAOMPklNLkmb3NjEJHIcJMPknJPQcZBu6XYDPpHzSVV/XfoJ+2o20R7YpPYA15LnXZDug1rve7Mh2e9JxPx9pOESPiGtPWAo3x/6Zwf5Cf2HtSL0TwD07/kc3syG2H4DyjcefBSTCyE2Z89kxE4yM8SfgDZPsFUPiU0aYjSQK/c9r5Pxvb23KidsqN+T7afUSGL7jChB
*/