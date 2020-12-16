/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_IO_HPP
#define BOOST_PHOENIX_OPERATOR_IO_HPP

#include <iosfwd>

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    namespace detail
    {
        typedef std::ios_base&  (*iomanip_type)(std::ios_base&);
        typedef std::istream&   (*imanip_type)(std::istream&);
        typedef std::ostream&   (*omanip_type)(std::ostream&);
    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  overloads for I/O manipulators.
    //
    /////////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    inline
    typename proto::result_of::make_expr<
          proto::tag::shift_left
        , phoenix_domain
        , actor<Expr>
        , detail::iomanip_type
        >::type const
    operator<<(actor<Expr> const& a0, detail::iomanip_type a1)
    {
        return proto::make_expr<
            proto::tag::shift_left, phoenix_domain>(a0, a1);
    }

    template <typename Expr>
    inline
    typename proto::result_of::make_expr<
          proto::tag::shift_left
        , phoenix_domain
        , actor<Expr>
        , detail::omanip_type
        >::type const
    operator<<(actor<Expr> const& a0, detail::omanip_type a1)
    {
        return proto::make_expr<
            proto::tag::shift_left, phoenix_domain>(a0, a1);
    }

    template <typename Expr>
    inline
    typename proto::result_of::make_expr<
          proto::tag::shift_right
        , phoenix_domain
        , actor<Expr>
        , detail::iomanip_type
        >::type const
    operator>>(actor<Expr> const& a0, detail::iomanip_type a1)
    {
        return proto::make_expr<
            proto::tag::shift_right, phoenix_domain>(a0, a1);
    }

    template <typename Expr>
    inline
    typename proto::result_of::make_expr<
          proto::tag::shift_right
        , phoenix_domain
        , actor<Expr>
        , detail::imanip_type
        >::type const
    operator>>(actor<Expr> const& a0, detail::imanip_type a1)
    {
        return proto::make_expr<
            proto::tag::shift_right, phoenix_domain>(a0, a1);
    }
    
    using proto::exprns_::operator<<;
    using proto::exprns_::operator>>;
}}

#endif

/* io.hpp
u6FXnK3RAqAJ25mWoFleyUMbe0rITrOBMLTwcUYw3hfG3zWMq50WjAc1jBqAweqdGER2MkABeXECQzrOWgD/1KCOs4E6R4M60qAI4+FtrvAnRuhi0wVzUC7S5yLnSBPnw9+qBRo61prBbks7KnD7PWXZuW54Wk2kzj9q4QvJ6HBKdz5C4k2K9WTeSzk94rDxdBLUPQBV8v39E3mRU3xJqAqK8FK9hooNhRwHiFsmBM3U4DLBeP6xVmfk9MX4O08SxkTQRmqM86SOgZzEY2+ZSIWXyYZjG7X9E/TzUsE/1kpXtygI5ts3CW3vgAlwPf+QRU5NMG9aLySjwKpguK7gSNtYrpAKohcmuR2jSAV9/O6OWWcRiugRfWiLMwVt+cezVpGvl8Rm7360/840YOW10egh19sG26fGYlgid7FKzf8nZLDXQCpCMHuISLgnkjedAuhCtYMUaAA32ABsbNLSuEayF+DSuPD8hVLCNj4LaHzijycrLRdIuJyx+pyThmkVeAnPDN4gLepPLcLF8WVI4yz+D+iTNrZ9tVE4uOOBcWKubr1OGw1cEnN1B+q0XGCJuOxtjSkW3rTEsbiHu7LmcRmLOmIUsH4zsFyWnllpvtHAP8x1z4jaCnqLNAIOpd3OXvRLIlRoS2QeJoWR3btLCoelcI+KdF7vNtSl+MsDbPPUvYzzoizRvEAKTpOC3aKb9hjKAcAExQU+uczGBY6TgjlSMKaiZC70GupIOtoiz2darI90SWCNzK4Q9B5LGAafK+fBAosRPEf36BVOq0cLdPFj9oglefbJrznZ0PcHB//Q7j+MRBez6XzfQYvoQL/pQi0mdog5M91nLn6MRgDeY7NUEPZZYOHfnwJxsuaXHUVnidRnVqV2DwFPsYbSsRXmn94gOBSJ/EyJT8b33V3siJpjmcs1fzSkhaup8LN42izM1q7w+0jjN/QswO+vqxV+7cwJKgcCy7F8eD0SiuIKKt+myvfo8uuw/L1Svk2bt17UANNtCQKITHWLW4HY+Q3LRkPS+RCKmeuAli2pzVdOCmItJV6sQGdvWEYAKlEthh58puZCfpo36xyQPm2o/HyOfubJzyb6mS8/Y/RzBJG2fPC/TohUGIDF6IAHl043nMDaqAlYaSVO9Vj241M9oDUN0HQH9y5sOvZCev3k/t00HrnETz1eiRd/KJc4Msqonzy4mw3Xu8EM+kIRzZBQxkdc9txZmKgCOZsV3GOsmwH13/etiBTsHKvswm+kcywdn/ztC8g+ttUp14ezzxbZlye8sbfzsHSeNZddRCKg0RfS2wnXIl91BeXIghyyzkooAlCxdBpN0nVe+DmhhCbpZvb9EJivViD8MdMeVTMU1M7qJs1zJJn8DikD1tFzATE/+AyhFx/hg53ZyQ8jHQ5yDCJLSE87sL2UrI/yAwr2MzCj1MTQT9ATF/YlKdKgoGc4sh0Qjza0L99PJM5rFb/b0g7mwgjQut+iROa50parZzmyr3sHxGzUM6erjkKVeZdjzhEkw5ztnU8duV4cvMyG2JN0n3A2/ZwFXcjXC6PZQj7G0mXLLnKo3p8SYesd9LC6Fd7e+G1Pf1d1G9xWFnqB41Vcbc7JtScUVJuR6g5sQAdfZOnwXnkxR8enbLBNP/trgqkOEvMH8g08g0/+ndlu/L+NanT2t6qrNoE2TaA6UtZI7X3JJfS0uLxjjgfDwFfHov04KVKutsTihdMRCptn4SNkwr7EuRbz8hSsJ0gx6DZYr10sHd0vjSyxCdoMuMoLD66K2VV0VDvtACLuuN6T32vp6iezyUhYTCcuDde0OoJnUecU0ELZeF6cN/Hbf6WkJ/NOIOg/AQpC09IHG8BBHJw=
*/