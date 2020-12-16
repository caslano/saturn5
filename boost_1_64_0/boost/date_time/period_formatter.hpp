
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
Ykpx/ffN1LSrKrj++37eKmv8i+FoRTi4SQHKGXdzc6CovIqPTWoZ6jyRMSN4wX1fF2j9XkHwwfb0Hj1GjcPc+MDvAvO7OyQ9+MmX7LGUA0fJ6IkiP1+HIm3RmI2MNWWua2B/f6i2eabj/yZt/MMNXDKz1zwpuPAXxn0nGWfNFGar9yIcBoOfjmLqwu3E/S++1MpoN9f/LaDufOAyc/3fyiT1Q305vl6TzPV/K63rhyLzCVXmZbH7o7SVVvZXD3P41Qb9wssrrMBP5PBnL5Vj0E6jAt0NpNOgSkGHAwxXwvZ04Pi8Uw4Pvq01DJ9AgfuXfnzX46EbrVlyZrQFw5JIC/k4Do/4hJ8BqyM7vrxVpNXErwTdkTf9/cI5BJnvVsApHFjXitFO8TSkmTBJYnnI/YU7qi3COXy0Xr2/iLj2w5VJ+tUesdanLZ/5SZrzxU37ncgs0U914okRb77Elb+G3hjT3rbSHYI/9OSBaJSLAyerjfcwO1nhHTIQ+hqXA8h4lALbDoLFHKT1fFP1vXteTH2zlDLPgfpiSrm0Hh0lnUWXMd/eikQf+iVqgdOo97tM+T/VRw0eUBA6GjQZnG6dQBw9JihM6CasOjgbaZA/Nj2ll0c+xmez8+9qdUFyREbImbIKaqUtBS9M0p7coc+uQW+G3Uh8/hxQiyRfqOedmNSdkrZiEh1X3Nlo0XmH9K/w2Vxumnc0IZsGyOr8mNL1bBPTvGNoS132lNxSPyS31A9emZR/heK4/guGztXH9xLbaNX7wCg20I4Vt+bI3cB5DnkH71Q7zydCUuB4q8CNfTka5xaQJ8PIhdD3BNBG8UwLHI6E7hNJBGCKpA3U9CdrsemfYNMvlk1fdwU2nd22IojBeCd1egBvk1zFoJ8k6KsZ9G49dAVBo6crYM55AEO+4sbE1AdNxGdMYbEKrr+6k6GyhYwrUpmss56lMp2szI/0ZTZOZp3VhccMKCyqTeFRQQppKh5V64Ht1SH4bzjUT/z53Wu2xm+o9XAVpbITn+9gCI0DeaicFetGweLUUZ/aT6YuHGVxzhjW/1l85nSmmbNiI8wcF6aEzzJZgSuTZTCx5f1+lt4IOB/Kk3yk4+1Jr7gG+1cbh+VwJXHjXT06k9VELK46/7JFtS72ik8xb2jrkx5S7JLYACrDyix+NYcr1PyULDuyIyVPPZomg1c6MEXakWQqrvOUhRqmNx6kX9H4/GfHDRr/scR3Pj4gDfy/s1nhO1eOkHznL7YEfGc4zeKTn5B8p0LO4r6XMc4xXcUh6egnvt0/wMiMTEPhDSMI6xePE2/QYd19KeMNPakSmSpPou7FlviITXz5+H+KTcTnBzkzmuQHJWzG93pczPg7RyI/0Kd2kKnTRx4kP7hjOp+fk2l+zn8sx0Zmoe8O+XfwgzxR3jVUXsfHFH6QueQw8APODhLK53dfL/hBri1WJOfrCk5YcmD7zKPED8o0ftAShXHJDgZSquzHdix1auve9XnkRtojIjoiK2BehnkgqtAzU6xsVOPLc3Xr9PJc+nr98ysx6e1i0vvHPM+LeT495nk5Pjd1H0Hzvbc5cX+J/An5976p+kgdPq2TfMS0j9mgMe3+0Itix4VRYYg5H4NMMcokFuTR0QYWycMtWCUqFfFNDXb5FYBdeCVkG7PK5sYzEpZYnwY7K8zK3SeMIYdx7chd30aYQtUu9ptv1coQiuKaRprrY5zapnTH8Y8V6A3bNIy4n8802tUpmNOzKUTBR16Bh0L0FAibueSDhiTxib/ejJ5C80cVc6X4CgDMPYt92nhiFhPrKUxQ1sYUezXMtOnsYOB3+BUNOvhqyulTjudwjCYVor8inZvIgMVjYSk=
*/