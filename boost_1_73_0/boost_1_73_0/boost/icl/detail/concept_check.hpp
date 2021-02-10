/*-----------------------------------------------------------------------------+    
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_CHECK_HPP_JOFA_090913
#define BOOST_ICL_CONCEPT_CHECK_HPP_JOFA_090913

#include <boost/concept_check.hpp>

#include <boost/concept/detail/concept_def.hpp>
namespace boost{ namespace icl
{

    BOOST_concept(EqualComparable,(Type))
    {
        BOOST_CONCEPT_USAGE(EqualComparable) {
            require_boolean_expr(_left == _right);
        }
    private:
        Type _left, _right;
    };

}}// namespace boost icl
#include <boost/concept/detail/concept_undef.hpp>

#endif



/* concept_check.hpp
f+QfuqZqTEKYH9AAfM7zhTSBFdVlcs3UKJosSVKlCBiuiQWmSNgRh9npalULvCxPJRooa8qpQno/UwCOKnmSucHswhgwGdu2e4YwosyOKol7VTAqGSkrtRKRQqm6aLHA6saRCW1smxYNUQHl1dYyqChV/lQ2TVtpV2Qh5CzwtbAqBAZbJim2jDiyPLNxNHxGqLXtGuWO2JHlSabFhSKzyslEa0spOKhsQ3apcI7w+7P9DGYPf3Gogp2w1z16hQda4FaFF4pHZiUOvvhTqmMQPwZ+yM/js3QD7UNBRbj7QkfEUflWRrYRXDHp/6TgllP5c8FVBu8fD64C9hODq6C+OrgYiza236T4wDfbZvsw+CYw+2q30WMUbyL5ZI/k24TKswqd7nG36VOQk/fv65b2yGCV4+ngHT87siEZ2hOOvYiDz8rgyLgun1yjDntCsI1y74k9ZkFFnEDsvnM6cb7C8PlFtBQ4xExggrqEoZJfuPk8/lS5gqtdAw6yx5zm2TY41K4+T67tvjnE0Ie5Tronp+95UEBSjUXVYG184c/lJ/KJF7svYqvDYK+r2iooHomwgx4z+jsHCgVQPBMp4GEcJ2dFmWOs2QJkNR0cwOUDXdfv3+pvP2qd7htZkYW4TC0/HM9jiCOCTsAGd5ND
*/