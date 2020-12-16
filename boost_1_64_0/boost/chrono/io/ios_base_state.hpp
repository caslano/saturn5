//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_IOS_BASE_STATE_HPP
#define BOOST_CHRONO_IO_IOS_BASE_STATE_HPP

#include <boost/chrono/config.hpp>
#include <locale>
#include <boost/chrono/io/duration_style.hpp>
#include <boost/chrono/io/timezone.hpp>
#include <boost/chrono/io/utility/ios_base_state_ptr.hpp>

namespace boost
{
  namespace chrono
  {

    class fmt_masks : public ios_flags<fmt_masks>
    {
      typedef ios_flags<fmt_masks> base_type;
      fmt_masks& operator=(fmt_masks const& rhs) ;

    public:
      fmt_masks(std::ios_base& ios): base_type(ios) {}
      enum type
      {
        uses_symbol = 1 << 0,
        uses_local  = 1 << 1
      };

      inline duration_style get_duration_style()
      {
        return (flags() & uses_symbol) ? duration_style::symbol : duration_style::prefix;
      }
      inline void set_duration_style(duration_style style)
      {
        if (style == duration_style::symbol)
          setf(uses_symbol);
        else
          unsetf(uses_symbol);
      }

      inline timezone get_timezone()
      {
        return (flags() & uses_local) ? timezone::local : timezone::utc;
      }
      inline void set_timezone(timezone tz)
      {
        if (tz == timezone::local)
          setf(uses_local);
        else
          unsetf(uses_local);
      }
    };
    namespace detail
    {
      namespace /**/ {
        xalloc_key_initializer<fmt_masks > fmt_masks_xalloc_key_initializer;
      } // namespace
    } // namespace detail

    inline duration_style get_duration_style(std::ios_base & ios)
    {
      return fmt_masks(ios).get_duration_style();
    }
    inline void set_duration_style(std::ios_base& ios, duration_style style)
    {
      fmt_masks(ios).set_duration_style(style);
    }
    inline std::ios_base&  symbol_format(std::ios_base& ios)
    {
      fmt_masks(ios).setf(fmt_masks::uses_symbol);
      return ios;
    }
    inline std::ios_base&  name_format(std::ios_base& ios)
    {
      fmt_masks(ios).unsetf(fmt_masks::uses_symbol);
      return ios;
    }

    inline timezone get_timezone(std::ios_base & ios)
    {
      return fmt_masks(ios).get_timezone();
    }
    inline void set_timezone(std::ios_base& ios, timezone tz)
    {
      fmt_masks(ios).set_timezone(tz);
    }
    inline std::ios_base& local_timezone(std::ios_base& ios)
    {
      fmt_masks(ios).setf(fmt_masks::uses_local);
      return ios;
    }

    inline std::ios_base& utc_timezone(std::ios_base& ios)
    {
      fmt_masks(ios).unsetf(fmt_masks::uses_local);
      return ios;
    }

    namespace detail
    {

      template<typename CharT>
      struct ios_base_data_aux
      {
        std::basic_string<CharT> time_fmt;
        std::basic_string<CharT> duration_fmt;
      public:

        ios_base_data_aux()
        //:
        //  time_fmt(""),
        //  duration_fmt("")
        {
        }
      };
      template<typename CharT>
      struct ios_base_data  {};
      namespace /**/ {
        xalloc_key_initializer<detail::ios_base_data<char>      > ios_base_data_aux_xalloc_key_initializer;
        xalloc_key_initializer<detail::ios_base_data<wchar_t>   > wios_base_data_aux_xalloc_key_initializer;
#if BOOST_CHRONO_HAS_UNICODE_SUPPORT
        xalloc_key_initializer<detail::ios_base_data<char16_t>  > u16ios_base_data_aux_xalloc_key_initializer;
        xalloc_key_initializer<detail::ios_base_data<char32_t>  > u32ios_base_data_aux_xalloc_key_initializer;
#endif
      } // namespace
    } // namespace detail

    template<typename CharT>
    inline std::basic_string<CharT> get_time_fmt(std::ios_base & ios)
    {
      ios_state_not_null_ptr<detail::ios_base_data<CharT>, detail::ios_base_data_aux<CharT> > ptr(ios);
      return ptr->time_fmt;
    }
    template<typename CharT>
    inline void set_time_fmt(std::ios_base& ios, std::basic_string<
        CharT> const& fmt)
    {
      ios_state_not_null_ptr<detail::ios_base_data<CharT>, detail::ios_base_data_aux<CharT> > ptr(ios);
      ptr->time_fmt = fmt;
    }

  } // chrono
} // boost

