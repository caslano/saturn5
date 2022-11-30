#ifndef GREGORIAN_PARSERS_HPP___
#define GREGORIAN_PARSERS_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/date_parsing.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/parse_format_base.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/find_match.hpp>
#include <string>
#include <iterator>

namespace boost {
namespace gregorian {

  //! Return special_value from string argument
  /*! Return special_value from string argument. If argument is
   * not one of the special value names (defined in names.hpp),
   * return 'not_special' */
  inline
  date_time::special_values
  special_value_from_string(const std::string& s) {
    static const char* const special_value_names[date_time::NumSpecialValues]
      = {"not-a-date-time","-infinity","+infinity","min_date_time",
         "max_date_time","not_special"};

    short i = date_time::find_match(special_value_names,
                                    special_value_names,
                                    date_time::NumSpecialValues,
                                    s);
    if(i >= date_time::NumSpecialValues) { // match not found
      return date_time::not_special;
    }
    else {
      return static_cast<date_time::special_values>(i);
    }
  }

  //! Deprecated: Use from_simple_string
  inline date from_string(const std::string& s) {
    return date_time::parse_date<date>(s);
  }

  //! From delimited date string where with order year-month-day eg: 2002-1-25 or 2003-Jan-25 (full month name is also accepted)
  inline date from_simple_string(const std::string& s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_iso);
  }
  
  //! From delimited date string where with order year-month-day eg: 1-25-2003 or Jan-25-2003 (full month name is also accepted)
  inline date from_us_string(const std::string& s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_us);
  }
  
  //! From delimited date string where with order day-month-year eg: 25-1-2002 or 25-Jan-2003 (full month name is also accepted)
  inline date from_uk_string(const std::string& s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_dmy);
  }
  
  //! From iso type date string where with order year-month-day eg: 20020125
  inline date from_undelimited_string(const std::string& s) {
    return date_time::parse_undelimited_date<date>(s);
  }

  //! From iso type date string where with order year-month-day eg: 20020125
  inline date date_from_iso_string(const std::string& s) {
    return date_time::parse_undelimited_date<date>(s);
  }

#if !(defined(BOOST_NO_STD_ITERATOR_TRAITS))
  //! Stream should hold a date in the form of: 2002-1-25. Month number, abbrev, or name are accepted
  /* Arguments passed in by-value for convertability of char[] 
   * to iterator_type. Calls to from_stream_type are by-reference 
   * since conversion is already done */
  template<class iterator_type>
  inline date from_stream(iterator_type beg, iterator_type end) {
    if(beg == end)
    {
      return date(not_a_date_time);
    }
    typedef typename std::iterator_traits<iterator_type>::value_type value_type;
    return  date_time::from_stream_type<date>(beg, end, value_type());
  }
#endif //BOOST_NO_STD_ITERATOR_TRAITS
  
#if (defined(_MSC_VER) && (_MSC_VER < 1300))
    // This function cannot be compiled with MSVC 6.0 due to internal compiler shorcomings
#else
  //! Function to parse a date_period from a string (eg: [2003-Oct-31/2003-Dec-25])
  inline date_period date_period_from_string(const std::string& s){
    return date_time::from_simple_string_type<date,char>(s);
  }
#  if !defined(BOOST_NO_STD_WSTRING)
  //! Function to parse a date_period from a wstring (eg: [2003-Oct-31/2003-Dec-25])
  inline date_period date_period_from_wstring(const std::wstring& s){
    return date_time::from_simple_string_type<date,wchar_t>(s);
  }
#  endif // BOOST_NO_STD_WSTRING
#endif

} } //namespace gregorian

#endif

