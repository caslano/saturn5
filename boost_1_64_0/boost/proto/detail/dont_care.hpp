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
mf8q6CpW+xCarhPLGWD4VXDBQOsA+cE/Jx5TjPi9zGPe4CWkHMweX3A1y5XfunZRlgPIuYtFF8ns4Hn/pgEWFjCCzjoa10KH61cUPLlgtum1a1TNzg7BaT716OAIlO4RnR6VwGkMMt4e0kF/Z143moeeMqlAYcybgj3n+Nx506hN3IbKqVD91+dOnFHgm+6WYrosjSeD6xH5wPtieVqOeU298w0j3WsIruWN+Y+58kC7HB9MobHksrpO9q8q6GrWqdBb4RsWKSHq6vzCwpdXpIJ39Sfn9/DaWsqotpkCUW0eQt/nMO86WIwhGodtyBtD2/FwH1rbe5Vith0kh4o0jm+62/kxfR6YxjH2DvR8m5vwQHQQG7Md11zMaH+4i8BkzN80gyUhZYme6WPXg7LpDJXmIv3Aa8q5MG3bqrb9z3kLV1OcovFc5Dy6BV3HRGi4tZ2EuShRV+Xs13TYFmNd/Q8pLcFZL+qamw5jTD/hMpzZJ0cHJLTe5Si7wyTvTLb2yjgNr6XyeaTSetvGvKAvHPkZ3pLCcc2U5lL3Fu6x6dHMXez4ADhDqGCIP3d5Got2plss13eZ0nl4b0JTK1HH+l448n8q6uuYb3tTKY/1ReVl5o+TSATG8PF/806W/k+U1iO4rjjXKvYRK6X5jo8pbB2YEk50nod5vdO9oxdBnZjymNa+oHNhE6rfCRWYcjSSYaz8qcL9P+qrkVUdnEtx29EbOt4fV/YP4gW9MwWOPJ/+bIgf+OXXFvWpVil4wTkd+6l+tajPMKFaY3vRMI7u15NTcrvg+kzC+2SYy98Va6fWtVKdEez0dOQr8oeiPstUZWsP2dFEXjXpCDo9mWyhU1u8G14YDQomRJd0l9fRtRO6tu9EJ2J+ppG/4T0onKhZX3dt6CvO1s4O89oEZ8N4JOQBTpJGvCyIHy6l84jed75ROta37D3ymUWd4JOpOi6t/6/qnAzr/m2UDvcsjmrfNUIznqNkTsDO8mD/efNIjut+9rQRj6YLB/tXnnCBZV3TU49J/Ge4ouFZPdpf4dl+JZ/tyaQ3nfDTGIJ65flIY28sh0V+KJ6nuY7DcTnmskR/jikth/jUA//wmoUyiAQ0v2GiO0v2jZiO69gH9dYUy08X2xD5h6H8JeNyUIUR/FctlIui/A2L5S2t/22L9CsnBrv9d43LMVQ88U34wAJMcgiaEp+Mjy6XiUEcjmBD/Oj30PFKwvfzLuLep+vLM2OEDa1XDLc4DZDs8F2e4nDBmrrVrZDmv+OVEmVqT/I3pIfyYh8aWfG5fTH+R5dnKzfULmnn0Xh/vb6MydxVPqiZOC7s4VHGFn7J2/0dS9wgfGt1zRlc7ZjVPt3tpX/ovSneI0XtjVEtZ+5JVq5pXsI+mMJeEK6zrg8dgyTPC7nJrqGwlzRkN+6VZ1Hm0a4Z6fUuU9jLputDb4Nns0fh8KQNpO2wr6KA57XrBOfNbJiSDvaaRzwVwxdTeTpQvFowI7SWRlczvgWw9w8Odq5ODoZ5qikZhutuuxxr0cg6iIrRqNyIc5Dza4/q9ppzGYRgwFKc7M+YrwKZ2HW8rsCtmee67rT0eWFQGthgsjY+UMxxZ1TwVvG0QpfY2fn8flLUG5gTIq5ulxZV4rRhRT2cMhHT0+gTMTIVWcP9Sunxium2UcHW1ZgeuWPSmJ4exU5CWl+kONjt/pzShCZ2wqhOzkiun23B6ykSXRr39w8lft9Y3nfSzPDRsLXEH+XlofLAqlZd3xvYdqv4z+hN6oYUnmtmu0rwWrTDbEQjpaj5AOflF2dWcHJIOBeYoyrnh3tDmfOpDpHB74GaHl4jyqZPc34TxMUcb6rTVqme9Sn0SurzuXQ=
*/