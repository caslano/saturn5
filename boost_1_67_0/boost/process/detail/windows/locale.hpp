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