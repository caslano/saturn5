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
1V4NNpo3PSPnjhISJCNMlqCcQoQhIE4C2Mdxu/FuTzAhIHFJRW1FoElf8QLUlm5ejtQVcdK4be2SjZ2tFq+/n74se1sbbfbqXY0mU3FiWX9/ZqY59uw3szkY0iZMpjOwj/oxIQq5FJCueU/+jAYywSeAqPLh2PU8q+1pJn3/S5anp9qdYlqcTKU5Ldilm4cYMWrIZKQYyAF2xmZdIZoXxCGU4XmmYO18HfJvgfGGMqypvw3oQDtpmq8Zw/e+IsfgM0sZD/z4+ChkCh6lwramraeEwPc6K7BEvBEuQBAaDjbEl2hqbGSWUFdURJLwx4QULD5Eb/2HLAZEuRzC9kfU71+iOOYX61du+DvutOr8HJ77tuMWFmPp5Gk/psDkaebAuANkyJcGKS/4iaKqqmqTRFgQgiyZirW1dVUB9cXFhVU+Yk0lcH5FcWjQjAN58njwr8nhvUdSs7ICiMKEiZKLvr5+kB6kfOD0Qb7sf+8B5cDV88P3IOMjGBVrsni4GTONBzIFpBBC2IV4wIU8qs6PCY1y2TLjolHWI/5Iwa6wLSN6XVgRBwFjl7BNiRATqY1SlWZAoD5WOr6vzBcVFAgKYmUAoMbJkb+/vyXPROzt7YEFssJ5TkqWzp0z4AMOlm3Innjn24xDNgR/mVLn/lvr36OID6MULpghKWUcEGFcqQE1IWSI49HoChs7+6qRS/lxPuBgCggElG0MThC107BJ4AWsRxOeeq94Z4kNt4GzTcxzhCBYFtog0t3d/fX16ekJhFVZ8PCZ8vFSAx8QZuCJ+IEeQy8vCW7MPxiYwY6pK6xZnOc0SfUJR0PgczcwRKRSF1qPB+MLSyOm4BBiYWVVicPvx8N9HcYdooqMyEfp0/WQUmpPweu6JIfmpr33pQ/cr37xMlOvCyTkb9VZobgKFFBc19TUVFdVVYVAAtu9SBkV4EF29Trkt3U/RtC3Fwz2N3JuledzCp8QIIoScupzxpIv7xCEOsRa0VhSYoobsADwpgsRAwgmBxWTX/eSh6/UuB1zfxepEPnHTjGLUj2rJztaqLdt+ioLFhkURC6UEBic29rb3w5c2QBchROL9V4Hvv48rQBg3Bde/rCBJwD/ZwpckAMPjJBwmOtzVOIYVFWAKIk4NGMtvHIyABIakYITCNKHo6lQO9VenT8r9Oubc+SK1jrl4dvyv1WGShGQW4wH9uIVS9paWlqyswG1fjgKv+GGv3gBDyIqu5+Ve5gCQnQQBrSu/R5soOTg3tUdHR34/RaDWYWCgfvZchJuMKgFRjHtyQYKJW5Zoc3AwywsGk1PrS0tru4uLk+BBAbB5VsGv2QBDwmLe+kzTAHtq0Nyy5qIcW3CeVJEAy/Wx8sVytmAmHvEKCk8OlRMxFCDp3xdtomF2sm2qj0LVk1zVauyc+ugYDsEUnAcxLBoH0CJ81gcHndl/mbm8f4KASDlWMpdn1Ucl1A6nR5vxWcgwpEe+5tunqLxvmM/l912EzQO0+IfNLDQgKBhWbaZhjXZeR8/5UPQJIeleg1hQTZhAQ41XL6LzVZrzVS23w5crg5Y/nY/5GfW4EOjRaK7dyKfFtBDPwhCTryYLwq2BvqugcjK0/kShQE3GzycFjJjivMnDGUzn2EyYf6D7GYFFGwWNPKpnLHgHli+y8MB6TuILwF3urUc50GI9dCTeJP3MFASz2m1ourvaLY6brjYFwD72eQMMxdCZS6DyRgYffdoPoApDrHX7GixhhAyu6jSyTufERQk1Z5awiLMBfwyufZ/Df0gOIag0Cu6+6dovOYM3h4IqGs5vdav7GvgION+j/mI/RmRYt+k2HexjMYZ2mozWWzWxK2WXEZ3HmIA2E401GZl5QrJLmjIa5ICZByODJWx2gCX38pTGXLLvOoq8+dpzdJK0yRu2R0gCOwcbahtEksihnGQrH+pmyvXAcjCYyz4RU4oAYs9lkulbjYozrFtLtt7t93gjn1g+c2xJlziWS9+QIiso30FirswvPjKgevTmSwUMrk8HVhwqEvPYDhcsNDsrXWUoEMlhwy1HL5zvNbI2ewZb50t5HICV+uGH2r3+zVMPCGpvJMWMnRRyLN/IaqUcs1x7dLaGzs2lmdzra0w6JlVk8mhHC7QCSwuELjXVdhjxWMO1CerGDXOEOoRKWXD8b0sSNAf8LRbbc4FoGbF1yvO2v2gEr583qRNqODNs0VTHdvWCL2do8BOCKDAfVHhmlHNbCZTqI4Y/2ZBtuF+KyigAoexe6EaT95Lt7Rk3aQiZN5A3HLsIPBbfKjz21d+fIqeQYHSg1iqCXZGM0BJT7kCFpLmoQLCCYkdLE5NiqCL5L4HwjNGi+KYZClyTbDj00CAIDd8SwYlltbsWKFK9c9SkgCSOLklT0FjWHe/9Jh7oApq135UTlQ5CwObCLqGS6UWhz3wCWs+z8aiMBqUd7lHu2+urLBtth2z5Vkc9rsmPGPl8dhMkIjUYCFZoRYIJ/zzK5ad+PUGZ93OHZIGxRYBdxyERLJB/ZdvECQc1QegcriZrwNXgZn9Ecw360cyS/cUWfdlvVr9TV1YyLgqfBIWr4GDorx5RdX6fX4U6A8++xL5Oo4Pwv7fNzcnt2UEb+McvuYbL9/whO4E3rOwrMMc+fKhcY5AcbbacmUm5lEG+eSQYSiYvphom3Vdqy67vmXnvk+GS5CEd2CxjqYx0Jmb2MkVdUz/HfFQQEqi7qXUl2r+e9VnNywNqKPw1SXUXh+y1QyGRvfbbNEE+tdX2F5Ecz2MXYbwBl5i9ax539xLPifWbtZSatAKiBSxC8V//+jBk/rMv70rq/3YlqU5uk8ngo/ztYAPlN9/TEZFzQWfL7X/abFYKKxYD01wVuJ2QsSsHIpZA4f7xHBy3pn/+K1ltl37XilWr2M+AgqbgMcMXczXZjuHiiXf0TBnjn02Ks3Gli0FRUQt1qQMePyNw1de2IGBAwiquyzO3A9R8/UQRowN5EA759umn/e8iy2B9+AvRUNNybEkz/qy9Du92NkCEk4rv+KgSCTB2KXJ7yHnOl0vW43bos134UW1fyDEko+zzMrNOmy17Pg+p1Evd4/memCnPWhcbBaLJeEylO5XVroVhyDC9yxKmMljW4Q/Zzgy8Pw/gs+7Xu1YgK7lDFB1/gAQQZLJM56K740W5RKuZNGkjVIsb5lTr/+WFrYsqbQazVxB1afFEs8olqCY3Q5HAiY9zSbBbpnhNIZgRSvqF1VqlujlOgA5gRj6Po4U+OwXm/+kAv7BCE9ILxXzf9C1wE8MR0YVnot9QwZRrdAyvlvbSaky+f/4uIjRHW1Iv29ChK1q4MjsjEwPr6ZPr+Z9r1+1X0gtze/aZSF5opNRCpVQsGcGTszMo4Ciljq57PgmVlQwgyyRR6UdIhTLHse5KbfUzKj0LqPLzEAekS83QJ0IaHedfz0zTF/sfQ2q9B1asHwvvmamceRYG+2qMAahgfU0Oy8uhCAthKXCYNDnhNW86uJw2NmIf3bj4e2xDh+kWKv0ovNUiiPKVfQvMwQn0uUo4Tn0FNdDcCAIEAXQ2LZt27Zt27Zt23YysW3bM7FtO9lsV72uvvflf2DYEglYlEdqFkyRYsG8t20DXrrJnzhd2D8ajPndhQiMVGqgnRTgxqb11Sj54/UmbnjfhADWw2Ybptcg81VM/xpYP306BmsXdKDHP7r/1eM8fWaluvlfTGVgYdvj1FFGjbNlr5LHqOJ027ZqOOPiyylazX2cwWtySLqbjPIIMmkDAnKfBoTLlgnYt4zYpQPwK7XVIRkJESEVsJWjex69xa37rKyZH5n9NaIgMMIqg5vHCWQBFMzvqM/Y8T/GjaN25XBT9RAsRecueKQO7wenE8urUyV+pZ167LnLWqUUHlRXIjuco6nFt8f7J1TygCf/rsOJekuPfEpAUZ+XHiyQVtWMkYMDPPqKC7wBAxY0/6cjqEIpOEgbLyAla+kR5plNfTosbonZ+sPvERTWoNzZJiVnqhF4Dp+Oa7HnVTvQUbUJkJJ2rbEIwxhyJfxPHMdPZw2+jIac4v2/9GceaCLVJc6iClCflBHFNxcBVLaTOVzL7e4sekqMeHhJJ1B1EgEZFRPnwH0qGLajwt27kbEk9llYXARFb/z6x7K3Y3UZdV//NDksKQomshr/E4tw/2nzKWBb9XRwZmn7P/EmveuhT0/PkKGs/juaJn5zY0zbBYNNwJUuQqziMnUaF77mB99pfuxHDWPgoRtGXmI7PwO0tnZqdFnzIPWZgkXVdescbfd8I8gDBfUzl41RQ5CP5C4YMnNPddQ7V51zBJEHTKQ77+TgclUZRWaTxWuhCk4WTxs++szTMLELjKLn/rIHx7tMi3vxTHUVSd7bdwBxPEmsOUBkGnVM2YfNi+g0Od8jh6zw/E++Gu0FdiyYNvImQzeT560z6y7bZ/LkG95POAZL4ltU76pLPn+03FhHe8m7t2EJD2WbE/CPIyzBxmXm2sLl0j9ktpciKvyjgyF3nd4BU/fBGm87ww46aqZ4EusorufAS+GDGm/wMk8yLe/4uRubW06PgzQ8ekxkYjimbsFJ7jMe8TwClx1S7vfRzc2nfCrDzH8ygIo4oG4iZm1n+brtM/d/OlmtvkeZTKZ2iRhIOhn3t64si5Iat/+4mK6NXixOsY50IZrtj7MqXnp8DNJy0fAGYMLswJHkFCuMqz7sPAWngAJTLpx4ZgncpKR0vZ54bttfNey/8l9lmtqa8tEMyJpvkIYu1eV3ovs66gt7xg+fpfnJNHs42O1mxijy/GTWeRctNQT8vL/NcAgmhuOD2AulKDKqULx2qZSqNWGGMr3q6pNTXUu2SEUJ+1x/tKS2a+8/3dINLRfRxWEYxCzfjLMhtC+DgUM5jrT4gwsbmCUtumoJMgozkY51PnzEnshoVH0O4fKMOXiAhRPJ9UPB5f8VaO0IofTSWG2SqNqpvzYgJYVyeVWEaVXpcsoy7jp/GSKKof1gjR6vPn3lxwsS9CDxtoyRKzmmuA0BHrxB1QYAUB97iwZMRpzoNkqRq+M+cL0gGR0EfI8X1SJMR4z/axW6tjsyWRSKhs7dQZD0wxxrQ/7vX0BJF4wQmYioRTJMbaPTpkPpWBmgr8a9XV4cId/f4smEq+TF4+Yex0gLX/6+jW6CkEsMB/r5c0+h8zxk15qDxomx2SAVTSHQJqjS+HF0BRy1NyYtVnI1AU3Vlzedvf679hSnqsWuKNfUk7/PWsfnN9ptZiAh39O1MbEDVFRQP8Tk0gB6aMjZ8Nd+aFtfJvXVc5yxQxPNubJfEOZo1DfuTSfaMpFrKrl9eYsnXVeuXPvwyPB216dgGq7KfuHC23cYaUfkfCAm/MgI6+y96hEMoTJhQhwSr0lhh9CthhXiDM7ckzWGLXPOJmdDNFmY7SAUoa68JTy17h0ktfzmlY3ou3U05pYeTMNvIFLA2jCfHHE05jM7PbQPajv0SckyP3n7VlQxtLnLJhQEFUq2f0OmEcf5DAZhD/JwfRjGv4FACl4RORcwixw2B4DSKEsaZEoDAGdtfszTxpi/+9K0Lt2qJ3n4yopxNPmlHWUIZgN5ZXgYeSBSoTU8ZhGTwIwX7QigHdUlL8JMWvRF8+yXykq/hRcG7Ox8cn44OVEjxRpjPNrRpsmVhqntASwyE9q3W4wEehf0CPAhRpxQ6chbog8sSjVoHCtGceG/w69evF5j4mVCxwrXpfwVysKGCXHdZ/UvCxccDwqVxeuQl01miWcPFYk4V3DKU3eIK8rCz5IWx7zvUO1BTZUHjBHITQumpwXOCOcIt7U79LBB9wlFhl5/0ifBkydjm/T5aDbjjxhjQ7BR/pUjeRn159Ikq7aebDt8u9566QQcy9acKl+020pcv7E4GEutu/N5HcHK5jJL042xQloLqJiH0tT/O826eptb4bkolYZ1c07BEimrVbyN1+BhyTfGvOynt53VSpSpggFm/eLsbGSnMAxbZQdt5v7OWQ8kIIoVg6WniKHJOtfu8bPcwZv7miqetq/yHxxQO7vliDaUM8nbWfGKUn1AhjiR33aoIWxsCaDX6jddfJudlRw6qBW8eNmG0pTGBoZ7uk0FS3WA0pTI+zjTd+dfI2wQ1Bn7GRzFOZzZduUnjgGxudt812gKQmxw6BJ6eT8MIB5zabiSVofZVoH5WE1RiXNfOrRDzWd61nHk4JhPNs3rsWt3xtg5zl/HrZU51Nohd1jqeatrVFJ/dRxvwVktiGZ95j8NDGNDWGwk9V88gjCY/4qxsAjXmiZk5cZwkeWwK3eSrUyK/4iWNnT2SlMBwRusiaC51zhqjURyFFaE5WBGgTauO/YeNIDrNIFNCTc3tuLNDmxh+RJ8baHxxl+gr7QfmQ6S0OXi84EmKvTxQogUO5EjrWAR+TAMSPpBzKM62rjrtvkIZrbbaos88ctaAKo5xQinpRaym3q8XwCY1AtdH48YG2JYAzC6ir+bWEM0sIchNsxHAamBWTCzenqhnnogzQyQQtITpRWeQ0Eain2KGM80wXZJEu7RCj47DzyBUkGOwGI9YAs0oPi3eeDvwacoHfaJTcxcrPw69jbFqaaJ4xbZSSQO4SELXMoIzI9z4F3hRrYtKz94qr7UEEOuclPRh/KGN30Vb3yOSXvWZ3rZmlQKM4gHmWMw+cjO9pIfyclar/pPAhBM7WfoQVB3VFL3TP6MQmroi8xz4PxoO9Y7zyykQZP7iRwOj6kdDp1unhgDX1yfZcs1nAI7UBCV06UVR/bsJ/3xJjn5GxI3Gl9cy1p/Lcc7VKSvWvOEYiKFIv6g8+vFlY2lXl4l47bw1iR+my80eb6utC1eOunp4t7QtFyfAPgPJDEauMBnYkTxT7PvNl/MJo4nl18155o0BS1LiLf39Yf26zT0bHwWCOVjOLO1wXQUoOUx6i7fw0/xIyYV3ABxEd/u9FKP46zDMQupZNqCh8wtHLn3NNn5W+Qc2BuAnW0UNJdQfRofJyJVpWl1/ea6AylPUvXaUwlvbdB64782VRbrLsRClrj9zRltXqKdlaH+W4jMP4DAU+gDKRuqebKb5YaDKj9pEH7Is33pEDkfyOJbcO/JAiBXNkqrV7zPIwlvYVDw8VsaOCk/if+82XPhF/shqM1YNmv2byNf+wv1S4fCoxxnl4EDqdQ9lWr90fpHFCfi/xFl0r3hClw27H3xJVm4EQv+0TiOmdx/q/tINMAwjkLXvAv3d8tMUMt5Lns63OBfHuS/1p5y9rFuEr9wviN3kQDNEMgmYxFTKdkLmw+Ndly3hdhLOtkozGNdqcOlCRz3usRyeqxfCWYb6Li573Ebl/fFExobWFec+HwiwD3qvCtR+btDuiNrCMLZpPrsQQoWVAlr+mM31uxszi3fz49/yS7uHzhj7OlGCg8bj/M15XxqCjQd7tT3bZ4mTM5Vcz5bznGHFiyRPjJcOTO7atIGDZPIgarVMenroMZB9HTnEjfA7eDxopC4APJZUpAqiHAoMAyn5beZseQxbJaCihxn/zOMkMRIgJjfAB5C1T5L9UfNZDGUp/LPoZ+gAyVH597SnVowF0fWm93lBagLPB17r4achI8P186QrdXP0VTOjeYC4xczBhHR2/YNvKAyvtfC64fj2QUi
*/