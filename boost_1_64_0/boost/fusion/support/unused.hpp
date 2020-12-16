/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SUPPORT_UNUSED_20070305_1038)
#define BOOST_FUSION_SUPPORT_UNUSED_20070305_1038

#include <boost/fusion/support/config.hpp>
#include <iosfwd>

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4522) // multiple assignment operators specified warning
#endif

#define BOOST_FUSION_UNUSED_HAS_IO

namespace boost { namespace fusion
{
    struct unused_type
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_DEFAULTED_FUNCTION(
        unused_type() BOOST_FUSION_NOEXCEPT_ON_DEFAULTED,
        {
        })

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_DEFAULTED_FUNCTION(
        unused_type(unused_type const&) BOOST_FUSION_NOEXCEPT_ON_DEFAULTED,
        {
        })

        template <typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        unused_type(T const&) BOOST_NOEXCEPT
        {
        }

        BOOST_FUSION_CONSTEXPR_THIS BOOST_FUSION_GPU_ENABLED
        unused_type const&
        operator=(unused_type const&) const BOOST_NOEXCEPT
        {
            return *this;
        }
    };

    BOOST_CONSTEXPR_OR_CONST unused_type unused = unused_type();

    namespace detail
    {
        struct unused_only
        {
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_only(unused_type const&) BOOST_NOEXCEPT {}
        };
    }

    BOOST_CONSTEXPR
    inline std::ostream& operator<<(std::ostream& out, detail::unused_only const&) BOOST_NOEXCEPT
    {
        return out;
    }

    BOOST_CONSTEXPR
    inline std::istream& operator>>(std::istream& in, unused_type&) BOOST_NOEXCEPT
    {
        return in;
    }
}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#endif

/* unused.hpp
CJsR42JnuU9k4fdXNp3yorWxC3kPNyAn6vvxmiGdM9U/d2e/LBqzT8xzG/ANgPgsUUwLaoMHWdnSjX2GXEwG4LsT1SGJ61INpRjHfRNsuXvm8U0xvx+/H+WizaG3eW/6ZxfyU06wQkxKelcvk/eON05dP66AHzri5STzHJkQsD4vvv5XEC7E87vV8j7XeCdV7hjZur41n2/fnrQx+WBjlrldaxan2d3to2kbfzYZx2iTDsJ0i+2wGEOU+7qXvshcWXPSze5vfot4A0lJdTWpPsiHTh64BYOcn7e3NfdbSeWgmHOEN/doh/D9ifA0MVwr6jsxruen7LCNT9oDPtDepXEbOi8iJ5twl9asQ4/+AF6HuiS4llqAbHTAnO2uMx963daViI/G0ZT8sou3jy5eWi3XpDz0fI0OPAydyagPWbpEmOpPWci3rcUoQyFkUomXra4+DCwQXr/ZX+nDmW+n5XmOV6qjSpcbjtf1Jy3kN4RlEDwZa31AMvBTZHgPwpCRpkypXMggOZt8J2MZusBDsJo1MmzOZPgyqt+YJCmLfCHD9uZrJ/OkpWWC6GCZ7CIeiLccbhyU27KNLaynP0M4XXJlZRdiORaKTfzlcF+xxDpddk2AWbsE443087cIw3kpbUiqyNK/x6G1HveVpPXy27u+ryrCfLz/gurnUpvIjV/IkKYy/A3LYJmWKXGKZOCnyHDugy1GYpZzoeJChv2pDHdpaWvKIE99SrGRYT7e51uey4x3UgRrSBD8EtyhwPfcB/F4p+yCd4ohIc4Y71WEI3102UlOrm9tAg7cwZFCi/xKnVFd7gaYSyvPweMNe1HLt5oCDdVgZfnO1Ah0Be7ocX9Z3gXaCb/sr4LSjjnclWIe3XVR5hgXgvRPSrM4L+/B8pQedoE5huQ5bexvobF3KhjPgyYv4uXd6/IFPPZfxu1iZWGwrAuNLPOx/yGqv6uPDWUWksPNvn70Pj4de+1VWbICEgKP/ei/W9ZdZHekc+w6WQS5VIHab9wDeCfA8nSSybpCEirX+7WLX33Rkgl4/tDyeMK1VGW5y0WgHgdW4ZHnLxjHG5Y1Z65dI48Pe5wnDvtmy3OJecti5oJ0cUm3Cm/zH8LzURtjM1W9DGWyNDLA23zLU7ScRetjJq8vR9QbcFJp3+YxBvNGUGW6Zs7P23+h5bnkU5Qmk/UIrqZwBzOpW4nOUyNr+3udGtsPsQ5anueWaa601/WLfRnaBe+xk/6xInJHNehs23awSWt5VjN1sehhLDeFu8cl4cfoXwpnxkKP4vrLGLhnYnk9UZq0t7e7ARsVjvN9q+V9dpAh8iQZuVlY8T3FBKOLoesM9QgDFke8L/wY8TKibeiyjHz5kTE7+cOZ/dcTzPpC3CnLESZMStzePyHejnCuuyKYrKd2sVtN7l57s57B8z58LgDvuQ9PvwGVF6FuMjfeurDR2tre6r/jZ3G7ziPeTGTZxjsaAz6/ty24stK3Ad0FEFSPJkqzxJhLhN4oB8ehFfOrDFj3W35PIuUyR8WXG0XMdbNYmX4/HLQ8l3kUmnKVSOgU2E6sDDp6gusvxGUam7pHrKAtAuKSo7q1LMuqNJJcf/3roG6IHXFrUncOdPEUWipdr83P6+uzM+O3W56VrH1n6yvR8e7x3vb0e+6HLe2a6jpnlBOk5BwtUZ7y0dEszt+Xb0NvwNlGzUKuF4wlGmljWNHsuz/78OTdmGlqZdes7deu9lJAu378MPTeSIvgLmfC6frVlWYDobB/YAzesbK8BNWs6ydFrTDGH5DsrH7NRFGu0zaOjlfGzaPxXccYxgulmPLN+jiX4x8Io2y5MSSlejngCD9i3OUjCENpkYKPplk=
*/