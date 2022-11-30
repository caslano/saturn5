
#ifndef DATETIME_PERIOD_FORMATTER_HPP___
#define DATETIME_PERIOD_FORMATTER_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <iosfwd>
#include <string>
#include <vector>
#include <iterator>

namespace boost { namespace date_time {


  //! Not a facet, but a class used to specify and control period formats
  /*! Provides settings for the following:
   *   - period_separator -- default '/'
   *   - period_open_start_delimeter -- default '['
   *   - period_open_range_end_delimeter -- default ')'
   *   - period_closed_range_end_delimeter -- default ']'
   *   - display_as_open_range, display_as_closed_range -- default closed_range
   *
   *  Thus the default formatting for a period is as follows:
   *@code
   *  [period.start()/period.last()]
   *@endcode
   *  So for a typical date_period this would be
   *@code
   *  [2004-Jan-04/2004-Feb-01]
   *@endcode
   * where the date formatting is controlled by the date facet
   */
  template <class CharT, class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class period_formatter {
  public:
    typedef std::basic_string<CharT> string_type;
    typedef CharT                    char_type;
    typedef typename std::basic_string<char_type>::const_iterator const_itr_type;
    typedef std::vector<std::basic_string<CharT> > collection_type;

    static const char_type default_period_separator[2];
    static const char_type default_period_start_delimeter[2];
    static const char_type default_period_open_range_end_delimeter[2];
    static const char_type default_period_closed_range_end_delimeter[2];

    enum range_display_options { AS_OPEN_RANGE, AS_CLOSED_RANGE };

    //! Constructor that sets up period formatter options -- default should suffice most cases.
    period_formatter(range_display_options range_option_in = AS_CLOSED_RANGE,
                     const char_type* const period_separator = default_period_separator,
                     const char_type* const period_start_delimeter = default_period_start_delimeter,
                     const char_type* const period_open_range_end_delimeter = default_period_open_range_end_delimeter,
                     const char_type* const period_closed_range_end_delimeter = default_period_closed_range_end_delimeter) :
      m_range_option(range_option_in),
      m_period_separator(period_separator),
      m_period_start_delimeter(period_start_delimeter),
      m_open_range_end_delimeter(period_open_range_end_delimeter),
      m_closed_range_end_delimeter(period_closed_range_end_delimeter)
    {}

    //! Puts the characters between period elements into stream -- default is /
    OutItrT put_period_separator(OutItrT& oitr) const
    {
      const_itr_type ci = m_period_separator.begin();
      while (ci != m_period_separator.end()) {
        *oitr = *ci;
        ci++;
      }
      return oitr;
    }

    //! Puts the period start characters into stream -- default is [
    OutItrT put_period_start_delimeter(OutItrT& oitr) const
    {
      const_itr_type ci = m_period_start_delimeter.begin();
      while (ci != m_period_start_delimeter.end()) {
        *oitr = *ci;
        ci++;
      }
      return oitr;
    }

    //! Puts the period end characters into stream as controled by open/closed range setting.
    OutItrT put_period_end_delimeter(OutItrT& oitr) const
    {

      const_itr_type ci, end;
      if (m_range_option == AS_OPEN_RANGE) {
        ci = m_open_range_end_delimeter.begin();
        end = m_open_range_end_delimeter.end();
      }
      else {
        ci = m_closed_range_end_delimeter.begin();
        end = m_closed_range_end_delimeter.end();
      }
      while (ci != end) {
        *oitr = *ci;
        ci++;
      }
      return oitr;
    }

    range_display_options range_option() const
    {
      return m_range_option;
    }

    //! Reset the range_option control
    void
    range_option(range_display_options option) const
    {
      m_range_option = option;
    }

    //! Change the delimiter strings
    void delimiter_strings(const string_type& separator,
                           const string_type& start_delim,
                           const string_type& open_end_delim,
                           const string_type& closed_end_delim)
    {
        m_period_separator = separator;
        m_period_start_delimeter = start_delim;
        m_open_range_end_delimeter = open_end_delim;
        m_closed_range_end_delimeter = closed_end_delim;
    }

    //! Generic code to output a period -- no matter the period type.
    /*! This generic code will output any period using a facet to
     *  to output the 'elements'.  For example, in the case of a date_period
     *  the elements will be instances of a date which will be formatted
     *  according the to setup in the passed facet parameter.
     *
     *  The steps for formatting a period are always the same:
     *  - put the start delimiter
     *  - put start element
     *  - put the separator
     *  - put either last or end element depending on range settings
     *  - put end delimeter depending on range settings
     *
     *  Thus for a typical date period the result might look like this:
     *@code
     *
     *    [March 01, 2004/June 07, 2004]   <-- closed range
     *    [March 01, 2004/June 08, 2004)   <-- open range
     *
     *@endcode
     */
    template<class period_type, class facet_type>
    OutItrT put_period(OutItrT next,
                       std::ios_base& a_ios,
                       char_type a_fill,
                       const period_type& p,
                       const facet_type& facet) const {
      put_period_start_delimeter(next);
      next = facet.put(next, a_ios, a_fill, p.begin());
      put_period_separator(next);
      if (m_range_option == AS_CLOSED_RANGE) {
        facet.put(next, a_ios, a_fill, p.last());
      }
      else {
        facet.put(next, a_ios, a_fill, p.end());
      }
      put_period_end_delimeter(next);
      return next;
    }


  private:
    range_display_options m_range_option;
    string_type m_period_separator;
    string_type m_period_start_delimeter;
    string_type m_open_range_end_delimeter;
    string_type m_closed_range_end_delimeter;
  };

  template <class CharT, class OutItrT>
  const typename period_formatter<CharT, OutItrT>::char_type
  period_formatter<CharT, OutItrT>::default_period_separator[2] = {'/'};

  template <class CharT, class OutItrT>
  const typename period_formatter<CharT, OutItrT>::char_type
  period_formatter<CharT, OutItrT>::default_period_start_delimeter[2] = {'['};

  template <class CharT, class OutItrT>
  const typename period_formatter<CharT, OutItrT>::char_type
  period_formatter<CharT, OutItrT>::default_period_open_range_end_delimeter[2] = {')'};

  template <class CharT, class OutItrT>
  const typename period_formatter<CharT, OutItrT>::char_type
  period_formatter<CharT, OutItrT>::default_period_closed_range_end_delimeter[2] = {']'};

 } } //namespace boost::date_time

#endif

/* period_formatter.hpp
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
*/