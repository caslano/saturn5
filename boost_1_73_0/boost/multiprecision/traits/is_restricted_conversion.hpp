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
rH9MxgHtQ2M8BhjZ4FjY/1Xf0Jj0fe07Y9pfTd3gp/ZXf9bMfQdydEvtM2PaVwOT9m2Qc4ZFtn1M+qnIdoxxHzWynZBNx2S7xrhvmjhuMMbt1fBGKSzLwjSOjWl/tHncPWb6o+03pKOHfM+Y6YdGvpfjjMv3jWn/s/HuHzP9zMhvzHri8gNjpn8Z+U3GuG/F5AfHtJ/YeG9K+nvID0Fu+onIbwa56SNSxoe9HLGaPuhlYZWL
*/