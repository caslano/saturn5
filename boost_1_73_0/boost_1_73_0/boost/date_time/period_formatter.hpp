
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
xeILhX84eIfnD6g6pd2pL4sO/dCpL9T2pxaVrnf8ebH4AXV3bCT/OeXDdwv+iJVwsjp/YTbbQt2vHLUvOnT2+vVf6YRevjh73aVLoZXMaeakXsrivkvvUr/y95X4/Lln5U9dko5E3jsQOF8pS9Zk7lEUkvA5V4nUVqYkLKXSJoVa4ovS5FaSMpVLuhhPbgejX7r0uFLJqpKzNSXZlSnzlFbiQVIhE6kegpiNKByZDBIgP1XWQWbplNE9qJfkZLG2lRg2QuTWkHgQKhdLqBOOVs5t7JvT06QscnhymprEniZ1KHort37i1S2sWYstmY0jZ6i0sku8v0trk6qMnwgRFjflMld21d2ZBYU6PTUFWZnnlTgcVdIGFyTNqmh1eSdtYL1y/LBGW9b2uDLrg40IayUoKwsNdQgL9qUGge9SqVNZ+P0+ELWWKso+5N9J2c72lIyGVdSKZzSYtWgprLJd+jiYvx/fzOljPJ3Go/ktja8oHt1W8j4MRpfAhoLWguTnTSEtrChIrTe5kumB8j+00qPe/D1d3EyH48l88b4fX/anVzeji/lgPKJzap29on+UmtH9lxa1crXk9NOr3vmr3gss8LeFFHa7sNJxovELTFmInb2nUXzdj74h++6EEpHnS5F8QqiBrwqsllZS
*/