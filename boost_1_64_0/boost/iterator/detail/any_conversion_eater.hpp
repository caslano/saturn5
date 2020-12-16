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
oI8j5sucFqH6OFNCtJ/sg305JaCPI+Ye1jpoxnWghH0c35zvSlNlDRVyMu531c85EFAvEqf6t4ujaDbbRXPNeSH7OXMdtotTA+tFyfo6+uxZCd8M7WJZ3Q7Vl7muCfb2bqq1nmh5PCTuuVghcaGtjjB86DrytLjPkj7Pxbrfw3Bmv0fsSt7vCU43y4r1+6i4D5f1Mxa5R/iS9318fkPIr8T9tvjJRFThv5v+TxORC7H/VXPFR8a5sM9+Zn7/97b07/56q6d3X/P0hln/G3PFF/m+qfC7WWrAWVQ/8Ww2NRfmYjAMvASsCfYHy4DpYCQ4FiwP5oBR4E1gNDgXrMAz9OLA9WAC+BjPjjwAVgePMl6VrsO+MV9+s0ilrO737XHDs9M28MywB8Ee4DM80+shzg36I89OfBicAm4B5/KMuVvBbeC9PGtuA/gncDPPnNsFPg4eBHfyzKw/gx3Bv4BpoLLPpH0h7VV+7wKLeCbdbvBp8FkQ6ZPny9RjZrBjvpfH5XtfGsR8TwNVvo8AVb7jGSTfR/JMtCxwPFgAzgcngHeCE8FNyj/vN8M3xgEu4P0qSDj8eKZXObAOWJFnecWCrUFZB8sz2s5lPjcHr5J4kA88y20Mz2SbyrPcbgDPZ7paMx1Fuv8JWWC5yr6wTEddznVrTHlrQnnrSXk7l2c2NgevAVPBTHV/MIf+pnEO2xx1X7AQbAOu5Jy2+8C24BqwI/g02Al8CbwE/JBz2/7K+Limgu/g0tcLWlNxgPnzKtiVZ3r25Jy0QeDrYDrnsGWAb7Dc3qRcwp+k821wKXiM5fguuI5nBm4B3wOfAD8AnwNPgi+CH4EnwI95Zt2noJq//Bk4AvwSVHN3vwZTwG/AViD8Yi663J9zE/mew2cLnJt4A5/zJj7nHD7nCj7nfDAbvJVn0i0EJ9F9DrgMvAe8C9xBe+ohtkN4Z7DooQ6Uz46Uz4spn/14lmQ31pceTF9P8BK6dwMvA3E5V4ADwN4shz5gLnglOBPsS/3Qj+XB+XxBc/k4j0/P4TsxJiJwHt8ZzeH7HuGTx0Y43XGNxbUM105cX+JKzC6dp1f6K/2V/kp/pb/SX+mv9Ff6K/2V/kp/pb+z+/uN5v/nn635/weM+f+F3OBRrYmuCSaDLzaFeaz/3Kr8U3+H0/stLZNw6/WY+wVifgdjIf31Pqcts2Wc3/rtAfe1f2vn/lCLxL1Ij7GfJ+YPMOY3CH5gp+Mvb/s2wfjt+6hWBTuI+98575j+kTsZzjgdj9e+5N8l6Nf6XUIVwmZxH46wffUc5TSxW4Oxmaa2bxU6zgQdZ0Z67oQcfAuaMMrc962y5EVF/e2vmYQ75OSo/GIZrRC7/sHfOQLzS+6TMyHbiL8189o3r66T8s+zFZONuJIZV6jvKymG3xTDr9+ZCLxHF3H7DnkbgTHSPL1vYYHY79ff1F9IwsU9TWP+w99bkuR7C+3MsqL/ZBWvuCF/aZdi+T5z/1j/b+xOtv0be+9yjvxmwzEJnA6+os4ayQ5Zr3nWiKVus+5tkbBprk+W7hVznLvU6am/BX+aI+Wv5/GXyRX5s9Z1pMVe1ymXa8W9iytmHVc5W71mXKHr9QZxH+nyWyP9F+g4vHYlr9P0a6vTUvbv/pO9KwGPqrrC702GJJCQjSRkI+zIbtgEFREhQISAQRZBliRkAgmGJCQDZVNBEEEQUFFBQanFrYqlilUrVKyooFhRcC1WVFSkWqmCRUHt/07+ub6Z3AkZtmq/ud938+fMXd9dzt3OPVfcO5odjUWqb0RL2SzQ9GfG578/K15xj8QxHBy/qyrzrRK2ka7/Ml7//bdumXf/fVT8h+r6rz0uvoMycVppgaE=
*/