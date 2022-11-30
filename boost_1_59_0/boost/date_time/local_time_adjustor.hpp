#ifndef DATE_TIME_LOCAL_TIME_ADJUSTOR_HPP__
#define DATE_TIME_LOCAL_TIME_ADJUSTOR_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

/*! @file local_time_adjustor.hpp
  Time adjustment calculations for local times
*/

#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/date_generators.hpp>
#include <boost/date_time/dst_rules.hpp>
#include <boost/date_time/time_defs.hpp> // boost::date_time::dst_flags
#include <boost/date_time/special_defs.hpp> // not_a_date_time

namespace boost {
  namespace date_time {


    //! Provides a base offset adjustment from utc
    template<class time_duration_type, 
             short hours, unsigned short minutes = 0>
    class utc_adjustment 
    {
    public:
      static time_duration_type local_to_utc_base_offset()
      {
        time_duration_type td(hours,minutes,0);
        return td.invert_sign();
      }
      static time_duration_type utc_to_local_base_offset()
      {
        return time_duration_type(hours,minutes,0);
      }
    };



    //! Allow sliding utc adjustment with fixed dst rules
    template<class time_type, class dst_rules>
    class dynamic_local_time_adjustor : public dst_rules
    {
    public:
      typedef typename time_type::time_duration_type time_duration_type;
      typedef typename time_type::date_type date_type;

      dynamic_local_time_adjustor(time_duration_type utc_offset) :
        utc_offset_(utc_offset)
      {}
      
      //! Presumes local time
      time_duration_type utc_offset(bool is_dst) 
      { 
        if (is_dst) {
          return utc_offset_ + this->dst_offset();
        }
        else {
          return utc_offset_;
        }

      }
    private:
      time_duration_type utc_offset_;

    };



    //! Embed the rules for local time adjustments at compile time
    template<class time_type, class dst_rules, class utc_offset_rules>
    class static_local_time_adjustor: public dst_rules, public utc_offset_rules
    {
    public:
      typedef typename time_type::time_duration_type time_duration_type;
      typedef typename time_type::date_type date_type;

