#ifndef DATE_TIME_TIME_ZONE_NAMES_HPP__
#define DATE_TIME_TIME_ZONE_NAMES_HPP__

/* Copyright (c) 2002-2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <string>

namespace boost {
namespace date_time {

  template<class CharT>
  struct default_zone_names {
    public:
      typedef CharT char_type;
      static const char_type standard_name[9];
      static const char_type standard_abbrev[11];
      static const char_type non_dst_identifier[7];
  };
  template <class CharT>
  const typename default_zone_names<CharT>::char_type
  default_zone_names<CharT>::standard_name[9] = 
    {'s','t','d','_','n','a','m','e'};

  template <class CharT>
  const typename default_zone_names<CharT>::char_type
  default_zone_names<CharT>::standard_abbrev[11] = 
    {'s','t','d','_','a','b','b','r','e','v'};

  template <class CharT>
  const typename default_zone_names<CharT>::char_type
  default_zone_names<CharT>::non_dst_identifier[7] = 
    {'n','o','-','d','s','t'};

  //! Base type that holds various string names for timezone output.
  /*! Class that holds various types of strings used for timezones.
   *  For example, for the western United States there is the full 
   *  name: Pacific Standard Time and the abbreviated name: PST.
   *  During daylight savings there are additional names:
   *  Pacific Daylight Time and PDT. 
   *@tparam CharT Allows class to support different character types
   */
  template<class CharT>
  class time_zone_names_base
  {
  public:
    typedef std::basic_string<CharT> string_type;
    time_zone_names_base() :
      std_zone_name_(default_zone_names<CharT>::standard_name),
      std_zone_abbrev_(default_zone_names<CharT>::standard_abbrev),
      dst_zone_name_(default_zone_names<CharT>::non_dst_identifier),
      dst_zone_abbrev_(default_zone_names<CharT>::non_dst_identifier)
    {}
    time_zone_names_base(const string_type& std_zone_name_str,
                         const string_type& std_zone_abbrev_str,
                         const string_type& dst_zone_name_str,
                         const string_type& dst_zone_abbrev_str) :
      std_zone_name_(std_zone_name_str),
      std_zone_abbrev_(std_zone_abbrev_str),
      dst_zone_name_(dst_zone_name_str),
      dst_zone_abbrev_(dst_zone_abbrev_str)
    {}
    string_type dst_zone_abbrev() const
    {
      return dst_zone_abbrev_;
    }
    string_type std_zone_abbrev() const
    {
      return std_zone_abbrev_;
    }
    string_type dst_zone_name() const
    {
      return dst_zone_name_;
    }
    string_type std_zone_name() const
    {
      return std_zone_name_;
    }
  private:
    string_type std_zone_name_;
    string_type std_zone_abbrev_;
    string_type dst_zone_name_;
    string_type dst_zone_abbrev_;
    
  };
  
  //! Specialization of timezone names for standard char.
  //typedef time_zone_names_base<char> time_zone_names;

} } //namespace


#endif

/* time_zone_names.hpp
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
*/