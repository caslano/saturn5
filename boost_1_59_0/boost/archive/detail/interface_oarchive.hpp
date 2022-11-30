#ifndef BOOST_ARCHIVE_DETAIL_INTERFACE_OARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_INTERFACE_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// interface_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <cstddef> // NULL
#include <boost/cstdint.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#include <boost/serialization/singleton.hpp>

namespace boost {
namespace archive {
namespace detail {

class basic_pointer_oserializer;

template<class Archive>
class interface_oarchive
{
protected:
    interface_oarchive() {}
public:
    /////////////////////////////////////////////////////////
    // archive public interface
    typedef mpl::bool_<false> is_loading;
    typedef mpl::bool_<true> is_saving;

    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    const basic_pointer_oserializer *
    register_type(const T * = NULL){
        const basic_pointer_oserializer & bpos =
            boost::serialization::singleton<
                pointer_oserializer<Archive, T>
            >::get_const_instance();
        this->This()->register_basic_serializer(bpos.get_basic_serializer());
        return & bpos;
    }

    template<class Helper>
    Helper &
    get_helper(void * const id = 0){
        helper_collection & hc = this->This()->get_helper_collection();
        return hc.template find_helper<Helper>(id);
    }

    template<class T>
    Archive & operator<<(const T & t){
        this->This()->save_override(t);
        return * this->This();
    }

