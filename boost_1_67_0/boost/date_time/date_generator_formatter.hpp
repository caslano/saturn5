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