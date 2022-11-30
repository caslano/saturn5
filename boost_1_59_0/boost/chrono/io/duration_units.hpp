//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_UNITS_HPP
#define BOOST_CHRONO_IO_DURATION_UNITS_HPP

#include <boost/chrono/config.hpp>
#include <boost/ratio/ratio_io.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/io/duration_style.hpp>
#include <boost/chrono/io/ios_base_state.hpp>
#include <boost/assert.hpp>
#include <string>
#include <ios>
#include <locale>
#include <algorithm>

namespace boost
{
  namespace chrono
  {
    class rt_ratio
    {
    public:
      template <typename Period>
      rt_ratio(Period const&) :
        num(Period::type::num), den(Period::type::den)
      {
      }

      rt_ratio(intmax_t n = 0, intmax_t d = 0) :
        num(n), den(d)
      {
      }

      intmax_t num;
      intmax_t den;
    };

    /**
     * @c duration_units facet gives useful information about the duration units,
     * as the number of plural forms, the plural form associated to a duration,
     * the text associated to a plural form and a duration's period,
     */
    template <typename CharT = char>
    class duration_units: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of character string passed to member functions.
       */
      typedef std::basic_string<CharT> string_type;

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * Construct a @c duration_units facet.
       * @param refs
       * @Effects Construct a @c duration_units facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit duration_units(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @return pointer to the start of valid [N/D] units.
       */
      virtual const string_type* get_n_d_valid_units_start() const =0;
      /**
       * @effect calls the do_...
       * @return pointer to the end of valid [N/D] units.
       */
      virtual const string_type* get_n_d_valid_units_end() const=0;

      /**
       * @return pointer to the start of valid units, symbol or prefix with its different plural forms.
       */
      virtual const string_type* get_valid_units_start() const=0;
      /**
       * @return pointer to the end of valid units.
       */
      virtual const string_type* get_valid_units_end() const=0;

      /**
       * @param k the found pointer to the [N/D] unit.
       * @return true if @c k matches a valid unit.
       */
      virtual bool match_n_d_valid_unit(const string_type* k) const = 0;
      /**
       * @param k the found pointer to the unit.
       * @Effects @c rt is set to the valid Period when the @c k matches a valid unit.
       * @return true if @c k matches a valid unit.
       */
      virtual bool match_valid_unit(const string_type* k, rt_ratio& rt) const = 0;

      /**
       * @effect calls the do_...
       * @return the pattern to be used by default.
       */
      virtual string_type get_pattern() const=0;

      /**
       * @effect calls the do_...
       * @return the unit associated to this duration.
       */
      template <typename Rep, typename Period>
      string_type get_unit(duration_style style, duration<Rep, Period> const& d) const
      {
        return do_get_unit(style, rt_ratio(Period()), static_cast<intmax_t>(d.count()));
      }
      /**
       * @effect calls the do_...
       * @return the [N/D] suffix unit associated to this duration.
       */
      template <typename Rep, typename Period>
      string_type get_n_d_unit(duration_style style, duration<Rep, Period> const& d) const
      {
        return do_get_n_d_unit(style, rt_ratio(Period()), static_cast<intmax_t>(d.count()));
      }

      /**
       * @effect calls the do_...
       * @return true if the unit associated to the given Period is named, false otherwise.
       */
      template <typename Period>
      bool is_named_unit() const
      {
        return do_is_named_unit(rt_ratio(Period()));
      }


    protected:

      /**
       * @Effects Destroys the facet
       */
      virtual ~duration_units()
      {
      }
      /**
       * @return the [N/D] suffix unit associated to this duration.
       */
      virtual string_type do_get_n_d_unit(duration_style style, rt_ratio rt, intmax_t v) const = 0;
      /**
       * @return the unit associated to this duration.
       */
      virtual string_type do_get_unit(duration_style style,rt_ratio rt, intmax_t v) const = 0;
      /**
       * @return true if the unit associated to the given Period is named, false otherwise.
       */
      virtual bool do_is_named_unit(rt_ratio rt) const =0;

    };

    template <typename CharT>
    std::locale::id duration_units<CharT>::id;

    namespace detail
    {
      template<typename CharT>
      struct duration_units_default_holder
      {
        typedef std::basic_string<CharT> string_type;
        static string_type* n_d_valid_units_;
        static string_type* valid_units_;
        static bool initialized_;
      };
      template <typename CharT>
      typename duration_units_default_holder<CharT>::string_type* duration_units_default_holder<CharT>::n_d_valid_units_=0;
      template <typename CharT>
      typename duration_units_default_holder<CharT>::string_type* duration_units_default_holder<CharT>::valid_units_=0;
      template<typename CharT>
      bool duration_units_default_holder<CharT>::initialized_ = false;
    }

