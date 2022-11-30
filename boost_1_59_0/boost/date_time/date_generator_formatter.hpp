#ifndef _DATE_TIME_DATE_GENERATOR_FORMATTER__HPP___
#define _DATE_TIME_DATE_GENERATOR_FORMATTER__HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "boost/date_time/date_generators.hpp"

namespace boost {
namespace date_time {

  //! Formats date_generators for output
  /*! Formatting of date_generators follows specific orders for the 
   * various types of date_generators.
   * - partial_date                     => "dd Month"
   * - nth_day_of_the_week_in_month     => "nth weekday of month"
   * - first_day_of_the_week_in_month   => "first weekday of month"
   * - last_day_of_the_week_in_month    => "last weekday of month"
   * - first_day_of_the_week_after      => "weekday after"
   * - first_day_of_the_week_before     => "weekday before"
   * While the order of the elements in these phrases cannot be changed, 
   * the elements themselves can be. Weekday and Month get their formats
   * and names from the date_facet. The remaining elements are stored in 
   * the date_generator_formatter and can be customized upon construction
   * or via a member function. The default elements are those shown in the 
   * examples above.
   */
  template <class date_type, class CharT, class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class date_generator_formatter {
    public:
      typedef partial_date<date_type>          partial_date_type;
      typedef nth_kday_of_month<date_type>     nth_kday_type;
      typedef first_kday_of_month<date_type>   first_kday_type;
      typedef last_kday_of_month<date_type>    last_kday_type;
      typedef first_kday_after<date_type>      kday_after_type;
      typedef first_kday_before<date_type>     kday_before_type;

      typedef CharT char_type;
      typedef std::basic_string<char_type> string_type;
      typedef std::vector<string_type> collection_type;
      static const char_type first_string[6];
      static const char_type second_string[7];
      static const char_type third_string[6];
      static const char_type fourth_string[7];
      static const char_type fifth_string[6];
      static const char_type last_string[5];
      static const char_type before_string[8];
      static const char_type after_string[6];
      static const char_type of_string[3];

      enum phrase_elements {first=0, second, third, fourth, fifth, last,
                         before, after, of, number_of_phrase_elements};

      //! Default format elements used
      date_generator_formatter()
      {
        phrase_strings.reserve(number_of_phrase_elements);
        phrase_strings.push_back(string_type(first_string));
        phrase_strings.push_back(string_type(second_string));
        phrase_strings.push_back(string_type(third_string));
        phrase_strings.push_back(string_type(fourth_string));
        phrase_strings.push_back(string_type(fifth_string));
        phrase_strings.push_back(string_type(last_string));
        phrase_strings.push_back(string_type(before_string));
        phrase_strings.push_back(string_type(after_string));
        phrase_strings.push_back(string_type(of_string));
      }

      //! Constructor that allows for a custom set of phrase elements
      date_generator_formatter(const string_type& first_str,
                               const string_type& second_str,
                               const string_type& third_str,
                               const string_type& fourth_str,
                               const string_type& fifth_str,
                               const string_type& last_str,
                               const string_type& before_str,
                               const string_type& after_str,
                               const string_type& of_str)
      {
        phrase_strings.reserve(number_of_phrase_elements);
        phrase_strings.push_back(first_str);
        phrase_strings.push_back(second_str);
        phrase_strings.push_back(third_str);
        phrase_strings.push_back(fourth_str);
        phrase_strings.push_back(fifth_str);
        phrase_strings.push_back(last_str);
        phrase_strings.push_back(before_str);
        phrase_strings.push_back(after_str);
        phrase_strings.push_back(of_str);
      }

      //! Replace the set of phrase elements with those contained in new_strings
      /*! The order of the strings in the given collection is important.
       * They must follow: 
       *  - first, second, third, fourth, fifth, last, before, after, of. 
       *
       * It is not necessary to send in a complete set if only a few 
       * elements are to be replaced as long as the correct beg_pos is used.
       *
       * Ex: To keep the default first through fifth elements, but replace 
       * the rest with a collection of: 
       *  - "final", "prior", "following", "in". 
       * The beg_pos of date_generator_formatter::last would be used.
       */
      void elements(const collection_type& new_strings,
                    phrase_elements beg_pos=first)
      {
        if(beg_pos < number_of_phrase_elements) {
          typename collection_type::iterator itr = phrase_strings.begin();
          itr += beg_pos;
          std::copy(new_strings.begin(), new_strings.end(),
                    itr);
                    //phrase_strings.begin());
        }
      }

      //!Put a partial_date => "dd Month"
      template<class facet_type>
      OutItrT put_partial_date(OutItrT next, std::ios_base& a_ios,
                               CharT a_fill, const partial_date_type& pd,
                               const facet_type& facet) const
      {
        facet.put(next, a_ios, a_fill, pd.day());
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, pd.month());
        return next;
      }

