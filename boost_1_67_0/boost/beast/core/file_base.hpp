//
// Copyright (c) 2015-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_FILE_BASE_HPP
#define BOOST_BEAST_CORE_FILE_BASE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/type_traits/make_void.hpp>
#include <type_traits>

namespace boost {
namespace beast {

/*

file_mode           acesss          sharing     seeking     file              std mode
--------------------------------------------------------------------------------------
read                read-only       shared      random      must exist          "rb"
scan                read-only       shared      sequential  must exist          "rbS"
write               read/write      exclusive   random      create/truncate     "wb+"
write_new           read/write      exclusive   random      must not exist      "wbx"
write_existing      read/write      exclusive   random      must exist          "rb+"
append              write-only      exclusive   sequential  create/truncate     "ab"
append_existing     write-only      exclusive   sequential  must exist          "ab"

*/

/** File open modes

    These modes are used when opening files using
    instances of the <em>File</em> concept.

    @see file_stdio
*/
enum class file_mode
{
    /// Random read-only access to an existing file
    read,

    /// Sequential read-only access to an existing file
    scan,

    /** Random reading and writing to a new or truncated file

        This mode permits random-access reading and writing
        for the specified file. If the file does not exist
        prior to the function call, it is created with an
        initial size of zero bytes. Otherwise if the file
        already exists, the size is truncated to zero bytes.
    */
    write,

    /** Random reading and writing to a new file only

        This mode permits random-access reading and writing
        for the specified file. The file will be created with
        an initial size of zero bytes. If the file already exists
        prior to the function call, an error is returned and
        no file is opened.
    */
    write_new,

    /** Random write-only access to existing file

        If the file does not exist, an error is generated.
    */
    write_existing,

    /** Appending to a new or truncated file

        The current file position shall be set to the end of
        the file prior to each write.

        @li If the file does not exist, it is created.

        @li If the file exists, it is truncated to
        zero size upon opening.
    */
    append,

