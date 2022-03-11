// Copyright 2008 Gautam Sewani
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_LOGISTIC
#define BOOST_MATH_DISTRIBUTIONS_LOGISTIC

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>
#include <utility>

namespace boost { namespace math { 

    template <class RealType = double, class Policy = policies::policy<> >
    class logistic_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;
      
      logistic_distribution(RealType l_location=0, RealType l_scale=1) // Constructor.
        : m_location(l_location), m_scale(l_scale) 
      {
        static const char* function = "boost::math::logistic_distribution<%1%>::logistic_distribution";
        
        RealType result;
        detail::check_scale(function, l_scale, &result, Policy());
        detail::check_location(function, l_location, &result, Policy());
      }
      // Accessor functions.
      RealType scale()const
      {
        return m_scale;
      }
      
      RealType location()const
      {
        return m_location;
      }
    private:
      // Data members:
      RealType m_location;  // distribution location aka mu.
      RealType m_scale;  // distribution scale aka s.
    }; // class logistic_distribution
    
    
    typedef logistic_distribution<double> logistic;
    
    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const logistic_distribution<RealType, Policy>& /* dist */)
    { // Range of permissible values for random variable x.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(
         std::numeric_limits<RealType>::has_infinity ? -std::numeric_limits<RealType>::infinity() : -max_value<RealType>(), 
         std::numeric_limits<RealType>::has_infinity ? std::numeric_limits<RealType>::infinity() : max_value<RealType>());
    }
    
    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const logistic_distribution<RealType, Policy>& /* dist */)
    { // Range of supported values for random variable x.
      // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + infinity
    }
     
    template <class RealType, class Policy>
    inline RealType pdf(const logistic_distribution<RealType, Policy>& dist, const RealType& x)
    {
       static const char* function = "boost::math::pdf(const logistic_distribution<%1%>&, %1%)";
       RealType scale = dist.scale();
       RealType location = dist.location();
       RealType result = 0;

       if(false == detail::check_scale(function, scale , &result, Policy()))
       {
          return result;
       }
       if(false == detail::check_location(function, location, &result, Policy()))
       {
          return result;
       }

       if((boost::math::isinf)(x))
       {
          return 0; // pdf + and - infinity is zero.
       }

       if(false == detail::check_x(function, x, &result, Policy()))
       {
          return result;
       }

       BOOST_MATH_STD_USING
       RealType exp_term = (location - x) / scale;
       if(fabs(exp_term) > tools::log_max_value<RealType>())
          return 0;
       exp_term = exp(exp_term);
       if((exp_term * scale > 1) && (exp_term > tools::max_value<RealType>() / (scale * exp_term)))
          return 1 / (scale * exp_term);
       return (exp_term) / (scale * (1 + exp_term) * (1 + exp_term));
    } 
    
    template <class RealType, class Policy>
    inline RealType cdf(const logistic_distribution<RealType, Policy>& dist, const RealType& x)
    {
       RealType scale = dist.scale();
       RealType location = dist.location();
       RealType result = 0; // of checks.
       static const char* function = "boost::math::cdf(const logistic_distribution<%1%>&, %1%)";
       if(false == detail::check_scale(function, scale, &result, Policy()))
       {
          return result;
       }
       if(false == detail::check_location(function, location, &result, Policy()))
       {
          return result;
       }

       if((boost::math::isinf)(x))
       {
          if(x < 0) return 0; // -infinity
          return 1; // + infinity
       }

       if(false == detail::check_x(function, x, &result, Policy()))
       {
          return result;
       }
       BOOST_MATH_STD_USING
       RealType power = (location - x) / scale;
       if(power > tools::log_max_value<RealType>())
          return 0;
       if(power < -tools::log_max_value<RealType>())
          return 1;
       return 1 / (1 + exp(power)); 
    } 
    
    template <class RealType, class Policy>
    inline RealType quantile(const logistic_distribution<RealType, Policy>& dist, const RealType& p)
    {
       BOOST_MATH_STD_USING
       RealType location = dist.location();
       RealType scale = dist.scale();

       static const char* function = "boost::math::quantile(const logistic_distribution<%1%>&, %1%)";

       RealType result = 0;
       if(false == detail::check_scale(function, scale, &result, Policy()))
          return result;
       if(false == detail::check_location(function, location, &result, Policy()))
          return result;
       if(false == detail::check_probability(function, p, &result, Policy()))
          return result;

       if(p == 0)
       {
          return -policies::raise_overflow_error<RealType>(function,"probability argument is 0, must be >0 and <1",Policy());
       }
       if(p == 1)
       {
          return policies::raise_overflow_error<RealType>(function,"probability argument is 1, must be >0 and <1",Policy());
       }
       //Expressions to try
       //return location+scale*log(p/(1-p));
       //return location+scale*log1p((2*p-1)/(1-p));

       //return location - scale*log( (1-p)/p);
       //return location - scale*log1p((1-2*p)/p);

       //return -scale*log(1/p-1) + location;
       return location - scale * log((1 - p) / p);
     } // RealType quantile(const logistic_distribution<RealType, Policy>& dist, const RealType& p)
    
    template <class RealType, class Policy>
    inline RealType cdf(const complemented2_type<logistic_distribution<RealType, Policy>, RealType>& c)
    {
       BOOST_MATH_STD_USING
       RealType location = c.dist.location();
       RealType scale = c.dist.scale();
       RealType x = c.param;
       static const char* function = "boost::math::cdf(const complement(logistic_distribution<%1%>&), %1%)";

       RealType result = 0;
       if(false == detail::check_scale(function, scale, &result, Policy()))
       {
          return result;
       }
       if(false == detail::check_location(function, location, &result, Policy()))
       {
          return result;
       }
       if((boost::math::isinf)(x))
       {
          if(x < 0) return 1; // cdf complement -infinity is unity.
          return 0; // cdf complement +infinity is zero.
       }
       if(false == detail::check_x(function, x, &result, Policy()))
       {
          return result;
       }
       RealType power = (x - location) / scale;
       if(power > tools::log_max_value<RealType>())
          return 0;
       if(power < -tools::log_max_value<RealType>())
          return 1;
       return 1 / (1 + exp(power)); 
    } 

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<logistic_distribution<RealType, Policy>, RealType>& c)
    {
       BOOST_MATH_STD_USING
       RealType scale = c.dist.scale();
       RealType location = c.dist.location();
       static const char* function = "boost::math::quantile(const complement(logistic_distribution<%1%>&), %1%)";
       RealType result = 0;
       if(false == detail::check_scale(function, scale, &result, Policy()))
          return result;
       if(false == detail::check_location(function, location, &result, Policy()))
          return result;
       RealType q = c.param;
       if(false == detail::check_probability(function, q, &result, Policy()))
          return result;
       using boost::math::tools::max_value;

       if(q == 1)
       {
          return -policies::raise_overflow_error<RealType>(function,"probability argument is 1, but must be >0 and <1",Policy());
       }
       if(q == 0)
       {
          return policies::raise_overflow_error<RealType>(function,"probability argument is 0, but must be >0 and <1",Policy());
       }
       //Expressions to try 
       //return location+scale*log((1-q)/q);
       return location + scale * log((1 - q) / q);

       //return location-scale*log(q/(1-q));
       //return location-scale*log1p((2*q-1)/(1-q));

       //return location+scale*log(1/q-1);
       //return location+scale*log1p(1/q-2);
    } 
    
    template <class RealType, class Policy>
    inline RealType mean(const logistic_distribution<RealType, Policy>& dist)
    {
      return dist.location();
    } // RealType mean(const logistic_distribution<RealType, Policy>& dist)
    
    template <class RealType, class Policy>
    inline RealType variance(const logistic_distribution<RealType, Policy>& dist)
    {
      BOOST_MATH_STD_USING
      RealType scale = dist.scale();
      return boost::math::constants::pi<RealType>()*boost::math::constants::pi<RealType>()*scale*scale/3;
    } // RealType variance(const logistic_distribution<RealType, Policy>& dist)
    
    template <class RealType, class Policy>
    inline RealType mode(const logistic_distribution<RealType, Policy>& dist)
    {
      return dist.location();
    }
    
    template <class RealType, class Policy>
    inline RealType median(const logistic_distribution<RealType, Policy>& dist)
    {
      return dist.location();
    }
    template <class RealType, class Policy>
    inline RealType skewness(const logistic_distribution<RealType, Policy>& /*dist*/)
    {
      return 0;
    } // RealType skewness(const logistic_distribution<RealType, Policy>& dist)
    
    template <class RealType, class Policy>
    inline RealType kurtosis_excess(const logistic_distribution<RealType, Policy>& /*dist*/)
    {
      return static_cast<RealType>(6)/5; 
    } // RealType kurtosis_excess(const logistic_distribution<RealType, Policy>& dist)

    template <class RealType, class Policy>
    inline RealType kurtosis(const logistic_distribution<RealType, Policy>& dist)
    {
      return kurtosis_excess(dist) + 3;
    } // RealType kurtosis_excess(const logistic_distribution<RealType, Policy>& dist)

    template <class RealType, class Policy>
    inline RealType entropy(const logistic_distribution<RealType, Policy>& dist)
    {
       using std::log;
       return 2 + log(dist.scale());
    }
  }}


