
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_pointer_tag> 
        >
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_pointer,(T,Tag))
    };
  } 
} 

#endif


/* is_member_pointer.hpp
wZoNxqzDdieUB04zKwlBZ7tOEc7l7+iYaxrpSk7D+xX9CDLxh6+2H9vbthuZWwT92n5PFAm6zYVeG+lQ4jfEDzlLiZeeskV//Ch82xO2a2kPObzRos3vfalCtYUFNL+guuy/ZHRGnB6F3CHpGZNouOV6/tyoDl1GpmSv+pZ+f7yBuoAQ0qlezLN6TClZ8wZTqV4Am6kVmDg2gxLjZGBmcJs68l6y4AvtaG4Yzl7HiuGb+kI26PYAr4fFUv6ReNwd/wEHt5qS+KwR9FLSFjqLPvE7QYeh9qGUVgRNops3T7NdUV6UIO1JHgsF9z1bgk1QHUlPHrxlfm/FaJdkCKptDKBse4FbQYVe9xvzvSEG9M3xDN98ag7pzJrGd3wcgYyjGbDxfYP4zEe8ZOQP0nX34gval0HFWZoP2+ZGrsl/sN3zLboDi5F/cCsuS93GfzkqkFWNp3MrvZCy9hi/LOOFj83hmHztJrbsW4akl6IUbbKNaRhnoH/mEXIQqqCFQXPY8vmP8PKTEBfbcgZnkkaT/q+ndGSsB31c+pHMDT7DdMcf8i8+QHp18zGix4ByK5PR2DCSbTrxiLRnn8B/lxXhKRLF/3RexjL18zAq8oX42UP00bWDbv3poyG+Z6jFfykTjGTB2gWSanQKXdTbwramDMe8heaCDP82LRL4lblpmQiaOIfHmarCLbmLibmfpOFdb1iWrhrlXtjNs375UaCMDF9vvR0uf8PZdw0Bxw8qpNOveujMCmcW1roEnVWHBN1hOVrhuZb9i5Ojmd4jmOnbbPp3tJM9/TALs3OtcWlXKt5/MuQJoTrob37F97qvpY17rbjXYxHsdV+Cmvxm2tP/EdvEWillUzF+NkTCbvRkcls7lnxXtsGYP0FqhxNTWXGauj79Ip3sL/jQtYvv8o2m7/mvsWi0ESYf30Mzm5Lg8kSBfY3wJdeMfAjMI51SyqLot6EodJvANNIEfbXu99xHtwVTlRRYmpMhJqtH8ee/FmHp2iB+LaaAdu29Qq95Id2X7MWPEfn4GdYNC80Z1DlpD40wC6fmLdV029MQRabvWWf1A7q55xJbmLyBFuyPZcZ19vg4zQEuSxdDZJIUvke8wb3iGzi7Zj4ubJuM3O4hKFU5w8wSnqIlbB+zet6Mc4bPeecnL7KZPYzHvlLFoMROdnHtUSwLmsGW75WhtCgnfuKbDQzLbMhdazttDvjDPrvdJ/FcX/ZB6ye+tpvRlB+SFOV8nj10VULE7Gj+c+c+2C97yWSHrhL0stQR6W1HUw/P47GWAl1cKg3960tx1mk1D90XTh1vb0C6NJzObG7kXzRryTLkBYxcFtCU2RVMLHg9mVw/ysUkDBBc5M/CqrTp+g4RVpJmQ+MS3WmPcTNqdA6z0IGhZHa+hqb26tL7hkc8zCgMa2Z20Lnl2hhm0Emp6U/goiaH5Y0v4G67lKnVX6OxDZ95Tf1GEpvjzgJPJaJPwJFCNVMp2HoSQt8/weD0Nbi01RXheU8x5FQ/Gcsch9j2C4hV/8OOh32los7X7PizdKgs7cG4tlZ4SAh4CFegP0letP+8IuI9unnAqKkUdfsOPhTsRq/sVLbr0hLM0FsCl/fvqBt3EPVbHrmHv+DUgasUoJHCtI6J07WlS5iGWi7iP04i+3MxdN/+DTnczoaJfjd9OGRCA/w8T8q3ICMTNQzfp0uynPi7FdJkULefZvSvR9dxNfy84oParn0IDrNB2e2jvFv1LNqm93PlVDmkubZQ5eS7VPS3iZ3VPk0GK0S5hYozxp5T49kkhV6J12zlor0YU2BJKtMFeun6crZi8zrKW7iG/1zpgQn1dfh81pzk6/NJtMYbuUrf2J7AbdA=
*/