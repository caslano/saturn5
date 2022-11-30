#ifndef DATE_TIME_TIME_FORMATTING_STREAMS_HPP___
#define DATE_TIME_TIME_FORMATTING_STREAMS_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>

#ifndef BOOST_DATE_TIME_NO_LOCALE

#include <locale>
#include <iomanip>
#include <iostream>
#include <boost/date_time/date_formatting_locales.hpp>
#include <boost/date_time/time_resolution_traits.hpp>

namespace boost {
namespace date_time {


  //! Put a time type into a stream using appropriate facets
  template<class time_duration_type,
           class charT = char>
  class ostream_time_duration_formatter
  {
  public:
    typedef std::basic_ostream<charT> ostream_type;
    typedef typename time_duration_type::fractional_seconds_type fractional_seconds_type;

    //! Put time into an ostream 
    static void duration_put(const time_duration_type& td, 
                             ostream_type& os)
    {
      if(td.is_special()) {
        os << td.get_rep(); 
      }
      else {
        charT fill_char = '0';
        if(td.is_negative()) {
          os << '-';
        }
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.hours()) << ":";
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.minutes()) << ":";
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.seconds());
        fractional_seconds_type frac_sec = 
          absolute_value(td.fractional_seconds());
        if (frac_sec != 0) {
          os  << "." 
              << std::setw(time_duration_type::num_fractional_digits())
              << std::setfill(fill_char)
              << frac_sec;
        }
      } // else
    } // duration_put
  }; //class ostream_time_duration_formatter

  //! Put a time type into a stream using appropriate facets
  template<class time_type,
           class charT = char>
  class ostream_time_formatter
  {
  public:
    typedef std::basic_ostream<charT> ostream_type;
    typedef typename time_type::date_type date_type;
    typedef typename time_type::time_duration_type time_duration_type;
    typedef ostream_time_duration_formatter<time_duration_type, charT> duration_formatter;

    //! Put time into an ostream 
    static void time_put(const time_type& t, 
                         ostream_type& os)
    {
      date_type d = t.date();
      os << d;
      if(!d.is_infinity() && !d.is_not_a_date())
      {
        os << " "; //TODO: fix the separator here.
        duration_formatter::duration_put(t.time_of_day(), os);
      }
      
    } // time_to_ostream    
  }; //class ostream_time_formatter


  //! Put a time period into a stream using appropriate facets
  template<class time_period_type,
           class charT = char>
  class ostream_time_period_formatter
  {
  public:
    typedef std::basic_ostream<charT> ostream_type;
    typedef typename time_period_type::point_type time_type;
    typedef ostream_time_formatter<time_type, charT> time_formatter;

    //! Put time into an ostream 
    static void period_put(const time_period_type& tp, 
                           ostream_type& os)
    {
      os << '['; //TODO: facet or manipulator for periods?
      time_formatter::time_put(tp.begin(), os);
      os << '/'; //TODO: facet or manipulator for periods?
      time_formatter::time_put(tp.last(), os);
      os << ']'; 

    } // period_put

  }; //class ostream_time_period_formatter


  
} } //namespace date_time

#endif //BOOST_DATE_TIME_NO_LOCALE

#endif

