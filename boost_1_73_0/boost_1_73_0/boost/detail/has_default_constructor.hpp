
//  (C) Copyright Matthias Troyerk 2006.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED
#define BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED

#include <boost/type_traits/has_trivial_constructor.hpp>

namespace boost { namespace detail {

/// type trait to check for a default constructor
///
/// The default implementation just checks for a trivial constructor.
/// Using some compiler magic it might be possible to provide a better default

template <class T>
struct has_default_constructor
 : public has_trivial_constructor<T>
{};

} } // namespace boost::detail


#endif // BOOST_DETAIL_HAS_DEFAULT_CONSTRUCTOR_HPP_INCLUDED

/* has_default_constructor.hpp
F7i+gWoEu6j7+ADeFHUPwzYq7rku9Hscv4FuoZPUf0Y6eBHrV7R0kX38WFSbmt3mCobjAzg+P/8AR/Dru+MzEy5JySiHUNFySetbEy7S1vJHTu7uLEk/mUAVEG7tAUY5kyBFptakpoDvnCW0lDQFIiGlMqnZEr+wElROIWOcwtjz5+70qwnrnCV5j7MRDchcNDyFnKwo1DShbNXBVKRWIDJEQPyUSYWYjWKitJCegqJ1IXsYnQThUgBZEcbJEumIglypSn4cjZKm5ljJKBWJHCXbVli5Kp5UNcdsCrIBUSlQAhpJTdD+JhQiZZlesUVorJolZzI3d2khYZmORA2Sct7DYSijsiuBQth3y9SeUGH2TOlFilJqtnUuij1HbGsPlDV1iXTYFvRLBTbehKZMad36t43YsvRdblv+ysh2uacgSswKBnYIbjiAJZFMmnDjRlfedQQ3dhDY02gO3hewp/Me75s7vURtMGStgd5VNZWYRQ2sqDij6R75Tz3phhVdwfg6mHh+FLt+4ITeZObACQyOz+HPptTCPh3AgLOlnjycWSdn1js06G8xJXITS6r0jPGDcpKIGF7B1P7uGM9hF0cgK5rg9DvhgutDVQslEsFhheNDhF4sLUw4n3p+6IbGL6xMeJNSuNC8nQjz
*/