// Must come at the end:
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_DISTRIBUTIONS_LOGISTIC

/* logistic.hpp
7yNIqAQZUf1J1QRJ4USNBpY8JUPM2ea4LEZrr8UDYh2Kgs4KnGsawvisoA71CNGaV0p/a551AJEaMwREcklVQpZG741PSXxPO3fuI3AsWY7lXKrCDMfY5reoP1EKJg94sadFfuL6Ubyh2xrVgs5AbMDeDbgdLHfwmHnA5XDz5oVYRF+6g4yXLbZCTvUwbBImStWUzd9dZtXna3trkpc14AIDCWGsN+q5dC93m0K5paIAm2rnv3+6+dgUJfobLT6HW4/UXMzYIsdRUplP6K5FLoqWikcDbSv40XYFKCrVrIYdzQ1AMHXV2sij/4hJqMdXL2RG7GSYZBQbSypVAyZ+96kmIT8KRiIB84eWvw15c716vamhHymzm9l884+ITfRAls++TVNltOx04nm6o9dQhGrK1lkWruz6BflqB+HnL6Dz0lJVPBY4f9V1pMB+SI/H37WkJIn+xvmJcwljINxeKlMwtxoWCMq120MDEj96UG7xsvpmJchZiOoQplgX1gq5eS3CuYEfRq7rawB2s5DO0Y1J5LJUF81Lez0uYKWeoGmS5XIImqKinLQ0GRvZY8fqksrRvNCFTWHBq6HZvonT1eZiY1kNh38NaHsUs1rCNh/mKpuATgQRQoquJZUDIwgN7k0wIQqn+ieOBmb7ieEUhYl1VuDKd+r4m+oqGJ7praszqP78vALNTXBW31BC61NS5rkF/wOtZrc1e7dyW6+vxwQpNLzwlIASCF9K0VYUcNzhvn3CqoumKiRi3V9XJKBFx72QbXRjjEXU9QYUPAErt5O+ZiTETdD3+IWQiArMIqgg8Y3J9CfUCOGmvbHaLaTK9DubbI3pLpQ5a556md0/lmtBRIReszP+5cebCmxrdmecOKOqPQMJ0K7gw9F7rYPSn/nkNdniOY5czGde7ovpmtaTaTOcaXSm7m+GYch4RLxGNldhMcE+C/eT7cO2WAgJf7nrftBfpCq8KWzPLrC9Jrbao39I2wsCdwTPFKrLVFOz3qECpc3k0q/n8XimV6E6qQ96KCIOS3z2Df6CfhTa6Lr5trvPDhzjlEAkGGvVFc/CGg1/PymPwTWhLx5osXr8e8qklB0qjCWo5F9SctDLgh9RzS6XRy/KQk10elpDvth1KMyhNNNycPDVd8KCBPwAO3mAWn/t3QAOQy089KUUvNZaec3N87y273DbfErvw2mF1e85Z5w98caML4m2RY+KSFq2sUWXcsm+0La8Zzwco67s7ltbfxzWwfRYpr6YbokcOdVhHEu82Tty5lkZeix36dUsvIt57nq2KJjo9Ki2FMLybZGJzjptCzvsK13p8dXGTXLVrTjN5YF0ibjf19rxiJwI5Sn9w3IWzuc5qyX9be17K1S+w0V1q6enUHhHzGU/DIsvX4Iz9r8O8zqww8ZRW/wWWZzHT+deA//cbRuB09VscJ3AcSQyEiA4ya+GoMPk0xDRFSWjEMRq2djiJeLQ5AHnVNZc17oOdKQUpk4r/F+7KYzYJfLuOswBdIVN/8bBgBlJbGKn6azvBHsY8F9G9kITPiZIFdSdGXpne6lUNoLjxToQ8Nhh47NSCdWws+ZDkLlV+YHi2wYy83JB6LAZBwhXyiwiuCyq2YdwUME9OXu85O3a24OF9MwwLgJUWpKIl1HiedGh/ENnsrl5lIhhQkspnEYsEC3VDHGDtKVCTDrCE/ZKZG7/qmSLfYfJ11doxmVx+hLlfT4D4NLqhU8vgL4FDpmAk1IoGtYddbnUVnL1hgz86jHqOgElsiYzPCtcCtfyHYkxLvT7dLOcmg7BYAIiisYs1e2EZI4FvKFE0GQ+zKYLbIUgAA9yUcEUtslX13BUukdUfFHrWdqUu7turR4boz4/9VFqDOOZSI7Tsg7AxNvXstcHGqf22sLb6kWX85DX32G3f11T0y+zeNG+zOvTi7dbKNZq0fnaLNf0NRb5Mxd2fNIGBQuUfCoGdxBaa5B29ChsntQ0XwaHhkHCRiVKq32PzLEUWGw+5G0vtjvmt/Njd8CEhwll4QhZLy+ImLnv9NUxVzUqr0LHTJbxqqVZMdk+MjJWfOn3OoIbh2UsJMcy3Z4Xoor2qlbHBE7RRedwCajpMJXTS5p9TGvEuW+A+7sttPu+XZRzCyW4GcH1MVBpI7jUsqI6Yh4fDcATcnNaEXTv8aB88KpbLTyC79nEfJ9Y0BaZPoJVe/msFFxCl0sado/0Ua+C5/5dI4qcg/xG/QOvBfVrEGhxofUcdPsKIa4ZjXbHta1cUnTyKSmt2anh1Li6YX4JUi8ifGEWpbvmajezrSWkTBH0an/OuvpjelNbTffK4YrB1CBzqNig4CRxI8yqL1vZjKW3gT0I/Q+sizS7nGaD7uh2bkIsWdOEMLCSnoeau1g+YV/tS+m6tpY9xxp72Z6xxaiQIOVQIDnGtA61ubGWGi3NinKeXFsC/2uZel/fgKaHR3n9T8H9ln+Hr2eoWbn+rOhArHAaxUYXARJhibG4iGw+KZftBubtMxcjGOa5XmxK6vC5YYtumdrd07WdkSv0obcgxfYn41iNGcZFAXe3U7moRiCmEDrQP/9LZF1SSuQEsBoH5pdLwDgJzl1Uyq4vqzwsQ2/OU/nFw589uWtpDu2mIycm89a3kEmNjj3Pzz0MCMGwy5DdadETIurwc1gb7HaHJMipbFIeQErFT7cpSADZCoPb6MVPJDgRvCYH8YyaK0vvahpd1d2ehgWCbwh4X1irPajX28VhSbdOUXcrgPO9KSk4UZ7+6kWgcWSbovGeEcgabx/9Ck89b2gHqE8FQWUYpdAwr98RAn7TWm9PPfCnc7pW13P5QvWtvDyd41rMbjekq8xEaHoB/+1bt++Ol8vzfee70vLi83ho0tL18UBxyGWvMefE6+U5mO4m/tZeEX9Jz7B/FRMNsEdOaUceV7sHV769VGYoWs9ZuKvWvnsGe1/e+ypTbrofOjHe9n6Ix7tbQN+tT9BazYpboEK9ch5mZ3GJFRWsefr3ruw4V9kOyKw3SA76suO4e319doc77F27m+I0djp1NQ15Zd54vPG3aJ6bGcqfxR3ybPmcOFFIxpkcLB77OJlSiGwdnaZGUccoyYT+xEqpQsD/r6lZ4aGikvlpP8oB7643MzfSzaqkYjBgdXm+kcloMSvwFr8Mk8lBYsyTjQB+DWra8Xb9C3/aTJuHmzbtqq9PJBmO8g6aA1URIjcjxmirRDjZ4Fxiy8VncMdOwqvAewATIp4BPrZ1oproJ2Xq167B90EdVkh9t8l4eb9eoQyvmT5w0CJjv/GwbzM5KEzLl0DjvyDb1aOKxILUEMtVP5KbNQlcFi9ooJmzX8OLLwzbQP1JI4WRhZfkcFpss89v7XwNmMEFpxIVdia8exCGkA4QArBRDnts1OiSIY/z8n5++kuFHA7BEoF7uFjKTFgrhj/hF0b6TGFjYR3yixMUXLs6MqNfRBESGE/5E9Nd2wRK9KV/Cjlw5nPd+GxdoPGtLO5YEt9f1xobwJPXjqxRciFlkc7P/xOy4/U/1BtfPDcxxCHHGxpw6+HrgNKxOpTRnhnhVi6QtxPjDT5+DeYV+dGQ2QaHB5CQPYeOESCyJvWXWWoPfm31pDUiH4nOkYKTHvBiIAnJkfLxSUVnImz9O/1ZOL8Z0I60u+gw4ff1ZzXuyqcBTYSdYIIlRFbNVg6ivmyi/U5+Ju1GOzAc7YcAfm4F47Wyj761i0RyDuVeRn6MDLHdQAENxLFlhEyQRzZQyjJULykcQH5EDrkfioObRRFCB60w+gfZCBdlhGbTQqwZBzmyytudY1cWN2xq+nC17ic23oDNmZksLEHkwWvK2hwKhWSSh0ZmEA2n/OVa/MuD9OGiBhrtJ8J+Dov6LVCR98CapKxcJjFVb4rOFTsWZ33+z3kIlV/oj8cmQ7w7L7YpKIirEMpmBFR/TNBMbOBY5ERMTe5XK9n8pQxNHC36/MzIj5NOVBpoEYYztV/NjJXyzjb50hJ4vZLaLE9HEglaex1W3GCHGHrjGG/PcKGVyi+6TXeUkPLKi/bYGVKKxvmD3SJ4Tg1zYPc0OUMgvPbOgP0euOFY0EIo5NRJQH+mJL9GTGLLz2AtVbEm8QCg8yinkMj9R4KOOp6V7qlfKc24mwJz1YOww+eGvLOvEq7w2lsHxA81gU8/U5Er/h3WeXuHU7X8Mq/YjqZbfd/FUZUvWlc8BATHGinxWSCltHuOpZhncM1WP+ark/CBx2ly9r9I7IeEkRM3v4nOBIsVADNTHiC3+Acs5uAlvsB5i/3twwt06wEVs9SmiR6u0S5jTWDEbttb6FdhO65Rb2bDvINf67I+Us9Gs02t+ai/FeBBMM46dZX7PbVHK58oStmf9XOESQRf9nQ0Svd9w5wb+V89QmgsECrgEaCK599+NlToJ/rYt5PO0cij5vHSpNpFQ+jWb/MMazogZSWqMysV+J3j4GIXQD3ZSmEeZ1yPzGOTm+/xF3hsWcMcxfid9ieeMa4k8/I+aL36ebiagfoJj4X1Vo9zXwItM/85Fm6ZIpZiAHh7RUcIqVDW2Aru6MENcL06MzcO25mJnNIXZZf8Z8NjM+xqMzYuy8JjUIHH6zntktpnDGlLa+XlaF42DUSbHxirdRU9kxW/PGHrvku0Pw8JRkoYW5Bg2xTzrSG0Yts2apUW8kIuOeSVcmLEU2vmevbafpJS4ugss+5jN6KLADwP08CpKJxzFapWORJa7O/OpYZvuziODPsr7x61diapF+Td3e5Hxj4vt92tlhn6rmzhooCdcjFx7BXe+WY7Zt2TXdbrtZX5N3XMmWVIw7VnMMGpZ9uujrzOcuWFIX7npnwj7x+41yw+CogsliaId8DMz4P3rzcxCvYxNcciC6/T4OXkiiJbu7ekTo7eVgzm7wVfJd9N913jr41akPUgqoqHRRqzjPpmuc5lhi8O192Xcx2MHiEJIAoXP/e1hoyuiCK47cOrK8eT2tEDh+8IJ4FHo5BhfKmOWWiDKKDZOj9e2bDMWhgTal9fvJbpBYgMWdOKDtlLEQwnMpmjUvEb8BmvI+WjJ0YOLCqlnu1ShDq5PHp9eqa8XlqhGKONgFvRtQcCls8mfvjvIc95w20kdLlRP+PIGQfTn3A94WjBlRmGAUbU99qnSONqUf0RKQt6dJLl9faPcFVn75NQCuZlmSZgwe+xRwLcRa/6ZkFBgaaboeZR5wghUOkxNehPt0k7rZYhXql65henCVPnXKqm2K1rKHxVDpD25xQeDzQB2RdpBMB6F0bXBm1AMWBxEU0pwSoS/7QipuRE79rUtnnhxcpmTkc+g+tw58lM9takMmTr8HeRkROKicZPanNuIT0Xlw3rmaqoT2CwgKDbuEIx+0LR06qbTuO6MdHVOJX1eclUSkB/VaVgrWrZ2zwJtTmkywQtrssHXmdWGcgJz2HUwOl+LcLVN5z2EmcpZCWK5ZKtvT8neUP80DfGhN8N58hCHRzw3ZFZ5FLqce6J8IkDauuv+qY0lOuLqbpJjyZyvCq1KCUfizbH4xJuv6EouNOTEK+j6CS/8EVYNNiQxUsZ6TufnQn8aEZtnSWWPf8OLcf7ACFNq3kvTA58o7aexz7GaYHeMfcCaFTjyJZ/r6/15J3iQK8IkZsRjWQeZ5e+APwKOdkLIQXmp6b44nczU/XllBou7LyFMXyMGqkXm8P5h4sKXUYHrlXcAPeey28g6Nt6hmOJ+GkHV4QPzvIPZ8IgQEf2MRX6Opc66lv0d3z1vYFoyf4PYzbmGNQ/Ou6KOd0aoJBOBcFJ4FpoYF5+eJschnq2BvBdeoIThYK8nAmV4BVZVIPlbnoarKPbN8XTDHZzW3mMlmTkeeXWM5Lpr2oAYgL/yOVtxWuW1+Gg0DdhrRo3/em4/+mj9ajb5eVeN8o2ErF1eRoQ3l85guLdT+u38P3C2sW8Ggv+4Hy/n/5C//ec4Ud54nvSxpDdp17Z/28rOR7xNtE/DyW5xbaTdPDYkwprWXF1gkR8KvWa+lUdR8WEapwqNcRS5V8+EJJIIo2NbfLKaHuHRRCQqrJc5zNSbu28l6GFgDZUsbKaRLyUjy1VeiFbYOX8qRaUICMRM99MRdOYprQ5mntyd1dxoAQJP2+Ao6gFo5zPxXGToZ1mInUIuK4Kruwe5z91EODBn5KNlwgjEV4PCZrr0Qy4ZHSfFBiLcjfnhozi+vDFM/50K+I3nLlz7kVz8lqHovbCXszIO2XlyydJDIRydAItYWpxVmQolZeobgvxmFTC4f1KL4zWzEXVNWWnYNR4Obx7Ye7ayYIMXjk7rDNig7AGyG5Rl0SKGlfgLw1ajqvJDygdT94mmvG2YyjlzKtJMYw/Ogl94RlnzI4K/6xENmOT9alOpb87xngqU9gaThD0wWHMyUvpnjVuMs9OY5bR2rkfTHy/dAqqNvQhAdrMXZ9V4wvu8UVSfSga053hBT9s32aO5hdNQsGhNm93COxDe3/YJUDjSZqUCmS2Fy7jfo8ToCFUQFY78NIduh3TUdkCLRVhg/rTTMvxSLByaCqv7KVe6fnGDIaS0o3mHL8SgEbB7gcfkk1BQoMYcjhD4DbNVkwHtPxep5fGePulrl/BEMnHfWgL6IDD1r4Aeer3JP649OjxBfgABLyR6br50U27ghl+CxPQDGbSTRgEMrZUFLJiSR6u26LRPgYE64i32ojKon2HmNRBS5ivZRFAnx7Pl51HzCLngs80ZfMfX/mM1DqKJOi0o/aDuwk4KO8ieBw3ZSgwJcbvoRAkPlX2G2JBS+XTKK6H0QNz4CS46/nECKR+qzRkeD1oAFU594sL3FKvOWI2NrfCuuUa0oBuE2EcQKgFGBNU4klOFQxeJ7MSx+LXYoXgu4IrEzmeIxO7/qp8b4a+XnrdfzRifbsp/GvikPgr8m5TH/06EmMzRGcOidMT0GA8KMK1EyUSIodEtIA7lKBF6u1bhY8XaFC8y1BwNkeBD2Cx1kvPPBw7Qgn/UeG/zg81FrABFhs8G4p6DJfH1zegcowh3PArUVLJibT2mwBo1Dy76jmEhfIpxZsSHOpzsEUni/ITWmpOY8QhF8HeBtwgWlh+FnLes/IihGaVKGQpugfCPSQsm8F1ek3IKtmgUxMzbbTLn/V2t9C3TTd+SOLV7H7cz05yTVa7xpd2og8n1c3NjGvNE+upX36mrNwFSiX/1g8TchN172h85W0JK+H+2R4oFmCfH/kZqL6UloCPfokEjTibUTg+GpLYECX4YjXNlE4SfCqNmYOODos7RvCPAHuvIhxMipv4KpqpFseBNs+4eSymh08rLX21th3SzUfFwbCIZj2A9WPfy4t12L6qHZ0189W/CH3cnVU31lZLeA8JD2icvZUmhugv/YIXpZ4iuo9AriAjb+KQqEVa6JD6jS7ggyoDFZHOkpXDBCkGQrP3n/EjOLKPYWRFqK878bQeF4UfK+/9vmrUVWTgXcIzPDtH8so42bQnulLPrkTQxMor1oizNCiFe+TBMjyngDhixnrR4Rvkskdin8hTD551mNA7O3XJnXlL3nSPwLALO1FBw9yrdSrMsbs+pY0AUTLRN5w9j7wiIHxSJXnMPI6RlHVn9f43cUkyauPvCKa0qPhMycwYyWoN4K4xAYWL31SYGQzp4UjH1s0+jvY4pzd36SQkugIKTt1acn8Y/rSXLrcOUjvY9gg6a726kb1KdA4QZpBupQrZAykmB4AAgENLAQCA/3+1jER3VE8wOXz5FD4x+evA4SCaY7QIJcebHCQgyieIi/S2s3SWDnbsP9pK4HsvP2DxY3yLgaWkn0sWJPdJnU9tKhsWDIbkqXh8ytLHZZ2ZnKAKsdHR0IgjEVF9Qpy0/HRk08hIcNOkITwL2KAWon+IF0AOuqUR4ZqAaNig3TPpAGg0RqcP2/WIv19bBrZTj0Z+fL2xd+I4QpcV/QCI8wVqaajLs3lww6EXDm4ZZoE1ZdSpLb6pddgozvHG7L5cPTF4Yys5hvvnElRecCxEPF0NAlF9g9x65BczNJF5PhdQ0xqND+cNUEANF/zDKPMLoQL5S7zKtrVGCosGwtnCCGv89QD5XPux2B4KDFFA637fQaeSr5Dhwzin4bSosjrfJ+UpFu+QbslxtZXGeuu3aWRDQ/E6ObJZ6JL3e2sODKg5O740dkdmKHohsb1g2hJmhHFlgLpROO4oQVlAi8iAwiipozwIOOIHwmADqsieyZCcgzpo6qjoZ1NNbLvJKfLhU3R/64wPsH6cqN0c8kt0YVOpu57u/nx2hpi8yA/0U2DpQKCQeDjYrLJ4/oDxiYCZAhLEDAo915kvb0bnsLbhKBq9OS9K2zv/f6g7019FDJs2wxVPEwkqjo4TAtaqYeLBOJbCb/PLTABhsvc/MaKfNZvrdS4DkWAyv/mPw9ecnhC4usCSafjW/tz/gaBYZ39u+M9NkVlfiM8j5u8LaftNT5ENT2YoCi2PEutF9VgebJ/FO0D3mBGztkjBrooQCh+vXZKYEnUL9MvnB4ePIUs09GcrNbhNSH4m40yZkUngdNArgo0LHRAVs3xdNyWFpc3EVDVnSy/0sMJ6FllZGkIvDSO97A53gP6zU+RN2RrJsZ0lUA9ZgssPZ/O0aYwC85cPV1JLE74oUOJBGRRQTmBTB0QE+5cSf33XzFyfdOGfsA3Y/TFZMgoatV1Ma8jx6ry8lGTtd/MJ6dYnK+/vY6RwdB2A6NX9/jS2XK6CH4uC8FAsGTCegkYUHqKF7y4Q+VJoO/74tSPus+gybETwiVJtIrSqkA2STrEktAroMq8Hq4QrCR2xedi4ae1peLCz7xTsEIyK4jwk6ALw2eTjhfYaD4aFGwadHRveSTkzjFrSC3FWDUnbBjrWMwPmoHxLSUCCXCH5g1VI5IRvccPPIjxokd/6+9Vq/IifS4tvdRJVEyVIhOMbRQNyRpc++alNp7kaExYbHzTUzRVA7OCz4fl/8HBy/INI0xnM91Yngg/Bp4jPsWijZxkwhW0eFpCP1GiwDLzvR8snH7fjx4T15a3Rgs+YGp/yXv7SX7UD6GQ8KvPJMXQtjdEQTPf65qq8ci5dOV4kE4WUhsX+xwGtGkmf+DJIwK9sV6dbm389t+3eSr1QKDmZiRoDJ52BiBdKCVh+2+iOX9bZUVTD53WkpV5wYval41IiLZabvJ2VyDA=
*/