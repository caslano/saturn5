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
W9uHXc70spkffR/2rymf7wKHAf8GNO+5OzPIeA50FJQ8DLaxQK2gfaAjoPJM/3bDjoOisa84BZQDygfVgVpB14HaQQe89h9ncA9yC2gbaDdoP+hF0BHuTY47E3ygYlAVqBnUDnoRJDbFQMnZsOsFmghaBqoD6XuZD4GOgj4HOUYgPVAxqAq0CbSdtsaeAx0CvQc6DgoZifuDdNtjzaAtoJ2gdtBzoEMgYxR4QemgiaBy0CbQdm3v9EHQEdBxUESOuZcavKACUB2oDeRtfyx6NOoUlA3KA5WDGkCtoDZQ+vxwIw+0DLQJtBP0HOh9UMSCcCMDlA+qAbUuOPk92V/593/zwNLTpP9/LM19Dn8Bn2PoG8r++G6EZOfo74ZydyPVWo8LKdf9h+Tmlo/En6p19e4zNMZI/OgurK85JM2cw2a/kyTUXD/jNM71/c81T987wOmauz8ic/fGjPyeP3j5lxdMTc3bffiPw+cEmqMHmtMHmqMHmhMHmkMHmot/9bbUT/ZdwhrLRW4pz8d0nRo+Ww0+S52cK+/+LxzL/5PH8dM1hnuP37tOYUzuvv7J3nnAV1HkcXz3vTRSIAUihJJCCwmBBBBDD8hhBMUAilRDCIEEQhIgFHtAVERPET1FbOihFFGxHire5dSznSUqKp4NEHsDQeTEcr/9v9+bzHtvN4QT7vTuPT7LN1N3duY/Mzuz/5kJ/oK/4C/4C/6Cv+Av+Av+jtXvmI//p1t+rQmAXz7+/6q9ob6ZjjPtv5muyWn8N1P4bfCb6e05v+ybqfc7dm6ox/e7uGcOuBXs3Qb5IPEvZmZKTvF8a12X2ecceIYZoPSMY3pY5lvM+mecXTmN/kco/yconfVw8X+DWX9m4/TyohnzxL0C7v3FvVzcq715Upit9u7JEfeJZpkRh7NM0pFW2MNmtdi7IEg7PecT48kjJP3132XvFD+hSme5qKfoU9HdNK4Qcyp1/uvjjDY+gt2JceUmZVbsY2nnsWwudtdp6Z53jlfXLwEcLe6rIG9dkBtpSgfrMsueOmDHZ1khFloZKPsmjZSomYcoNatc5oSJH1UwTanr+LHEczvCwazSHo38eE90wCfBT613fYD7BOgUdRXNjQDZZF7FSvi8QNlkOUSKe4roY6Qx/vQQb/yLsxB5aJilvWT9EWUYTvdxS573sL1PmfX84t5F6X0UGHY/86J42dusr+g6jDRdRmK9vh/MzK769SK0R1bTzsAP+Q87yX/5jj68B/cLSTPEPJbmjDYe8/l+7pf5ua+huXeWx/y1n/+Tevqax9GcS//Tve6Mb74y69/1nebEnObWnObEnOaOjv2clf1cnNOclfMc3fsyB7j267anPvbc/fsW9nmpqqLuwyin799Oc3THfn8k+7nTI/8ef6RzrU5zqges9Gvf9XP5Xd/z3Yj9FPu63F/43WiRas9gx3PN9P1q4vj9Mp7feZuDfWk/gOYJ/C7/CL+HP8/v4W+DGaAbcWaDD/K8sa3cP6kWxJzkYectD/b9dc1bOn2Dql7w65m/PNbfoQ5iHjP29OBcZvAX/AV/wd//yu/Yj//LquYdpe//n2nf/0M4NnPzOVy4+rbA+7hn/D/s5IIxhZ7RhXHYb/n6WH2Vdq5ADK5+uMYn4F3eL95C7Adr+OznrPaop99ePKe8fr1nboPrI/U113OD4wub8UXMZMv+xs+z6lrXDqq5+6Ko08I+/O7S4PjiMOML6hiwbrDORPjpi8VyHNGc44hEpQeIi+HyGE7XA2zF8UZbMA5sBzbX9HmTwT5gCtiP9lsaOQ74LYwB/l/e/8/Du/+1wff/4C/4C/6Cv+Av+Av+gr/f/O+Yj/+nlR21/f8+0vY=
*/