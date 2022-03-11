
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
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
*/