    // the & operator
    template<class T>
    Archive & operator&(const T & t){
        return * this ->This() << t;
    }
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP

/* interface_oarchive.hpp
ywcjFE581NfuR11r8mz6Pm9c8QC5cYGT52NPoYTQgkKTbo2jykmh4D5DyY95W48jPmriak9wPuHdrQ4DOF2QKt/0M5zr5RtEFRouok9+BAl9o1gvD8gyd23YB9UtrS2tE9r65XxPx+ayNHXQbXdtKtBsY66CQjquiNdCceq1A9/mlhPyMZyZ/ESpaWkNp+Fq/anduSQoEPz3Mqqqg3ny7+zpU6kDfok1I7FQlbTHQomuHtPc2cew5K03iFBwmJSYOhPl/mAULtxWJuUj53GOziCmBVhSrmPVW4z0A98TxxMU72zjpv6FQglToVjp3+9czQTWnX6aD8QdFElJkHXFcaGy+6cg8vjNEtxpxA4vh43y2Z68j9K0grO59eDPzDKD4ownqYOOPPSSFhwchSZJsvqjNrvMC4Wkwz+Yl2zs3UM+u99GlFcKu9WGmnCkQIZEzsM0t0Nh6s2lM9lkmGRAOGNXFeE87Knxu3WhMVNWNxkSpvceAzdmgGBQOKbv3Tqpm2KYvCMHEkm2mFFeCWtAqd6hfo6hY+ovTr7clMw8F3TBd572XpBmXR5Xy60kplWirh19uQmdFwekH+lYpRs3sMrMFm89eoDVTTwhjKo8/e5BcKoJ06NH86/dM9ClGqZX4Ig/Z/BGTOXfYMQQZ3DGoRHjoCwmwkIK5UUTf8mcuJaRLJ8kS/2KEsMmmtmQIzEJKfsuDsgo0BpYcFIdwDChZ43LyPiK9puimZW9UYICgaHq/SOnoyHhUUAoaPi2Blh24i7rE5VZkOfmAGJHGic5oYFuN6YYQ4EJre5QL4zks+Jsl+B46a+9IGyEvimPEWBTiNkD4ikhjtyAkAzJ8K8HCIbyOvaTAG/sQNV/l0XrGz9JMNipLoT5T3jTBtOkWVMVFTZeaJs6lWz6J1oEk1Fls+eA/SKW7j4MCZTHUB7PAjPt1MNZWLnMP1uAkRdQs9xJqz2+DpqJpwlsdott9DWTCdqGU0mMF+h8wJ760/aDs5DARAMV++Dzs+3P7kZ5o7MvKchXlEcYHzkIj2V0ImP5pmVKymdn7Gix87zc87GRABQAWDfIt4Hek/MVsO7Yb9YiKvcHg0sWmztvWIaJ7+xpGt0/VfDYXBPeZjCkQnTJTzvuM48i8VWWLjx2RPAuwNAnspsuT/IPm4SEQCXsVSoDo6BIp6lalW3w65tKmNod9Ys0tp6c8EUvoq68o6Y8mI1B9yDRqUbrnPPKLnxGJCero+w8AfmjQW0/3VFZX51Py+WWxK3uQvriZMx4+M0Gfp8SgxUhFcNiIBga0bMNZ2ASnkrVyxlqaVYwTyi/n2jSQyu+c3LuciNjCMIIIjJ/cOBIoMk29/VBQKeDo4oe3m5A2B3xjMejCRd/+XcwTIYnbSjPi5V5DLxoRV4i+koatkP5MpKGZ7Jlw9qdO+lTHZt3pI6E73WDYpcU2w/Mu2AovHJCazaXRs+/p4wmX78HYVyhvN00/8IPzuKobMQi7JQeiH4qYZoODliMQuLexWQglllix/3bo2j+L2eGqZzJVOu8ubvoEowSuxuAwVmzDOKAmYja5M6XUHaogbsSzNJ1gPgxHFkZWejSG8piDpLTjNYuIcr93UJhe1IeBSiev9BIVyCQsN9mJbGjDUJf+NYJF/ZT3CdJeeSeZdP0JDt3LN/wOoRRYwt+AP7C0v+6lJNsZVdY2tebbTb+F3WZ6r+56v/V5YcHcbdfLbypSM5SePmkYoZTbLoFN18P2mrkHEdox9HRz9ep3U33lRBiSa5M9IpZoCuZaC4Bn1n+0sGEqlkAQsgVHAjKIXwfuIiCGuOoaNDROW5sHenmEc+o2PZ3CgLsEehlXy5H2o4eX14V0scqHVNDYsT9LkumFcxPA1kYqdDwZF5CKhEpeaqkR6v7AxQXfvd3Dnnv6lSvvKHLMIVNCh15W7N5xEwlodUUznFPnHB1tfjDmD9IzC2H0G6j07iU9ICzXmHbFwCAQmMaGqfHFb/I2NypOh1robA0pAznnnPd6Sucz17rfm+DKjA4Kk0aqHXOh+VROswzcrdNNtSqx4efad+1NFYLM1s2YWKozW6CzaQ9Jxnwj1MqvtaKbsnJTsZ5pwMj6tgGvh3zFgQIyEJ5tJecjg8P9eh2an9GHtJrhgf2KzsC0tRNeLBIz19WecbQry6HeNZaqgJQx7ewzwmZgJDh98MYb6Ni55tFi+2Q925Rsd7qleXRcMxAEKPZLXkUnpcx88cP01YAzsAhuEV+s5jY1YjGurRv//WQ6sP2vVuvNyr29Y8Jc6Rh7LpVVz+MsIhjtTWOadCAAm1jCim/S137P9N2m70uIYa3CESJfbkm5q0uIfGp2gX9FQvea1S9iIhGxOpOqLhsTUUPHZCrT8vA4YFDt4L1tEjLKioKhXQmTDLsP9xjJGdvwiSHGR9QVwPgR43r7iVIfLRudKprulZi9qlNjUbJF08T0fVJ7ciBjNCXKydKgekcsTVm/MXmzGxSuBa++ReQ2nPQDAIHJ8rRH6E3PBMFDiJ+qjf35zwVFwU+uM3SjGOxc/58xfnYa+QVT5GxW5idR+eJyI15ygMvNgftVFcmqYbFfePx/4JTkN2glYvUDQJglZPPN2y/NAlIA0OEudlGTPT6qm9U53vx/COQ9dfSOkiSoFk34nEHJ2RHc5EAkV2YtDd2oaT9Xn4MLjJjsGjhiuc00NUVJaqqTFzrSUe6QcX4STk7JyBG8m9wnIpXqvFeE4o7hgjmyTmNaJd7x9xjwEHzI0JQaKQxchBgaT/NVhhfg6Ntrj0I0Qtzxq+MUV44ke3F9roIaAsXymhPElMM4buWz1lH47JVVm0c2/xFawP1lIfvySP/bQmLOH+iF5adggNxcuP6wip8wve1nqYcLGbN/X3dnJWKvtCXKnWE9V0R0bpUhEbjNAGvIaYxG5MMi3w+6ZXbR/Vuur2wC8ZhKJaSl4wKtFyBILovFD4YATkCuEvXaevBt/hkoR/+fgrIVqjJulrg95UfxDDn6LAHShWQ+jjCLRN7rnsPKpRjiR2HJWKhHW12XnVadnNvl0ofLbaiqxxvT5T1u2h2CiJt5YzAYHoVt9jxbuJciU4KpyKBvM1HRnqc3BKWsW3RWlgh+2v81rm3Z1VuQmZSRwZj+PQjCG0V3JSpUsDwNYAotm2bNywQCubBcnn7laij/eQKBbkXzeg+4JaBjWp/mu7nPM6s40mWI2eYOdVcC8U8e1P/jRuXdXzmI28h7IXDA2v7F+d4Eh83Jro34KgOpN2sVOCNKEr+Rhz4iknJyxPG9fUjoyn/arTsL5j2cdX+ZKjcT8WMrwo0m6ePUY5hivQMOWFI6Q0EYOEkZ2pnsWWl5xRIxv6jTbDr7OBJFhjp7bqaIvkf9HSt4E3ZYXz8/Yrc5RrpFdoURURMJp2Pj+kAwwYfWGRAnWTUtBRXBZZe7xnxhLGSvZovwy1TfybvAOW8927jjJt7hG05PKF7Cprbo9Vnb4M+u6OpOWEz/s8jiNRENdrX91zdG72UbdMeMhDU6mm59FQpvVt0Xb3ZlFKMOwczFd6vtQdyi95wceHUrj6OkBUUXkR4Ggc/+vxqH2/asif1zGzh4AXF+m7XMIGvTj0QLn9wQzl+Y0sq9tW4JtXejpfPG8AEKRxfQk9wJj0CvZIv40nOEdQ1oVTLhBDFLOcVqQOjG/p1uo4rI4iK2B0VpeOPNnRh2U0O0ea2tm7luaXScqT3tPByDqEpwiFCFmE7vFv7Po785W8HgUDCPmrmJoG6zTCRexJFoJ2JZK8ENd6hm4/53Sf7G+TqMGp6BA2KYb4RcHwhurgebIiS8nh+tIHh0H+Wz3Z2w8tQvL2zcSrPe2OH1fHK4i0m+RKDJmGnyDO344/xi6CMxeX6vnY7MD3YXaa1LDuMupJxnYtzTWor29g9uKbxWM0EPZW+8sQqPRBNA/xBkY6kdLlAqV4ryJXjPD5Tq/XGAIjxkooCCy4mzg6RVtRXp+ILT4GlQIMPEHZsV8IM4rvH8ZK5sZPYGB5FYzWdKEMmMRapK6aWQzuOLljHpBEu2A3kRQXObrqf+CFubpjH371RV0IoGFRg02Mor0FJUiN3XVUWDj3HHYYo5z+6Yym5qV9IdzjkSMrK3F0SCQ1PCo5z8WqIIawwIGgJlkKqzVeS6tKDza7AJSclGqXJo50ya4bf4U4cDPeEl/H8/VP2ivuue5K5k6n6ww7bFdgnTY5Ex1MZhjOufx2rY2T2rlLnrYHSWZ8bpPXfFmuGB4xHmBdiFyMGNgWk9g08kXEwO3dtcds3FpGN4PXO9NdQvOEb0S5mhgOxVF+H4BBhM/+lzWkqdrjjH6OjgnynGoMGt1tf8B0HARFB6e30xjeBXxrAIsBTHEs8CV2OhWgzWMK+/ehy5FDM32ukxXN1MTq+dTDnpqz8MIfUhzinjsqsG8vI0zF3sDvKCKQ/2qoTdci8lgReepZqsJqskw6mHBqrCgttX1wMCwgPua3muZ3QRH68NHq2yLnbQTDRPo+IwwYpK9jPl7vULjTvkQKOKJ0YyWOZ7N4noE0EPIbo7qhtv1jxlov/ZfhDuElYUHHyYbJga/feKrtCKx6Gcd1Y9BXskcKpCw0ajD5KMVX3FidCE0tFeh4BA4rRNnMXPoVCZSRGWtlJzikEp61qvCjO0k3yegZSj3y1i2aQ3y9VhCXIlYO7rCHwrAOEru4QZC1iy4UixmdqDGtnHWPP+W+8CJuKDxGNhY92kqh7mx1k3v9gYNb+TPmaQnuGETeygw6SevqGNfgtWpSefO9WYzEh9HaJZQNwGnY7Q7vyrh082a2fotUaP9rQEYCYR1pC/hASLeoNFyUgzWw3iqH8rPhnRsXRoNsWcD+SULEKriDCgBLZFcrI23G5MtBZkvmVDYaLBxXUmYKS0AIaHIm9PfWYIZy5DqIiTw6Okb3UdoGiwNveL+IQCUTsufpl9s2lMJMcIPfc9vvb40XHbM4ttwqFsyZJdyn8D6LGji1E/4nJboxFuJgyAtYOB6G2yyTC2VkqZWrsTSkpONvnzxRQI24mdsrfJXAOrB8c0mATzbfTdF4YfkorNomDl+E4hhTKY9RqzlSnNYNUPGsN4gAj5ogdPKvWhFus0P7de5Pgnmfiz6q/f7D98gXwJ7uTuiSPA9XxDP8CCrLPNRo5S68nD20Qy5y27iRl3DB/ajzGyH4CJ4Mn5SKYOWjGnOM58CMuFIMHx5aZU92F/IVSSsy0bz/vVTywbVWQK6myW3x7pm9q1j+5zg+l6E0YvpOvW9GujUIOBI1A0LYPhdLKe8VqImX/khBzA85hevBNegiQObItKK0kfBy0C4wR4Am12LkgQkgOYQJi819HzCCZa9Rq+zT56mas5BEOAmCELifcRUkez93cu5ZKZkK3ITys7pEcP2SPgePfgHPMmvqrSUwBxezBG8bA7fy1zMIH6R0NdvvuKdQSkD/09lpIIdCZ3y8HsX3n9PNxH+1UCIMLhEsF01fbsfwg8DQ6RT8cHsisQ1egUuDYwxbPO0tJO3u7tbKCR+E3lOLAVOwDxYzRB492GCjbU2nrzLAB53bFpTXm7svT2A6+oLZ73RFly8DBQ9SR+NOWzMAwClC9D2lRa0VRdUA4VYugcTqcb4N98ZAyJzp2JY38eCLerNaylUHiQmEBR4w/AP2POouYbBR8jsd5dHvxz48rPll0aOPW2sn8cN743qFRxhaNhCWWnYV4daoaT+kD6I5X7fbjsHrIVKUj1JWt7d41AZCcq9BqMmjukyl1/aSecoAmYZstb6JiwuzXbf3R1F0jDusimipFbKeX0SDc35PwfHJXAhO6E1kP2rcE38vpoGsJMNg2IwV1d7NWpRwzKaNbnOHvqWcSCBiWgmjjbZOpEYWJoLSjRhZYrP5w37cDueDPo0jRDERIh7F7QIJlPOcPzwEdn3jqUH8frMI9/kIsWGRerOXcKre2zLNnr7LSeQMlcVSydOuWLMc4dDMWozxxugA/hq/59Q+KEUd4IYY5D1LgYpYu5nxmPYx43BA1J+myBUOrOWYAaUmKLFifEZrOIC6QdVpsJBz5HPTZp6s6bD/sjozodC4J3AmmzJtL5BF4LRfEEd7cyboTpwBOSeQgqJ3PUh94eydBfa7tz2QfLf4U0aBFoz9Yifb3PgqBQZvXjHGaL+2fUxQxlgzjyRKrgiF++c9SB1eOnDl1eR1kkH4VD1SfGjCPrEqgscxEhzu4wf9miZUsSTffNz/I/Pj9PU5fxISCt7kQ2qqDNSnWF7UJonP3D3hgZ8Jq9z0HaSU04yOgObLkr9FToaGpvHKdcOUgu5KFDEVuR508eHs2MkUfoJYAJ87frq65bKRMw5aFdkXI/xoA8mJB4US9wMtGf03g0dZ1dlY1owc868pPC1G/awzG/tWi14DIw9YQ3VCjpA9GzX6TNfHv5F806TZSsfwW1PIPLEnZm9IEgPWw8J71zaxLlgGFW5CAmwbXaWYG4HGn31fHlNrhz3ztv7EgWFT9RtVU0/X4EU1jw7t4asZPBfMuPAdlc+Zj0EoOcBgNRZqP41+97FvpIMy8oPUOEgbWBRz+MDsnCLXLlHEzM1FoR1a6T/BYINfdeqQwqEgvU4/7eSOSCzXIX1Bmx7+px0YyS7t+AS5mn/rySY0pTctM7ju52AhnETzCgE0A7GoYpeH+qBUPjAOd/7QUvkk4gUUPEiwPZOI1ysSptTBU8sOYyc6v4Xa4VK1DKNinAGVtU7OrC7cDBxzhsnlVb85LANM23zYXfRCTSUz7AVU86fDkp+HM0IZowDhr/5eGwhHuLJZNOGfShIhorifSAgAV8hkr2iCipi7OsTAk1WO+cYJ6o00e7so1eiE7BilNvh203sA6CloQZl9wFo6mOrXFKKK9Eek8m9DeOC47e+RD0f85ceGcyFiJjTTZ+B7iLnR6YV5GeuP1j8Y9AESp5gSD381Z8ZlEa4VWUdT+auNBSE1DiV2cV2UrpwdWLMh6kaSOicSX60VkXCTmR0IHP+3AIv+CDWzLzXBzn7Yc4N+hpAcA3tQ6djykwSNEWhgES43dH1jcboUweNMNn6i4+q+4/kBCRrGvATwzQEi/J0l2HVEEZCV3fyHV70O4TEITSUgN6HCu/vUgsf0JyrHrlNgDp3jTzTvxFSmLx90YLmMQgROwzODWgYwrD33Uyr1iUdXsfDxuM5DzkXc3whfjIBDeLyDRvYD9eRFp+yt5pcHTbp1bP7rorvLeuxyPSz1l+4yp19JCmAOVQhDvW8fEUILCUvj+Dy1ztYB2lo/1jzkDSorAz7IpXnIGpBbSNjelgQ+KJBpbhZ9urEtJKmh+AxY2yg8Xj8Y5R9NVqFHWv/0v6/X8TuzGEL0mXh0v5CboSZE1iqerIsmmO0CqiSU4gszfvNKyCsxEadygc8WaH5lwS5nePvD4ad5z5AwOgmnP7wDgPyPMVMsij4mDa250CEX3RKlOgk+72gFcMV/+ihr+eCGKBkH9L3DopEk+H2rWhwMsJ64t7iUrVcI7SXyvw3h21+cBBlgLn9rBxotVVC1YrwCXp1w7MKhdWGZLStrY0thjf4i7ZgwNgnq1FHCFXaRe57LLAyMwKGc5AQ68UFquXPgg9jjwcrq1lAqI
*/