// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef ANY_CONVERSION_EATER_DWA20031117_HPP
# define ANY_CONVERSION_EATER_DWA20031117_HPP

namespace boost {
namespace iterators {
namespace detail {

// This type can be used in traits to "eat" up the one user-defined
// implicit conversion allowed.
struct any_conversion_eater
{
    template <class T>
    any_conversion_eater(T const&);
};

}}} // namespace boost::iterators::detail

#endif // ANY_CONVERSION_EATER_DWA20031117_HPP

/* any_conversion_eater.hpp
5yVAuzluijwmaUGlrf469drWNjyXQjWiORKo0Xmn10MKhZGutXuUnLzV2iJJaWiDFjF/o+0+VTZ5VjCNRMNLbJPE/fIlQX6TNaTTjwOoXRSE/r1jozgU32bIjR6Jjz/OzzvNdmc4SprVWsI8j69pWO8tO6aVw5Vk1/hNnaqQRBFv6j5Gnh/bTkjNQSw7UPnerdE67cJNdPwRodELCOXxM/TsYiE7+gTBd2pPbpOYrN2LmzOQZoWKynTdY6qLxccX2UWNOO20ZP442+Bt3caCvMfER9v94RO35j7d7gSOS5u+91H7QfQ8SAZhs6jwINBH2fbLU8kRP2a5ilDcPTXSLmgmjpZwC7nsL4PeD59UN7Y2pVJTXQZGDfVZCWru2CAy5uqOhPhFyICIEAutkC+JGz+dGqcgVoMcA50oiS+UMmUF9jQH/RQkfctUBJWQBcXnATTL5aZ3LF1oZ6+ywnYgz7dFQ9yYL2d8zt2gbtWt+0jfYTsl0zvaD5BneKmv4yjTSN7Wwpw2NfoaSfBm91IEJn5S6DVTyRtIIvyxWJ64U9DV9uZwjnON4M3oQVa9V1ERJt3cnrqsE3ubCCL3udeWbWRlVltoFg0VIep486OhLYYkrxF0KZXolxct9g3R305ur9Lu6bus3Tll6RdP
*/