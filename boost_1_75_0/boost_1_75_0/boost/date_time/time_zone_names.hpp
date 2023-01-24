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
JHVE02El0Frkk6sDJL1FibQqkl+6dqks+U+tTq9MV3Cc4nTYJ5FT/o/IJ0i6gdPzl5VeemrtkSUf3vHH5377Tw++kvz4gi//9ztOXVv+5vS1/ofT1/o+cconS7KcoH/v9LVT4W8sPfrLP3wbW/i1dNxomBSAJlyJLfJd7FcS8sW9HYm0SolQInKp9sboxOhIR0m6iDKDieDO/OCh0ZHBjvp0LeVEEs5p1o6G9Cwq9yUqTfmuoUP5hb0T/YcOp7av707XV8Q7lqSXp5d2LF28bHFHDshlHJl+82fPSsti6QiVRxO+7m3rO+am52hU3a4D/cP58dSu3t5UT+9FK9Z3rUsvTG9c0r1wUQf8a0o3audT63g+LE+avlaazfevFCC+a6ViGA5SRL5WksjtP161es+2W6MnXv+Hl/9x9NX1pe/v3vH52052jNfFqr/X9ZMnlz/wbXL9w74ti//79mWfeCxx3uLHr304f17rrx/f//jJN93/xBc++sZ3/6X3nv+64onrLn7mC21Fv3vLiXUlt+WfWkDe8qdNm7b/cbHywYaqFz64a2Tzls7TD7zzkYYVDX+bmLhm9fI784/OvuHr9x3fGHznzzd//kX18T9/6q872n7X8KFw8qODVz8w+PN9Lyz4/s8/8q/JPzb8mvT++/oLb77+6+87teGuud98/+XXlBzYkv3yn6/49Iv/7zuDJVdcdt4L7/hy+K0/
*/