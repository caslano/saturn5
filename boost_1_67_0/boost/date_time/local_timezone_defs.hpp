#ifndef DATE_TIME_LOCAL_TIMEZONE_DEFS_HPP__
#define DATE_TIME_LOCAL_TIMEZONE_DEFS_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include "boost/date_time/dst_rules.hpp"

namespace boost {
  namespace date_time {

    // Configurations for common dst rules cases:
    // See http://www.wharton.co.uk/Support/sup_dst.htm for more
    // information on how various locales use dst rules

    //! Specification for daylight savings start rules in US
    /*! This class is used to configure dst_calc_engine template typically
        as follows:
        @code
          using namespace boost::gregorian;
          using namespace boost::posix_time;
          typedef us_dst_trait<date> us_dst_traits;
          typedef boost::date_time::dst_calc_engine<date, time_duration, 
                                                    us_dst_traits>  
                                                    us_dst_calc;
          //calculate the 2002 transition day of USA April 7 2002
          date dst_start = us_dst_calc::local_dst_start_day(2002); 

          //calculate the 2002 transition day of USA Oct 27 2002
          date dst_end = us_dst_calc::local_dst_end_day(2002); 
                                                    
          //check if a local time is in dst or not -- posible answers
          //are yes, no, invalid time label, ambiguous
          ptime t(...some time...);  
          if (us_dst::local_is_dst(t.date(), t.time_of_day()) 
              == boost::date_time::is_not_in_dst) 
          {

          }

        @endcode
        This generates a type suitable for the calculation of dst 
        transitions for the United States.  Of course other templates
        can be used for other locales.

    */

     template<class date_type>
     struct us_dst_trait
     {
       typedef typename date_type::day_of_week_type day_of_week_type;
       typedef typename date_type::month_type month_type;
       typedef typename date_type::year_type year_type;
       typedef date_time::nth_kday_of_month<date_type> start_rule_functor;
       typedef date_time::first_kday_of_month<date_type> end_rule_functor;
       typedef date_time::first_kday_of_month<date_type> start_rule_functor_pre2007;
       typedef date_time::last_kday_of_month<date_type> end_rule_functor_pre2007;
       static day_of_week_type start_day(year_type) {return Sunday;}
       static month_type start_month(year_type y) 
       {
         if (y < 2007) return Apr;
         return Mar;
       }
       static day_of_week_type end_day(year_type) {return Sunday;}
       static month_type end_month(year_type y) 
       {
         if (y < 2007) return Oct;
         return Nov;
       }
       static date_type local_dst_start_day(year_type year)
       {
         if (year < 2007) {
           start_rule_functor_pre2007 start1(start_day(year), 
                                             start_month(year));
           return start1.get_date(year);
         }
         start_rule_functor start(start_rule_functor::second,
                                  start_day(year), 
                                  start_month(year));
         return start.get_date(year);
          
       }
       static date_type local_dst_end_day(year_type year)
       {
         if (year < 2007) {
           end_rule_functor_pre2007 end_rule(end_day(year), 
                                             end_month(year));
           return end_rule.get_date(year);
         }
         end_rule_functor end(end_day(year), 
                              end_month(year));
         return end.get_date(year);      
       }
       static int dst_start_offset_minutes() { return 120;}
       static int dst_end_offset_minutes() { return 120; }
       static int dst_shift_length_minutes() { return 60; }
     };

