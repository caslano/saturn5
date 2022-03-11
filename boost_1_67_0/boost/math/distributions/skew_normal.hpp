//  Copyright Benjamin Sobotta 2012

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_SKEW_NORMAL_HPP
#define BOOST_STATS_SKEW_NORMAL_HPP

// http://en.wikipedia.org/wiki/Skew_normal_distribution
// http://azzalini.stat.unipd.it/SN/
// Also:
// Azzalini, A. (1985). "A class of distributions which includes the normal ones".
// Scand. J. Statist. 12: 171-178.

#include <boost/math/distributions/fwd.hpp> // TODO add skew_normal distribution to fwd.hpp!
#include <boost/math/special_functions/owens_t.hpp> // Owen's T function
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/tuple.hpp>
#include <boost/math/tools/roots.hpp> // Newton-Raphson
#include <boost/assert.hpp>
#include <boost/math/distributions/detail/generic_mode.hpp> // pdf max finder.

#include <utility>
#include <algorithm> // std::lower_bound, std::distance

namespace boost{ namespace math{

  namespace detail
  {
    template <class RealType, class Policy>
    inline bool check_skew_normal_shape(
      const char* function,
      RealType shape,
      RealType* result,
      const Policy& pol)
    {
      if(!(boost::math::isfinite)(shape))
      {
        *result =
          policies::raise_domain_error<RealType>(function,
          "Shape parameter is %1%, but must be finite!",
          shape, pol);
        return false;
      }
      return true;
    }

  } // namespace detail

  template <class RealType = double, class Policy = policies::policy<> >
  class skew_normal_distribution
  {
  public:
    typedef RealType value_type;
    typedef Policy policy_type;

    skew_normal_distribution(RealType l_location = 0, RealType l_scale = 1, RealType l_shape = 0)
      : location_(l_location), scale_(l_scale), shape_(l_shape)
    { // Default is a 'standard' normal distribution N01. (shape=0 results in the normal distribution with no skew)
      static const char* function = "boost::math::skew_normal_distribution<%1%>::skew_normal_distribution";

      RealType result;
      detail::check_scale(function, l_scale, &result, Policy());
      detail::check_location(function, l_location, &result, Policy());
      detail::check_skew_normal_shape(function, l_shape, &result, Policy());
    }

    RealType location()const
    { 
      return location_;
    }

    RealType scale()const
    { 
      return scale_;
    }

    RealType shape()const
    { 
      return shape_;
    }


  private:
    //
    // Data members:
    //
    RealType location_;  // distribution location.
    RealType scale_;    // distribution scale.
    RealType shape_;    // distribution shape.
  }; // class skew_normal_distribution

  typedef skew_normal_distribution<double> skew_normal;

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> range(const skew_normal_distribution<RealType, Policy>& /*dist*/)
  { // Range of permissible values for random variable x.
    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(
       std::numeric_limits<RealType>::has_infinity ? -std::numeric_limits<RealType>::infinity() : -max_value<RealType>(), 
       std::numeric_limits<RealType>::has_infinity ? std::numeric_limits<RealType>::infinity() : max_value<RealType>()); // - to + max value.
  }

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> support(const skew_normal_distribution<RealType, Policy>& /*dist*/)
  { // Range of supported values for random variable x.
    // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.

    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(-max_value<RealType>(),  max_value<RealType>()); // - to + max value.
  }

