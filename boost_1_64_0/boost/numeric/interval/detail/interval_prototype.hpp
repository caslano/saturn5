/* Boost interval/detail/interval_prototype.hpp file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP

namespace boost {
namespace numeric {

namespace interval_lib {

template<class T> struct rounded_math;
template<class T> struct checking_strict;
class comparison_error;
template<class Rounding, class Checking> struct policies;

/*
 * default policies class
 */

template<class T>
struct default_policies
{
  typedef policies<rounded_math<T>, checking_strict<T> > type;
};
    
} // namespace interval_lib

template<class T, class Policies = typename interval_lib::default_policies<T>::type >
class interval;  

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP

/* interval_prototype.hpp
Ffs46LO58tk7dCyHBgNy4tvhhd/gC4mk8C4Cu+WkRLCIaHvYB/AOQoGlwnw4jSrHlV9pQNxNupXG5iCpw66QOKJTly80hlUUkwwQr3DxWDYTLinC/dYn8JendN80EZjk6TG4SBZqfF2ylzQdQLT7iuLMi7JDND8njckRivB5o8+lHoV4rQrP0QdqZ2soYksgg/HENLryRop8vtmJWL1S2kRD4YfGuc3IbCdl8ojed8Jkl1LfpiidVhUksQ0876njMtsXh12qOqm5nrJ6D77Q1p+CY5t3ntKGeoAmiujqujg484EZ56k8g+3doiqjEQZLu/mvyrJrZdL4REJIYq9AttExlg3VWb6H4MTpCPBlxYaOIRJHcOMdpasHwsJ4xPVm180tHWcSymJOoNt8ZUPX3XLC/EH3i9lAGByxnnyO1tTPMDPJCQqrfkjME2+cQ4uT/pyrAAQN4r7asBK3ZJGHRJEWGpjjX30GU21VjGCJRMX7815qKaEkKBFi7VK/FrHcsBjUwIy300yKGbw7n440QmFpngWOhpzgBGe+DpPg5ik2YuLLXchH1CMH2w==
*/