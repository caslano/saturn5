#ifndef BOOST_METAPARSE_V1_FOLDR1_HPP
#define BOOST_METAPARSE_V1_FOLDR1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr1
      {
        typedef foldr1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr1.hpp
YjdyFDhGzVCtjnE73ZnyOlWXaCX+Fw9rQd1DrSuGgvAIb5y5ht29QPupAf0x4sRirUsDlWtYAO6Ku71DcxbndR5aEOEo3o1TkLkYbPzdWYMWm238CzgF5ywQFIxNef810RRSbaEXmILORgZyCdxFP+e9xU4vZ/84RKGDs5LB2O0ZAB1PNf+S4FciVqXLdKSri6FKhLb2CVgPCyjFPjfGp+5o6uwZ5l6eN9WrVlNZJU6fTGld/DrJD/s8vOZ7J6b/vQZxb9DWzryti0VXFhsLegHSRRlbrUYXG/9Gi1e86YrXUFxc0LiHnc9Po5euW2kagLOMASj1iFL0QBwyb8Qoztl4JSnX8ZdL2aDiYlq3kZfTsW4ALdM/L6PfB/jx58vakSHGWSo2+HdIZ55FMg4RuO56jSRYNmZJruDI7sKZc/H5xI3mtisNc2lzLV9aFWxpXd6XL623heTlXhuytBqM8g833Y1rq2AFLRiNECkgkwKqwPujP0GRy0d1U7DWC4kpjyVC1NjEMtgaz0Pk/80kw+qlkBxdVPlJBKoXn9i4o6yLHPFSCZakbm10klj24kA59Nf25zIrr/UALEfUV0xX60KGbcBKGDYH5jLXYh7IEsQGIRHRA3iigvN59P6uV+2IITmWMz2D29V8HinS+OoUjjTCa/7p6YFZKyAuKTh2BcYmIT8ZFMV29Q39yJWwqF8ZDTYAe8Apzl56sJuG
*/