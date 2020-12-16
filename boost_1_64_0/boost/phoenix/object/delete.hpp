/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_DELETE_HPP
#define BOOST_PHOENIX_OBJECT_DELETE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(delete_)
  , (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct delete_eval
    {
        typedef void result_type;

        template <typename P, typename Context>
        result_type
        operator()(P const& p, Context const &ctx) const
        {
            delete boost::phoenix::eval(p, ctx);
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::delete_, Dummy>
        : call<delete_eval>
    {};

    template <typename P>
    inline
    typename expression::delete_<P>::type const
    delete_(P const& p)
    {
        return expression::delete_<P>::make(p);
    }

}}

#endif

/* delete.hpp
wH5w5D6NXq9Jobdx/98o9m8qomyKlXGmYmXs6shHyNjKcF2jyoe4BRFMqIUVsWIFpBwktAJ3CQPZMkAtvHyRU9lLGO+0/vC3b01K1Zq2/wFOaza//CLSGp9n/YLhz11eqVreWdJzQulN92O3Pq/tlynDNJf78AbWtsotfHlmMLRrZsE+Lc32WNGm2teShk16Cyr0PlKhfYUKfbyOVShz3f+D2PPyDW8dkZ4ZvyjV/hstz3Rdnin6PJVi4XPwxO7vG1uf5FvI9CSz4WC13vKE403UJcnmJNOi3lyL0c0W6tPzGwpH0c1ArtXRM7xc5cu7tdhfDbMEmn4Q5QNjK5F2rqICawH5poGiyQCHTrQafCOlCLqXGntp++UX+0F7ipb5k8S3SiMLU+3BcC73E1yW/q7jMqlu1gCkJ6g1Iw1qnvt1ear+psuzXM+hTAsZYoX4gmCsUWMMz14I9dmYK/QIQ2SZGtmZZaKZaYeGTMKyLYTaKDFmA2O2VRrounDfin8Jc7X56rO/5fkHJF22Y7tNvVHS1ZEl2OIgtlwv2LL1Gx1bWlPcIFpoBxOKMYUP3VRxxkHyukEn5dcGrLy1/Hw77dZ4di1P+zn61Gn1oHQqZmbiEYNnflC2VBYmO/IECRN0JPQRJPjd3JA1Qq4/U/O4OjjubEr2mVrOE8gLdHCME8kzdMmfKcl9mfYY0M5C3UBBa8mVQb5fT7fJUrkYcYJb5zFC4bbi4m2I/7duHpyl/VJ4//9Z3o8Sg8wdp9Tt9GSqxucGV6KXT6WPi43DglMqw3vb9yC3jr83CGYc+pqZgfGmUuqjrmH8M9WNovHPqGqSdlRJkPnDL0IMPK2k1VB58qB6DpKF92raHsVSzZd5HJezvmMamYb3mqXhdkEDi3yIBn/oBlUAjdQgGglylJ5ZU9gPcijk5+/fazoO/7NM6dmyK145gmd6AYmVQMAY+KN/dBC8w4V13uz86FuVrp52f7N0bftrM3QFRntVDHeqGJw2bo0Bp9QZfU/7NxrG8TqMkxSM+bZKo4bxUo8c/6Ufkq9E3v9+huSrVsjXd3VqDW/CKtLoGoBWFXU/rqWk+LJrhLSVanE2hkn9TuVHb/tVhjAO9xf8GP2X5lo+kgffGgnZrtayjddl6/CXEBt7adneVcf2F9aF3VzsbU/TsEzVYTla01zhpc2KHb+ckyXad2BmQ+FA7WbePNEFqYfgv5C/K1n+6oT8MX5CB/3RM/B7+/BmOTGiJlwy/qPKRT0fOhJ+f/TYgfDwkENhYfnRp4NBffiH9eHhuc+Gh79bHR4+2ij8whNh4XLzu+HlZ70VHk6tCqfn+6fC8R14Jjx8uBF9y9aGhxN+Ex6++fHwcFajcGyj+s1ZHU5/2uFwejc0Co9vxN99B8PD5YfCw/J74eGcRvD1jfg14O3wcOI74eEljeArGvF3XVV4eE6j8jc1wr8iHL+js339B5E2ceyDn+5R1n2N1kMJv4apdjxDOmzyM36G09+OTeUTMfHURefWYudMXKrOMNMBw1D1ySLqLec/z3n2Kd35tdk9QBQymdfB6OiBGD4wt7DpRYN7gQW3uYgAiyDg5VaRyjIeOxm0yYdx5V1d+iNaehSnh24qR1zchWLiX88Q/8q+bIZ/Ft7/fjIYVCpCG7d0GtiKzhKXhxsImFGhgFXQpNZQWAjkOCiTmKAdsTH5yqRw0bWq0ZqFqxGrbuKQYqznFrDADaQEYgEuqpkYeAIgSqOoUP+CE0V1vXjv08q29FnPv9ZCnq4R8mSWx/yZ+Xb+zSwtfwny886BWSceiap4MCtJuw+FSZWC8kLtN5X1P/CrDQJE9HhJiwvAGrL/eCKUX2lfbsZ4dR4=
*/