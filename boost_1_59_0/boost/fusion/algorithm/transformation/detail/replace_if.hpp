/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0946)
#define FUSION_REPLACE_IF_08182005_0946

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_if_helper;

    template <>
    struct replacer_if_helper<false>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, F&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_if_helper<true>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, F& f, T const& new_value)
        {
            return f(x) ? new_value : x;
        }
    };

    template <typename F, typename T>
    struct replacer_if
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer_if(F in_f, T const& in_new_value)
            : f(in_f), new_value(in_new_value) {}

        template<typename Params>
        struct result;

        template <typename F1, typename T1, typename U>
        struct result<replacer_if<F1, T1>(U)>
        {
            typedef typename remove_reference<U>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer_if(U)>::type
        operator()(U const& x) const
        {
            return replacer_if_helper<is_convertible<T, U>::value>::
                call(x, f, new_value);
        }

        F f;
        T new_value;
    };
}}}

#endif


/* replace_if.hpp
J6UiV3URy+YV44kBUNTy5QQZ1Ko6YNZlSVTK+A0LlHIWTFbXiPoA8ep4a++1/4gDZKI38KUjlnRU4zWlrLdIscKXNMdJwUoptYid/qMKs61PuGr8ckUS39TtpqapSWHbUO9o9v4yDvRphnpBSVeT2TV6vFC10MUJ5gEuNEll1rTtBEMdTIwAXeloqJeHqPxRjgpHyefEJmBrfPNqncXc74OdhkGyYtl4ZPzqgOvdu8xtUczQSk9/sN2CeYQ0xaRgKCjUTbRMAmcx/8LhnZ8vo5imXyI+dBQZNcVIJcv4Tx1DwwA5QSRU9F6ccYrR8IyKyMiWzYTGNh+HJEAQYWKvcmSb2VU1XJfSyezydZ0wCniUeW//GoEg3TtTcuBTppGYM2e3pv11rjm15vS0/aXM68BzxtOZbIF47eoQpl1TXaavv61KZ0oBl/y49oQcjt32thM0hhHfQ9rQPcgdQ0c0N/gt5OUOGxPAmOVnaIT6G/tnzhP/AqIjTAKyprAysAbRfMY5WQBJ9JaUthcV65FfkJtfVcwY+TgR4YPDwS6AOUF9TdFRERhcknwZ5Ff/h0QZN0Qixo4giOuXKT8ptgkWlc94r2miHkG3WrJ2ejAJXseeknpAHkNU/oxR+/pYc8CTiRyp5r9Xy5r/kp1ZLGnQ3NevRX78En7N8Lcbguta5QzsnAeEt6fmaH4MIuaTiuh+dUj8YmTGlEiLwIm0QnN1FeViK0vpLSX/YWdB+SjP0uXzimGfYzkCucl7C8BzgR7u/0vkCy1Ym7Gn4ioEwPqvICgFnnpxtq8aWQEciJEhjRStgjETPWRiCH9aR3FJKIIMnsQJEFknkhDuRUifAXIm3zoBgG5DhxQ2X8H/DUcap32j4yimS+PHYIe6cghcXADoTDcVvIjhX40BMHCcJYAiowSGUwO6kyW6OA8DMLUhNx2DwpLVA7kCeQWgSPkLkjuASDfDW6GokSEePvPgkUIJvnKiasSyaMJ0CjIY68AOU3Qdfgoui7wD8mDC2nDKkCaHN1KunpVpZZ4Sy9zpaq2fMFWQPRVdKyYiujxFS/x0HnWoLkekyuxp1Ldlx/GhDkTZhkR+vRaeiXj3vT6AYFU0EYTATm8U/eNgGDW/pjqr66smTu/DBHgHeIt/UGwRIMIkxAo36lMBkKqRmgekcDekMNONal4F6GM0p8esZYrbrtJDjhLVbXu3eVI29D1wZOdhnrorCvlG9Du9gk+ckE/chlxuBteMKRgTw5BVO/KKig14r2li3HXMcWNQshn2eiJWAhJchWBZplRUTVVFxZYiAqUa3eiMmxuOOgJfqG/7ZR8m9PpWcccrPjK16mQH2VGZaV0lhyNne3Pa2Yp+wJ6LEqkRxCBCNr++Ehk1yGVC3sB6e6fGf7vZXUV6Po+eDdxdyU/Hco8HPu/fgIPbjsrJwDP6KVHX04+pTO2fjh7G6hODTtUPbRXoT3z78D79PK6QCyoV5/Gdps3vvGqWO7ZgnkpHTwWqgisssKsBFcTdn61KaeWJFM8Fb5dZwm3sOenPFk/sIQcJaEPWLI6ZkuPZUJI9qOOLB3Rk6/LHDV1bQrEIqT11qUo7q9TFR1KoL47Eeqh+7ankdnVd3EG4tXltx1BeHJAXopI3GmuT8VtY3Acsu7GiOsWju3rllD2Si51BPOnszPdlXoBZfrkbdDlKn8l+Y////Xe0me6VbU6+0s5UcXhCgM2aVTrhp8+s3iOFYzMCnheB08idoysbIXxJB+wWp4HAW17kriyiPA8UuhaYqn00PJA695h7mDrgXjOQbEECFzAIG3fNCRJ3xnTIU593SDNpzlHqOcUBNlfCthvvWXK6bqLmtbVAPuGsXYhvJcNTxYhKx5pACEPRq0qSoAHG/F08TtL5VWdbXlIHVZA5yVnyFpQg4w5Rsg45WE3N8RwGVbDiiLLiiGVSQLyWLllFPBjc/V38nWiHPYCpPirF4bUoyZXwPWXzofiVICqqTPew6bLNDsRrC/WD2ZlGMh3oo11PO8OUIGeRbYL7DC1pBGaiPVe7Y0qQo9QgdT9TYiipBqD4fbq/RhpSqpk3ilfvKE8hIWVjEOZpUXptqz9CermtzWbM9HHsdkcUueN83M3gCIaSC66c3yQ2b/LsjFFtzgQbWhlyxdkH8NxFsnNsIXceEXW0sdC/mlkj9szqmsHXqaMqeVczxKZYtqDNjAD5lTpvmdJ9cZUT7U7Ciga8dLcRHjLlZJK6mD/aYBrmnpoijkonRlFcS5yCPIvqOQ+5RoAAJUGdtQbRVdNQjJJN679mTmbwpnbcVyBGZrvGNlFPHsBA1dl4t2NUj9fhDBDhndslatXZ8/XjR7YoKxODH1OHamrigYMLDngF23gfvSoN/i+dRg31DOAiaCl+VD9gpkVXEkCfmpYOjJZvRsMGSoPeCLrjZbtUtZ1fs4eJz+KuD0Xd79sxqtvUhwspj2eR42Q22tqi4ZOcQ75lim84eppgh1/seqRHIkOwE1Hhzx1m3KHD94/s6AV/K2SujKLyFWJXw4QhPuys+XUVfTBTSc1jczN3shNE1qYVdF6WpxyRVOwEOkOwjC0Z3vpBRpJ6RRmJtyHZyaQhSRaf+MTflZXbcEAfeTzjX0rXlooYLq3lebkDnJ9O7frjrj0J3vPHPbysDEStKf46sMP96k3XRqF+2H+tsjLHYhRAIghnL6/VkTL2KG0bsXQN66I4y0aurWs2fSyuSwqigL97ZUY422I4IU9+T4kKYrjb7+Y5QAgQObIx2TONFYF8rfGR7ng7p1A235S3iRTtJL4yEl9WkHQ8Mhow6Omc2hpsBq9c0gfHdacYGPOVrpR2edxqn9OwmdGJHS2diXWnh61LXSKumU8Zfd4QrPFcdzI2bWN33kG5KBiZcvozjcEXwJ3oOOSrR9xiLVW3ewbSrRxhpIUsoVjGddNyTQ7bjkUB4oYIe3GjzTJzieTp5mR8/3p4nlbGo+Z54whNze+WzsfZsH/byDUN2sgUC2KwkzSv9iOUSsUK3a+wcTBxIn0Z673N+UW+EzMJERVjORvImZfYhOlGrShmwkVFF5goXIf2i3/lYoickCwKB5/YmDGP3YRFe/ZjnBhEF7LB5xPNV8dtZ8oQrgvqzIi3UQ8JPNyin3KusCRyeSeXKLmdpR0ehnJyU2fTTZcYXFE9kt55pnvlfIOXCmMIMDLCcbE6mcRKT5ZmEehtCnmIzrvN3o+3ic51vqyoQxBFYqOL8Iry0Adqze73CuOfutvERkZugVPdjYJ786yL5uVGfpNfAXQqHZJ/bdBML3nKWDVMxubnwoTs4HQYLw+63UU8qFFIEmErw7QlpFQ2KivNib8lkEX77Dt1C/Q7aGQ+BsSwoGfLAWbP3IfizkrruD5cm+hY9Vp87Cch3cc3DJHabzTWPbcX2g2inD7vUoZ/DFi2XVMjLwvaaFmqaH1qBosb+9OHa/DemL19Lv1+M09yWAZKz1ErpBGztx4Fh1vmhDLEF14b6JpIwcofhRPn0bkTqR03v33exbS9CH9oPQR5YCtvIWMs+hclyrsvhD+Xdkh51sKULh+bSpZqmFxPv1vu0fqzbj5tIrAXN4iYPO23og0e2rSejoK1PqqJ8VR9F0+fzQMvv+6EPQPtxNZ6njB9l+MhXES/wbxFvyEOnSfkzwg2h6pju5e9TTnL6crpGKtLn2C1S6hBd5cy/MapoHdgVAiB4SLTpPIf/MmhtypI9+iV+oP8Q7hhUoHUelIK05CMr9afzLe8BD24kUFu9iLYJnXNFjDq/5XSNLpvIFLNSKtFzKRVAoNThdMP5uz5qvcHY0TWAeWQzPOCFM+3huxe7MSfWnJ5eaQA4MXQQPTAudBlJsYva0Z4IEuAcDUqj+KQONEk+qNwx6dV6r+ILSwp1dB2GtXQOmrWDz1NlemrpWa0zRbRBRhNMQl59HJjPPoGiEnT+HWFru+h14Ie58RTqn7Sy0x1MQ9XqmJkgFTAJ40aBVTaEEX8oCMv7MY5r/JLvIavd/qVtMfOL/8qTfvE1MidtcpISTYc5sbcb5Fe+GWuRtWG6ytVTKtqHOdCy14aEJh4IUG0kg7mTUYdo1AfHjd5yfaRAU++pI9pmL0ta6lHKp1HqKm3OFlv0kxobY7xNbg0viEw0uTEQLTUmXWea08f1KMeMKwlUpEYg4SYDvucGt0sHUx7ZFfuw8WzuRD0QhjeDJf0+cn/wo1fTPZ9IP4SQ3yhJfWRGXxUZHvmbzad1gOBZLvnPnlagy+CgcySis1wasYI9pzi5cdObGdEBauZuOMwVu2QMenwM7gzzNsLFOASZGj0GVXsRq1z/GOq8gyYDNj4V/ld6XnlLUPo0IzDlKpAEWu+GDD3qIUNvj1gqiOyjKUnEkKTpklb17sjrTiJ8YLflQd3RvY8BuT969u7nfJAIYfkB1npNoOZc9kO/ZL41BdTVH1VjRqv71cK/PnjA/1Se/Pf2qbyPtJCWGSidF2rVN0rw9xvXMAPGfCTmlAX5MYh/+2ivBvpWm9R34+HVpbRBhzKHJy2W4Q0+yvpOYKgBakGZhEVmRhYVJCwBoMbxDTXGOScbuy/R8YMJs8JALrC8iYZ4xHA34YcR2t9TSBfaxGN+oFPoIjXBalCfG1buC+GPXReJ9IHVHriTtj/XPe7AOlz7LFV53LzwX40IWCPCxXGetxJ7paZPMTz94N3QYHFpFXFw/4RkpJL3d2mOAIB26YgzPmpzMoELkqI93unPDwSEJ0unQK/JiY1CHY0WYf+c9cx8IlQqAQpspv+l9ihAsIDnFES7gWDrYDKIeSeNGEemQwPoPvUDKtRv5xg5H9Qma6BwzDJnK6i5J1tnBKCVI+U1o8GlnjDskfwbBZZTpBGRwABlIsLA1Vn2GV5ZtB9dGyUy3/nSKH73CXJxe+fhMhdcdyIxQYoj3vruKNqOTPJgtDymbOwVTv3vDHL8grRIcubHH594Q3gdXfIXzwG2QPqTbbeElYFUc9jmxKCImoWvNkTmnswinp4ZTXBzvQVdFk5RPrfjeFYFDhVbP3YUtHbsNdVSA8Jm2lgvZ86TG19WX7DSEYEJmUJpi2PzFVhDwlVCvuJJq6AdQ6G1EmU9Fkj8ZYpKXWcwwf1ZnGSPEcMCvmrvdonlOtbmLOWdfNXax4reHkouFfYA++E4qA7L4tHemHWxgqFXYPl8ZlqyVYvjNqn3jnDr6M7tpUjDlSmzySiPTvsAip2T9cY0DBD6S0VXJR25e7r4EFAUdgzFNzlKd4K2AOfU7fv0POHiGj6U8p6TScgYu1hym6hv9AIzlGbFENZfHyYA9Kt9dXnk6nyx0g/qmexr3RXr8OdA9YvZ7vDg4riJBssHJlDZE1mWbU1tnfgwuVtpBKWWeO1+0daKM/DE8X39ljycXz6cfzkZHFnFjtEamP1Qqqn4fxLD43ETw86Jq5ifBAyB/lPNsrbwfoes8GHz7/z6VleOOndnkzbOhxB2fkRTtMyaSgVsojij1eMFbsE2DP57YcyzRAfMDta953d5opxcmIfnepY4mt+mrQpvpuNoPukPbrr8u0u7QT8HX26u5LiLseEDpKjRm3aymi8hmkfkPLFfobWGuwqiNHPNvtUyjArperevFey8CABSr9KutYdJ5rqHyIdbDaBHHxf/OJcqQEeA+6V6hXY2TOK+FFPj+s7MwIyQItHsK6CJ2Fw+ipMJwXo28wjTwKvPvm5y2wxkdcZlfny1Xp6+rX42Y4xc9/nLuITKdgnNvX9FlqKhBwv/All4eUDkXZT4JAvFwiisQd7X+EPXO5nDi8MVGniUaUV4ras1S7bitfn4CqNklg9GKpztiiRhVV6qn65Ot3xhA1gtSdN08U8EOnsnlCVa9Bx0JvQHmBWGMnSWqk72Voj1mhqf0PrizWr7HWAUydq2U1EcKeh1X2HN6NjB3X4wdded/I3Uf+77ceqkx8Kndjb1a3ZeZevdY97Hhue3NsDCLc9c7RfY/ajpYMf/ZdUbbAuGiRu5XcBx0s1e1gB7rc95pDEg32/9B5GLikFT+6L2WvkFi1x3tK6QcGHdmINYwIHRXYO3J6IQFkokAn/AlQt8gXyLEMPCN0MS4J6qQRmqIjMgXNUxC7niJAhCgltVES4kO2/pkt5CLFMAnVjnDtF15ZgYKsnNbGthGNQCHHQABU18dPKANZ0/yEqnEKfZ4QxaCdTkFpWTQuMWtuGl3tXi1DMquvIiNX3acmKsXyeRxA7NESMS7b6oQSaqrG+TgJBmGFmCygc13jkHJsNotdCTh9r7Xuhn59RG06DbjNY9o4VmfMWM8VLW+4e9vl2nFXWCs2iJpIHdQR31tks8iAZ4rvMFmrWcr06jX3mHjB7v/Z8BE6VYhqCLuJKauuPzNqjZgGPCioeng20H9frwiKOui5VmOeplv5nSRPgK8gS/W2IN7X3dgtcifYejK4On/jKrqzJ93Hbxm6iVcuZ2wC57Y+J+ajyldcy+g2O2nE1fQ7bWvlUZg86bCp/ij93b1HwtkI+UOf3oCV0KyipLszzNATYl0qjvW80di/JB8DKr6n+Eeqhfs1/cGP53ByKUhzR4YDNs33x63soHiMXcKr1a9z0L4xDJ3Q7hVpl6kpS22Os4Nu5xFkfsxqmtPGMjfhvgOmCnUnzQh3KifFUMniI2R4MBOlJGzIsTlvPibYkNPXmtg1gRnrEVFE2h7XjAc33QY5mgOMus12dkNp+o/4GTuZXKMn64nw5+KadB4YveZKI/QBrXPDJeHU8yNFw/jD3PVBdj4ITEQEYkUMAa+kAFsYU3cY4+0ZFCspYWMBKiMWs2jlDrggpeabpC5UpNjir+6IWaAb/uuOuCv4SDM88XlrwlmFgQOrsAuBxjVFUeGqcNQaRe4fiOBeI5Q7gy7KcYvspTk2xFAQ6I+1xLY4n8/ffxZ3nkTYFbQcvt+9T69xVNVhDEVT1Cx/7myX4JNXiL4XsJsq7aoiAPohtn4vlTlHS5BshShwVajYUUwYYRZVmxLyWi7CH6mTKRzLmLTwHChtACGEFFBwZgSaIfXCbIYp9R9fTbgwvMzPT6+5OYFlLvqMDjNuZnvfuV9/HHXezk/MaE56XKcxMYC7hghK9RpaFbY4OITL9DhdTNFDAxe38d4AY/t2c8QW0R4JiDhwrbyU+wZ5+9tS0knf1INjexZzxTgvrf36TvwCgWGDmRnF4MJ3RLrr3fFfp+VzcjyjhKPgcC21q33D6Tw54NuC6i7OGQvNE1p6wBU86MzJfwOhXkA7tjaIQH132Vytmg+l8iX5+1qFMt4l+aDnJozI/X8yCjdG7B1SRsYO7QdFkgm+Faof2X+g59TZfU9aoFZNje7ejF3DxAo1FDiaMhCkDth5gFBe2DknIMK3uRBSi7Znj4mqRbSZQEwyt1kIcMzpyoe2KgVSJDFXMfdtwu2Ttn/lZBzVk2EqSTiaMnMmgf22exE68iSFaJttlWbtXqtDN7w0Jbzl33kW8MMktKGGSZl58Sgw6+OT9Z0CFcc+AsiNj/EhTt7WdzMBdFDSNV8tK4zXe6Zgn9bVwnnvQINBiL5iKvWay6SijISs5hv4caMCRMoBDf305if6cA6B/EIAjAv050v05ioE8xSBemAlXEq8bSv2j
*/