    /**
     * This class is used to define the strings for the default English
     */
    template <typename CharT = char>
    class duration_units_default: public duration_units<CharT>
    {
    protected:
      static const std::size_t pfs_ = 2;

    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of character string passed to member functions.
       */
      typedef std::basic_string<CharT> string_type;

      /**
       * Construct a @c duration_units_default facet.
       * @param refs
       * @Effects Construct a @c duration_units_default facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit duration_units_default(size_t refs = 0) :
        duration_units<CharT> (refs)
      {
      }

      /**
       * Destroys the facet.
       */
      ~duration_units_default()
      {
      }

    public:

      /**
       * @param k the found pointer to the [N/D] unit.
       * @return true if @c k matches a valid unit.
       */
      bool match_n_d_valid_unit(const string_type* k) const
      {
        std::size_t index = (k - get_n_d_valid_units_start()) / (pfs_ + 1);
        switch (index)
        {
        case 0:
          break;
        default:
          return false;
        }
        return true;
      }
      /**
       * @param k the found pointer to the unit.
       * @Effects @c rt is set to the valid Period when the @c k matches a valid unit.
       * @return true if @c k matches a valid unit.
       */
      bool match_valid_unit(const string_type* k, rt_ratio& rt) const
      {
        std::size_t index = (k - get_valid_units_start()) / (pfs_ + 1);
        switch (index)
        {
        case 0:
          rt = rt_ratio(atto());
          break;
        case 1:
          rt = rt_ratio(femto());
          break;
        case 2:
          rt = rt_ratio(pico());
          break;
        case 3:
          rt = rt_ratio(nano());
          break;
        case 4:
          rt = rt_ratio(micro());
          break;
        case 5:
          rt = rt_ratio(milli());
          break;
        case 6:
          rt = rt_ratio(centi());
          break;
        case 7:
          rt = rt_ratio(deci());
          break;
        case 8:
          rt = rt_ratio(deca());
          break;
        case 9:
          rt = rt_ratio(hecto());
          break;
        case 10:
          rt = rt_ratio(kilo());
          break;
        case 11:
          rt = rt_ratio(mega());
          break;
        case 12:
          rt = rt_ratio(giga());
          break;
        case 13:
          rt = rt_ratio(tera());
          break;
        case 14:
          rt = rt_ratio(peta());
          break;
        case 15:
          rt = rt_ratio(exa());
          break;
        case 16:
          rt = rt_ratio(ratio<1> ());
          break;
        case 17:
          rt = rt_ratio(ratio<60> ());
          break;
        case 18:
          rt = rt_ratio(ratio<3600> ());
          break;
        default:
          return false;
        }
        return true;
      }

      /**
       * @return pointer to the start of valid [N/D] units.
       */
      virtual const string_type* get_n_d_valid_units_start()const
      {
        return  detail::duration_units_default_holder<CharT>::n_d_valid_units_;
      }
      /**
       * @return pointer to the end of valid [N/D] units.
       */
      virtual const string_type* get_n_d_valid_units_end()const
      {
        return detail::duration_units_default_holder<CharT>::n_d_valid_units_ + (pfs_ + 1);
      }

      /**
       * @return pointer to the start of valid units.
       */
      virtual const string_type* get_valid_units_start() const
      {
        return detail::duration_units_default_holder<CharT>::valid_units_;
      }
      /**
       * @return pointer to the end of valid units.
       */
      virtual const string_type* get_valid_units_end() const
      {
        return detail::duration_units_default_holder<CharT>::valid_units_ + 19 * (pfs_ + 1);
      }

      string_type get_pattern() const
      {
        static const CharT t[] =
        { '%', 'v', ' ', '%', 'u' };
        static const string_type pattern(t, t + sizeof (t) / sizeof (t[0]));

        return pattern;
      }

