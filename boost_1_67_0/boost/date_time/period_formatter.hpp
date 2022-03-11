
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
QggrGiibyk37QRVRvYiWeMQJzko9QFA2AX+gj3r+Rhe2iP1zwaUQ6neOIsIq/eIEHS0LzJwHA05bRh/I0/4hycUfkcg8fLGMVD2zIomDQl2p6NJz7daf9DfHGPGNIiXRMKc0YqzmqMF8UJMIrowr0DhC82/4jghd0Ay6b9yGl8vDmSzNn28gtZW1ar5wVEbOBgh/KKcNdxMaytycuBnaDiFKy2GjEKOKFsWLH5jkmWft+s3vHNRGZ+vfwHsAffQb907QEIgDYFsKfF5m0xvqVl0liATlk51W2XDfW14De+ye7NpvqzgzS9WUX+tIX4GCvKkpTxuW1JBVYDH52APN3UL1rC+61vIgv2pExSJjJJzSiL7mZ8zG2fu5D4r4ySRyE3TY6+SLlOMvKP5QIdDCScefjwV73ZIeQjubozqkUNz2yvqh2Vm8/Ig4Oep0XjHngnjyAJY7InPr0A89G+adsGc6ClYG92Y/EeSh2B9OcDYTHBPN1F1dolQu/QshNKWKx7uPpcVNioo5hBJLu7hgSJh+kIPhZYZ+yybxbZzh0nbSu9QVJlpZgO4bvNuhwv3HoWrEXYD/lktKgI+BOKXLt6ZU5Df6rJ7UU9vXJpZ0YnJGTaTT39wNGDtOaPcFRpTDFvOTjA6YOc0Rn8YdsbGLLs7wQnueazDkKtHrYlQS3gwI0GxEZH9QeWChqviD31/FaHMYy/DkbZbUoz2MlX3vRVYghdm7G7ATrMLLn/CIZjOt0sQ75FNms5E7nFJBcK70zdWEBH3EXE2KYUkZp7MdNP9MKMUNZcE0y41rQ5Oxbkea9eY1nnH0dNR5amkkskrh7b+s8h+uGyJVde6sYlf2H3+B4hD2yN/1oPS7JTIjFVY2nn9G3mF6ofJMTYRdoEZ/hSjqxr5xWNiB6D/cbGcnRLLvzbztn9DwRy19RGx6mYcbD5vKngSY4ud0/YROAIteX7ot6wwSgHyCBnjVPCgmJIHNmZvoHdFJVTN8c4fBl6RGbYJ9epPMN3q2Cz1OwGy15jKErWsMv3idFWO22cRtkjUAuEMFCFZV9/C9D9PwXdwVb9cwlSmlZaQhFORGcmQfLgs2fow9Q47CkrE37py+pTaCRyQTqMaOMVk2uysg2Fu70IHeyN8xEQqpEk8WrYckVJw3FAo4Y4f0CGh4cburcbqRumhXdH5bKgahK7pfwRUEifg1NipHxeSDWrwRyVccytKlqZrqSCk6ycpKy07Y8ZT91PzoyOi4HAoODy6KfEWULLEOus+pasoKtecqCqkMK5dDGSrY0wTWF523mXajePwzQr/UF1AE9aq/Kh3h8WWgw26ppco1aHqa5QYLNfRGixybbw0T9Wiukn6yY1fwQQPNeWs6rlVwtQgrvYa6QimyGN1MIbJPptVbpJb/mKjlhHuEw9FiDXRmeD84QtV9ZP09U/ONcw4TEmLDp1eC/m/8QBGQOuA+HCS2QD6BL4OXcZ7bS8myQroJfsr8VckFEM9ldtsFsuQtMtsQ5qUnG66iuik28XF2lLwLDrf7sUbFXyNnLJ8xkfMTscN5+f9upbK/QkQHE39pDBf0MJ8CkfsW3PQdu3lWLBZDmfGvH6wm67ntz6e/Gt3tBSpbFDZ+CzDQcl6/h9vyHP7vDRQBo0W/5Gg13zJxxvqMP48/iijNW7Em7hAkrxe0kpWaSM+MP3ZIZ26Da+wmvrELjLcFiCzUcKH1EtbeutSctvlZEWQL5j1HPNkg6ThaPk6O0EAscUpIFR9iHKUsLQt96jy7zP3/1bWQeXVlOEEq6YY1fL6cDROA0uZC91bqcyUOtLNzE0n/Y2B2NimLDcyoqiF2tJB8UXgKG8CKS4eaaqWvUeweacdm8czEcenEdX0wFyeptqTsthcZE9zY+08EMIksBr3M8BGZ5MetGTD7TrHIZOSQME6lycbR3mves2J5A1b942b4oh2Cd0EwYrqCbNvpNcN89tk5kYlZasM4bcZmVcpI8pcMVhd6KG42tRYYqhkVjqXL3/CJCWqOP7ZLWID1kykbwNE8zZpL9MS4+p+5JU3TgCqO8iKPow20/87dlZuVlGe5YVSeXwvtEIJrBlaDbdcl1zv+bz8MrAIIL5U8BPKy5qyFvt5XWVTBni1zlJJ1YjLGyra7AJ1/zEX4LZtD6dtLzb4aAN7VNzIH6iiUIeOUVvOytvc4RRh8woaOZRUWn5oJAKs6+xjxo06nkXBmlqpmojQDQq7L3t8BTWpi4FfWYfX8dgVmIkb8hnOOkx7P3qJDj2lOGna3eOcbVHbrddYvRrHZoWVRUkMeNNyUDsErt5GnIigUKYTMd1TjykqoHbpme2UiB6VE4KiYFy0Hw2j4T5RrHXD+XQeF2cpo/u+JKafOGJaSPGbPanX4ggFy2WotHyDwpgLVTke3Lq7NbVbBedMAyifA5nZ/AJbXW1bFdEDncjT50zrq7bgH/ofmYTh97B0UjpFKaWATUUBUX4WyJ8DG59Sk8/iB8q77kga74pYSJDJrI61B9n+c0btxoZv+YXkg8hBmz8tGkQ5UodFbD086ZgyvZamILPe6J9B7+cXyxWuR3fnM7xwxjMzi1+1EOb6udZxTHpAD4mVKJCrtjyJ9a+yIrAvNbOW8xi1Y7FbV4GMDJtiDL00wPxQkDfuenazRF+pm7Rcok1jCIcxnmyYKdnwNlBy32wLGIkW1b78cMUUXlw+KUPkUv5IdtTtrcKVFxW9PSmqgw/xXkY1xXZfvBE2MrKcjCerUQ1zCCjMUD4Nk+pXTdwSib5uU1/MCBT4nx6847ED/ZxxXXr+PLRWgR0EvC5VjXVZ7bddaiMiA8xnp9B713Rk1xyw5vvBp/8Dm7mC5ockM+UjvdDveiBXvr/6DfLklpvVFMJKr1a49kZZ8wKKFvZn7aaMj1fgfmy7FxapQ7rvdApuJzT1L3CCRx/SZGb9eDMOiQ16Ui6Hl5Xh3DwxCeYSSeM+C1M0CW0yHMJ34Tm3QZ8rzR4spG/U8Y96c1prJ3OL2l4Q+QngBfXuKR9h7n7cdoAf+CY7PFeEdsf2A1mmWvRy0fyoTzx1fk8GWyndIhi4TnH2FloE82o7FJ9b+4ykRcyInqhfJgdOOe4d3gwapraceLzVB3Mk5oacz28tD0WUKj0F4TywS/wpuulsM6D/nv1L392kXRkgxnom9V/EXJqapq7LT/pe5Gnms3+n2u+XQACbwC+s0sQsjsx2zkslRBLo4gOF9FPH+r9j/4ohIBG0hpKRM0BHg7iTNr41GiCsmDWqykCnkztVu+h7V75WzTlEOxvzeCr5sZoaxf4bVG4IkY7FLFf5GCgvwMy9vyLVHNHaZEhD6+PMuCzngOsPGbrHBvgWtXcZQ7u9tZV9tj5oSoZlPThQ9FXrECvBnUh1LFKdc8Od8poUmdPES7JdhCCJ0wrEl8jSM6p+pWpi0wpDXTV67zsQK1WDOMKzOadwm65YpIORUDtA6P9wiJeXUXt8UwzkfNDXC6AJd3/cxvgQzVIBMMytC57X9puPaTu8PMRNsy8ZzoFwg8rNR96m2RU8HYaAU7u6U9kmNYM/ajTZboYNgq+ZPj606Vbu3Qh+6j3LavXK8pzOmlvw0VrNA7uKmvKipBLjHpOA8DAhYsW+oD6ETxLb1wuQPwXTtFgfTLnb5EQhRjOI+huuaQ2vS0xmYCMpKlb/h3WtMc6YOKEtWVbnoYxFsujKwI5Y+ofzp4+DjywTcAqQFBrXqNQN3qtdbXpqMF1aHV4zefBVTHHQ3RFCql52hqkOyDE53N2/FfS7hPe2n6uNc4GZnvlCJiUzif1x5UHCRakdwnEwlc3pczpwzaneWIXBjCj/NOQ/ELRx7vtweOcwrEXarfINyJmv4rbopbw08IeL9NZmz52ihXBAKMGlSPSKAxS9VHqzUaB749x2qjOAgEYW/TElnBWRvuxo7ZfoqKs9CFo6wdN8P44cJQwcGCIyQsXvl6uquIiC5sdqpVu81xP7a324zXQao21HxO3J57l853W+DgFSkuxXjojTtrguK4WbaNEbNk8gvDBTEApivnB09bz8t1PUOAFkvQoGR5k50NzG74b8pqszhKrAvr443wxtL5p/HCUSx4vo/l/PtnEq0DLsGW4kULkKfFtMXHVDMrOrNLwNIbgDeCJTZoCoevjfpGK82XKDrdgWeoZ90y+UdL0W8uXa7LjttXHecjuaqQhI0QOVLcsI6aeCVTplEP+VzOx2u5lHBEvTaQb13Vsvx4OSph2eCmLNZxP6aRLPE6TwxnRM4EJQTdIO0M5oEY6e6B7cjHNJRncKiiOa9HwtXLOK6WifrJnlxKR3GDu2pu/HHZw7asptXj+LlkDrOt3mClwvrCdbiknYfqBDGCWjf2yqEKCD15kRu6Za21/SN0n7jpoSPl0JOFpzTRp+I2+LYstUkJK5wScn0Qf4Li68sXi2nKiIEjEPp/2NT+Dh/hSUqPQZW5K4QazGVJrcz2dXL9rdPfw4yu39EeSB9SEa5GnWrMyARLMmC26UZyV2v24DXDjyLr5FVOTuhlz5zSQ3itAh77KbWYMGntlNAtL02WdkdnnHg9+2EAmHO+nZYPP0hpCzNZjJGuKiZCmnjr/1nCbVSCnW6SjVe/YqwaJw0l+aJdyuS6AQxk1I7gFs2BiPspXVsOc3pS32Ucv0/Vdf2II4sL9MiiVIbq4KdbUkPFABzPmDuPw6PnmyInOrCHLkaCJWUfl9Ot1VpN6xRYqLGmcNu7Uu4nxvSkq0gOoQw5XNcidV/VhNoDEiT19YTj5uMQV5iFPUEhcFW4uCtbpt+MLhF6AhjeykI5pCVKML9IFLFxdKkQg30dlV/Y/mfEG0qX0Arc829YMaK13IM+nPaBrc7Wk2dXY8iGzyrCuqN1B+xSjQQFe13zqN+s3rw5GykDR5hBfKlnj8p+J6bXwF1KuxP1L1J7bp5M2uu2LoL4cfwwtqigmr0kvKg5oDgp51o0cxkjduC4b5JpAwFMwBB69P2fIAzZIoqcdpISqr50oH5LQ7oqjkEzfBpR9Ip1sigbhtdDpmUYZhxOzxdaX35CRfjKfODWKZVhf9T+JiMPz9uCFPtGncSgGr8r4XNvWh3ZeYIEyojfw5QxjD3DCaGKPGQmvZqDtDreDXM8lvIa55l3B7hqjGMBM6X9Mih6LBQqHOBqi8K0AOPYCvhVrzfnIg1Qg6Px/qqaU5shx6dU7st8HDLwqXRtEIkdlelLxpan+enhbXdw/Gi76vrENB4CrWutfLBFgAALP/T95WcxSQ/nEII98RjWAv0VW0r59OdKwukimpOhq1z3WP9+C+Kut49+HPo00fA9CyfsKOx0SpPNGljNWZLcS2bQFcV3wPDTiPatE+5tIoouRf3eFJEFIferqBB/16Ub1+oTC7g/oEq4cwmIAjJ9wQh4+85H+Kz8GnV4EU3GRyxLsRUM3a8G9B+ErjD90lHqXOflLOiZOTDA7oqZAH1DFdsPuBqF2pXlVrKl7WyLu+txeSJI6pJD5tg4uYsiBfPqKvkOucWamh/tRYnhXpkSW0akKNyLZNKWi3M/M+6ga2vwNs6m0uOhBg3T6S4TnthFUNBNHw26ABOd6dIlzecT9uMj+BWS10LDCXl94GWQ9pHIqgUTJwR9sK7HffTTuZCPsktyyDK26zCFvq1yyzVNi0jjVc+/HE8XC3zUkdjb1Ym9AmuESINc43T0bYwkH6l7JG9IIswJ4viFO6eMVejEwXPHokVgY4hhCUOWxSiX8CA7gothCicN/k0yEi1WiP0NZqaJOnGxTjX43wEVsRNr3ogXAoNWiqqk5ZvVS0kDt5dqNtTK64efSCEsO4tdJ0OPVkVxdIr/yh3w9vPIuLsXZqj+B4OlVctnyawUrlGeBPXt6WEm7zcT9yUM0smu0SrGvcveQSz3dIBOqNGjdZdd0nx92GErA+Vq20+E80anQUCGlpoHK9OiJuDaVthTJC/U9ITSsWp3sV2j2Fnfift3a3iqiJaQTstFLGZOBNOxFm1ziXfY9ZKmtDAZQjgCen+m97Jmp4QUlmTNypYMzXZ1gpS8O4tG+tolxW5zUR+zVoGgUewoAgp+6duLBiG7KwZeABc+48g0TybOhcP2GqufbmZ2vm5EC3U5JD1EhpivyKdkLR036BRLUI3fV0wro+p66MHY0k86hc6OHAo+a10Sc2PTXUepja9vBqNX5Ddn3bFlfM3cIN1Uw6YQOvyS0W0qcmE4QRxE418/Z2uBZENBRXXW7I1fQgWkKquXghCTmFe8ry/yaD2YT3c4sghI/W6pukjrZ+MrruobJYZwcTeZh71o6snduOeXmqn9WmEtGEWaIdE62ZnTLzlQYrByLl+gXgAk1U7ReVPAV7ZDCD/tSo46kBhdGJdNoiw3qXdMLHn7dCIw6hZEOtL73LbPlUYP3+HTat/xpm15mfMoGRXw3h69n1JtTiph4ueOivlufFXwAMZj7wjWfJwul4kqsDOml6jjhkJQWuQra65U9ItuyR4aoEbd5lMPj7uN/+BTOiC1nDREp+7nHlUYjdQt5Y/fB5tCU/isZt/YPumxJv3ofo9bf1kigfcm/P2Qy56D+Ww7VQh7zkonfa4wrcDtILXjELrg/z0ZwU/9ht3M4ZnxehZq+uJxRzx7bpqavUCLivf3Fu55bZWAliiBUYZo/3dtoQ4NIX7kCvKU7Q6eF/foSC8EhUSBr7g8/i7Ansd4m0V8UcDRC/EHZ0U8yDS0SGJIQyMblX5HLlmRg2RwDLrwfiuhdTLhBtj0HoGcb8LIa6J5i1varRqunGBag4rPI/6DCyPbV7IyAE8cS19aa5WCXl1AUJirXanXUqoAu2AIjyb5cEZ2MeL6xdnuxIqNMU4DfOkzUD/IVM2yqth0U826DHkodguUP7fkkLd3IOsA82bwcoG2qroFHnNWL8CyXvzTfHb1NUt477WV/UtDgLB9DOXkAwzIXU8D/4IRMXLpuk4OFpaKLhj/0QgX9u/NzEexf/FgPvfcPCsVXxTyKl7C8iyfm1aoYsvzIqUUm4dLexhpjqz3GTVjYRLIFjrNkPbGUmoinXmhSdiRU8LZijnBiq0ul8uZPeP1aD7KBGSK6hBRtYZuejeyzjWFUb0FE9HL8duARzyvLSLW5Wd15zz7i3KgIlmRCxC6K1+u+VfuLiLUqMtC/4ToiCybSRiV+4gR+nEvKPldxhxrJxWAC6kb5+WNGzUS8NSKjdn1tCbZPdX7+hR0r2iRY6N8ZsfGrqK6wtVzCTrINiXlyNCPQHsM4+eiaw5fxTSjYErfBmH40dKyWdnOPtfC12+M8Z0ak7yxE4ZuIjXx36TVWXzZ3TAQ00CbnQfyUjDAbXU+cDjnhuPyoVP2du7CDpGB/MZwm+9ipnydjKuDxvrqZSdss/Ebd1AgqjfTrVn7J08OcmAVKUJ99IHhpGFAZhMj5nBy2qphsJ2mtPwVdQTEoHeS6RA3fPmFCg6Wxv2m7s6yUkeAnBpaADylZ2YYiCL68SniJZ8MyWr5152QyybC/6eg1iDf1y6aK96JMGhyiekbbbkXHJXZwqWd/pwr9CoE7tjfH2Rla3Qktq0DKm5kMZqB3g8HmM/sF9qa/rnyX36niqH7sQbCWCS9D7Rl4OFkx42GmoKaS9eulTKJoNn4fYlxetcdZVsRPONMwTuKc4RQmgloD9a0mGFyt21UXKYNC8Oyhibr1DCRf5Tap3SLsLvHWNEFP4nAsQMfxHuvnrh8S5i04MBbZCXTohRwLlYpmgU155Rcb+yRwvx+Hib/dnxmg4V79aiJDJAgQ6w6OvmBvf2mGXevQ1WfJCPqx93/Pz1MHurXO41tocuELkaCSXEtASu+QguqeycGetsBafVXPHtmHilY/wh7vM4tQoIZ4apedzRzzWi4wuzqds3yJLmbY7cZdMqWpLbM0mtzWNviFLIZQOii+LToCjNVtgWcL/8LAqF1t799NcBghXPnPCowYxp2aMr879ClDYiZxf7O1/LAueSF+SbyZttbuM8CzmXumwr++1eObXLB6l2GJ7VaPHgO9nyTEdo13A0pos9/5+d4uiDRvmnFeVFeSMla83+eb2mIs0DnlnRkvLktDJIV8720K3Cf2W7H7dS5qfslkrba1zYVTOLW3XZX5iok/o9iq7UfrIqBstyqKT9D6hDyLJjrewNCyRFixAEWuIWOVl1/Mr88VT4KEe2rDFdOcw6dZdthXTMwe1DymDfzj7qlYZldDC4SniUOo1VoRCePUIU+wAqZ9e117td+gbjrzpJMf0It29KtozFQy0rSH4NyrqZjS8/0qE3GHfUeIhg031d8YyR2fp0qlUbEs7B+QRLzXS8MU3YESntsjDYowrkTh/Qvy/Wcz7LgJD6lGphrnwX6tZYrnpmLhRLtkD8cLpT9LW1HgbSpay05PYN8PYOBrybrxvlPmImVfmyduXyFGbStuOBr+5llbB336RpJmIUc7WsLJFnqt82ucu+38BdlaR8tr7jHBHhxlBvLZecUQ2qXf+e97th3tsLVaWmnoApJVAQoakWAfjjK/yTZ+vJ/HvAJBCuJ6hR/3TlwtcqMGEbUDDscaHj9Q2y0hEktyd+DO0DNzqzGMpU3SOyFfJkJCgm53CywQr+9YYHtRXvSr621dZVEvbOcCrYZXep8GRa+b1h6aNnT7JWajvf4ycu7FAVllzRflvESx4HwFqx6/cnucn4OGjg/9YEDrC1uO57LEZMa/wqMDq9Xsycsltn6hriDKNErrO+Q0R/Ee3ZYwwXPStCD4Sepx+NCDl2jzArs7bVmE0mdKmE0f/DEaIydcfzvY6EQCQEOqdepj18s/WYoy1QnaquwUm0KukrlKUmdoZHshs/DB8VZmkBZGX/YI/G6Me3BAT5w1nGrGcu1uRFEuwWiklwOw3OXYxiOZ+GTi4faUimQpKbCEQ/MLiyQuDHdN1OOKpoO0jy+cNP2G3YnD1Hh0PvkHQf6hPicr4U9sdbg7/6EEhOMPUn/YbpJppgbLjGredSh5qZz3IIhKAlKO3PWxIjwZbSb6jpFEFUjjTVSNy5hFmZzT0m9+RSNndKj3fMJBSRkSC0KH0MQQgYdIdg+GUiLdHVH5cDf8Emz373XFpboaqVZJ5QsH+wZRJSVBK5DpowvlwapgL8C53Tfqlo0H3aU33+OocgeXtmW5Y=
*/