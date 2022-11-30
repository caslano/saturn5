//    boost atanh.hpp header file

//  (C) Copyright Hubert Holin 2001.
//  (C) Copyright John Maddock 2008.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ATANH_HPP
#define BOOST_ATANH_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

// This is the inverse of the hyperbolic tangent function.

namespace boost
{
    namespace math
    {
       namespace detail
       {
        // This is the main fare
        
        template<typename T, typename Policy>
        inline T    atanh_imp(const T x, const Policy& pol)
        {
            BOOST_MATH_STD_USING
            static const char* function = "boost::math::atanh<%1%>(%1%)";
            
            if(x < -1)
            {
               return policies::raise_domain_error<T>(
                  function,
                  "atanh requires x >= -1, but got x = %1%.", x, pol);
            }
            else if(x > 1)
            {
               return policies::raise_domain_error<T>(
                  function,
                  "atanh requires x <= 1, but got x = %1%.", x, pol);
            }
            else if((boost::math::isnan)(x))
            {
               return policies::raise_domain_error<T>(
                  function,
                  "atanh requires -1 <= x <= 1, but got x = %1%.", x, pol);
            }
            else if(x < -1 + tools::epsilon<T>())
            {
               // -Infinity:
               return -policies::raise_overflow_error<T>(function, 0, pol);
            }
            else if(x > 1 - tools::epsilon<T>())
            {
               // Infinity:
               return policies::raise_overflow_error<T>(function, 0, pol);
            }
            else if(abs(x) >= tools::forth_root_epsilon<T>())
            {
                // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/02/
                if(abs(x) < 0.5f)
                   return (boost::math::log1p(x, pol) - boost::math::log1p(-x, pol)) / 2;
                return(log( (1 + x) / (1 - x) ) / 2);
            }
            else
            {
                // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/06/01/03/01/
                // approximation by taylor series in x at 0 up to order 2
                T    result = x;
                
                if    (abs(x) >= tools::root_epsilon<T>())
                {
                    T    x3 = x*x*x;
                    
                    // approximation by taylor series in x at 0 up to order 4
                    result += x3/static_cast<T>(3);
                }
                
                return(result);
            }
        }
       }

        template<typename T, typename Policy>
        inline typename tools::promote_args<T>::type atanh(T x, const Policy&)
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
              detail::atanh_imp(static_cast<value_type>(x), forwarding_policy()),
              "boost::math::atanh<%1%>(%1%)");
        }
        template<typename T>
        inline typename tools::promote_args<T>::type atanh(T x)
        {
           return boost::math::atanh(x, policies::policy<>());
        }

    }
}

#endif /* BOOST_ATANH_HPP */




