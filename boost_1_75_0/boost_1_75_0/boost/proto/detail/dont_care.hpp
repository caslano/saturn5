///////////////////////////////////////////////////////////////////////////////
/// \file dont_care.hpp
/// Definintion of dont_care, a dummy parameter
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007
#define BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007

#include <boost/config.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        struct dont_care
        {
            BOOST_FORCEINLINE dont_care(...);
        };
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* dont_care.hpp
byE3Ci1pivixFsPjB6IKZalzcVPfHkhpTJmyBGzLepP5sx0VGNcfKpHLR5jn31SYRxya3f8yMxn27tz7X+Ug7J2iQHu5tB9rncDDx17XmI571uznRG2IjifOd2Rc6ukLXmaurVa7J8uduM7eY9KJcSuwmHYm1+QxKRUnXna3bPdBOkyQYqpfwQ6iASyI8Z+hqJNmwWfeifDyzzBPacXg9jUFrQl5LGSf+7GPXwrX1xTA+5stoH/u3KYXTYTjmmmSUAT1c9KFuI8zvAkUh+hqClK0Y791B6r30bhQbdb0d/VeNIISWKOUhhRs+5loCdg0Jsw1jcHp9UBvvwax+xv81e3FzXw9hxhCGo3nAbY6zXW2RbVogchoVEl7atmoHxhn73T9z2113zNtnhMIF1XlSy+uUQ3/rPt+9s4KZeO6XSt+fco9Rzw44X3AmXBu6pF4+EmFpHB+qSKLaLB7WPk7Wp4AbZz8/o1wQubXQzkd7zhODl8Xa4qA33Opz/r8zg4/trIH8/ukjPMxDeXk4xH6mFbcTiwd5xyf3rLf4sDo4My70LVCPRihq3lA1x0VTFoimLkxynWu5Vjw1s54Rh3GBheEY8DpdcUbMzchmz3dS0FZUJ7pTWk/RcrQB0AYv2VxS10Q7y5CCE64O7LOzV1zCFDNxs7GDql0VJ4gfJXgbTc5qECjXUvpgL00VlP1JLaIckDdctUtodoJgo26
*/