#ifndef DATE_TIME_DATE_NAMES_PUT_HPP___
#define DATE_TIME_DATE_NAMES_PUT_HPP___

/* Copyright (c) 2002-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/date_time/locale_config.hpp> // set BOOST_DATE_TIME_NO_LOCALE

#ifndef BOOST_DATE_TIME_NO_LOCALE

#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/parse_format_base.hpp>
#include <boost/lexical_cast.hpp>
#include <locale>


namespace boost {
namespace date_time {

    //! Output facet base class for gregorian dates.
    /*! This class is a base class for date facets used to localize the
     *  names of months and the names of days in the week.
     *
     * Requirements of Config
     *  - define an enumeration month_enum that enumerates the months.
     *    The enumeration should be '1' based eg: Jan==1
     *  - define as_short_string and as_long_string
     *
     * (see langer & kreft p334).
     *
     */
    template<class Config,
             class charT = char,
             class OutputIterator = std::ostreambuf_iterator<charT> >
    class BOOST_SYMBOL_VISIBLE date_names_put : public std::locale::facet
    {
    public:
      date_names_put() {}
      typedef OutputIterator iter_type;
      typedef typename Config::month_type month_type;
      typedef typename Config::month_enum month_enum;
      typedef typename Config::weekday_enum weekday_enum;
      typedef typename Config::special_value_enum special_value_enum;
      //typedef typename Config::format_type format_type;
      typedef std::basic_string<charT> string_type;
      typedef charT char_type;
      static const char_type default_special_value_names[3][17];
      static const char_type separator[2];

      static std::locale::id id;

#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
      std::locale::id& __get_id (void) const { return id; }
#endif

      void put_special_value(iter_type& oitr, special_value_enum sv) const
      {
        do_put_special_value(oitr, sv);
      }
      void put_month_short(iter_type& oitr, month_enum moy) const
      {
        do_put_month_short(oitr, moy);
      }
      void put_month_long(iter_type& oitr, month_enum moy) const
      {
        do_put_month_long(oitr, moy);
      }
      void put_weekday_short(iter_type& oitr, weekday_enum wd) const
      {
        do_put_weekday_short(oitr, wd);
      }
      void put_weekday_long(iter_type& oitr, weekday_enum wd) const
      {
        do_put_weekday_long(oitr, wd);
      }
      bool has_date_sep_chars() const
      {
        return do_has_date_sep_chars();
      }
      void year_sep_char(iter_type& oitr) const
      {
        do_year_sep_char(oitr);
      }
      //! char between year-month
      void month_sep_char(iter_type& oitr) const
      {
        do_month_sep_char(oitr);
      }
      //! Char to separate month-day
      void day_sep_char(iter_type& oitr) const
      {
        do_day_sep_char(oitr);
      }
      //! Determines the order to put the date elements
      ymd_order_spec date_order() const
      {
        return do_date_order();
      }
      //! Determines if month is displayed as integer, short or long string
      month_format_spec month_format() const
      {
        return do_month_format();
      }

    protected:
      //! Default facet implementation uses month_type defaults
      virtual void do_put_month_short(iter_type& oitr, month_enum moy) const
      {
        month_type gm(moy);
        charT c = '\0';
        put_string(oitr, gm.as_short_string(c));
      }
      //! Default facet implementation uses month_type defaults
      virtual void do_put_month_long(iter_type& oitr,
                                     month_enum moy) const
      {
        month_type gm(moy);
        charT c = '\0';
        put_string(oitr, gm.as_long_string(c));
      }
      //! Default facet implementation for special value types
      virtual void do_put_special_value(iter_type& oitr, special_value_enum sv) const
      {
        if(sv <= 2) { // only output not_a_date_time, neg_infin, or pos_infin
          string_type s(default_special_value_names[sv]);
          put_string(oitr, s);
        }
      }
      virtual void do_put_weekday_short(iter_type&, weekday_enum) const
      {
      }
      virtual void do_put_weekday_long(iter_type&, weekday_enum) const
      {
      }
      virtual bool do_has_date_sep_chars() const
      {
        return true;
      }
      virtual void do_year_sep_char(iter_type& oitr) const
      {
        string_type s(separator);
        put_string(oitr, s);
      }
      //! char between year-month
      virtual void do_month_sep_char(iter_type& oitr) const
      {
        string_type s(separator);
        put_string(oitr, s);
      }
      //! Char to separate month-day
      virtual void do_day_sep_char(iter_type& oitr) const
      {
        string_type s(separator); //put in '-'
        put_string(oitr, s);
      }
      //! Default for date order
      virtual ymd_order_spec do_date_order() const
      {
        return ymd_order_iso;
      }
      //! Default month format
      virtual month_format_spec do_month_format() const
      {
        return month_as_short_string;
      }
      void put_string(iter_type& oi, const charT* const s) const
      {
        string_type s1(boost::lexical_cast<string_type>(s));
        typename string_type::iterator si,end;
        for (si=s1.begin(), end=s1.end(); si!=end; si++, oi++) {
          *oi = *si;
        }
      }
      void put_string(iter_type& oi, const string_type& s1) const
      {
        typename string_type::const_iterator si,end;
        for (si=s1.begin(), end=s1.end(); si!=end; si++, oi++) {
          *oi = *si;
        }
      }
    };

    template<class Config, class charT, class OutputIterator>
    const typename date_names_put<Config, charT, OutputIterator>::char_type
    date_names_put<Config, charT, OutputIterator>::default_special_value_names[3][17] = {
      {'n','o','t','-','a','-','d','a','t','e','-','t','i','m','e'},
      {'-','i','n','f','i','n','i','t','y'},
      {'+','i','n','f','i','n','i','t','y'} };

    template<class Config, class charT, class OutputIterator>
    const typename date_names_put<Config, charT, OutputIterator>::char_type
    date_names_put<Config, charT, OutputIterator>::separator[2] =
      {'-', '\0'} ;


    //! Generate storage location for a std::locale::id
    template<class Config, class charT, class OutputIterator>
    std::locale::id date_names_put<Config, charT, OutputIterator>::id;

    //! A date name output facet that takes an array of char* to define strings
    template<class Config,
             class charT = char,
             class OutputIterator = std::ostreambuf_iterator<charT> >
    class BOOST_SYMBOL_VISIBLE all_date_names_put : public date_names_put<Config, charT, OutputIterator>
    {
    public:
      all_date_names_put(const charT* const month_short_names[],
                         const charT* const month_long_names[],
                         const charT* const special_value_names[],
                         const charT* const weekday_short_names[],
                         const charT* const weekday_long_names[],
                         charT separator_char = '-',
                         ymd_order_spec order_spec = ymd_order_iso,
                         month_format_spec month_format = month_as_short_string) :
        month_short_names_(month_short_names),
        month_long_names_(month_long_names),
        special_value_names_(special_value_names),
        weekday_short_names_(weekday_short_names),
        weekday_long_names_(weekday_long_names),
        order_spec_(order_spec),
        month_format_spec_(month_format)
      {
        separator_char_[0] = separator_char;
        separator_char_[1] = '\0';

      }
      typedef OutputIterator iter_type;
      typedef typename Config::month_enum month_enum;
      typedef typename Config::weekday_enum weekday_enum;
      typedef typename Config::special_value_enum special_value_enum;

      const charT* const* get_short_month_names() const
      {
        return month_short_names_;
      }
      const charT* const* get_long_month_names() const
      {
        return month_long_names_;
      }
      const charT* const* get_special_value_names() const
      {
        return special_value_names_;
      }
      const charT* const* get_short_weekday_names()const
      {
        return weekday_short_names_;
      }
      const charT* const* get_long_weekday_names()const
      {
        return weekday_long_names_;
      }

    protected:
      //! Generic facet that takes array of chars
      virtual void do_put_month_short(iter_type& oitr, month_enum moy) const
      {
        this->put_string(oitr, month_short_names_[moy-1]);
      }
      //! Long month names
      virtual void do_put_month_long(iter_type& oitr, month_enum moy) const
      {
        this->put_string(oitr, month_long_names_[moy-1]);
      }
      //! Special values names
      virtual void do_put_special_value(iter_type& oitr, special_value_enum sv) const
      {
        this->put_string(oitr, special_value_names_[sv]);
      }
      virtual void do_put_weekday_short(iter_type& oitr, weekday_enum wd) const
      {
        this->put_string(oitr, weekday_short_names_[wd]);
      }
      virtual void do_put_weekday_long(iter_type& oitr, weekday_enum wd) const
      {
        this->put_string(oitr, weekday_long_names_[wd]);
      }
      //! char between year-month
      virtual void do_month_sep_char(iter_type& oitr) const
      {
        this->put_string(oitr, separator_char_);
      }
      //! Char to separate month-day
      virtual void do_day_sep_char(iter_type& oitr) const
      {
        this->put_string(oitr, separator_char_);
      }
      //! Set the date ordering
      virtual ymd_order_spec do_date_order() const
      {
        return order_spec_;
      }
      //! Set the date ordering
      virtual month_format_spec do_month_format() const
      {
        return month_format_spec_;
      }

    private:
      const charT* const* month_short_names_;
      const charT* const* month_long_names_;
      const charT* const* special_value_names_;
      const charT* const* weekday_short_names_;
      const charT* const* weekday_long_names_;
      charT separator_char_[2];
      ymd_order_spec order_spec_;
      month_format_spec month_format_spec_;
    };

} } //namespace boost::date_time