  template <class RealType, class Policy>
  inline RealType pdf(const skew_normal_distribution<RealType, Policy>& dist, const RealType& x)
  {
    const RealType scale = dist.scale();
    const RealType location = dist.location();
    const RealType shape = dist.shape();

    static const char* function = "boost::math::pdf(const skew_normal_distribution<%1%>&, %1%)";

    RealType result = 0;
    if(false == detail::check_scale(function, scale, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_location(function, location, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_skew_normal_shape(function, shape, &result, Policy()))
    {
      return result;
    }
    if((boost::math::isinf)(x))
    {
       return 0; // pdf + and - infinity is zero.
    }
    // Below produces MSVC 4127 warnings, so the above used instead.
    //if(std::numeric_limits<RealType>::has_infinity && abs(x) == std::numeric_limits<RealType>::infinity())
    //{ // pdf + and - infinity is zero.
    //  return 0;
    //}
    if(false == detail::check_x(function, x, &result, Policy()))
    {
      return result;
    }

    const RealType transformed_x = (x-location)/scale;

    normal_distribution<RealType, Policy> std_normal;

    result = pdf(std_normal, transformed_x) * cdf(std_normal, shape*transformed_x) * 2 / scale;

    return result;
  } // pdf

  template <class RealType, class Policy>
  inline RealType cdf(const skew_normal_distribution<RealType, Policy>& dist, const RealType& x)
  {
    const RealType scale = dist.scale();
    const RealType location = dist.location();
    const RealType shape = dist.shape();

    static const char* function = "boost::math::cdf(const skew_normal_distribution<%1%>&, %1%)";
    RealType result = 0;
    if(false == detail::check_scale(function, scale, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_location(function, location, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_skew_normal_shape(function, shape, &result, Policy()))
    {
      return result;
    }
    if((boost::math::isinf)(x))
    {
      if(x < 0) return 0; // -infinity
      return 1; // + infinity
    }
    // These produce MSVC 4127 warnings, so the above used instead.
    //if(std::numeric_limits<RealType>::has_infinity && x == std::numeric_limits<RealType>::infinity())
    //{ // cdf +infinity is unity.
    //  return 1;
    //}
    //if(std::numeric_limits<RealType>::has_infinity && x == -std::numeric_limits<RealType>::infinity())
    //{ // cdf -infinity is zero.
    //  return 0;
    //}
    if(false == detail::check_x(function, x, &result, Policy()))
    {
      return result;
    }

    const RealType transformed_x = (x-location)/scale;

    normal_distribution<RealType, Policy> std_normal;

    result = cdf(std_normal, transformed_x) - owens_t(transformed_x, shape)*static_cast<RealType>(2);

    return result;
  } // cdf

  template <class RealType, class Policy>
  inline RealType cdf(const complemented2_type<skew_normal_distribution<RealType, Policy>, RealType>& c)
  {
    const RealType scale = c.dist.scale();
    const RealType location = c.dist.location();
    const RealType shape = c.dist.shape();
    const RealType x = c.param;

    static const char* function = "boost::math::cdf(const complement(skew_normal_distribution<%1%>&), %1%)";

    if((boost::math::isinf)(x))
    {
      if(x < 0) return 1; // cdf complement -infinity is unity.
      return 0; // cdf complement +infinity is zero
    }
    // These produce MSVC 4127 warnings, so the above used instead.
    //if(std::numeric_limits<RealType>::has_infinity && x == std::numeric_limits<RealType>::infinity())
    //{ // cdf complement +infinity is zero.
    //  return 0;
    //}
    //if(std::numeric_limits<RealType>::has_infinity && x == -std::numeric_limits<RealType>::infinity())
    //{ // cdf complement -infinity is unity.
    //  return 1;
    //}
    RealType result = 0;
    if(false == detail::check_scale(function, scale, &result, Policy()))
      return result;
    if(false == detail::check_location(function, location, &result, Policy()))
      return result;
    if(false == detail::check_skew_normal_shape(function, shape, &result, Policy()))
      return result;
    if(false == detail::check_x(function, x, &result, Policy()))
      return result;

    const RealType transformed_x = (x-location)/scale;

    normal_distribution<RealType, Policy> std_normal;

    result = cdf(complement(std_normal, transformed_x)) + owens_t(transformed_x, shape)*static_cast<RealType>(2);
    return result;
  } // cdf complement

  template <class RealType, class Policy>
  inline RealType location(const skew_normal_distribution<RealType, Policy>& dist)
  {
    return dist.location();
  }

  template <class RealType, class Policy>
  inline RealType scale(const skew_normal_distribution<RealType, Policy>& dist)
  {
    return dist.scale();
  }

  template <class RealType, class Policy>
  inline RealType shape(const skew_normal_distribution<RealType, Policy>& dist)
  {
    return dist.shape();
  }

  template <class RealType, class Policy>
  inline RealType mean(const skew_normal_distribution<RealType, Policy>& dist)
  {
    BOOST_MATH_STD_USING  // for ADL of std functions

    using namespace boost::math::constants;

    //const RealType delta = dist.shape() / sqrt(static_cast<RealType>(1)+dist.shape()*dist.shape());

    //return dist.location() + dist.scale() * delta * root_two_div_pi<RealType>();

    return dist.location() + dist.scale() * dist.shape() / sqrt(pi<RealType>()+pi<RealType>()*dist.shape()*dist.shape()) * root_two<RealType>();
  }

  template <class RealType, class Policy>
  inline RealType variance(const skew_normal_distribution<RealType, Policy>& dist)
  {
    using namespace boost::math::constants;

    const RealType delta2 = dist.shape() != 0 ? static_cast<RealType>(1) / (static_cast<RealType>(1)+static_cast<RealType>(1)/(dist.shape()*dist.shape())) : static_cast<RealType>(0);
    //const RealType inv_delta2 = static_cast<RealType>(1)+static_cast<RealType>(1)/(dist.shape()*dist.shape());

    RealType variance = dist.scale()*dist.scale()*(static_cast<RealType>(1)-two_div_pi<RealType>()*delta2);
    //RealType variance = dist.scale()*dist.scale()*(static_cast<RealType>(1)-two_div_pi<RealType>()/inv_delta2);

    return variance;
  }

  namespace detail
  {
    /*
      TODO No closed expression for mode, so use max of pdf.
    */
    
    template <class RealType, class Policy>
    inline RealType mode_fallback(const skew_normal_distribution<RealType, Policy>& dist)
    { // mode.
        static const char* function = "mode(skew_normal_distribution<%1%> const&)";
        const RealType scale = dist.scale();
        const RealType location = dist.location();
        const RealType shape = dist.shape();
        
        RealType result;
        if(!detail::check_scale(
          function,
          scale, &result, Policy())
          ||
        !detail::check_skew_normal_shape(
          function,
          shape,
          &result,
          Policy()))
        return result;

        if( shape == 0 )
        {
          return location;
        }

        if( shape < 0 )
        {
          skew_normal_distribution<RealType, Policy> D(0, 1, -shape);
          result = mode_fallback(D);
          result = location-scale*result;
          return result;
        }
        
        BOOST_MATH_STD_USING

        // 21 elements
        static const RealType shapes[] = {
          0.0,
          1.000000000000000e-004,
          2.069138081114790e-004,
          4.281332398719396e-004,
          8.858667904100824e-004,
          1.832980710832436e-003,
          3.792690190732250e-003,
          7.847599703514606e-003,
          1.623776739188722e-002,
          3.359818286283781e-002,
          6.951927961775606e-002,
          1.438449888287663e-001,
          2.976351441631319e-001,
          6.158482110660261e-001,
          1.274274985703135e+000,
          2.636650898730361e+000,
          5.455594781168514e+000,
          1.128837891684688e+001,
          2.335721469090121e+001,
          4.832930238571753e+001,
          1.000000000000000e+002};

        // 21 elements
        static const RealType guess[] = {
          0.0,
          5.000050000525391e-005,
          1.500015000148736e-004,
          3.500035000350010e-004,
          7.500075000752560e-004,
          1.450014500145258e-003,
          3.050030500305390e-003,
          6.250062500624765e-003,
          1.295012950129504e-002,
          2.675026750267495e-002,
          5.525055250552491e-002,
          1.132511325113255e-001,
          2.249522495224952e-001,
          3.992539925399257e-001,
          5.353553535535358e-001,
          4.954549545495457e-001,
          3.524535245352451e-001,
          2.182521825218249e-001,
          1.256512565125654e-001,
          6.945069450694508e-002,
          3.735037350373460e-002
        };

        const RealType* result_ptr = std::lower_bound(shapes, shapes+21, shape);

        typedef typename std::iterator_traits<RealType*>::difference_type diff_type;
        
        const diff_type d = std::distance(shapes, result_ptr);
        
        BOOST_ASSERT(d > static_cast<diff_type>(0));

        // refine
        if(d < static_cast<diff_type>(21)) // shape smaller 100
        {
          result = guess[d-static_cast<diff_type>(1)]
            + (guess[d]-guess[d-static_cast<diff_type>(1)])/(shapes[d]-shapes[d-static_cast<diff_type>(1)])
            * (shape-shapes[d-static_cast<diff_type>(1)]);
        }
        else // shape greater 100
        {
          result = 1e-4;
        }

        skew_normal_distribution<RealType, Policy> helper(0, 1, shape);
        
        result = detail::generic_find_mode_01(helper, result, function);
        
        result = result*scale + location;
        
        return result;
    } // mode_fallback
    
    
    /*
     * TODO No closed expression for mode, so use f'(x) = 0
     */
    template <class RealType, class Policy>
    struct skew_normal_mode_functor
    { 
      skew_normal_mode_functor(const boost::math::skew_normal_distribution<RealType, Policy> dist)
        : distribution(dist)
      {
      }

      boost::math::tuple<RealType, RealType> operator()(RealType const& x)
      {
        normal_distribution<RealType, Policy> std_normal;
        const RealType shape = distribution.shape();
        const RealType pdf_x = pdf(distribution, x);
        const RealType normpdf_x = pdf(std_normal, x);
        const RealType normpdf_ax = pdf(std_normal, x*shape);
        RealType fx = static_cast<RealType>(2)*shape*normpdf_ax*normpdf_x - x*pdf_x;
        RealType dx = static_cast<RealType>(2)*shape*x*normpdf_x*normpdf_ax*(static_cast<RealType>(1) + shape*shape) + pdf_x + x*fx;
        // return both function evaluation difference f(x) and 1st derivative f'(x).
        return boost::math::make_tuple(fx, -dx);
      }
    private:
      const boost::math::skew_normal_distribution<RealType, Policy> distribution;
    };
    
  } // namespace detail
  
  template <class RealType, class Policy>
  inline RealType mode(const skew_normal_distribution<RealType, Policy>& dist)
  {
    const RealType scale = dist.scale();
    const RealType location = dist.location();
    const RealType shape = dist.shape();

    static const char* function = "boost::math::mode(const skew_normal_distribution<%1%>&, %1%)";

    RealType result = 0;
    if(false == detail::check_scale(function, scale, &result, Policy()))
      return result;
    if(false == detail::check_location(function, location, &result, Policy()))
      return result;
    if(false == detail::check_skew_normal_shape(function, shape, &result, Policy()))
      return result;

    if( shape == 0 )
    {
      return location;
    }

    if( shape < 0 )
    {
      skew_normal_distribution<RealType, Policy> D(0, 1, -shape);
      result = mode(D);
      result = location-scale*result;
      return result;
    }

    // 21 elements
    static const RealType shapes[] = {
      0.0,
      static_cast<RealType>(1.000000000000000e-004),
      static_cast<RealType>(2.069138081114790e-004),
      static_cast<RealType>(4.281332398719396e-004),
      static_cast<RealType>(8.858667904100824e-004),
      static_cast<RealType>(1.832980710832436e-003),
      static_cast<RealType>(3.792690190732250e-003),
      static_cast<RealType>(7.847599703514606e-003),
      static_cast<RealType>(1.623776739188722e-002),
      static_cast<RealType>(3.359818286283781e-002),
      static_cast<RealType>(6.951927961775606e-002),
      static_cast<RealType>(1.438449888287663e-001),
      static_cast<RealType>(2.976351441631319e-001),
      static_cast<RealType>(6.158482110660261e-001),
      static_cast<RealType>(1.274274985703135e+000),
      static_cast<RealType>(2.636650898730361e+000),
      static_cast<RealType>(5.455594781168514e+000),
      static_cast<RealType>(1.128837891684688e+001),
      static_cast<RealType>(2.335721469090121e+001),
      static_cast<RealType>(4.832930238571753e+001),
      static_cast<RealType>(1.000000000000000e+002)
    };

    // 21 elements
    static const RealType guess[] = {
      0.0,
      static_cast<RealType>(5.000050000525391e-005),
      static_cast<RealType>(1.500015000148736e-004),
      static_cast<RealType>(3.500035000350010e-004),
      static_cast<RealType>(7.500075000752560e-004),
      static_cast<RealType>(1.450014500145258e-003),
      static_cast<RealType>(3.050030500305390e-003),
      static_cast<RealType>(6.250062500624765e-003),
      static_cast<RealType>(1.295012950129504e-002),
      static_cast<RealType>(2.675026750267495e-002),
      static_cast<RealType>(5.525055250552491e-002),
      static_cast<RealType>(1.132511325113255e-001),
      static_cast<RealType>(2.249522495224952e-001),
      static_cast<RealType>(3.992539925399257e-001),
      static_cast<RealType>(5.353553535535358e-001),
      static_cast<RealType>(4.954549545495457e-001),
      static_cast<RealType>(3.524535245352451e-001),
      static_cast<RealType>(2.182521825218249e-001),
      static_cast<RealType>(1.256512565125654e-001),
      static_cast<RealType>(6.945069450694508e-002),
      static_cast<RealType>(3.735037350373460e-002)
    };

    const RealType* result_ptr = std::lower_bound(shapes, shapes+21, shape);

    typedef typename std::iterator_traits<RealType*>::difference_type diff_type;
    
    const diff_type d = std::distance(shapes, result_ptr);
    
    BOOST_ASSERT(d > static_cast<diff_type>(0));

    // TODO: make the search bounds smarter, depending on the shape parameter
    RealType search_min = 0; // below zero was caught above
    RealType search_max = 0.55f; // will never go above 0.55

    // refine
    if(d < static_cast<diff_type>(21)) // shape smaller 100
    {
      // it is safe to assume that d > 0, because shape==0.0 is caught earlier
      result = guess[d-static_cast<diff_type>(1)]
        + (guess[d]-guess[d-static_cast<diff_type>(1)])/(shapes[d]-shapes[d-static_cast<diff_type>(1)])
        * (shape-shapes[d-static_cast<diff_type>(1)]);
    }
    else // shape greater 100
    {
      result = 1e-4f;
      search_max = guess[19]; // set 19 instead of 20 to have a safety margin because the table may not be exact @ shape=100
    }
    
    const int get_digits = policies::digits<RealType, Policy>();// get digits from policy, 
    boost::uintmax_t m = policies::get_max_root_iterations<Policy>(); // and max iterations.

    skew_normal_distribution<RealType, Policy> helper(0, 1, shape);

    result = tools::newton_raphson_iterate(detail::skew_normal_mode_functor<RealType, Policy>(helper), result,
      search_min, search_max, get_digits, m);
    
    result = result*scale + location;

    return result;
  }
  

  
  template <class RealType, class Policy>
  inline RealType skewness(const skew_normal_distribution<RealType, Policy>& dist)
  {
    BOOST_MATH_STD_USING  // for ADL of std functions
    using namespace boost::math::constants;

    static const RealType factor = four_minus_pi<RealType>()/static_cast<RealType>(2);
    const RealType delta = dist.shape() / sqrt(static_cast<RealType>(1)+dist.shape()*dist.shape());

    return factor * pow(root_two_div_pi<RealType>() * delta, 3) /
      pow(static_cast<RealType>(1)-two_div_pi<RealType>()*delta*delta, static_cast<RealType>(1.5));
  }

  template <class RealType, class Policy>
  inline RealType kurtosis(const skew_normal_distribution<RealType, Policy>& dist)
  {
    return kurtosis_excess(dist)+static_cast<RealType>(3);
  }

  template <class RealType, class Policy>
  inline RealType kurtosis_excess(const skew_normal_distribution<RealType, Policy>& dist)
  {
    using namespace boost::math::constants;

    static const RealType factor = pi_minus_three<RealType>()*static_cast<RealType>(2);

    const RealType delta2 = dist.shape() != 0 ? static_cast<RealType>(1) / (static_cast<RealType>(1)+static_cast<RealType>(1)/(dist.shape()*dist.shape())) : static_cast<RealType>(0);

    const RealType x = static_cast<RealType>(1)-two_div_pi<RealType>()*delta2;
    const RealType y = two_div_pi<RealType>() * delta2;

    return factor * y*y / (x*x);
  }

  namespace detail
  {

    template <class RealType, class Policy>
    struct skew_normal_quantile_functor
    { 
      skew_normal_quantile_functor(const boost::math::skew_normal_distribution<RealType, Policy> dist, RealType const& p)
        : distribution(dist), prob(p)
      {
      }

      boost::math::tuple<RealType, RealType> operator()(RealType const& x)
      {
        RealType c = cdf(distribution, x);
        RealType fx = c - prob;  // Difference cdf - value - to minimize.
        RealType dx = pdf(distribution, x); // pdf is 1st derivative.
        // return both function evaluation difference f(x) and 1st derivative f'(x).
        return boost::math::make_tuple(fx, dx);
      }
    private:
      const boost::math::skew_normal_distribution<RealType, Policy> distribution;
      RealType prob; 
    };

  } // namespace detail

  template <class RealType, class Policy>
  inline RealType quantile(const skew_normal_distribution<RealType, Policy>& dist, const RealType& p)
  {
    const RealType scale = dist.scale();
    const RealType location = dist.location();
    const RealType shape = dist.shape();

    static const char* function = "boost::math::quantile(const skew_normal_distribution<%1%>&, %1%)";

    RealType result = 0;
    if(false == detail::check_scale(function, scale, &result, Policy()))
      return result;
    if(false == detail::check_location(function, location, &result, Policy()))
      return result;
    if(false == detail::check_skew_normal_shape(function, shape, &result, Policy()))
      return result;
    if(false == detail::check_probability(function, p, &result, Policy()))
      return result;

    // Compute initial guess via Cornish-Fisher expansion.
    RealType x = -boost::math::erfc_inv(2 * p, Policy()) * constants::root_two<RealType>();

    // Avoid unnecessary computations if there is no skew.
    if(shape != 0)
    {
      const RealType skew = skewness(dist);
      const RealType exk = kurtosis_excess(dist);

      x = x + (x*x-static_cast<RealType>(1))*skew/static_cast<RealType>(6)
      + x*(x*x-static_cast<RealType>(3))*exk/static_cast<RealType>(24)
      - x*(static_cast<RealType>(2)*x*x-static_cast<RealType>(5))*skew*skew/static_cast<RealType>(36);
    } // if(shape != 0)

    result = standard_deviation(dist)*x+mean(dist);

    // handle special case of non-skew normal distribution.
    if(shape == 0)
      return result;

    // refine the result by numerically searching the root of (p-cdf)

    const RealType search_min = range(dist).first;
    const RealType search_max = range(dist).second;

    const int get_digits = policies::digits<RealType, Policy>();// get digits from policy, 
    boost::uintmax_t m = policies::get_max_root_iterations<Policy>(); // and max iterations.

    result = tools::newton_raphson_iterate(detail::skew_normal_quantile_functor<RealType, Policy>(dist, p), result,
      search_min, search_max, get_digits, m);

    return result;
  } // quantile

  template <class RealType, class Policy>
  inline RealType quantile(const complemented2_type<skew_normal_distribution<RealType, Policy>, RealType>& c)
  {
    const RealType scale = c.dist.scale();
    const RealType location = c.dist.location();
    const RealType shape = c.dist.shape();

    static const char* function = "boost::math::quantile(const complement(skew_normal_distribution<%1%>&), %1%)";
    RealType result = 0;
    if(false == detail::check_scale(function, scale, &result, Policy()))
      return result;
    if(false == detail::check_location(function, location, &result, Policy()))
      return result;
    if(false == detail::check_skew_normal_shape(function, shape, &result, Policy()))
      return result;
    RealType q = c.param;
    if(false == detail::check_probability(function, q, &result, Policy()))
      return result;

    skew_normal_distribution<RealType, Policy> D(-location, scale, -shape);

    result = -quantile(D, q);

    return result;
  } // quantile


} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_SKEW_NORMAL_HPP



/* skew_normal.hpp
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
*/