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
rJbkfWOlQxWW1KaplSzfSf6/Oj3p52d0crGYzOb58izLs8vFOB+9vpie5OPZlD6j3iefUyabIPAe9Wq1YgXQF/0vPu/zAH9bSuG2Syc97zX+ISsH5OyMpsPzUfL38NdHdGcV9rsQdb0SxRtaY9E8jyrjvAsY2dV0Ns/GWfKR0kXdlpJectKoxOrbJOAjpDB4VSEqQO7zKB1yZSlhb1p0pVArz5Da2y0d4ilN3t8InkYoqOOeDgvTap/SrVElHULOtjn4OiYPmf9KRFdABYHW0OnfkpA+1gw8XvDop/loMT4fTfPhJLkUkKu+OY7OXUvh26g4KWy9pZCaPYCRjbBvotuhIGnVBstEr6Ex1gFBGl1vk5UkqdnTJa22PA+9RnkAeVgNeQCo1+qGc9xBjXS9fnV0FCOOuM7r9bwfrA3dJ6K8VS4aSRuP3qOaWCZaVWNNCQYhBVpJ7KoMjnpaGKG3oFnCmFZuzG1QOVZ/OspOFuM5U5PMBWwgqDFKezao4R5nn6il1SFFyotmfGT1xm8byY3wDrErAPeTJPj1WRjdSB+HIx07cVvZgGdZMi1og3Vt7hg9EQ3TJUIoXji/W5bSRxusAZoK2i1EgcG7SuoHSBVqaUMrRK8ohC0T5VFZhgOBIa7X46ApEAxub1rm
*/