/* atanh.hpp
WQvEe5TW8j0Hn1tIK9JY7R7yD0Onk6VElmc6jpz1fhRxRZd9IO/DNVR/EOSqh1Q5SvI3VksdKhgbZaGXn0uXfFPRiY7cjUnLY2skhnPMNDYSKmC9cmQcel5tZaRN7ipEIKYT78WDajFR5tPrJnW0UAg52qP5bVPU77TN06OpuihPNNCdA4kTynUCjlkBglbThbP8qEI8vkGIquYgTTdf5BTOvMnQ2bSfMqJUpFPtR28yqYbwi1ICkXzC55VQfs7ROiLQ3E+heJGLnBU1xr56/1soJfT54HtERX33nvYYTnVFPBkSMRzvpv3VBe6Dg0Q6u6NlVaQYO8lr14gIWy6TFG4Ji5RwkH9xt5e7BXmGySZp2rNEaZ3SqYiujUdXMBhGXZXgoOZZiyAwd6lKol4KE8JBkHRc26sWIEhwKXVk+zEA7zMOzvp0JJLlKgzmRwIL4Oh78yaLKjzrFsxcVXljZSlXrlEgF1LKoEFTFA2zVSi8FEX7778xNM9bRl4kT4oIwRWYTtfSaKxo5go5NCpSYNrSZqrWzxZoqnlZwtXJxpoikAtk6tY3UapBK5E3Co8IMkrP0cW7QqqidK3S60yd/2642Rhu3PPjzACZmLFL3TirVi1KkNT2ans4vehzBcTkyrZ64yYHKlmIOShnoTmLJN3+GlhLF1NScpvuLJAAXOwEJqWsn+QFPPCWBG0E8+1zrKr97BAffvk4E7rKINwxj+XAO4pYatHOBAVIdt/4FQCKvhFaLzD7klf+7/zVKJu1aYa0C/OMasBYxXKrsKhmapInLZhISwKxPm9ZKmuHY6ICcMLWzCmk7o5duJFWKnDqxqpUkpjzeJErulyMKm+2ytTgj8mtXETok9bM50yttpjKBA8yvLOzPleQZPOcQUH9HJ6R476bq9GyvfjDz4Vp+j1SRHVqPSA6zfakERzshTCvIJRiUJMaVSE8p059nZ/CUnHUK35GpmszW8wsc/gEhYGBAg+6mIszbZXnSsnJ0ZbdNmishYckdr7poDwobbqOsgkS74zIJxEiBHruQ7RtvR8Y6ml8mruTXuB/jz1hhn+yjAWp/zmSrenkg1KAeZXGOdrMfrGPlZDKYbOevFDXOT3lGLQICXjN5kOJkWQY0nT6JsLmM5YIWsp+alBQwQKTrIuTQ0iCv0YbiRUnXVV1ntXKytlJ1wd0Mc0hFafKbmQkv8GqqyLILnxqjkUGJaHi8drb64c+OOOcWyQ+GfSnIzgQitl7QPo77blZCzGacGvH0JoDim3EPJpnzV5Uy+X47LW4XXmFvjV5pXfvtb7Exe9GheV7SgYjiRHcTiKsbB6HZ8EavEY99UQwmvXX/qpdx/1PRLqsxahKrjHcPmwqXsa79BPMqffI+ftHitHXVU4C+cP1AvTqyu8fIVSv/wK/1A5N3FPWDbNOBpqi8D6tPv16UvBFUkKmIKS2QivWPfLK6Yotp4GAVarOC1Ei96vOOe6pTkFuzv26T+BOc53pys7rSWF0IRnHS3CpKd4CEnwMxK9tlTSslFhNPFmyA999+3lZdvKi2m2O5ehzWDTXtQmygvILyuoziL8vEM+/e+bpHqJAE+9vSlLSGpriyZCdm0yLp26NQKp7t6cOngKBDvidBk5IBCqv/YBo9Cf6lvP3+w+6KX9DEH/5P/H78MwEQan6CbT/oRlwfu0/QKmAoeDAwMDtX7/ACYmJAhmRMSlzV4qImRE4oce/Xs8DZqkh7bGQCjma5l4YktfPsu1IQHR0f6IR1z/BADrSFw8KNB8D59uABYoLsc0jn7XVrR3rXyqbCOvlkvezkxPHDpLeU9rbsWdcs8+uxanfJFQYWJyT23pS0XsypFLbH/CUgeARjW8j3qOb0ppW76/iC505juMhEy+Ts2pPtAGa4NymRjuaY24akXsLIziiMOLrIF9aIBI6Hf3rAtc5BXuiKRhtotTLZNQ/97yIDfqNSDOhPrIODty8NNcuZOOy6Vwb2ExiCPWs+pf6RSGsj/6yLH6QfYzdrZmHaT39tLENT3KsC6RsxFgExEvEOxoeoo84l7BvApq8evltspFwS5J6oHk7XcY1ltqvPe/jo6tr+Z54et710wX3372LeXZILMb6VWmcPPrH4sqrZ3aaNCjOmOMtRkrXFq7Ymu+ixgriDb2bFl6AwPHS9JXSrbrPYpvWF1QdU9YKNmBAe3JYKfKliH/d+IYiZ4/VJBn5V03dUiSc7Z3B5Y3JnSMKJE3fcaOikAnZL+ok9opOQm5Rg+I3XUtzFZDgHROJ2amb8papvkmQMTwDCiVjcfhaLHQQm0GbSvyo7ta2fskLxJuZmCTguLBXd6F45J+5GuXBoWOR8sGC7672xrIDiFajDNPcoPeKnvQr8Zm5GJIDTsxq8WIITEwed+98DVPDfu0s5N3PT81QLyZwHgJnnXjgOB9kPAFX+UsYTRYpkq5C0k7uXf63AmD5g1hNyb792NmIyKV20ZFsOP7f0WlSh2wdo34bYrf/9N8pZKDCJjc7Un9eBPl2el4MSE/OF8yF0cYu2NAvDqnULryIw5lahy6ijLHTvfB243vpdy2J570yt+a/dznqAze1hEGYXQLTkEgeHaQFyLYtK2Trm/ZF0k+HzhN9fVwnoN8u1WMX+En+19IN8OPefLdIq/sMfEL6hU89U6T30cI2AP2yvS07HJiJw8mosAZHE44JLT2KuTmOwIhYVbZkYXBiOh60Ef4FF5GRZCrNhw5JsEZRgPTq4n02UeiITXbGK/JnZzyXpkLd3GGB8VotTlrpopH9Gpd1/UXztQ16WC88Zqi2wkSZjYs4PbPdNgTU0BDYDj4fsucEI/R6WtKh9etcgvGrVz9iGOvLLM17ui5K93iBgrSdU+YP3I7l6K7IOQ6RIj4zreSV1AUSS2sKJ2bfCJzrqwD2jHD6jYUcs4hRpWaGPOBUnfjsLqgm3PFs6R2CJBPTy9YBXdVhuZnoJqYajzkJpEJmFMPCKjkdU0PLlbCzv5x40qd0O9Zw0cDNV/cq032TOJxVqNUn+p7YTrL3eXIkNt/DxZ543ryuKII27bieJGvQayEwn0nlKScbGHXR58RzbHvvDIhvupNJqibcR8TCBB3ED4wa8zngWfpTyz5gp6tjkOiz6uQlfGEq26xLwYlx0THZgUgx3dzmZjSubbgspr1SPpZwclV68fi1UF1sD8U6BbYU9t9dz8aN6iqZqMH08qrWknQxMu85/0XTXMkanYhWgHJGozZC+O57g6+sp2fwPYMeE+cZ94Zkuu7jmyFunp+LJ8b7L29eGXUxkxsCGI9aQJCXezl55TQ+tvDuvdIEmY7SV+ye7/FKgDaDc1N/5l4tylIsg5H/jmRXeVMYhg0hLnVn7DuN4H8toDxaHK0fSNbf5iVwaVmE4JUSuFMMlGq+7XuPdE1qeEYlD+wPj0i/fwsGNf4EgvwDQjliUq5xpf//IyGn/OdA+53fjhHEQALS936hN/5TR9wvUAMAjt9xzMHU+qTQst9rWvTrPpfxn4ZCSEux9syI0Sqb+/YMAJWLzLqi2hH3DKEeOe7XwMuac+iINrfWK1nDCE+ViAAzg2wJxjGY/PlJV8PK6PD0VldlJCxoFe0OAh2W76yOAU3gFZQtxsH2yHToBgCcVAT9AIzwKhgZH6vfcJFFZ+IVSQRQ9Ylb4BOvjUIPiHmuJY4pP2FhKGSpDtx6gwweV7lq+vkmcAq0JKrsM1el7pFlVx0JfZs9zLX3L1z7fpXbIyn0Kbqp7VxYjvQCTfffKNZfsSl1fwHxaE2c25CFc9+Sy5/YIoWf9BQ2O6Y9dr0dLN5z3EbJtMeey6iB59crtPBvEmwSf4Ai8xc0jxPnn88OzO87lVNSaX+hIsROq7REEYwXlrheeEYo0Tgw/TKui4ULTWso7kJAdKQ3fV1iWqdoViYJ18PV7PYvIYD1io4nn6sY9BwT8EZag02h5jR6SmmpOv2jV6wr8Xa2pD8O4n40JvOwY/wf3nJ0xpo/X25wdNPLtZDoUamIqiw1Kgzf9haFGS05AFWsGXQNs9r25wsFl3ahlqUXiExPjUjq0zyGdy73hKLWka/PV4Nw7dOhgignWAfkSmqednsD+PoO2o2sFG812Q3OeHabFhTdZrw9JSvQWKWyGXNVliaXAk3apmuCdSF3fsRAQBWSWHs0qaM+oHA0/T51OZnRjR/VuaK/pBO5/swHgsgb6Q2ASQ8qb5LTz+NQR2SXWQfEA25JU0vTHAmrt2QJXcCQzPojqtvGMHW8z18OknVpcpj4LQ+CiRWo0DS5nJx63SGS+rYo7QLoNLV48w+0AN8JpN7SWhetWvy8dyoFaboISqt8vcvVYUxFETU5DQJC9f5BSe8v7a5u1achpzWSZJFqCkQW1Rz3DMoQGgx8v+r22jBxl4voOmqSdHZ8Wo50v7e+VAg/5VyIp4RbHkadGJMxlmoxDg9Ok5Rm8GTGx0EaCcey63Q2KfVCX/4jmFXszPlkX5hLMq+7QqCEA677RvIx8yDhO82TJWFoKRRYZfUwKbFk/W2eLdNz/ZG1v0o6lAtBcxtlceGgTndLpj6Ck6XNJL2Vjkuy0hq7Il8syN0jm1UN6NVE9bPX0XXmvvt+LhvCIlpa96JHojmTpSEB5zfqoES5mwc2xnhrzUAq3382GluFUXHORmsDGjBbMQ8NslA1Qea3Gs2QOcgYtUntKWKE4vIJEEwXqEWLxStx9nG7oH1tJ440XwHlzuuMjVsxLcYmEpgaA4KXwermrd6rmVlYGtpQRDCTHTdEeGZcVazaFG4OY/WeKBG+ClUbLkufQDj6J9Y5JldJbGP1ODoN/yXV48WMO3rXQIJT1QVU97huSYhwUHapPl2BJBA6vft8fXgVgoYme4x/s3oOU4HsiMa76naP4jpXWxF4eSIqp3eO1+/G4CP9QcKD51cDAgD+wND+f3yu/wUAiPMPkYmIApmRqRrHOFfPZl6SkCkhOrHIP1jQCma5MW1nmXPIoRJ0qphXQN7Pmu0yIsA5/6A82uigdQBX7OzV1ZWiUQigAO5jAgq/VlwS1MNcxv9Q9syW/ZL10Z7+j6xvUgp1nKYaXZc9Ls6fu1DOlVkw3/7jzzXvn5V9ExR9yMFIX+vh97PEj1c2oNd3deKVlnzi22d5/3+UclRVNCXj6q/g3G+40ao4Zv7VovvP94Q7WtvFtkk+YYsksg5DfHPcJnisdUANGUKfnHS8+o1t5GLbJfbWndcb+sixvORH4gIyJ/wfxPEmckCTTmla/GWuN0VgmFyeMquNhusn5AvPYRHGnFk0o0KjVi+9thInAcQfkGGY8KB+G8SwIc2CdatlpsB5+lSJn52YvX15+4+WleP36BIVaDe5dmAP0o7lsXYjrmoO5pT0uscwk+LrP2SO9Yhs7L5BWPmOtvfEcmX6CBABdmNerclC/SMXnNNk6y11Bhp9SOWp2DFD4Z+rgzr3EcgpoHes4fUKbvHNoxU7huTU5wPndOVsUY94UmBEuG12ikP4EUrFsLVeX4fC+KkCF1MrjhOXtpx4zlk98taMR50Wj9TIWiOtzdl7hklUxXgvysu3T+gjpALYQLrpmmKpk/aFvcpJtcLj6phfm3MpM9wXyh6ShUTx6ctfwXSW1ENWSsxAE3RahfY5rbtxI66iVnYsjOK2co5Rji9Qcwr8RqQy1aCmyVQng3j2/VaK3gplZiav2xAXQn/v7EozgbPv9Gm0svtuJl8DZf8YMSOGKTL81PeRhBV7SpFxxe5qv2Nu1HENV2OyTJ1biKbgcbOwBV6WzFeOK5VBgjaRA0ZCxcNH4LAI0KihykwWwL0kP0FR3j5dqh7KEJ2tRDt37K897GuP0x9raqRv9ZU3n/JalQ11zL5zsQsfcm9CD314/tK5ThzeKOe+K2IfpXxWu9ZDEHGgeQUf/0oL6S5Y1jrN7JncmtVBHIspb/q09EapjeOOdjOjZbj4lkHF1qsvxwBKqLxbOa56wzmvSHoqnk6r/WoE5VnwcyyJx54Co6rkU9wUr8hHDo6uE7onQS0BnOWpfCloeVAFj1dTOVzljo49OOL37docMj/uIgFrKAGGRvAf4LDwlpRs32Xx7PPfafjTlO87DIZoEA5VBu+fm0D4GCi2wl1rmL0iceZmp5s6EG7sbqD7NJlF8+mo+3tFzTZoMhmjmg8xY/VNrmUUS/4klxAa5N7k/Fkf03Eu7eCgKZichqOSBmpD818z+8M62XuSJIdWM6x2DVvJmnV4Y70Cn9GZTGaObLi5pa1eoYr4cXD5kUynu+ikd3yyAvZThr/Inlv1LE/qJSYxU2VcjWEoRmWuPQYeI8C14sL5/ynMyugXOj58L6rXnYx1WISycOzipRmH2Z/ZuBLydq/7mtHsOi7WtVGmHPi2KaUnMcY506CkeXqQUnWOfXt1VKLTSLoubXSq3clPTONp9oR7uoCEXr3cIu4R7VIeUnhDlED8MFIqSNs0ctvY+pZFTe4K4fJLS2fM2xIHoS3Uf76EjGBd82uo7f1ij4r/m9Be0yfn9HDv9nLgtKNr6OihR+y4a1DMCMJ2qMsZFtXkljG4UTO0lwm8gLRwUhVWGGYIycIXDI2Hm7WfEIcgKHHfVykYG1MNab0mHsy42h8tApNmL/17TvotTEHOWp+xoi6DiwsuOSQhxXZd1jYQSXiu2O/Z47PURkHc40ukBuTILfhQkKPQWsmcU0HM9J3/1Z2iHxEBSjJXc1prHbXzpyMxffCJR3FeVxSZDC+K+crMPAVeJczKiVGx9guzx3gqm/Y7bGUOZCRKiZr8Zlz7HlFfn8a5K7kPtdBvSIZZBUE/AncnMTVUr6yyf0ZlL+kX6C/Yi4VBapLFy4o6hfXMx9NUh2gQjiTv4uVQPVeqM+KuGqJ56SjYVcz60jzcWtUlNfLeZV7a06uP2SKrDDwTKYpQOMOtcv7Gubajd+QzGWjBKiclcn1kFO2BxxTysuPYEzf6J8sah7WtW4zQKLezfZblX9K2wSZwGTP6/b5hFMnEtiYOfc9EukXNGT0xeyVhJmA4ZnLQfPyYAkuPM8QrdfzXS6QhYh1nwRyMiak2TdHRF/g/ZgWYSR+VppeR+IbBcI/g1qhjBuNcMuVskCmWr7VuHq85WStR1FleqkytE3dcuwKys7EcwVyxyD34ayZbXDPnr0SUvdOIzp7DidJGJrlA4bFGb09LUCXdxequSxgP4b+o4o1LzAaQaUS91Vsso+UZ4kX5yRYRVBb8o5qHOWejVs7d8tPlSS++JQ+STCfIDVkfvbc5nqX0gbPLHjblTQQa7Dotdz/8Au0Leogi1afJNSIE9aju9P5zAbeyOsIjNswF/fjrwhBEbQs+JIF7d29xkzGnC95ZOJXbK7DMXUdcGykgVylnkJZvF6FsXrP8LB+fBHtLHYEI5oIlkbXJr39324lkzc1nIh4hqEBosLX14XlJau6QnNuIWKPzGtelO6WiKNp+WbsPkdJ5bJZY1YZtOmn6p5qsYOJsvt/WJqfkdYydNJFbsOwuz5wK6ktKRCRrmne3PvorxJGaW4Q04kC6plX69qDrt1r8CB+ls+j95B7F5wmNdU0Krp73G083UPSoSoD8O9voKy5OxweqLvFQIDeqsPjF3WjYQaeLyMA+7qCf
*/