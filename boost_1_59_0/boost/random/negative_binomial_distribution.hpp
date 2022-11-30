/* boost random/negative_binomial_distribution.hpp header file
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_NEGATIVE_BINOMIAL_DISTRIBUTION_HPP_INCLUDED
#define BOOST_RANDOM_NEGATIVE_BINOMIAL_DISTRIBUTION_HPP_INCLUDED

#include <iosfwd>

#include <boost/limits.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/gamma_distribution.hpp>
#include <boost/random/poisson_distribution.hpp>

namespace boost {
namespace random {

/**
 * The negative binomial distribution is an integer valued
 * distribution with two parameters, @c k and @c p.  The
 * distribution produces non-negative values.
 *
 * The distribution function is
 * \f$\displaystyle P(i) = {k+i-1\choose i}p^k(1-p)^i\f$.
 *
 * This implementation uses a gamma-poisson mixture.
 */
template<class IntType = int, class RealType = double>
class negative_binomial_distribution {
public:
    typedef IntType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef negative_binomial_distribution distribution_type;
        /**
         * Construct a param_type object.  @c k and @c p
         * are the parameters of the distribution.
         *
         * Requires: k >=0 && 0 <= p <= 1
         */
        explicit param_type(IntType k_arg = 1, RealType p_arg = RealType (0.5))
          : _k(k_arg), _p(p_arg)
        {}
        /** Returns the @c k parameter of the distribution. */
        IntType k() const { return _k; }
        /** Returns the @c p parameter of the distribution. */
        RealType p() const { return _p; }
#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
        /** Writes the parameters of the distribution to a @c std::ostream. */
        template<class CharT, class Traits>
        friend std::basic_ostream<CharT,Traits>&
        operator<<(std::basic_ostream<CharT,Traits>& os,
                   const param_type& parm)
        {
            os << parm._p << " " << parm._k;
            return os;
        }
    
        /** Reads the parameters of the distribution from a @c std::istream. */
        template<class CharT, class Traits>
        friend std::basic_istream<CharT,Traits>&
        operator>>(std::basic_istream<CharT,Traits>& is, param_type& parm)
        {
            is >> parm._p >> std::ws >> parm._k;
            return is;
        }
#endif
        /** Returns true if the parameters have the same values. */
        friend bool operator==(const param_type& lhs, const param_type& rhs)
        {
            return lhs._k == rhs._k && lhs._p == rhs._p;
        }
        /** Returns true if the parameters have different values. */
        friend bool operator!=(const param_type& lhs, const param_type& rhs)
        {
            return !(lhs == rhs);
        }
    private:
        IntType _k;
        RealType _p;
    };
    
    /**
     * Construct a @c negative_binomial_distribution object. @c k and @c p
     * are the parameters of the distribution.
     *
     * Requires: k >=0 && 0 <= p <= 1
     */
    explicit negative_binomial_distribution(IntType k_arg = 1,
                                            RealType p_arg = RealType(0.5))
      : _k(k_arg), _p(p_arg)
    {}
    
    /**
     * Construct an @c negative_binomial_distribution object from the
     * parameters.
     */
    explicit negative_binomial_distribution(const param_type& parm)
      : _k(parm.k()), _p(parm.p())
    {}
    
    /**
     * Returns a random variate distributed according to the
     * negative binomial distribution.
     */
    template<class URNG>
    IntType operator()(URNG& urng) const
    {
        gamma_distribution<RealType> gamma(_k, (1-_p)/_p);
        poisson_distribution<IntType, RealType> poisson(gamma(urng));
        return poisson(urng);
    }
    
    /**
     * Returns a random variate distributed according to the negative
     * binomial distribution with parameters specified by @c param.
     */
    template<class URNG>
    IntType operator()(URNG& urng, const param_type& parm) const
    {
        return negative_binomial_distribution(parm)(urng);
    }

    /** Returns the @c k parameter of the distribution. */
    IntType k() const { return _k; }
    /** Returns the @c p parameter of the distribution. */
    RealType p() const { return _p; }

    /** Returns the smallest value that the distribution can produce. */
    IntType min BOOST_PREVENT_MACRO_SUBSTITUTION() const { return 0; }
    /** Returns the largest value that the distribution can produce. */
    IntType max BOOST_PREVENT_MACRO_SUBSTITUTION() const
    { return (std::numeric_limits<IntType>::max)(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_k, _p); }
    /** Sets parameters of the distribution. */
    void param(const param_type& parm)
    {
        _k = parm.k();
        _p = parm.p();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /** Writes the parameters of the distribution to a @c std::ostream. */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os,
               const negative_binomial_distribution& bd)
    {
        os << bd.param();
        return os;
    }
    
    /** Reads the parameters of the distribution from a @c std::istream. */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is,
               negative_binomial_distribution& bd)
    {
        bd.read(is);
        return is;
    }
