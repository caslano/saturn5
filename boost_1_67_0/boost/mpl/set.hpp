
#ifndef BOOST_MPL_SET_HPP_INCLUDED
#define BOOST_MPL_SET_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/set.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_SET_HEADER \
    BOOST_PP_CAT(set, BOOST_MPL_LIMIT_SET_SIZE).hpp \
    /**/
#else
#   define AUX778076_SET_HEADER \
    BOOST_PP_CAT(set, BOOST_MPL_LIMIT_SET_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/set/AUX778076_SET_HEADER)
#   undef AUX778076_SET_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/set.hpp>

#   define AUX778076_SEQUENCE_NAME set
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_SET_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_SET_HPP_INCLUDED

/* set.hpp
md6cd+tximr8dHzkOYieZwuocTRXdySkLE/G7LD6SH6aSIvTvBe7qanwaVZ2bRT82TZ2yzyKAeXeWVMHPmaupRygxMu9CDwJ7kiQ8kxk+gd93r6TA0emzwkYpSYUSqO4agVbyqMaTh8YPPY3dZLfLZYaM5t53sCDVtYtb/nVXk7StPRmfZzyI6j3wqezI4IJuJwhHelRZpVwfATNQGzi782MaxKHB8KDUW+MFRQZ3FxJYkuxt+nriQz68hFZ4DV7GBHzzsiiWc74bWe1yMVUkD9RDsRENYWl5FXmmQS2/KQ/i2IFvAnUlTpqPfuOr11Cahr4OeeISABOSP9gCtL+rXK9LnKCb8AlSd6HODxNGiFyG2OXkemH/SWUuYqKgvGvHaoi5zDrA28QJ9TmPYm+KpLE0BMuoW2C6e1LRyYSKnYcRrUmlSnhasgV3NFQIYT7epIJ0L6MOxjvKCtHhZ9vKthO1fqxM3TYTn/BeRFy+ugV6QPF66mRqJ3RlLNEqVR8WkSenDEGqzsa/DCfD6fOEIXvNXFiWucTG91hW364q/ZVwZE1FBgy4XCQIjWE0MwSe9lipdS9faYoHpM1trUv75UtzR7L9fT1yV5MmNWXy8PsYHPHLWg8+aqUHCFKqV9aWnUCi95yAJrw7CvdfK1qntv4rDds+80MLjOsHYifa6M31y1smNjRdhmV3EO6IIY3mmxoMNamWKegzl6hQnWvGEYc7edUoOWstLm9yDZZSSArDHLF9ENajvD4JlgzTwtDPyxo0gyatpx69zMorjNF65O5V2DOaZxCkF2dp8+v3FsqHUMEQYd5yq82pmaUSHbeEo4MQ4XzYzHTFUF+GprpfO7b3XlZb8bSCUovUPd4NDnnCLNIq7RF41DSzJO1gfQqasr5aYaEvXL6Lplit05CWvtsOOcaBC1TPDJVLWFepTJYBgcS/LXZELJowYoT6O0rtQJfIvsXtyBFVZkgP+cOy0MFtZXJ9qsAGdaPvgdzH9woA0eSM4o0MsuPMSW6T27QZ30jkkR+DIcNhAp2X2zSnSrN3qg9kFdQqC5N5yNlxLFTehPZgaeXsTNSyS2cJ+N5VOkLR1qjfMuZiEpwqhyY6KtSB0oeoQ5hYw7rdEPptZ2dCIsI+zrPjBNCItQ0f7AXZZRsWsTvNNuINcdlUkGhCzDNo9UtkVDIgfQWSzrMPKbtvIewcbNEJ24lF5FWC0vo36OoJsUWhCyeC+s29xxclOWdLTptCXd7S+l9yLPwah44MmYMnh/9KhPhY3gc5XnMGZmw6pf9tVJHUN7BWNoQRM2RKoB9o2EcE6lUWzS1kK7alliEDJQARn9tQS44FKKfZ9IQL8+OzrdA9pCsHbni4y1QN6/thbIqbc6GAKFU2GBU6d+apVAGjvK2lMrPuMY28vgVxSXzRM6X/NwxXiR0aoZ/2pvuxq8p6rYnP1NLb6uuWyLKrSYkYn5wqSjfEnZpgwlVu+Dv2GG3Jag+ozKTuQihVK1gqyHANUpQWJgJM4wpjw3xoSRsZOQOY+NS8sFrKIHvvYdrd1cV8NBSshuR0Ix6ixZ9dAAj099x0ktVPMCfsEtFYF00Vn4GBoHE/CIOw3Mk35w6Vs6h1dmiwX2lhR7du1Sf4K6or1WppTUoCBkpty3Lk+zxAiqzF9/b8vVnvK+qKdEUEg14V72yaXkOfVaXA+XUyb5U62lUQAHWG6PH+641ED7M5nMVKGKToL15DWaDi03Iu00SRw7/xd0xjc6SBJwNt+cYihnVrJ8M5wHCgvNG2ifpoXv7tn0gqDdzxt1vrS0YV4S6jMcmhb3R/H5ifPRC5ru8RMz+4KCEKilr7k2RUT73vgeyRqGKvYkXSfJIwAGo6bbGhbJ76cN+49DKLwaacPF4Ec61M9yt6t0SyBuSFO6kyKPZznS4FLbaF/KpkthOsKM9Zt9gwxvXDJvxqzDuUi8jUant/NBJazjqFGDXHVcyPrgRt3n0aBQvenmKFTKBpiAp+hM0N1lYq+QVvfLTgukzXKtYWaweCgYSjr1RXv0wKOB8l9036w1JnIw7xsCZMFi5usq2C2aP/lHImva2bsnJRYNZdlUZQ1k1aVFT7VZAFP+r/F4N6E1xrntfMsGexwvmzAlCP7vYprruTAHYQJoTOH+pch0tzO/aoAGczBjLjbLQ8wuWhEOgHJIbuL/0toaL0fHm45G79hT5TqqCYC5wY/wmmlgQ5quGb1Udg3rZOwSHH6Ib4H7fSpPTPLu3CJIzv0xbI3oyJOMkFT5M+1QvSc6It+ofH7Tl+7419jQRR3S/qL+i9Xmbjb95gOQdbpWlU0AHxKUCWpqzluZ5V58xahWHOhaXzh16Cau8DRTrFCqVlVEkYgkXAPJch+1gt6qx4MZINHXqW7SR0/tYZo8b80FJcEe92wfg/WSkuzPT3jUkOgGPVG7eSuMR9JYGOzDoVGbFVXGTjsVhwxovIjCFZ36ALzlSjAgXVE0hLDH2YoDWpNKyx+jIWyCrFcuCc60QCS5xzPX9puQ3NKE0FGS81qAjJo9IZdyyfZ1UgjGYVaCdb6wIPC3uRal5K1El64pCJ71wtwsOBwmHDeeWM+TzptjbKdTy/pDF7aAlKglv8sjchvEI9lG2I6kKf6nuVhQTyzwHRRja0d1/sTWvrK2Utb/4KuHxw/2Ch8GzfAk+WyNq8JOm5GG4eYpKFugDbiRfRx8szIcNP6GQRXupT1M+U5ZGwhr1eOAQ0KZXnf2VAIpnpgeQITVU06WMaAnpRRUpITtXGrPnsvjYl4j847erXJnxpqnOSZdZJAtu9dsZxvtFtkjmSAuV+K0dN4VltW/6WHYJDJpKD4fCEW6HjUkfTuNukvwUBATsZfQGBIAVGxIop0Ir/RZGhW06rbYxUqAqsxO9JP0gHdnJzyZfyFRNkLCiXrBD8mLEi1imIa8TUak3y64ncGi1OnMOJ70+ejpck7uDfHKXZwr8qsyMs78xflX5PEfyUyKywq5TvAku31tG9QtXC3PtD55R4mLjgnTtysXJw3ziYFoseOyGJk9Oug1O4gR8kgPj+jez3GtKIHtuEhIc7Vzf/jTv/YOm4gk/lF/GfBtR0fSO5Aeqeb2lIVULfqhwBXTxSJq+M8irhST6X9Edb0xlEFnmUBpw+usZP/QSau7527/b3LEOdNeVRzJnrD4M82e9oDiGRRj6fGT6xO6ByGGCOy1SPCl0PR7LR39xEH5XeSwyG1wq6SbTxFCiOB1aSlgTUmqROkISWxeSz1IZkmNhVJ1J787Jmlw+rBC9hJvnug+gRwP6goC3C53wYsQKsQYZL8LvEl/GteNIbXdxr/U7zkXuYLstKF0Smm5mSrErd1mNZYuiRe0Z6VlN0aJZzPztStNtA3ZRSq+Zaarqz7ecFMJjgNraLUbhyMC8C2t8hg9FqOLqlQ5Swohwkt5tZ8LflFfWS+Ws62S6r7BmpWaT5o13HwUP8tur3yV4suPGTpMcgpKVguETUE9Bep046labEabfIRU5ygY32Gc6MDRVSqAFEpb7sT7xxbJ9F5vz88le1TUHc5p9mGWZbbfv4RVe/qquaVGyHqmxlRJc4VM1d+RNjGoh+LlA3Z4gnkZSqKgGVAdSVw/1gHxE7xzACqhRGzuCQRaqT+8tRK4B3+qIeM33fzvMjCoCB++EUyej/lSd1FaqunInDsZS4EE/PA8KSu8FVMU3lICA3dVHLl5ePPxLupKmqmqGjL2aK/7G88Yd1SR9mKVpBggdk/FJHqyNUzwwqn7K3PDJ8J/iazRESdR6/LmAQpY84ZDQ960VdKkDSf7T3t+t7Cvh095nojLHy+AgFfDY9XTCqE+ROmiBQYXm5WIHURJHHW+qXW1TeAvAbmuNLz1IO8MwfLvNcZb6fYnzY9YNFNhK86UMXAr86htIVoRn7sqD0TIlhNcBdDNV020Lmod3PE3PRAPu+1nI360bhm5NTus4EO/0lGcNNJqydqKn+K0gpHy/LCqyQ3+bzCq39FZYNCLd1TomgIrWIxNIVi+R9NlEUFDUiRGdZduiD7Qt/doa/QFVOJjTGb0zX8XuvZ5xCmkmBYiohJbrWwZGDdIIElhLSzwYxhmAMh+KHVF9hJiVxOvD/B0BdMnlBhKTpEQAxt+4iRWVlhLE8cKq6B0cs09Zyw99Ke/DJW/cJTWG0QYKYsYW2qbQeltr3Gmwh1ejffIIq2FwvzR3al7GWxMkseESIOv/PmVSsxrTGV/yXFXQge1ZcRQRKNoCPVSW/u5w+TDghwOPz7fY+YtyTzjWIZ1eKlkEfV2lALHMNPsx6id1AcEcLKIelBpnf65hCQkSK4hS1yuhFrfKhSOO2QELG+zaJm1hbj2SA3LQ93q69DzQkMPYBP5s8ahhfx1/hJJCtGeprCekMgESXkqxlq9R1LA3iHEH5M6PQRI/u9smPh8PA7fgDq5TzNuU+KluDlatjJPkYgnyvXqB7C1cm0H0uIGGL/DFRttU0hbyEevU0YxTJZFV0mtlKq5m7jTOm7psJAqx+/L11qTngyHdDL+jwLiOxU310QWyu3NQiWzVGXRRBXp+YqOWDbc4o+5HRzgtPCAOcAyv1eboR29Ob7ADyAe2xTh0ni4lmUQSqMZ7DT9Fgo8KQVGcjNBZKw0ya4z5sDir8GvGGEl5V5hNBpcObW7bZiJDoimrya26z0j20jiMt6ijid4DtBwI4tQnHElb22EnJtgVo1/aoFfYjvm8sa0psVOWXuvJQBD2lZhj7mf/17Z33NWW8J7lPQoP3MW+ah3hm655QmCCFIgphS9eLz6IOwrn6vpIDYC7Jf7ts25EYuNhGE3lD9yRF3zaAhfL0zCT7Ijl0xkdCSweK+jGrokTK5zH0ZNgfol2gk6nr9aIAtswyU7WmrytRkBz4eLdU/CHj3DzSdQzHxWY9cuargau62lH0UrxCER2l23DF/3kyut7TjmVw3FjP+ccCt8kPydvl2o57oSU2YZGKFKaOZk2unIdx8TgFyiPAb2LgPRPMhkfhcBTM+sf3dLo39tZERzZ8so0dwikzPne6bmt2NlBEgTp0m0bjcFUJAftEMogjf3yl9rSrlHTdUguJ+D5NF1cwav/UjVtBuyk0xIWOCL15tf6wC+m/3IeRi1Ekjhwex7sGeRparChPK4hbLRjV/SJ0SGriWaz7uPirwpvAtw5IWMtgVVrzuzPheawSipaCWWNZFVhtKrdydhWVt5GJSQufWeVkOQE+Qe+5wJC3PXftLCkKRtNS+VSvowDh6BP7UT9vvDVfWjTLd4+vY7g7JKhPYuP0QkkDcfc5Lu/3DR2fpZvtWUEAMWSClrwv43UeF9BE8aUV8uUszgcCPXwdNYcruCPnu3fLYFKBlTa7/kSLu6s/BOm2+SzJYVDS2K32OGFanaUkc64pjuGBpdkqqwiZFRlcC0wZfbb6sv1um3zGEpP9WsvrqKFNvMjHyKzN6s/SpcBQ3cYJMsvL+BTBC7aaDsTi+GNJMRcllwmtnDOSXcZ6jAgVuxPH9J1XN4NXaHCwAq5vlZC+JnkMg6H0tLHMZKpCnnbiS+yakRIWan3RbwqkpfYWbo7TfYVZhts+n3jDjMtnp4KL9waqI9SU74+ykbb2dJbGcVcvsb+MLBO76e3UdLnvzIFRh6cr5SyFGwL17TSIFAy9svEffNqD3+/VEDb8pEnWKOcO5KOoJHIkdH5EuwMw4pTc/tD8k1Hdoo5RI9MhqJ8GGKCfejcTGkrdhNb4Wkc2WR0sxNi1b4fv3l5oh9xpIIwva/z55+fJ91AWtZ8i+czIFTwRVSkXNLcBg0JFS78IYiA0wBaWiY5+Rvw+4xWCmIiIp+3sSRSePZ2kY4YSN+z3VF91kJYb8xkxsCO2eawuSWkhoiHWLg4QxFE7PMxugSZ41HEzQBq8CwbEmmPIvP0XF/jE8XPkCtbzsPvTZTfKTMvlqZ/KEW+85UayrRXwRjv0OW4prdXr8nlWub7fFtpOKxJECnHOxvlbTybCeRQYnjSl9/Z1uWl9KM+6VfbceVBl2SfkfHEkV7vYBEypsoeTcBZauxMwbW5QGVILaCScexnzn473/+MBqFXbEflqwSEm1/Fj7ufBfxq9IstDEubKInQSnFrtC5ibku32bsiZ/ZneY7N2IW7yi+2zCS90Io5OVsnmAFlfcpPcYmYcfMhttobk4iNE+I+bFQPt+QPrzzoVhYpnud9b+xs9wGAeU9CvN93m5LkNCY+U3DAaWah1dg/RWP6IYd27VC8EZHvq3x3ES+oB9F5smKwU2MuRJb2fGDbJ5qPaI7dcGQjS8NQaI6lRi8roY/kbftKPgECIR/2llB0rKFrMFt3iVWy1iYLY0YhCu+s/+nAVcgX7zgdx+VrzskRwrGPWsytq0QJufsIhI1R+r0wfLJKqoNh7JAl2VEZn9Jedq6NSinkBAIloq4EGk0Hz1tLbFLoBNqC06y687J0ZC8v2FE7k7vLPUk7Tw9WncESdfMQ5QMKUc2asa5WTVDvwiUGSpFSpDBl3/F2kLSWTkYaZUO+41mXcinOatxPN/SN49C3JZR8v/3Bb5EIRHarOxwbZS8hXJQw20QNLF4ZUO5DEdQUUPdnSZ8sx4yMJKm/pe9VHJLuUO6fFGpwbUpKJlcf1+twryQCKqyYEqT7QH0o1noq0bLkQ5w0Ji6+cEEtWckzrlGrLrR3rS7luEmxVa4fke7Fhop9F0rdSciSp9aX5aaOnA9xIMjEOYw74mQCRk9PsDWBYJ2hN+2JuY8Zm41v8m5aGs+L3sVlOFzHIC7xZdSajCdt4e16z0vZoF+yMGBsXJY9lxFXrVF6XDdOWF84dDFDh1yV582PFCpfJsdPIhODwWU4z83gGGz11aLdkTYcp4MkmOtce8sijpdfyxwp2bQjRMXp+dRndO1xkiaRpsb8FMx7YEkZl8X/zExlHxIHPYo3tRs3McRuYKfa89jxOIlkwPdjk/+yHDhAFsOrL6bOrgqWPi2S7VT/QBaZdNBs06B3Y+3PLKSheg9meCp/4sjmKCLQ4g50UPo1kbxiOWOnm7hQDO+5+gPFM1h/yaYJ1bnYE6SuKodHiSckQcZ960JIsx/sZtJ8g6vkWtERVfdDft9ziNr3ndcyOP8UQyzyxUwKfVuBa1qjg94g0z5rnmc9GDud0gfKSoignUXJeDQ78gq+RCHy+5CqIZxCQbawD5VwMQ7+9WW6c2nPEP+7k2JbiIcvEeiz1x7NB41zWpFyMTzMYs7sZUBzaAkLzyLF2ma5vDnrBmKMZS5Z9fgPJWEbB9gVI/OJPZItHfRKxltabreSzAXEwg4qC52uDsYjlXDvDyHXDcXs2c59zb2PqOtWhd44GmukR/law+IttLON9ROul/uzzQInldnS+eUydO6NSGqnbM17Ub6Td19DDtXrBKi26XuzXm18bcVMQYibSGEsQujCxfGx2zK2LU0BXyeWIx+QE2tiw300ziLY7UNSVE+7/AVOvj7uf1ltpP2pMvMwnD0tmfe66RVGRdOe9e0tTfi2oZ1Fa/cTQdlbWtxZKSSbcWTU7SpXWCr9losc2rDVrb9q0i7BWV38FFfwMtKOPNFHWV4h+GZTT9VU2RmzgH4Y6oKng3chPMkURY+LiJ6nDcJxPj7t2w/NAkpSoeGOkg8nzNg1abtjjDra9VMRQsOd2k0pyfvKdNbCpkYtxqQJyuhawsnKnbda7BOU9IedM8EC+kgadl+cZDj7XgQB98Or7z4cvtP9D/+fTE8EAID8OqAM0ARIAMRfr0qvd6Z/f0EAXl7/AIjUAAAlTSczG7CHpLOjo7OTlLOHipUHE5m2lZs72NlJmJ2dhYuFk4WDj42JTNLTwcPTzUrYycrTw83MgYlMzdPcAWyhaOWj5Wxv5STs5OngQMhLZuHgxuxk5mjl7mJmYSXwX8Ex/+sQAECkCQFQ/a8TGlbu/1/oYijxz3R5xRc0c3e3cjR38BH+b6eB/+0oBIBQmfGfgbNIOjt5Wbl5vKpP/A9nX81XhQQoOrpbOLs5gM3/3WIuFrbff/+5uea8vGbcFtw87PycXFZsfPyE7DT/STsfdw8rx3+39d9kwf45AQkgsoACmPx5w6IDdrJ0fuPOIu/0qp2ZhQfYC+zh8/+BVpzs5tacfNw8ZpacPFxWnNyErmr/nVb/vby/xOUfrCL6R5NQACJbaIClMtjCzdnd2dqDRdrbxc3K/bcR/77Q2cn9/8K0OAjT/2jbP5b6W73XDHCz+ncz/6matP9LSGgAMdNvMqD5b5JO+fUpMxsrSavfT/3pNKjXpUSGMABdtVfI13Gz38Jk3F4NeePsZv9/4BsiHViA5l/Bfyv5f4GrAQdQ+VvgJczc/y8gsaUA/LYeHi4CrKzuFrZWjmbuLI5/d7qFsyPrG7CTtTcrBxsbD6u3maMDq8tfzIICwABgAXAAIg14gMrf8lL3ddH/QT1jC0B4M/2/UQz6VRf4P7TBFoOw5PiHj1r9PZlYzR2snCx/o/D9BUAB0tFC8D8hOLtYOXk7Olg7uzmaebzeutmwOpq52Xu6ML8iury6wxzs8JqPfyj0FyhRTPf/kpP/tGH85XkNqFdN/w9Y/S+QglAWTl7/b7j8L8/yQL2G+X/JtH95zBgC/H9OhH+Bd4a0Av//nIz+XR4zxCuBkCIBAMRPUNAqryKpXjcesH8q+emJFBPidQKA9Oe9poePgxUVIgQAWsXZyUr4hRQf8vcspriDw6tFWm5mTq/6ulk5WfjAwkICWAAQpBhQvxcgvsYM7Gul7GxpRYUKBYBXcf5z4BWBCPr3AuC/4Zu5eXi6KDlb/FGRVMjQAFhlMydPM4fXldgwv1eiaNo6vxH/bbWZh5UlLCzMH2KwYf+ce8XUcn6NtcdrUVO9DqLqgC09bMWdLOWswDa2Hq8oBHAAhScA1muKuLhrOUtZeYEtrNTA3lYO7rCwcH9gIcP/xoLRAnu82ooLD8DQsXJ4rQorMg9nsj8z69MT3P4LlP4zABqeFBvhNx6KvJOLp4fEqxFgJxt3JAQAVM0zgBQREfB6gXqlBSp4RACkDFf1Myk60u8xhFdXgK3Br+lIhYAEgBJ38LB+JkVFBiw/A+B+562ZkyUcMgDq+AXAgI6MqOXm87dBRmh4aGRSdBQAyQsA4dWHzp5uFlbuKCgAUnxUwNVrJJQ=
*/