    /** Appending to an existing file

        The current file position shall be set to the end of
        the file prior to each write.

        If the file does not exist, an error is generated.
    */
    append_existing
};

/** Determine if `T` meets the requirements of <em>File</em>.

    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example

    Use with `static_assert`:

    @code
    template<class File>
    void f(File& file)
    {
        static_assert(is_file<File>::value,
            "File type requirements not met");
    ...
    @endcode

    Use with `std::enable_if` (SFINAE):

    @code
    template<class File>
    typename std::enable_if<is_file<File>::value>::type
    f(File& file);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
struct is_file : std::integral_constant<bool, ...>{};
#else
template<class T, class = void>
struct is_file : std::false_type {};

template<class T>
struct is_file<T, boost::void_t<decltype(
    std::declval<bool&>() = std::declval<T const&>().is_open(),
    std::declval<T&>().close(std::declval<error_code&>()),
    std::declval<T&>().open(
        std::declval<char const*>(),
        std::declval<file_mode>(),
        std::declval<error_code&>()),
    std::declval<std::uint64_t&>() = std::declval<T&>().size(
        std::declval<error_code&>()),
    std::declval<std::uint64_t&>() = std::declval<T&>().pos(
        std::declval<error_code&>()),
    std::declval<T&>().seek(
        std::declval<std::uint64_t>(),
        std::declval<error_code&>()),
    std::declval<std::size_t&>() = std::declval<T&>().read(
        std::declval<void*>(),
        std::declval<std::size_t>(),
        std::declval<error_code&>()),
    std::declval<std::size_t&>() = std::declval<T&>().write(
        std::declval<void const*>(),
        std::declval<std::size_t>(),
        std::declval<error_code&>())
            )>> : std::integral_constant<bool,
    std::is_default_constructible<T>::value &&
    std::is_destructible<T>::value
        > {};
#endif

} // beast
} // boost

#endif

/* file_base.hpp
hpDUiwuCJHMZRCUYthgXC+BH9I8DE2JSq9S0bYs6I+Z+ik8ojmLq/dOORIW4snO19Vt+bXtwSEbkqoQfTCOzAUhpfozqIkSVfE/R04Aqrwn2dcoZJNBRfItlUxpX4GkmY9WMEQSF1cGysjHFFqgnV3NqIBeLWWUQguBKZ7W/PpDsxjD11a/an4C9us8cKuqkdDnoQWxvsIWR1x8H3SNwGJ4U39r3vRkVHjc3ORBa7VgPHleK0AsyVV9oKzBM8FHvoO6QiB65GpqalIja4KRF9kWN7tgrmtdqRDPPVaSMQcHWPOcBXW8nFTi5Zk0saq9tj4tQAdOsRxXU6hPYEk6VvUGhobl+Pj45dsLA+tG+yNqjqVvb2XchPqMzx4+yuhdXg1JYFtUs+8SJgGfB5sU1S1mFXzbIEXWhlX4kdrT0ZZW6JRQqF3YNpvjuAbN49rVHCuuUnsvZfcI0o30dSAIpn0rTCEIiFwKgTU8wnpkmvRMFwNlxaGhZWAN9CYKFmUxF1w8Z4AOyNs4eh/iYrqoShgiQaQ0IamnEjIkr++sfcXrjMafvEUujze7MkT0Q2lpKpVlyQdfJ9/u5Nc6/7JPGeNgMbTOOeHDkclusGyzNXi6yj7JLkS2XSp7QoB7R+ENIeMga7FBb/7I5xQUyIiNIKxmHBn1DnCY2nhxjkaymE8+Xbs5xYtsHe2wMq/3eBIiM2cT16AZHOJioigODJ7MjKsE3Yl63lrw2jFuim2LLmtK6gxhlRDLLMcwqB0OpynkEH+L5KMIBimaqniT+o/rlaKFOgdOZUlq405L9F1sXeVPBXz4HnNCTCH80Yct6whUOXNX7IYmZXOdaSPXol8CfoZwIZJ+bss/bSR6UddEJd8BiR1SZDJRMUWcoHwgdEPwvFJTi7Jp+wCQw6txaAZlWaT0nVgh/ZslPhUuRyryRv9wmSZNmfrUKw6YnfkHVxRknDfbiTHe0MLvfEU1g4lVr/fV7lPvOJZrCoJegec3XgXUGm+KHX5sd6zi29HfFNVv2pScMIHwA6ZaeAzlx31EaFwExPRDBfTwpKNpm371A0HTix9dp/EtItp9bQrChvhKiVQPNEReHmcspY2ls6e3z/bObOzn797uhmypZ0Hzq1ci0fvPw24PrsnPrdYfcfiTomisgnwUAhpdIW0R8D/yIGARIkgykGs1s4X2XedBsAb4cSmfYhDerWJrxrAlt+FcGHqFkXEElEVmkPQB+rKuj//YTIZkitEex8fceCFsPcCMShxHeMxFnaPeuB0sKGdRHqQw0caE8qLWlRarhQ8dY5o78zCKIFLJrWmGBL3Pn+/f3F4gGAAD4D8gf0D9gf8D/QPyB/AP1B/oPzB/YP3B/4P8g/EH8g/QH+Q/KH9Q/aH/Q/2D8wfyD9Qf7D84f3D94f/D/EPwh/EP0h/gPyR/SP2R/yP9Q/KH8Q/WH+g/NH9o/dH/o/zD8YfzD9If5D8sf1j9sf9j/cPzh/MP1h/sPzx/eP3x/+P8I/BH8I/RH+I/IH9E/Yn/E/0j8kfwj9Uf6j8wf2T9yf+T/KPxR/KP0R/mPyh/VP2p/1P9o/NH8o/VH+4/OH90/en/0/xj8Mfxj9Mf4j8kf0z9mf8z/WPyx/GP1x/qPzR/bP3Z/7P84/HH84/TH+Y/LH9c/bn/c/3j88fzj9cf7j88f3z9+fwL+/F/vRYK7ysOE6pmZmPl1p6anYfmkiV+SjUnYlYyLBKXQE9BqFXfQSSGn9TWCL0K5DeFsdpZMmTF/pocD2bYKHDAR383N4GdYAMdB6oa/RgvW5ufn00uIjBBQKZetrK0t4UttbGysXoJZUgilKmgHjcy+GRTi3f2nOzo7lSd+As3CxpSK8R4e7lyEo0EI5OYC1z/vUAZhvIX5FW6sgbaZNY9y3tl2gAQTuGEhxmkCnKJeBOQ9F31p6TiYjwY0gxbnSp4PKzqKHstQn0oMIIJH+S8yvL3cIkSrZliIHaor8nVWklBYWSiG6EWZCki2t3b09CdhPd1cXDzgyDVRyC3023znTEPguDRbg79Auu6Z4PWRfUFlzeEAguXMxKAZx18EZCRTnfoFOJILqgbCRSgwsbAasmJE1qcI/p0UoL47xgNGzkpFE4Vz181TvkMzd6P3R8UFYsUZjW5s7CxyjTveMZuy/Kuunm5ubaU2mI4i9az3ggzxg8XQnCeEuxW1ydNQv4VHIIOOvBtR/V2j/Y5H95Mu/p5FFw+xUlWwYCYUYgDrUVmnHJiYqITK3gyFOSjFPuXwzZQoRrmIEGMd4LiNtE2Tzp/ueeOdwyr3WIeVPhgLo7DJVMWbF0ilJN1/emIhJCYGNgyDLPdhALsENAtRuKI27H5d+W5sXY+A9GIBZ3ZARaeqAfGYQN2Hduef5ySzDSjZuPUqes+kjDMvbsmYBoGs0YIKD+0TF7PGFG/ESt2DMUPgTbZP4d5Sg7KP6f4JlKxWWV/isGrEcbWxfO2d5jJSxR7BU3GrAEQ6B/8GT4Qs+u9o5JGNAuNaB9RaRpNyX3Wo07leIM5HQg6zDcWaAZuk2M3BEoQdhFwKdRZxikM8tz2PMI5tJmONWipVrn9PAn5CyR6TnLGQYx0K/lXcMOzkpHY0dhrSMeE6799y7ZQEQVc5u/RgNdm0q0JdBrxQiDOU9VZHOaMUSokIUSDfVd2ygGAkEA+jjt+Ea0fDGtgKsmaXww8GG1hfmASHdd1/Xa3t7eu+PQH4/JBOIWdohiQIGkvaV4X8phgoB3PgiUrrjFOk8EwJpLg2XfcgqUr9dGMcdDKk1xM1HEAa3z2oD2dKXP3r2xqzHhnrNO7LXLNvW1jycEoDQ5Bjbc5MDRnXdkWaS0i5sa2otSXYRIWit4XwphoZzJSqgaNa1lg5rjLu9wfoNAjxrQivalypRD8MdBqBBSptE5qWzJtAl57SVmeoSkrehDlvZ06qVFVEmZB8zIVvXo3beuot51XYiSXQxAOgqOt9WIbeHSE3N5kDvcjmQiiJu7CBp+s/WxaL0iiQvKlKiQRfIrH5ZbE2GpYPYYqFb2RcQbDF2eM0tQRGCpR+xT6exgXGApSn25SgCDgQKFzXfHGnXMoaHyjnF40A8ifdYdgVP5Tth4+VB24U7QqynAKes+pHTKliuhtPcwSQkv2kWGoJ/NthxFNhZYi9sJyNAa58xSj4ZjxG6yQW3etGfLIB6C3lLn7YM+hte/fzST+YxbdenpuTVe6s1E9J0JgzKOq+PUz6IB3oAyhfoz5N016eNvzUwaiF8wvWaxLkfEPr4eB42shba/GSt640ynY9e/qBm+slXKJW2QdYHWit3nKsaLVCVsOWihRftt+byYkgqFcqCPWe7Y08teVN83xuTW7oDkNKrc9OoKB4ldaFZROt+7roQqd6CozYQKKG5V32/MhJmxr+iVTCIIYu7Qnjx1Ku5xpEBQRwfhsD7Bz0rbAbz89BTCxDKd72p/9p587mZBfNFmt3F5i2oiLViqsNWMWn0+IU1XsSQ8dRdYmN54sju4r+Z52I0zUlAvSZNeHZorraeIVxWoRInq0sxI0tcpPKMsNRVw+44/KMSls+dgJKigOyc0l2FBvZOf3rENg3Dgn4HwPbHUw0Kye8ogDVpcyTZDrDTic2lHsQELcJBNA//KA+YFsbJhSw738lCPT/FhEUSmJGgNwfh1jfQHpatji3V/ZYF8juVE2qf3dcCl7dZaanic0sMSuQd2Sg38IK4nNq/GBtCY9/8JEB4Zh8ipmBwWEXl6EEXwVyVv85DQueztugnEdCJExO2rFCQ+vY13yhA7CpgIoaUU4kfZCNYwLNxXOWz6S0XHDTzyDMeNr6PHuempRsuOWHcCd+PuZSxcmmn3x3Lu2Hx/HbVHpPShkzZg/KMczaOJsAhgOnxiOjIdo9QxW8hdOyEzfEZdrWuo5ONxVSodTpyZBEEU+5/FLtEzxZTJfoLwNbxXAfMQg/04yPwe2OcaOPvv7YDJxWSePgT/SFMZFReSkoMtROGbbOh0Rd0u6pqH0145Ot33W2dIplFJz5aww2eb6gGUg+Rd32hp2wNfTUYhScgWQZVE4qeNqgMZMVS0SRsvrwKbTuselQ/J79Zj0z1SQGT4GsqBd3oVfI/qu0n3kQzxXiZxSNHNOdSSod5uJZ0NhkU/oYP3Pr+6+0xi8zpky7J2TFGe94jk1eJeW1Ano3ww2CdjCJ1ri+YU6j8K6kUJ2cdDvESmAjZfCDgSsZVbTvwpoi66VMdNmbfLUC8gfjG/7IYHuQ8r+SUMUznuXo8G3HVvIsap5x9dBR10BLUaQuRHxyHOUR19rzi9ZA3jzlWcdxNWb2TMoDwzhIMt+6cbMKFaJLSihyVO3MlbZNDhumaQiYLSxjq19iBcb0jRU+JiQPhuRc1xffDPH/WiE8c1nooyybnTttZ8uWuWzoz0yaJrqYJtfn89lvjirSwcstzFhxUJaJQkHpiW8guvferbYdt7Aea8D5C2+lncOMPuJ19hx2o5v3U18pdB9npd3DAZsc8WwI0cqC8fzCsvK5Ow+xVHjOXbOhPC7W7O6HtW5kBvIKKGfjxQndPARKGDfgbgESJxJFXpTNmaCigShbZEpTJMOaYR8jv2xCc82on/U4eq3n+1BqvOSqYC7noBsrEFNN6Z40fz+iGA+YDI+XUpToB3dnDhOCmYB7w+d9amOpdpe6BSt6Ygdu2NrjUcSr2ISNwFlZvGaspUk6LqD2IYXN17PSptWklclwdlKUmp3n90FhNiUu7apj9V7XpuNNB2y+nvPbUd1erkQLgCDfME6hzTygXgBa6KnMMFQD8/h+jy6wSq0sFxHXZi/YLrpFmbPcXnAAfH0CmkGqghHo6JRA5Wq2Dm9X5bZfx7u+IBtMZkhKf0Vwfo15QZlw2yoymJQ0LS5wQjMwDEd8+GrJpQZqyg7lzJmfXv0hRfKf+gSjqtXwwfRzSZGEWeehaOdFGvOgejaDHAJc3jUcRervCQBtF4x2S9wuIUsIsO2dseSIPuHRUrfigOf5SaVR1aJygK5U2qOiWiXH97IgPGihZWjW5zV035FWBAb27TGXOqQ24dlXkgcFzJY4d+GshE6S3mupO5AO4klHjc035Tb9t2+86OBPLBtPv2PFcHSfY88d6B1o3O4MjGeODFgaWDy8IT+XzgyzjLsR7vsRKDj2xH9m2B+/WnAA41km8RbvySxsHFUXP8/hqe009vz4bLLg80PFmal8Z/yr2IWQJm8SI3LW7hxNNJhh0kF9Chu/wQj5vVGic9HF6gv4zw5Use/Ac3OhmJ8bUGHP8vn4CaEJK1y22OoKmJbUEuXUM5GA4glxTh/aZLNnb0wt1xA3LNeSpC72NTxWL9Yxn78nqzv9kPr3Jde3veka/gcUgOt/uTfLKKZrz4Qvvrlgjqo2wES1X1uobQ/wUtz5eBzCCjriCB0t/D5YWN/57zijp/pmS2yIjKtYYQgZhpRwmM8fqN4knq4qm48PSQsM/hnhTjTp8A1zUYhYCRY73/PwFMwoJOBAxpO4FQ/EjqrS01t8YzKwJha6xVH/PhLO6uUFns7gcFncZPOuuvU4V1/o+GzUTnNRKbUHvqAte18qV1xlhVOwB/9luuqMzwdrnt9oXmbzv2V5xDLbiMruyOop9ZaRhWSP0ANfMA1nivGfFbDcG/6F6maSmIYz57KDAwPJhh78QgvhR77z16TXabOi2futAFKvoqGCKWTYgna2fgra/Kg1zEqXxcy9LfxdwcuRy24OjjenoZUDLGgzxa1n345CZsv96+u6KrPHTiC2nGs4wsydWyeMDibxxYyj9E4l/ht9tZ4rfxfY4X1p78ixMzw6yY8w1o7SoPCZ7j8T2QOLyZA31UvhpFDMIERZQeVQzNRQ0DcAs6j+1sSEZIknGKmEcaCgOHsQSSiAXiptnudMdVQOFZz/OnJRmaWfGTA1s7NKNg/cxic5c/yFXYEakazHtO3UH7zLuw+KXSbJmdVgipkzZ86UZiRxILp0cf8n8O8eX8AUtMXwegNTNgNfj9jmbk9mf2xVMtOI6o3MC79CV+eMwBL25IxVtn82AYBf6h/99JkQUn+wEEUiNmvFy34oYgEcMJRh8T0VWoWs88UcwuNhoJ45R8Avr0UKbzbMdLmFPMfk8GnPoWLpEMdNrNdmwr8KQLW7F9fmZe1R6gc+libP6Rw7ZOBrpMWTM+Vbzy4JG0V3lXJx4XKtZuNuDO5QflTjsJA38gsZ4+jS50rgSIgsOOBdjpmzjBUqzpQg7giRDWGnr77UmajAFI/4UVl4rHy7IGCKr/uaa/kj/5cN0pQb/Zb17asEttT4NTkSjylBqYl8bDlLvFvBu16agHnPyVpGEvzwx4wuQ992nudf3eeQ5Sd7blgosVvJ9YIoYv4QMKq/HP47vga2a9mQ/5flBBzY2CD/+G8o0Ng+g/r31/vju/92Hja8NDLksAqfZdz4rlcL9h+PerccjoR86dJzn29beR+6htDUW4En7JXR5IzIKtAD6Vi2V3PcoW6fUwVWfa0cFwqN8W0I1kGtz8RAIwL+G7Nh0yeVD7pr03JxU2A+5wniSLkxiD6ExcmFdENn6gYunJavXa9yVaoZ5YkfP64GwfV/xniqC1WFJYuRykBeQFQpCJLILDNu1AxdrpXeH0OvWTP8ntP61fcAIZstsFS9EGRHKILbZF8/WDG+htYcNCC5zI26noplivtmVdWEJjzioycphGza7a5tNf7uKTKnYBX8wny78Uz8s8AbGtabkFj0HVsp8UpYdILJma0/th03O12t+LL1fxaiYZt3fLSRoj8vHG3+gwe3JqsufwcipgRlJKBEl0QCdhu12RBwWCu6AkT2lBI9yGxfAu8NPv/Bv/LfY/EWIlaKG2Ge/adIfN8FaEZ3f6twIAlQcx20JDAbfJkYIJYVOTbS2aJo9OyrJcYPlVbUDksfRO3J/Aa0no9xVBMoHy/fMiAK81fyXhla93kFB0Aldv1v/y1ynQ8h8SQPFpjB7obehSXzhR8LDku1Q+3+mBExIRQo+CGOPUDkqak9jIA8tCxQYTGu2n+MKs7kTAuaUhxtcTKi10zH4RFbvmPrIWLDVI4FO6LlIFAp8vq9x3VVOGAkJJ8Y/naWXDr1Wel/1k3a+W7GVdFx/kFnQ9E7wDrMDqOn2esZVhNox/HsfbNa7LY34unyitb2m/1T4bFmB/6KEwExxPVE8n3dOu8wONYLKzHkCB0IJdFi2WSZdDi/6WsvsYe0sPAbFgjqUKVpdLrf3bI31gyB+J3ze/XXgqONucc6N4dVPUOtR8hqvKTvobNjgw0Bx3sJW5IWAWbKco410vDHXfVWYrEPDoRYsIZtMoP/tLrR0EHHmOxLKBCkV4rU+EepTdtbTjHfqHs8gSUdUdB+ygNQr/s3eO/5lXI2ZlmBRVLv05IVBZNY1jkNebu0RaQnrja+sjDAh7Xva6KwoBPlx1Cm+A8nV4C1KEloF+TgVfOeEOl8hTOdQY8XzZAMhwF4kbFjvPQRJWjB93mk3PhdQ3KkhgHxm97RhGiknbR4n/vpvkoNfsTijO3Z8lmWeGYg/Jgypf3oOaU83Z9esYoSqwkufxfP0vfP9Mwjmk8E1cTtv+5Wv01aDsnKbc2AyT8Vfr17NBP5DfjPz6dRe7+F2LGcuLLuxtvaEf3xgBFUxZ5rAc6nwLfrFUvZcvTIyqcjANQ2JURI+eo6s3be9F912Qy6A1TApZLwkBexBLSip1sW5ZzgeJnDZy1W5KGFxGqug14iVg05+vv9WHB2qGwNBlZkNtswzngURJcKct9Kec8ruZmlSMIPrvpkhf7pZGPAmJqJhHVQ8goCJanwcCdltZ8desLtddECHO9eSAcN5s9T4Mxx6zx910UxCmsC47In//sAAyz803FqLrFiHOfFXr4fYNKQJlsLjLkMfzLF7IHeTy9aYMgIr7LW2WieGVoTxkwcjWXMy7HP0jNV2/sUV57HBM+6J3PRH5DMhGAwfir1944fA3TDz7Q+ftaLN60YvFXSYkit9b6lcT+nkx0hwIPq6Y2lWJlwaLjzlBXuIM6VogaPdY6u74tmmdWk7ECloTQSEpiPunTw1pdbzLwwhx3c/1FnR6UJE9cbjQ90/Yqz586v9aFS8PrPvDql2omaZZWoloN8iAFwGtddge8tt7ozBA+eGmiw84wYaKeG3L54djPXn5rlTZFhFZyVaE1DQm77bOrAc2LvvmLzpU73XL4L9o0wNZGNKjMovuckXEc/9lm3MtWK+DFmjx5tt01NeXFQg6qh568qF9b6Vmh0/d4hNrI85w8unJnGHKZJPI+L/lyzG6hliG79kbMl9N+JbaUJsjrWUE761Eo88kbC1j0vu6H1jA6/S9TT90Z/7b8tZUruEcQEJGvKlVbETppDUhXpYmWJUqEWRH8499SBxxojHAcoBa/eNxUBEW1NE01oe3+sS73f4qfl6An4HvJt3FuwBR2YTx+EbUM01JnIePna5U0mTq3VbT2nyIzRIg0/2FWZYRyfuE/WsIXQC/Hr8uUPbaDYQA5pCjTq3mIwceCM/6ha5oAXdg+5aahNLzWkQoAXTGw7OfkRGsaBcWKfd4YZGd5+fGjOuBa+i0n7FHUPAWpE34zGrfjMCILZ4E9q/t71+Q6kGw9AtwC7GWXdJRGOxlq+dYLsEWJi0kQMwYT/4/XMktz1y7H2uiDHdkdj/GOUcMF9yaQm8mLt9Ln7aY6ewaa35aQ9Wj43NN1nUTMmP8GM8B+xuNmRFRI4zJ4vtBvWhB5dlqp6m6Ek6OVZIgpYkbq0mGOPHJTiQTmpAI/Yii4v8GeaTPk0EFjkYWVfrfDdVKbgH9w1OYOn2oVz+FlEnOmu7W+YpaWGO4mKnEFtOj505CSAnV+dCuquO4ZMosvQ+Bqt6DBWNUjgZW/RUANcP6nwCRbcn29aZnefFc4zJxDoYV9oszHS/PrnzAntOUEbZqjj1etyA0yjW/dZfx1qKBUms5Grzp+MKyXiReFLvu8Ss+bca3sAy1Ai2tVw/6FqqQSLye3g6YLsz2rbcJGOsxQRK7TzPxfbiRuweftOMg3S4k2Xrj9HMYzZ8YK/zgq6wx7jo+oYfG+Df8m6CblxZes5xw8wQ6jzRQ6CcKEyNFAHZ8rNoDIRxx8CAounYAe90z7/CzbHxa+eyY9nt9WrTxo=
*/