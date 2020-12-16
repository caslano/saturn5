// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_ARGUMENT_PACK_HPP
#define BOOST_PARAMETER_IS_ARGUMENT_PACK_HPP

#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace parameter {

    template <typename T>
    struct is_argument_pack
      : ::boost::mpl::if_<
            ::boost::is_base_of< ::boost::parameter::aux::empty_arg_list,T>
          , ::boost::mpl::true_
          , ::boost::parameter::aux::is_tagged_argument<T>
        >::type
    {
    };
}}

#endif  // include guard


/* is_argument_pack.hpp
jwiE7GdoSXoJztBS4b2Ibz1DS+L7PEPr9gbHzSkWfjXq/KxTVB6BwF8965nzpsfuq1lN3EqDn1iEq8OHdzQsN5UeOZjRBDmIOhMrH8fvComwBreBNNfq8sU/22uRKievJeY+RxWvT6AbeVjtNlJ++XaJHo+4bxoxzi1SdSFvj14JnRYmLpd9+0uDYb0y5g63PsJpj9zmuGtZFd2iYG/+vwY3IWhbbyPp8W8Q9UiVeuyi/LNkLf5Mtb6fZ/AT/M4AZ+PObIIecuRr+Z1h+ZpDIZ3ni+V5vzxfb4Sb/XnvabFzuPccG/umaH64FmNfumuTf3txaFODfc9WZ7ut2LQpnu7ZCyRym6frJfZh/coMTURm7TqpkWUVGYySv7wZ9nFtjFGuiuXL+YJmH9cmboo7rpFG9Lg2pxnjmsvHK2aGCTeJrrwD94FjfzDLW3m+YfAxy12j16ddpeiv4DnJrrek7JE2WKTXpdWpsOupdQubDBE3dq4MnbqXyb2bay58mIdz5sqDwPnClxTLvNDOlxr13Fq36yLnWeUh82fVz+7dFN0Pfy7P+z39LneWZw2FyOeYu1y+es7g8yGfY+5qunwe635zO1PuW0uK4PWUq9AoF8O6KZv6jLzQZodmSrALKwgXB97W93YNVP5HBLsF3gpkBFtrmfhI+Y8MHE0vDZ+DIvmQa8ukJLNu+NvnA71kPlCswr8K9mUkvRz3PGfLnR08LPDD4NDAn4MpKv3WcdKP+Mc/L28oZTXPy/tW0Z/PWaK9VdppcdKO+Mecnafn+o+rtI9R6YTipBPxjzpXT4+rN6uwYvZDnaHfgY6GaHbDZ+VNiTor7yekYzyX8uyelTeJv73n2B0V8dPnq723OfYsup9H/HTcjZtjz527anPsGXMrNseeJ3fq5tgz4fpH/HRZvr4r9ry29yN+eQHZo/aW9hupnrfr5xHqeYt+Hq6ef6yfh6nnK/XzUPV8kX4e0qh5o5+z4IqlTfZ6bHS753jsVzKW77jb7bv2c+BSjXmaRa8Q3/85V9AmPOdqz92NOwcuVc/j7OdcmXPpyfPkbGSZ23UNht/B6qPrLyo1enztLjrpc0WbHczj/3m4jbj29jmepCv2C31WcnHFsqKy5fb5jsQRW+4e2uvuucRz5oJZS5Qt1/V/Gf+z1P7Ouve9+zvVmOaZG5/dAWzE2UXCV4+dwyi/vLeU3WOXtcnz7fPGwntdXsecqeZL1grv9S9r0CaUtSX3Nu5MNT+y5tZ/yNmxawk/pv51nvrXlFcXOW/+fubNxPWcs1dbXbTYuo9G02ZqWrXuin0w1ndc6K3n/dnO8IPWa19SayEVbZZBm+WhreUZWqw5YdrOBm1ng9aV54IOgSa/c1MHnhV/xJ4kfpoPoj8t5wVmufYoqRd+lFXsUVJ+U69UFoQLdL/w526Zs6812rqioLRoeTHnxC8tMdtZ2zA3KtpbAgNo6ctxtvYnPXOOI/vLI3dz3qXCfxDowzz4YpxDd0YOAaydkr3A6j5UQz+oOcBNuMIOUAm/s3zPeRW/VZrkw7PKR+mFP94b/X7Z/77w89+IZ84nr1goeiKZNMGO4OekVQm9y7vaSvu79sWKpmXySFK8mVtQC5PWWPlGWppv6Rn626OeZ779gBN6GXPSVuKHzlZ+Q7m7tEfQiXeTksIVev9oFtjlQYfm5EB/iZfFU0j5DQ+0wVf0mW6nHGmnLao8Dye1Zg5aE0wO/Cgp2Xw30XPIJJXWBPjaR7+vOPq/BnnbVsj+Pkf/p60aq8YF8X8X/4WOf+tVvcyzM0yaA9AUq7h1Bxz/bPHvXBQea1ou44RALtEzw4a4YdWE1UendwVh9Rmk12b1JDfPu3g=
*/