    //!Rules for daylight savings start in the EU (Last Sun in Mar)
    /*!These amount to the following:
      - Start of dst day is last Sunday in March
      - End day of dst is last Sunday in Oct
      - Going forward switch time is 2:00 am (offset 120 minutes)
      - Going back switch time is 3:00 am (off set 180 minutes)
      - Shift duration is one hour (60 minutes)
    */
    template<class date_type>
    struct eu_dst_trait
    {
      typedef typename date_type::day_of_week_type day_of_week_type;
      typedef typename date_type::month_type month_type;
      typedef typename date_type::year_type year_type;
      typedef date_time::last_kday_of_month<date_type> start_rule_functor;
      typedef date_time::last_kday_of_month<date_type> end_rule_functor;
      static day_of_week_type start_day(year_type) {return Sunday;}
      static month_type start_month(year_type) {return Mar;}
      static day_of_week_type end_day(year_type) {return Sunday;}
      static month_type end_month(year_type) {return Oct;}
      static int dst_start_offset_minutes() { return 120;}
      static int dst_end_offset_minutes() { return 180; }
      static int dst_shift_length_minutes() { return 60; }
      static date_type local_dst_start_day(year_type year)
      {
        start_rule_functor start(start_day(year), 
                                 start_month(year));
        return start.get_date(year);      
      }
      static date_type local_dst_end_day(year_type year)
      {
        end_rule_functor end(end_day(year), 
                             end_month(year));
        return end.get_date(year);      
      }
    };

    //! Alternative dst traits for some parts of the United Kingdom
    /* Several places in the UK use EU start and end rules for the 
       day, but different local conversion times (eg: forward change at 1:00 
       am local and  backward change at 2:00 am dst instead of 2:00am 
       forward and 3:00am back for the EU).
    */
    template<class date_type>
    struct uk_dst_trait : public eu_dst_trait<date_type>
    {
      static int dst_start_offset_minutes() { return 60;}
      static int dst_end_offset_minutes() { return 120; }
      static int dst_shift_length_minutes() { return 60; }
    };

    //Rules for Adelaide Australia
    template<class date_type>
    struct acst_dst_trait
    {
      typedef typename date_type::day_of_week_type day_of_week_type;
      typedef typename date_type::month_type month_type;
      typedef typename date_type::year_type year_type;
      typedef date_time::last_kday_of_month<date_type> start_rule_functor;
      typedef date_time::last_kday_of_month<date_type> end_rule_functor;
      static day_of_week_type start_day(year_type) {return Sunday;}
      static month_type start_month(year_type) {return Oct;}
      static day_of_week_type end_day(year_type) {return Sunday;}
      static month_type end_month(year_type) {return Mar;}
      static int dst_start_offset_minutes() { return 120;}
      static int dst_end_offset_minutes() { return 180; }
      static int dst_shift_length_minutes() { return 60; }
      static date_type local_dst_start_day(year_type year)
      {
        start_rule_functor start(start_day(year), 
                                 start_month(year));
        return start.get_date(year);      
      }
      static date_type local_dst_end_day(year_type year)
      {
        end_rule_functor end(end_day(year), 
                             end_month(year));
        return end.get_date(year);      
      }
    };
    
    




} } //namespace boost::date_time


#endif