/* parsers.hpp
Gz5Y5sZwifXF7F0gH0CCIEi5AjX8KCjpAYpm2/GovzAPB2MeD9YHauwlIpxjwtsFaKQiV69N6p7N/h50UyL+dVFTGwCmEbw5qqU4BlCUCofU/W5SCH0zz1Ddn7uduZQbucgPk6PdePx79knAKK/rv3n4h1LF3flFp5Fqff3SA0S4GFHgCr6Bd8I8hCln3AuLZ7cQYk2UxKc5uccapQTTRDLSKKs1ZtS3FtzvWIBeFRHdPVpny5dxZB8P/YkNjNVSIqcR9+Plwxhd4gBEsoBrehA382L59O2G+qA7vrZwnwmAotSriznrBhhpd6vBXziGfwvt0WkZq/urXElTmsdB1LyiUZf7tYcQqMGCRvIyOsvEMdXgAaoNyQwOVTtFnWbczGunGOuPHnZeP613KqHXWgGJhjf76BzwSfiHkK6VCCX3AFQYAqJGnjZZLHNbObffUKtC2y57+eJ0UJV6Ro5EB04oKQsXS6SmWdhU+3SK9smxV497deQuZ7gXvgwrzvVBll8zzElshXN3onyugOfSMOD+WN8cICEBOMSKsOPFARslwpmIe1aHCveknXEXIj5suuiKEC/oB603ZO9Dg43Lfk9+Vw087mKdvLPtmd3UPDO9vhyZ3Vxn0t14TsWeQLeyhFgvq/Y2TtVfHjMmiCTYqXXfP9Hc8Ph1tcaSBwdcBgbWT1uyZRbFQrzjSsxLe7JaxCv6TrKpMGJ5iYXIkCQDah3E8N7PTDOy3jGI7ev47U0B8hGQ5A5VoIA37ZLzqCNxT8kUNe3PTyJ690U7ZwEEqPcgFkYbq0MnK03fGkuz/Kso55IBGKb3IBVRG+N9YGKSVqIZuw28MN9TwyW1BpHR/Q4JF4X+Wrl/iCXLm27ncxOCvRliFz0rfXZoe4znA+ZT9aIZSgxMiLsjf95a+0kD5YHsWeIBax01FJx9Il+7HheL3bnpD04NB3QRMdgXEZMWtWbkxSvigujaWlfTJZyp2aSChYz6mQFcmm+5fNXioN4hiszmdzTvkdA3+wvyEo6j4+hGU8VxS8jFtx+3PYvXGFWSNrC5+MM/C8pgpWpklSc2y5PpLDzQ9HbxN5uNDrbBwPW7Le6DA/kNQw81AY91jUFFvyPdVYO9Jy/UwXq7iqaxC2UKgECG6cMN3/a8iSy277ctN3/9Y3Jx8klYKi4x31cBuV62afdCfl90P5QH+kmgq0anG+l472BKvkcEth1WIZ9rYrlyHPcvFgfEa2y3y6wtDxGg44Yr5xSkWjdq8slGZ/6atwLpymvzHF13Kawdr/PQu4NGqDU6ufzHlKCTdum5CpGFX6+iq/ckhhKgIUt76mH9zjIyHjZLTw3UFxe2Fr0uRDvqfkSsdqyvIWhUKGDsaWih8ojMaPSrVJC/55X1avkPhVJytHktx6AXkN0OaN4ZWsRCgAESkdp1d2S9lFs8mZz336rsy1g55XYiaWZt+WBu9icri3uYt2m7uWPwOe+IlSjnXMik2rkB8JUEd8IwteqU+4i2KSPNztf16BQur56SL7B8W6i5TYGcXTLvTSc2gs50X0P5TW91fUIz2xw4Biykobj7mMTEOJUHIMElCqW2lqHuuTwArPCvOTlNfTdwSn3sfSQCdAeX6QGEwS/3i8DSevzNPk1BizMSQhK8i3TZC25AYyn0vFyGu3ucDViJYbcbJD4Mgx8ckAkdpT4Px+dXcv4nuz2rOmXMMOTPv6LtLRmP4QX3PS40YQ7rRYyj+YArUD8IOvxPm49FQytLTGEoap1GFxxhGwyCT8XRrlBjVc9YJq1JH/l/guF2RhtMjD3DQkLeU0ruEr4Itdo3BerjbIUvlu97EDqPxR/NjtKxpjA6IkY/spsRelcSVDlcdWLgt2QQG3IMxfleZBKGB+gRjwoRFvPqp/4iBNdeRKw9gpg6ZvI9NA2d1hw0o/K8tChNh//TNAm5AcZ4qV4CpJehcRTRT4sUjlVQipl3ZFDDpMPHgXYW4jHtdxMrwRa/PqonNqQP6xq1JkolxL6B7OWrs0mJZgh9sSVZQdNjK9Nf8+gHazFiCsSW8LQoWmxoFdV0h0cQwb6cpI2pFrtmZ90783Gd/7iK2uD07PB+7bZ8a8D5/eLhzqcwCWL9D7UIi/LA11tZ0dejfiCAbcQQpv7O8MKWulN+8oBv7mEg4Q1GuBL7/61yBe/4nth9N/4Mn4MIOkdoaq3nzMAsbWNksKgmbLLIpgQecleLIMl9VchU6XyxtSJBApZCL62HzEzUzjzWJ9G1BU7h07O9sU89v/YU/66QnRlqM+irpEMqcJ9xIE0KFGV82C0s4EfWqSVm9P4wWO/aCqGnVdQPcbx56gX6t5+xNaB5Put4qd494LH8N/YpJeLJG0hGoq+9n6IXvrH4AdeJ9Hj0/X07Au/z32O3BOAUrEb+hzpZ37vGAlSVv4adlC+MaeFalfa3+P69z63e8BtuFVTrbEs+551pP9YrZ/7abZcRk80pD2BRt0DxVDjhhtXX6TB/1arChFTJY5jPcvDm9CV8qu9mdOXk0RfaAjrM9NIwqCEw4blEW9t5p/agpfqBMWqUYs091w0/H2H/IHxAiVn1jXL84IJyesZV8vSH6lkRMqAjH6ud5DAFnMzs9lHpshz6kF13+3tJvdCNtlEe6tbN8Db/Jk96YfT6X54Hlx9RUDH8xrkGN2WUhXIicJ41c+zc2x539wuIISW5tZd7gGovKNk9ELU7N2Edqtv0zgaSkxOsHGEZMFUcx2dN2WG3qIkxg4o1a5WhTV60PPBb96VQkdzd9/Q1QjOPIhJ66dLHx0YvX10XppQ+nuyAkVtUYRqJWMV71bvnrPXM2D983sdVj62T8yfNEt/kFiNTVKLYfnXGH3z6iD1/yWI41Vz/WENMhvCgGATUmXARZ4kTZa2/ds6cKuM3OTezVbVjvKUEdJLI+TcwfVt948tE8MEkoDYCbr676zofwBPyqqqZI3HbcKds+H1kO2xgMGZkdT1tI1yPBlsBpwnuLX3w0OGOk8FLgkST/SPJ8+cpNSU/8nC5OD1F4Y+xsE1GTs068APgIWEXPhFaolle8K/Lk9Ljmrw+PqQj7bvfrT1JZUSkCFkhsNXad2t7TWJ7ud7mMoGhHWqQ2MjhNsEpLtq320bkq9Yqdl2g2Cxljr6UhfRdoYmRzlVRzfqZ3SF0y4YNv20XNg3QrMYX7kV9VCWyO6TRzpQ1UkrDOIvkTn3pfTU3dtRAVVt4WvbulLG2MiY1w3lXCT/g8pmY5NYVuCmIM2HTGW0YQtR2/bMMPPCZIi/1WP7grDkUCvld6yHv4ftiyhaA5buQegm+BGLEXkvl2QSoet9zs7FoCtZuOrQ0Wgx+F2KtXDfIZw1P8niJRPFAnnh1jDafdYz+7OOJgar0dVfkhs+lfz82QaF4sS6MUu6fy2apTtLMA3c5KcxiJ+P8YdJnNxoqmXNAhH6CQZaAJeORz4ynPStEUd1oxcY2pidNM8MYL3GzWo/o+mDBccXgYFA+L7Rb7UP5zPyhPSLzkgdbIQYcuWmWbD5bKv4H6ARNtED6xHV7w3H+eadCdkQXmTeLBKpJ3ODpTZpZpffpcCnp6aFk/Pd17lQX/W2G8mi5zIUrXi6niEGLmtTVb3ZMUOJu9Za+JmKd71MrZZ4RkkUkbL78ezYmLP84XVpIeORh4cTOBoTGUDBFIo0Bu4YrRTdrQIT2wHDII0trPRtn4dbrexscmK7ytUEIsA0wKMauY+T+nWiPyTHt8s6nmMhN629lV+7VhSUxuI8q7cCLynqvT2we6uMEezB+o4bojpBxXRdqwGpsVQIutyp6ZxoKzu9jdUTsqJpb2cvBi5autTV9Sjxd9bDlLSD4THnOsbsrIqcyeMjITKV/ih83yXNnf20bOged+2L3WgZkYTp4M1SuhXgFn8Q12GM1FtqlqS7V7s7W/ZqMlQu9Y3N+7zSk32DuA9tTKusPhs5xOxOAuPkjiEe4kua0E7od5jHHSdFHujV982qwcxp92mpsyRSMMrrYxR0GkbarWJG9Tpj1jxgD4mNlX3mYtOSdlTL51Glaz2qs13JTWsrb+TXurfztZvNpZovuJyViWXcIi6V5rNraJGUnzxY26g3jyfhNseYJ3uAlHf8iLN6PFS7D9sqNuYA5iGwdwkhNXy2GHReq4XVFL6fCufeLBnxnaKVna555DIjyMgGOFo/KEgYEDGwX+jiYGFyjCcSUJ8+/tO8wunwHHXkKqXqqRQGSQXPOAOdiPX/fCK7kJQibzLiQ1RwML1QrovWeMMLVeSBTAKDRgRAdpnmQSaxHUC4eQhy6ynsw3+4iqB+Hrb5zk3W0NdnfZPIDAn1eVp/ai5bMGAGXr16lEakT2RmainTPuCU5HMhQBwjDYPUNojGB3T4ATyuPLJrqH0JPmo0vsDMRxTpOzHKbTgNdM6g0jvXfgmSKV+DB9rj7xHnvJXmn5qx0jvKkqm0G5n8Zo9niYjK9UoKeU0lCOJfE0BDbbmX4M8t+6LFcGB9tp33leIJlu4RF9pcd1/aQJXf4bGo+Sw5mMmF7q1UQHBTIWbUpD5p+b8dVg9t3q5SvV6r8ebzbXmZcwy7/jqfoMuGtpdT6ygIFPeH7Grm9Tiwyh3KMHaqRuirome6m5U4K4gQTcWDwnT0IrnEMY56EwbzOLHlyGHIYBbKd6RL91MsMPv5MW2A6Eavi7j8Qk2KRXU1vD42JjHgDN7ShsU9NH70NaBHVL85hy/8VJOtKjhBERI+tqoJeUoEy1enJfb/IlgMXXFED/7dtrpv/d8Eb7m+8naeletc0p2zqfAwbBfu4TsYjmTFn3V8HRKSi2x6kU1tfPKSrrfCFu5kiK7m+95p5lN1Pou3WxkEk85tAUMRBPPm2pJxvvcJs6JGiHsA2UgjsO0SHkqVYCYHG0PIp2/FKR0/Dcf/ZW1hvrQMG9geyU/OLcWNKgqZBlBPGJIBkASf2grwy+WpGyzusjkykBFLDdRGxkZXVkr4rpeVNr4uX4u+k1pUj4K3nIixBtNxh6Xc0pNEbaziFoM7ysng3S1ipGlkJmQ39I2G2lYjYZKCpjjwvHs4PHoOvhs66kSkTRryXyOGwtwUmkDLyf+Ln5pSFBtj10uzSv6kBAJRRoz7SRwYVQj9M0HzLyDEgXl3kmI8B8tlSppZqGjOxxA0GuWslfdCFslVfPB18/XkU29UKSpQJlW60NGL7UtBmaQOFsqMdpRkgSkOAp9+g+yBSa9wFcuYc8wZfOpRAYpA/28Mv2R5ZO6EHtasijpH8ifEKrFs/wT6nMKuubNbWl0YivmTMTQn9HXUdx/+UmHDgMVBg2sgFrDG0l9ARQV3HE7bCEuXjUKgk42buqWdqDkLMcrfefo1TWacszyrPVnfLRZqiHMwNGdiigz8KYEVR7OdM6PQ0BPjEvp18HnYTJGSgY8+bFzb7cJMmRYeeO+duxwn5OxKC1q2GWh2KUrC+qqsPg5otZGQ3y5Ya5Dx1FkBERNrShyxHPWAXwRMrxJI6xMhvQnzZkMX8EM1qXDQh8cBqxJB1rZkpXsEAzf51j14sDF84/CSfMem8jB29Ptcqmf1GlZj+jqPqtIz9YaN/SSukslySwGFuBXm8WY2CeUgpbqHCTwSa6laiRYcCHown9I+6lP9GFWCDL6sBcIKJbMmlR+QqxeNaEQLSfg7lnj17LzOALhkw2teKPphhtLEvhHcE4KuppNGZ4WQutFq0E0QsobtKwO7FQ/lmjPwYD9wzZvHCulNSA0f+egb42rK18DxkOV6+OOsXOmOMpmiRebJj+0vf20IpKDpw8TMz9C6yBZQbl3A1V7U+lbzzKqGpPFsFaqBi3kUlxp+ndF3YQpjhePvpIXahbVrR51zeSJ7YZ6xDXMlT54B/c9OLFKLWQ5RSbaKeEDrPGQNrJMKNm/6Pf+owRNGixysL4jpdpTgAxM4SC3hmyuMgcZZO5TdfofOnYd2p0M2z8GAFnzPnUTZFkM3hbe/PLkkYqRtqW5yK/IFeshoFRFKvQUvIdEDJiSkIotFlJCGiwh7BAj/2QukIKZTYF/gjzsug8lCAFV5tz8/bwf86LZR6byZG1cd+ghJ1Gl2eCbQEkFhiLM9j6DbY3r8p3YVK3AccXXHFlYgOqCld4m1wVdch18xDfDcv7TMLHB1zjaYQmFhR3kdCdtd01iA1r+0nBWJFmzq3IvmnuhsFAgjXg6EzEvj84WdX3A77Bh5nuYOowN42wqOXKMfkDbFfOKB8Y0G3Si2iU4w93vZT18YV+9N8jTELh/JN1agYjtrLHaDNqNnr6ZQcp2vS4pGpfdcC5b9XqGdN4pKjpInpL+s3TFstlbpEbobcTRTzUy9ZcM93nP4XiTKnuD+SL5Hkh8La1CbIHtCKXiBH8x19tkrG1DvEAzGq6o8zNPw4mjJZS2cFznYBN/ke+nZwREEyCUD4IYIhO7FlR/QqbxlgEFI+bJjwxH6L0I/m3sRrQHQ1w6YY5Zm8ZO3ZwWncqLmFU42Vh9Ng9TL8FgGLf3fai+nITpec/XjdODUzwkbmIzDYfuRfc7mKaGXRijjhc16Gya9+2Af/HwFBuxu/WCW6eKMSIv1aHTHdhAFzGsB9MpzxPTvFID5Vn7H+h8DY42t02Je5v2R/LoeLxqepgcNzQkLNFg+/ZvbCyAm+DdRTuTemrwJGTHTJWj+P8ICjCb2RuSbq8DGOOV4ApuRW5XOwz0ynP+cmZ2zodWN1yg0k/VR6Wbdwx/jRXpFjsaqA2doAACz/0ypVHNt19z8rrEaLF0Gi+xY9rjJ35ycX8zg7Bw/wwvdPK5VX9YMe40X3Hk12lxEw3xAJFd42SiluH4Fci8yclq5K7gKAlIodEQV4zYxu9CWvEm58EOnOEjEie1Lt0nswOuTNRSWCs1qX9XO8Ml/BJ6dIqhwyGES3YpHYExlvkbQUY8eWM4P73oWfRtYxjqiIsvoSvizjMOrAusLEFtSAN/DmGUXiyx8SPEU5aZPandxwzk7W6cR5BV+DMkCKFOTFT59bzg+PhDOYwaNkJuPesKrjqJPwsCK+zgxn+P6UnjHtOmSHewwgpmA40RuhwOL68JiE4rM0V5r7FXqL/s0H34srpRLO3GEi6UO5qmLwiex+jSy8ywB3xhkCbXsHAEELgs6pnEEe0rK4ccunFJtFfX37i8ZIgmvrIa/c6AHxuvG8K+6XY5WGqmVrbACHcoC1rjhpO+Q7Fsgu7oaRJ88tTGcznRbU+nV55PqHLcMSrhfR/sdKTbFm4CZ5NhBZbBEWp5V99K3omDkvK5n3cQKWQ3fH3lgIODL+Ih5cK8pVmeb8ahyOyVeUHALsjpqWHrg8+ApVS4Aoh8ddjGT0OaKwfNZwjNpUrQ5kaw3wUgz8NH3c1obSfQbFWhQJGdKETtDKkr0lPb+/ce/UDUqEHkRzBLk0K+q5XunuQXe28Bk6eEMNQ0kMOMTU2kBHVxj9x9/vEm0/qJDp3nMwH1uDnF3OzFTmT+WGMFEduvd0vqrOdQsZ4vptFjSshcYR9An7B6ROMcPdDhHV5iCQaIsZYLq3J9jUqQ1de/b6dTuNHF9vg90yKQEmE5VFXjV6Wr/bKHAuNGiCLnfrK61bYxwktTJw9R09/HE8fyTau1HlK2ca
*/