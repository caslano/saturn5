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