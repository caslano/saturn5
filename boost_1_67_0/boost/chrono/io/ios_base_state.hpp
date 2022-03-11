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