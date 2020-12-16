//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_REAL_CAST_HPP
#define BOOST_MATH_TOOLS_REAL_CAST_HPP

#include <boost/math/tools/config.hpp>

#ifdef _MSC_VER
#pragma once
#endif

namespace boost{ namespace math
{
  namespace tools
  {
    template <class To, class T>
    inline BOOST_MATH_CONSTEXPR To real_cast(T t) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && BOOST_MATH_IS_FLOAT(To))
    {
       return static_cast<To>(t);
    }
  } // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_REAL_CAST_HPP




/* real_cast.hpp
bJCBbBl1BuL9o8MbZV5dFKYNDmdJFR3ijWDGjf+ccu4qS+XAP4i7vOx9szA28c08bRXRDXTbt/LdMagt75TDWyWJjGQdGd7ltaUejVf8PqHNW4kyDOM8qTDb3L/MfN7eW/bHuI+KtApi9TYF1Wz6+Jx+RTDqhYHrp+I5b3be4adJ3kQJisJFsLUMQf5Fv11HMv5c5GECpjwSreJOz63A+mz4iHRtvdenl0L05uTsk8dtHUu9qgnqUgo1ErCHLWN0h+Xsm7kue0lc+HllnomqZx00ZI712/LezvKbiViGuZ9HvrCfE6iEHRFxO97b/IEURVNHMvYr5L/8wyBBb57H3sLrvcmrusnKUgyLO90+kDCTB3xz0/LvYfyxiPI6r8rSb/mhgwy0AGzIts6NXxDGn4smq2Qhg5LewmlNx7ZjTwqOm/dhM/xtWRL66nlZrd+H4Rac88Ck19bjgKVfC78J/Lj2K+DFh8Eq98iMyUM9nlhx3reeseUEvojqzPPTTImhukOJ6sWYNflj886vsvwkooD6DMug0YKM1QIBqytYJTob860Op09hOpxEcVElZYDsbMyhN0Is77Eo4jD3Mi+63Bsz+KY0CTJCtu/6tzp9OAPjV8XFcEzXutRmAruTsw9m8zeilFlTykYiuy6tZTPp3dcX7DJD00nlK6eKIoFp2ZWNJaEWtOr+CMt/rJwOlHGS1gJXCiM7pPUGf2DzB5kowXhHTZUR/4Yv9eDtONnxS1geM65GZSy9JBHadAND7+TAsUerfnt/kpVBirKJ/Cov1RsddeY63KxSMxe7Vpw3S9902jFJfC9ImnqEjOXesrpAuNrx7/LHt7r9KgmaqK66Mugx9Ki51MRp531uWGZl1HjuwzGyDMS7h/EGwg/LsAHlIF5ScHf9N8V4M+AtsjCv+JsrNGqj3n3tfdo490tT1UEQNB7nx9GJmTV6J3z8tDuXr8Iw9er23RP2C5v3SWqf7OR1sOZ4nNpiwoHf2hxW9DMPgn29xxPd2hymWOTKptHesAbSqyfab52w141BLWTgF5HnXfGbF1UG4Zz7vHeMrToM7dQE0XornHbdNk2j2bx1bvHV7UhzJt/23sraDoPBm1nEf/CuSOtOwIh/F2HwghXFlrivogETzr9hCgbzL6LftAfpOF1u6Q9H+tL9FH3DhS2LXX37/QGrIrN055uwlUwyn3PdhjgMrU0yZx6A2CPTkzfOejKpD1E0bAv3zS6OIl3b8d0fyHAz4C/Hf8pMhHvdWOYH2RgtgeJo7LVolBPDe5LTQSrR9jzYpq2d6B8nGhSEaFgND2/XH89l8bWKsmyyBndHsPMBlnT4fWNNVOJxOdhH6kC9uWX7bH1yk8IeVkZN9UHsaUTfs9nQUZoG0Ju2CaDru/i0aYKpUMy1N/B78VGcV151xeE3sIuq6qHyvX+ssyDVXQvuDpq83T6OuM7ClerqpZsJQ0pIwvq2D+4tXSwKNJiZbYjpbrJR3OHtDmZ9yfAvXIU0d9PMKv/pOxOmu7FG+d1xF4ajRafV/nvv2sX01ql+Lt2N6KosOrg7ojA5I+s/uwiLI4vqHabc11+DdNzdYu8n70k0qHs7BdI1wmhPyEOfbKsDMGkmDzftJgztOFAeL9yb0zGf9E7mPpyOFo58nu9hdJ0F245PXYt06m0Uc+H+QCObRyqJdsDYsesMjlSNgHSv8wGAc+3iiWW6G/rADh1TIlvYPKiDQctDmJv22pjgkCSbZ/JyvoPRKdHZ94OJPspm/pvRNS+dqTL7UYksi7I4Sco7akBs+3G224874+7YZsLRhvuJQc+ytYMJg6H+w6BUj5e2IJY2lzv6NdhGGNrQtfrYTk7v3E0=
*/