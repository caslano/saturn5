#ifndef GREG_WEEKDAY_HPP___
#define GREG_WEEKDAY_HPP___

/* Copyright (c) 2002,2003,2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/constrained_value.hpp>
#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace gregorian {

  //bring enum values into the namespace
  using date_time::Sunday;
  using date_time::Monday;
  using date_time::Tuesday;
  using date_time::Wednesday;
  using date_time::Thursday;
  using date_time::Friday;
  using date_time::Saturday;


  //! Exception that flags that a weekday number is incorrect
  struct BOOST_SYMBOL_VISIBLE bad_weekday : public std::out_of_range
  {
    bad_weekday() : std::out_of_range(std::string("Weekday is out of range 0..6")) {}
  };
  typedef CV::simple_exception_policy<unsigned short, 0, 6, bad_weekday> greg_weekday_policies;
  typedef CV::constrained_value<greg_weekday_policies> greg_weekday_rep;


  //! Represent a day within a week (range 0==Sun to 6==Sat)
  class BOOST_SYMBOL_VISIBLE greg_weekday : public greg_weekday_rep {
  public:
    typedef boost::date_time::weekdays weekday_enum;
    BOOST_CXX14_CONSTEXPR greg_weekday(value_type day_of_week_num) :
      greg_weekday_rep(day_of_week_num)
    {}

    BOOST_CXX14_CONSTEXPR value_type as_number() const {return value_;}
    BOOST_CXX14_CONSTEXPR weekday_enum as_enum() const {return static_cast<weekday_enum>(value_);}

    //! Return a 3 digit english string of the day of week (eg: Sun)
    const char* as_short_string() const
    {
      static const char* const short_weekday_names[]
        = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

      return short_weekday_names[value_];
    }

    //! Return a point to a long english string representing day of week
    const char* as_long_string() const
    {
      static const char* const long_weekday_names[]
        = {"Sunday","Monday","Tuesday","Wednesday", "Thursday", "Friday", "Saturday"};

      return long_weekday_names[value_];
    }


#ifndef BOOST_NO_STD_WSTRING

    //! Return a 3 digit english wchar_t string of the day of week (eg: Sun)
    const wchar_t* as_short_wstring() const
    {
      static const wchar_t* const w_short_weekday_names[]={L"Sun", L"Mon", L"Tue",
                                                           L"Wed", L"Thu", L"Fri", L"Sat"};
      return w_short_weekday_names[value_];
    }

    //! Return a point to a long english wchar_t string representing day of week
    const wchar_t* as_long_wstring()  const
    {
      static const wchar_t* const w_long_weekday_names[]= {L"Sunday",L"Monday",L"Tuesday",
                                                           L"Wednesday", L"Thursday",
                                                           L"Friday", L"Saturday"};
      return w_long_weekday_names[value_];
    }

#endif // BOOST_NO_STD_WSTRING


  };



} } //namespace gregorian



#endif

/* greg_weekday.hpp
uhhsTI3aKjoXVuTZPjAv+tOZCZvPw6ULAOARQQlHCxsg7QfgDaHd20331LwAD4BcLdHpzHGLgPfqnQvcOQpyA+IxyUEV57qq4HixD6ciAGVHLQ1nhfe5vujOvL/bJ3z7ePUXue4PaC0yo8NfcJt0AzEjwlUAEAguMAmd3Pj0m2DlHcGfC8QQgWnNhPO5wtl3CRhm7VnZQSCK5Fa6EhnG4tOo7MmgmZExnCBRDPw7ibbu7qhcfzhfhX8GzAzL6Wnb+lnfLwe5cm+9FIBZO8aozAd0vkq1+JUGh+8ACtaJmoKTugiVyw4QIxKPeYs7TJVk/Vaal99Qpp8n7/+eVr6kTaDrblVrt4G3qVpjO/cWNGFMl/cXdBhf7WAEyMuuz04jiLYSUlXyNcrOTDwdo7J18qwLj2GbvVC4lMlZYNuaPCNvn2YTUvMvzKKOfut1bJ+P3GW+5cKlPeFx9taR44Vc9HAeDy+ULp+Dm1khs/H0HoZ/zAas2e1Ba5BrF0MmDOLbwTUNc22eXTQ0C9tmbdvYaXMhXuE1oIrl62ERNz4holikB5b3z6IKZjxgmuEYZGe0I7YVk2+4qhieEDCPrbB5LayDc/7LGPS/In0brhXOvWNz4WDC3SGWBIdoPkLmF3zMbeAyIqzOnv0MhR4HDwNv4ukMRVLUDtNlf53YvkJ6dNn/hrArFHf/BtMWwCm2+cKn1GY9CwzrVhLqV8qaPMcUKupFAvx02D3zU1+CF7sKh0UUPMQmFjZvBBHQzHw2uocng4UK1R8URed9lLBa3wdgkT/BO6/JzMafbPJlbYK2L+RpD4JkkIx0CT2CPEDLi+HLWYFTNc/8bgTuy0kqLbL7+wcG/RLCvocOUeP+1DfZhUecf+IjrbZcySB0Ae4+YfuDQ3MMjfs7B3XJivSlid/swBp6p0hkR6XgUSIV/6s24x93peA+tkf5eu/KXObiSIk9slj8tjc7CwtYx0Lex+g1GHvh+N3iUGUhwHOQvxnwSzwPjSUy6vUtoS1kwcYHeDYPmNJhw7U6NMwDjhofdt9EYj0qvjD96LiMEbUSsX72lathEqcdaGkcU3Rh85mBE0ymDxZWGpLF6bn7YMjHGv872yVIbW1bTU2oDmDk4Jw+gejZVrWRSU2LDU7M0A5zkEZ5RMy8L/IhSYNIPvjLTBmM69vCxV3ewv4Yxel7EP7w5ST9bnsyF8a/zQd11y9WrZP+1rO58GtRoFmj9X7mtHZmBpiSGAokb8ZlzPK0GMRPAaBU8AK8Ri9h2c4URmFKFHk2OqlrnoZItBdf1wV1Io5NGxJV1J/AHvy6/Zs+4wOSzm2LJ7dOXG7ENyk1crQPDkhfOKC921ATksMqePM5Xu2TUXVCVNsYjLp1rJ1bb3zkWw+nvCRWVO81VYKyfRLeLVkCgfX4uDJgRbJ38S4LhpePr6O6kpZAYGkdR/yP7PvydRkM4ohGg6EtrgFPjgkKyKscKB8bJi9MjEIm8h7kZtIoGXcpM6uzEq6YqMk8KTU6qar8mkDPdUJ30TiZYIvBNh+pQdXcWnUumu1R2tnrjYWMWTHrDnvv4IBUL8lFPrJlMo4iDrLFQn5F9xA+tVng2frmcCYKD4SkHpaXl5g4m66KAbNTpv74KMoRE8tD/GoU7gZH0NAzE8RVCt2VpjVYhhIhJ9z1TpZ2zGOav+s4qqa2NYC81EY+6rA2bQuKL+gFa2mjWNBhIar45NC0VJJr0W/V4HhbbkGAoq/EzYccB/ZurIP7vEXLY7gD1gdkwPmjOIH20Gf31ANbEsAO0Qj20jbE2IUgiJLUxHXq1s8oFGTDxJQa0MuxIlYd4sdvDRiznyVpNTJuKcBDNBUds/fWvR2Geet11hokB1Gz2/ga5n8ObboSmhpoktajchFsDSep3cpq8RpMSC4N5mgWuw+V3wV5LDVCep8M8kmES6dlExf18XETWv9Bd+qCciZiX1ryXDhajLYIQP3cjXYyJiXe8nLOf4ssp8/9A87O9YjLWqOkdJpfaEiJp9uQuvWl4xKocRo8DdouglFwDC7bsOF6W7slkm14MuiQULQvAsrmb1K5z9v3qf2OapxkzBwIIs1JtM37jjUIuCG4vXH6YiVXtU8yjXwpZWrbQxeEwrhXsw5+joTuFbZ3kevsJLOAl5LduN62R0b4CW27aaKmvhtApqDta90PpXWPTZKa6w7oWe8MqXB1LhNINzQaPwv9UdPvOgY5dGRgqXfMr2yhYmB7578fbPisV38BeuGKDRtSnL46UFLTEiRHV4LwOgUQfisCET4iKiTvgO+JTWlS4lnzQu3xjRKhfGa4eocfNQ148jxdDodAC33KcFHoD27mdVqu7+cdfhC9XW8CA8YlnIESJWwC0LhXUh23hUOKN1748Lgygsd0a4LneSlNHKLL/suE0EKnE5/CYCkffJxSQRSJO45MWxjSjnpiLbwhShNkyZ2BnQSe/i+EQu6TyaPTzdR4dHhIAJx0xHEaRmE6UVxbSedgMMFiR5+KnRrC14OGlhq27djdPzZoCZ+eSTggisGdzaQccG2Bk49WDMwXFP2I7G4v22QcaKTRSJsnnWsLzr01+ybJB7Bwin3kc+BTVU+xctxc9CXeCGYwerr9MUXO4V3AKHPDV3iMNMPj5Q21kmwOufQ1AmfNJejSZNKv/ZZ+Eb2D3Ylrg4x0FuMZkUzUjNFlM6TKq65lBRJQYP+OgAi9kH9Indv7H3nEaaD8MRhSmi/uldZQz/dZ0xpn8WcvBjTP5mXXNdr+ekv4tp0p1Y0BxtiOHwoHVKE0uVq2OyquFwO4BBj7U+mTsS5mXMub9N/eWbreQtMI+NEBGXU/1Ic4/PQqf200A8cDFgOmK316UTfN+nuZ6lBCU39XhzPO8KWPZCqxGXZTl2sv/x/oOUUcxG2HJjT8rZ0cCVSlpGEIJUO+qJQE2RPZv3dkG3HoJFgJEmbAWq7KYbsu0YUzE2zNBO5YBlRhAq/FEt+GN+hIb7anz0aNHh8sZsfl5K+dlnM6JtthEfNwKrR+ozeRCs1J4/Peh37IEG4y5bLgbbhXdDfPFZ5AYCHBfJ0Q+eUarPgXWDvZOTF/IFes9IRY28ZuO6y7WcI9wGiM7UgSwAa8thfx6TcoxAjXuOS3VN8Ctp6BplYbDpb1+Yw8PuRhwNvkWdRJI7IrlJoPxqi+BNK8eJ72tw6dJByt8nWAD3wSy8ByqoiC0J7KJle7O2T7VpVWDrcNxaNYt072A2huPhvWQ6ny3TdNNs0jzPUQmLzWjYj7e6wkTSf/EseqQgeZNXae6T7COkNlKBe8CQaMwqy+WUtOGdREuxNY6Hc9mX0mrGkcdC3S0IKTyOfUueB1xzrsFz7q3m7ntDTZF632rmvQjv1tUDtsuuekB3/Qi8jOeUUZV/by0q9E+CBkkpcP0UO2RNBWZxX0YC5cJm1oerRHjsBxenb+M56dnXym42E6ERxTPz2u23qNuTsizY0iuOiRadq8F+FM5IveMCnAj1OQAdkNwWgIQRQEsj1CEwWh3S8wUOthxKBQtC69VTZhsi+JOxS2I/A3nnntYjuqLsvGgRm6n2fMMtLiU4LzEIWN/4aKxtpwtrMTMAH8+9jvwGj3HuxWfeTWt4/GiOqeK0YDMaUXgkla9zaLPfyflnQd4Zy5bvM7pgxYKgXTpKwvmTsOhqdOLE5ZGQfvK7vKc4J1AQVPrYXAjAXMT2rAKDYLQW6joN5p1aA+EdKAT0aiX8mhclI+t9qdpfBIyLxrSFBhd2VdFsTNIOYqxgt87BLezJ8wXaS/rwbJy3YY+abL7NSWB9Mw6sUPieHwXD4AGsvof9PM4o5FTqh+0F/wU96Tep7rryz7sEXTJcEbFTN5/+rs5g4hn4eCDfVM1jC/JJXQLxbB+wLAKt8USysUPEkcMlg9ylBjH1zKTa3JK1wBUpajEnuqrmLRXO7IhQrqtOvyyV5FAvjWsygzOd2kYEEwtP3Jh5QXiugvZZIcZNGz2Yx9dG/v40VhF0sbys1pNMYC4TQvpJFt6RkVSp2FZ6BjERgW0rfbKgVkjMSptHkrsR+9sJKuqKGvKKNmXbw6bDK1sit97V1Un7enm1Aws8hwH4mjVjCJm2BuHoNtUg087qnzWccIaZmjGYtBGomzQpq+s3aci1594XCc3l1p8S+65/n4fjs6FSkxk+xmfb0nh469dIfQOsydl2E0XXTjwfa+APMsNKWlyjP/F0VWt6/6KnQ8hjSVimQ170RdtDsMe0znmFomZ4vqRlFaqPll8TmMvRSqSxEN0ocsjKvkoI/ALtaxMPUSxdT0ulGw9pVB9puASSe5ENWidzPWcQeRJNmzUTqZ7eJmSv4FHj5hnpJ0mRD+HHQ2TpFwanlhBbyETIfSzBFbDrr4U0IOPn7VyuMhbeNfJrLl1shLiOu7NPdeM0bIjG0lkqmZ+6haWGU4g6NCabGCTiROJKzCiuloiKx2l1qWs4fXHFySepjV22oV6XUUgQ5k/sn2jwIn+R5vxh7Zg6grcHB+nA5XPRbb3jYw+lfeJO3BXIatLl5n82RlW9t8Vbf89tta4cjxiqd/QAy9ZMDE+8xxNIX0gt6Jw3Nqk5ozV94WuBjBHFUUjQn3csJbHWV9ZiQFIx7PKaNbSf4AwV7jEpMfBMgPePiePnUUjIbekzuW3yNGEqUz4+MxjOkN71fnxgYII6Cgg7pCJe06Wn+bj6Bf2lsbcQAsZm278kjTIbtXI1n7JMs7+CUakfrNITjDEPc0CJ3XpUq1kxMy2FML350ItuGcVX/hK8i1rIwBmxFirAWVVUj66dcTH9E2iJUnPe4ycd7vI6papuOk3lm3QjvFype0TxdLz/NF148QFxReypVYRzZQGbxmJWmw+Uw72ZUtgqxX3ds6fIXQHrE/K4Y0yfg45ifXIFoDjGhrhUAs40lPVBaP5kYU26RA9LDfO6NMoXpeQMfFiHWe9lFwz368LYyRKU/2ZKfzXLmGZfAAYGjqUrnzDoHpDWYLUE1boSK49bDxRBTDpCgN3Mls7Z6U7jFz3TZeaKOZ36vAbfjRZVDL7qvpZ3RbRMtNd4uT8RzNL4K4sqII8UkhS/bxAwRBEQz6CggN/80mU09haHqxF2DS8EGqn+kG0iVpLsNnMMqDGhRSmsYGcHWChVi9Jxr7IXZHPX3JyaJfJ7pdx91p9AMJUjZGrLp6L5iow5dos5eNfn6TVucbJm8BTm3CWyNcalDh9V4fNWyy1mk9Zi9XIkXilp0dkWV09JQ7YeVQflCmn0fc/Ps1vc48nNnkJNg4EU/bzYziShiqzHm5/tu4M+atjhga6U2HvIlMy+clQvTk3zE2goLWptD9BPeJjhFFKjh7cd2HtslQ2z1vHQmN2jEfr9ECFRxHXz+xBppgBfWCtl/KuMIqqAQbe2LpVWm4we+WKvWlS1IKtC47J9SHhJ020RTCmCPwEoUTRRarsJGJXxITuo0pCsoVu+wLr2ETDOPatoo8sZKcfn2IIuSt8QJ+mJ3kFLUJ23KEC4z2iFw2YXqMT2IQPzir+wc7pYAjs9yruYXI7+JxYJbYhrT4zabkhO7625c6Cru6qws1pBZL1SL1dUKBvmZi6uP/pYXb+VAQbT8LRmjwKQh+NRmMJXzDUGi9lAGftk8OKLu1RpvCVFxNlm46zx2eGMCgNDVpGd7UzkFLSkHKlsPGfOnY20pwM3Iw2V+7olbIy2bUYn0ZgJT5em+1KQ9R7W38UzjpEP5QEE1j0rHjPuLO+unjHcH0uc1yyJ+n8bY25xz9csJxes6YVNipmY1LZlbw6negiu5iiijFASh2lYaAAkAA+cLESDecQiOKJHdaAXp+L6S6Godh2XufDnLaw+SDMnNcJJ788DgTOgrr2jtTjfQQpFO6BwQP6Xya4e5qjyWo9NoLow0a/8beYPhvzC3sGRSGk1+m3mKzePI1rSaq/EsCOYNvzghj5Tt65nO2unJwLmdIcogIrKFt5CtEtbg7vbrUwnl3J3DbN2O39AtI9sceo+Mcfa9G558xSPvx9crevlyNkGSeYfIOSnmrAy9c8OExWx7mxjXtHiNsPdabWWJTvT70Z1Wf2+qaqmegvHpACOxtDHG4Alw3qTBOMg1wvS4J0A1qdjS8fllWwNwSnoeMfvAcuGJU8RkEKw7yPjK8n4D2WyGN+/dNhigWLsFF6XETDAA5x7XvTFSisEhcFP9zN/UcZvR4uR51ADNfxKXqDJ6gXnf0rBL0CaSjIBNrHcpOD/R5VMpwWTHtgTsqpHkYwz7t0334fnCM9ZWRhJSLCZJw1g3R8oprMOumnkBiorO1uOzsSgPPh0s89imOPIYWI8QKLRdva4ZCJ2ohs5cp4nA/lXqO9nE5JzSxmubr59BZRoY+/zQ2rug/OInJfwtMWhAlLgHAtxt2dEHX11dtrRgGf9Gyj1uAFf8hG8N07SpecUgabz/4FmnNud4qUMlk+6bnsgh6xV6HSmycrqlhGdQmfbfWproOQs24Gkr17bq+OkEgktpy1iyE8IDNC4AztfPQFwwaklYI5gswwmNR8oec/ty6Of+GMMdWZSkyy7JdxcYGyTWGVBMKLyrZpF4DVbi+a1WRYb1M+U8yUlKkv8klYa6GqVFI+v4NjTbusN5oZLjoByZxvIK9hG+hGmUngYdgSbMuyYgdBrEw2soUy4AMpQF3hys84OL50o4H4pzrnUyleQQ2afVCf1wuiKAlNMDeDJ2wFVtoHIkQ7I7JW8PyrnY2pxpVxqIsUcK5aMbWynUNzNSMiir0YD5dkTBxQQjYmSrfxcm60+OvfWzrZMxI0eIwBv4NTiCLTn6wacabOlqb45L7yR7z+nzwT5H7DmxOxB0hHlxHdZHrafv1+A9GTdCrBVktDV+9Vqduv9fT0W3CJ9RzbwlUI2NuVZldOa6Tuh7mq5zUUR0fYRwzLUJK8RzwuU4g/AMR3Hx3v0IVI0iiZ5kcpUfmYPDMIia+Sgk233AU0OXUNbpvfTRMORLfW3vdcAvjgCannx3USo+6HKLbzoqStoz2hUroRw/uP4ZILh+QzWPElNnsiJITkdZStNyXAnzxAmWYbjItRAImFPWmg7jmVc9g2nGJcqrT3MaIOF+Gp+Eynh5jAr4wjcq3uX6M9DCDc7632dS59RqN9axtbEEoi5P5adQlPC1iQwk9QBYv8yKlXBLCUh23TGIkjTwUaBg4xeAnS8TPOhsSHij2Ex28I3r6Igb2NYLg5VLHqVFHfEjacyGpu0PdO7u4kvQa93YSRsJSm0tko/PyG0Ez8OOU6TusGdmde8WDZXt/AkUy7H+n2urIO9z1RhRc/N461BEDvzReE4rPT29sl4O8zliSsYbdj40I6Myq/FPr7c8gGINLNL8fDiT2hLWjS2YtqZjHs8hhMDAzt72eCR5xYi84PbMPQkmqA81r+rQnBrwXJwfhI46lwrTL3eqPL+yiOvtmY0NNJAkJchEpXOB5IlR/j8zYzQFJZebhO3t/g/dSeehPdTd75QYquZtX9bWEG6YcIeUgTdO+zYDYXUnycPBBJT+KvCTDFxqq0xtpgbQJOzsbHU3b3l8/9ke2l9QwaLWzPa3bntzMwSS1Fi/zQrEno3qY6YPuD79pHSj2UNhgUg3DXOR6
*/