//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_DESTRUCT_N_HPP
#define BOOST_MOVE_DETAIL_DESTRUCT_N_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace movelib{

template<class T, class RandItUninit>
class destruct_n
{
   public:
   explicit destruct_n(RandItUninit raw)
      : m_ptr(raw), m_size()
   {}

   void incr()
   {
      ++m_size;
   }

   void incr(std::size_t n)
   {
      m_size += n;
   }

   void release()
   {
      m_size = 0u;
   }

   ~destruct_n()
   {
      while(m_size--){
         m_ptr[m_size].~T();
      }
   }
   private:
   RandItUninit m_ptr;
   std::size_t m_size;
};

}} //namespace boost {  namespace movelib{

#endif //#ifndef BOOST_MOVE_DETAIL_DESTRUCT_N_HPP

/* destruct_n.hpp
VvircDydJtO/IBwF7zU2BFeF3g22BeL+2vCqyL3RnZHxQjgGYkEZNTKJK3E5LhlCDDVEND/sef5UgKkgvEEtWhnh+sNxKNgSgT66DvrIcOgPj0N3/J7QjNMA4Fc8KPcV6qfItC2WLuEQ3rmXLOpuepUm15d1Ejoiv5JeSH+FhWTMQYW4VCgVt2JpPTA0+VjNxto+9W1lL1omaZpPRXl/l42iHbegaEsNiib+AUVdFUPObloA6wUyZvMAePsVYuPD9UB06JgKj4sYXO6YKZjx0ajMbaon7YZAINSQWb9VoNHSBrZZ0vQkxnhz8xSXMHUFWoDxNmGbuBxLIRiqYnWdWyv23u3bpN/tXxNoCa41YqEZRnWgUK8OGHqtr0hPesNaSC1QKuQyoFU6mu3XhMIQSCYkIJlCdUQgpWhBci6hJfKR5goi5oHG2jz1lAe9RcbidgBWQdpyivLWgw/vebPZwLSxuw+6TlkOmDVxCS0ZFnqdXtARw5VSg7xMOUmv5mChTGokTYmgv3lP20enuN/B5wBU/taDpkIK2OOF8+hz+Y4IJXaH0Qr6U8XtmI3MrW7641E3/fVpYJp9/sm/dYoFz3vLL8I+dAuW3pV9ICZv1NZ7fWqhkpR0cbZg4ALglnWpQV8lHfet8j9MjgbwbJH2ru6TFBCMr2ZrfuC3g2L9HIUfxGzMbl/K7Et4zl6G3Gv0JfzAbzAqT+vnx8D6
*/