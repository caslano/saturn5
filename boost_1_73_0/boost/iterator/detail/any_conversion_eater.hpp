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
kMDX46vsb77Idwb19f3EqbiNPBpH56+dhHVuWdfoMqTsECHtOImF3JGs6EidSWuNF4kZaew7adFIDvm/YgTktE0QtimEbUBoqelI1uyWg/jdclZI9zEDo9rHOO+/o08iTd2hyecm9YwzEFXRuXPK8O6AgFsbITC7XjGL5WlWexBS72nC8kCcvlhbJHmmJzkkyXOQTFu3bZJc6kkOS/KFSCbxTkk+xZMckeRCQ3yPJEfSkzMN
*/