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
hXkTMtWvimvFV6+ehd3H/WU45AGIiY2dXsoSr7u+xMsj2qrzuS1lsyqIsi3RT8y5SNlRQOp/r/MNZX+2NiTHpzzuOnzGlXRbefRK4mlLekXN8NmosFJNrvg9mzeqm3Cbkml8DHD5RHzszLu/Iw0/HgfLYUkxJ6M8OdRW3IEUao1vebSao7CmWPQqWr26L7i8SOsO6kZJ+usxWuWV9Do8kEfNQAhtVQXdlaaQpzeF7pSftSl0tzaFtiNlU0g4B5vC1eW5sVjhKPhoAh/vN18dJbRs+djV/OH0u6/PZfME/XsGfldrE0/b9uEz8100Jhpnk7NxOYsK/Yn3ztYK935L+sPprojQNXOWJ2qIPwMUeIguqJk6bW9DOAZsGtG/dqknzFDx98l1uaS5KV1OQ8nVr7ZFuDyYIi9/HZBGLZ5+D1cJMQKaKQ4cbBtWEG7rQvQUvek7T5tPtb74nTjVK0GmwlQR89l9+/u/gw3qeV79MNpNiJ/Hil8bgd/fNsWC396nzPht/1ac2pUgj4YOAD+rPvCmzxV9YGoLe31gRtPvq7GlX7vPDfqpvk39RDk2eJnZ1xW2WHmN7C38IAMV9fOMv4eBHJVdOPzqWraIT13lcU36OZHvDPHr87c/9LwZap3HpZlCSjAdEDeFPoKt4hn7mGkboQ9VadD6M0kDly7GRt7QM5mOJJ/mMm7o2TGbtZ2zykjbWVZmHEkupWHbxwihsJn2GrY4dhcAJCstQpIVgOoRX2Rjq//ckuy9VzlZPlCbRGNTunyZ7mnZAs9yK+4DykhtSp+ohgIdpWq5GBpHX8YlL2WKHY/OMMqUNKQEG3GSM5Svh2dS+NFqWaFMeeixdaTDCMnKWflXwllFeLoAAbvD0weeIniehrDd8ATgGQjfWoIrAX4s6yY49otvYR/uwz+uTf+5P+OqNGUN4VOO7Pn4RJyMyNYm6ouLtdH8/++2ylslxgm8QnqlZnSEaLztoPFmrqfGy8NVoOpsP/7PDrd1RxwrpKrs94E8Q3y4YLcqj1WBSBb0wMvNvUjfObpL4RAPdtjce7jDaldTh/35Kr3DmmWwWfUQvgcezUU/zeXcT1Nf1GD1f3Ntdhvs7LTLVn7cOEyRH8+u3z/58fWdLD/6a1h+nLGtqfJj6IMmy489C+zlx+KdB0F+tJ0/3/4oYv4s5vuu5onlCLzPElFgg3YENHWs2tmmtUkLsTb5bK1YmyD8ueC/Xsy0dTQXFlX1N5Yobhp1u8i5uhjuGLbAh9N3lDFb2TTBh5vfBzyXNuqveN2Hgh440qj3f/Vy6Y594T3PpUcp9OhHPo4FPeIxzwDQ4+01TI/8IoRHesCiTZpRlCE5WCzVyZEXOoIyouNEQA4zeDh9KlJDHk051VqLY8QIlop3vFLZReRjEgl8dh6tvLig7qTHgmCoEpwjwGyl3c2F4fTKIbmaclHI9b35OFKSPMfz+Kt81GcuA5wHAAXVGFPzN3kk5xaCYZ00svygWhda16OhHcp69KWWjdiPNX1/2tY+b+oOtT+ZF4WFuEwkXisM6ykY5gWGLa5lhuFUg+5B++TB/2JKS0t7XDChi3536IwQOuBDmIABA35MYAhkgBxz0WI9ytiv1nfnmzBq7d96lIyN/rbdvD9fxbtRUlGle/lDkdRQ7MAaNZ/XqCH9gGw+ECT/Np7ygqNpylsxWp/yRJ4KIU8WhEyGdKUvISHZJQ9shS7BNqq7NOxHfQqikJi8OWIAUSMIpx91BXey+iuxLpFl+UVZCbg/t4rLKqXE1NVEV07V81s8VM8vwz6/40V+qAR4RM+vDDZxCVB03DJrtreKbGt5g5igg5Nb4NYyoTNpp0sETy/I5IIZEvc=
*/