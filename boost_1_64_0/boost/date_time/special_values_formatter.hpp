
#ifndef DATETIME_SPECIAL_VALUE_FORMATTER_HPP___
#define DATETIME_SPECIAL_VALUE_FORMATTER_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <vector>
#include <string>
#include "boost/date_time/special_defs.hpp"

namespace boost { namespace date_time {


  //! Class that provides generic formmatting ostream formatting for special values
  /*! This class provides for the formmating of special values to an output stream.
   *  In particular, it produces strings for the values of negative and positive
   *  infinity as well as not_a_date_time.  
   *
   *  While not a facet, this class is used by the date and time facets for formatting
   *  special value types.
   *
   */
  template <class CharT, class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class special_values_formatter  
  {
  public:
    typedef std::basic_string<CharT> string_type;
    typedef CharT                    char_type;
    typedef std::vector<string_type> collection_type;
    static const char_type default_special_value_names[3][17];

    //! Construct special values formatter using default strings.
    /*! Default strings are not-a-date-time -infinity +infinity
     */
    special_values_formatter() 
    {
      std::copy(&default_special_value_names[0], 
                &default_special_value_names[3], 
                std::back_inserter(m_special_value_names));      
    }

    //! Construct special values formatter from array of strings
    /*! This constructor will take pair of iterators from an array of strings
     *  that represent the special values and copy them for use in formatting
     *  special values.  
     *@code
     *  const char* const special_value_names[]={"nadt","-inf","+inf" };
     *
     *  special_value_formatter svf(&special_value_names[0], &special_value_names[3]);
     *@endcode
     */
    special_values_formatter(const char_type* const* begin, const char_type* const* end) 
    {
      std::copy(begin, end, std::back_inserter(m_special_value_names));
    }
    special_values_formatter(typename collection_type::iterator beg, typename collection_type::iterator end)
    {
      std::copy(beg, end, std::back_inserter(m_special_value_names));
    }

    OutItrT put_special(OutItrT next, 
                        const boost::date_time::special_values& value) const 
    {
      
      unsigned int index = value;
      if (index < m_special_value_names.size()) {
        std::copy(m_special_value_names[index].begin(), 
                  m_special_value_names[index].end(),
                  next);
      }
      return next;
    }
  protected:
    collection_type m_special_value_names;
  };

  //! Storage for the strings used to indicate special values 
  /* using c_strings to initialize these worked fine in testing, however,
   * a project that compiled its objects separately, then linked in a separate
   * step wound up with redefinition errors for the values in this array.
   * Initializing individual characters eliminated this problem */
  template <class CharT, class OutItrT>  
  const typename special_values_formatter<CharT, OutItrT>::char_type special_values_formatter<CharT, OutItrT>::default_special_value_names[3][17] = { 
    {'n','o','t','-','a','-','d','a','t','e','-','t','i','m','e'},
    {'-','i','n','f','i','n','i','t','y'},
    {'+','i','n','f','i','n','i','t','y'} };

 } } //namespace boost::date_time

#endif

/* special_values_formatter.hpp
JcwTN0NtCheSMMe8kpSAvlaFTdRKmifFq1XCPGoG01rZMQfWSto6L0DLIzdObtEB+lYUp+CLfLTD2xTK7hbF9zgiq+26AijdnSDd1WS6mmhe+19FbXSEwpQKoDyaImJ0IuyGzOa9N1XjJMM0DlWBD1Vo7eitdrHfPKFKWKoh5DBIPdpOpm1gVIlTJPxLI9hoZmjTYJhuGgyDabDnyDQ4PNMgffiRaWC5NqbToBqFHHXYK6ObTFu9+vFeAOM9ayO8ZobAvTdhQhWWpMwQ/Xz4DubDFlSUIFgBYmTwSA+1e/Oxe2X/iRfYIhwVwvxTLkcwe+e5fu2nl0c+9EnSHpX8n5ypaRIkG/LoTse1NDcOT+QgTeRxJcwTN4M6LD0wLL2/qlrZRa3IXL8Vi7lHVwhCoO2JZCkvMkF7pDJJuh8AfypbClTbdVexKd2dIN3VZHrcRNmKX1dtXobaoEQriSVeoO4xCYOlX9kH/a3PVOznSuLf/x0iQsdVoLIWJPxqkvBPcGmxy+UUyBdvkJAxAc7lXMjHYWwls8t6Zus5qaLegIWKehGjlcwu65kt5gzMDLnEO9RAwCOSP5LBH2Toxaz5U7jsOEo2Lpc9IlYZNVS2KRcLbyKPK2GehBkkNzSmGbmheSUS5ombASUFrGFvXkPcZIt7R7ECbi5wSwP79FPs5AWosNwwRM8m/XpphV54Y8W58mq7/loPiXMJ0l1NpjeV6IXCE6S7E6S7mkyPmxi+DE5mcRjuz5r1joNGKqr+lnFHgaBO38R6RXBLZLrYKzwj58MBti1iRnJpWXO78KiuATiueOvHnzEq/qjWKRTNlXd1g24sKGOgwcJAarAwIGPzZCfMg60SCRamVIOFqWmohJrnsI7zhsCRcd7UOJctV4IbYhYD++YksJrRZS2jpVxeqxX0Wq2g12oFvYlzhVubiQu+gIVVmCkqrGR2Wc9sPafQe1ioKNNdWMnssp7ZYs4kxIWqI+KCkiEpNrkTjK50CjLkjL03xaowCun1/z3LzMXZxVf8wvAVmqjwlyND8GCH4NknHMQQ1GSyck0mK9dkMDT0LYk24C/ooRKQwVpzGawEZLDSvUwGmy5lMOrmhqbGQIM6gBKkuxOkZzeVnt9kYoLC8xMUHjt1Y8c0HgVbXXV9Vlddn9VV12cpV6HVChZarWCh1QoWJs4l/AMIvS42iw9ar9CU44QR+wZVL+PX62XwhbiDv7BTWortp2Yptp3w9xz8LYe/SvgbCn8++FviTrFdBX/D4a8//LWDvx+zUmzvwt+z8LftyOfI51/sHQl4lMX1381usuRglyMQEGXRoCuJZZGIQYNuJOpSQ42IGBUxKmAUj6AbigoBBIW4YFFRsV5ULeJR8agSqEcQq7GiorXeVexhd13PWgWNdfuOmfnn391kNyiYtvzfl+z/z/HmzZuZN2/evHmz+9n9/EBPoj1n+0GaV0xgbB7Fx/h40LIqWxDDXZZwf9hha3aYTFCFgTMMGdgLAz0QGM5n3YCZ3iOj4MeBcZgP7JbkDBFuhTwbo54F7+PXgo2GDcKeQ+EDPINfRr9ZjispjUulsas0IylORWRxBGeSJeqYupMxDUO0iQ1mSo8OJkqND0emRiiZOj27F3UKuhd18rsXdfK6F3Vyuxd1enQv6ri6F3Vyuhd1srsXdZzdizqO7kWdrO5FHXv3oo6te1HHSEWdBOGpb3FzX5tVyAJ4DgjM6NzL7mf3szOepPNf+++s9YLR8XrB1r24i717cZes7kUdR/eijrN7USe7e1Enp3tRx9W9qNOje1Ent3tRJ697USe/e1GnoHtRp2f3oo67e1HH072o02v3emH389/5pLTfnk3nf/c=
*/