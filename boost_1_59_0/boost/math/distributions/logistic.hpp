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

    #ifdef __cpp_deduction_guides
    template <class RealType>
    logistic_distribution(RealType)->logistic_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    template <class RealType>
    logistic_distribution(RealType,RealType)->logistic_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    #endif

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
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
*/