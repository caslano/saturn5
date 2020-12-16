/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };

    template <>
    struct is_sequence_impl<assoc_struct_tag>
      : is_sequence_impl<struct_tag>
    {};
}}}

#endif

/* is_sequence_impl.hpp
XBghb7cweTOD5Q2Trds2doL3SrY7JdvKk9xlU4P9S2Xzt82dpfT7oWR7V7KlTXORrYrHzMpVqW9TPuti01Nb/UYG9dhmW9v37KppweN9p29WuwjRBZmtMg5Vsx7k72dnOmW020RevWXSGDQgv1u/Fd7Pp5h3XePg5jon/ZmxaWHnz6fBm1/qi/1baK/P5elbGFivC2lzC5TnIdIvSid0IfLKkDy9fYZm9R7SN9vb94gc76GD4uj3m6ZYMniDbALotzH8pvmVI5t8WDiyB9dPdms7g+20trOt2mDOqbas5fZMod76cZkzq45C21ub0PYW0lZelyzd9T50kSw+W5by/Eqft6iwxFdYUf/4bEPeT/+674zt7QTf1Dx/OeFz2k7aRZY8QT1wbGs5Ye1Xzy7yG/02mU0n715mXeWi2L7R/jpM1oH8s/S+naqxZ+bFVjoMA6t9ZqxR4ItdXo3/wuftIe2oTvkWac6cD78wa6HB+Rb46l2HMHnkOHkG1h/GWs+RBCLXD8LWHYrNGplVj82QaSmho/FjfonTZ6WFrkc482eVpd8Okeetb6UxLrw0xHcH6/5ZfYfFeeb65i7uflSW7RB55jq3PfXnmqfcqMRx3vz37SP9qGy+Hj8qo3aMPH89F9nTLnORJ84z2Dd3qf8Mtl+Ouh0jn8Vx3OALyNFvwNBh3pzBGFaJ99z/qG7u5/5zd4os+2jiznHJM95z/6O6xV72pTtFlr1lV74jATn6Zw3KGtJ7oHdQ7yOy4vPns0Nr93aYu3Nk2VO6Ema55Rm/35odYrB74C//yp0j34mv6FNyArKELLWO5VR8zHK8niE5XPaWKsLbwy6Rz+Frs17hJke9/rBSQ3SFc60889mqZDc0/Pm75Pu9mVO75Rvn8/82w/35j9o1ss5/NP24a57x+3NSvYf0Q97W0fuhVbu6t4G0y93kic+fUyxtwF8vvraR78VPGfzuJkcD3otvM+p/L/yyrEvVet3mxBXNN36eLYu9e86AmpGbs9JSactSs95vbwv7W3SdvpXsB397tfXvPQcO6tzVo9/udH7r7P/tHOe3Tv7fxjq/dfT/1sf5Lc3/266B3zp193/fpwaNAbR2rm8YJdIipOYvgfmHy9ggzGYWtRA0bzmqhzU+rozU4bYyCDyHq6xn48svDptblOzmvJ/Ntd43gsYx+kb7OfjMMD+OdbbhrUPmFvp7TMj4bpnynGFk1jjvOOLV2nlKicEbl+1Btfl/pS66u855dB11d53zaDrqCV30v1sXva+li35E48MLDvj02XvyV51+4FkTjhzYMF30VI90dqTLMz3sDHnTJNlKSJIOjXRrTLx9zLxAekCzKEZbeLVsWcyBXeF1sA+8QWehb4Sl8CZ4IbwZzoK36mz2bfLrMxfOh3fCJ+Fd8F04D/4E75Wu+HzYXbYjjpTtiGr4ADwRPgzPgwukI/4YvBM+Dh+GC+ES+IT8/iyGq+DTcAvK+AzsAJfAjvA5eCh8Ho6HS2EJfAlWwpdNvvAVeAl8Fc6Dy+AzcAV8Fr4mHftuHunewDTVfzI8QPX/ibZOVssWxaewHfwsyIbFWt0/QvcH27CoMP6KYCW01hl0RqAa7gEnwR7weJ0VqFG6aR7pz8CtXM4oEGdqE/gtbAm/C7pv6nru+1H3rdN9P+k+H2GO7puo+7aABR7N3VWOc9TOzoX7yHZKB9lO6S7bKZmynTIc1sJRsqGSD2fK5sRFARsZ0kmBRco32EbGZNmCOBl2hKfIFsdUnamYpvRPlW2L05TP6UrfyLJQ6XdV+k1gF6U/Qc+3RGc+SuGusEw2OcqdepXeCN8Vl3r9QvX6JWwBvwq6L1X3tXS571fd95s=
*/