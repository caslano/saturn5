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
j/1z9Vab9eISglG0XmBU68qXPhgYtFhzlxKMovUio1onfO/0N21W11KCUbT+i1Gth4vPnx2wWH+1lGAUrZcY1Tpw5uKrbdalSwlG0fpv5tTqtVi3LCUYRetlRrXurv70dpv12FKCUbR+y5x1uM1i/WEpwSharzCq9a/f+EmjzWptIRhF63eMauF++SyLNdBCMIrWq4xqfe+Mm+fZrEoLwSharzGqhfNG0F6/WghG0XqdUa3dj731TZv1aAvBKFo=
*/