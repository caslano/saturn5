// Copyright (c) 2016 Klemens D. Morgenstern
// Copyright (c) 2008 Beman Dawes
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_LOCALE_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_LOCALE_HPP_

#include <locale>
#include <boost/core/ignore_unused.hpp>
#include <boost/winapi/file_management.hpp>
#include <boost/winapi/character_code_conversion.hpp>

namespace boost
{
namespace process
{
namespace detail
{
namespace windows
{

//copied from boost.filesystem
class windows_file_codecvt
   : public std::codecvt< wchar_t, char, std::mbstate_t >
 {
 public:
   explicit windows_file_codecvt(std::size_t refs = 0)
       : std::codecvt<wchar_t, char, std::mbstate_t>(refs) {}
 protected:

   bool do_always_noconv() const noexcept override { return false; }

   //  seems safest to assume variable number of characters since we don't
   //  actually know what codepage is active
   int do_encoding() const noexcept override { return 0; }

   std::codecvt_base::result do_in(std::mbstate_t& state,
     const char* from, const char* from_end, const char*& from_next,
     wchar_t* to, wchar_t* to_end, wchar_t*& to_next) const override
   {
     boost::ignore_unused(state);

       auto codepage =
#if !defined(BOOST_NO_ANSI_APIS)
               ::boost::winapi::AreFileApisANSI() ?
               ::boost::winapi::CP_ACP_ :
#endif
               ::boost::winapi::CP_OEMCP_;

     int count = 0;
     if ((count = ::boost::winapi::MultiByteToWideChar(codepage,
             ::boost::winapi::MB_PRECOMPOSED_, from,
       static_cast<int>(from_end - from), to, static_cast<int>(to_end - to))) == 0)
     {
       return error;  // conversion failed
     }

     from_next = from_end;
     to_next = to + count;
     *to_next = L'\0';
     return ok;
  }

   std::codecvt_base::result do_out(std::mbstate_t & state,
     const wchar_t* from, const wchar_t* from_end, const wchar_t*& from_next,
     char* to, char* to_end, char*& to_next) const override
   {
     boost::ignore_unused(state);
     auto codepage =
#if !defined(BOOST_NO_ANSI_APIS)
                   ::boost::winapi::AreFileApisANSI() ?
                       ::boost::winapi::CP_ACP_ :
#endif
                     ::boost::winapi::CP_OEMCP_;
     int count = 0;


     if ((count = ::boost::winapi::WideCharToMultiByte(codepage,
                   ::boost::winapi::WC_NO_BEST_FIT_CHARS_, from,
                  static_cast<int>(from_end - from), to, static_cast<int>(to_end - to), 0, 0)) == 0)
     {
       return error;  // conversion failed
     }

     from_next = from_end;
     to_next = to + count;
     *to_next = '\0';
     return ok;
   }

   std::codecvt_base::result do_unshift(std::mbstate_t&,
       char* /*from*/, char* /*to*/, char* & /*next*/) const override { return ok; }

   int do_length(std::mbstate_t&,
     const char* /*from*/, const char* /*from_end*/, std::size_t /*max*/) const override { return 0; }

   int do_max_length() const noexcept override { return 0; }
 };



}
}
}
}



#endif /* BOOST_PROCESS_LOCALE_HPP_ */

/* locale.hpp
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
*/