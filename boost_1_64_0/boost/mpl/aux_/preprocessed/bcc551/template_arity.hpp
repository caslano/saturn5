
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
bhRJGwuGaNo1S2zgQBsLBXlXlkedQQxoeEckl2WRAE87Ws19m4sammKrXnVKoueS/cU0J+7eQ1XLKwbiFw/wcuVPtpcw+VJV8EXZH7t8nLZN9b5kR178XKZPfV/Wq9N5kGcUO/DaDuW1N6DDtoFpLBXgRF04W6uziUEedtXzt2U1Jz/zbX7Om84oBjUql7Kcy3o1AV8vp3ljfxTFXd7PieZYgUbAtlf4lbHzAJOrKsMwSm9SRKQpimAXyYZAEBA2u5NkSbJZdjYhoY2zM3c3Q3ZnlrkzIQHFjmJvKCqKiI2iiAoIiojSBQVRadIFAUUQAbt47v9/5/z/KRN9Hp4n7Pd+99xT7z1zT9O8047y8MCevPhzdp+N40GeL4/K9OCeHL0PhPNm3xfF55Ce3O/jHOp8vIQS0/zpedwvzGvb8wLdXQQ+EHMsscN4t+KTQZ0v+SzKn/lJHufzAt8X5c/CJI/DGYp9eKFifFxzaRPEFkVM9jpYHLN2ZupdnjFfonmiPQ1r7toTs6XC9JJJakcjMZMVkGhrhwee6Wyapg/wKD/G1ZVnmhoK37ssOl1HS3pwzZjP3L5qy3zd7cmzXHSKpE7HEZqZfoa0FRnjWBF60u2JwluZ9PpjJkdGnt7t6ijlbdXGvTp+dMT8cy2PSfDWDH0VJn6sz6N3TiXmWVPxt/g8qtPViEudHo+Y1Omaz6I6W/c56ixfm2nmPbsx9i/cPpmp3CZFt3M0qrVOtzrFG/uQZ1XsoQCqncz1XRuRR/YGOS5mqPIc/upevFJvNRGHqZ4ek7WoX9Pr9TR4n0LEtxl7u7mhRXxbMTuRwsG1M5rzM0DOoNWM2z5vGYC0tiMePxty7em0TXtmvePrTQPonl2lr/XaFNZ+CkdCOB0nkD62eOmCSnls6Shvo4d4rg0YfzaZak0WnzEadXoHrAs8/HMHv034Zw/F78SkT35bnxRwahH4zf5WYXLurNMkViZKxE72GX4JczzeHrCZ7vhUo0YftnnegePSJt/paTRtGpsfcD69i3mF5lisrJSW9y9WX16w92zaQ5GgT6nwvWd9vkaed7M21fP3pn2SGXmnZce1TuntrXQakjfvS/uKRFM4709z+iys03Dq+nxIQ5/xfaC3r5LT8KOuERz2B3tdE6TlQ+QzBT811ajqOUGo2x/WPOzpIoyPRB7/HfDRkLsQ+B4f0zzq8XJd/bj2uFcQ9rHVTM9DwrWf1DxI36c0C98GuP407XHzkrCfbcEGS2XKutrqvDuN/WyVHoZ3Opg/zYrZZxUL8/lzYNjA0USi+PjR6Ng5Up93XJ5nZ0CzWWb3VPwC9CK7Zgf59UVhURzOdKyezdaJA/+S5n4CiZ8V8uD6L2uemB92NrgVZ6EcvhLofdC/GuizkVdfs/qE7HH1dWg0AT2rUg7b/uQ3wCjXc1MAeIaeY/VmPJ/uXMtacTmfp5gQrK8Fc5NdEd43rT6j7oVrvgVGq9W4IpJ+AXSarNqapiTRWlvorjoj/y8MdK5rMgb2nZB3m3Bgv1nNzQoD1FC69ntg+LRbzNnsM0G49F0Uc4OZXWzZ2jjtlxBbWFk0ON+s7ars24cy/j70pTNZs1xeTNql0DCFlrTLoJmEyPpZrdkZsWA/9Fl3XD0PLmemt4oi/Ues0we1biejK2i/2Fg3d6vXszrGtcH1uqQrWXPrhXT5/SRgHPWsk7Vz3i+2N3dr4K5iD4Zqm5ONZkb61UrXbeMarc8cP2njea3otLKnMmu/fSy7ThitxNFz1K+P2Jz9bPpusCz6sstx+Zlw7/vCjaJjK3r238Q6hcE7tLL+c6Xr+aS/UDom48zM0G0wjq249KqwpjZgZvGdXXfB49k=
*/