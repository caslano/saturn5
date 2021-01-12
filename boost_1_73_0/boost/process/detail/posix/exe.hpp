// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_EXE_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_EXE_HPP_


namespace boost
{
namespace process
{
namespace detail
{
namespace posix
{

template<class StringType, class Executor>
inline void apply_exe(const StringType & exe, Executor & e)
{
    e.exe = exe.c_str();
}

}



}
}
}



#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ARGS_HPP_ */

/* exe.hpp
bIfh0x5/RQAu/iKvW7Va3ckHZZeoBnXCoB7DkEINtr94K4TSBDBdlsNAyov6fWeYIZ00WUlbKI5oVrZAK4LIkoTIyqTGQgi8Bk/sZyPKVh4jCv9BAncjRarLADTysgE4hiMfSx1Gjut04lkZJHY18VcdnpzSa9IiRcf88kSrx26XPtzE895XUo/7g3ot51n6UXMwSD9qNZrZcq3m4clJ7QIKbyx1l8YLREhoJdOH4uH7ZOIK
*/