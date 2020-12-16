/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_SELF_HPP
#define BOOST_PHOENIX_OPERATOR_SELF_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (address_of)
        (dereference)
    )
    BOOST_PHOENIX_BINARY_OPERATORS(
        (assign)
        (subscript)
    )
    
    using proto::exprns_::operator&;
    using proto::exprns_::operator*;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* self.hpp
dcSkfBnmmDvffwZPttbfdFp/3aSoQ8nIBDYu1VEbTnYpGzegXbHP8MZG7NOQO/pmdBA8Oeb3B6sA3qZmWqHHYKYt8xoANydx1L21RU4cwhIyabkUgkRQgSDVFHDSHQqyBIFfDOtSFE3mUQjqWCSHgyp8yJdaSFvRA2XgmemGDtTSszPDg57mdz2px7tn1yr6bqQHO5tN/HaXwW+kBBsWSC4xQhDlJtsg2ByH9+zU5KBnZ/YTPbvyRC4mh0EyMnhXjAzWkbrHHmj8g5PUQYCGFmNHypCNtg2ZxKInOTlEsAowx3ApCsrzZEaJdaJett6kZUsJmrMGlRCttZmwrbGdZcT3pa+Mr+aD628m7X+T7OchuCTAS63to177oSadXAcMo7/9iJ02I6WzSINu4srq6LzHRYQIFyvFoE4lOpNgE/uyC3S0MyUQXZEcGNnZ5LixDdQl99kCOmWv+Xb/WHiHE73CtZP7xw4RMoCu93Ll/2YJ337aYRD/JeFY5HwUJYs9rCj8Lg51pGKWNj3ha+CRkpniWRWJBfvG6AJxDacCQ2RICgXZ49X/KCRCg7zBQwW3bsJNXFMKehdHGL0z6fLMSkLPPO1EPmFU30dxyB6OlIFZwOpIuWk79/zluDhrN805WAXdwE3T9rLZTquKTFVFD/wERfuDSWosCNBD/nRX8uiewMG2sCkGDl4nZJLrbyb4fLrioEbylruSV+CLJmWnwJeYfa1T2QrmgXTpOc2ch59QGtVHLCIB4zc9LYYqsdstigSJkwfHYEGfo2gDDXLdS6FKNeouSZgkNkSH2GyIAl7oQJxgbDDkSDYYIi678wiQNUX1wIx1pRqYrYu519ZTgKyVzLVeto2nPjsNAleoKx3cO3O+lXhi2ApVk8XtVlf5ZtgldjXl90k15aNBOt47+NRQXGYGR8gol+vt+XBBdhQjGx0K7cVlVwksAIyJGfGwImUUOHkQ/0D3HE8007KaouMJCvck2PfEid+Ys+pX8eF4nQ0ScVJ+T3JzgsU/nlcc7002qocH17TZlVqfeh4tbZ9EgSDbuLsdyqR2DG5sKa08PRNloyOJV5BvhBSXzgqdIjveBNuOxxZw8OQqmVVhN/D3EnjmYjTfwnMkn+3vwIk6kcHZvKsVqJ+z9t5RVN9nOhpImM1LbhHv/gk+iA8ssm/wrzoSgg0VwXEBeqxgi3DAM5QOHJAvcbsklGIK5qSHT099mZMe5kPszIkk9gB6DBCqlTBcWTuLrzPMn4UkuOn7xEXf6KBluiAsXHS2aOtnYyDLkqK91bcJ/ftKkRW/FK/EoL67RhHnUL6t50dQu3QjRkProgdaGFbmkbWkzp4v8Tr9tesXOVXIQAlPYsuXi7PLxzkjC93GF2SOeL2xnXjtNgwaEsQrDbkBFrllE2U+YwLdh04FXq/PDcdCHtA8h/ajubVmsbKj91IiLyz2eFiv3sRra+LoY2V+vnoIToJlmx7E2CrB4CGQeAuyqSOiA+GRwj2Ngoet+DASwY0EPA/icCX7sQ+KQYRK1NuUhv+lNaV/fpZR20N9dAzFF5NwkTm0tIszQ4oF+YXda1dDoXlEIUyHAcUetMPuGQ8TMzrc/nr/I2yvL8XX2MtoLgvLK9qPuHM0ZMMFMMERLCMpHJixHcdy+94tFTQQp0H7+CBJ3lhgnfiKcxBmN8ustePybhBwPbA3bGz1efHtozU9yYEZWwsCQ4cTRgceenvxgRDyFnsgaE+mU7kBwpt4bLmHXUL4YePhSJCy2d9hi9JiI2hE38K0q9y4rCaRxMPduxk2dW1MfJLLfu8qmAYy6iiyIZCBbyuhdagBnZwRvaXJcH7uibCL/sin9T/e3h/tOqA=
*/