      //! Calculates the offset from a utc time to local based on dst and utc offset
      /*! @param t UTC time to calculate offset to local time
       *  This adjustment depends on the following observations about the
       *  workings of the DST boundary offset.  Since UTC time labels are
       *  monotonically increasing we can determine if a given local time
       *  is in DST or not and therefore adjust the offset appropriately.
       * 
       *  The logic is as follows.  Starting with UTC time use the offset to
       *  create a label for an non-dst adjusted local time.  Then call
       *  dst_rules::local_is_dst with the non adjust local time.  The
       *  results of this function will either unabiguously decide that
       *  the initial local time is in dst or return an illegal or
       *  ambiguous result.  An illegal result only occurs at the end
       *  of dst (where labels are skipped) and indicates that dst has
       *  ended.  An ambiguous result means that we need to recheck by
       *  making a dst adjustment and then rechecking.  If the dst offset
       *  is added to the utc time and the recheck proves non-ambiguous
       *  then we are past the boundary.  If it is still ambiguous then
       *  we are ahead of the boundary and dst is still in effect.
       *
       *  TODO -- check if all dst offsets are positive.  If not then
       *  the algorithm needs to check for this and reverse the 
       *  illegal/ambiguous logic.
       */
      static time_duration_type utc_to_local_offset(const time_type& t)
      {
        //get initial local time guess by applying utc offset
        time_type initial = t + utc_offset_rules::utc_to_local_base_offset();
        time_is_dst_result dst_flag = 
          dst_rules::local_is_dst(initial.date(), initial.time_of_day());
        switch(dst_flag) {
        case is_in_dst:        return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
        case is_not_in_dst:    return utc_offset_rules::utc_to_local_base_offset();
        case invalid_time_label:return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
        case ambiguous: {
          time_type retry = initial + dst_rules::dst_offset();
          dst_flag = dst_rules::local_is_dst(retry.date(), retry.time_of_day());
          //if still ambibuous then the utc time still translates to a dst time
          if (dst_flag == ambiguous) {
            return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
          }
          // we are past the dst boundary
          else {
            return utc_offset_rules::utc_to_local_base_offset();
          }
        }
        }//case
        //TODO  better exception type
        boost::throw_exception(std::out_of_range("Unreachable case"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_duration_type(not_a_date_time)); // should never reach
      }

      //! Get the offset to UTC given a local time
      static time_duration_type local_to_utc_offset(const time_type& t, 
                                                    date_time::dst_flags dst=date_time::calculate) 
      {
        switch (dst) {
        case is_dst:
          return utc_offset_rules::local_to_utc_base_offset() - dst_rules::dst_offset();
        case not_dst:
          return utc_offset_rules::local_to_utc_base_offset();
        case calculate:
          time_is_dst_result res = 
            dst_rules::local_is_dst(t.date(), t.time_of_day());
          switch(res) {
          case is_in_dst:      return utc_offset_rules::local_to_utc_base_offset() - dst_rules::dst_offset();
          case is_not_in_dst:      return utc_offset_rules::local_to_utc_base_offset();
          case ambiguous:          return utc_offset_rules::local_to_utc_base_offset();
          case invalid_time_label: break;
          }
        }
        boost::throw_exception(std::out_of_range("Time label invalid"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_duration_type(not_a_date_time)); // should never reach
      }


    private:

    };

    void dummy_to_prevent_msvc6_ice(); //why ask why?

    //! Template that simplifies the creation of local time calculator 
    /*! Use this template to create the timezone to utc convertors as required.
     * 
     *  This class will also work for other regions that don't use dst and
     *  have a utc offset which is an integral number of hours.
     *
     *  <b>Template Parameters</b>
     *  -time_type  -- Time class to use
     *  -utc_offset -- Number hours local time is adjust from utc
     *  -use_dst -- true (default) if region uses dst, false otherwise
     *  For example:
     *  @code
     *  //eastern timezone is utc-5
     typedef date_time::local_adjustor<ptime, -5, us_dst> us_eastern;
     typedef date_time::local_adjustor<ptime, -6, us_dst> us_central;
     typedef date_time::local_adjustor<ptime, -7, us_dst> us_mountain;
     typedef date_time::local_adjustor<ptime, -8, us_dst> us_pacific;
     typedef date_time::local_adjustor<ptime, -7, no_dst> us_arizona;
     @endcode
      
    */
    template<class time_type, short utc_offset, class dst_rule>
    class local_adjustor
    {
    public:
      typedef typename time_type::time_duration_type time_duration_type;
      typedef typename time_type::date_type date_type;
      typedef static_local_time_adjustor<time_type, 
                                         dst_rule,
                                         utc_adjustment<time_duration_type, 
                                                        utc_offset> > dst_adjustor;
      //! Convert a utc time to local time
      static time_type utc_to_local(const time_type& t)
      {
        time_duration_type td = dst_adjustor::utc_to_local_offset(t);
        return t + td;
      }
      //! Convert a local time to utc
      static time_type local_to_utc(const time_type& t, 
                                    date_time::dst_flags dst=date_time::calculate)
      {
        time_duration_type td = dst_adjustor::local_to_utc_offset(t, dst);
        return t + td;
      }
    };


  } } //namespace date_time



#endif

/* local_time_adjustor.hpp
n4Q46MrASJiUPLwN0S58Dkb5aEA4W9Uxgo4M/wBQ02GHEemjKJTA/D8cpCD0rubwsd9J4SX8oqMIjgS973L2gKSrMfkY1V4Y0PwpSDhXV8PBbUg9+/8m62g5JYKscR004Bwbo/+lyjrJC1hMfPOsKJbsHvCMvAg3LjcfGAWXVXp5+UssXOL+NSktRMk5slEUqWhmmpqGSQufm5KjDKAlnp7uO6D7Pp54OUdq1qHTyq21QpZzRe74BgB23rGieqLIH3W5f1FECy8G979NW/I22qSEwHLydJ8KXRxk7/D8w8X/vg6RKCdC8olqRWUhRbBfs+GWj112J8331w3QpMRD/fVsmKv1S+CYCqsKLN5yfof+7zOmlIh06kpnbcDx+GQjD1tCmx9bllt0Z/Kf8NJ8z9q5FFdb/MF7DiHrjrop+cw2kFhcDqibDeUh1cUXn/m6McVJ5XCN+jmoeSI3cBLauhAEoviJr1KI9cHOkkdCflMD9kdEVwDElD4OA0UYcZmJIcxEhLO48lRhIE+BGsp2/Da2h/BNjeTsHfcQIHFsJ/3ptDh4amv0r8Krf/bKfa2u0vxS+B4bxdjGQa1vPhaSEaH03V6FfzRQBhjxFEJXEIIZc/pAnXc6bm92AL2jB+KuS+Bgw56DyeqLtxlHIcoO3WiacbBp3hpICCbRSbBWOknKItElCCxTZ1gRMah2ygXDkAi+FnrBbcUAPDqnKy1RQ2btQYxGEcG44JDbD1DOg2kjxuwR9pguHcKu1b6ojC3QnwXVlnnEL4yJPHm5OZrB2RhJAyMQiWGGgoGX4AKaQjRZLl3Au0Gh3T09TC9GzMIQP9MYM4gXuCGax104HtvrVEX6284FIdAUbJrHGnbPhF9evV17F+oDVM5RQ9PUWFOVgLzQTwof1MtWiKVEoS+FYIXjgRv6QOxBqmdrVyFq+QtQkM0YmGe5UgnChmHFDgVdcnIJ/BWNSBSXKM4ClDqO/iCokYN8AVPnaTZxBfbeqEfOtyqIXD3GvlOmcCxAKodi9uc78b/Rl3HvR02AHMGJ6PTER42KO9qje3f3LC46efsfL3/1Px4cvQ1i74trBlNrEyPBPKPAXJwBeXHqDFhXXMZeXiWFdbXl+Ch/8/n56+VbwvrjoqFZPzwugAUU+3RYr6QdLvLmxvyT2wzgnbGf0gDYauzA6KN+/XKU0Go9mQ1EKhMUZlDnX8GIyrHUJUXm4//o2YYEk4NW8w2eefoB6BQAuGAm+d8PI94bCQdtDlcnWewr7Ku8njgfIqumo04bjVfsUkUkNvFBYCRSOk+NuPZC9AfwZeS8HPRjU6Cq4lNOBrRCJBD7CRIkTBrTF6HRJBu6qyiyWYdj9XG5t17v4NmK7KmaoaEO4Vpv76sFQ/XLJI9wBybmU6UlQkzjp1TkAT8Y+rpUwCStSS2RgwuUPofgsZyQV8VTWJDDdFBWXBRZlzkigwr8QKWiZRm5aL0ybTw9ivwXn/aNa1syoOfxKSM/K5WlrxUFViUhBYf5kcwUMH+EWiaPxVAxn3sRMKZCIJ9nut6jBOo+UZ5RR/N3yq1WryddlgNvv3GeLxDZHWJVkr7BJ4mTc8GUkpNoo9Qh1E/J6cukF5IO0xAVAjcm9r0Pi4w3GkPR6GXOBtGi0o8NLqKPiuXWGXsVq/kUYgqksW3LBo3Kw86xOBtm4Y2t2z+MkW3xwlVbpdXYwvOQ4OPhGo9i13ypr3ktBM6luic04kpQ3RatpXZCSXWzjxYR0Ph0ZUA+9MuJhhSzbvkNpVOXoIlo/EE+CJ9LesFusd78pktiNUEyZshhAxeejGAa8M+DQf2fwSQ91b4Avr7Bw3WmVfvFdfcMXw+TnKKmgGbsNbVvEwzlNMKuEMVapFg29ETiQQKNhsSXiL2qCB2WWM79+deXFfLL//At7/VAvwEvxoST/dQbxlEJ68e/zp1C8VfMRBx26kAGdS9atxJukSmlFwnTanPhiWPPk3jT6psiTO270xmz0ZNR1AQ3lRQs0efM104hJajmFdW9K8pNWtBT+re6n6mqQ5LWiUsQdjo6tApTLy70og7mWMcbZQaUJ4a8+EAeTxlsfKx/pLUZTsmSuXlSC6jnQ1at48nSwzfOIy8utaf5t2k9VhxB1ALnjna1ZL2qrWpUjIE6Yp1ywJPqGgQiv5X7cqNkEI3MliGKVpNmNSHyoVsRmOIC2y1RnWkunYgxSJ4clsidMU0BF/UDk3Q237seFBKQJz1TCzuUon408JjdRi+7anD1+3SC+uA8NzvATIQiCzocL0En8xqFvNGxnqgr8Q6fj2UucvTPE30RR9zC20BgFCemy5ErI33xaCiQJRCuE5YozgVgCqNCBSUDTgNyUwMbAfRuKUXISeP+vasd1r/1jhniUzY7DK8xGWqbASRVBrskyFp/fvEvuzD3GH3x6P2DkS8KgfEKa6q7PxjBUi/epnug6S1aoQNMeJK7yvFENYOtwWDBrsafzvmg4oUeYAIhduYW+YYwnbDggyAwi2lYggHu0h2VXz5tryswz9KdU+c5BX4RU7Yc+bbyRV98xDB2p++Gn5fVn4u3CK20uRQGmq6Ts43vJmtf2cj+Y9zEy/xwd3jKosvNckoGZcWPUu3j2ZyScGvFBkfvuBpPUcfSnfxHfXLdffC4CRumtHhoq1DH8R5eWtjoaGz4kZNL10sDsd+KovgCBZwQwuDwXoQ4oLWQBZxXCxApiFr2z6qTWIq5JVMwjchuyoJX4In4tILDiVQkJVaDttKU20eYt0c/zr3bI+/WoSKu5KIbdav+EXBqNjhlLcRi09QrU1A/SI8G9fdyXtsNS/66KpC8Iwu/W8ruk/XZWkEe5fZ1Amd5PrWc2ah7GfbksZ8mNSZNFEe3Nj45zmfgOjI7jL6gk7prXQYjoJ07qzHVbiFYpd4hDPQFn31XAk6xGCzQiW/40Crzx040FWBzC0BCPIkLCoqPtQo8ZUrcZS+xj84yK4iY4HYK5R4Zr/lSzZPoAsVVNfQ/W2oZ74voGzN2PcGznOXp6rgy6LKygdEe7VNlfU4MlkYaPEQjBA2jbGLec6uXykhpd/+tDLphdwe3AEefSLZrWgNN/JC8zjtdhdVGsmdpp8LmYa1DCiXmyZSDx1I9lDoOLteD+4lIjZkp1cNQG5hCsPwCLNSt3Lcg2HyDaKNGjzhU2JUXKkzTGCFvsmgVghoCGLTwcV+4eHfsHwr7OxWSsF630G7HrjnULSEAY5Gue++AEOdc+U8VZf8NLvmKnsEXI/Z2VUnE2n27SJtRLEhgkOINfdapLO7VaAPDFAYNAfmNni3dHiLCOTli6JbGm8uRx0WuRZuxPDrrLuVSoHkWyUDOLhldOyNq716HZjdq5DLWOhFUkUDvzhIyPzPS9cnmEdDLoJbWJ4gW0jMdnGZq+dbX+bvh4kJ3/elTDV7+Kd9MD07IHhZ+SgTNgPgZMhC2z6WR0aUqHhwxN8Z6IUAfTGOvJEI3v27ku8PaYXb486ywUEQOldqzPplYHTzuINUFD6CJnlQc5/qwbSALAds/wpH2QAQhL6qxSQq7x6/+CG6XfhBaW47325LgX1hr0evIdeTYJGIsKC7qtrT9cDIBbVNbDaGTzdCmeSP+GqSKY7tumdwYcqiXlydhJJIF2HuZdy7WSJOGh2wZKy0EEjg8Tp2NpOnVhbusaHPXZqblY2ik8vED4k6jUlGNPdqDwTsjE3Uxg9R6adm0rsaM2mbFOXt5DUxHpmufKN42Gzn0KBxrOuytwmgy1ruaFE8+w/nMrtBZMspOeW9HR621af6UNGLFZOdjCube2AQCmFoZrHIgWFTZrYK+r3KFcB8aXr79nhFKtyWLk/I8nniqfHIY+BWpApE3V/RJRnMzqg3Jxo6tYoHjPGFhqDXyax7vNj/3tnMsqaQdvMU31VaYWTuK9gvxK/br5pxRgQlM/oFbx62LwdM3OTE0i0KdDlGsZYpn4F5MjMXr/RRXZHsw7PyHA8eELtV+1AKC4HwRBNh4YIIfVEnmiT7sBfUHqmA4R1xzQmh73LqysloPd1Bd4v1kCrPt7X3AXFxKJSy8/zD68pUYT1nrlZUgZUPsMYjXyoG88JpgT3VZmFf2mPINMzg3XvZYNGUwS5oJTGpRWNAwEt0bp6E72JaQ/pQNmXpUt7r9eZILj5nKwwqiRrC9mTY2OPTOKsamgSC4MgBM6QW0jMUY+Je+MCryIGRRYHZ9SuCJJQ/e1zRkdHHSe5luBmIgf+wf+M3sF0sifEErL8T3RiU7y+Ylnm6DbjymbxV3mJ+qAoISfBjxgg5SlZ/9XhdClpLRi3PPYghDmOm343nofTHWtCaoJltZMes1xOzot7dG+GxIZpzKdH+r6wkGtD04gCGf+hJ6XyUpfbiFKdbd8GBQRQKGbxISavQNsRwaBCUtMYzIv1T+J7SxOj+kely4+RMPU1NL3CTFJrjhqKVl1QGUAMyNFUd3NLq+rSiksnMParIJVr0Vhw9Ov01XTfkrkbpsm5bqmN1yBzSKGlUTMLvOkyOfHRFCKwvG7trQ7Uw3E8ZhURrbvmlvFbPYySnOPTqHOxN86AcKw9serf5NzdY2ckY7adN91ThCk5t6IHTQr2PreeKI0XoaopFmOQz3edkoxTiXlT07ATKNHYK+CyOXT0NypBgV1ia9R5reTVnOzq72ZTwzoCjTZ13mYpCrHf0UpyeOWTxMvaCBM0HAC1HT4/v5aaP3TTSXFoxDLV8gy3Rx+xUKzuz+Fq6SAJCVttPZAj1zdHtmUFozyt4eBFcHEMmU/6ppgd2vWSJpCCPvbmHh9iwKvpEwA3k18vFA/gMFcoiAiaIBnEkf8BullRSKOoAh2kW+++ANBn2GMTjqRPr0+t4NV1l4dtcWtkFRJvHV4RVo1jTexAcRG+51zcaA9R84VrbB1UnQ3hGMy3S7s2jyEqLKVJzVG+WeyddJ5VtW2Th9StT+AFcISRDKVUh/s5b+CxqnkZmFcHU5spd+tHfE8PQdEIfPC/TB/fqeYL0HYc8BGnkhJk3VMgAx816F0hEF3ue3Z5gUvorDOxYGKxG+V0PZ8ys8TBwlRG2fbctzDHbES/lFLG5V48JdGtmOA5HblRKbZ31WBqNSnC04ZdcDwc3aHBJbaTw6yOLZ3eCZan2vaAdbaTWqZwelVGGVqltLase9mzLRMwOjmk/1GO/DMUDER31lkvsJgxi76Jz2PE8IJSdheIrdWZ1j8doipxhNRXCD1kR+zRjdbKZfn/UlP6PlLu1cBV1jLLUF3uDyMuZNx1vi9oGlPNZzIohwQjWcEUbRx4z8gAmVQRM2fZqHIWl49r8VAVW8BPL2dOUl6Xslfs4t7K8VZPzXRWAiPZ4tmXM5BvBxrIgKvj8Al7MUe7HKlpyZWxjl+5iQSJB9KuF2K4yhFygGBeswezxT2gMUrH0A9heLsZvsu+u8KEVRnKNdb0NYwhebn0Xuu04BlWZkWbmT8rwhCg48Ox1he9m5F826Gq5oW/2vZT9/10h1HWBdj1FF/sHm7oxpys1isZ4HI0UyS3XEAwBrDtQtWziOUVcN3y1W9KfVk8mrYzCAF/tgXkKD3HuwjXAaviqLOqdV122LMKhrU9UpzjCTwMc2c5pM4sSkGOeEohlPWdB20Nhva/iXone9IbXwY2Y5hccsnYbwWuLY04ka05253RWFU4EMWcIfKWGWI+F20+zP6YK3wX/OjcxnbimiEb1jGxRABw0QPaIGmyZVOO+zaAqC7KWp5iD5UKRV50hNGw8Ck15c/avxzN2bvy6n9v3KB6KNLhKeQFdPjfmXZ/+hlL3BBaFxUh4PftniBnE6nujrCNfOdHewAOAw+hC0kRRQM4wVJuC7RK5ZC10Gmlck5zLD/A1EM5mjr0F2Bu4JDQ0p3nbeRXtsZRDKP+EmPEli0Axue3fwgBAyKOTmilJk4W4/StimcgcVTBVEvnK+464RxSUgK8cHTFlx09RG8OApgD0NMtAwdRvRy2ZrIKeGzuPqkUz+6lPAwtVSOWsrDgCkRImoJ7nLSruPIJPumtSeo88zdVb+EPMzhVWioMdciM4iyJrk10vpeBEiNp8sxKyWF9DnQlA3YQPkhn3HxaLJt7elkUN0PqRvT4WTC8Nfa3Y537GHrMyLJORqrDpgsZHZskDDcJVd0SzkygG/xMu0PChHdzLjejg7Ggtkmna3TsuvmgIi/BWjdrM76jOjh8+cpfvu1Jy5R5Com81ghaDY97vaniqP/YCWBYfDXlFiA1MqBeprV0iMh9TKZj8xSMwrM6mVGLth82mwbNM+9Hw9jSNblyvIEdQTORY45Gy94M4NuEsG/h9hcqc9a3F2P8cSIZTG6c0xBJ6EXIr4GGF9Hw+z6pMQhRwM2tZr1a9DKg04n+38oDtjTrswybDE4H01Cb2uauLvWzoWokjU6hP5bRwfLp3qca2uPmclBO6m/OY+RZX5Ajor5TAh6oMgUA5kZxSDamp8nXBzqyXI0XoMsK2ha1xO7XFg7eMmNaIUTOkwcJhrdTs+eo7cSIY3jt1ETrp9AFfDtr5OZSCfnXCVKlBVMKmqDX9LLR7bLO8sWbeMUpYNJKs1LNhSlghwQfaoTtqp7vANEeUD3CplY9DaDakdycmGzpduaiBSXLnzD2nwNbot6KL2baNYOQo49JgjMjjuyn27HG17lhA8G/Lr0xO3DsPLwSnzuMDUmSjEE0DdJMHqXQNJXZrn+RmD6+Hg0SvyQ/ZdWSUN+tdJx9BQ7HSoenhl9WC56oMonX9WcPWNIeQOn99IADjhKQ82mzQn3Fw/VHWcinTIActq7UaB0JtGBjeYp/rq5QNbVNtHCdAVnpEhf2lX4BbXipeSUy5QcupR0wxUEUvrdEPOZFrfirBFsCpVzjxsHslx5PMClC9hbbEG8aXTh9TEm/bNzxfeQAFTIm65IcRBeyEoXKQdzaLm2ITMUbjua7getjsqS4x11gM8XGUbr5c70ZAJVd4CWmIuHzZB4mmYL0WQOeKzBmUrhgBuMn0FMxS8/PZZbNV1+ZgkPzQjp1j7Ad4Kv8H4ryVD7rhMiarKqJMwUBjJoN+821KsvZ5uBg/TP2o5DkgJmbECdTXdvZH0AMc3t4OIt1rkMjt63GeHsN/mMP2AxLq+dSeHYliFLItThxi9o8uhvRKQEa0JqVeS6p9QqpMgCozYnR2VoDRKm20TQ7XyKa+hSqgHai3ihaUT3fGwZyw90mfAmlzXiSgaDzaGAkX5cYYIST574uz6CmbyPQZR7pO7Z3TuJxSuOdjcPpY4vDbdOZZwL3Zc1JpMdLFa6NpPWTsot7rVlM1EhwcdIy6hmnO+UgzCYbGllonJntOsT2jC0uX3VP8mTDaw2sCjROLyMBEJEc5xQFDtm9VjVXnZGybFF/m+nchFfVXcbSg1PCFh1GYz4zhAkFrC3mkyDixBZf3dQS7RJy50hww8/9QHCHX8KpBWZMR8hkFvjn7rIHaJpUN0F0TU29nz3TF+1UadYE8UPWrZc8HG5hf3ANVFS1iQR20C9Wpx8HhxeKgbqLVLz6d4pERtle4MsaIGoWsa9HQ0tsrRWVsC4mGLxax1plTjuC26WfNTkuV3UfZxI9o+AQ+6prQwItZ4faoWW1Gfrrr2
*/