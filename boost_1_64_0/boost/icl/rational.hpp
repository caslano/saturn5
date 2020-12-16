/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
itl_rational provides adapter code for boost::rational.
------------------------------------------------------------------------------*/

#ifndef BOOST_ICL_RATIONAL_HPP_JOFA_080913
#define BOOST_ICL_RATIONAL_HPP_JOFA_080913

#include <boost/config.hpp> // For BOOST_MSVC and more

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#pragma warning(disable:4512) // 'boost::detail::resetter' : assignment operator could not be generated
#pragma warning(disable:4800) // 'unsigned int' : forcing value to bool 'true' or 'false' (performance warning)
#endif                        

#include <boost/rational.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/has_inverse.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>

namespace boost{namespace icl
{
    template<class Integral> 
    struct is_numeric<boost::rational<Integral> >
    {
        typedef is_numeric type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<class Integral> 
    struct is_continuous<boost::rational<Integral> >
    {
        typedef is_continuous type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<class Integral> 
    struct is_discrete<boost::rational<Integral> >
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = false);
    };

    template<class Integral> 
    struct has_inverse<boost::rational<Integral> >
    {
        typedef has_inverse type;
        BOOST_STATIC_CONSTANT(bool, value = (boost::is_signed<Integral>::value));
    };

}} // namespace icl boost


#endif



/* rational.hpp
mA/iywThNYDouEBw30FsvCC0ShDZIxAYHohrAYT1AEQ1CIIqBjGFgpCiQESOIKA6EM8+COcFiOYyCOYCiEUchPIVRCIFAhkAcbwGYciCKMhAECUgBlcQgi+IwB/gvwrg5wDozwHwgwD2QgB6QoC8NAB+A+AeD2CnAqgzAdDPAcxVAOR3AeKNAPBagHc0gHsFoP0BgM0HsDYGULcDpKkB0NMA53cA5msAZQkAMhbAeBhArA0QVgYA/wLgawHg7QHo8gBwfwLYMgJoywGyKQDYmwDXVgCrN0AVF4BaAzDlB5BSAERHAKC6AE9TACcNQJMWgEkEsCQHUFICJJkBkHIAx1cAxiqAYiwAER9gWAAg/AEQVAMA9gH8vAB8YQC9JACePsAuEUB3ApDrB8D9EuCmCGDbA6iNA9BOAczGAGSSALEEAJgBwAsbwHUdoCUIwLIEWG0BqHwAUl8AUGkAJ3YAkzBASQyA9ARgdANA1AQQuggAcgP4RAJ47AE6jwE4OwCbagDNEUDmNgAmGeBiDWBRAKjUA1DYACYyAJIcgMgBAOQ0wEMLwLEO0DgDwFACWNwDUIgAJJ4DIDgBDh4Ahi6AwhsAwgzAYBtA8BYgkAEAAJxjYgoiCBOVgFpMTAM2MZEGKMFELcQ9Bm8Qr5j4gXjF1AZAHSYCIVoxtQFwj4ksQC0GdxABmBgD1GAiDGIOE9OARAyuIHoxqIRox0Q+4A8TixD7GNRDHcBEFuARg23AMiayIQoxUQsRjok8wCgmngCzGGwDejERCHUGEyuAawwCAb0YtEJcYCIfohhTI6DaYGIfogsT6xDFmMoAsYmJUKgMGNRC1cBEB8QYJp4ghjD4h6jE1CRANCZeoUph8A2Rh4keiG1MpEI8YmIHIhlTeQDdmKoBNQNTH6ASYZAP0Y7BPMQsJnqh3mAqGtQdTB2CaoaJfYgiTKRAbGFqFcQppooB6jHVDCIZE9FQOzDVB2odJsogujGRD5GDiXyocpg4gtjARCREOibqoDJgYg9iB1OBIFIw8Q8xi6l4UIkwdQEWJrKhemHqINRETO2B+MFEI8Q6ppZAlcLUI4gpTLRCtcHUP4hATCWCKMfUAqiOmDoGtQFTA6FGYqIVIh1TeaACYGogRCAm7qGSYWoYVB5MfEO8YioYVA9MjYNahakBUBEwNQfqAaZ2QGxiqhTUU0xthWqCqZpQCTBVFeoFpo5C9cBUOaifmIoI9QlTt6AOYmodVGJM1EMNw9QIqCaYCgS1D1NnoD5jKiPUOkxFhoqHqRVQrzH1GGoOpopBrGOqEVQLTDWEmoqpylDDMDUN6gamskOkY2oBxDimxkF9wVQkiHdMDYdajalUUBswcQ8VDlN1oFpgajZUYkw9BomJwKGXBjuRw+5yAQR8grfHg+VMYLd8A1s5gixbwVbFYJdU+Jac4XDiwbejA/LJgt0dC5bZg0Nb1QWQAXvlwLcfCfLqBznEwEfahUN7Gj5ePuCBA6z5GHbbK/joSnBIJkBusnAYDMDyI/Ax34Ltr8Ju2YGPGG0JMAUkMFACzOGQ2oNdSkGSvLBrv4DVggAdvwBbacAh2AS0pIP874LslsFizwBXLzMAcGDDVdhFviABHrCFDci5AGTMDRa7DFbKAwm1w64KBowog50FwU5HIDsLwKEuyOUJ4OoKWJ0A0JIINiKG3f8I0DEqAxAGXPSA1DdAUuxgxzlAhimghBokJAkyFQM8+oN1qgGB4yCNwWSAOeBkEfAVAUjCBlmtnAFog61/BqnRAQbKABUOIN0osHQoyOIcSJIKLB0CSFYBDJ8FORWC1AhBnm4gpfNgAx9ABTNYYwEkcxvwNA3IGYNDKwEW7QS7/QQ=
*/