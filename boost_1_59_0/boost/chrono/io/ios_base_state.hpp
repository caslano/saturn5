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
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
*/