    protected:
      /**
       *
       * This facet names the units associated to the following periods:
       * atto,femto,pico,nano,micro,milli,centi,deci,ratio<1>,deca,hecto,kilo,mega,giga,tera,peta,exa,ratio<60> and ratio<3600>.
       * @return true if the unit associated to the given Period is named, false otherwise.
       */
      bool do_is_named_unit(rt_ratio rt) const
      {
        if (rt.num==1) {
          switch (rt.den)
          {
          case BOOST_RATIO_INTMAX_C(1):
          case BOOST_RATIO_INTMAX_C(10):
          case BOOST_RATIO_INTMAX_C(100):
          case BOOST_RATIO_INTMAX_C(1000):
          case BOOST_RATIO_INTMAX_C(1000000):
          case BOOST_RATIO_INTMAX_C(1000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return true;
          default:
            return false;
          }
        } else if (rt.den==1) {
          switch (rt.num)
          {
          case BOOST_RATIO_INTMAX_C(10):
          case BOOST_RATIO_INTMAX_C(60):
          case BOOST_RATIO_INTMAX_C(100):
          case BOOST_RATIO_INTMAX_C(1000):
          case BOOST_RATIO_INTMAX_C(3600):
          case BOOST_RATIO_INTMAX_C(1000000):
          case BOOST_RATIO_INTMAX_C(1000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return true;
          default:
            return false;
          }
        }
        return false;

      }

      /**
       * In English the suffix used after [N/D] is the one associated to the period ratio<1>.
       * @return the [N/D] suffix unit associated to this duration.
       */
      string_type do_get_n_d_unit(duration_style style, rt_ratio, intmax_t v) const
      {
        return do_get_unit(style, ratio<1>(), do_get_plural_form(v));
      }

      /**
       * @return the unit associated to this duration if it is named, "" otherwise.
       */
      string_type do_get_unit(duration_style style, rt_ratio rt, intmax_t v) const
      {
        if (rt.num==1) {
          switch (rt.den)
          {
          case BOOST_RATIO_INTMAX_C(1):
            return do_get_unit(style, ratio<1>(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(10):
            return do_get_unit(style, deci(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(100):
            return do_get_unit(style, centi(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000):
            return do_get_unit(style, milli(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000):
            return do_get_unit(style, micro(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000):
            return do_get_unit(style, nano(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000):
            return do_get_unit(style, pico(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000000):
            return do_get_unit(style, femto(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return do_get_unit(style, atto(), do_get_plural_form(v));
          default:
            ;
          }
        } else if (rt.den==1) {
          switch (rt.num)
          {
          case BOOST_RATIO_INTMAX_C(10):
             return do_get_unit(style, deca(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(60):
            return do_get_unit(style, ratio<60>(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(100):
             return do_get_unit(style, hecto(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000):
             return do_get_unit(style, kilo(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(3600):
             return do_get_unit(style, ratio<3600>(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000):
             return do_get_unit(style, mega(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000):
             return do_get_unit(style, giga(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000):
             return do_get_unit(style, tera(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000000):
             return do_get_unit(style, peta(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000000000):
             return do_get_unit(style, exa(), do_get_plural_form(v));
           default:
             ;
           }
        }
        BOOST_ASSERT(false&&"ratio parameter can not be translated");
        //throw "exception";
        return string_type();
      }

    protected:
      /**
       * @return the number of associated plural forms this facet manages.
       */
      virtual std::size_t do_get_plural_forms() const
      {
        return static_get_plural_forms();
      }
      static std::size_t static_get_plural_forms()
      {
        return pfs_;
      }
      /**
       * Gets the associated plural form.
       * @param value the duration representation
       * @return the plural form associated to the @c value parameter. In English there are 2 plural forms
       * 0 singular (-1 or 1)
       * 1 plural for all others
       */
      virtual std::size_t do_get_plural_form(int_least64_t value) const
      {
        return static_get_plural_form(value);
      }
      static std::size_t static_get_plural_form(int_least64_t value)
      {
        return (value == -1 || value == 1) ? 0 : 1;
      }

      /**
       * @param style the duration style.
       * @param period the period associated to the duration seconds.
       * @param pf the requested plural form.
       * @return if style is symbol returns "s", otherwise if pf is 0 return "second", if pf is 1 "seconds"
       */
      virtual string_type do_get_unit(duration_style style, ratio<1> u, std::size_t pf) const
      {
        return static_get_unit(style,u,pf);
      }
      static string_type static_get_unit(duration_style style, ratio<1> , std::size_t pf)
      {
        static const CharT t[] =
        { 's' };
        static const string_type symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const string_type singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const string_type plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol)
        {
          return symbol;
        }
        if (pf == 0)
        {
          return singular;
        }
        if (pf == 1)
        {
          return plural;
        }
        BOOST_ASSERT(false&&"style/pf parameters not valid");
        //throw "exception";
        return string_type();
      }

      /**
       * @param style the duration style.
       * @param period the period associated to the duration minutes.
       * @param pf the requested plural form.
       * @return if style is symbol returns "min", otherwise if pf is 0 return "minute", if pf is 1 "minutes"
       */
      virtual string_type do_get_unit(duration_style style, ratio<60> u, std::size_t pf) const
      {
        return static_get_unit(style,u,pf);
      }
      static string_type static_get_unit(duration_style style, ratio<60> , std::size_t pf)
      {
        static const CharT t[] =
        { 'm', 'i', 'n' };
        static const string_type symbol(t, t + sizeof (t) / sizeof (t[0]));

        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e' };
        static const string_type singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'm', 'i', 'n', 'u', 't', 'e', 's' };
        static const string_type plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        BOOST_ASSERT(false&&"style/pf parameters not valid");
        //throw "exception";
        return string_type();

      }

      /**
       * @param style the duration style.
       * @param period the period associated to the duration hours.
       * @param pf the requested plural form.
       * @return if style is symbol returns "h", otherwise if pf is 0 return "hour", if pf is 1 "hours"
       */
      virtual string_type do_get_unit(duration_style style, ratio<3600> u, std::size_t pf) const
      {
        return static_get_unit(style,u,pf);
      }
      static string_type static_get_unit(duration_style style, ratio<3600> , std::size_t pf)
      {
        static const CharT t[] =
        { 'h' };
        static const string_type symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 'h', 'o', 'u', 'r' };
        static const string_type singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'h', 'o', 'u', 'r', 's' };
        static const string_type plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        BOOST_ASSERT(false&&"style/pf parameters not valid");
        //throw "exception";
        return string_type();

      }
      /**
       * @param style the duration style.
       * @param u the period tag atto.
       * @param pf the requested plural form.
       * @return the concatenation of the prefix associated to @c period + the one associated to seconds.
       */
      virtual string_type do_get_unit(duration_style style, atto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, atto u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      /**
       * @param style the duration style.
       * @param u the period tag femto.
       * @param pf the requested plural form.
       * @return the concatenation of the prefix associated to period @c u + the one associated to seconds.
       */
      virtual string_type do_get_unit(duration_style style, femto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, femto u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      /**
       * @param style the duration style.
       * @param u the period tag femto.
       * @param pf the requested plural form.
       * @return the concatenation of the prefix associated to period @c u + the one associated to seconds.
       */
      virtual string_type do_get_unit(duration_style style, pico u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, pico u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, nano u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, nano u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, micro u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, micro u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, milli u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, milli u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, centi u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, centi u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, deci u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, deci u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, deca u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, deca u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, hecto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, hecto u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, kilo u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, kilo u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, mega u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, mega u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, giga u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, giga u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, tera u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, tera u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, peta u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, peta u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style style, exa u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      static string_type static_get_unit(duration_style style, exa u, std::size_t pf)
      {
        return static_get_ratio_prefix(style, u) + static_get_unit(style, ratio<1> (), pf);
      }

    protected:

      /**
       * @param style the duration style.
       * @param u the period tag atto.
       * @return depending on the value of @c style return the ratio_string symbol or prefix.
       */
      virtual string_type do_get_ratio_prefix(duration_style style, atto u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, atto)
      {
        if (style == duration_style::symbol) return ratio_string<atto, CharT>::symbol();
        return ratio_string<atto, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, femto u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, femto)
      {
        if (style == duration_style::symbol) return ratio_string<femto, CharT>::symbol();
        return ratio_string<femto, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, pico u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, pico)
      {
        if (style == duration_style::symbol) return ratio_string<pico, CharT>::symbol();
        return ratio_string<pico, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, nano u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, nano)
      {
        if (style == duration_style::symbol) return ratio_string<nano, CharT>::symbol();
        return ratio_string<nano, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, micro u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, micro)
      {
        if (style == duration_style::symbol) return ratio_string<micro, CharT>::symbol();
        return ratio_string<micro, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, milli u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, milli)
      {
        if (style == duration_style::symbol) return ratio_string<milli, CharT>::symbol();
        return ratio_string<milli, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, centi u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, centi)
      {
        if (style == duration_style::symbol) return ratio_string<centi, CharT>::symbol();
        return ratio_string<centi, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, deci u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, deci)
      {
        if (style == duration_style::symbol) return ratio_string<deci, CharT>::symbol();
        return ratio_string<deci, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, deca u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, deca)
      {
        if (style == duration_style::symbol) return ratio_string<deca, CharT>::symbol();
        return ratio_string<deca, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, hecto u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, hecto)
      {
        if (style == duration_style::symbol) return ratio_string<hecto, CharT>::symbol();
        return ratio_string<hecto, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, kilo u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, kilo)
      {
        if (style == duration_style::symbol) return ratio_string<kilo, CharT>::symbol();
        return ratio_string<kilo, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, mega u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, mega)
      {
        if (style == duration_style::symbol) return ratio_string<mega, CharT>::symbol();
        return ratio_string<mega, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, giga u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, giga)
      {
        if (style == duration_style::symbol) return ratio_string<giga, CharT>::symbol();
        return ratio_string<giga, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, tera u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, tera)
      {
        if (style == duration_style::symbol) return ratio_string<tera, CharT>::symbol();
        return ratio_string<tera, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, peta u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, peta)
      {
        if (style == duration_style::symbol) return ratio_string<peta, CharT>::symbol();
        return ratio_string<peta, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style style, exa u) const
      {
        return static_get_ratio_prefix(style, u);
      }
      static string_type static_get_ratio_prefix(duration_style style, exa)
      {
        if (style == duration_style::symbol) return ratio_string<exa, CharT>::symbol();
        return ratio_string<exa, CharT>::prefix();
      }

    protected:
      template <typename Period>
      string_type* fill_units(string_type* it, Period) const
      {
        std::size_t pfs = do_get_plural_forms();
        for (std::size_t pf = 0; pf < pfs; ++pf)
        {
          *it++ = do_get_unit(duration_style::prefix, Period(), pf);
        }
        *it++ = do_get_unit(duration_style::symbol, Period(), 0);
        return it;
      }
    public:
      template <typename Period>
      static string_type* static_fill_units(string_type* it, Period)
      {
        std::size_t pfs = static_get_plural_forms();
        for (std::size_t pf = 0; pf < pfs; ++pf)
        {
          *it++ = static_get_unit(duration_style::prefix, Period(), pf);
        }
        *it++ = static_get_unit(duration_style::symbol, Period(), 0);
        return it;
      }
      static string_type* static_init_valid_units(string_type* it)
      {
        it = static_fill_units(it, atto());
        it = static_fill_units(it, femto());
        it = static_fill_units(it, pico());
        it = static_fill_units(it, nano());
        it = static_fill_units(it, micro());
        it = static_fill_units(it, milli());
        it = static_fill_units(it, centi());
        it = static_fill_units(it, deci());
        it = static_fill_units(it, deca());
        it = static_fill_units(it, hecto());
        it = static_fill_units(it, kilo());
        it = static_fill_units(it, mega());
        it = static_fill_units(it, giga());
        it = static_fill_units(it, tera());
        it = static_fill_units(it, peta());
        it = static_fill_units(it, exa());
        it = static_fill_units(it, ratio<1> ());
        it = static_fill_units(it, ratio<60> ());
        it = static_fill_units(it, ratio<3600> ());
        return it;
      }
    };

    namespace detail
    {

      template<typename CharT>
      struct duration_units_default_initializer_t
      {
        duration_units_default_initializer_t()
          {
              if (!duration_units_default_holder<CharT>::initialized_)
              {
                typedef typename duration_units_default_holder<CharT>::string_type string_type;
                duration_units_default_holder<CharT>::n_d_valid_units_ = new string_type[3];
                duration_units_default_holder<CharT>::valid_units_ = new string_type[19 * 3];

                string_type* it = duration_units_default_holder<CharT>::n_d_valid_units_;
                it = duration_units_default<CharT>::static_fill_units(it, ratio<1> ());
                it = duration_units_default<CharT>::static_init_valid_units(duration_units_default_holder<CharT>::valid_units_);

                duration_units_default_holder<CharT>::initialized_ = true;
              }
          }
        ~duration_units_default_initializer_t()
          {
            if (duration_units_default_holder<CharT>::initialized_)
            {
              delete[] duration_units_default_holder<CharT>::n_d_valid_units_;
              duration_units_default_holder<CharT>::n_d_valid_units_ = 0;
              delete[] duration_units_default_holder<CharT>::valid_units_;
              duration_units_default_holder<CharT>::valid_units_ = 0;
              duration_units_default_holder<CharT>::initialized_ = false;
            }
        }
      };
      namespace /**/
      {
        duration_units_default_initializer_t<char> duration_units_default_initializer;
        duration_units_default_initializer_t<wchar_t> wduration_units_default_initializer;
      } // namespace
    }
  } // chrono

} // boost

#endif  // header

/* duration_units.hpp
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
*/