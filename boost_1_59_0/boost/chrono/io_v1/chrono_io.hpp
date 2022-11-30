
//  chrono_io
//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o under lvm/libc++  to Boost

#ifndef BOOST_CHRONO_IO_V1_CHRONO_IO_HPP
#define BOOST_CHRONO_IO_V1_CHRONO_IO_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <boost/chrono/clock_string.hpp>
#include <boost/ratio/ratio_io.hpp>
#include <locale>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/mpl/if.hpp>
#include <boost/integer/common_factor_rt.hpp>
#include <boost/chrono/detail/scan_keyword.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/chrono/detail/no_warning/signed_unsigned_cmp.hpp>

namespace boost
{

namespace chrono
{

template <class CharT>
class duration_punct
    : public std::locale::facet
{
public:
    typedef std::basic_string<CharT> string_type;
    enum {use_long, use_short};

private:
    bool use_short_;
    string_type long_seconds_;
    string_type long_minutes_;
    string_type long_hours_;
    string_type short_seconds_;
    string_type short_minutes_;
    string_type short_hours_;

    template <class Period>
        string_type short_name(Period) const
            {return ::boost::ratio_string<Period, CharT>::short_name() + short_seconds_;}

    string_type short_name(ratio<1>) const    {return short_seconds_;}
    string_type short_name(ratio<60>) const   {return short_minutes_;}
    string_type short_name(ratio<3600>) const {return short_hours_;}

    template <class Period>
        string_type long_name(Period) const
            {return ::boost::ratio_string<Period, CharT>::long_name() + long_seconds_;}

    string_type long_name(ratio<1>) const    {return long_seconds_;}
    string_type long_name(ratio<60>) const   {return long_minutes_;}
    string_type long_name(ratio<3600>) const {return long_hours_;}

    void init_C();
public:
    static std::locale::id id;

    explicit duration_punct(int use = use_long)
        : use_short_(use==use_short) {init_C();}

    duration_punct(int use,
        const string_type& long_seconds, const string_type& long_minutes,
        const string_type& long_hours, const string_type& short_seconds,
        const string_type& short_minutes, const string_type& short_hours);

    duration_punct(int use, const duration_punct& d);

    template <class Period>
        string_type short_name() const
            {return short_name(typename Period::type());}

    template <class Period>
        string_type long_name() const
            {return long_name(typename Period::type());}

    template <class Period>
        string_type plural() const
            {return long_name(typename Period::type());}

    template <class Period>
        string_type singular() const
    {
      return string_type(long_name(typename Period::type()), 0, long_name(typename Period::type()).size()-1);
    }

    template <class Period>
        string_type name() const
    {
      if (use_short_) return short_name<Period>();
      else {
        return long_name<Period>();
      }
    }
    template <class Period, class D>
      string_type name(D v) const
      {
        if (use_short_) return short_name<Period>();
        else
        {
          if (v==-1 || v==1)
            return singular<Period>();
          else
            return plural<Period>();
        }
      }

    bool is_short_name() const {return use_short_;}
    bool is_long_name() const {return !use_short_;}
};

template <class CharT>
std::locale::id
duration_punct<CharT>::id;

template <class CharT>
void
duration_punct<CharT>::init_C()
{
    short_seconds_ = CharT('s');
    short_minutes_ = CharT('m');
    short_hours_ = CharT('h');
    const CharT s[] = {'s', 'e', 'c', 'o', 'n', 'd', 's'};
    const CharT m[] = {'m', 'i', 'n', 'u', 't', 'e', 's'};
    const CharT h[] = {'h', 'o', 'u', 'r', 's'};
    long_seconds_.assign(s, s + sizeof(s)/sizeof(s[0]));
    long_minutes_.assign(m, m + sizeof(m)/sizeof(m[0]));
    long_hours_.assign(h, h + sizeof(h)/sizeof(h[0]));
}

template <class CharT>
duration_punct<CharT>::duration_punct(int use,
        const string_type& long_seconds, const string_type& long_minutes,
        const string_type& long_hours, const string_type& short_seconds,
        const string_type& short_minutes, const string_type& short_hours)
    : use_short_(use==use_short),
      long_seconds_(long_seconds),
      long_minutes_(long_minutes),
      long_hours_(long_hours),
      short_seconds_(short_seconds),
      short_minutes_(short_minutes),
      short_hours_(short_hours)
{}

template <class CharT>
duration_punct<CharT>::duration_punct(int use, const duration_punct& d)
    : use_short_(use==use_short),
      long_seconds_(d.long_seconds_),
      long_minutes_(d.long_minutes_),
      long_hours_(d.long_hours_),
      short_seconds_(d.short_seconds_),
      short_minutes_(d.short_minutes_),
      short_hours_(d.short_hours_)
{}

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
duration_short(std::basic_ostream<CharT, Traits>& os)
{
    typedef duration_punct<CharT> Facet;
    std::locale loc = os.getloc();
    if (std::has_facet<Facet>(loc))
    {
        const Facet& f = std::use_facet<Facet>(loc);
        if (f.is_long_name())
            os.imbue(std::locale(loc, new Facet(Facet::use_short, f)));
    }
    else
        os.imbue(std::locale(loc, new Facet(Facet::use_short)));
    return os;
}

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
duration_long(std::basic_ostream<CharT, Traits>& os)
{
    typedef duration_punct<CharT> Facet;
    std::locale loc = os.getloc();
    if (std::has_facet<Facet>(loc))
    {
        const Facet& f = std::use_facet<Facet>(loc);
        if (f.is_short_name())
            os.imbue(std::locale(loc, new Facet(Facet::use_long, f)));
    }
    return os;
}

template <class CharT, class Traits, class Rep, class Period>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const duration<Rep, Period>& d)
{
    typedef duration_punct<CharT> Facet;
    std::locale loc = os.getloc();
    if (!std::has_facet<Facet>(loc))
        os.imbue(std::locale(loc, new Facet));
    const Facet& f = std::use_facet<Facet>(os.getloc());
    return os << d.count() << ' ' << f.template name<Period>(d.count());
}

namespace chrono_detail {
template <class Rep, bool = is_scalar<Rep>::value>
struct duration_io_intermediate
{
    typedef Rep type;
};

template <class Rep>
struct duration_io_intermediate<Rep, true>
{
    typedef typename mpl::if_c
    <
        is_floating_point<Rep>::value,
            long double,
            typename mpl::if_c
            <
                is_signed<Rep>::value,
                    long long,
                    unsigned long long
            >::type
    >::type type;
};

template <typename intermediate_type>
typename enable_if<is_integral<intermediate_type>, bool>::type
reduce(intermediate_type& r, unsigned long long& den, std::ios_base::iostate& err)
{
  typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;

    // Reduce r * num / den
  common_type_t t = integer::gcd<common_type_t>(common_type_t(r), common_type_t(den));
  r /= t;
  den /= t;
  if (den != 1)
  {
    // Conversion to Period is integral and not exact
    err |= std::ios_base::failbit;
    return false;
  }
  return true;
}
template <typename intermediate_type>
typename disable_if<is_integral<intermediate_type>, bool>::type
reduce(intermediate_type& , unsigned long long& , std::ios_base::iostate& )
{
  return true;
}

}

template <class CharT, class Traits, class Rep, class Period>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, duration<Rep, Period>& d)
{
  //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
    typedef duration_punct<CharT> Facet;
    std::locale loc = is.getloc();
    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
    if (!std::has_facet<Facet>(loc)) {
      //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
        is.imbue(std::locale(loc, new Facet));
    }
    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
    loc = is.getloc();
    const Facet& f = std::use_facet<Facet>(loc);
    typedef typename chrono_detail::duration_io_intermediate<Rep>::type intermediate_type;
    intermediate_type r;
    std::ios_base::iostate err = std::ios_base::goodbit;
    // read value into r
    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
    is >> r;
    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
    if (is.good())
    {
      //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
        // now determine unit
        typedef std::istreambuf_iterator<CharT, Traits> in_iterator;
        in_iterator i(is);
        in_iterator e;
        //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
        if (i != e && *i == ' ')  // mandatory ' ' after value
        {
          //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
            ++i;
            if (i != e)
            {
              //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                // unit is num / den (yet to be determined)
                unsigned long long num = 0;
                unsigned long long den = 0;
                if (*i == '[')
                {
                  //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    // parse [N/D]s or [N/D]seconds format
                    ++i;
                    CharT x;
                    is >> num >> x >> den;
                    if (!is.good() || (x != '/'))
                    {
                      //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                        is.setstate(is.failbit);
                        return is;
                    }
                    i = in_iterator(is);
                    if (*i != ']')
                    {
                      //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                        is.setstate(is.failbit);
                        return is;
                    }
                    ++i;
                    const std::basic_string<CharT> units[] =
                    {
                        f.template singular<ratio<1> >(),
                        f.template plural<ratio<1> >(),
                        f.template short_name<ratio<1> >()
                    };
                    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    const std::basic_string<CharT>* k = chrono_detail::scan_keyword(i, e,
                                  units, units + sizeof(units)/sizeof(units[0]),
                                  //~ std::use_facet<std::ctype<CharT> >(loc),
                                  err);
                    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    is.setstate(err);
                    switch ((k - units) / 3)
                    {
                    case 0:
                      //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                        break;
                    default:
                        is.setstate(err);
                        //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                        return is;
                    }
                }
                else
                {
                  //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    // parse SI name, short or long
                    const std::basic_string<CharT> units[] =
                    {
                        f.template singular<atto>(),
                        f.template plural<atto>(),
                        f.template short_name<atto>(),
                        f.template singular<femto>(),
                        f.template plural<femto>(),
                        f.template short_name<femto>(),
                        f.template singular<pico>(),
                        f.template plural<pico>(),
                        f.template short_name<pico>(),
                        f.template singular<nano>(),
                        f.template plural<nano>(),
                        f.template short_name<nano>(),
                        f.template singular<micro>(),
                        f.template plural<micro>(),
                        f.template short_name<micro>(),
                        f.template singular<milli>(),
                        f.template plural<milli>(),
                        f.template short_name<milli>(),
                        f.template singular<centi>(),
                        f.template plural<centi>(),
                        f.template short_name<centi>(),
                        f.template singular<deci>(),
                        f.template plural<deci>(),
                        f.template short_name<deci>(),
                        f.template singular<deca>(),
                        f.template plural<deca>(),
                        f.template short_name<deca>(),
                        f.template singular<hecto>(),
                        f.template plural<hecto>(),
                        f.template short_name<hecto>(),
                        f.template singular<kilo>(),
                        f.template plural<kilo>(),
                        f.template short_name<kilo>(),
                        f.template singular<mega>(),
                        f.template plural<mega>(),
                        f.template short_name<mega>(),
                        f.template singular<giga>(),
                        f.template plural<giga>(),
                        f.template short_name<giga>(),
                        f.template singular<tera>(),
                        f.template plural<tera>(),
                        f.template short_name<tera>(),
                        f.template singular<peta>(),
                        f.template plural<peta>(),
                        f.template short_name<peta>(),
                        f.template singular<exa>(),
                        f.template plural<exa>(),
                        f.template short_name<exa>(),
                        f.template singular<ratio<1> >(),
                        f.template plural<ratio<1> >(),
                        f.template short_name<ratio<1> >(),
                        f.template singular<ratio<60> >(),
                        f.template plural<ratio<60> >(),
                        f.template short_name<ratio<60> >(),
                        f.template singular<ratio<3600> >(),
                        f.template plural<ratio<3600> >(),
                        f.template short_name<ratio<3600> >()
                    };
                    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    const std::basic_string<CharT>* k = chrono_detail::scan_keyword(i, e,
                                  units, units + sizeof(units)/sizeof(units[0]),
                                  //~ std::use_facet<std::ctype<CharT> >(loc),
                                  err);
                    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    switch ((k - units) / 3)
                    {
                    case 0:
                        num = 1ULL;
                        den = 1000000000000000000ULL;
                        break;
                    case 1:
                        num = 1ULL;
                        den = 1000000000000000ULL;
                        break;
                    case 2:
                        num = 1ULL;
                        den = 1000000000000ULL;
                        break;
                    case 3:
                        num = 1ULL;
                        den = 1000000000ULL;
                        break;
                    case 4:
                        num = 1ULL;
                        den = 1000000ULL;
                        break;
                    case 5:
                        num = 1ULL;
                        den = 1000ULL;
                        break;
                    case 6:
                        num = 1ULL;
                        den = 100ULL;
                        break;
                    case 7:
                        num = 1ULL;
                        den = 10ULL;
                        break;
                    case 8:
                        num = 10ULL;
                        den = 1ULL;
                        break;
                    case 9:
                        num = 100ULL;
                        den = 1ULL;
                        break;
                    case 10:
                        num = 1000ULL;
                        den = 1ULL;
                        break;
                    case 11:
                        num = 1000000ULL;
                        den = 1ULL;
                        break;
                    case 12:
                        num = 1000000000ULL;
                        den = 1ULL;
                        break;
                    case 13:
                        num = 1000000000000ULL;
                        den = 1ULL;
                        break;
                    case 14:
                        num = 1000000000000000ULL;
                        den = 1ULL;
                        break;
                    case 15:
                        num = 1000000000000000000ULL;
                        den = 1ULL;
                        break;
                    case 16:
                        num = 1;
                        den = 1;
                        break;
                    case 17:
                        num = 60;
                        den = 1;
                        break;
                    case 18:
                        num = 3600;
                        den = 1;
                        break;
                    default:
                      //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                        is.setstate(err|is.failbit);
                        return is;
                    }
                }
                //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                // unit is num/den
                // r should be multiplied by (num/den) / Period
                // Reduce (num/den) / Period to lowest terms
                unsigned long long gcd_n1_n2 = integer::gcd<unsigned long long>(num, Period::num);
                unsigned long long gcd_d1_d2 = integer::gcd<unsigned long long>(den, Period::den);
                num /= gcd_n1_n2;
                den /= gcd_d1_d2;
                unsigned long long n2 = Period::num / gcd_n1_n2;
                unsigned long long d2 = Period::den / gcd_d1_d2;
                if (num > (std::numeric_limits<unsigned long long>::max)() / d2 ||
                    den > (std::numeric_limits<unsigned long long>::max)() / n2)
                {
                  //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    // (num/den) / Period overflows
                    is.setstate(err|is.failbit);
                    return is;
                }
                num *= d2;
                den *= n2;

                typedef typename common_type<intermediate_type, unsigned long long>::type common_type_t;

                //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                // num / den is now factor to multiply by r
                if (!chrono_detail::reduce(r, den, err))
                {
                  //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                  is.setstate(err|is.failbit);
                  return is;
                }

                //if (r > ((duration_values<common_type_t>::max)() / num))
                //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                if (chrono::detail::gt(r,((duration_values<common_type_t>::max)() / num)))
                {
                    // Conversion to Period overflowed
                  //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    is.setstate(err|is.failbit);
                    return is;
                }
                //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                common_type_t t = r * num;
                t /= den;
                //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;

                if (t > duration_values<common_type_t>::zero())
                {
                  //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                  if ( (duration_values<Rep>::max)() < Rep(t))
                  {
                    //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                    // Conversion to Period overflowed
                    is.setstate(err|is.failbit);
                    return is;
                  }
                }
                //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                // Success!  Store it.
                d = duration<Rep, Period>(Rep(t));
                is.setstate(err);
                //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                return is;
            }
            else {
              //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
                is.setstate(is.failbit | is.eofbit);
                return is;
            }
        }
        else
        {
          //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
            if (i == e)
              is.setstate(is.failbit|is.eofbit);
            else
              is.setstate(is.failbit);
            //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
            return is;
        }
    }
    else {
      //std::cerr << __FILE__ << "[" << __LINE__ << "]"<< std::endl;
        //is.setstate(is.failbit);
      return is;
    }
}


template <class CharT, class Traits, class Clock, class Duration>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os,
           const time_point<Clock, Duration>& tp)
{
    return os << tp.time_since_epoch() << clock_string<Clock, CharT>::since();
}

template <class CharT, class Traits, class Clock, class Duration>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           time_point<Clock, Duration>& tp)
{
    Duration d;
    is >> d;
    if (is.good())
    {
        const std::basic_string<CharT> units=clock_string<Clock, CharT>::since();
        std::ios_base::iostate err = std::ios_base::goodbit;
        typedef std::istreambuf_iterator<CharT, Traits> in_iterator;
        in_iterator i(is);
        in_iterator e;
        std::ptrdiff_t k = chrono_detail::scan_keyword(i, e,
                      &units, &units + 1,
                      //~ std::use_facet<std::ctype<CharT> >(is.getloc()),
                      err) - &units;
        is.setstate(err);
        if (k == 1)
        {
          is.setstate(err | is.failbit);
            // failed to read epoch string
            return is;
        }
        tp = time_point<Clock, Duration>(d);
    }
    else
        is.setstate(is.failbit);
    return is;
}
}  // chrono

}

#endif  // BOOST_CHRONO_CHRONO_IO_HPP

/* chrono_io.hpp
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
*/