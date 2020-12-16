/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP
#define BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/call_traits.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename Value,typename KeyFromValue,typename Compare>
struct value_comparison
{
  typedef Value first_argument_type;
  typedef Value second_argument_type;
  typedef bool  result_type;

  value_comparison(
    const KeyFromValue& key_=KeyFromValue(),const Compare& comp_=Compare()):
    key(key_),comp(comp_)
  {
  }

  bool operator()(
    typename call_traits<Value>::param_type x,
    typename call_traits<Value>::param_type y)const
  {
    return comp(key(x),key(y));
  }

private:
  KeyFromValue key;
  Compare      comp;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* value_compare.hpp
9WnDsE/Hk1Vm5l54aBryfEa/QTObFOxdBmOC7JlJ2psvWRB74r/Yj8iUuZUsK0w5jr1I39xkkzX7mTb0nZtpJdqMrBazqCd/y2+yJvuKuyZpZ/9oLL9r8lJrF83ux8j1uhLJApldTH7th3Z55SuGMBtXLEs/zJ9kWZj1H511B9qaLLNJ2tw89wcg9jc07zJrfL7FYfTfW+3+vGaB399KQV3e+YoTWroV9PfKgvbzEPsHXzHNS9qd8gMmoC6f5TnY8rRzsEWNciN2MgtM+f2WrCCzTN5txyKGL76iDbN+KRNXIgbFlj/aLr9hQdaX2YGDr3sh3VcaSzD9WIojywrTj5cEsraaLUs7r8tTdg7GEkVnYeadq+oRtBnJUO9vtpQ2dM62ryVi97GIRpZvFmuiqSHkZjWUl8kign2+2U9pMWStMht55rCIIg5pzU5VkvtYcYsorKVbQhtKbSyNto743iJG+36zxWlzVlKhBpgLqlJdzN9sEW1Y3zRLccQXYhHdbNLy31l4DP3e1CJ880m7N7hYIOo5yiKigqSFJb7OgthX6cvrfLHTCMS+1iJcrLw1y5atQbqdFhGopVtIGz617rgH+8puiwjQbIGJ/p23wyHUZa9FtBLSnI0+CcRAllOz+bThcOK9hhi7ZLW9pZmK3PmCdkmwiKNZv9m8tH3669sCaOsbFrxzPpc2NNi3pK88L7CISZrF0IZTwY1MqMsDC42LbzaHNkyf8S4n9od/LSLLd99sNm3Yu39kUdTlvUU80PbbWfS37dOZj9EuHy04V5xJG/x77d2N9iQ7ptmMtOP0h5YbYZ8suJ88nTbsKn32JMZLqt6mD9pwAP1HlhWm34+SyH5gFnYk9SFi+GwRtZh9evOyN2Ige+4lzd1r31fs02arqMnSPcoybDjKI7PAlPciyUpreU5Lu+7P3+clLINVfDRJm96qxWj0ra9VHLF/s6lp5c2qtBz9l9OK+XqK8i5+IlmkSVqj4Su9kS63VTRmlvQg1xK0dYBVDGfWpnvgRLRZkFX0ZHb2TafRiCGvVfQS0j77TjuKNstnFbmZrTjTKB51yWcQA1l2Zk8jmk1FeQbpXPmtIprZzMBffFAeGa/n9lL1O8v11qiPmPmWlef60WShzH7ul1u+j0AWwOzN4KFjUJeCeutysXcsylMstmK1Xuh3sr48z4X1MBeIQlbRiNnEy5mq4NyGLAezL21GNEcMZOWZxcydKr8tR3aVmV9sxx6Ir7BV/OgtbfzeDLWxr5Sk8WmStuFx3ZLIs7RVnDRLO7Zr72SMs2CrGOYl7eihETnRR+WtIlhIe9ErbC36nawls8XrVr5E7BWoXUzSLg+/7i+fnbRi3cnJtMHy3D0fbU1mgSnvqhtYjIHFkQXC9M9mJ5JVMUl77ZxSBDFUST9dDFkumP6Z7gSyxcw6Hmw0BzFUTT9dPFkVrR8m0YYc/uYSyLOGVdQxSVu9a08C6lnLKjoy+6tPKsZLUB0r7uv/SBs6RC0rjf4jq6XZROUeYFhdK54XnmASFMSjJagnWaBZWujunFlRl/pWkUGz8bTBcSquGspraBXNTdJ25V3mjz5qbBUzhLT99ZoGoS5NrKKNlmc0bfhxrhfiC2lmFf81Sav9YIW8r9jCKgoKaSsP3+uN8shyMKvz4E/5jK5iGbPVlN+aIrPAlOMKWSCz3LmqedAPLa0ihtnqPeYLyJMsO7MTnldLsa+0knPrONqw5FXkXuRJlo3Zvp/t8nvXZK1N0sq3GBCHera2CitLdzv1rdw321hFYWaXznVdiWMOWQVmmSuNxJiIJsvDrFDoHzEYL2T+zJ403TkK+x8Z6qL8/pdE5mRWdmO1X1DPtlY=
*/