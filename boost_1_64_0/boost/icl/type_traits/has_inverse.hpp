/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205
#define BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205

#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost{ namespace icl
{

    template <class Type> struct has_inverse
    { 
        typedef has_inverse<Type> type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (   boost::is_signed<Type>::value 
                     || is_floating_point<Type>::value ) ); 
    };

}} // namespace boost icl

#endif // BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205



/* has_inverse.hpp
mkldoul5uyP0ucd39J50g96LvpLx2c/rNFPveTsx7ky5Wf8W8Gi9p7uF791I9+h9Xea/A/T/5r+ACvU++t6M98nH0p36LKU79fD3uRnve6toKA2jQ2k4HUYjaCSNorV0jz5rWUlf1vv8r9N9dGc4+TnRYtvW+tsZn2A8msbQkXQUjaWjaRzNotk0hxr0WdBcmkeNdBFdTJf8G/9GcA3db98L8z1aTXdTsf6dVBNdpc8+7qE1dC9117+bukZzll/X5yFr6X7qoX9HtVhzmZn/1vIu8nnlCaHkZ2TH6zOyE2mSPgs7WZ+VXR9Kvv94mrbQj+kZvbdvoWfpp5qr2Zoxt/1L2qa54F/Tc5rjeZ6uoxc0F9KquZmX6OWMz2d+S69q7uY1zWOfpzmbXZofekOfBbTpPddb9Dbt1uc779L36GHaSI/Q9+lRaqYf0BJ6jB6nTfQEPUk/pM30lP1ciJ8L8XPUHOLnQvyM5u6+QnfQqox/g3sT3ez/Pjfjs8rrQvqMkj6X8e9fHtLnud/VZ7t/0Oczb1LmfLPPBT5JP/S5wIy5wS2aa3xG844t9GzGfKTPP/Ynn0/2+c5faF51m+ZTf03PaU71eXohaz70JXpZ86evaF711Yz5199pnnWX5mHf0JxqW8a86duaO30nY171css+g9Cc5vsZc6If0kcZ86VfYnELraBb6Ta6nfYPpechHyH/zG7Q4omL3+uYPA8nF5GIljnJZTTQt8NhH0R84N/KCfsgGo8H8SAaD3LjQV48yI8HhfGgQzw/9cN5vkxBxAdRHwQ+yPFBrgZRX4YHd4pGcu2swM7y7KzL4NxwEL5qdF7qGkYj5l3trLMkccl8rabAl2EfRHwQ9UHggxwf5Pogzwep9RXULp4YXrxnnBZhLRNXo5dvtRz7qqOdFflm6+CDIuPe/uNhH0R8EPVB4IM8H+T7oMgHHf3X58TL4mWd4mWd42WxeFmXeFnXeFm3eFlxvKw8XtY/sdluiYcj8fzoNKqLB4PiAXfj4IKbDvjszW9V1oUr42X97Jpxx+bEg6J4kNhn3r08b1yhD+y2PDMqiNrFypLj8OCKaMTOoqk7JLWlYtH8eNkAfnVOTl7yPKpFWMuIlu6BlvmJ63v1yEi4e2rUQ6NCftpH0dTIt1UQjpf1jpd1j5eVDp7G93RdisLpUSQ1iqZGQWqUkxrl+qiQH04NI+lhND0M0sOc9DC1FxX7oLsPeoRTo9T+WOKW09EHnfRA1faLhLVM/Uxnv2Tgg1wfFKY2XSe/dKd4cFA8ODi5Eq2rSl/5l770+6ZgED+duLMTZ/57Utc1dW+nBqHUKJwaRdI7RWoUpEbpleSm15L+4VD6p0PpHw+lfz6UXkEoYw156WF++jqF08NIehhND9Przbh14fR6w+n1htPrjWTc2Eh6GE0Pg/QwJz3MTQ/z0sOM9Rakh4XpYYf0sCg97JgedkoPO6eHsfSwS3rYNT3slh4Wp4fd08Me6WFJeliaHvZMD3ulh73Twz7pYVl6twinhxk7SzQ9DNLDnPQwNz1Mb74gvbKcjGF6vbnh9DBDo+lhkB5m7J36bREdqELJhR4qwpzkIje50CM3P7koSC4Kk4sOyUWRVhbWUqsLRbX0X6YVh7TmkFYd0rpDWnlIaw9p9SFff0ctO2nZWcuYjgARLaNaBlrmaJmrZZ6W+Vrq90b8KJ6jpS4f9YO/rlcQ1tI3W1TLQMscLfXzgX4+yNeyQEtfXwcti7TsqGUnLXU7c8JaRvxrh3BKoj4IfJDjg1z/6dRq9FO5YS3966iWWocfaH038WdB3198h/E9xncZ32d8p/G9xnebvM5axrTsomVXLbtp2V3LHlqWaFk=
*/