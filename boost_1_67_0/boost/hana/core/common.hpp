/*!
@file
Defines `boost::hana::common` and `boost::hana::common_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_COMMON_HPP
#define BOOST_HANA_CORE_COMMON_HPP

#include <boost/hana/fwd/core/common.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/std_common_type.hpp>
#include <boost/hana/detail/void_t.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // common
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename T, typename U, typename>
    struct common : common<T, U, when<true>> { };
    //! @endcond

    template <typename T, typename U, bool condition>
    struct common<T, U, when<condition>>
        : detail::std_common_type<T, U>
    { };

    template <typename T>
    struct common<T, T> {
        using type = T;
    };

    //////////////////////////////////////////////////////////////////////////
    // has_common
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U, typename>
    struct has_common : std::false_type { };

    template <typename T, typename U>
    struct has_common<T, U, detail::void_t<typename common<T, U>::type>>
        : std::true_type
    { };

    //////////////////////////////////////////////////////////////////////////
    // Provided common data types for Constants
    //////////////////////////////////////////////////////////////////////////
    namespace constant_detail {
        //! @todo
        //! This is an awful hack to avoid having
        //! @code
        //!     common<integral_constant_tag<int>, integral_constant_tag<long>>
        //!         ==
        //!     CanonicalConstant<long>
        //! @endcode
        template <typename A, typename B, typename C>
        struct which {
            using type = detail::CanonicalConstant<C>;
        };

        template <template <typename ...> class A, typename T, typename U, typename C>
        struct which<A<T>, A<U>, C> {
            using type = A<C>;
        };
    }

    template <typename A, typename B>
    struct common<A, B, when<
        hana::Constant<A>::value &&
        hana::Constant<B>::value &&
        has_common<typename A::value_type, typename B::value_type>::value
    >> {
        using type = typename constant_detail::which<
            A, B,
            typename common<typename A::value_type,
                            typename B::value_type>::type
        >::type;
    };

    template <typename A, typename B>
    struct common<A, B, when<
        hana::Constant<A>::value &&
        !hana::Constant<B>::value &&
        has_common<typename A::value_type, B>::value
    >> {
        using type = typename common<typename A::value_type, B>::type;
    };

    template <typename A, typename B>
    struct common<A, B, when<
        !hana::Constant<A>::value &&
        hana::Constant<B>::value &&
        has_common<A, typename B::value_type>::value
    >> {
        using type = typename common<A, typename B::value_type>::type;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_COMMON_HPP

/* common.hpp
9AHjnO7ugpmsbBmU9mjx2M1/COXGGyb9QxSSlfpMhL1/etiUYWos5irIJAd3ViF3svJI4fx6V+8lKQnn0UAaombkgiIBhLR1qHKhJbO6a/UGVIWYYnLCBxZ+mfk7edd5EJURHMKzUZrwFMRWzyDzTSkAEJ3yyxIIwEX2gR0iUTQywxR51ORyBLX+dKAQr8fTQWE2AAIDd8qBBmRyJQRJCm2ZJxFUkgscUFKwD0WyBXUCbJe0s3EOM46kNHSVVPDjYGiU0yYE5zIGaB0xThNioPiuRgMJRAwhhS/E0uXYx6oazvdrJ7C/eakoRQjpo62XFYZjKJzN8fFTT/l+1pM4D8uDHp+07sDKwf7Eiq64dvAOj5nYGx/rLOXvPLRTT0UfjpbYmeJSPeBJuteAwb53vdWWjYFkjyXbcnkdOl43FdwYsN0ilhc8kWkpe83nC65qtL3yFVcYUIb0L4SlG8nmBeG017ZjZIuLmVdewuJK7ypOjdEuRMIz12jMp4hiLcUxCJYScQwd6TFIYrdzsa4hR9GW8uaEOBmncK6pQ0hNbIkSxhwYRgwYwLkcWqNFW7oMAMwi9vDHXn4m2vYFE225cDuzs1uATbgISBifmdpXzaJ0WY6/U3UyQ7arlcxGdZx4K7H/lOQpapt50H+aiTJZt7MtTBV5vX+DY/NaOjs3OcTbnu//ITCXOI4Qk0IE8jWfGFbvBqnrMvD7xzu4CmZBCGADAWhFxf7XJibE9nc0LbnBEQ4lBTU13y/2r819dAbWbWX7psFq/Jtqjzdy6OYvUV+KcoeOpWvCKVOkl9adcluCq2gHrhNeIUDokN2brTINQQET/MkfMgLSQqGGQEEhLq+CjsFZtFehIMmGrB/rKz1eFvDOXqQXMFrTQ+/1IVNEBAekDHhKYkQ8U+iYZdF5BmP0ib3C50P3P4ArARplA1gdniEXkNQ0uug7v4nxSuw1cXeVqjXLAJlU99Yom5ZW4+30ZnEruA5gUJu641gUxEUkNxVSx70jHw7OumzdDVdmAMz0XGq0wAEa9EnLeuphiKyAZKAQYioDoeDPlZJYkIXGOWhZgFEtZRn6gJEndyTxOclEW+ksr7xQu7G/EV9CqMyFsT6FJX7Gmw5545ZQI+jM03+DHViKUyK7vj2nwC++p6xlZ//6luXMlIzDkrX+YQoARA/XQm6oHN+AcKfhpunZcGXa7YiY6IhXnoVJS5q72U01ISp8p61OPT2nDpRVh9idzXYFXjWgJ+Sqdy9p82ru840SmLwWGGhElVVahIErhn4xgAfT92M/p5CO+6wKwcMZ44/bavGPJa8JI3yk0zzKhEjumwU6IxVeqPJaw6I9LAgLj9FIj3ak1zpf2FJiTuJsU3hqJPIwSx9qOXZqia2xlbMACbeVdHTPcbn4EfZo/UltytuZqsU0jx7qDD2GcdM5C7g+C2wtPTuz/QiqkM7OSpDA/FCa9feGpbZYEpEBIejFKGA3FouyZ55cMQPb5tigVTncNjsxEVA/AURf9M7xFqpCxd84bW3LVmK3t8oXQPggC7MJLi3ilRXMu1xp8ehY4fDS+Gl+QDF2X9dwMiqIRwpiz3gzuGjHwxnQZK7quQlRlJp0z9jTDtPVoBlSg+P6i2qaj7kJ2hDO4ME9e/cnpxCBqybvQhn6q7Tlhs2uh7gOEUgdeVoghiv7ZI3Yl9+oKJtMHuTgiaYYxh0muqanNj0O68HkZaZFX2QpEgtKdFMp5tE+mq7W8OqaUk5XOKBX3FoPGqqjGZBVg0T+S0pxq61+NTRmFuE7XiXxxo5wsuKzRJqPNiZBEzbxPrhy8e65ZNeqIfe13270pVM0KMwq7GfOiZ0UxNqIuuEQTV+Mj8GCldFD06ltLCFCZYGlvn8icSbVmlOnOuWE6RCNNV+YgdO8ACzvKDHfNOPdprk//wU/UwiJihtfyAXqcApcBh1rjJisswhWGUnQZrA4QTzOcM8vveO63VXXqGa/tz6ngt4KBb/xWCpviU602ea9LvYHFMo4misqBTmwva2Libv0+YdJK5v/l5UA2je4keGXQzZXs3ODeHyNmfBe57BIHkliHQHDBmTJaFzhgRdisCqgVT051pGXEZf+utuw3oJzkrnuF7iOFkkwNmqtaLDZC7TomkI+TzveaXLkpOnS0WXyHXn2dJcyrBxlPcRjLDdALFb+OO8hob60J8A19vfN4zQeh3704X7eWoETxkdQ/ALZA8GCEaed3Mcj/MIcZhJAzhD56pJnK62qBrSYx+jnaaUU3T72+9LCeKkRf+fn2pq45/VkjwdMWYd3peGvvMzCUww1utbuB/JIZdLTa+xnHic3RvX5eJZRZXNI9tByqNpE0dMqQp27/KFM9z2nsbi0jCrOR1aXaDet9jAd8Lu34S5WMEAHwHwAtIWwAW6uQhJxiLii04PSt34cb1yNjrbYrVOafMelnCfBu0tckeBEOHD7sl5WPxVkMV8Yz9Z6xXhpAs6LMpdNb+EsX5VBwNgBwwUS1Uht/jYeA7gx1PlFVxeWL8keWE+CqLtkawFG7PAd8+kdP8iLhW8ijwKhDm2pPX0X708fb80uJHGPrA3/ctHZ5QkHyLNle2zlEsPM9YsGo2n2Ys8bL7sOP6DZmzcvD05Ow+C8eNzl++mh8wsApfJGSKwZGBPbDgxoo2d7Huk87HUO0YJzRA0J+6pe+DDgr/hlSi9GR2kEbMT3NL29wQSvobJSUJTPAZg8cRo8k4tkfy7QDfoWIo9I4q/to99pyWJsbaDYEgfT8MHiPB6WAQs4IHhF+TVK2MaJ+cKN3WP7ahoxVbaXzGV8aD9sA/R7HzGQTODCaMixFwn1VKROqSGVk22T/0kXPvNgdpO5bvBDo5LaX/TIhou6Z9m/oPhB54EXU2I2FbhttbK+6z2eucwptdmi1Nm8M131yrKZlzPaazOX8vUt97d/axoWmLiRor3OVbI6AsyENua1KHscJzgtzfpMbjpyfgCoRuTicjNz7jn4g5+RyqLWNShtJRklveO7KjvEnkjDNo04onsaMeLiQiuJlvdFeqst4tSe3UipjcuSGW4L/iyRHsKaFRmBrDWP4Zb5i05wv6eb9kWrxC+hI8Vl9SzzkTr6vmTGMcAQnpz8zKGNjO1BjqeHCbcbdNjeZ8jssdJtAwGFrU15xwztRdc862TUQXmX+12GLB8lLS/CNOgVZjPlBTo7gOHQ4lsk6z3PBWM11LbwYZiyIDAd+cgcs7rlTxwiEc/JpctDwvsVB0HsZHJchluFOfGY9qxsLO1PxELM6Yw26G7LxR9agnCuj8rlGB3CvClNDDDWK7rCmCVBcAUEBxgCRLH+nC7jtGEAq5JkRLMPQYPVYOj4f/gPMZES0iNmTXiM316lvT/jiph7v+3zPY/8pUK8AKb6HgN1jWgCiFSZ+twx7lyOHgGaZDLT8OQhgWezCjAlyHaHyJMGiF9Vvsxg91om4L6B7Ak50QnozL1bGLFYF4FBLrikt1SuxgIujNVlDBHI9w/95BsYpN3dMBzji6yUY6lk8N9QOOgRu/MGUnFkmcdXAGzO5mslSfsz/o/SilsKwf+puhnNwmh6PXhwEYoUZbeGTgYAJZFgXjiHwVZ4mNLAfm9wmgfTT32amrbisrL5PJI21JDkN0o5aFXUd5O/A+ffoncNp1lHB9P1s02C/tTnMurULkeWAftKol/Lg2MTGaeQoVjk5XoioB5tGzGATBaTBWu+wAt8XZxaff4EUckpSIHvYjuNb8Q/S74D/94vMjFi6hySWYNusOMeLYhGwPh5gs4EW7lXzUZWpxLX+stZKP7Y/jbow30fb+gpgV7diMOgQNUYpwgDypnaiRD1FnPTUy8CAmvaIBNB/Blyyr2ZVEjJXHL9MPunlenbojeQnX+TYTzEjmh4yu+rS+k7fj7+BoDdvsIIJyGL45VHkVfeiapUXfionlOfnDgjb62+95d2tS9A4dkJClLSLtmBuMP4xlTzJQSqHRMK6Ozhk4Acacd7acT0oUNJGVxmnAh0C7xJ9eikRu4iW2VmflbLXAViadA3EIh53tZTukEMSNno3H/O/yQRqwc4l/Xm7MGgJTLkVOTZBqziyOTimfxYpzM0U8FQCvRQ/OWBWM+RvZ85Dmivq9f+rylj2iSEDsz6xVsu5nkpWmUBUKuVbVXKCEx7n5Xi7MMEbxQEKuPTLttDYU+w3Ixo6aMA/Fy3lIZCtY6rGQ7QeRi+evU8KFU+pVe5pE5c9Q6/C0NGNDNP4WadAmJdx20Novw25gehsbjvQIbgLgkXm54Pd+5CTvUEFJjrxObpdu9s9GrnhlGE/cssU3g40hOyVuE0Mo1Kxw0c1cFw5cN9AYDcA9UUo7ldorOMnfaEew4odcGO7CwkoXPkVmuWHeoRMAjx+3SdWfkyONNr7YXE2WA2G3RltNXZ8o0DlLS0c7696kLAHtWFn1UeyQG/2qKFgWH+bvCOuXahAy4i1BYi/WhqbdhaFmGMofAcJj91gZ3eUsqueElTQGuhbKsXAZsvhu0WqdavtoqbOpQfBHLjnOzfT7jhkXEwlQdOrZKkG6gLFEAjbplvPOumwSq7smp1kEHO8EPFVHvrKASRJxK6APGNAdIWOHzJybgRDdq32mkIId+2FI+Ewug/qgBETX8wJ/S8apwn62raj3qQVyn8xE9cfRAChbNpTi3ANLpFdxWEDhIOjLcHe/cueougnkScr2tBXhmLq2UjbvLRwieIEDKgwj14hEpUfPKmaQe74vr7WihtZu0fk9XxfUpC+DUXg3roJTNKycQYBtku8sYqdvNtGNxipUWgzdnExNjIm5IfRkDx4u9BRalqb/g6wUfeiJPTAHBgOXlHKDUSFnnPv4y5B9OmDAB3x6ShynE6+KfJY+aJApqkrPBXk3J4Nw2Px33UrGvC9gweN3BWScGrPkPxBl0bKX8Sei3bNlJpPfl33gPn45sMD83XKF+LDoO27pkuhP4MKOLKK4NI+zijpRIyO5YTCTRS0s3vH0vmpPKzD8HvAP14yw+LsYlg2KdsPPruyNf2HaLXouQRaSu2P3lB6bqK6pCjqjzZyNYbdiacBzUylW3LiKMMfwNwDhm3f8i4wS3J1gL6RJ3L3X5mWB6QBX56WZRBeL4ogC+okCJpDPKLj89BjAa+zAlG+gGz7okdMnzkEi8VmHh4j2GuOY0/v5f6EzuFz7sUxuJDM1Qstojk0Xbq3T/EDIiZBSqYVIHtMcX49Jm94OvHoR0k9DJJeSAsMhMpjLMlEm4W+M6BS+OskFKynx3XRRdPkTCpT2Al+D6tJwy6m88cEv6hFr9LCvPkZ7IVJV9LvCLqzJ8Zd5f3nzarehj8/WgnJjvuuAeWHF4brwtuPP7TDxWE0+DN4ALLcOy2yQc6GMKJQz4FW1mfIBKyfRO6a2hdWJ5O+FX62gJ4edBGHZaA6/OhUa0tSZfZdjt6tn3JaES+XC7zw2EQJBYSMXYHFRYmFC6wD4MSv2m0BDvOwPYu1ynfcXRRz7EjrUBHNF5bINxTV/LNgizFAdjoRmD+h3CR04DYW18yphtjhV1fOeqw42uD157v/SRz8VXYVhBMI6J9VbCGW4Y3QkpFk7QABTtLW3U0CaTIMcq6il975RfX2qCsKXLcDoVQDp5kD/iX14AU6Ujz3hyam4EQfTn0JIwYkSzKkVaHVa0pjyPw1zg4lZOrKNRIkFjy3gvHM2mN77hrTBA2DBGq6G8UNl9UOFKWz28W/nEUbsFonLEMMfKfeT6rIPg4k/vp+vgVw2lpZrHn9AltxBHz18nwYZ0Lq1s9QbZWtz5czxMzeTF9ciZp83Q1JlVqLEGuTK6wfFOBsxw9Qka9j0xR/Eel+FUwc5II6jKnQ/vCu/ar/qGafu+DlV6vwElQkQM8GrFA0IoYAFdAJFAjgpzE13MmsJBhpIBzjuy9XPJ468hoAICozOSuDjBcPHZpF+ffeXu4tfmOldQXa6h8uW3TD+NKLvU8bMM5lZYhxzr0DMeTdmYom4y2nkeaISVWmF6xktfFuXNuAgVRWDpwTULSTcIO+p3VAD9rFgVTV2EZkVyIsfVSUQAGEYqWJjIIOo1orQE4QvSU1EOQEinLeZ4xRxysjAJCTxB/5V21RxqVBGsuIz30PK3hU+vCErvBc21Uzll5EO9tts4yMrjM0aIQqc45ASOd5BXlUQhyMXz1kdaZMkwVztbdamSb16bcO8gQ6kl82VO5OJ8RO27TYYSON/XYm8tjx+JTw2ntMzWRY3NcfQxJ/UUV/3XyBwz5FbMs4jy2lXK00l3F6ljsmRtxlvJ+fSKma+hQ9nzApVLzznbq0E7ju5vrwIXIMfa+CUIv3V2AioDRJClqVTSIEcWAwJLIJdlPatEdAA4nqLp9J7Eq2raKIVUTZuk6l9qRZxAJYmi76syxL1YTerWwFq1rUZxYWaBhcILqwouCwO5gt5mSFvTWAOZ7oh8Hqc6NEZ3c7rn0BOsym6we33WF/vmdKEDeGhC/4SpicoqFjY5uuWNkI4wEl/9M80GxlsnbXxvfBgAAgNr89zLlKbb/KlRABBbE0XV4DpcxMhBvFdnnK1SRkCXWC7kGCUxNoQXbOtlfCTFyMTQ47kfMaIWRJkAKQ5Z2L+6+EScZEqqMQaFub1XzjjsbKoEIEYhI7anzmGP9BFsvetWv3/m6N/aV3O9tKr6arvwMDHs9bb25KD8rGLsgtpVv8LTWlWGDd1tecKBb1IL2cj5d7jX8KfftFyjlaTUQTngzgnSSbKEW8Br2h86Mdc7taI98qcKv+NOE543PNuyKFMmUKLFFWMWAaOhWriXepvReCgCwVls5/LUqbVPTN5UCvlSRStZ6NHvGChltBfNMaP93mclPF3xMVhhmdcSm+324Rl+chGuZrnaKOuoiYxT2mMYWD/RHgkLOY4IjFmf/3hSTtb3pLJPGskscUrrnUARZCRC7S+wf5CESTdhFixQq3wnRVWo3Q4EUWxxrfHBgOWaByQB+o3dx0zePjbp05ZfLBNZgLuHb//K0Crd/5kXSyanzIYFyM2Bcwmunder5FjBtEdebEBkucbSjqywbXcNuSRGSSCQ5uPZ1Wx32+XzcbXV2hy3+9VZfwY38tP7JhYw8z4Wc4dWt4SPTMk3WGzMRwpBnWoc06aZMm3htZMBNWrBOKq41qgnPvYDOU8PGMBEv5ZBxAyTDJJ0PCoABueCnuvFpL2GdDhLl0HpLURHmpolvXto3E0DS3dTx1Lo0AABEZWsHHWLeBDf99q9WNJ3eC1ErSnvDCbNNepWfdCqnpWo354KssAi+Y3k0z4fAVBQ4CtGszkycm/Yvny5MIvbH1HxaHLH7a3ncggzzZzh5bWTDlF/GXIrDYeuqJgddaHNI+FhAquGrn6+f/jWpTcNCizFqEeDxP0/iQnGWiWydz1H/i5cgOv/7gk7vLpiw58J8eEb1ZRxVlQLUes/elCafIPb8pLx3fbJflEZ8QDb1OklFWwB1wou/8ruSMckU9Si9lD3siIyJrV1ajPPSujvVr9BzdM0G2yfGjgVak0gi5L4Mb32iMTxG0Bsw+0KGeDxjPztxEed93mnm7ritICe2nUQDzkA24/V50LLc127O7olcy4CqnjNtk0BHllDP6UbIbSBJNgAcG3YY/xt2cGso1PJaZ4BuKK5jcUGMAd0c8X6I1AAAIs+NZLilmWL12HLER+u+69/Y0j5zXiqqAqcD5h1U0MqF8pvOi5orMwsjR8v4JVe1Hyd52B/dBBiSaaoeN2z3dYiuutfRac9fCu8tEp3y5D+kkybm4E6WfeeZhLQCkFxpp7HQgZghJdLv7gcBruX19D8Q52c88ts74kDpzkWjKHD/YeQQwQABeYNVOZq5qgjIOVjmI9JVFbcKGEIOV+YetrnxNOSFtPMIJTQIrgBbzgQ2DlpsrTqc05FvaywAACz/0ycSvbG4c8W+T7SMEb7S9HPSGscBsdZAbG4cxdfCddcwzibXHaQucHp3F1A4O31c7NqNJ1WF243z1vZw69nt/EI7VaqOf5ZowsmNp0KhMGDXeZWso6MlhpSUrXNU6Lw6pJCMm5FyIJDBfr6v42UR0B1iaSnm1Xx0r8Q1L9yocGAmALzV6nlTPd1dqgAAs1VH9W81oC8PZW5TBN0BW2PKojPdBkBkhokfAGo/A+lBxg2KBcWoeYuLa1y7nTfGbs1+UE/DhZT2ZWAgS1KTQsaC4PkYGXc+F6V91yW3D/pBoigvSx0sjpK5o15eI0U9Sa2UacwlSElOIUSJK610QXikrz4y6ThWKkvDzeNE3o+x7P9NVt7/IVlTajchghBZgpX05dmwzkQYAN94Os9eeojgZJfr7X3v+HEg7zFZcrA9bKIe1M9sDVvz2lzYAcgisd1xv4dTOz4+/vIdpSFmvoQ/Sa5x+1XsurevnqHJZRifi7Z7Bxe/9lnF4EqpOZig451PcUSjLxMfpO25P8F1q+3bJi920CIsC4et8tyiAhJK2RvyAgpK1TXiIKlrKG5WwKwuu7anwIbzk0snye+NTdcQfq8TG6DLMhAZ6RiYMEDiqqTXU1uWfd2VSRXQevpk47raZ3sNEqG6kd5cqdinyRbr55gx9ze8gPDeN7SLiSFHns14AWEx2knEsy5KrxZGwb6i4kr1LF0qgEF2o9gOODxXLOtZArKstHkGsdhL70d0HRKiBUjQ90qDmGQtiyMsdrb1e/FATDlO5TmHCjtWiIbGxPN41th6YGAK7DN3/GPzrmMJg4wBB7kuLKJnUsYN50TDf07StiiXCZlqYbluUNGoYtAqdVF1ZaW5kT2mip1UeT6puVnx5xZZKoaYA5n7g33Qybe8hfRA544zH0bFpaAGxh2VkEF2T08iJovGqGe+wDnTUFPpP/HX6g7pH+NIgNQu3IAkpTCoDDzgLJme2eghoTaOtLT4kMtNtZgm4EH1YTMoUjYRtlZx3jeB1ZXf08oTYpmlRcdXZgPEAm5dMLBgYA6eSeroUAD3unSclMs8G/i19h3ENp0Dr3ZxwJjKEoZnPksStU1V1P27a+LI1nYTQCTSsnGNBvrsbdASdyAYhKH6VYsvZyUp7Tksm0o6oSX3PEKgYE6NO76708h9ZHLY7l7Z0mI9MY37EoJCzHK0lvKMlpC+jAOEuI7D5rtvzTrQjqlaA6HJB+WU1wE=
*/