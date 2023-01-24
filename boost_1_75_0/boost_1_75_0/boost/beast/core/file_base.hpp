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
nECc/D4D770NQIpABu76TAK8wDRiSPdj6ECKUbySrbw9whgEFJC0UM0jj1b6wvlrd6Q6I+KHmBE1cVIU4UwrfQ4a1Ca0DWJFVu55TLr+JXn2f1CoF346teO4Gdjkqx4kZ2fIMXsdF2QaVMBtjSq8KrCfZJOP3sfQnBbKSX44jGQ/ZvF82hdUA16EcziFbDq9ku9tvsMHa7XXEI+yy9GUJT8K7p0WlbuedcHMFdJu9eEM3B6dkJE6N0QRhBXlQOnN1V0ecN+xppThp4endThrW4nY1nYvQm0hCo3PZ3jqAtjm7xYsRNh6blh54YXSqYh9p8Ersm4GCrNyaqpd9dywrYz+Mhsq+5C8VLAlIYzCfgFeqHFly2HFlo3QhUnu38IJTDBY0gUuoZS+i8WwikKZtituCJsxXQQyXNoWNjFwtgn+lYiF7qSAwfwrdnwAvRESf2XbwgYoStPafiNsRJZdnejPtB1yv9qGlRu9N4Qa0912oWXv79Vc0CLHYOi4A9qo9WnQ+jSixjOxbVkVJvUeQZAqegOm64krwdYe/GasP/nmBCHHFdfBctwMX5iUpWwV1ZpNk/VYsfTsXdBj+2zgYniP7gleMSDrSRr6wdhmHCDSy1MW+XmFMJlLRsEhzw3jmVYgdMS0PX9UyWn/yivpzK6uB95qn0N3n9Le/OsJcy3rXYWgvoHGymn8IiORhrHe2lyWY6i5YbY8Q08o
*/