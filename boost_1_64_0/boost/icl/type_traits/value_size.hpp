/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_VALUE_SIZE_HPP_JOFA_081004
#define BOOST_ICL_VALUE_SIZE_HPP_JOFA_081004

namespace boost{ namespace icl
{

template <typename Type>
Type abs(Type val) { return val < 0 ? -val : val; }

/// static class template for the size of a type's value
/** This function is needed to be able to order values according
    to their size. This is used to e.g. prefer simple test
    instances and to express this simplicity independent of the
    type of the test case.

    @author  Joachim Faulhaber
*/
template <class Type>
struct value_size
{
    /** The size of a value is used to be able to order values according to
        their simplicity */
    static std::size_t apply(const Type& val);
};


template<> inline std::size_t value_size<int>::apply(const int& value)
{ return abs(value); }

template<> inline std::size_t value_size<double>::apply(const double& value)
{ return static_cast<int>(abs(value)); }

template <typename Type>
inline std::size_t value_size<Type>::apply(const Type& value)
{ return icl::iterative_size(value); }



}} // namespace boost icl

#endif

/* value_size.hpp
qrZToriE7734bW6U/cPHt8qzbyrlfZl4jxYHvm8otZ/6i9dAeZJknLHtWtEHU+nypJgOCc+K4R1410ZEi0+keiiumSnyHJ+nWod+5ZViSNbj/FLB1q5yegF9zw3veA8Ti1Hib/yPY9hNvzfD8wA/HRfewZV3sS3Z67iVte8vkBPmN2pP187yUf/1hXQI32Xwc7zzBcn8UMZn4TnZmh/J2zGj+U3fH9Z/Ilp+2K+ZYtu+jl/56iU254T7VZScVXO2jXPNHiisFju67GHb7fFikmlf9yLL+N1V4lerBpOdEfbbGDHtbewge5M+iWlylB/nYYk9/na6GNNpGT0vo0OUvN+bae8MZV8cX0/iV3nQMUcOFNG/zH1vMB+1oWMNfbVT04w37rti9Tb8fqu+nef8HDb/S79D4TsDti2k920T5NYwOpCRFH6XHmD/6zs0UTxHqS2Ox5bydw5/Y1OB3GfPDKxJ4wft9/nylk/+Iu/MIf//9+hWj7fvetnT+JFfYvjncK4aWqs//IaZR1djfjNntr4cOk5UhxqTOZo+W+RlQ6U6r70ivEtew69qxxw+2ZyoTpTSrS/btVe2pBuZ/czv1oe9fPhztvsx+lbz4zg+G0SGNl2uvRvacnZYv6N5r5GzL1ftdtxGbN6y3ipk21+zJ4tteCdSHBaG3+tTrZfHX+KeG228uDwXfhdOs462Gbl7K9QUJIzl30J7oL9alk8uv4+w9qfhmUQ+ddJ3a3imDZ+BMSC8axm+M82V49aP6MBWcWggIyW815bj3lrkuJt9a+1vS9R8MuLl+OVR8j3JPiY7F7Uj7ad0drPx5Tw6GT9I/nzc39zW7I/Sp02yv+bL8bNj9Jv3YJ610/jE3EXh8/hgMbD2yl7qWI7xWeST/bcxzfPVYO00fRF0XiHHx3WnP8K/kp/dST6b/1ilvWf+1R3tb/ok8mteBp+z791J4kqPbdrrw7uzreROeB9/qGPyZ5nbNXyvR/f6nmwcwPcJ1qfb7Ej3Esetw3esoc/cW4w7NV5bIRfCu7uxYmLt1H58LM7Tyf0kxT4sUAsynBu3UX+L8WxlR1G2uEXZA/QuC+/g16gn5CWT9VJ4V8/1EzPFji4fy73zyb2tv9jFiKM87D6J7ohuw9+9Mc6e44+oHmxBQ3gnRpwPmN+azBfpFquvcwpf0aPpCPam2zd0aMW3kyvonih31IQs+qbjTtc/62qe9h41bkFrdSfXfiwT6xj1q8AYPlssd3+g213OGzXIH3MuNe5b8Vuu/Zz8LvSLG6b+TWSjtWu78YM5X5qTVMhX2oYY8gvg+tHx9DZ3McaL991yb0I5u8mJ56vKAebmmhfelw7fkVSK83S1NjzDdhGXoXIg/F1OCtu7stfxYteP8tEkx0+Fz9/43bzKJPnrWmI7eV7vXlAq9/k2Rv+O8FnJ/K+j7Ove+orJHmc9Pnx+AJn07OHa3FjxCc+Qxl7H3gL+nN+GX8N3tYPln7ZnK3u/vdyfYg+E9/3D72fyN1+eVob39sQngrw4tHd8WqF62lpNEO8LxWBWnrpYq56QO69S3lepn+E9htON68yGSPqnmifuTyRbo0SdMyaLnu2yrafunGSdbSPh2iOOo8L7iHjPtWl19r1xOzuK01Tz5MyyUfyc4v4bIwbh3WzxK0ySg/S+PrzTHL4/tNYV7eTDMDGbbrz2YK46mSaXyRtUw2/TzB9pvf72XYH9ov6MocN0Mq/mj2Elxk2il33VIp4ueWSaf2VW+He4rdtTvvDv7DFsq5BPGD3IOmhjTlq9PUSPq8wd4bxJpXx03Ixd0wfKY+vfg8TwO9IAOdrePDKahr+h6MRu+kc4rnI8mR6zSuWPtR4=
*/