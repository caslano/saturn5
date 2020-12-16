/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_10022005_1817)
#define FUSION_CLEAR_10022005_1817

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/mpl/detail/clear.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct clear_impl;

    template <>
    struct clear_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {            
            typedef typename 
                fusion::detail::clear<typename fusion::detail::tag_of<Sequence>::type>::type 
            type;
        };
    };
}}

#endif


/* clear.hpp
l/yvYozOy0Y0HJ2XXsj4MRvt7ZdapyjYPwx/620MafyL1tN231TndTaP5xwzOw7niNtf6eKZNjvl6xJaX2lunGGtcAnWfN1B6ynNGal4C3Sf11J7Z78Ff1dOUx3pPJnp1ezs+7LXyPpZC8/c9vdBIyuauJPDkZb9XkvzfSe0vTH/d9131uEb5Vi3ThT3saVd4OJOlHwX+gCz7EjRfAvrvFLX8+am1qhD5LRus2Y7RHF3tHBb5rhT5PppSp1/X0M5H/I6OzxVaBNKo8IWY+gkNOvwUPrQ92hOLuctwO8xjByQOaxuwPFAy0zPMr5JcpkNmJEOCK8RWp3qjdqCiCd32DA+wcwUDJO2IwqJ+3bDpFaCsonrzjrXVdlYzltUsg77BgPH6jTOxxxRWntUfQ4Mt8fUZ/dOmhlVn33D2frcNoytz/yUZsL6LBnd1ueGYWx99gxj63PLMLo+c3fW+qj6LBqO6xNvQ8C2XVWKb5HIv7PNL8GnqXnduxIYG5b839mFqKKfv4PXAscP/dwdWff93CL6EWhw/BbRJxeh7djPbTOn+jn4nePQ0UTQB7Km+sDd2PeDrs77b2Ls4iqSv8sfhE7OIZf/Fv4ef2c3QZ/L7+zCR0ZafHULrXhpr7EDyWsXy0rzNcv+RjemUw2TVIWdPDZljtEbBvRdsYlyg9yOdnvVMZgbrHiGqr/uH0eBrd7Xa3iP120ZDXuHKtreKhi30d9CmdSzv1fbjcVztGjSYn+64bXAzy7x393QxPV9P/936gY5DeJtSNZXG4sLq/7TEgh3o+X19FjoKup73f+d2lBrucZrOqf93wP/sXQ2+7v7JJXPlNCTc5ne5nTKd/Hv73W0E87D9tou0iYPTWBV7VZjMuztX1zW63rSijHwwV6fZQ9S/r74EOjsRcp35AKdcs7ztA2ttYPf5p6yy+vwCvkcntWGHhefJ5I6jITDfir0NGCxJ9kNNLke1nwaa9La0Yf5PMHapd/MafIJEnOzh6a/K43PjJNV0Xez9RvAvQeHup77JQ8zOhW1WHfK9LuEMYi++8ERRoyPzVgYFIvsG+afsStj4Ar7TgZrlKUXjmKoo5Fj+pKPLwxJnKXPv8iHZUPiOevxNJz0jVl/v9J37wjndbsyxr9l5gF5xutNgiH/I8YkF78cMzoq3rd+T5aemWPHS351Wrzj2/+j1enKYbtC7+HR5UEqALF3+SfJylOPNLfAHFYza03uT/P/kJp+w6T7H6npdYhisktq2uc/n9Syy4hLCxXaiSa5jnZgOT+TIpA4tLsIR3c7a8Q0UMeWIdOsVeU5rp5h0o/WudFCpmuT2nnA0c7/SttfmEe6BiY8ZJP98vNbZr11ujZsiyLO/AVGck2ZtsEojoYEmbZty1Vry2m7QPk/3OSzVuEZLN/XenSMO8UktUfk94ImXmdN2fyghfqynK/SZAFnBR5r4iVHg641N9bo3FBaJ4QdwzsWF9pl+Ab1Bd7NaNPWXXmp0VojdA42bX/jmo1b+uM168ebdND+lkpFOWPndXgnF6hq6IZWNrbSC3jcn24p1ncTtAeZiLlYcmHFuN62gbjef9lAo/M8sjnIN8Q/aVjZDmtYTxjNDX3arG7yT5AcjsjoBkRtLeO7zxnJy4a0hvZ7EZnvtG34/b1TaGsXlYwpZr5DcDHFtbXdM5e3HJeR4AajuaYMb+PiluPKYW7TcNwNyvd35i8ZcqPbN8aa4De+ffOY/itfL/RhYO/OZz5eHeORZcxuEtpPnMU5Z5Thry3HCyjMJb+Jct5nY24jxvFkuAyfPsJRY+S7Gb+1entEXjejrM1rYTvG2byWopzN62acs3kVHC8Ns174tNArC3UfEfQ=
*/