      //! Put an nth_day_of_the_week_in_month => "nth weekday of month"
      template<class facet_type>
      OutItrT put_nth_kday(OutItrT next, std::ios_base& a_ios,
                           CharT a_fill, const nth_kday_type& nkd,
                           const facet_type& facet) const
      {
        put_string(next, phrase_strings[nkd.nth_week() -1]);
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, nkd.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, string_type(of_string));
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, nkd.month());
        return next;
      }

      //! Put a first_day_of_the_week_in_month => "first weekday of month"
      template<class facet_type>
      OutItrT put_first_kday(OutItrT next, std::ios_base& a_ios,
                             CharT a_fill, const first_kday_type& fkd,
                             const facet_type& facet) const
      {
        put_string(next, phrase_strings[first]);
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, fkd.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, string_type(of_string));
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, fkd.month());
        return next;
      }

      //! Put a last_day_of_the_week_in_month => "last weekday of month"
      template<class facet_type>
      OutItrT put_last_kday(OutItrT next, std::ios_base& a_ios,
                           CharT a_fill, const last_kday_type& lkd,
                           const facet_type& facet) const
      {
        put_string(next, phrase_strings[last]);
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, lkd.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, string_type(of_string));
        next = a_fill; //TODO change this ???
        facet.put(next, a_ios, a_fill, lkd.month());
        return next;
      }

      //! Put a first_day_of_the_week_before => "weekday before"
      template<class facet_type>
      OutItrT put_kday_before(OutItrT next, std::ios_base& a_ios,
                              CharT a_fill, const kday_before_type& fkb,
                              const facet_type& facet) const
      {
        facet.put(next, a_ios, a_fill, fkb.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, phrase_strings[before]);
        return next;
      }

      //! Put a first_day_of_the_week_after => "weekday after"
      template<class facet_type>
      OutItrT put_kday_after(OutItrT next, std::ios_base& a_ios,
                             CharT a_fill, const kday_after_type& fka,
                             const facet_type& facet) const
      {
        facet.put(next, a_ios, a_fill, fka.day_of_week());
        next = a_fill; //TODO change this ???
        put_string(next, phrase_strings[after]);
        return next;
      }


    private:
      collection_type phrase_strings;

      //! helper function to put the various member string into stream
      OutItrT put_string(OutItrT next, const string_type& str) const
      {
        typename string_type::const_iterator itr = str.begin();
        while(itr != str.end()) {
          *next = *itr;
          ++itr;
          ++next;
        }
        return next;
      }
  };

  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::first_string[6] = 
    {'f','i','r','s','t'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::second_string[7] = 
    {'s','e','c','o','n','d'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::third_string[6] = 
    {'t','h','i','r','d'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::fourth_string[7] = 
    {'f','o','u','r','t','h'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::fifth_string[6] = 
    {'f','i','f','t','h'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::last_string[5] = 
    {'l','a','s','t'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::before_string[8] = 
    {'b','e','f','o','r','e'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::after_string[6] = 
    {'a','f','t','e','r'};
  template<class date_type, class CharT, class OutItrT>
  const typename date_generator_formatter<date_type, CharT, OutItrT>::char_type
  date_generator_formatter<date_type, CharT, OutItrT>::of_string[3] = 
    {'o','f'};
} } // namespaces

#endif // _DATE_TIME_DATE_GENERATOR_FORMATTER__HPP___

/* date_generator_formatter.hpp
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
*/