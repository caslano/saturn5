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
3nf6/c6d6oXPxO1x5nmt0axZXAP+kzEqQcatn/3+LuMLcvs9z7WeRb973M7L+Y6Nyzdx9PObtTKu/tbK3BUofJ+nsXMY/c0qvoEjMZy4peqohTpHZv5NP6Xse42dryx7sd+sMq93tS7CzOvdVKbklXKi7EiXsiOvv5TZWjkf0EUk9STWXvQ7r6+5dK9S3Wyk0u3nWbT/JU/j+zfm7WmjozBUe3/liEXER6Hsx7x0PUvOSkjmKOK6PRn7xImSdwrDl3W/T/TSdcV43yc2Su8XX5L+YywlKQk5xrq8i7RX+gfr92++le4AGZ/N+d5Gt+SsbF2XfpH+/vpdrvnSbZe6/XmonElx/sVH5eItzvfZ/nrnjmM99/H4V9azfr4p42H8pOnxS9nnexU9Rv6our9RzzOvqO6zoUWPWSvUzvFH2QbpT/QjT2QJvW5S0uMT5KuryfKuoD73Y/oyX7qMq8kwR7h/ZnW/H5T+VvMzQMZqfI/xlvT3l28jb6bO0OY47xag3eqfQ+Nm9UiP8aPcSN8SJul+nl7htoZevrYAv05e1Wz3869wv3ZeFf1L1aC82A6Zrmx/o4z3CdS7NPo8Uh/zhsn08yyNKN3pFg+ZjwymZ/d3br/+weP9baEWfTzKD3Mejwqj8Hi2lfTP3RyHvIvsw12/pavLU9ZXZomi5xxjVfdzFZzdeSWKfuN/o0v+fJ2/6LcI25VyzsBLhB+RS5yLlDaJ3KzvWF1WVnl31e3xTQ1rdVc33J/Pe7utB/ocpY70z7aUZc67EcY7apxqpmemJKcl6v1wV8nbiO26sn4P1rR/1/maS74Aiw97veqWJ2SetrGethMbgo1nxuZ/u5wTF/etXvWNKspH74td16l6D0K/22Ash3wXTG2Ll0ur7/WqbfEZtS2udb9unhyRLNX3H26T78mwmZZh7rdJxv2Pt8kaPsY22Ym6M4953BHm3CYHsb+vTPp50ueUdtkm/YZ7VbB5eNn9PcNlu1Db4W4321/hOroi81KOMgnW+/3SPuo7feq9MDvTySVkewzr+F/ZFn/3NrY1877zooyRdMKTGEacZ3qtfIqur9T0hBEpiVnMv/mb1exNTecm7XyKvXZW46OvXkfZ6bFDMxOZPb2eO0qeOEs0/y08P/6UefnM9D4Vc0388Teow1y/Qa3m1XxMbxXkHKCnxfBmCPXJWPbU+JSU9CEW83v5WWOL2YcwnOv9gVFJ8dnu9x86rz42j8wwl+V26R+ij823nfn18WCnsc1TLn/8LTrHte4dGUcA70g1ku7buruxy7tQsowu176yLFKXrvuodr/Ci5Zn1RDnBJcTJYhlRK9QOSlQ5SnntqO4ZVz0XLy+cfzyk7xzLH3Zx00i3JSzGp+16DgaMA51Pecp/RdbBvLf5wg35c84XH8P4Zi1+rr8h0n/QLfvErkftoEedo4a1t33BPWwxnv/bKPGu9htpf9AytVDrlu7Evr762GOuPtrQ31+Xd91XUp5SZq/ftdNll/SAoqkNSiyv7CUUdO00h9/IxqGU5+NdZydyheAEzNHxqcU3W6y0zOK2W58Xa+pRvBRfvn0qfttx1SGrc2/41C/QTgg/X/kGKm2LXtc0fnSV1eZsm3r32XIcPXYc4fJuL8Idb7PPEpt7ycYt5H+pxFpwy36PWe+ccOwyyirVrIc70bKuh2TJYvBvKl89SXfDMmzhzzeXJNJych8tFXnCLxfIPm8JC1YlVOuSlPHC33dVdVcGe7ifFxt40zV9brLKHfySlm2lvTCY5y/lOcGue6SwmN4f1mOfEeaLEt8JnklHflzpI+Kz0zjlq6zbko5UoaMl7JVaecL01S5hqk0ypE0XY6y/zniW/Q=
*/