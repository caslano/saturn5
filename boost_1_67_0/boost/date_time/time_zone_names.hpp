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