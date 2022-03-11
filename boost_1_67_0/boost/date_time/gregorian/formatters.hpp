#ifndef GREGORIAN_FORMATTERS_HPP___
#define GREGORIAN_FORMATTERS_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/compiler_config.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"
#if defined(BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS)
#include "boost/date_time/date_formatting_limited.hpp"
#else
#include "boost/date_time/date_formatting.hpp"
#endif
#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/date_format_simple.hpp"

/* NOTE: "to_*_string" code for older compilers, ones that define 
 * BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS, is located in 
 * formatters_limited.hpp
 */

namespace boost {
namespace gregorian {

  // wrapper function for to_simple_(w)string(date)
  template<class charT>
  inline 
  std::basic_string<charT> to_simple_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d);
  }
  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date& d) {
    return to_simple_string_type<char>(d);
  }


  // wrapper function for to_simple_(w)string(date_period)
  template<class charT>
  inline std::basic_string<charT> to_simple_string_type(const date_period& d) {
    typedef std::basic_string<charT> string_type;
    charT b = '[', m = '/', e=']';

    string_type d1(date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d.begin()));
    string_type d2(date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d.last()));
    return string_type(b + d1 + m + d2 + e);
  }
  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date_period& d) {
    return to_simple_string_type<char>(d);
  }

  // wrapper function for to_iso_(w)string(date_period)
  template<class charT>
  inline std::basic_string<charT> to_iso_string_type(const date_period& d) {
    charT sep = '/';
    std::basic_string<charT> s(date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d.begin()));
    return s + sep + date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d.last());
  }
  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date_period& d) {
    return to_iso_string_type<char>(d);
  }


  // wrapper function for to_iso_extended_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_iso_extended_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::iso_extended_format<charT>,charT>::date_to_string(d);
  }
  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::string to_iso_extended_string(const date& d) {
    return to_iso_extended_string_type<char>(d);
  }

  // wrapper function for to_iso_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_iso_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d);
  }
  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date& d) {
    return to_iso_string_type<char>(d);
  }

  
  

  // wrapper function for to_sql_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_sql_string_type(const date& d) 
  {
    date::ymd_type ymd = d.year_month_day();
    std::basic_ostringstream<charT> ss;
    ss << ymd.year << "-"
       << std::setw(2) << std::setfill(ss.widen('0')) 
       << ymd.month.as_number() //solves problem with gcc 3.1 hanging
       << "-"
       << std::setw(2) << std::setfill(ss.widen('0')) 
       << ymd.day;
    return ss.str();
  }
  inline std::string to_sql_string(const date& d) {
    return to_sql_string_type<char>(d);
  }


#if !defined(BOOST_NO_STD_WSTRING)
  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::wstring to_simple_wstring(const date_period& d) {
    return to_simple_string_type<wchar_t>(d);
  }
  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::wstring to_simple_wstring(const date& d) {
    return to_simple_string_type<wchar_t>(d);
  }
  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_wstring(const date_period& d) {
    return to_iso_string_type<wchar_t>(d);
  }
  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_extended_wstring(const date& d) {
    return to_iso_extended_string_type<wchar_t>(d);
  }
  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_wstring(const date& d) {
    return to_iso_string_type<wchar_t>(d);
  }
  inline std::wstring to_sql_wstring(const date& d) {
    return to_sql_string_type<wchar_t>(d);
  }
#endif // BOOST_NO_STD_WSTRING

} } //namespace gregorian


#endif


