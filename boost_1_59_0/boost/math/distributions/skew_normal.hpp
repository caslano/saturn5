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
#include <boost/math/tools/assert.hpp>
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

  #ifdef __cpp_deduction_guides
  template <class RealType>
  skew_normal_distribution(RealType)->skew_normal_distribution<typename boost::math::tools::promote_args<RealType>::type>;
  template <class RealType>
  skew_normal_distribution(RealType,RealType)->skew_normal_distribution<typename boost::math::tools::promote_args<RealType>::type>;
  template <class RealType>
  skew_normal_distribution(RealType,RealType,RealType)->skew_normal_distribution<typename boost::math::tools::promote_args<RealType>::type>;
  #endif

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
        
        BOOST_MATH_ASSERT(d > static_cast<diff_type>(0));

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
    
    BOOST_MATH_ASSERT(d > static_cast<diff_type>(0));

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
    std::uintmax_t m = policies::get_max_root_iterations<Policy>(); // and max iterations.

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
    std::uintmax_t m = policies::get_max_root_iterations<Policy>(); // and max iterations.

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