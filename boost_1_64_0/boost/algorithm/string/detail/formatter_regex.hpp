//  Boost string_algo library formatter_regex.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FORMATTER_REGEX_DETAIL_HPP
#define BOOST_STRING_FORMATTER_REGEX_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <string>
#include <boost/regex.hpp>
#include <boost/algorithm/string/detail/finder_regex.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  regex format functor -----------------------------------------//

            // regex format functor
            template<typename StringT>
            struct regex_formatF
            {
            private:
                typedef StringT result_type;
                typedef BOOST_STRING_TYPENAME StringT::value_type char_type;

            public:
                // Construction
                regex_formatF( const StringT& Fmt, match_flag_type Flags=format_default ) :
                    m_Fmt(Fmt), m_Flags( Flags ) {}

                template<typename InputIteratorT>
                result_type operator()( 
                    const regex_search_result<InputIteratorT>& Replace ) const
                {
                    if ( Replace.empty() )
                    {
                        return result_type();
                    }
                    else
                    {
                        return Replace.match_results().format( m_Fmt, m_Flags );                      
                    }
                }
            private:
                const StringT& m_Fmt;
                match_flag_type m_Flags;
            };

        
        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FORMATTER_DETAIL_HPP

/* formatter_regex.hpp
iaJE2aOJa+nHdCz9f2qEr4zkoJcennbdCF8Zx39Vx7Orlej98YR1HA1kb/JSV4qNeKorE9yTXUBqcWeQa2l/b+xhTwoO4k9noEnI10QItmf0ntENSTEgSd1dy10hLigBfHBihkDOGpC+dIDQYcxMNxwlifwgDvyDtFMfiPDOQ2ESXvImv5ZwQk/yPH7TqTLsRr7IraW880GBu3QwEfgHdn413Iuz/i6IBVKXe9EQShm0hfeGLvZYjXgv2kJkvQMc/9C3s/wHe/U5fH/au1g7MHovaAhL55XHi9828uN1PVVoLIGuxQzQ1RzMseMothyxbjYrQvwFiMeolCfmft/rSByl4K8Z/6eW+q/wNE2fOxlTlMgUp7Y8Zaek0o6MXd9tJMG6Kxvrif6PrqNl78ArTPfqBX2yLDkPjo98q7lDm+2soVqK7GJs2BYRu68JXACJ2xb4gu+Q8Yrrl314ag6UfPwk5+nHiU3zfGQ1AFVThADrCOK1tbAxOFk9+h3tWKt9uLiEy3CThJwID/1xEeRsVXNaCzl8C0heqi9M4M1mOmDXjxPR8hcAJzyW65A8nc0mtcjKYxpV6bR4qVQN2oXeewqBFiQTjngSjebFtXMHB9tIVVPzPCLwsETgAs7xKufginMToPaoODcAYf7mVPNpMal77TQ8ZYpaY1Jpsl9oJTZPj/OeK5OufwMvOBoVpvVG+sbZ2DNECikCKDtH1WYWRrWlP2ovB8sR6iNwSmg61F0NdaTXSCK9Rlwaz6EDFbT/DV4no8a/ts4dd7Ie+1PTxQMXq6K+pmdHwIt42NNA4QHHr2GJv+Zz0bem1mkQ0tHwyXz8PyBS6xRvap2WowmN9ej66f0Jc2iFt7BWvdqaR0xXVo8PyXK80rFH9uqiHmVBnbtcRm/umPDoXaeqWrEbgHUx+iWVBxLw/tT6iFxLJFdyRK5YdZ/kIsdP/HDLXATkJYwlJBvtnBIfU1sE8hxzM1j6HpmsOjN1OPCl3XiO9s6AA2F9h5j1YzxsqUH1KHOnypAdCSSk+qpNpXaBBtLSlr1vacte3UVNMnfj1DijsjbJW1gJpdmBYwuWo8duXDV5L5V5pnDMcztHcMw9wjE/Fb95fmNimGPuBjAzudPVMnSUh+yYjWr9AAvUce8RXvV0LIwFLybm+ma8qDl748k1sNWFuk9rpE/7FIb7dK96PU4YUpzFEgM9gJlJ9ZN3AHQWRmrC/hD3CQ1efu+45iWE6FXkxfp9hzGxrNZ7iTSheWwMY/IEsvn4lia/+CQAjxGzIFD+FqBTNY/Jkt6Po5PXZQB+vMKoqJ0o6tszSfzah74W7e3U6yzt7XkfifZWnrwLsdoIxRMVIEH2Xup+KLTg5gTknebPRuMFTiSuRcY6l07mXUeCKPxiZU8zgl++4TdN5Ij1mBqgmO+72k/k0cLPu8q9EPVaPDtq3GcPpJfN1708WBRkw66l8x0bL53rY8MPshbviw+cpHburgvRu8y3UI6hfOJGq1Stu7i8vHj3+bcne+mUGpMtLcbreGrxbQOC7v2Y2JP7zt5jQ0LRhcHZBaTr2m2f3JNQjGcUj8kA21iQFMPkyDszV0aUzs38g1+GjZaHdnbi9uCXq8B0i5IEuX5Ud2CyWvGNOV58BdZ4id1Yh+FljpiFGGOS47DybBP7kICU7qbZ+gF04SoOTaotps7Wjyqf2JOPWbrkkElsFeYJ39nZVKftXbqCPqOSBt2PsnlpXl//fkdN33qsQ0TfJtBHRBmtZY+jH944rUAklRPYG1ORyCkJ6pkY3vn0BMsmboDNDny4qjvTiPtUeuXm/UmbzZocj/gf5+TqAPuDTkI/iSzMH8yX6NVnkDkOef4=
*/