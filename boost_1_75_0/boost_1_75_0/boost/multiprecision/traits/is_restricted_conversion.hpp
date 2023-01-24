///////////////////////////////////////////////////////////////////////////////
//  Copyright Vicente J. Botet Escriba 2009-2011
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_RESTRICTED_CONVERSION_HPP
#define BOOST_MP_RESTRICTED_CONVERSION_HPP

#include <boost/multiprecision/traits/explicit_conversion.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class From, class To>
struct is_lossy_conversion
{
   typedef typename mpl::if_c<
       ((number_category<From>::value == number_kind_floating_point) && (number_category<To>::value == number_kind_integer))
           /* || ((number_category<From>::value == number_kind_floating_point) && (number_category<To>::value == number_kind_rational))*/
           || ((number_category<From>::value == number_kind_rational) && (number_category<To>::value == number_kind_integer)) || ((number_category<From>::value == number_kind_fixed_point) && (number_category<To>::value == number_kind_integer)) || (number_category<From>::value == number_kind_unknown) || (number_category<To>::value == number_kind_unknown),
       mpl::true_,
       mpl::false_>::type type;
   static const bool      value = type::value;
};

template <typename From, typename To>
struct is_restricted_conversion
{
   typedef typename mpl::if_c<
       ((is_explicitly_convertible<From, To>::value && !is_convertible<From, To>::value) || is_lossy_conversion<From, To>::value),
       mpl::true_,
       mpl::false_>::type type;
   static const bool      value = type::value;
};

}}} // namespace boost::multiprecision::detail

#endif // BOOST_MP_RESTRICTED_CONVERSION_HPP

/* is_restricted_conversion.hpp
QMwno9P0iSMZuTdNTByAo3x/aj/fcTzSu9mJc/82/NOFpv+/BtD0/7apje87zAK03Mgl4WQ4FceOlINriuvsDU3pYN4bwqmSKjorjsEFehlI3qNvmaSRCeEdZu2DP+M0MnpAuBHhMamuZ6Wxi6M7VqbHFTaUOQgm3tdTeSOnkB0BkwaiHvQwPU87KRfRBXenn41qOoCBz/rzGFrKCRVkFZvVFbjfOc+N4joHZkj7PJAaEfo0zflvrrHqAdTf0iFI5M+uYRwYuzOXPyaUDw6xjDZth4/j2rF1ZKshWWHCOAWCEtgSkNkynaA2lif0m39CqPXsHz75onHCs97KjiEYCaz+vRAG5iHl3KN8GxgHnTnz/SljfTfgvD7WNxT4f5bdl25MNbsyMBRupIwPx0wFPSo4viXS/Y+k2Mqa29aP39taTsiQheLj8Nx3vNrmue/E8QprUZT/h7MgRWR1+wB8d+m3Ra39P5wjCbwOrgB1u0ofaFBLGJlMOVjvskr+HdHw0of20EuTNffSlHBtOpm16WT1ZugV9OiiXqBh2s1zJvd3A/UXBxpmMmrxMEofDPX48Qp7UQt6/kIeVZEN9Ud4oO0AVh/9H8SL9G7jKnTdAPFkRlNsJk2AM26lOSpRfRK/OekAaM2Ki7SEbaQMH3Mt3Ywmo2Mw4bWhCa+XVunXbK5l7E2akQiajKv0cWaLeL23mdeCAjQK5EM/4s55
*/