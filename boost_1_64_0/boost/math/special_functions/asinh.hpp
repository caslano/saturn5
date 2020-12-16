//    boost asinh.hpp header file

//  (C) Copyright Eric Ford & Hubert Holin 2001.
//  (C) Copyright John Maddock 2008.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ASINH_HPP
#define BOOST_ASINH_HPP

#ifdef _MSC_VER
#pragma once
#endif


#include <boost/config/no_tr1/cmath.hpp>
#include <boost/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/sqrt1pm1.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>

// This is the inverse of the hyperbolic sine function.

namespace boost
{
    namespace math
    {
       namespace detail{
        template<typename T, class Policy>
        inline T    asinh_imp(const T x, const Policy& pol)
        {
            BOOST_MATH_STD_USING
            
            if((boost::math::isnan)(x))
            {
               return policies::raise_domain_error<T>(
                  "boost::math::asinh<%1%>(%1%)",
                  "asinh requires a finite argument, but got x = %1%.", x, pol);
            }
            if        (x >= tools::forth_root_epsilon<T>())
            {
               if        (x > 1 / tools::root_epsilon<T>())
                {
                    // http://functions.wolfram.com/ElementaryFunctions/ArcSinh/06/01/06/01/0001/
                    // approximation by laurent series in 1/x at 0+ order from -1 to 1
                    return constants::ln_two<T>() + log(x) + 1/ (4 * x * x);
                }
                else if(x < 0.5f)
                {
                   // As below, but rearranged to preserve digits:
                   return boost::math::log1p(x + boost::math::sqrt1pm1(x * x, pol), pol);
                }
                else
                {
                    // http://functions.wolfram.com/ElementaryFunctions/ArcSinh/02/
                    return( log( x + sqrt(x*x+1) ) );
                }
            }
            else if    (x <= -tools::forth_root_epsilon<T>())
            {
                return(-asinh(-x, pol));
            }
            else
            {
                // http://functions.wolfram.com/ElementaryFunctions/ArcSinh/06/01/03/01/0001/
                // approximation by taylor series in x at 0 up to order 2
                T    result = x;
                
                if    (abs(x) >= tools::root_epsilon<T>())
                {
                    T    x3 = x*x*x;
                    
                    // approximation by taylor series in x at 0 up to order 4
                    result -= x3/static_cast<T>(6);
                }
                
                return(result);
            }
        }
       }

        template<typename T>
        inline typename tools::promote_args<T>::type asinh(T x)
        {
           return boost::math::asinh(x, policies::policy<>());
        }
        template<typename T, typename Policy>
        inline typename tools::promote_args<T>::type asinh(T x, const Policy&)
        {
            typedef typename tools::promote_args<T>::type result_type;
            typedef typename policies::evaluation<result_type, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy, 
               policies::promote_float<false>, 
               policies::promote_double<false>, 
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
           return policies::checked_narrowing_cast<result_type, forwarding_policy>(
              detail::asinh_imp(static_cast<value_type>(x), forwarding_policy()),
              "boost::math::asinh<%1%>(%1%)");
        }

    }
}

#endif /* BOOST_ASINH_HPP */


/* asinh.hpp
HrOuxjzybXgvjM2YjFh/5DaEe3cw2G+c7wj4OM1ajQWTnpwINlz2/6D9VI5vBjSQ/c45xkJ6/s+YfzmPXYLc5OxbCL0he+HL0X+yT7MSrBLH/DN0lj2KtfAhz6EbjLlycSxbMVZ6aKexoFwj9kKXNuz3EMbK8/Qx2MlvjJxGbhl57F/QtAzrfBmaurnmN/6rEedxF7nJ+7I41sIB2f9DHwxl9gI+9nA/v4WdvItJUsdq+T/OLaUxr7x3TmfMt5Ht3oWdfA+b1Zhf9hhzGvPIOsqLsdIHBY1F5Tf+i4HJO4xSxgJyf1DeWEzOFVRGbvL85jEWOc52tcByMquPfGX/uQnsvmO/zeHjCevcGhqsY78djIVn8tguiHko90tPY+6n3OP9kO8mZoMQX01mwzGfT/b/wFrJ+T/M9xevhU9hJ2c6psOugOz/GQvKM84CjJV3WV9Cqxms6TLYzeaYv4Muq+T8H3rjAa+PNch3Nuf2G3wMkf0/Yy55ntliLN5H9v/QV5fl938xn+h3EDHLd3xHMVY0OAUf19nuvDHHEI4lZsz5ljW4jpq3Zr93MF8HHnsf8UU5j3+Rr5y7eY6xoukb5DGBWeK6pn1bni+FMa+bc0trLKfsl2Qw5u7NY7MYixZilsNYqCX3UB74lW8a3geTc1BF6+JazLG4Md8A9lHOWHAk98sHyOOo/P4v4uvKa7CmMf8sjqUexso7+sbGXA6e72PEvJDHtkJ8r9iuPezkOa+zsYhcO3vA7wse2xcxy7PaQGPOFex3mDFHK7YbjbE/cM0D8Cv3elOMnZRvGT+HpjPYx2z4rcDaz0eN+vN8i+F3BMfytbFlfvbxP8Qyi+NbYSxWjtflauRWnX38ivhqy/6fMd/hBGKbweQM6XbUsgqv1d3Q/gj7OIC6ybNuFH0v35ichC4D5Pwf7IYyu2TMM4jzvYb+k/PFt6FBgO3+MRafy+wR9GvF/fwMrBH30Gv0pPzNS1TP/LbhHk9uzCv7a2mMBauzpumNuTuy38zGAq/k//8zFpd3gS6MlWfOAsZ8l1nTIsZc7XlsSWMR+R3UsvArzxqVMHYgsw+Rr9wD14BdRe7TumDvs99GxqLy7XUz6BLjfmlpzDNMzv9BU3n32QmxZGftu9fDu3Lu+z7Q6gnH7Md8sqc6FBrIdWgUNJ3O8Y03FpPrwWTk1p3HfgYNZrLdLMzXQ87/QYMlrNUixNyU4/sKPjawBt+iljmZ/QC/z1mDVf/1Bvv9BXat2O4PY2F5htiEfCszi6BG8vdyF+rxO9vtNxY6yz10BLkV574/gTxkvrOI+TVrehFje3MeV6GL3P/dwpqZzexvY45j7OMhai5nTp5ibIDZK+SWgXNLqI/vnf/P3pnH+1ylcfx3N64s2RJRXaWZtF4VaiZ1KU0SLiGKkBZrLiE0oj1JLjJRCjUqlaJ1WoSKsuUqSym6ifYm2iOaz9v385ucM3/NnzOve18zr9P3+Z7z7M/5nvOc5/hVD2DlBMuLcrQVgUX1TVUFm3V8CDtIsMLobOIQwXZE+8HDoRvVeTQQrOS7UC8NwVcYynuCYPnnhWNPBl+0pztVsILikG4zwRaXj+7/QiOah/4iWFG0ZjgfOS4Lfbw9Ooj+va/OgpU+FY69WLBUdgjrSb9dIexyeO4a8tcPefuEvjaIfqOj+7/I1jKq/6PfkKj+D56jOLoReV+O8n/Ie0pU/we+aI8zGbqRHHcjW2TLGYy9NORvtmDzW0b1f+jquewA9hg8XxLqYL5gPb+K6v/QVSTbi4yNcvqL4K9rlP+Dv6jWarlgxZFvvAW+KAfwDrDo33t4F/6i3MNmZDsp1OlWYKNDnj/FHm0zAthX0Lg=
*/