/* formatters.hpp
uy95csb/WYo/Mq9RfItYxFsInFmXcgo3A+Ofvsqr+3i/F0zilnvepSbhvWpKrMkkxQ9ty063biYO4hO9M7heYWy3ev8nlZHb1XjexSgONksBYbNvF+Ltfvb4Ix5CTFbsDOv0guPXeSR90LPxgifEG8WXwNCa8f27sRwKps/1f5/LumyONRzj6M0zwd8c7Du8uyTPzqk4zSeIJEuPqUowxYFIhBEgjQSiPDXz8Lhu8M3Vv8aAqHSn0FyJc0OQIKXHxyNy6R6jN+x+WV/pHM2vQD41lkaUHpjDE5IZke1jJk6j1BVFM/UAKSZ4z67kJtzrkP7uagWAWGUi4NBCELgsHj/bnS2/JPEnVAAM8pB9JtM1CJE/mAaQYiwIF+pr/9syMtFwBOHfEHzNs2cENXvRPnT6iH+UORWRTgxwrmXRkC/fEISJUNRTKgvcyns1zlhwCYiSeFuCfS2F0XLjdQyBlU6FwvGIKpL2vIugmPQX+MR4OnFkd21MBnD2lMVJoOMYdKzs4iPzNKSmdzeED7KWw9+hs1c+RNMNrGXNyE5ygP8XoVMUH7/nPZ76pR1XYprbWyf1ngBvLPTJ+BvvJRDF1pRFN1HoPxix7dMwXdekLFHXf02w9AGSjURGIsZtquBS4PgTwMCEzWj1bi8mgutlMADKRcZ5tUg9DJDnTZhIkJYzqn/uDbBM6R30SjDpAWR0kFpH9G+D90r8O/AyJEGaFYBIv66bYeldiuAUXFeVYDjfVzGfWzJxF9w1OzcA4srfbC+wBc9OcAPzohZhWQZiYDKDX48KrkSujZgNS6CAi6EPIZdzKH1QlzCFm/bozoz/iAFEWkFz3f7VuItsmwpJhd8L14UI/91wAxxGWVUzOOTyjZ3IOt0UnA9VXNji2TTuSwwA95NOGQesyvVtPIPCSIlbsnB4gQ7QUXSsv8lNBIjYTujuv8FKd+6Z31drA0fwCGY9WXQFjJHDrhaE0EQbqGLUYJlK+Y2gLEwMBFX4BikA083hRKfFTo0PdjHgM2ESPqoX9pbKcQvTvOL+JVv0f1MigrXerieEeOAsENfMv0FCHJc7m2GTgFozMXofOvRRFDmPNWn8VgwBL+09JWff2xV38V18ETKvUrt7HncOpqivKyY4Oae9QC1U8A+SQ50BbD+j/0H1u9ORjM20p+jD8qPQsCYbACK7fs5oDpXHJhyBBeYGPzHalxvx4VRikBoCHWwgsBx7MENbSzayqlSMkYxwm8urG+A3D+yl7wAKBEY6XfXRdcWnbI2aU6qNo3q2DIxQsG47K1YN9Xo3U+o2FqmfWimQ6HwbhFaD06pp2zR4i9d5yKbq+p3VxUQyTJhPlZkW+JbAQ+NtbuAjaMTnIcYNdT15UrICf6/h7fynlst3+Hs6lPTObq3bT9FZp+FTP6gG3DldWGdNoe7ayHcMUjWA0UdehQVo7OQ0o3VEnehIjdJKFWR8NwOLotJ1e0iptwg+WqLNjW4Fx3dSutkTAaq5gL5yqkIwxwkWhRbmDWfUxh+gPXR534c1icrmSGTl8qhFRBt31wIVwuPJ6QoBi8Q+FT6P5m6a/myH5qYAwBb/5ML6q4U0oiJPqmRfSzGYhuk80QpOUWU4Ta6uEapCfFhnQP26NvIePZIK+0h5CXjvRkah+jbLr63DWJ8WFuY9lR8mEEaY93YHOwvx9CGoogJFo5IDvOV7vAO+qJXG6c5MlElp8uIXCK/LdJi7G6KJEsUpHwzFqnsxuSt5+1LCP0i3IFB9+IEcDCcr1jtNcWW+MEiSqhhm1uTM11IfkTOALjZLpRSdps3mjnwyP8Jl5E/FQQu32PffpmlELC23pCfzbX6egja9/qYMVWXGJmlRQTiktAzA+MnTrVYf2eIu651VbYEIFwVGGw9vMvQhXX8XK+8Y3EpogHt5tRlFhbeq7kWnHzrwVFOA0XuQAQRYGjUAACz/03GNBkqyF/qQsc3GZMc95ZFNUztX/a6qvOdIgJsCtkfDSfSiUr+bLRIvkm5FUhU5YcdCtMNnTJvbonz6SsxXecwymwpyXfQp9RN5rNM+EvbJF2tR44XNvPliUwHbCaZEvULLNwb0lz9Xp5erexH5po0vazB0N4iRraMxioejuBAbZQhXaWt90TQuR7EE9xLwBUNFmTG4d4HDKV4KyqjFRdiQQVAJ+kM3kGDvakD2UZ5wCkoMB05dUGWX41xihkiAYbyFJw0K/hXoSgcGv/ZIJujugNupc2Jk+AERB6pACdFMUIQb/+JqfYpOhMIztblC/H0Mp6VLgNm/lWmKANGpV4CTKCc6SjlRXW1dBmTPQqu5tqOHtWCC5tYMAroVFPs53QpHVoY3AYMj8zfhdnzPQ+Rub0RkEEC2xkSx1KI1vHgHZJr9m/vXI0p9d2CSc7D5x7QOyA/tmRa8qqssUrVoJ4AjoWJDmVlh00Tjw4YVC2DhE3eXexqWMciAMVgnRwRLBFJzhd0jw9MZ3+Qh3yUkYtWtf5e5jIzD2gzYd0nHRMv91iVnD0ZXFJ2urOi9H7yBnHczylkHKMZL3jOqEY42NchIS/41Zx452maXdQGQcfw/+LNju8cvE6fWTDNOtY0BhwuOqiEZat0z0rCkOrNMaG4ommGKSkY1/RVzIJvEHubY5fiE2tyOtYgdGgaLZve0yUFnWMiDVnXZh3Vf+h5yD1lqB+yeYFYKjfUbvy+IoRt9oWz/YPGIyGDcwUycieci7EddXmxUT8TwINCKp14cBICQg83ksw/32V6Gjg5Wrg44xQoEd+tyPf9Sn5h0ROwGy5GJFTj7ZiIq0n9jlu9vMNssYScYZwyuub6m+yH+gHtMOq14V3vA4W6lyqGuQvT5StNe5Lnk9HOjiTUlgRfL8GkRJRP02DpwZI8beuEwJRuKHLDyaoA1vWrhMFEBkEnCdVqhCfGvAZcCQc3cozYYd+TDvZoVVUhapMI2rvFcakK98XoxMEenOMw5jKCUzeZ+5b5r1/uH0H4jZV44O/ZYTVwxgOzE+0qDc32FoGR4FchnXIkQ01JuACrbY/qtKhpcm8e+e113nCkN576dHrS/aX/ILBTSpzuS+w3VqtpZhUrkmXBrFiJxNeSEunIfSOggQG/Qvzqe0mHmsEa1cKOPOuBnlgXi40bOl2XnSwP37fcfDwppWVKH2ujY7QQ+cEjyu5VBrLLy4m82nkIEvm4rQKHSjBrMfCAqC3j2+jFypsHAl739w6aMJPtZyQxoLBV4Rk1YJbedgIpzWUCKP6xfvZWLDQ8zw6hnAROGZjWLT/UHXO7OqjzLlIcDhFlck1EXJ3N6gGova9Oj/fWCZDOrWfEbCiMVwuHLasmsa1mKbuLoYOwRmRZpnqiZq4apFShh6p301SXrvckpEl6knCPXxtOMK/kOKI9iejuZfSLuA49tetg4rh1j8U83YalvqryrZ9b2NrCOMj6yfutU+ucemVBQKhd0+JjRSEosVQBw1G49bvPhgV9yxgUaVzfjIHcgW2CWVF4FvXLh11UPtlOma2FeECR3s6PhE36Liewho1W9NEHQFDb0pT/guntq+n9Z5JjS4o7IHr8suGT8byX3VVHQehS2GdRzW4a0cXEfEEZMZXv8EB6usT7oPlrqZgyoJg1Y8utC2rv0ZeIEXxt5w5uZV80QZD0B6LiOG0grCxYhNjKvFgDb1jfvSf/Y3qHce9QtHWNbxj8K+5931i1A1h23vHLWdfS7MOyZG8twFvQAeMZqplqzubCAGM9x+twapwZyuI46OCUKbR0WKDU0iuR7x7eFIRmlhzi3dzXSt5t+DKMROwtoHRKF0Ot6S0xtDlQnK9hWZmFeWmG3dfkWZOYCnHq3c7Ay/V2vmUddtIU7xuXe9PIEjumizuqAI1Gz5scvYKwr5DK3AMYsBvZAdhdgxQUcnnhdJu8uWyd/LfShORVB0iFeAUWx+sKbjZpAj5BC/DNNIDzTZxIyK/l+BQXQPVsbMJTCF65tidgkmE3CZNH9s0O/oiuA6qnTuh86Sbrwj35DDm9k+qN8wXWf1KMEYtnS2lPeaISwd+8W956UXpWOc+pFFwCXMFy0z0IydmOes505PTOQQ1ZQBZfUtjvyUfD8w/To1GFnAsYn170sHd13RHtlUndNE6E0n7EJTnUB+bE5/dtike6Cfwop4x5sOLlomyItANfu9pDD8PVjGi7fr2wpYJ5hlw0WgWghsdauHOzXdLoQpbBvxi3HPkfOdKmeDkfw4znJ1Y6qxj5oTYEN7jOVpRDqwSYZggM6RZUyBQQm6yM69wxToDfFwrb34/p5JUg2upCGFBuHkTvSELrgIcSRtDt04GkZFtexqj/Adny3qVrmGOwEZ50bseUgfIx2GyzwXUYoTAUasJAhSfGa9AhVBAcwmKXdYJ8qReGez6u/E8qJeiBs65xHdQMJErulZ6Ucutyqe8L7O8/ba+Rf5isUAgRwceIwYjwuy+w0yIBSG+xoAwVvLzXkH7lgndjqwDhYHmR+AwjYzmykst4DUCzq5wUU8dd6K4zVf0c/Uvp7Dv0tNFMan7AePOCXZ+OAeCf8pSlGr3RcpOPqELpid61HB+z1JYQ6hxEBGV32QROeNvwIKFeMRD+haPKZUo0HeYmk6Ljqg3UcU9fPihfZMu8CZG76m8AC/wb1GNwmSsu2Se0W5LZ/yUDMiBIGdHpkWuzE8b0qanHxwznw2dOiyKvebfcRkgyFBg5C3/AmxrBRCziwc/4mzcgSfpgo9bExDLuBFy/BFWw7RnfsOlMW1DdYPLYIz+jAXfsecMoK3zntpE1Oc/wJ6nnm4S3x/MVT/JcoWRCsTizAPdd20r4jdAnCsTPMWDR44FztLX7q4/rBe39MWYNO7r/Nlne8PkosC3k3zeN2XH/z7gyeksdNqFBUHXUTuBkD2KJcIMJAX26FsxHcI0qAIF397Nj+uNfSVmrR+jG8p1fQLdTqvpHwcQ6rNrspWsuB2R++DqfU1EKxgHAeZosqH2rf0v+ytrPAZo1E1eDvQolbRzpT6kSYYCoM277L99fvVAyV/CC2XVBGk3ubTjjeOLHQA1NG1593liZ3yR2oV2hlQy4CIr/bEmAF24JPzHUUR6wCY2aSGomJxKq2E3gQh0XOOP1YR20eaet/Ho03IPMDKJUgn8I4OFfnoszNude/A/CKttJ4Ub6gGwzKzYbXud1Glf9zhHK/ZdlskQUPpcWOmnTg4PGom3OiOaPmhv7MA64tzYpuQunqDYOxGlL4LBguuZZBvmHEmRtuNsTq7D75hP3po85XBhm9ot69BTVfcp6aXO9MEmGVV+IwDczafwYBVh132zbI9VSB6Rj3B8Oz5dE2rP8R6oJue/JA25uj+jJbcQO4NPxGNSYumzaK8SP/kc2RcP5FrdyLG5PxnjKYNUq4lNwtg0J4ePi8QnsoGUOYZv/20yeOwFhG3xOgJK8N9AEwBxJpLJoLF/7Hy/X8QogXjzRFS8NnlGjMzbex/9/RJmJU48DhbxJUGEeGbMv+AJpC4vBVdCTOOFZVEmT5tQmhfLX1Zp2YQTOsvjRIgM8IF9ADdxZ0XQzJjCr24BKtgWuO9ya6nfTFf0dGZfaGvaWuE0CAbOp+nBMkHeFVdqvQaO66WRDnqACARlrjo/0Ym59CmtBQVlsTWOgjVwqbsqiLB2FqSqxoJdKr+UIfVtcQtYBCa9gNkAjfKU2lQrGJZzN03MO6kd4RPvBIUEQZIAbwoIMyBMdBeg75AS9pYV+izcFNaay8ZRqCMvBVKf5Sx1tEhFm4bx9Qnkf1aT/x1FBFmcegOBv/QY+lqlRh41poLWwbkH4R3f8jWFZnjl6f0SggAzFonA+CgEiH6npWehgjQq8qZcU1NkTfdVMwcg2wAUd3pRqgjnhtzP8vtSY2u2tkHSzj3JCeXE/qmg7+MJJeuvk0LCcecl0+OBLoHa2fIeABiBqnXP+4kQcKA663iBsrhm78wNKgEPjpl9LoVN8+oEi4zJCd0LAO4XouV5k2ooLgFkI0JkCiAtWfDaounnHlGglS3/CU8iAAjr79+wZ3BrGQYnJfNsNAi7+e8gymbr9x8PxttUmXG9s2fUJu123eQx1/D8+qD0TMdZudMqEy+8c1CEOH3Cl1QrnAThW+Sc/sPBCgQBy7zpwyxKKvnm+hP4evLysSdkW/tkfm53LX5vXRSPDnnO8fOKA3uOUcP3LhP2nyn1XI3e8ScTQDsVbQKNHIutkZ6/r+JPMoY+jMJzBNGph15r6eMn6wPIVq3gDWzE1KpYHJ4CDd90n0usRMRRwauhYq+n8Alt8CROEHkK7pZuCh8gv379+CYt3zwUBKoZ0a+oCdnCHTwQQpHf8y5d+MlZYFwia37OOK7jbwmYhgVnzM8gWFKwBJFlqytXn1ELKsWc0lA12toauG1jFiiTyx4SNf3UznTPIpre0Ojf1V19aPhPWeiOL4wmvZhmAyIuda7k5MCIFlRksQzygE55J9NPVs+ckcZfisIj5QbFIU8s165GIyVL8/mDOF1PyPWLUMQ2gVS/1IhkFjunLZJWkHKtssYOb2mto+43CsKqOeeDXWIBbszm6rZV3nqQAixF3mjXI3AdtUMiOuz7scribnK78ggPDhRr3PqVnEhhaJACFTR8j9o6osibOBIhFaSIcY9L/OFAbqteKCTnzjlIZMELCkFAK5LcoBgBxcrqhyN1ZbvQAyG/Zrwwxj02AyPEYubqhCZhcbXK6wnwJejmDDJO5xZA4lhKpgvpkmNliyv+KzAIBy4mOX8ErkIvWuxl7ibpeUATohGZUAXRfVLjL0ZVXQ4ATT1QD/OwuBEelFmwkmJEosjrm9zoUzg1m1/tmWtJlhUIdPM/h3HEbuCNpIDaYpYD2Yjus14o6amUMQWVTu07pOyDUx53ZZeZ387P6s2GPVqkGDVg8l2ZyosmV6o+5hBezQuZrcDV55VbjRTsxf3H/N2niSukgpf6xJVe0Qt7IBu2EUju/nx2ecN5UMRxZtyPyqQg+jGwBo96jjM+BN4Jutc826qwRY2/cZyMF5KoIa5aO+w+IH8pLFunXiLGr6AvUVlQ2UmmwQjH6mqqgCu34qBV0sUOIoViVq4q1U0qWdbltlhwL59DNIxCNVIkaKiC4cy8hWX6akPEdig194xrNb/WxO4/sGMyGP451DnzPnko2qHjbSe0R4tmDPb9Fo4tcQFut6AjIcsaGC8WR/ivYjqY3auf0MzONr27tFchaQHFdGqWrf13JKxc2/2QeIw8YIpMyM7cD+L/95Tw8Kz8jD83nY2M33nRiVBLyXRtJz3yWwWZsFkGsoykdCB+Mub/opElfzuDSLpuRuspGrV6YS3NBVDFw4b5LTTJSU6za4+u5lbk3c79FuEBFXDZXyK5fgOUH7bQ5PXp6xudOoMisbVhMhTc8/STMhz4o+Fk/kgfWTdOVFJMJ9R6RODLWHidEoAtyPFD1EMO1LYwnmPvQh1Ws7dhWJAmJf6xS8KcJvS1Qf5GUyIIFyZx6jHsCAhK90DsSY3X5iZLS+6szwKCm1rwbHDJta6ClGDw+w+4YSyaQq8DIFkQ+1dtFSHrO+5zsvSe0QTmENpdZIoLSOR6frelU+1yiaIJjnv64P2eqiSQyX8XH+40nptQ5Lb2wszkB8dzdHkkByogozdMReZ+gauxP+ef9tn4LePOlFXWxhfT5VhoTOXiGrtLUwt5Npoip38P9soYAhS+oROEzfg0MG29xx5tgYoNv3kQM57QbHg5R0RSnfKLPu+bATNjnLPcyDwrsk0kArLmLHpo+TDAuLqJdau5+Hu1nw2H3rprfg7tgDiBAaQlosNkfqPntVZ6awVLWwF88UHLVgWQUziCagQ1Clr+pvg508jMJZOL6uwHUJ7k4GK0CjF59SqqZd4wTijb+Z5R0jXtjEqz89glC/ea+M3n/Sgp45lZRAry6tSYwK1O33IAwJfMWDyWA6pH6ATpqYuj6BY809ueZ1wKnBqFIt6mr63Le2lkKtNvmDQNRfykOvU2Q/W5p/ECS6TcDio5KBCS4Dfjf+BRO/X26nVo0jKTVtau/Dl+jC32XJIazA91qKAik6mCJdegmmZ5Jt0UepqYQmZ4L1qyLJVpX1yh9aM/j6v8DA22un35Sg1gEkguDfqfezDeFuxCmA+gYYKkISe2dD7hXRtALY1FyD+BhrCu2Nrh25p4IUUWcbmOzVds76kvSPSCPpb6IUJg5Jl/HX8yw1D5wWVwpZQ6shCXrvd8M2L37P50+SDHMtSI2uGuc13Hp1SESp2D2M8UetFnkcjFZBORMArk884WXATg0v1o7rRV+aAmnGfkIXgZin3xHskk9S/StSz9uDu1mknxBr5oaq/d0aJxEl5c6rFmpCkwhU27tdwQPx9+nH0iUljpei+4EhC8t82xzNTRRDZfaU76pJ7L3xlWOvZTeyfFz99jZkGbhaArCC+wa7Oj1Z6wAyMsfWVR5KSm4BjcdsVW6TDh3Fupq4kA5jLgjgsgdnb7ANl/ivigVJHb1Mh3kRMOvV3T1rw8zVJeX9zpAJ4OXet7tupdrYPvefaIqwQm2jKcI5EppyHwNvviieS+aT3uBSjmLXlfk4FvQ57SbBMwjdESYUjPXezXRHjc1Hy7iTbr+Tfks1HLP11dUVMHhbgNhAp4BYioZtNraLuk0PYuj5usisuT7l3id4p3T6cxfo2fmrOLNUsaNHME0ZTxOlTUAzarvYsrrl3lXtDKWxmnx+uX5a0A6iW2azomnXXLdK4myJ+UoaQFodtKSs5R3HYxArAkof9dnMeVX1Bar3sY6pDjD89+/vb4AFAEDgn6A/wX9C/oT+CfsT/ifiT+SfqD/Rf2L+xP6J+xP/J+FP4p+kP8l/Uv6k/kn7k/4n40/mn6w/2X9y/uT+yfuT/6fgT+Gfoj/Ff0r+lP4p+1P+p+JP5Z+qP9V/av7U/qn7U/+n4U/jn6Y/zX9a/rT+afvT/qfjT+efrj/df3r+9P7p+9P/Z+DP4J+hP8N/Rv6M/hn7M/5n4s/kn6k/039m/sz+mfsz/2fhz+KfpT/Lf1b+rP5Z+7P+Z+PP5p+tP9t/dv7s/tn7s//n4M/hn6M/x39O/pz+Oftz/ufiz+Wfqz/Xf27+3P65+3P/5+HP45+nP89/Xv68/nn78/7n48/nn68/339+/gBY/p3/sjd+US0CYGU=
*/