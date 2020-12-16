/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    unwrap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNWRAP_H
#define BOOST_HOF_GUARD_UNWRAP_H

#include <type_traits>
#include <functional>

namespace boost { namespace hof { namespace detail {

template <class T>
struct unwrap_reference
{
    typedef T type;
};
template <class T>
struct unwrap_reference<std::reference_wrapper<T>>
{
    typedef T& type;
};

}}} // namespace boost::hof

#endif

/* unwrap.hpp
5Oc3Hiay9ZUV3LUmJj3KvxM2NtQ+nM4nQYOqx1A0mjctOvb/ZY9C/71QSgOkAwOkg7cT0T/1AdKK311t1/OAmMxCXNDOMiA6eEBM1gdEOwbExFz4nRPzrayXyaLu5xjyqk4VzE6pOpU2O8H2yKZdLQ2B5qz6qrcG7HobZ1WzXm74Z/7/3LzrcENgU9bL5F+cwz/xj5ZBTb63bHEb+23rtnFi6y6o3urURI26AdSz1pc6nzgi5hOeTSjpNuc/nT+aaP64j6ea0OTRnScPizZ3RM0cn6fy1PULZa1bE7DV2wXv5pNvIY7Sk2/JaY+yECef3orbRdFHcyW8kxRoyiqy+FCTTZiTwx18LQMq0iYOagoUWXY1ZcUTCT70wCAHxlrVUOLBH0FmLI71MJkmNujurkBxXlyT7enrk2vHOeKa8ZBwa0dG3NHcVz19ETa3xFrZNTDCEjfCmttUafVtysh91XuYRHVo3bZTUQXWIiW7vkPrJzeslYszi/cop7JoOK/L3q3rFkPk6x22ZfAUHhwrZDppLO5d1h4ke8dD6xskyfWsfQ7qwWluM+c2e+xZ9YHnO2x/6Q4/HUMhg14dEyWDFmM5Bk+ieBJ7MG24K7GaCn/CjsKDTBGL9/GyOiYsHBRc/oTdp8X1E23313OVPbOVXr3svWwVPyeKop8jxvZQSOEDJy2uBBU0WQdix8+4AA6wZzHennTD0thkJ9Y1YggEssGy5KA3Neh1iGmUn4mRdSB+ymE9ViUZRRY3kZcGsQBCUtJTm4LXhrAMP/xwe3Biaxr222TKvgUWkzdxa/wQhI0Ra7CXIV5czxnnFhFP/JhfuiJo1ToEbWtdHROZvozmiLUqfzDiMHkSV8e00pFdOsUPSX48LrX0LhTtP+VMXgrp8cUyo7+zcd16bUoavf5CvnpGDa1v+yZ31lrvcTc67HPkm3stNtW0XouT/DgpD+70kUceeQ7hVQKCSNrUrfGUmxg0NJ/BjxeL7kORzx8gCy1eB9b2DggeiB1W5QY0pdu9k1fm4WdRHb1wFx2zVnbRGgc5X4suvZbccDfEOLEZPPpEKtnXfPPSTfMvaiw6jSkRbd82AMqnAVPWtkU5iLbetmxjYGNDYIZQPQytF0uhGHce0xl1oNr7uH5tVdSeXbLq11L//3FM+NddlT+EGyihCmsC6mQWsdyH3oXfR+rakUe9ZaMHk3hqAownQS+GDTKImgjjodhY7SZb8m08Tzy5dyIv7Iss4ZFER5QmI5KxJExuXYugiFV2gV8mRfduDkwZvBPnH2QKe4tDYxrWLz5h8mSR0CeNUA9C8Vn1BW2Z4k+b8dmh3fFjW1PfhszbKabBJiTSZqcVEb5auDjFuBiQJp9D0gOhsEId4QdoC3wEf9+ImqLPOqu+tYnN+WBzuKbonSdjaiYfoo6CoynyM8C5iqR727HUp3dmy2pepm/JM1Y88yt8Zu8+DbQB35pizeplVyxDe9nFeityQh/FZWLuY+w5TTFfBVdTJlwfYFeOkGUAQ/cjTbW3iEIQFsOCyXR6mVzPmzWwwX+hS7z7CmfZ04tMZMSiDgJXB3aI3VvR9K8G47MRGSpMpCM7DUsmHwp63xFrICz7V/XtIcyvoXobjq61khLBfiWZyJ9YvIrexKEdVG8HQ1UWy1W2rxa1cssGoHFUP3MwVPoGco1qBe3Hp1eoKb/5R+q1WdtwnfP9+HbEd9agCOI2bK1C4Vl8sP28CoF8Pkr5vA/JBRZY6VTo8HzK4UJq4t1IjLMYjPF09QVjPfEwFtl2FVCpm7JwCu6k9H+Qzqj/Bi+SPA38rk7+sU6+Cc3CZETnvZgu9SjlQX4k6KUuevoaAsonvhggiOE=
*/