#endif  // header

/* ios_base_state.hpp
nn02BvSyNiF1fUbrb6Z9Jnz6LF7Gs0WWcPjaiJZlhime8VhbW5vaeptsLGPZd5f69N3DDdB3yga0X99BPsMeWN33qOpqh8t8T6vh9tjM9/Aabk/Laq8o4n4t/fZ9W1/tHbPrgjWHBjmOr5v+lNUem9UeVd338Mz3tKz2COtu362ue2DqbPYCry2T3j5nsztwT6YjbZl04l5Olno+xNpNvlCdHbMy7t3MAiZTf7IJcD7PbN/GeuZ4nqmAu1gPbUyoM/jNgfnAjsCJtHFSArwcWAAcTBs3I5h+I7AIeAtwEnA+8GbgUtq+Wc5yynYO2xFh0v6ebH8vYDjwCtV+3sMt2n8n238X238327+Y7V+kqyeTv59oUk9X/n4m67sYGEubLAnA7qoe3ucs5FlK/mWUZznlWUl5VrCeyYL3DOBY1hMJnOBZvGgjaxD35AbTBscI2si6imfwh3CPdChtXwwDDqFNrByW9/ye4O+NN/m9HP7etcB02o5oA7wOeBFwHPVvr+c8uIHzYDzwWtqcGMP4aYeodb9w3JeRP7nz8D/VfcNyjFUFaDfoMOgkKPyrSJEBuhw07it7T9EOdrCDHexgBzvYwQ52sIMd7GCH/7B3JvBRFXccn7ebLJADQgghJBDu+wp3uMMpIGBA5FA0CTlIJMeSAyKgolilLQpyKCpqvKGliq0HVqvxqHiggqKAYkXqLRZEFMSrv/ff386+t9lNQqHWttnPZ/LNzJuZN29m3rz3Zn4z80v5/Uzj/+CZG/9Pv8U2/o+4PeP/3ZoqvWdJ5yDj/0eWWsf/EVS2OTo1DUDnIBqASk/cZqy10gDAfzUaAB4PrgHA8f+MBuCDIBqA1kv09VenAYA/uwZgyJLaawBaL6mdBmDskqAaAMYRXAMwfElQDQDDBtcAFCz5ZWsAVlADMIljfuM4/pzuq7sBNQB6z2PxN8i65zHDRut6mHHK+9lm2NMYRCNwZLFOY40aAfgNrhHg8Wo0Ajj+n9MITOe4/GSW0VksI+Uro2AaAZYTKH4Hq5a6nBie+xavSJBdCUq9eTYexzvI8QR9zYdrUY685qAag9b1AmsMKn1lWaPGAH6r0xjg+M+jMfAKZ15ju/cc6+XWS/S1VKcxoL82ut3bJfY/qFj8nQxzWXCtAcMmSthJsL8q9rtlz7SzYZYG2O83nm3Sy+L3BlxfuJoAk4tSYD1nvAkBx9kbg40kb6NUNOPqK/ZxsLewhGHbwzCdxE8yWs1oyYfWHj/wP0ry91s559UqHuUVqjzt4lkw5j5LpafZPlavf0A4+mvtaTPtdTVcyW8Py3c79RAV5bp8q9ND0F8brYd4WuwPq7ZV9RB6r+0nxc9alYByKVORLG8zLj5nxB/OInkWFnR/vMfF/yOqne85xzgSqt7v3HfvqBwvC1r2LeWcDl/Zi70XUtmYfrzpakpdhk5nlboRyzhPyjnPUy0QxxjlCFg/jnvyO2D9uPU060f1Go8q9aNO83EGNB+Phpnud729M2H7VdOuXdTyxk3Xjj321f+v5uPI0uCajyRqDnpT89HHojGoXBpcY7CZGoMt1Bj8gRqDh6gx2Ko1H3yHDaL5WEvNxw3UfNxIzce91Hxs4Fj/neBkul8I3kzNxy3UfGyk5uMe8Df059UcpPM6JlWjcRhNjcMYsDm1DK2ofehP7cMQah6Gg+OpdZjA9E20ajMWB8+3R5lv25hvjzHfHme+/ZnxpMIopnsy46kn6fP8+jPdycy3EWASOJj7MQxleoeDZ/G4Ltdq0vck0/cU01fJ9D3D9D2t9ynis5zvJ8l++xRNpv9pYEdqOjpz/4pkajVGUNsxgdqOOdR2pNFfETUei8A5LOc07us=
*/