#endif //BOOST_NO_STD_LOCALE

#endif

/* date_names_put.hpp
rxy7+XczyLgAUGsW2jluTm8NYtbI8OlQVUId9caIID1MzEiulxosBsd7Lkpulf5fSHCJ00uSk807p2uY0HDpINtPdvcTt8Xrk8jjhy/7h/c2Lgadva0b/zcwepQvytSQSY199mhNySfdipFHzD5gmii/dA0T/aTsd3Sy6T0B7LCnAhdbVjDItrwCJD90GKYDhV0Mhj0FkdgbtbAtVTLbqqPYZKWEbwWLSdK44DhY6DbIdGPLY7s9LbH38bFFr6xpyVCFO3JQjC3E2cUgU0BEwAO0yw4F5cb9PZ364qJa2RsNScepZQvm/OIL207PIrmKTIr7PXLl1hJ9099TWSsGAJeJKMl6aWRsZGE2wl0Rhrdp/RqebT8WyKvti1DSukT5hzchDiUF86OqcZdCYfhOx1P9udJHssU5gkP1JJa2Q/RPQakytgbhBrOwsMU5gAuySWpKhUYB/2BTe2xUnLDoZg/WZti0XkAiebaQmReAbveVkPUO1Et7NYY7KD1oz1SWwWB7Ub8eVHuUC+Q1y37EPd3wnljZym7A4+WhAPqulhNKT1MYzyJFbwAkYEOQqlhl+dIgaa361Ty+dpfrNs/fP6AFv3ry+RfUYt2Vz5goux27aYmd6SMkXD5AIeFgt/6tXL3Md90BUxFWCAT5TzIKmHZB5FJUPaqlyd29ELAh0rlVLhylbFHVo77L/TxkBxy27G6vdRbL8eD4x49ce2Py2WCuGys8aCj7/EGHWVch7DX4O6shcjGhj3BDNEhxPv5INQTyAB00IsFoBVmLGet2oOAv+qgjeqUfNzxZy8tiUlY7G+se3q94bFwzUdsO5tkKRQ5iBYbkIZR5ZT7YI0mxUAGNl35BlVwdoRroTvhmcrELnolw5pgPdNT8r9Oa0y8JIM+7zDfg45P7RcGXUMdIg0Vxm9D/c/Uff2OW+1beXza7V0gBdeS7RxeapZgqTrWPDaay8Yi5aQIQSV71L5wuzmTkkaxxovHwJaeZJKD4gpgK+P0GD7nLgYU2gWSoNY/gN/U+XCnSZxSfKTYSwQjIH+6TUTterMPcBt7gzH5/3AkmZSgsqEgdjj/djtoD3LwOEhMBfwFmVK3/7Z+j5DmM15T1W7lM0bsIWYAL7E/npYeZVlkXgZKAroTr5cLtrTNCufX7CWxL2a9WTEjnc/Gjoc/avZhVbNt/mQOluaaYLGGMbpvvhftbnliPNrrinEYkLZXhexgAgj1IX4WOMtEkRq40DX/b2yoL1QUhQA8n/pB2lRJNf/QSaGNWsasz64FoDeDOBd4F+JNqRkioZNtqfNGCor2G7ZAxsOgDzUWJWdrEdaTIQ5ODGK3w3Iah4FMRwLAdJraIz7oRapS2KHcEXciNOuvGHJBgfdB8Ri8rAj9hpSvuXgHlGzwH7aEgOBqTR3RQVFBAn+gEqXI/AAss9NN0RDZf6rPSPCD9kJb2JMnIf74VXIpTwMEEjm5iOL35P/g3bF7Z2aXDBLQOzZ+vAZ2O/B16YfcgdnjBylmCyHJh9mQGaCTdlBtp4NPLUHtuCeqgEvrrse8IyKk0MGpQgNMVtjaH3he4xYq7YJ10KGPlBzED+JGV3nNbhkjLvs0E/xmrwy4QTSAQPEPHI2+H99+cX3s3W9YTQFYuyxqEwYqJdzuHn30BTlOxIA/FqVNDIuAisvgdQcZ/7toawWeV2mir2iO/ai/bY3wPnxE9wulBBhEe1XC1UvU5E2BFfkJCHg8fDnk9d400HJu5vlGYcbUxkTT6hg/vDaoSFcJQJVa5FciNrrHZMUdBeoBpYliYZzUULl8Zw85/V5KzsZgcnRCY5Wnq42JqDlkRua0K4pDwx5Ej6XD7Z3GCYf7yrmnFKzOKJZ7Sm5gCLvdlW4S3+WR/Hu/tc+jeEV5U9/sf/PzT0qyOXV54zoxMTMMSCuVGSauBCpIkYxqUm+JbqXXxm/H1r/KvjzwdK9N7jR+IHXXSrGH3KrwjJh4wcdRj6qEwMfccTK5/n6S2lbyjW2JQ3KEwSVco64wU65k/zwrTM0Bk9c00ee/vJtzOBUmbuLeWSqWx9yPHq9fK/jFIOMbpJPd7e6FrarlD76c8+UaRnOOxfX2iFKQ5V9yh/GU3358LvXqv16gJsRZfUoVM1KYMGUDu3KcaCgNdPRLZzQvkuhI/2lNBN7QH2h2Oqq9+TKwvX583onQucrCxu/Uk7Q2eGScen8LurvIErTC6rZZ6fCEJjowPVm/R7izrz1YHjhg5jUJN1MaehFF4T+DjyUvG0jKqEStG2rZDKJtWhNYziv9yrsy1kOWCYxLqIqfMfUHmxkqUv5nRyZg9nBxVGiqmbG/yPgL9UEZFnnHel88bLe2rnFDrE/sz0ZgumtKgN0PZKtDbChy3U+/lbP9k1v1vnhACyWx6VCIkxHVulBufTkQq47+42ojJqLeZU0UPq0HvcILLusdwGWaTZPvL0eNoOMPZ04nWGuCqvjzOJqYAJOvQGRwCo/mC5Zj70gpugh5Mt3Nf6yBI2pJ60G6L1zDHgj6yFR7s/BMCY+u8+Z/YreOrJQPDoVqpmEvuh/Xg6sMvGN4rbzOLc0G0V8+BxuGJ5BihD/Wvfr7qsi+LV3anX3NTRzVXiXBLjoZgzTIzj+aOt/Yw38Szr0Kr5rSVubd6/R17xckGOqivcAeOj2Cv9gCO+PlS684jlf546+4h+jMsj14CFInw5RXhAVpjODWj6gjWte/qBsZLB4oYw1XhOTEdcjm0bMg1ctA8oOB9vLIDm2++/LJukkBPy9HttnhFC7HMVUFuhqwaMoW98nZjf/SqDKxRpSYN7FcRd/Dt+W4gS0CsGyPxoWHLWVmuU3XA8/HgcpClIHE8eK11DCRoMxaeDkNthBny9HXaZt1Hh8Um24j+x34lHs79GJMZJ8XD7jkz7TZV7mAAYpmE6vnjXgaTmdF6aj2VVhe2rlD8W5JaDbofkJAhaBf8pkOnn8+DHviVmoYk582UjfW3eT2YDNblek6/qhK6ZDfnHUYsZtwRPnPUmCqBUB3o0Tqpb9h7r+icgDhvbtbs3sDiAJ/9AOgxI2vasMe2H7h+C62I/cI/oHNLgMTha+HkP25++hOnIDjbJRq/5+bBiLtScx2SeaAtI1E1H4p9mZ9StaFR4buTFJ2s3f5DJZOK/Vh7G8y0RnG/AZKORnWUxIy9DB4oI2WizzLsTC6cPVMv08EgmROEmtovSQhqALRAiICrvk6ENq21pcUU5aA/GaQlK/zXSoJDE61VkTPFEUN4xBmColXW7lp5X0oK0iTVc6KXtkO3vi2AyulxPf2g+hqJxwJM+B9bJWYULKVBCpw6TvbetK55Ye96pHCOw0ukBYAksVNNLFxJeCjyLwW3E54KX9k0CG8DVpv1GQXzCmKGig/65gE5dIIW/+JCo9+lM8Fl9lpgPFKGGmsG9BvT1eJxxZtQCfrwR5c57/raJwG6lWieEJIHRlaDkN3G0N6dRMqV3lVL6j617v6vMMn8ldshrGtVeJ/nOfEIUUHubr+ZM0gPytgYcNxsDoazoT5ikCzkYHoz7QjQKORkyKxODj0l2DA18GS11LGfTaRMyo/z9Uv4aVOTLv/JhQrX6vwdLaGYlJ7XZsmPOizpohXmpjpV1/+W00xMvUuxjMXH2um6K5NNZ8KJ/2rD/LQoHXHcVwrNnaK10No9URpK7WrJApfpt0Srop/0TlawIdnbMCDS1757ebAa/ICQxzlwIURZKIj0co6XLK8apWN2sJM0VrW0/dBW/hsRav5/7jFe5A92cEy0VybiLAdM2o/vsaKUSVEUMo21Bw796d+x7BZ88fMtCFY9yV25/z9GCI/rGplaNTP4lGT1fiRITvhLMld9DIeqioJ+zJKmjSPvalgG7e+at4RgFz7lBTPRPs+6he/VWIsT0KDWjCjHtsk0h5ou/XjBIvBOoI+7Cg6C4jO+UootgBPZ6lEIQYFuh720vIeuZMTjrcnfxtADTO8O/wv2nE72rZ+5tT30ZwMePUn7pRsMFtfEJPaFr92R5JnJ/ZwhIPAOlpcvba9Z701FqPU/FoM9qteldMUjDHobNIoUrK7M69D1joaM+gb5TPLEZBIhOIYP2A95LPCX0oUrsn5HZGWpG84/hY0jXcQvD5WWZr3YmXGy3jZ6IB0TmMG9uTdV35PVp2mI1U13I58QbCLfQ6iIgv6Sn7xyNnybdbINc2QaW70JW4m8d6zzJYc27cwHWLMs8UaR93Kqcydha9QowNKh0IpckQyPaiODA8R63LtsCt6UFb6X08Ug+aM3vYPSJPF4muKDe1wVfylfoJ1mxJRYp5IsecPLFMVMsPEYrCsuJh/P37QAk+iKO99KNTUfq4IT50KCM7A3vHVDIxB21lXf+JXYZRRiIWGV89nEF/X6LzyI/y0y68kwZqlw7bRSHA/CW655St/429M0CE7no0/p3AlvAGjrVWfu2+y0fbi2MQy7MMdOS5aBClGvwKWPKNLu/XlwTaXsrjRzdU/OhpDkW3eq4tZAbiC/w7imfFdk+hXC7WtqvTusuMxtQcx/DUQcqcnw4+m8LecJ3z3AyFNz3EvSaoM3O5GAy5kK57hP0Ms5D2fuBmzGkJpnZfkz2FY+j8Ic269tgbIgP4BmBjIbzRw6jdqP8dXG/Y3nHepYEfzjBP/aCLcw7vkqFCjgniJTmWiewazd1+4gHlU0dSZXKX1uRbdBKx5aCD6gWperDgL5H08JR768kTsVCz/EUuoHeBgi1HJsZK6PgrwRYdpX+MQVfJ5VtkBS+4Db1CdKy/weV97mb2EbbpRR/8Oein1ORgYywPV/PkjX7upzqDJ/zzNUQ/zF8SwkbysRXaY3Q3FtonDrRHsxQ3JditoC0WqcaFZQGJu2XqrmxzsnWvgBv+U04X2HSIjjymuI6DHKbAo0ga75tbE0mNOebKv7WNpgKGIkqaKdCo93lP9xEIOTzK7+8R5M/rko7TNMvQT6AVsVve/xovwxiP5sW9d+ynnGF617DHGTJlIeUrriSbyh9LEn7RRU+tWX6ppOb0DCRFbbQPaVl1Gh7X6kehqTRaSVKyi5Ev9FTW5yz0yPGw9jN1s/BtftO0yYWmqxHtjS38OFTo09YjuPu/Ji27KjFMs4KNhBUO0SLM/rV0+ySY5rqH9kf2wSrpqlo1HCokRyUm5rF3NulKK257AMWa54wtGkEG+o7jNOSiv4jF3mlbNHZXs1sEZ1p3jwABt+PW0MgZ7lqGG6sdN/ZdWRB0fuH9T34/rKSHHiujE5v1trNsginNGMWBrlCNqZVqQZE9Ym9H8He7SUQ5HDvPO2bOIgjgpS2H1bRBSwMN5YXbj7GWW6rwkN5abVxWopvJDDs7l6/7o7pyJusynjQyyUQo3muRTMsx/qfzF4m9UxBIz3NNnm19lyR1giyYK4ddBIXX2BlSpb3cxzJ4IYcOq5eS8c9xUEMKefI6eN0yjPuLYhz8VjpSTCkJr9WM8NaV7GXl71GB75XP2As8IWjZaH6KQS4Cx3/3sod5ClI8kac1B+hL1Qfjoby3ZTmPEQ8wIDg4Qw1R2arY7WHe9bV4xIqxqq5s4m3a0sGJmRKGoLA+qAldfKbc0oHpcB2pkeG4/5/iLETWDt9DvoqWrIeJZsjZp2R+p7rEFw+ALbpjuSE1hawJNeG4RYSupzQuBcjJPXtlOQV+qzH5y3UpmX24Ft/c3EA+tumG6o8Xc3vzYO50cVQyusxoRN1JLljX029fC+DW0bUaMUk9/acsn62IsUJ8zMp3ASDTuH3fXGIHZI+FHAC5BmVd+lfNqu5BQEJLVwAxBwVFO8kIFmXUkqjhVo3FJRi8UnzY5WgOhrSu/BiHS4PblKXCmJuV/JtoiU4cbNi06PDnzyK3lGxjETt8q6PpP/pADQDLoPDoqGZQe0Mtj3HQ1VSbnLESBXDjqGACNFE88vGTdxiARYcqWe7XVVY1oqrC+xwsJB/eLa0T31Yn1Cro/HaiJ/oxqyzDTrgj2YFKiq0POe+8RDETIYHTGgL3fbk3VHzvA5slW800qmrPBa+80m/2n4dNxQlZy3EN5GQ71cBslknMI2UpHg/TWNhC9pZ+gUkYjal7VtwIQTlheXP+t3GNZ8R6KDofmGn1SeH3av1ltKFBWOLENTjW0969lpHX3kKmFiVv50dkLdN4DMBFmk7sM0AsEnTab/A03OwsE/qPb8tK507SA7hYNIGnZmx0JAf6jNHVyrMQeirnBeV3UJiYxAmkiw6nz0gj8JhC63/DX6yTLJLxLEl835hIeGf7w2qbjPQSf4t+lydEdijGgCNJedbtQUUv7JzD8PV2/RHAdHsmsQb2tg5V4GoqHSU97gazbrzI1nH/UzDJEutv6z8QtmGG6A3njs+AbqX8TqfWG5bWMqUo+AZrQFNDlW78KkPjcqgO8l54Dnq6GEk06jWylfowyv+8bkcT4YxGFxHuQjIAgBJoCOCouDmLU+2AuDC5iA+bfBnlQdae1yDU+q/JG4xL/cnr8ebX8PJTx7qjStOYh0Dj/iwjO0qLIGJGCdNISWFmsg5z1BdRFf31Vk5mGXzNGJw5ePpFrNeY76XJWTfOlq2XiLiZggECi6wgSN4pVHjZGVn99jCgGikyve/Hvy8kkX54ebi0OATXN09MO+6ZmqLsVj5dw2rCBsJftBPZhDgaFilyrqbn93BYRpbxKwYn0Kq4eVmoYnTIHfK5oId5Do5OoTOjPtAphwx6DENvQlpE+j833yybnOLZE3Tx3fwIau9lfFCI21boEW8XBuHJjP0QWEniipXRRhBWwlqjWxwFkzi5XBCaCEEoJXpjb92Wn3TZ+76sQANAl0Bx22G+ay1s8CFMHQEmeguIX1fzdL4tO+sHNFI7+vDWN+e9aeeECNtI2J+7/Y9Nadi5g+FEg9Pv8q2ltb7pf4TAHweVZMI9PJdbOH+G8dCZSbH/sL51a5hd4LlNLFnUg+SD0HQDWLc2FzxOvWBBJ1CmBYe/OAReJNUL/GMRIRn4HNemiB73yDrWLQDScRKweUfvpEl0dSOS5sQfxqLqE/qndwEgn6uleMx0PnMnTA9BP0mtH9UK0rZH4gG4rgN5f8j3+hPpo3LyeRqvjwJPeEeBD5vszIgAoFDVgDIXMl/hSE4gf2l4A3WVDrgRb76EV2hu9tvxoz5y9W//O6mgGF9YuAQkoIAM6Bmjq7AjlSeHo8shUvn7TiLvhcnV2bMSOL3Dho4fYAhgm5SRLvmjVjECd8QTHNSK6zXlTIJUnyh7l63gYJs575jlHLZ387hKlaSyJ4FC6OWhrvae21cP9WpXuuDlvvM6isELaT8HEhShfZL7nyqKckvomVbO42ZxrOwjgVB+wsYJeTZNBKnG5a85QQFvAmVGnfu77uG27koYva3iSecFkEUaHANYStMiK04gPFunSoak7iLQn/t7zkLgeUCo+rNJaVRI2XO/OzNZXu+My/1z7fnK+y/AjkNfwxXU5aBK4onsXenR4xbp56nJg8ZFdbXK4wIA6HKarcqyL2UhcDZ1RjSxPFqy5OI0YKeuGaZB8WrgvIf0hdXqQD91lXiCWGfYZ56O7hoBw8COQvzZyrY36tF9IjB7HA5qdHlPYQHleVytJSakvp5u/RsP4/wKkQ+mGSHWqcy/kv1tTDhnBNlC0vEHUyfGosWdV5e+tphhk7PWJCJ4rxmBnOhfW7Yi6lT/PVohMcKW+zRaYbbsx0V4aR2/LL85TcyvlA91CXNCpHBprNml9MdcD00LcwXKDlgWDKiAvKBQbUB70M76kkeb6sB6cIE2fPsf6/QN5xQ+nzRFF+NFA1jq/1OgqLbKTMdtVnvYdDT94isyiGXzPPxyiS9pr0XZ8XA264pQlD3FJOMIDdW/CmBri/XHkL4TWNtYHEr/fNxfSGp2ewazBPRr49qcbpB7ROwwfwB+7DKbc06VZdCZC0IncVym7p/tEpvXdY+e5aFHqj9li/QvAIMSDE/PRkABacgtg1oSydbaCkmWIUK48ZjHCymrAhUt8QneUul2eEfniAzoVAkcfPnY4FdeRLNV8BTy4GV8YZjk5jUSqf3aVeEKVPClGpNcIH9NZTCyAfqY6+OOhrjXijxWsnWZUNi5KRcYmCZtfEOvrA1kfahgvjpjbdivsZfSy0sNLOz5BF8YBfVDOUo+k5ULsdL0Pn2hfFW657snxBKOIjUKU2lf8BVyWAseiSPxYIlQ0Z9hHroTx6VPOku8RPInAYIUH62GKrXxSYcsAcz75uxXuJ7f3Cxd1dTfvFbcX0dqXA0PzJs2DOn9RlXVim6T1EFJIHBcHBrq7nrNXHGW06i3QDgscUV6a9GSdmKIn3Fd571HxPMaYKoVW8whP6KwjSf92sHEjsMewCWlSLaKdeeD4nx8jPSxyjnC5/VvrWQxK9x+gg0z+yfOYtCxnhz1o6xu1M0WfnXlVObkSjDUCODmX8RUzjcmk/GD3DazAOwz8JgMt9MvupyZlxC2cnI3es6U7SDhrfvwT+/3IBQegUkyCV5XXdJBmF1WAoPNo5+CYMi75IFqF7Zr42H6ehQgxuKcYiFSN3OiWND7RKoRICLfBqvaWBDbjqSVnRJ/Mk3rpnK6O+Iaiw4pRqJw2mQ2yiLJ+kn2dl8dqzZghU+jJ9fgDLmgh6Vs3KqR185chOnphuDAo41yBEY7gw+8hVLBxojpca9jOoW09iCOnIFslnm1H7BL9vP7YbwnQb0IeSXIjBocHC8P0e6ofEwS8cgBvtwXZJXRCa/5jlOlSz3ZuYEPGJHfh8OPMfLMeG9zw7ID57APvPPTMiAf/2Xyij8za697fWZTlv3S5Nwk6+Xvo15tJ71n8D9TcYZAE5jenV+AnkOYVLs7q3bEvjs+l6SKBW3BV/ZIifoTur+aVN8XxlEZq7w9pwYoMgiwEWSwRfAtWuC/hzR/kS99NMQmAAgqmbvm38+tU6C1QmVy0zOYXpC0fqJNz187VNo1mS8rAHRSGsEl10yj7AZGyaoK/LJGcnAtV9v4cjZFD9gbsCaN+ein8Qhloj7w/n44zZ8npItj9CKBOA5Sqj7av/BuEcYfnbMIV4+rp3k6bknJ6MMP6S8GhvXpjz1LQp6bC9LFC80oGXhaZKauMKdj9bfDv5CC72SZdePVbzhzYRhmA8jbKPRhzy5NztWTnwLdy3ifEagoY=
*/