/* time_formatting_streams.hpp
bCTBQHJu1viaRB9CmPdO2JPPkOyw77RRuZp6z71YiPV8tsr6+cfNb2UZAnfGlMaSEv0JGqMJJg0RlPQIfqv6Vf9icMOn8EEiWlTUfqI9iYLVDvA0wftAA9NWACYP9TaowNIaMqC8vwA3yqrgOMVfqEYJRWyAcLD4dTkYsBpDRDAoxAQkakegT2iEE8buHC/36LWVuO1+IRgPJAbtZlEIopEgOmY1in7U8lu3BcEbwO12cwRjF6nt6ah3ufdmT2rcFVBvb5T2qLGD8o2a97lZYWi9URM6/SfMnUJoi2pMY0LH3QCtmg56uCvhoSbUexEGb/vUBHUlZTn5Jk2HYThEhbpRj1t/iZAzk9TaHPRX6fpAeBAhyGqmKc3UR1kTmv2tNiA5Wcjr9nhCu4RlO4UzBnMldTNkoHDCB0pmaPQrz9GtE6R0/aRsg7UxK1zWJ2RChIKVdhYk2G0W9d+Me7BEy01v/5bHdyV3t/rSZmAQndV9E+yzh3aIMWqr8ithCvEm7l4AwWMZ3CBqLiqsqq2ERA6SBQ784zjplzm7cb6v4dTH+oUwoY1iK8BafmksXQvbb23CZkgdvCJXf1kYA0cEwQGFWhEhWWCo9eBVUUGRqLeRwkLg++WShRwvA2uZR7XGq20OrD+18zjh0TDUZrsFla9Id/ULWbt2qC3M7jdJGgy7aEktSvr/UXcFEbDtOgR0O4seo+CkVBCRlARJqVKNPFDZoFHSUuwvX+qK8Vq3Q/UJGh/IRNthXV7CEpJtp3yGLedDG65xaIM1DjFUozJH3XploHFEVBrHUOOC7dFYsIopF5TFlfd70Yaf3OLq/Nk+mRaH9eXAo0QUCkDNDfwIHtVtwfoZH/sglMCsCjRMdMjanIdknOKgxOKSR7Y7f0LGeQ1LMC55KPGh7ssnjb3/yLzs3p9bCm0fgf78DURzQSwY+vNnF7Tfdz5NKwWxSPZOTmrt/YdXuXI+Ka6SUhDf/q7/CBGvie/5nD/S0XSwVZLNaUQNIbx7h4yMxoQV7MqBI3RlXLta625FsFkp5SuqxhRZKTLfdSlRifhJSkbALqV4EkjhQE1mcFGyiM3XQF36sNvc6WjEreyQrnv2e9f26ZC6zph2GLKEdL8Bw48W27a0YoJ5XsidTGJ03PZgNGxyMM73OQh1//T5gvlRKbD3GTU0bfvYvnfnhtm9TTJNpdRQaGwCzn3blLyH3/T1KQzP+UtkZGJiuyMN4L/AxyMnxDARUtDvPlihwrdXKJI5ySdjfdvztDEPRZJYEtjhsPRBMlWWhoQR5eNYMMUxkks0EeTXtmDpz2XEW/dlGyq8IWRphUscQuzS+OvJ3M5WD0HAgAJjLgoWavTwpAtpHDBmtckFhhoT1M9ofXtXTPjF8P4cjxY1QsnG5RUjfQ4Y5zMuicB6CCYubldCTGjjXF8xLdNQZTHPRqRMGPNryi/4+IUp08sVL0JPCGFCzm4jcfleqHunxhTGMHkQHvuo9O6za1UOhjHGYU2RGM9UHS7cLUhxrq5ubSlMDKCMz+OQeguwVh4orTtSNhwJxuTIxoFVV5i7rY7YvnI5qtua7CG3KhFHxeKz2OOVxQm4iT2uRLCU7mKPKwWifxNDHIndz/s8rlHEYRuTUm7FDGHF41kwaezDijtnTlwhpHg86ewTOcQP129iHwbcuOBOpfG4uyX8YJ7GMRCsmSdwCQLePamB3HbPHrdC7iN0K6cbQJDyT1AImLiF8Fk7hshWbML7PhZ25Xye3AWyVgqGfIn4jHJJZZZd99k5JFQ2CDDCTVFq34WVdnaXywf5FN0HrAD2yxi3ffK9xdDSRvK+TSRCZOnKhs0NysAOzRgHGqmwwaGNAu3MR/yC6pgXLzu7UNQGbTYGlkQ1hnLXElP769jsOz4ddbEM2A1W1WJk5ZbU2Mph2V+1tfJ/tBEw0e2IuGeeubgWVShNDwNncYI/BaeojxLTKKJMuVTA0MSCgpp1HGU8sgAznlWwEidd3hA0gi2cmTKb6cTEOIwACyz0027MZNgdKUS/6mTO2F0bA3fv3ahvnHvCCWVza4W+osDE+tyW5pnLHLm41MjUIz5UUT1P0IyXboQ3X5Qw0I6I4Kgc9g5glCNkYxyBOMIVJstmGXir4L9EyEy7BD7xQhL6DhvfKuNrn5Xoo0Wwsrt+WEl7E8G2yjjaU4kCq2mB0uTNOdLokWuEWmJC931g7yX/FP6QkECHFaYsHGPFp/4cIJhCmJCX6RhGJMYZNzMJ0x8jsfMlUFZaPFJDCj+/xNrCAjtjbUlg3Lui4teyIuHBjhJtRnr7+ptph4xV0al7+rzto19hxa40xi1/d7ZzV7Mvbv5DP6fWyQk9mppX/2jczKgf2PKGdwOJftQ6L5WOAMsHJIDb6gHNe/BKMdQno7Bv3mN91hcZ50jrbxXVTVGKeCOSgg2uajaNFCKfcEmUiDK3HKzKZA3k8Dt/d2LIturIePL4PEJ85IO3AAi0YbamifocKyOEv+dmg2KZtZ9wY/c9sEClf3cYn8o2VBiGtX+C5acR4oo+6kzR6YvQtdtOeGWYcWQDZawIJW7DCxJ2iZggpzKgphJ2V3ZGGFaHiLXzm0HQfCHuz0t47DJWJ2hRWp9OCIcggjL1aq6Y+BS/5aP5CZzOSO6CvnPGrukRxBhs3y6I/BhaH2Y3SiJ3g+PtFLsWLzzrcZz5MAkcL2ZoyhtZ2ThixxrxPPzq6a3GX7QENQw2HwV4FVqPeQlagaw/V4SLzwX58rMAXzzyTNhaS1x4tvwgWDel8FPLsN81OL5BvjkGEG9XsFsxbA+uNS2aJJuguurlJku+QHRnvAAiqsgeXM9tEpzdkLn7HmWd6ryZF/iaW6/jdh3C/NcMgYZHUOLyV6+2n/gSwrZegdAQG3z0aCXjWXUFgJYywmgre2z0PcdXe8d3JTOnAXB+C55vZaaW+/ht2jlRCewxD3cQlL3DVm2cJXVmM1iHfcPn/tBgGXaM0K/ZCRwyMblOxX3Gyy1atED7HJxpbg+SD0MNiS8Q/HkIyhsw+GgguBNOh+UwrY2ZvJCcHGV0apbF8fkyzRbYcJ4HD6RH4FTkT79ino4U2hVM0ko5vIbAoDl5qGYCX/2wSmU5dYky0C1FEQdLc5bdU2nxCufEAQjlMPX5He420XIc/uw7r1wnnQKZGF1RyhONETeL9U9ExHQveFDGWuXFRsVyeKCoiX4eObr87sCec5mxgoSmrshSwzXQqDRTeO/oHUOZJKcz/IAQg1WnYr8f++tYowpMhwEiJSt5zB08fiD3nC9xVPLc354jLYk0N6BJKH/OWjRrYa8RYe4Eozjcz9NjZyrP0UM8IrPxtHLzpeGoY5CwHPiJlNK33//YcaFplYvNS9x8eUv7q2eKzJs+YekGye8Q77eERN6B+4cTsJNfiLW5zQMimQ8enHQtLf9948CgwMxs2vMGJC7350EW4QJJs/eCFIRbL5hCuVvXWucud8cdTrTqPoZlLy2JUb6BhlDftNqkXxUdOkthE2la0pClhaK8B09ZZP+1UkUhZi2mxtgkJku04XroVxPq9TS4h4gPb7PWfyz/dAPTS3JTcP0kDHNa9BBdRpDokUk1nmiFWb21nLySybCuwTFxe53jGXP5KF4pcn9t3Vj3LqzOipyV46lLPx7YBs3oXlQr0smH5oYkw0I90PeTkZfYoQewffl39DrVGBr/MoAJP5xZDhKTVvsblJwmcar0grCu+vLwxK+LDcp0+F6dVA5dlspc+nlLV0gxYIzfy07NpFxndJgksk/rfZBECp/Qo39TzJY5ZOCIrYRKj/tr6+u09VJXCfdKNsoTlFbKNxYbob5GSqgKKfjeuHoym7e52ZHa0Hh26IeXdtX9JQ4TZzgBHTEVu9ulMuplqbj6WVYYc1gyGXfnVcrlSiFQVSPmndPTLN4i9CKhrrw5DTBts/LGMRI0CSNqFb84t6qMrrgubL4uI3TMMbTeCP20HJOwmn2GfWlArlfVuv6vPlnyKL+cZ03vPsL96LgIg4fuYl8MUfctPxz79zk+voF/aYGeg4ZB7ZoaXvmV+WP6lx7yB3ouzWaDNftz/43r/KfCL160YEoBJu42ZmWUDBid9Vf1ZeWwk+WVU6h9Edq99gTmrtQWhoolnL5A3oGpy/oEdXvqdDhY8G4+lrrQ4eCi60Ty1hc41rPU6eDPikiQOdhV3/jPRf7a9SaHliMKIpy7+tkTVm/uAFPt9ZWJO1mIPFoOA0YIrqtlOyE49rciVFvPYGr29mE4JCu7+cRFULdCyATLjM3OlWiiCTE13UClIGYX9HZHJmfH16LxtAvhZlMCajWl4/7cHawhK0oOR15Dd2JIXmuIYSWo2ogEoBmIGTfVMcwflxv8sC/nCJQtIXvCq7Jq+E5GlD8DStFrnDCs3THsIsTYPEIsXfK7s2nlDNDBN9pytuB7OvaedYzhlaR/fxayH+PpQ5/Cmz9SoFQaNsJF0zLg4x+nNWJSWUJ3iauMRPxI3Q3P6E8sFvlz9rdyV8sowsRMQe2wN9sk77/N0/fmd/nPTGHy3xW79wgBcBRh+F7lfLv81PuXdOq3o9fmNPb/YR3OMK6KMqFmEgbVTMLHW/ZXRkJTkQnjr6IAMnHMLnc4Q5ycwG13zBwodQFiC0wk0NdkBbsVnTH1hNWALc4ytAy2jrwm1ML4jsJ2O8G+ljt5rDHHZh4GBKXYyJhvt8LRav0dvsmCijwwAi7DxQ3haN5gFUM0fGGm0GBg/RecSweNv7Dl+JM86Bjow0Obu3pFoYnH6dAib/DbBmW2xMBofs6xSvMp/g5HlsNq5K65AhcplLgGKDvbBAxLvNvHEvokxh+aani4Jw21CZluu4YqsN7T4K29jYvnxkDUIuOmWMEaDzaeFHtUO8k1kr8xsVmImVgidmpI+EmT+ekTDC3hgYsqhjDLwqzd3Ht/B/VDcXw08LlSInwDNU2zExh6SIih6dL314gNARsYBX9k7G73rRnH7s2o4ytKAuNA8fiIlw+W0GTCMIIExmd6wLx3plRX8zTiKHuewhR1zh0IQbBtklD37QplsIvS4d/rdI1xoRkOIMuROiZmYRwiNYlnRb7tkpDaNOhYJV46HMN8OpSx5whSAscRXPPQTi07PlnBSvHfwqnUf8g5KVAUpAF+KPj2E94O4MZbCBTLaMwNZ4OUdu10vqGj4azH+Qkv+dqVLr+NTYgiKhiD86wwC4hGbSoFoqZvUSgpQzr2iBAqSvBcZn0onsdqyknG0e46Mr+/+2nUE9fQtIGza2UCCRXiGQQZW7Hk4yK2Q31hAZNQDT3Bh/EdjbR9mx3xnyBJ0iJnJF4H7KW2yknHmwntNwpdMdI3EKb9myQmd4Q1vZXee93Gau5hgrcKGuIU94fGgMQluRvjnUpTh2a8fZjvfUG+tMpgwSJdZ6VjWFYlaKuqBKZ1RrtboSYRVl0pmy43bzeZdbHBZ7K2FjnPP5vGOEhMGZ3CgDTn56N8pKVHXcszH6izlP7wbtYEPgXdaZiYDqQfNjeaTpSyc0pQ40Ku/ZUkbLRbSwH1TX+cnc2y5RKSK/b9/Dz2IOsWiKiMt1NRbsvpySgzVTFq2zF3C4XTK7Ovr5M09Nq5Itwsh0+WcBGJY4Nd4A/7tgmT+RV/ljDYb4iyrdMEitIc9HTNZkWHH0tUsUUS+pxKgWPxqDmv35qhrImyr8xPHM/QElihGwIrEf3+Kvnhig3YBgWlsNlQOJjCcJ+VQJ/TYL+VoPy84pm5uwaENsjKta+3cNt4HI7UzeBFMM3LDEjUbThI7T5KZnP5cEibKsO4KMduLpITVuz1wrTElrrD5YndvXpP9jYoLn2/dtsZBwmiSAiCq/p+S/vT0oLKaRn2UvlcrzAAwRYiQjTVhfF7mXmEho+5MI+dPBHJhCwMNoxPoR1jhDdmPI2CwK56qf/iTDpDOfqQErMW6QIeiYXj8AuFwR1OQlGwsRN3aR9XjS5dG2Yfp3OclhrrtzCXWLne8/gJHpraW9Q6JSw1kqCxTRcqdCNRLdvhnYbvMq7jG1nJE2nFN0cJEFN8mUjZha8EcvQ6QadZJzRklOH3gGeG4AuFeO8zRjoWBtXcd9pxcz64UFAIcpcJL4y4bl14kipjhaVxlSL53MEwUhcYsBu9D8u1+jBMGAGCgKg79gx3sE2aGz4flyEs4/ghjBg/wOoitGylNA48WgWivHIfxjFaFu6N9VBUMHzl7vwq4LoUqVqvLvpZ6B/36TI2xiCiGlkPF14Y5uMO/WooSpePfgjaDeHF7eUhhCDjBXfEMPM+NMPMA2xpDzeliUIYfnwzg7sR7rTLGFxzBdcGNgzu3UyIUdSQunozgn0qgs3TW2DmNML2GOZfygANXeQTfsA7VQ1P4fcu1EnVLMWm/zhRHe+BcCdjYaZvUJnYKK6MGKO6iBLuiyWwDxU0VyxGJhIboZKrEibsGQHOW0pc/Y4a0K8CcxQUXKUrxS5JASNyFBAqRAE1xHcCO6wVj/G9uMwETNJAeUqI7LIjwm3i43qIvgrNJ1ywTHYOPX6fEkM4PdbIJxegsDu8y5Y4HwMgx4ig5iOyUcqIOhAZrsOG4c19TZkAfzrBHxpycopzLfo8EPLFQAZ14DkWBdSyq09HX13kYz/UjKEwvxObaR5yEeHYcwi21+KLwcQtT8jwzkRHuVD0Rqe33+C4Vux0yM9NK3ASqYDreAJl/HQqNbCTYBVdwBco0ahCBSSIv1KhDcQVnvJ00Z9gwhIMKwHLlKdG/jhdi0D19Lg3QhQ93p+S/Cr0IbTxL+BYIgCOfea44LzBAKpy6ctAe/QfKl3lRJl5Iyw943d7P8Rt2dywFLfnjOUPKnWVumbe1uLk0o0PSkaD96PPLO2I9hcetJMQpBqj0mdUkat+9m/t1eQz0wfPxFJmeWLw55RcyxzoKZTLlF9asrbtGF7CyI6c/qjwOi/kv82Ll9mfkr1Es80llzR2QRm9JPEYrBM4w65mJxXUf7O9XkJwrKx/C+TBrte7Xym/3dUc76aRVoElYdo4YnfnAv/gBUYfxWk8iodEORg8imVFCGjNfByjP+++xMeREXKZT2MwsIxktQuvqDI0gt4+wBdFCvBK8JmULrRebt3Ci75w0Y/7NOF5jMsEkVvuQZNOtjrf3N1qGqdvvEGzwaeJRWxsZimg2JvpGoPMaVmZD8/xG8CCT25GIWNhSB+jF6hibxfCt1h7Yb4iZk/Qhoj3QK/QaZxdhx8xWPo0xq9cINyKIhcM/cwHTGz8wu18hoeOXDa/zoFc+95Pe3j1HzoKlhGH88eERntQAITQYMY0xKW/Hd98wFCaRJh4uWk24+Miu4i9UIj4Pm31YnzMtO1r9e/zMZ+eoVM/Mg3dp7U7uQN0YWuc+s78v4hb+csotbngDcrQpzK9KtRMrs+TrU0xASbL8VEkkrVdermVkT5d8du/9d+m27zxAPc/xh2HMgKtU/7xZlT4GCt01Hc5xdvOFJzPIQz/t365TPMcTy+jPk8c1sa3G0T3m26vae7Wy9sfv0fCu7gS127HuLOwcV6ZqYe2FpQA5mk1N3HFcPFpSnA44J1MrpHDX+1wZ9YIrPriAeu+m5V0L2siyI38D4TkGe7Ebcqz1ZcBNFol
*/