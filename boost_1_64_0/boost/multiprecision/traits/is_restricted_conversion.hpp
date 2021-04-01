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
gl4ECSuBC+nXHLfMY9vvaBCSZtVlfAFT68nxgVAsQPEhylAcpos4l/pke7uibvGGd2s4XrrTyGOghwlntBY7auvEFPXcF4XcQ+aBcyUUqwcvGOZq3ukQ8uc7tMqyNFAu0cHpUDDEwQeyeBjL72Hp+xiuL50WcEMucgUnhrwritX2ChdpuaixrycnfmxQkqxv34Ph/wLKLcjfbegQhWIqHxf7i7lJ+sPE2I7Beaax53x5ZcALcGzcDDr5xes32a/k/qs/Ar3sj4eEaBqWDB4VqJYvSylYUWkkyCCvqFaiSZchjU41WROAx51iUimpaMbuGC27rfoViINyhnD87/evLn6GM4WBXRAYoUCseSf3rkGTvGWqcda8Oah09GkP4qtEoycKLEww+ZeLrQfM5WO9zy1xvlu30oyUYRXPJ7RwDoW565HapG/ip/iUWCJ+di1L+lLZxEMf4vzDpeTqd1A736L4ilWm293xOY7gKtobP8AI7wzGas8k5jXqOwfhJPK0vFYkzymlA4TZEkuQDEXFJsw024dULTs9P3GN8jCNQX6F4pLbCbhNPoii1g==
*/