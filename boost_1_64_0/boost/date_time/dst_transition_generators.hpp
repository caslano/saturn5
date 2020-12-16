/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 */
#ifndef DATE_TIME_DATE_DST_TRANSITION_DAY_GEN_HPP__
#define DATE_TIME_DATE_DST_TRANSITION_DAY_GEN_HPP__

#include <string>

namespace boost {
namespace date_time {

    //! Defines base interface for calculating start and end date of daylight savings 
    template<class date_type>
    class dst_day_calc_rule 
    {
    public:
      typedef typename date_type::year_type year_type;
      virtual ~dst_day_calc_rule() {}
      virtual date_type start_day(year_type y) const=0;
      virtual std::string start_rule_as_string() const=0;
      virtual date_type end_day(year_type y) const=0;
      virtual std::string end_rule_as_string() const=0;

    };

    //! Canonical form for a class that provides day rule calculation
    /*! This class is used to generate specific sets of dst rules
     *  
     *@tparam spec Provides a specifiction of the function object types used
     *            to generate start and end days of daylight savings as well
     *            as the date type.
     */
    template<class spec>
    class day_calc_dst_rule : public dst_day_calc_rule<typename spec::date_type>
    {
    public:
      typedef typename spec::date_type date_type;
      typedef typename date_type::year_type year_type;
      typedef typename spec::start_rule start_rule;
      typedef typename spec::end_rule  end_rule;
      day_calc_dst_rule(start_rule dst_start,
                        end_rule dst_end) :
        dst_start_(dst_start),
        dst_end_(dst_end)
      {}
      virtual date_type start_day(year_type y) const
      {
        return dst_start_.get_date(y);
      }
      virtual std::string start_rule_as_string() const
      {
        return dst_start_.to_string();
      }
      virtual date_type end_day(year_type y) const
      {
        return dst_end_.get_date(y);
      }
      virtual std::string end_rule_as_string() const
      {
        return dst_end_.to_string();
      }
    private:
      start_rule dst_start_;
      end_rule dst_end_;
    };


} }//namespace



#endif

/* dst_transition_generators.hpp
5tPmFQsP8KhBC6XpRBrTlAteKZtykd/qV8o7tVzkN5cLCdg5Qo9upHwXSxlrcgRfXSTFG8GjS1nJ7LUrNFPN8gz9iGqv+YA6L5i2yjRojwyvSbuVfKk8jWrknN/T8wKKH5nI8rYEFd+ZZCtxvZy+Wiqcl9c0V28j+NWzK3ShlkCU64cK8qQLvlenFuFpgg4VUyhdh6ZRKK0Qww9NutscCr8fbmL8ikI95cXyTeK5FHdi9m1Kt/yV29DFv4SzLa/HmP5/5uv1UcqcPcxbSwrlsK62cT8C9kKEyTvrCUze/BOFDdYAN33ASiZBGX67kA6kZxqXRceoA1KxooG6Bgxmjq5kkKqEI3xEJ/MYWE8rioWEzYAs7zwlS5w/0qvMg/cfE7R/zNP9VyxZUNk0ZZ/2Ou6b1rdaDF12sJq2Bw5t9WVbzzssx2pF/NkkLi4ef675jK8ygcZDPkaarkeMbdQhhNMmFVRMqqWjrimQNR58VSnpOQ6bGFlsRDtrUuymCVAz7upiza/BBbb5VcN9uP0Wnl8bjo+2Iwot+egpVt7IFHvpuANNseNsU6xcdItToCOZoVHpUkl3dDbmX78XMP8kicEU/DldmxYemP+ba3+pky6k6mz+xdppuzZoUyv96JUf9/a5N6sZi/d/t6gJeygTM6Y8fV2FQo27F/OowKDqPhItp4yXu44tF1Pdjm5YeEwSznpyAmBqP3DorSUBaW5OWwkheZ1Oe0ekJXgXPkRRkRWWo51L2PbNp2cp475vJijhB2+sl/DGWnYTNtbfYWPdoTfWzyaLjXWBthzZ+hx5N8DBfZBOgfHleXYut0zpufOL4ZY2x7q81wwOedCYJB6c0zRuvgS0guddIWCJvVhsQJNJOvazzMEI/suSz708O8p9tI/3Gr6JKpUXeCeeG8NgQjfuZe+N6OUk9PJvdS9XlrLBBFzgZZvbVY7SJEgLrr1AXf1shdFMoYlRIp250zDThD8M1RzG1ay9AdXcY68mg6qpb6AvS3NgfnU1YAV666gC5ZHZx9zjcmSAqdTb7QXLYS1Ec3G6FKad86bIp+mVer7ukmvAz8EaqAQo5YsLuDlnidlAWVg1rbfB/O1ajma1tDfrxItI2HWYmmR65pXKmVdqUU2A6ynTvEbaEE+gOdf99rhf3itM4wBQdKWhT/DUb+LTJ+hyZaQ+waBpsmQT5/8VDCjGlD9zgjnk9ik/5no95W/Xg3bLBWLKv6jurPWUz8O8lu/5b1TzWt/Ye2LBGkWwBO/Pxd6baplKTAp0xk8gcAmk4aCd3gUPgLp+ikmrCQxN2u0noQU20TT4Zz6NMA79GYcF1/EktOHw3CTC4Q1ArjHu09OtKrDVr7qE6lAtOoqhDY4FbRagQR8odOkBQI2eyqDE6hjBoELLYoDqT6BCBbyKjuN8m0S+e+z53MjXNWrh6Ev3GAsnjxcOaw+O/eUtnIOcp3lCO2fZjXBgS1LX1yXz81LLWogvFjkk1t8rNLASpFsrjEKLiyIpHTYu2VGtrI6qaoZeVOoXA2l/UHc1Q2hQK5qrp0ohDwYZX3LvHAAmLdfiE3A5EjzxfN4ufeKIv5OvJWevzXBgqodZi+AyHuqHl2KoL8FQL9JD3YnKB1e45BNHjF7vIfxc6icZv4KY+i9lluxkfp6be7qIe7qfseA/r9INWKwbUHxeQ5i9wU/gYujV3PPUWOio587WHV0iVIXsHV2CL9HBhcaNYXFw0O8yHE1Vsog53yKm240BbS4IzKv22JGt5QN5uPuD2EpOgxylWBH8SHSHdF6bjrk3toDdECozNXGvvpj3nd/MYM2v68+Ilo2PjLzqPP9sQZhbcWji1UKaJKwspq9361s=
*/