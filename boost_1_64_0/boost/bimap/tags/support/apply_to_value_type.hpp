// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/apply_to_value_type.hpp
/// \brief Similar to mpl::apply but for tagged types.

#ifndef BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>
#include <boost/mpl/apply.hpp>

/** \struct boost::bimaps::tags::support::apply_to_value_type
\brief Higger order metafunction similar to mpl::apply but for tagged types.

\code
template< class Metafunction, class TaggedType >
struct apply_to_value_type
{
    typedef tagged
    <
        Metafuntion< value_type_of< TaggedType >::type >::type,
        tag_of< TaggedType >::type

    > type;
};
\endcode

This higher order metafunctions is very useful, and it can be used with lambda
expresions.

See also tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {

template < class F, class TaggedType >
struct apply_to_value_type;

template < class F, class ValueType, class Tag >
struct apply_to_value_type<F, tagged<ValueType,Tag> >
{
    typedef BOOST_DEDUCED_TYPENAME mpl::apply< F, ValueType >::type new_value_type;
    typedef tagged< new_value_type, Tag > type;
};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP

/* apply_to_value_type.hpp
3kLa0kEDda9W22M4EL5o9/3XuctOTX2Vd3+u2h1i3kn/KOZV5hvxpXpZV9+rXKn7MSaf3xJzJ19YudJyt0eud/VpuVL3uRH73dIw/0mudxH7Fcb+MM9+ta9LeC9Xswl/yzKlZYj6J/5VM4aXZdqtU8VNoL2+TsqIlFT5JiffTB9bD8pAhqscpOvv9a5yUWRFOui807WV8+Xb0id53RChTKyJUCYaI7RB60P72kwZI/yck/AH+t+07DylZScd6azyHHbzlkrZqV1cKN0z0782+4xzZp4pLxCR2n3KkLrBJ3dfkve3WnbIe8I2CR/+Bb8ZNXxjB4WH713sFkUOX1XppYVV9ZWVru+aI4fBnR67Itzvd9yvweN+9UsCdeqZCOnR0CI97m9DWILp8YxJj9Dw1Q0OD9/z2N0YOXz+ar/llV/qJt01xtT28G3zCN+048LD9z52mzzCV19b7hU+dZPuev/219W4x5FahL+gHenrhF+/Qc27NvdoUQZ7DQmP02u43xMaJ41SCRPH6sw8k4fC44U7Dbfpe6wwfZXmmunXbXucHnLihH/EyfRZVYTk0fYI8XkTt9alYfHRKu8ZF9wcfZ1/yKPODx0aHr63sJsdMXymyh91nW+OcL/ddhsY8X5Uec3bl8PTAzdHX+df9qhTG44PD99fsVsUHj6tUt75hRtTp14Nr1NcP/o69VCEOvWqqVOhcfIPC4/THtw3RIyTPN8807zBxMnUp5Jlpv/fXHf6GdoRp5fD46R1inu0iFPK8PA4ndCTdjY0TueePvOcYDGSMOf0jNA2f4FyhH8Ry9HbEcI3FrtN4eHTJPcOX9MR0rzpC6R5Ts8jp/kBuD2m/bqLHrqIHrqFXrp2Xjp+XjqNXrp8Xrp53jp4E2Qt3vfv/8Ut/e473Clp48HBe7/b8JCXbl77de2OlQ5ke3UdPXQXPXT/vHRZ26+b6qFr6qEb2X5dRy8d1IOyTiuH7sFSBF+xAnM98n2ir2h9Yn5L/6r8Hm+H1/W7u+t3N9fvLq7faa7fsfr7ZHv8xfU7zvW7l+t3B+e3jFPvh5djjtffjT7CDNdbOr9c553vhynIWo3j676AHuYbMBO+CfvBt+BIeBCOUfNk+FdYCt+F18D34T3w7/Cnav8X8AP4HPwQ/gV+DA/CT+Dnak/1LnU+tMyNI3yhepe/wZ7NZhgLn3G5sxZ5u3tC3T2p7p5yuUtRd/ER3N2v7h6AcXCry112K+62q7tH1N0vjDukFXcPq7tt6u6nLnd5rcTvWXX3nMbveZe7/Fbu95i626H3e9zlrkjd5URwd4eWkx/AIfAul7uNrdzvBb3fi3q/l1zutrbi7mV190d1t1vdFSBN6u45defWA16l4VwNc+E34WnwGrhBzz8I18DH4HWwGX5L/W+yRefpfaD+90C2BTvRVU95DuwL58OB8Bw4Ap4Hx8MCOB2eD2fBC+A8+A1YAKvgQlgIl8Ji2KDnG2EJ3AhL4Y9gGXwMLoK/guXwN2rvD7ASvq3uP4JbLZ0TBXdpPLojmzQeNapnXQuPg0s13JfCU+DlcDJcDmfAFXA2vBLOgVfB+XClpWshw+VwtcbjmxCxroWI9S14G7wBboA3wgfhTfAReLOGe5mZL0RbpOFORio13At9gfQvg31hOcyDFXAOXAyLYRWshtXwh2rvPngJ/DWsgS/CWvg6rNf83xOc4wFlrAVmaBrKe1tMIL87wKGwI5wKE+A0OBiWwSToh52h9H/Bb8OucD3sBjfDVPgg7AF/BtPho7AXfB1mwDdgJjwAe0Of3RcNk2B32AP2gxmwP+wLB8IBcBAcAgfAiZDwmTW2m4JzF5Ai64utsZ2H7Ff/sjXf4l0=
*/