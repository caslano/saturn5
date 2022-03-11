
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