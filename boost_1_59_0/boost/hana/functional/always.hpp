/*!
@file
Defines `boost::hana::always`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ALWAYS_HPP
#define BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


namespace boost { namespace hana {
    //! @ingroup group-functional
    //! Return a constant function returning `x` regardless of the
    //! argument(s) it is invoked with.
    //!
    //! Specifically, `always(x)` is a function such that
    //! @code
    //!     always(x)(y...) == x
    //! @endcode
    //! for any `y...`. A copy of `x` is made and it is owned by the
    //! `always(x)` function. When `always(x)` is called, it will return
    //! a reference to the `x` it owns. This reference is valid as long
    //! as `always(x)` is in scope.
    //!
    //!
    //! ### Example
    //! @include example/functional/always.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto always = [](auto&& x) {
        return [perfect-capture](auto const& ...y) -> decltype(auto) {
            return forwarded(x);
        };
    };
#else
    template <typename T>
    struct _always {
        T val_;

        template <typename ...Args>
        constexpr T const& operator()(Args const& ...) const&
        { return val_; }

        template <typename ...Args>
        constexpr T& operator()(Args const& ...) &
        { return val_; }

        template <typename ...Args>
        constexpr T operator()(Args const& ...) &&
        { return std::move(val_); }
    };

    BOOST_HANA_INLINE_VARIABLE constexpr detail::create<_always> always{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

/* always.hpp
71btCT3hIdRftI3xb1GO4/e1qNsN5YXNSq8i6LOpJ5x1kEk94Y7dSk/Iv4HcuRN0Du/R6qwmn23VrZplE9rqj/Y7y0h5aiT+ColT7GQebOzm8xgWH9O3SOnjqNwWypekhUPJQN1kNvBYw7LUXvL+BIfPHu2fFzHYl0nGkUwdlGHu2ynUa/K5ldXc+fwM41Y7sPjrju83A/D/oJTmZ7LizMXP7yvSz8TK78vbTnSufiaBdiKK3/cyjqa+Lxk854eZziA7UVn9TErbj1NWfk/ZiSh+XxY7AAYs+dOR8NkszU4keK3w1bejreLviptik3+t44xSZ7uXq+OhtsZVA+6I6iL/DhjwCAPe3jg2MKh6G+O8mQmPygKe5tZxyj5cjlJYWOgQJ8XFxdJnR7hm+taWA6KW7lR6oHnMKfeDK/hG47kblw+vubDdnmFj2jp2qXoT7nRKPIjHubMFziMry/MEab/34wF+9H8m6o8DDa2ztDrfOdzppf/9Bzr5XpQnHnDKsZf2MtDdstJ/005k0n+TtuzNcJJ2Iiv9N+1EpdH/z0c4/exEJq1Ok7TaSqPrS29SX44jw64ivrDbR18vf8IZZE9ZivE5Ogpjgmul0Vcxzy7R1wuDvv5WP76y0tc5OC9P+loe66nzoa/W9RRFX63rqUD6Kmw4UVzRV2q9kQ7codYVdxc5yXXIs6JNAn5gkpO0v4SMdpLy+iT0lVonHMQ8o/IidceYkHGw8Fwq32KXqc4S8gCKjBn+8SE6QV7vArlQ2G9E7HPxJ/wR42SsdBVdXWTZEH/WuDoqS2wHqQfNkB6J/tfjZJ6ObBmrPUtGqR4ozwYasaoTjRxR1ntEHt50I6OUtc5/AQAA///sXQd8FMX338sdubstx1Mu9BKaBgj86CCIJCShKD2RIggJyZEEQi4mh1SlI72rFBUUVECagID0KiiISBGQpvQOClKU8v/O7vXspRFQ+Xv5vOzum9nZmTdv3nvzprXmLFwsIJmzcQ25JM7KxeCO48pyaVxL3CcjrCKe4gC9VfEcF8p1RVgdLgxvs3RScU3iGiBWKsd+jvhpctyGXDuuM9eWa4b/ryIsHLgoLgLQAn9NcW0CbCSn/HYcDaCW0RqavdRI0Z9xVDFGQ2/001CDSSZaFyrS5Y94GT4or6F3NhjpMq5zAGcBeQdoaD6uZfx1clwHnNtvoD8mIAzwwxYN+X+soYsHNXT8bQ3FIO2xwF/HlcU9/YOG2u9BvMkaOjZaQ5OnAw9oOEJDFkBfwHjAcsBhwANA6ZEaagzoAZgEWA04AbgJMI7SUCVAJGAQYB5gK+CsHQR8o/VuDXVboyHtWg3tRD7aLjRSCso+EDAUtJhn1VC1tzQUvE1DgxHOyvM98piAPC7sr6Hf62hpJa5L7WCrqTy/FaeRaaUdo6HigI86a2gZYALS3ZgIXDcNfY5r+XgNNVtmpM8DDDRyjZFqRCvfiLZoqLbZTKxentEo9fNWiAIv4L7mOiM58G+HKMDw61a58P1DFGB4caEL3ydEAYbfutSF7xeiAMP/7IbvG6IAw191w08MUYDhhS9d+EkhCjB8U+Dzcp6/fICxwHM+foHHAmhgcz/6Bjy2oEYeSrI/V9lopNaAsGYNw8JTrSnh1l7JUVZrUpeY1AY9bTZrMt51D2uYGtPD4oVj8RvEKG1lFdJ9sAm0B4Tl09Hb5Xzze6d9ucfv0YV0mfJ7s+16avJ5Hjq4Xk/9d+vp1B490Q960m7Q05uAObg/iKsEfMTcPDJMwv0x4N7Fu4zfpY16VX5fPFrr5HfWzh38PjZAJ/N7kV36bPM7o4M7vzvoFwR8sxVI730jncL9G7hn+PU79FRhjSTH621/d89wIxVFeTfl0VGtbXrakUfnrIO/9unpBzzvA7BvPQSw9vTtSdAX91/v1NNJFt/tnVu4fxZhs4oSNZysldsYK0+bQUZKGmOkGNCV4Qw/a+n5E1pqOcNI/QYrbZG3x4/4Vk8PN+up1QMttfpLSzu36Om9rXoKQj6nDjOSbrORrnyjl/PUEfQuc1Ir32u2amndEC0NnK6luWv0VBO4uYB6gPdK6GjqJCO9OtlITfDcEuVm+Z01zUjDkearwBUqKdIC5NMfMGiMlmInGGn6RCPFI+yrD4zkh3ilhhrl+lg/SUsR84x07XMjfYc0e001yuWsNVwpC6sjxtMMWqF8XVHuCrgO26KUseRDA1lHG2ko0is7ykhfIx/7kP7r04208bqWLqJM5ydoqSvayTDA/lNairyrpaq3tBT+nZbKD9bSIMAoo45+w7WgXkcb9Eo9dfpVS1f+0NJR3G+epiUd6HHqO4VGLO9D7mup/ngttV2plfPsP0xLqy6Czmu0tHmtlj4x6eQ8BryvpVoTtXToay1tKKijS7yOmgzV0hfvaOkyvtVkrpZuDNdS88+0tA+w8rCWun+hpQfIf5VdCn0dPDp5HNIRlTZ4EPfdV2npFquf7VqauUJLvY5oadoFJY+1RmmpC3hhJKDKJa2bzCoaMreYjg4Vgoz285RfNQDz8E0/FfzeLb7lXtHjAVQG/DRln6J/5+v9fMqjrx5BHtXr6S/Lo3OcH7Uq6Pe369/hWj8PeRRdxI/evqehRX+m17/lQZ+syiMG3vJo5XN+FFzGjzjJj2rF8ZRQyo8abjPSjgJ+ZAY94gHJgF8A5fL50dRn/KgYwtrn8aN+lf3o1/uwfZCvNx4C/Pxk+jLY0cefIgHhB400rrc/XS9iJo1X/UpM9/1gpDxe+EKAN7eq68lNwJf0wouAc4v8yU8l/s1vjCiH54/lY9B2yFYvfADg4Hbf/Ngb/NgM9L4EXks6ZKQ+PYwyL57db6R7eE8DXhZxX2cn8vijkQIPKHKHtVcHrzp4kNULwzvqZc5OJe73vxqoyXSRjuH51E+udsq+szTOld58wHnci32N1CjWSLdxX/yAgdoC3gWw77D6n4mwYLz3XX8j3YhR3k/aC/0ebo3tnpgc3zIm2ZLW2tqLla9/MTM1xvXhQ6W8TYPyedBiB8ofethI795Q2iPLV5uLKOtpI1U9ZqQVwG/82Ui1/sDzXSP9iTCWj+eOG6k3IG8enuYhvO0J5BnpJALm31Jk8qfAzz5vpItXjFT3qD1/kYk2Zq8ULW6mFzVKvmKJp+AznvkynwigvUbIMYS1h97LyG55sRD/SHZLdYHPlp3+OO0Wdzvd3W45D3vlcdktp6D7m6Ac7nYLu6aYeA9aZ8VuiV2n97Bb2iJdd7vFkRd3u2Vnf5fdwvLLbBaH3ZKI6xXkg4WxMjFcV3uYw24x7tWTDnlwt1sc8dztFsY77NssrEdBnl7Du8xu+TAvT4vBA2WL8bQc/FYf94MK88SLPDUAbASMA5TledI9y9NQhFdFnj4y8zQqAHQEfgKeRwUiPnhRi/xQSaVfoybvEkYbVOXjs3t1qnItAN/o54V/DtAM+R6skv5+5EVNbr6MsnnLP8fP0ecOR187luvu7GOzH+tb2PsUkX3SbJYezSzJPe29kSS003kot1RKoatDfj5bkqfqwDXAdfthRVbu/slAqX0ylp8bSvFOfK+SvIf8ZPGGHjTQN5CF7X8xOOXnkF885eeXhwx0ApCZ/Pz4nEGWnz/j/dIHUGfHDWTBN2eU5qnOQ396rYwrL+6wF2nFI31GlwYxaZaomC5httQk7nIpM+n8XLK2t8El0zaCTiMqaKhNNV5u10yerSivLs9uI567PFso5lWVZ28IeekX5PHlsjwFIM5eXKsAKkl5qeUvSn9yb2ueDndCungu/xxPhXE/pwufoTxNbfdo8vSf6vdwl6c1XuJz7PfwJU/3tyIZQpvzdLsjTz/V5+l+ZV62t6a1VcLvoj56gQfeiuRpczRP3+A+pQbaTk2k9zxkD+Cjl9BXCUI9Af4E1EWd9UadDCnH09eA0+V5KlSBp3q4GgCxzSCb8Z22gLGAHYAuCH8fcPBFnjq14uWyOPL3KdLfW0HJzwNcK+Lb0cFKOxyHPPN4fwHirAPsBjysb6AqVXnqFsbTJTyz9+615ymkCk/lAZ8AYivytI1BiNJmJzbg6QGgGeCTYPV2xMCAtFlfMS+uFfDuA6TloLdD5lcG3x5k+auEsoO2+RF33I8aSnkO9qdK/2NTOC+3Q2/8j3V41f5KbEPQXgX/DGin1u8xNeGphIp8Xf6Kuty9iryr2cmDUN4AlfgXQINGXvhqgHkoV3OW3n0Fx+RMCK66KN9yfYldDnwcrcgdT39pC645/rfmInANBSYCT1G4ayC/mz5uGNcY2OZcIzlmKJ6Zd7VNpu91xl2LLMVzfaGJ/N/XV9TebSR7fR1xOnt5gBU91tqieMY+CDLTEjdZfV00O2nopu/Swnqm2aw9EvtawhNjkqzx3Fa8N8vgem/HWtd79+y0/rk7TyXr56XGvyrPFyyQAyX0dKCNiYLKKfHV+OE6+mqRXng9YAXe965gxiet4nzX+xR8uw7Cn03hM/Vzt+76eOX9lFdMT0zeB4FWavJ+7cumdPL+kpV/JHmfGGmiFa1M1A70C25rojPdeKdtw8Dhj5KSeaqGeqg9JoAqc462+/BhEJ5ruz2bNfkouIKZ2LVoBYVPgk8qdkOJodm3G84M4lXrMWIwdEfrvPQq4EpUXlqLb3wO3ADAZMAOfGvXMJ424f4PwKbhsD/fAQ/j/pkh0D2A8FNKvuaMyH6++gxWzxejN4P5A3mZ7odAn0Av+jQNNtMUfPulkdADgPKAdoD3RiFPXCqs1njYsBYuCXd98J4D14xLhD0bjv9p8nhU0dNK/l8bnf3800j1/H8HWmgQlgpwkyEuaznN6cLnDBXNZOMUOTJ5LHR9UgGPtpyE/AUDv3Gsp13dE8/nAIXH8TKtWB47wZ7NzK52xzv8OcyuduT9pOXx+CWYXd1MHg/sKY/n9cAf61mwcT4HviXwKbimMNnLiBaVmCIb1PiFVDLTBE7dpma/taBTuQk8/W+Cqx59ybnVk55+u/aHfjkfz/Ml51qCttPGo+3jakNdsdFYG1pSCtpSZ/QWWVtLw181rqpcJ8w2o8qK/ErSeuolE+DFidBnuvR4K/BVVfDz8F3eS7+xfnLkRN/6rxmgITiO/VhbdOpxexOkMwF0cDps85no1590ta8R83kqNoOnETNd/dbkD/lsta+KHyptjN0/qX7r0iMG2oVyPJilfNvhg1Trt/7wIZNPlh4NE5PkDv7cKmYKdmtj0flcbSwOdOq9iKdfFynta+EXPB143Y9SOvmR0NmPVv4C+RjhRz/iWqGRHxkWwgZewNM9xGuN62eAysAz+GShkrc3cf0cMAxx3gdsQtpvddDQMtyHtU1MDk1JiWBzA0KqmumeW76q//msM18dVWcHpMlhbWVZHwd8L8gWxp1sRkIP+6wExhsxcgz3eK3leQs2+f2G8jvxcmqRXIIcHob34+TvRuKtvvKb8W5fVctNG6TJQhPlMOW73XCfKt+zFJT7sEiLzZaYHJ8WabOmokaqVzPLeo+V+4sVPLn7bJejPj5ZzNOhFUp9BKxC3wtw+0uevvyKp8W4n7KEp2WIU3kZTx2WwvYAPET4XOC+Xw7dhfCOuPZF+F2k0wnXmUuY7dkCZY8CXULlPkFH9sGzip4ctiZzPblgDZ9lv0Xqap6Orlb8FhXx3pbVit+C6dqjvJnCXk2zpDJdgCxEIQ9LEafvOp7WbIQcwnX4Bp5arOVp1RpFBsyy57PK5uzn05c+37eJp48BrZHmy4eebfZXSWPIzbOKTd9+t/IdpVaSQ1BrYS7p0zxEvgx8E9flMv5V+XegvhLeKcQecaMSr2vI9Gnsd6G+cv26PpNZLa0pPVNk68E+mM/axDl8/xZPpXkh0/H894oKuabvCpQS/hvP/4eN508zCDkaz5/wqfaxj+eXe1bI1ni+o5y5PZ7/4SAtnQRkdTxftqdVxvO3+AsZjucznnCM5+/RCvRhHkEez2fl2H+f9xjP/wrt920SPMbzqyI+G88/fY8ny5885XtGIPrTpTNvqFqzfwCAQ0stfHVYVN/3NY20SreISIN0MygqAgLSzaB0S3eXdIM0SOfQDUN3d3d3MzD18vl933/OOffce8+Zs/fae+31PDPTGrqTmWXqv7/3TFawvffPb8Xw4l67Id7nD/TfmEgQZUDdEGGtsdixmJzoGGkF5Ieefoz6oQTnk47n3sxKmWSHNMTfAkxfpBxsOB9Y15wRUv/7G90kakq1bxLKA8DMm3rJLV5Lop1Z+jjC5Yi2d+MQ+8HTru7rj7uNihQMdcCmuvLzsO+AVA1uDyRHnShdLNO1vRl3B+5j4Va5A5Mumi4fqZ4lHeNFMZT4Iq/dQdKnxo6tWp7cipe6XeGXCpCA2Sqg0HlMbWW3JqKwsOUpuv5Vf9Lv4D5tcWiSYw7gaxKZuQt89G7A31QJjDC/+neZjRgsRGgZfL2cpH/4hEkE/2nxVrwG8ScCouS7q+ZbzsUMmaUn/USv4IuxQFZsZFPAEfcRLQmSLWXCjkeirhFns/2IcnyVIXUh8JIECpH33bhRYHTgAiLCblqX6W6VhMBWt0qIIxiPJtnjwROMaw0XqZe+oV6TJdV4sMuwNSN+K3ZsJ3bM96JJVRdWArtBm8PIwLLdfUDcngn4ssFCAY8bN65P7dp0zn8cpfIG0zj/EC92SipuF7jhoa1/0WlL6SjHPNRV0geleMr+qKdOk7jQBdd0TJZjHd9QEKVoNrJbaqohEc3hx/c9a6XHj1TRDbmCG4xVLS2ZNy4EH507ZA7xYnEMrkbQGxZeqZ1FRSXlHLRfjmZRvsYXtbntTRHR9utnAFjuRNCD46vXpv8VcQ5ZnhGu9PIQv6VdF2Fc87+9H8AMSWddlKQvt8uXYrVrOiVD7x6P4EovNJTRXLz7EESq2n2bidmiOXx6JBMqjmvDVfz0SIWKtLu7Ua/G1b6+sTHZsztVWk4L+Q7f4Wt5NJOlUzo/zFakAz23ZYirVwpw+ghfWJLi0R5PntHneGD0WfvJGtycwXz1xW/m8ex7wasixqpMhU3QwvKjaoK576U/QMD6QumKRdNVahOzL0aNuo0LhOysbQiWMhMzsU1J+TMk0QpD7ogSuCCVGkb4dIvsScV7Ole4gJSMMLB2UZx+q3jjggWN7KuadkUjBxLrPYouaY1W0MyHf3Az18x+usEoOTcQmRPQ9OZp/TTV02HnoqER7KPg9uv5GsM7oo7Ea/wkfV73v2sP15fTYyfQZs5j0s2/C67sHwen2jp6XT6F3Dyx1ZHRuRts3CWHr72tf73r7h16dSoJsmO+TEFB61BHuyS83cLjxDCjZzr8V+Mj9OTMMOOuwKr0Cty6whf445653Udo9u1gDcinblMPPOLV4arDcu+Sown2u3Nlk1p/vIY+XRNDj82q6runOMdqwEnO/uH8P/wedWP86PAvDoJjDt8Jw2sDqZ8DiamCC5aDhfvBS0QIlvoSk8LHUHMDTi+o+UR4XTAPFvtzny+IRJI5yeSQZ7X7ElzN7SP51jVO7O4tQesAeE6gh+/8vNwavQ/O853acau9f9gPYgNXfi1NFfM6XbUi2oReLJc4FXznzCHaCeXPKet746My7rIkn+Wb5QeSy2uI4a0MW6632uxkZUR4hR6c
*/