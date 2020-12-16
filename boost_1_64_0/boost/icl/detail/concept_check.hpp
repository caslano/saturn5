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
+UdJ9p0Yle9Kg9Qp8FRlqHtRxV3vTKDG4dZ4qpSGIyN9WOvkc1SxyhsLnI/TAysVBJvYQk+5hUZddaKUNVKI3lGExYL/Aj+kLeEYUQyrqycx0+4jP3Y4kfQfEu9e+oDqZibyJZFKZCRE5FiXTVlSTXz8TmPSm5rPxScE0y9XTnaF1jTynQirXXQVdmfnMEulFxSsksczlo0mu/mtrGCYCD3y0eF1TQnkpvWVfWl7QDOzy3lPZj+ejt3MvIwZPvkkYWR9PumeXI/YD2YUEZfPdC8Dq/YqsESTcHw4tYFuzVXBjQlTmHunEjoK71Oo+3OSy3kKi7TluBPkThStQlP/p9A843r++jB+HSOkKKOyR2VnpIiGlSSERGhbZVWiEpKMCiElkURRmUVZkRUSolAR/qJIoUIZSee6f/fz76PzOt/zua73+9NPXb5wscacva9kD52HnNOqOTz757BqhStGmQ2Cz5W2Qu/7GhwQb3g4MRN/224RJoMCOO5NA6foX4Hh/E38NCOLoUGBomO7a9QbrTjvyN5IqW8ttXd1Q435ea72GI3qG+eF3c8k3hj2mxGzrvBsm76MeOGO3SVrEZVziAV5e4XaxWKc7WlHal+EX0m8yClxooXSVd6aMJv6Jw8gvPN6GtWmyw7moegblikb85szZ3WIGHjmI2PdryG6IRkGIZqIPmiJyHvL5b645qze8wQbD27n3AP3ZAvzZPw7ksga6xHUGjOSfd46oeqyCp/kPkP7vr9kd6tPCFnRTaSvBnx814itSv+4NyheLJ2wCza6pawu/cDcoiCZsH4RM/w/Q2/FJ4xvacStoZtw5t14mXo4E+UlpfLH64m40sZP2CQYwXt9ByS4zeawmoUyNuQFPJks+94tQnif6aL+RAAOucZS0+A192uEY1BUIvsFXsbdaZX0DXrGUyHlLPLLRuU3bTQatKDPkqHsmBvD9NDz1GzSVERtnsd/6keEhUlnhC9Xx4UbJjS6ZEyPSSOY3S6IUe/sWNLxAHdoXOLf2Mf4qpfP6ft+iMUWT+FmnYLF4Wd4ILRK3MwKxaoZAeJAs104tN+Qd9f8RI33ZNneRp0bAj6zn8FNDHgWx0NbE5HWfIAY69CPOrOnMe2DL7aPd5GrS8fD49tEGe05A8kpX1m2Yjkzf4zj5ZnEqCcXOaT3RRZ+ixOTpjgjtp8WlzybidP3PzCmd3+UpU5Bx5o72PHRWUy9NQw+6+1E2fvNCDAbwybZpyF1VOXeq0+wj3XURhK6738tHD4UwCHbRJpty+GD/sYIqF7JC8eqRdg6hR/TmMt7h4fwoNMozO1+Cbbxs5EWsQFJSS3YMb8EsZd+4JB/BmbFpsgYNV9enVUhSkb7s5vmXGgHBPJU8yh5XGUzD93thniXULTQ7iYSdBvQdPAPojgTo1JKxZPKJhh1LVSuv96KD3wCeVUnF586vcQM66VoHxzEfY/MsWtmgPyTmMOi8BBEj0xiny/26Dg4BiVyP7UPXmDAuW5i4ILufLmunJVHVTAqQ0V+W9WCzVupyc72K7Ay+xFaRvZDUPAHbrjaj94LtsqkrZpYOHEQWv2o5hVDY2wNWkKDnrUysiRHkXvTZUj4A+7SNRLRJmWcPzlWPDpzDTOih9Bp+yfq3DTm+6cXafWiUCr5pvPgiNtCQZLhfthShJXF8FKpmnR578DVHU5Jpb/W+DPlLA3nKREXfGF5VmBsyyciZVsJMsy2saj1AtzrkY/TyXXU+HRR7H+Vgd8nXUXizt8csjZKuP0ZDpOJXWWn9LvY0OKVHL18Jq5UxvKflQ58Mydgl7Mh3zolysGmhnhivJpDvv6lVfOeIiimmst6lsL/mimbJn2XE04=
*/