#endif

    /** Returns true if the two distributions will produce the same
        sequence of values, given equal generators. */
    friend bool operator==(const negative_binomial_distribution& lhs,
                           const negative_binomial_distribution& rhs)
    {
        return lhs._k == rhs._k && lhs._p == rhs._p;
    }
    /** Returns true if the two distributions could produce different
        sequences of values, given equal generators. */
    friend bool operator!=(const negative_binomial_distribution& lhs,
                           const negative_binomial_distribution& rhs)
    {
        return !(lhs == rhs);
    }

private:

    /// @cond \show_private

    template<class CharT, class Traits>
    void read(std::basic_istream<CharT, Traits>& is) {
        param_type parm;
        if(is >> parm) {
            param(parm);
        }
    }

    // parameters
    IntType _k;
    RealType _p;

    /// @endcond
};

}

}

#endif

/* negative_binomial_distribution.hpp
mpCQ84kprD9t6sH8zrO0/Aru6PVK0wqebiY/Bsem7IpdOPyXLXqVBhdZ4TJqoeYSqEO6paAA/kHrXyHMX1HH3KSzUGb9zqMI3ljCQqRKN+ARUjGU/V+4jr42eNLidhhHXPNw2OUFIpd9LdGldMSC7ejgCPUHexkqVr3EaTTp1UlQflZdJiHjt7sRsfJ20PaWzJCX363q2rRn/PsP7t6ozV3GZgu9nsBQtRSs1MP5q0lpwLifeSR95+XUaXJObvad6P3Em8xVMX7Z51n8uh5do3ZLEX7sA1phuoUMlxXhwRv9J3sGS0V7uF0kNyaCDf9MSkyNhVppd9awqS4jYgF7YzR/C2xjNA7kej9dbFBDHx3+aBiKnHyIga77JOHzbbHVWAjEoPELpy2BIDSrou9/ewr9Rn1GWbd34uLcFl4LvhUpffiLV62XbUSnuu6aDD1I5RBTUsurMU9rq4hjTCiU8eCNIuEWh8T0E8ZggzFWVCaaK2YQUIHESTse0UmHezoKMVLaHois6+5pknY4R4nAoVYUSGxDeuRm59TIuPr5bFhCgW5eWohUZuKfl/A40tXHeAnao6F2T3eKTix7ByZqSDebPrVzyc0sTt9jy6JVPD6Ghy+7n9H2kZMMMRro9UbHI/KePb5eSwFoOOX1itHz/0qReZBulQiGrxJ7CTfHvK8U3VL8qwaPVtpS1kXjT21PQ51/2N+NAFqJ3CuSVn8FIFqQYELOmBs745XRXPyeFTA99q8BB29usMm7J5H31vo+hNhQXdrSYjaCmMk4KfwvyoyLbOAsmiI+qMjYI+w9m4fV6IwXo4X6iKfCeNk639lcWikrSAZvlV1chZnYxohADW15xxICIw68GfWtBGByMbqVAnfYwYMDN+pjRWNbSnuGTJMgDVF/idJ9xMcK35IY8iPBYk+gDv8d0oFGWE0KxMNAxABIguo59Od296SPTWU53q3laXYKpqfz24Cq8GYA6rs13Q2838MG03cF0569IPyW1qfUBEECxx2LMuuisgNMPJOMkSi9QpM71spAXxtc7JkpIQB6wZcozAR/Fg2O8ti0OjZKyNn1JFRgVOQrjEmvWkT/h1vILHblJTfYxiM5TcW5lyQ8g3cgLiVTq3XXVnh5EFmvaSnIA359r+7gcZvoMCxMYhbc+UYLo+0XU4Om6yWfen54NqgiQTOi0lHUqkAmkma2WAnMfMdoGTy4wbigaYc87Oz1hKgv2sjffSegxOF2JTXjWXgrdq9wezUoFmB3l5Zw1BB+H/beAwqxXc9fTRDRtVVK9Fs326WC+UzP3M9ocho6TbXE9w8oRWBT2CMhIqA8yAqpWQFiMRZGp7BQbFV5p742iVSCVK8ENE4jIH7iMOyHmfHzH/H7dXVuHnyKirLg8TNK/F5e93NEORQGVyHXletgDEIrYilCDl5Ld25Weeh2RMCtK89jht3cHb/z7ATlXqW1oVhUOgc+MzSAYnhTVoqH441JFukXC2LY6jqzhb+j3udCVhxTUHj4rwrRnTOM59YELokfR4zFa8pmxBObLFKfekw8HcWy44xVjmgXN5E/tRw9Jt5NqHzpRIsSukMKp1fJHTcmJFhu38f8Nfqgg7y6/3CZvVM/wEz7Jol1Ky4nsGnDPNLip512AZD4aeKbPj/lQWL8Tz0HAY9AZOKSEP/kQfUe4Y7ERgeCPVESu8RRDE9Nom8opifphw2D1zP/wZnDYG6I1ThLt8JCtNhvjarqqczkzefKmDMSwa+RwNHaY9wQ44I2S+2WwUXMpDUv+XPTFLIlxuj4jLjfwGi9ZyxqJarujTf2C0F1wP5gHFUcaKTB4xHfz8HJ0QOfDo/tdYnDMu1oWV+CpntlS5QKqWdyhjwyAiybWcqMPZs/az9wZKIq7X/94UarfNFTcMAdp5lBiQQfX48ws5SbJvA2oOO5FCn0Vzqrngb/dc4y46XMu5G8UPB+E56r1weTWcVwu+97WcSlDF8v7jHRPs/06/8Hvdi4KyIPOmlmzvA5ASnAB5ZJAbUM/07GOvyOPzpWqwDqxrQW+j863jKozTZq105w1+LuxSlS3N2tuENx9+JBiruX4lYo7u5aKO5uxd2DZsPzfu83s3/suZI7uWUuW5J1nDMArZ8lyXJCyx93SS8DaQ7FnSHq54puVfOfg5nqXy5xY8NXQkajpbkVC6HWlhZWEkuk9XkyWYQ5SRU67Mjl4zgMsfvJZPo4T4rq9JaqbsXxkWQducN3oy9fvwdAjHYv6Sf86gSEjngpIcxXmSxxVQSK/M8fuu+7XSHiXr4Iz11pQ2E1nTqkOQmv4mxoPZ6ATu5NH4LOjb57W3C231mAPCmZNSIqo8LpanMPnNH8OET43yWsPxdLHOu91gZDXJUZ3SF6dPvOL+MN6I3N8S6qONaLMkipgBDUNUSONAfog4kPe5HS24TU6bPVRtbpfmH/NAdJFRDq8PPoPlfe8gF2cvvfdlHHTVhq9i9E+HL7MtUNCYl/qxMs7kGkUd1EJZ3hVV+3CHoQEs1QRChaYnrpGGeyDD9ZJSFMszA7zVQtJkXU10EoBfPkUc6V60JruYB5LuBZ/8AS4T4VWk07ooR3KlEkjgk1oDoL8OfjLwUytuiLxSHPEakf2Wc5w8a5/IG1DcdzWSrjGEDy8f+elYOE+fCHOpNFu48jy72Y/S90xO+42Ks7P1yxDl67D9lrfqpphdfgqA1qWfj50aYQp0pvvfJK2WoMHzop+/iDsTof8iMDiZGBCdVZ0kz+Ps9NxvVTLLLAZXYl/2/yDI5RKT1eToyfoSpoqwP+naZeU5IBQxBynqb7ji9Ul1J+Y75+x8NfX/dPjKKCSs1fBB6N4FlRXgTlvAZFGFGiZLSEaAqrocI00gB+t5HnxNl16LT8QCCU4bpV4d5a+oz2Z1Sju1+tbqxk28ete5q5lRKwHPmVHzfcRuqTEuYHcSjziBJZEMdWyvd0Swyxg+OydgU9IvbCqZHjWnoDC7MUTsAiK/EVSkvLavJ4v7kXXfNro1DlNEbRk9c0CC/+XPkkuxBI70yWQE6ULEXi2APupM5cuAC9NBboLSpDYwEs7YTM0HhtyMT7+jkqLKtjnwNbHxu+1RrhjhFtOoRxgPG8fjX/3CJ+tVapCdYi/JYFVcVzwVf56mrQYbhtbhaPFl3WiinZxwPhWGdQ3qf+qhtm/5g3Lq1gT7W6Nv1xRPk4mnWUX0yE1n0wj6umAlllpuFWBeoGf1ujRfLYdxLlx9hxdDCOoGO88KSOXeCHwyzUDAwY9DPxW2EVdyu//Vc2m/6UNNtNBFlBsPxdGcNihdAPxqxuEtvZKfct9AI6JkdZs+oYg2dFyx97B22uLY0xewc4jFJPRZu6mbUQPMdNo/TOQ9RMGcOIjkAqotzL8PATIiM/iVWraTLMh6+7p5fpR2L/DukYpVr15H22Snpuxoj41C9CUR4616jlr1h41Pmiz8PSytXuG4Lg5humtcw/VrCM6izJYVKERptJfL1D2c7C71ujdvtk/o/AdNRrazqZmRsxrbbJnGFUxuTCHuEIVMiQeDo6E5+v9FWsIm0dEMdsXZGGFtTCrCNLlUAgyJ6wK7qWy38mAA1WxsNWc6DBJaJIvuRJqnHuULQt3Ay533t7W1zlOm6fiajVrJje+3OQGPB2ZPrBDpVv/mr262PYufMr1V3txLSiaueLxrNrySiQ7xANHJyO1nSUdGOXDzDIdoqY47w+5tYuNDNvTamT+SKj440qtcWDApXHkPoh9UTS28zyQEpU60K9zvyLlclH/0bHRLHzsJBN0GvKqJ1DVpIeo7jUedvdDlWoJMtYHUEGimkiXqch24G4ngJvoEq6D2lVVq2f7Mi1KKCqzRZMTYmtUZeP3SuErJQrffNodxubZFjzOV8gyDqR7AVDxYuiBRP107UqT+D95JI00iZ5JyzXW7JgXvHH2fRKyYoHQEH/mx+J5/rTOCYqy31AR0MWthFjAIv68GPN+PrH2cp3VmlTQrFdu+mHGCrYVIdteFWH/uOmQ/79wC0U5yTXIFPCTkrRRwOwReFyv4Jb1I8DsYrtqAjcBoaNab/H06UXla8584ufJZqJhw2W+dkITh4aVIWs6ULhSLXlSqMdxvKHsaMdSxvBQMGt7lvEpcY2FXJj+2R71kH5TXgUgElhPzpT3mKj5EGHCOs5dZO0Tv3oJOqaB5USZAC/UOCVOFJFWeVSII8nQDZWanySBcVshWWzF0BHKXOgcRaYVDKxPcWYbyd+WWIl3n8n4r0JRP7aGm+JEsFmTkqzI0zeJrwv14F+u6Ru7EMz4VINv+/0NytvDxz0fJrKfhvVncj/MIfxtCqfAWevQ5VglbqufWOrymo6u4TBdYOF1u0YJ32T3zelim56P9jgedpbucUuc1mTlyx4KZUk6l5zckTdAaz7yLVeZidyhWpgKIwyjHBW8c1FAk7WKJGzkGnj14ySZ0G4PzUsJXpkCJoVzvoadP4/joqUEbUsTeKS9jHrAefRxh8RKNLERnZE7Lm1VdQT31Mr7YZZFYZwA2h4ibKM17+m61hd/TAe7W7juskwgdkKL3fTKi39JFy1dVjh5lOW/OEf0rcBbzcExhaACw/gMzeY+NPfvlAvBEV/0kVv5/C8BVEqhP3veisZursad5j9joGtTLgnXL2qTyK/tfw2jm8f/xo6psR5aGnQywh8BYPLOyVIBtERo7nUlmmtYrLGLqgqxp1ILyecSL/mrMI/5dal+SE5smTC61nw+LxwH9mYZXaMUY0Hr7Dy+OjhRz9gtyt/NDNu1h6xeo7xKUHmcuBBvyovmLBei7Z/uc798CX4ACX3ein3EXYLt+nHprHDffUppZeLAo7taa93myThdpLK4FAcW2OGSDmYmpkkaVQRnWTg3rJF4hqOyuIwkXUdK2HlLPO6vHhOmAMpXce7o47PzGdksBKc+YKrFdo+4iarGN3C1BEkvDayj+jPP8Axffb5L7nScge8wv5WKhMFcZVSWNDmqGfQV1s62HB4ZC/MqmGs5+iIiQT9JVP2z0TzC1zKf+2il/AOUpqaXTxNBuZssBq8BBhedZ1VW1kY9q60a1NaAyrdYZ1LkgzFw1wDXOXGX023i8QDNXD9h1jx4y8GuRUf/rnPdg98FP50yDDCTsV2YdOvC2fRI/ONY2SS70+jV7zo7kE2AmBYeZ8nj9FTJ489XO/zOoeGtXWX1DqiOgmW8oRYe6dMelKMvhlXbKWfDh4FTpW+76UnZeD4K0IROezzvrF9X4x+JRiqStXNA8nDs2bwTOhodUIosJ83EO3qr05hdl+UgpEqSnb7QXYUK9zEZFdSQI8IL5SSnHeU3qSO9fRGGvC26+RkKZVBQ5of4owgN3YiwiM5nl1hhIsHf0X/yjMdGIbfQ1bUBAOEPa9ZZjlAzzkz0JaBjYj8t6Yq0xbXCqKMsvUwicnWOgcC4qw/rHQS1zw4dIQoqFJ0vtrzGhU9w6hSYmnpR7PNfTNBywApY8uwdoLzMyg/sPQqJpnhtF9prvdLz9Fdih1Xw2VdSVMjsN0cYlpLu8rYUbAPrviUWw0F2bhm0/R/0qq69439JuWVOslpgEwRj/tKOIi6qY80poiT/HVcc3zLbJmUcDw4TzDpD+vY5jl1vU9VA49bjipwWqitWq4w9R+WFl1p/fbArk6cnl606o2qaHaEIzmKks+lblfBmDcug+6/k3X21cPWybXYSiaR3+clVyNzeEtrESdnLJZOehZKVc9wEbrtdMivhdhO+l3g/JvUi4Td7fNU5mP9YmCvf6F/BfohI2sBtQtTTDYXllx+PsYs8mUfdvWGSWYZPry44E4PqWDCld8sVJhzvlHcjEyCfU6/nhLb8ROJQW20zmeZJKm7n81EN5+Mz32XI3+4nQz3OkzgLznunXir4MIB7W6Tul3xZXBw8MShT9S18CsoJSKbFLAp7+3lY3qOUGHq+PgQCn+I/ethVg8ZRm8s6u++hevVOTJGwQct64UJKMtQi10m+Wml3HxMtNPhJkqmfoxSXvcSE68tT2DpP0PEf0xoQZ02Tc6bwe/RMpKQ8zBRGF8rOSCNGZpa1QBlPY5XUrJ55JNUZxPVUw2L/y06YZoWLNc4wOZP2oQvgxabse6bG4Z5AZTV2q/fCZ3BO8nwAX3sj6yavjvhWK48fDuwe306YuKJyIsFOKChxD9481Ql5nVrIeVoN38VhArx96QJwDQy20TAmXbMb/6TnmwvTkiz43CUme2GDVP+j7WqYqYBCaODjrFZ+Oi38rbpb2UHjNYYui10Yw0dgPQQQegR9s/Kx5Bz3F+/DyvIdopoFtW6pTCJTnnkjPlaNZ0iYlk+kW5dY35k2yBlLFAat2R95v/nu+0N65zoPuntS3DSVdygEfIxMRq/UNFH9xenWb9CdME6TFujEjGiiTBXOJWjGGKYJgo3Nt/mLG6bElbpM9TA39nwytks/EiJDz82Ciuwgd+FwzF9ialEagfpaevaDQX5TjSxP9LWoZwuQ5ueWu+HtWqKfo3/9ev4S9JPiMavDAFjGWfNX/3DNFwfzFGF1E4PfSH0lUBYsWNe8rFCIB6DATCFRtSbPoc22YVSeJN414HImWZGX7VTONj+CRur5IJgxfJA48kG6wNmTD+TjNPSE45LP36PmULSLtHEgbnQd12q6r9JQ6MnPLKRKC0Bwx3RcsRKAcxkZzof4xZGZwyrCH/hDaoXCQ+bVaBh/jb/ahQQYsdo8gEjuIml2aaJ7HbY01qfHanya2ThNeOyNDhqs2SngrcEU3xZOZnoULe49euK/XiwntX+Fq2vmRRpPN+nKZ6LnX9XVp5WTYyOh4n3ucbqu+yEuHLMWl7mqxNQlhI3841Tm5DRKjDH5gQIgt3a5Vz5vc+q8uYjM0ljdHjLVX5Rz8Xfwms1XqoORofi4JyxE8jHQ+MO7fHoIQ8ONV5mg3gW2Im/J+h0JLg9AzDCsD4QS1nHhSgHqa+mcqyXmBgXgvDGcKQH6XOSbNnF4Rr12gN2FTeRLG1uqnfoghDfuesRi+SuAjCn7z2hixa9xXZn3GrHpxIPrPPlxY7kA8JpKl8Jw0R2TrwCjcWHtQAULOvT2ILbBw0UYXRY5lw52JqQBEAVSnYdvHAtXdbQvoCWG8K+Lzaz7qyZz+VDYUfE1qnGCBsoSEUf0+ZLg6iL5DFhf2L/4vXWSwhwhaXN/5QjotJEesHvY2qzLoVpRFi477bolLu+GwmmwS/J2VEfzZsV/qXuIiY0f6zm/u4iiXHC5uS/eqllOY8HreM/Rr/LYD31f+ZI8C7vqHEW3xypGGvsTnk+vRSS58F+Pv8rkafq2z5ByMJBFBTn2kywu6uPlJAVqSaBKJs2sbpD2L1crgpR1BYGScwdsQIytQVn7WDDmQMmRQ+/6W3KoXnabo6IOQDXN9axm9V6X7U5C7rKzF02R+4XySDxzfN1yvY9L1ws0S4q53c031VfWVLZgca1wnciE/2b8yCS3JrTAFFftwAe7AdAWdjVDAJmN7WHJ8J4TcAr4vpUL6+R4o9vJDH/AKso3QfFXEuqrSWMhCquXHgj+A1WlQj1yY+RUx+IjINOhwzvpekBrJo520mXDgRwgAjPy0eUtJcsFA6Z0CRaCwQRvmnMv2WT
*/