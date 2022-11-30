#ifndef LOCAL_TIME_CUSTOM_TIME_ZONE_HPP__
#define LOCAL_TIME_CUSTOM_TIME_ZONE_HPP__

/* Copyright (c) 2003-2005 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/time_zone_base.hpp"
#include "boost/date_time/time_zone_names.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/local_time/dst_transition_day_rules.hpp"
#include "boost/date_time/string_convert.hpp"
//#include "boost/date_time/special_defs.hpp"
#include "boost/shared_ptr.hpp"

namespace boost {
namespace local_time {

  //typedef boost::date_time::time_zone_names time_zone_names;
  typedef boost::date_time::dst_adjustment_offsets<boost::posix_time::time_duration> dst_adjustment_offsets;
  //typedef boost::date_time::time_zone_base<boost::posix_time::ptime> time_zone;
  typedef boost::shared_ptr<dst_calc_rule> dst_calc_rule_ptr;

  //! A real time zone
  template<class CharT>
  class custom_time_zone_base : public date_time::time_zone_base<posix_time::ptime,CharT> {
  public:
    typedef boost::posix_time::time_duration time_duration_type;
    typedef date_time::time_zone_base<posix_time::ptime,CharT> base_type;
    typedef typename base_type::string_type string_type;
    typedef typename base_type::stringstream_type stringstream_type;
    typedef date_time::time_zone_names_base<CharT> time_zone_names;
    typedef CharT char_type;

    custom_time_zone_base(const time_zone_names& zone_names,
                     const time_duration_type& utc_offset,
                     const dst_adjustment_offsets& dst_shift,
                     boost::shared_ptr<dst_calc_rule> calc_rule) :
      zone_names_(zone_names),
      base_utc_offset_(utc_offset),
      dst_offsets_(dst_shift),
      dst_calc_rules_(calc_rule)
    {}
    virtual ~custom_time_zone_base() {}
    virtual string_type dst_zone_abbrev() const
    {
      return zone_names_.dst_zone_abbrev();
    }
    virtual string_type std_zone_abbrev() const
    {
      return zone_names_.std_zone_abbrev();
    }
    virtual string_type dst_zone_name() const
    {
      return zone_names_.dst_zone_name();
    }
    virtual string_type std_zone_name() const
    {
      return zone_names_.std_zone_name();
    }
    //! True if zone uses daylight savings adjustments
    virtual bool has_dst() const
    {
      return (bool) dst_calc_rules_; //if calc_rule is set the tz has dst
    }
    //! Local time that DST starts -- NADT if has_dst is false
    virtual posix_time::ptime dst_local_start_time(gregorian::greg_year y) const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if (dst_calc_rules_) {
        d = dst_calc_rules_->start_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_start_offset_);
    }
    //! Local time that DST ends -- NADT if has_dst is false
    virtual posix_time::ptime dst_local_end_time(gregorian::greg_year y) const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if (dst_calc_rules_) {
        d = dst_calc_rules_->end_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_end_offset_);
    }
    //! Base offset from UTC for zone (eg: -07:30:00)
    virtual time_duration_type base_utc_offset() const
    {
      return base_utc_offset_;
    }
    //! Adjustment forward or back made while DST is in effect
    virtual time_duration_type dst_offset() const
    {
      return dst_offsets_.dst_adjust_;
    }
    //! Returns a POSIX time_zone string for this object
    virtual string_type to_posix_string() const
    {
      // std offset dst [offset],start[/time],end[/time] - w/o spaces
      stringstream_type ss;
      ss.fill('0');
      boost::shared_ptr<dst_calc_rule> no_rules;
      // std
      ss << std_zone_abbrev();
      // offset
      if(base_utc_offset().is_negative()) {
        // inverting the sign guarantees we get two digits
        ss << '-' << std::setw(2) << base_utc_offset().invert_sign().hours();
      }
      else {
        ss << '+' << std::setw(2) << base_utc_offset().hours();
      }
      if(base_utc_offset().minutes() != 0 || base_utc_offset().seconds() != 0) {
        ss << ':' << std::setw(2) << base_utc_offset().minutes();
        if(base_utc_offset().seconds() != 0) {
          ss << ':' << std::setw(2) << base_utc_offset().seconds();
        }
      }
      if(dst_calc_rules_ != no_rules) {
        // dst
        ss << dst_zone_abbrev();
        // dst offset
        if(dst_offset().is_negative()) {
          // inverting the sign guarantees we get two digits
          ss << '-' << std::setw(2) << dst_offset().invert_sign().hours();
        }
        else {
          ss << '+' << std::setw(2) << dst_offset().hours();
        }
        if(dst_offset().minutes() != 0 || dst_offset().seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offset().minutes();
          if(dst_offset().seconds() != 0) {
            ss << ':' << std::setw(2) << dst_offset().seconds();
          }
        }
        // start/time
        ss << ',' << date_time::convert_string_type<char, char_type>(dst_calc_rules_->start_rule_as_string()) << '/'
           << std::setw(2) << dst_offsets_.dst_start_offset_.hours() << ':'
           << std::setw(2) << dst_offsets_.dst_start_offset_.minutes();
        if(dst_offsets_.dst_start_offset_.seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offsets_.dst_start_offset_.seconds();
        }
        // end/time
        ss << ',' << date_time::convert_string_type<char, char_type>(dst_calc_rules_->end_rule_as_string()) << '/'
           << std::setw(2) << dst_offsets_.dst_end_offset_.hours() << ':'
           << std::setw(2) << dst_offsets_.dst_end_offset_.minutes();
        if(dst_offsets_.dst_end_offset_.seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offsets_.dst_end_offset_.seconds();
        }
      }

      return ss.str();
    }
  private:
    time_zone_names zone_names_;
    time_duration_type base_utc_offset_;
    dst_adjustment_offsets dst_offsets_;
    boost::shared_ptr<dst_calc_rule> dst_calc_rules_;
  };

  typedef custom_time_zone_base<char> custom_time_zone;

} }//namespace



#endif

/* custom_time_zone.hpp
WLQ1XqwyYFVnfYmz92RKI8ZgyEfYL7KpSn23B5O5sEEXpfnbkoxsxamVrztOaAv72HQb7Ui1a41G8adR9hlmuDcdbi4vhcEYnEDRK/7lhuVsyS4wGhjBp/21OdRalhvRCe96hm+SYJuidWt25mUpHIz4FTNBSCaw54JdakbG0KKXETkU9YL+HXWD474FB3Zm1hnGrVBuX8m1rtXAE5bLiCkjOYIsm8r6jJcmg9qjRizvhMDpYoiAMVgQQKZhweVC1Ij6gOX2ixKUtCy79GpeIZpZKQxOjMxwh5aPcR8OjvuZ4qgcjwEeK4NgEJzp4cKY2Tfdro1Zta9MBV6VKRw+xGE2RUnzLD2wtOng4K+VhdP+7TX62yAm6mZh6mYc/RUBSEKz3tgObpWhdTrwvmhDW3MXOrbwSXWuQi3nYaskwzO9rezTNj/B1JDGFLtv8CJ2PfsZkzFyoqXoPlKPyW8/LgFYID1q4rLpOoxe3tI3167wWNQRysAhLoc4mtON/ekERmQN6vXSS1rPc1II4gFTuE7ipbgJ+6FdyqVaTaHC8NJo8FdszCgpbrd5fbAWZWs9Zff2/M4X+xxkSiwkCo4ujWPgITXjO8gyZkkhSR7ewlPA4Cu81H09K19YtxTEr/6yVJTPEHNIxteBKAv24nnq6UNAh32PJUynDSBE9otOk/zRcNjxIsxAkt7uuX+O1iG2OPd4VUbVmBYGz7CS+10GFiX3VhMZXLUMl54wnCODj4E4xwGx1s/unoNYage7Sym2WJM52OnxzrEJM6qkSNe+KwOOAr8IPmU+BPUogjOIWkFA7CGUPtg7NrhsLADeKZZqqkFZixT8sz62LwwFTpnbGnn9j/4DIoDdf2xTnhRm8hwIikYtzb4HIj7b8UjDSHajCs5W3Tw1bLSSPJ1ieSXLyv01za4XeTRQKA8xbBNSybOnk29reSUBH+qxIQPDdOsiDZN/MA7ohHOz1ax0aV5oyS0PHGmSYXUtQ5kD+SaQ6SLt9PYeiPNPInLXjt5gBtoG4d0MK1xhYGTPzIZJhfvzGIeQe3PyQkdE8LC6rqCkbh3K8F6Mksg1HXRYgRn2d3Sz/Cf9LzIVLHtg8Sbo1hitRYruZCPXxMoL/Oxg0zfpYu1CyPwqTuL2viH5yKrkfWvFzIQ3jHbns6pgLkNItIWBjCsMNsOu2S9NodQpgkEtNFOTPSXNqPfyvib9rZMr0C7aqrjnwbj+19TypVt23bkL+YTItv0eeYysS0wyb/P2XzWi2ccn/QOQ+HrocZ8W1YO3Qn8gRlfDjOcPSGB2dmcqYV+DFCkR3TondPZ4rb/8w73mYym66ycfx02efkIr229HFgsvMB+olL87D+mx4ZKpVe5gnoP6iRvKcsdKYzEL4u+VaMkl0t498yZnT7EYcid+XosrB1rY6z7P82o9YWB2hhhWJ6VXcidfR57rMZFqZb3t2qZvcLp1zYvRppr5TM/ehPBSs4u+OSgh9RSY2IW6AuD71U5L4fKkF2KRbpjtIKam1D66uDZ53ZOaAwYW7noycrDUqlJMvqK9hVIqqWiTDQLmyzhdT8+kTQWpyiyHg9vorowrBzJ1aapvuWX1tplOkmVw8V6uqvO9ksRu7XkPubqjohxLQ+UPgKWKYc5/RQgBNxYuhNYN7haTa9fOgi6CYHUSu41YIFXO7Wdcpbp+/1aNQVGXDqVGO76mXldgHpDsNMpxhdqPg+4NJp4P6QvZAZ1cQkdMS7piDl8lBI2jwxHwQmoB8j4b/NibDa5E9ox7TJeVW7FkjKnEksbr08riIAfGegMqtyZdTuSruemnK/Xmb0PhVB1Sa/RaQVLkSfKYA3WpUNPuw4yeGTmCWZFUTdCX9nFM44+25xPOGiEzlxdOG4RacOqAFDC3Z7zt1uBdtCuGX01wafwMWI/E3pU5Ga/rc2rvYKNusrNneanOK2VlfE3jDnHuHL1r33Tukjk5T+eBLdp8QZhXP6RRqKk4snLjkFOmfQu7d7xCQzmnJ8hCZAhvJtp6vyHSnvG8wNYRm2bCzLOBAjgtqEQ5KWBY9/LJehAZkdcHeZW1BB1RfhESim1m113Qnjs6kmcCPb0zkZ47qArMNDuLQuejJDgjotj4LjWELRy7APLCrhZsGFrBC8pjIxiJEFKLfrw2c3M0OexKQB917T+q6SWC0xO2axTBoJ4m19cwGvD0t1BiQQwLUXh2WxDvj7qylS6GEXwK859XLCMh/VS2kCrj6BLxngHT1Dd3K7Hcl6IfvIJttgSEKxR2TmaPF/jFQa2N0zweDqZIUbBGntPHBTIwp9GWKgLnZw8VTagG2u609A1L26gmLFHdIMd+P4x8gCIPH/ZArhh+AcC9zf9Id8O6FPV9GJg/voy/u1pc98gRWthA6gz6NeaXTczTclyaP7VQGbkmz4x9O9/xsrq5P75lDudwvEnBdoX1Ljc03p89OHCj86o9BDaqGcXXbiRiwo1CxORuEwZ88KrE15ec3TypJ/cLLk7hmwXqwT0vUaroWuKVVX0n9IXNwM8yiLESfrSw2OSTEfSbxwTuIE3N8E1DSY9WC1/AbFNcJXD0y020ra882bfKlyQyE2FBaiZiyr2Vn4FO93/Lv3RQD0ZSKkRkXSAdWdbFxMyqkTJv5GuaftvIxZTWv3m82ghCQKPRtZmnEGihok4qYd/zwNmPZxEMur0N+efvn/9TAm//+OfnenUnOwDyXJxf8DUcwTPWvkmR6kExA/Xh1uRJ8x9LnXxVyIaBrcF6ulBc0/JfQ9LNmpxAnImsud+Z7IbqTE1AX9KjS7ewYq5+rVtzLk62+Oqh7AIxFh3NCuBu6UaCft+6RoVUmcjdzQaVq+kR3z+zD80OAda9wdC2b89pHLRXM3YuNMYO5oGE9HOrwomFlt800W7flju6vXfdKZQugAhCOTCo1+S/7FtuRI0yy4zXVpaXq6ZwuXYJXo/hFwA79Mct1KGnXZvLc5nsrYBvaru7kdpW/mn2mGWB1/xBxu/dHotw+DbSboTF3De9zooEWtEKusCzzK1hAW2eaHxBou/OH8k9kdipWXJnN/zmuG8nU06rXF5OKJO6puqoCkDta2H6OsVVKCf0e3mBwk0LbWfMy4xNI4cNs3sY66O12gU4arYBQwPueUVLe3RWAhTwcE94QPbi42cztmO4EatGRvgctSbfLLDVzq1CTZDR4ENZ0mr4pRJ/uZv/wnv/qkJZBGN7yX372epJYvNRlq1lUrtxhZpoPfQJQB68fMUU8vxBckHbtBTEKowFOt48t5beuTXQkKaWJnCat/PSy8CFkx65LuXB8uLDXhU+hWEPtCQhoQkrK7KCRojdh7cQjUSJfDw5ccaXhBAyrDC4AHhMWeV+slBhJngHUebWHnHu7F27c6MtSQCG6Kdu93Z5lK0uvoCpZMatWErQvlAZu7ed2XJCuCvFGND5MINNSIn6ikYcW2fNA0JKa3Ic+pas9E2BG5HJCGcRKyjXdRxtTx1t/dTCzdN4nFxUWDIqaJfX1ZJSx0r6uo0vBHUe5WO3qJ1eUEnqXP3E2FTOk2XnDsiS/WKB60aNQfOZr6/NFRcZyNXs9CPbbLPZKFCKybN6AYO92UBGoI3XIhlaU7EmNEP1GUiVfXCPE8o+cMZjH4g82dWJUjt8TCVghqVZgV8Q1AzNXe/rmzJT3HaoYWN6w3TDVxnmYtetXDZ5Yt7oO1pFH2jCLy49bMFV6KT7JEYYpM2WBcp6mR5/nnsoSCEWHbHE1Cl1enUKIIxNhDMe6vnRV4dtzV5JueurJ+Bso9Iwkiij1VSI2aVjK35mjlPVdbREKofpMDfre1yvIKBtBNyRjiAxWQndq72JLpRPQwhIw+zeVuQSmB8+k1WSyr9OZfH7C8uSuQbCPaukXck1O5JWck8Syj2m2VV1Covk9CkKEzNtHMabxANi7j7//Z+V+ka2iP2thdvXglOmCDY7ll5KLKZKaxK+W+VaSciQU+IwAmKQDfELGzqJlRyCXBV2/GZKrOVed3V+EhQeFbLZz1iNaGqOwJp4RmdfMQoB+Rr6JtSCwvg40wQDnzEx0lzfid0mL6vK7PnPdrPSvvoNqjbxa0hknUl1+IoRC7eOhwOIkc2Ql9nWadYA33KKW7SQp0rio5gr/efXyOXH/PdGVN9HhoBpY+vVYm1lkzi0LOFD+iJV41mxI1to9ats71opeFWhfKEKp723YJ/HFOqeOAdGbLlOF1fr0xTrlm6MDxbpEbK+TEfx/Lum7G12Nr3K1zWzO9jCq3BHFsHdpyi0uE9ah6CoDcvGakHny2aeyQktPCOvuasL4GZucALCYVNYi22wv0caXjP3PKcxDbCh5EgXc4D1OROp2eflgNsTcLytzouNFZ2rMOx17s1QJC1tysykVZSdrK+OdjJcSbfn70j3uImEpouf5z08d3q05OPgE0YeXP0oBBZGSvkN92FGl4rHcYdd57trm4uvjpWBxFk+Og42wsJ6rVL+2xcqprZhEcSHrdS+XPCW6bh1BG9BzoXfxqL9lqvAdR3sRu/iFaJcL8dQOMtxtsDel2XXhtgdnVqnqszJTL9fDUlA4r2kYBbj9V18wmCaiIZDBHKV8RkZNyBsSL8H1ivS/SQQw1wXW4m6P2AMexl1yU71v/q4UXRytbFDKzhA4IsX0xwlkf65tPghdELhGIjfDvsQ3sayZSYFAQYNgLTUqeYNDCL9Xj5Z/xEf9DocNhl8NDN7e8TrcIAHvk4xgQuELqEPuIzpeipH0PYxxIeQxSp+Zmu2x1PofMYTFPeYjvAFGfkvOM6+yEZodeMMtSeDe7dP1j6JcA02Pf2YbXZbBAwDgCXXfHhsapbYGoXCzSDjjpqtwpg3HPcI6ld+EgSvJpjczA5Hn0VW1B+muvFTWXNN7Xi7t/Wz2kLgI9v1uwkVotDQhLVBWNgUqZSJRd1WNrGAgbqbZKLm89CFBl2Z1X3wst0MjSzFqd1OvNj7FIYhxgETQYUiiyKeGbH9ptc+3vHax6y+yj7Boe3skI8DQm17DXtc1+zUlRqDMDsV+/elO3Esd6cgX8z0D3/zqqYvcczRoyW+vvjNBT4fdG2WCC3JosH1FdDJjyjB/1GhaFlMBo3tQEb4akuC4bTK+hTyTi7OLvWGffWwVYa4gl0SxlkiheMpBeln2Dp2/0xic4f1vMKz99DfyPVnF2T1TeCqGe9ZuBczJwQ+4nIJ2w9EmWRNITD0eohpXg8h0aL1xNdpp+83uz2SfRPbyD5MNAVjwoubYhTsZpSZc02RXGFBz0zQP4NWQhaayhoKoUPOcUplk0vB53FlFbSQQzc5PJ98DHE2GvKqJBQKeRjfiBhr8r6Lu0L7Lm4LCYOzcWa44qbx0eIJLoQlkEBxPEigIL9xcgWhj3HwiZ1jrs8h0+0QYrT+rIYZUoB3mWdKqwlD3B8oypR5fUHapCvtSiaG0PaLBgcu5/ddEqNjdD32l3b9scZhCO1gjLu4lYG3HpPYlfsK0PeMe3LD4FJJz5jjwkC6xIhlSjrrgNRqwCWPz3QIcYH9uHUgrJ01cKsO1TASNJtbN1XUsPxZeH/VamVqYl0uDL5II/Xp3JgXCeRFoHyDbubuZwEz8tURrIDwUYXA7LRhhkQMbezMdgKGHFJz+LBKAdMdmm+rPFTS5aP70R0L7+IajdG79kc1HFAxHpwo4Ts4Yq1w2DaKy1nX94H5oLG6jBRpnGBqRHCCoAnrfRpXy7hgQZSZZc2QjvPf9J7XMOCEqWAoCCJcz5iJ1Zkks7Pl7iUTQ295mwNg3H9NcRxcYnktcSBf4kC+QA1nX2318hx6ksK4W898frNu8myVOtw9zfHBk9jYAXFy5EktiBSpcYq3JyHUkDAafTHCHtTu/PZmu/cvJhji79vebVMWYqJdAjJDA5nNTXM12BoHaYbFqeAQ7mZTbThBTsWpdG0bLatJ5N7vOc8uQ24HqaTV7cNkszKQg27ATUOCXwDsmvAClXIpxF06oShDZNd1SYeNkOIXobJ+85acN8XeyTj3bOJEFejlVorFfcX6MzneJbUqrGFdWN1xo+4a35HjMNfsNUzdKnxaBZHAufsGvEMZ8lI4lxubtrL5n9U9QvlbGpucE1SloIIvtFJUqRzmHmYVFAiX6qOoSjKaQjamkAc2/YguhIx9uHGLVta+zXZzfHToClfL9Tb0Z63uqAUCbjGtakaHdV0Mm3JtmCa1YZLUDuEMvRAQg2dnv8I1R/47EC6yW7OU7V2IcI91+R6qMjnmrdPMfB3nmEq5O6a4aSOcjV+Hp6oyVCJkXTwClvpXfBz+gkCbgWB7yYJBE8TI83i50n757GkSfzWPIMY7hSijSZAdhGWUNr9uRq7WzuKu27b1zUd3AdXiXYH4YmbImmHYET7EE2Ym3CAhTDyzFZZ8X67Ivv3enUdX2kA3afZyWyV4aC6rlDbKmFX12Iz13nP4zkI8T4P7DoVl6Zd486Ht3D7mBv8eAqaQqenY0PHuOrduODIu6AlCWC6l6mtzg/X5sBOHyqiaMnAkRD27iib8urIKX3ejAAgs99Prs8IpUCGw1iwmgnNo68Ld2nJ7CikIASm0Xej3KuPj+K7usBIBObSXkIrumIHFdgtNcX+sUCH7RdYJbpzWN85zSHyeQ4xwVnno+oufnBQG7ul6PxcthI+hr9gNcf6uFNzRxzGnMhinrVs0HmOUXHHIiKBcf7cK0I8S95cKjwhkzfR7ga/1tuVBXDmVQz/H6Yv2y+oV1I89G4lyORAhLCxnYeBliPD9HjNO469an7rTrpatcYpAF/RAhfDHHpW9ky7/F7s5xTogDORtLUR1WItRHVJ7CS2oMDGOZiipWSxG3RQfIra1ynHYQTb2MbWXrh0OryNILAryp62HV/wGL/wE/w9Q5F9AMh0AgENLdZ3brtu4kobfaPIMnUxvoDcGmABJI4O+k2PZVuvkpqRowy+bGz+Dr3wxLBYPf/1UbtZyfTyIkigei1XJiC08RbUMYFLQHCcA+9YCwT0cJeI3FF+j2hjAi4VeFNU5Lu+pHp0JfLS36TggL1og55XlS9lfvz5p6eHKg5za+AbBpHcEZk1CjJ9pSm/77SClm742tAt7bXhHREkub3b9kAWz2lHQ0vhCmcEBhPkiP4eVNHdMOI7DMKAbUMWFQnAXCoLgPH8I+JkfzEI3b4dCVzycHGR+k9GdxsfYRqoIGYi85J+mS/EAhxVRtG9ZVC32Z9VpWY6XMxuj17ak+4Zkwqy6Bb2YGIQ5d8taGl8xuUbhpL2nqpZ6HoLKbgIwC/GefJiieAPIoq10bXIcmr6ZFnyHlljbmTLezlSE7Wwbk2u7B/MmlC5DTBuhqTARBgOt28VtF7PwJF5EVJcIHn5CkLUuepZceQEzAkxxCa8jmpOc7GfWDSdKPpRZ09VfXt7QFJaFvn75HdKJ6kisSF31JQz/Ff/zRzXwVzXQqSKwv5i6jwODjJmiKlAmnD3URJXLRkl2ZkapFOYqPoBl6CDP41h+lbYJ1FDis5neVF8m6ucEmG9/ehedeRHspxTB8k77vYpfpEF3fVXv5MUKQ0KqRSuAEHMe6GtRQDFskzYPZch11aFDfJ8zjDOurMuCzm9UpOnGNa/7IMivynWXC+T+
*/