/* local_timezone_defs.hpp
dOcT7RezmJf15Smq311zhd/mcvJVUM1ZmqAROjjJnuclxu3R1SpPN4LJ2yemcm17S7ynEqzIYLy2G45JqDl/RYK/71H2PtVQerYHmGxk/KDQLjy4td8IzPwZAGdg3p5D5sS3f37WVMpETdUP++q1/UIeBfM2qEBRv8hPR3AZVYn4KB8tUSA7PWowkmnCx9qcTOgdx+XR1YTokY6TyurPVEkfeETC1YWmRYpvp9zk/OueiE55TV120ushp7hotieSqfYvEsn4ffyyrcuu+BEhoJsP8i2W+Nyz5NBZcllqoGAD4IDvKc1IKGEbf032lWmlyfcjvuLllkMMezJ3+RVH0sQR3QYHEYuqgWWx6j1tcuE29m7L9fa6fN7gtqJjdWr3dWfMNQgemi1a0oNGURJw5t2KLKS0njfORQaPrNuQawzXw2IoCAAEwdi2bdu2bdu2bdu2nRfbtm1zY24O9Q3TY408GAvAJW0s5EZggoOdDcYiwsurhKZPx7Cb10BJDCdVaw46vVoZBAuAjyVGX98+uv4eL5rAM1earFUf/jnl4pTRXQ0s3zeI9RQjlDR4wEqilNUM2vVNx7Zpbrl68QPk3zIR3TQYeoRuUcVmsWTyc/sIVafBFkB4cSdChe/TXExrZz4EuBWGtgivHR9r9bCRMw90gO1UUUqkjQUQIdBaDe8YZY19TpMzyTik+mDeHVN7MyqYnXEkhrU6Pe+6A89b/Ojrh6synWAD+yrfd/fTvwmhbySOR6Em2uZ9aD4NFM8YrhJZ7uYsPbZaciXuAy8NZ5Y4sJHANbMitzHcLfySG61BPqdz/2Ug7R2qAIw/gK7Z/VLmmPhbhByy1kFE4mScyo7coUkPmjkLlys7imBoeZDWuMJv9nRlqjk6i5s6Ett4JC2/6XAiBFX4hi5KoJOxLtZKWsQPSDqJYuaBluONtZ/2Xuk+3sNBcM8MrT2GG7d4oDidOjXeEFtLtFa889SE2e1kubHz9EzZFkoZZxRvULyJ4fiwm51ncTyvZTFF5toTVjZ3qsuu3oxstOkyHPlD9x1bZvwrPsNTENFDFWs3zziYqNbzj53I0/Zb6IjnX7LmB3G9r5FFsQYa+S3xVcbFXaEtKNdxzahTNtOKgHEc5aes/TnqWgWtJRCFuWpvYe/V0xi1xkmYYxgY/2IndkCUVh9Ji2AOwbMMXPG5mS48duvFVSBwhZ3yF5ul5CTl7OWsAK655SL37+xYitmgNpTK+e/Eqd9PSXINQ17IQqSZiM6XRQPHcjoczeXDl68Kfnptba+m1L1e5btz0kNd3sJvHEpfShwYcTfP5+wlA3g3FJLJoBkysoob3r1STARY0Yz4iFuyP+4H99aaZ83sT5L7urVFle1MJUDlnJosP8ruyNAM+Yeqrn+ONb4phbLdDRryKzYoH8abphSfYbVKhsNjDJTlyDNhFtJl3IGkukDGHcMAwMnqzvSKQm2SUKrIYkfR4sE3GxlncQ8XOtn0dsYeQSzuTd6n8KLSo/bT2I/9/ClMs3uJ+trRRQXNTRhDuwisb4RP8Ax1eXsysg40OAlOtVudhhl3lFJtDVNz1ickVPqtV4zt0/TaWvR6TzkNf0Cl0Vab/IggO+59y2BLCvn7Z30wxUh4krJnbQAMgCUtU0wzec3iYJHDLl2dRVQ+vFlCIokj4biX7yuccrYfDBxZ5IBmqD3ld/DZEWv7iSQkRPWHlosw64vmyNPJ2GQMbzlQ9eTazepAUt+7MLECUfcFN1ch3e3ZXZsI+H+u6AP8DIGgzgRPoLOUoub7OiMsZaBbRGm1S9G45CHgH7CyU+LFAf9g9iRGhE1XeWT9zfu6FNcf4yE15AWy75iwMzvJ82dgZr8VX/fbfUB175EfjhB1ps8Kk1lo2pfGX94kbCnUktqoZtkKknLaPO4JJeueaEbwY+ZsYSZqVk31WnLzIwlOPvIoDoCxPMZspgZcFryk+fK0lryh6+57Y03x7ketmIn8D64u5Wn+fdxIuZOxC3gQsJb3FefIMD/cvbX0OdvtxjTyiSakiWL82oWEfQLcygO/HP9LuGThL7O5VijOcXKpu/Eq/UacyX2YGLN0Gv/H9MZlADJBA8KuKjO8IrQUSLLymPMmZFBe4D71DWzp03QcxQ64b+F/RS5k79udlInVYuCXc1qzKhcsAVJpuZ+Uur14xHf8ap3VBvKb9pJMcgTu/RnvvP1z9yuNibBpLjhz5FYUKmILuR6504KMLZ8igTLi0muymZujtthGsmp/Uxh8tFVzV3NG8t8Fe1AzpOdYOiuIcqWH82B+Blgf+3jt1vUaX2CwZ5W+C/EpwZD+Wev4bggfAO5ZV6gjJRDnBLNIVL2hLlD7YaZsEM/OkmMa72bdy0XDCT4hU7e9FBw4c80M1Ed2x+hy0dHHCoQFLzVRvseHF9f1Zbr+1uioJojFTF/9dU9/p3LgNNznp58SBT/7shySgXEVboVoQ/UQhMGWZxgsOGMOYwn6Uj7pqdhcbT0SsyEkRdfIMYqMk49U4CKDVAiYvH0xVh5WygCQVaLOoqOigwXyAJf2jSFjenR2rU3Ht+W4Lppv+mQKN8yY1z96kwz9lpSSklOwdCflYd5GeZegcuN1kjBJkfiXJTuhxL7zSsS6nzen5yoPaF8ZvGCQsGM0njmzcRAyVXBzjG3rsUsiXLtxVTMyYNmiK5uEOWedMniC1qGTzw2ra4AB/XJjiiEea3Q1pFW2En71w1t+gQ2pLBlbYccIL2LW+CZaqIgrqCET8RVVWH0VmY8XSDliycGxq2mQxgLid938moUN0Zjur/B8sBKXcw4S9j23wbjU41AIhpfdrsgCqr1Kiji3oYxiAow2gmVhk804q4hNWHlOBUjEyS5JixOu2Gy5b9vr6mnPHNrwV0TCY7wDRnWOHHassJne3RbN7hS6kkiEAG75iHMoEK6MfqV/LHN8DLScq4BzUwsD5pZNJpPd1O2QEXPKirD2rxz+xgrAleK2q6tSvTZQCrrrFf8lGwa7pgI3bDjpequodh+D/J4lwMrjGalAP/LiCOF7Idf2BIRmCiv104sxAyPOqhB/AlAY9VppXR7vM0+29cPnpWRU0cIWygmwm26zDcdkOX5BK3G8DeCqPndMWO+rweNfBTKNKtOX3VhXgGcfYz5gI5jP65Phz+E85WMB0eWoL4NTyiTbHd2q7pItM6FDY2ToEhUaZ1lb0OULjDqpTkmy3lImGxz7UH4MKkGxXnuIwvovU33Do2jy9282YK79ngXGjvMs0OyuuGzzOmX/o/N0S9YucymUbsKxtz42lsXbwK/v89v76unaizEr7pgUJ+LZNNPpq7vV7zmtiHE+rrv06b7nHFPSr5GuL2H3sy3s1wrCvq6tt3PW7wckPBWP+4VGm+EA8y9l0PdkZiOYc35vLlljBfsxdVs7fv2JX5A//wC2wmOzD4QBL5obmgy0Kt1CxAo7uzbEzCJI8b9RyUXml+KDhgHW3FuW92st/HDnmESHjlr3f/V5cWXDUAbPD5CEqk9dVdVhHUZLSUzgvdCN4Wx+igdrJoHD0zTCiFaJNkBTUBZ/xfpPNn+JCbqTXH5ls8q0fI2T4UDDN9WXwIB6slXiOcMv+T+s0OB8/WlV4rNDY4OioDASea1fkYShwxHccwm4f2+x4FdZFMqqzQ5lsbLLNlYrqJHZwtIANnuJxp8DlsiFoAnuFSUN86NVylgTgiNAzgs5Xug1SyZUbihoudaCjJhNDF6XnwbBHhg5eI5cjTK1d7jTz/o+0wrh/JQosKEfWKBor2t1Mz+XZxmqzYEUNQad2I5bjQbUBbUYWjSLiCrEMzR5LlnOlRVOtX0yghpKo1tz1J3syjP6r9LJ+ZN+xtUKc6Y3t0/1LF0zlTlzDuzdUL4aYsQ4otC0qPIQmOSom0SbR8D2Fj1lFw2+TEKiOgNfG9gw2iwPm3iDR0Gr75pd5QtbwdoA7KHE2v5HudtnNZhb/YBswq5dx4louhGF1ShlPtvGzmp3I8EYTVf/HTG99iJkcJJ8C7xSb1LpH6BH2dtNQnVHQxW0kVq9hO2siHHWZSlQfU/CuBO40N2B4ixEP2XREfOujd9aNvXvyLfLmem5kd+Fph+NSR7hb37UCVFCT9xaKjiheNQ01HJOzLDDqv+QCn++0Yh7/HZyyt4XhLMgvycOEjX6PnDw/Pdi04cKKaeEnwKsY0ulVWXinRo7wk4C3CFUTDltC9bIKwEcz7d93HTD4y1ipyBXDFCXU6o8OTrze116ufBSeAwYtdXztq5L/hmYOQdBdQ1DuoXKy5mMdrE5XdGrirWADl4Op0y6abhr9JByRNmnvcGBvSEPzm0UMmbZZY8gR/ELfLJD9N92REXXE1It3bL9x/SC/g+nSzVpUfcngDKS3TfRFw3d9i/48c5zI93hCogDN4qLC4DqXsxHQRIGvufOftq5jlavmBlKqRpnQYUtiq1/mdsyYn3p73llnk++yT04S33WNrDgyiFA/MlEzaF0n7R4wXXN6SQ2aV0Jki5z9gZ4B7/3Kmm8smPWHZfUs9eOBAdsc/pj6F7mVyt0EQL4w7Wcaim9utD+mUKhhfzxitqQo6J5p060Jcs+whQIToGsiD4bvES+6dr5pjKKT+lsKV+uhWxM0HdJkXMhQUb8htKcXL3hzNsm8eWRN1kF5MPaNzqaaQbMwIY+OGc8qPeZvJN5IgGuCEHsKBJ+7PR1Bkh0I+iYOehaiVFNwMkkmCueU9LaoXLtgzi7QwJhZQbPEejbP8rgJF2phATbcYg5xfhVoEu9ykIw2jsB+nQO3Iq7kegi0I5qpdPE5J31Q6vqcVK84YjTzxWJm2MXYV2sXRF2RyD5G7Jw4rWwuhZqcHjorQ8XW5Cxegp8MiPiurP0/uf9STSZIBUkYuaV7thv0iyxJpEeZsc6vBslECHo83tJH7mZBGcK7V12X6Js+zVq6yq/AhjdHNxKvyy/Qx/f8I7PFOKC7NL/7lzP1gB1pdFopSHhRh38rX9QnwgaeTyIxOTOpAK022kjH3ZPSNjbykuqmvz6rs7xzVCgAS5YrIQtrlSH8AroAXGbfIslXDNfnC9CeOcNSCHnS/aWYcKU95xOdHDqWoUdujCc186lTm8sRiqw99sHEELp36kCamOS1wW0gnbDWGRuBk1Nu4GcwsCsajbst1Lm61FwKYyKT26nPIoq5xgs/mXkLUOqhVllHSjT0MW32ywzfMP/h3m1S4meDww74YqFd1RwOFTTYNmxusqIKiTNogVRY9SlsP/qyn9rdZT+7YHsPNyhYUVJSKz6wivTMhbTu9AqTd0ulteW+pal1+9bQiSyLHM6fnYxd4hgRDP+Lvuftis4sr2PBoPvHU0TxXMEtJphAVb3mDdRXIcxS+PaWikhtLhi4fytXuQyVN7sgvq0yHwPCeBEs2hEIiCdNmP6JaA+XH6YEfq+BH/DcaDsQFirqHmixNTvMNRqXag4uM6Q/sxKOXXVkSD3m981ZnBRybsKmaN7SvAVo9XNrqaq8Jmb9b4W7EVea7EpHSSlfcbanYD4/iHTf64ZF2oc54SPdTsTAbg8skkMQ0wSNzCleXdM46FA4s2kj2z9W6doL1W/fb32MUhGXrr4yBatueqNVuh4ChWYThphL31ZSIZLfSDd4eadQ4TzacY2htkvuwqCVADnNKjrbWVUnKAaZmKX0YeHNl8J4450NTEjCzmOpJwS70kU7cM5Amm2HcJN1P9uwaRivgoSDrOzW4+gFJyba8e9n/bw6P0hQObnEGEaRWoJa/aUoQ2DQN0aqUwqFD9Wo22UYfDQOynR8Z6CGueZabdwVJzGEHZbwaLYYQAJo40JxK+EzpR7fGGVQicdJ8XUfNP7sYCYXl2m4lAgahrFTtWon2wWj3BGhBEx+yRYTJSTjtbHS87oNuaosGch4xzsXcpCbabKNBwM+Kk3RpkpQnutAAMs/NNdJdmXf6NIqjqo7kelKS+gqJg5OluwnVoR83W2WdxMvX0F6V4za60cPwqYz3YlUsDUJ/GHv0ZKyBb07aeeritQMifpM8kivpU7muZgQ1raIYv1dL1qEVDsjTXoNq8Cbgho1ZDsPYJAVb+KT2xS2/K5z6oLEX1WsApNxVeb4GMUOHIEMkvzEDh4lQ7m55Cp8L6zWdWsZqK6phViCotzVuIwmy3kF+A0UL5FG95Q1a5LXM1KX66hBegPbC9wZXnvIGsAagLc9B1zH7ueTLLj7Arg86mN5YcnBcJqA1jPsgBZG2GayeIlR7V8ybsBmtpm2Q9qRn6qQ7dJRlN6dSaM1RH1Bpmn9OIUPKFXh3j4RhFtsW5WI3fvgsHAozx7pTSjdDc4RiCvrax4YGs4EaEF3w+ApN5nhVD5v7X9A1UMgVw7USG7j+xx5eHNMDP9vaW3n7ShF0j6gYRuCK4s2R6YI8ldTAaRaBBlzLhkQwLKnzbcBNMg0xb9K+mH44zls00yqd/IvSIMGYrnQsOymSGC6MoRp1PJWKvGlmHApalgjVyJeIO6zfRNUjDP4b800sVkQmAQhACrW0pF408HJrBB3BMTDEsk001PQPbvrHrdQVQBbAPt63cESvD/8TyE+XoQlqkqSeIgrC/ALSq8u0OovEIdDLtcUg7whgjMxFwEJBuucME7MH4USLGeIj/YB4NBUOQ1/zrVdX1HKzvI55TfvDEEi7/mSzu+ZmJO5b3hwxqpzeSZ9MS36TZjhHBSEooYKY6TSs7QeNqKyp22gPgw62gEB9QeledlzfUzFeGFn0jGK2Q9kkMKcI3CEXp70uXgHwzOcaljkjYTEp7y4IR/TUUjIOo7NNYi0I74nzKW0S+HvTEQr0PlecbQUmQ5amfb+2QK45s54ekAaekskB6ZXu4KoHht17j/JjcW0F0N199efGjucH5x6r4kWC9s7p0MNFlQXHNnQtHyYmeWDhv6z/0T6iOtvTeXs1x54TdnWBZcMkyLoO/ZilVzE90R8MkO8Pic4WONnVKsMi1VIby1UXLgzLKZ5QWI+TG/MlWLto9NFvHpW7nGgoQvOnN8VgWY0OkGv+go/Q4/35QS2jWDhsigtg7rR06r6YPs4Swc6PF672JToKaQ1Xo9iGoDADAukFXsqf3PbTFzTlunFKBxmia41hLdMgLjIBbzcpPSlzmptNxitxfuQ3X4NNfMHn3AdapZxllegFtGqPEh4CF+7XbaljrLLUoeSwCd/h/yStv8fr0d88FHhzRQdHqHCCD2ypEMvAoZOdf5btFMnbiN29CeHgIh4FD89+toMkssf11w7cywTpz1BEn2ehtjTVoeH4Z2/TzuIhBcvCB8YgBF7m7wDqM2HHoTS7InXKH0k2VGfJIQMVZz1TSIw6nTlqSqIPAL9m2ygJjmZN8vjxw1Mxn57JEmWWIVltqyRrJFfpDmgWd9c+Kzw/lSfUdsZMp5vK6jcHCADquU4JBrKIB4l6uLdehXZwkmOjpVItcX9vWc0X+ZneoN3EP3FJzUN1szQ/5F94Bcv1gAiLT/JqK3mzunRni3TPj0ce00U1WJ4uvGYYuxKARlzHjpsILYFMhHi3KzcC6fnYZC1MofWv+bmtmzKAJycI/JmWkBdDKyLGj8Tygmwz8M3N5RZFg/4+lrjc4LcFJhXvomfsaB/D3XXHADArjogu2XEhA09lW2kghyPXwToDfkkOekBBKXXsD5bOs3v9UJlyBbD6JXT09CCw9UzmTabdQVwjh6JOUs2WLMUyDmc5TJ+N8741wpjVY56XdJNUjMZSh+7oxBI4D/P9VaYPM6Ei4nLVyHorozQmJHYQ/eZEft/0SIqIkYqy6MMLfPCG2Db9RlFiJQXScxHKIijEWk6dp2xogtJvz8BOtdaNJJ1DDxjDP+gfbJcoGnWXpkPc2eDyeW3Qt1geCcB1qKY3a9AX3SGP6XbrmAFv4SNCm4x1C99OYYxcBsC+XHzLq3Ot7hkYwn6h8/enbgPVMnhSsg2X9xemzEIs0ZLB8QmpAVtBtU6b2RK3QHDocBQV0j5WuWyX/1aLzA8fseUN0tMFPPyVaa33rq4pdGOteVJYG93A9fO4HuKBGR/GTocSWX7v2vsk+7g55gx8YQ3HQy5gyvPfGqe3GI2VMtIhfvmy9ou6gQyC14bunDebNcNmajkofhXi56Rt9uhSePZ0iIGl+KgAAS9R00jhN9NDJB+ZzChpebL40+TOAa8lcjsTpo7uikb0h3POmGrfgNSpG+mA56nUtokzsMw0boOciU7OZAicQoJSUJofwxwlpqYR93hsiu8d/Oaqr5SG+c26tiFS13wGQTiC0EPYKAlnGkyo+s+OQbALsanYvJcmWOHoyv7rCWCd50v5tUInyePlW/MwgljyrdDT4a2u7EzGkm4RaO6AGoc9MXRTzdGjAvoc3xT7ARIMDVP1mGHdhnhg7CX0J4xsOeT6m6PKK93QIiLthxomfTbcgCRPwV0BXxLL7aWABfmQ9XqrZldeGGs5LD0w4mqnCCflcGZxI/vUIgJ9wTFpkv9h3izkyxmuJRMKWNzrBgfTmyksOsLeIF/3c3CIyQXJz/fOFpb6nGz3LoN0Mly5O9G9jZEtDlc3pjzlZ0/l3z+UbT7wdzBoavvW9dL3uM7n7QlwJT6rnR6Drrnd/a2ap6ne/zkH+IR9ChUpKpy2F6Mf7aV2zSneKW4fmhHOssTvDan6eEUNXyGJDJgzC8m4zsojnh4iC8F9m4qkcz+uq2ONaOeZtTv8+NUKoPXLYO6kprgJ236TbiXaECwFwmTkVU+omweo0vipjvMCi5TUbkOxK3hqqSLH15aQ4mU6pI9eMsnEEriz8RJFGIRjjr6VUhQLyaK5I+JczkH//4CF8tH4i2bLl4Vj63Wc5c4Fkm82IU2qCy8QoglXsqg13bd2n8S5UcCAOkrmkUlYlhnbWyKrIBODrfkbW6i6jG8Ubnep8PlrlOW90FGlQWGlvTlmF20X6JJgIfrmj6L0sf1Z/D3bVhfsXVTPlEHNMo/RJcR4Im0W/z5ojdrO4ISm69tyukLsh/gcJKYLIeWoxAGVA3Z6hZ7dA/k0sJTXPrw2+NencnqDqH8Wg567/u+V3J1yTx8QJ+/4UhbhnubZVOadDQ7uSB/vZQL6lYaRQk4jkFpB29ql8Xa2Fopvh1hWEOj4A39FxNmxv9dzt6Mt+Io+d9MyqKe6s=
*/