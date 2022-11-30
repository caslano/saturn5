
#ifndef BOOST_CONTRACT_OVERRIDE_HPP_
#define BOOST_CONTRACT_OVERRIDE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Handle public function overrides (for subcontracting).
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Declare an override type trait with an arbitrary name.

    Declare the override type trait named @c type_name to pass as an explicit
    template parameter to @RefFunc{boost::contract::public_function} for public
    function overrides.
    
    @see @RefSect{advanced.named_overrides, Named Overrides}

    @param type_name    Name of the override type trait this macro will declare.
                        (This is not a variadic macro parameter but it should
                        never contain commas because it is an identifier.)
    @param func_name    Function name of the public function override.
                        This macro is called just once even if the function name
                        is overloaded (the same override type trait is used for
                        all overloaded functions with the same name, see
                        @RefSect{advanced.function_overloads,
                        Function Overloads}).
                        (This is not a variadic macro parameter but it should
                        never contain commas because it is an identifier.)
    */
    #define BOOST_CONTRACT_NAMED_OVERRIDE(type_name, func_name)
#elif !defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS)
    #include <boost/contract/core/virtual.hpp>
    #include <boost/contract/detail/type_traits/mirror.hpp>
    #include <boost/contract/detail/tvariadic.hpp>
    #include <boost/contract/detail/none.hpp>
    #include <boost/contract/detail/name.hpp>

    /* PRIVATE */

    #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_(z, arity, arity_compl, \
            func_name) \
        template< \
            class BOOST_CONTRACT_DETAIL_NAME1(B), \
            class BOOST_CONTRACT_DETAIL_NAME1(C) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(z, arity, \
                    BOOST_CONTRACT_DETAIL_NAME1(Args)) \
        > \
        static void BOOST_CONTRACT_DETAIL_NAME1(call_base)( \
            boost::contract::virtual_* BOOST_CONTRACT_DETAIL_NAME1(v), \
            BOOST_CONTRACT_DETAIL_NAME1(C)* BOOST_CONTRACT_DETAIL_NAME1(obj) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z(z, arity, \
                BOOST_CONTRACT_DETAIL_NAME1(Args), \
                &, \
                BOOST_CONTRACT_DETAIL_NAME1(args) \
            ) \
            BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity_compl) \
            BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                    boost::contract::detail::none&) \
        ) { \
            BOOST_CONTRACT_DETAIL_NAME1(obj)-> \
            BOOST_CONTRACT_DETAIL_NAME1(B)::func_name( \
                BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, \
                        BOOST_CONTRACT_DETAIL_NAME1(args)) \
                BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                BOOST_CONTRACT_DETAIL_NAME1(v) \
            ); \
        }

    #if BOOST_CONTRACT_DETAIL_TVARIADIC
        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(func_name) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_(1, ~, ~, func_name)
    #else
        #include <boost/preprocessor/repetition/repeat.hpp>
        #include <boost/preprocessor/arithmetic/inc.hpp>
        #include <boost/preprocessor/arithmetic/sub.hpp>

        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(func_name) \
            BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS), \
                    BOOST_CONTRACT_OVERRIDE_CALL_BASE_ARITY_, func_name) \
        
        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_ARITY_(z, arity, func_name) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_(z, arity, \
                    BOOST_PP_SUB(BOOST_CONTRACT_MAX_ARGS, arity), func_name)
    #endif

    /* PUBLIC */

    #define BOOST_CONTRACT_NAMED_OVERRIDE(type_name, func_name) \
        struct type_name { \
            BOOST_CONTRACT_DETAIL_MIRROR_HAS_MEMBER_FUNCTION( \
                BOOST_CONTRACT_DETAIL_NAME1(has_member_function), \
                func_name \
            ) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(func_name) \
        };
#else
    #define BOOST_CONTRACT_NAMED_OVERRIDE(type_name, func_name) \
            struct type_name {}; /* empty (not used), just to compile */
#endif
    
/* PUBLIC */

/**
Declare an override type trait named <c>override_<i>func_name</i></c>.

Declare the override type trait named <c>override_<i>func_name</i></c> to pass
as an explicit template parameter to @RefFunc{boost::contract::public_function}
for public function overrides.
Use @RefMacro{BOOST_CONTRACT_NAMED_OVERRIDE} to generate an override type trait
with a name different than <c>override_<i>func_name</i></c> (usually not
needed).

@see    @RefSect{tutorial.public_function_overrides__subcontracting_,
        Public Function Overrides}

@param func_name    Function name of the public function override.
                    This macro is called just once even if the function name is
                    overloaded (the same override type trait is used for all
                    overloaded functions with the same name, see
                    @RefSect{advanced.function_overloads, Function Overloads}).
                    (This is not a variadic macro parameter but it should never
                    contain any comma because it is an identifier.)
*/
#define BOOST_CONTRACT_OVERRIDE(func_name) \
    BOOST_CONTRACT_NAMED_OVERRIDE(BOOST_PP_CAT(override_, func_name), func_name)
    
#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Declare multiple override type traits at once naming them
    <c>override_...</c> (for convenience).

    This variadic macro is provided for convenience as
    <c>BOOST_CONTRACT_OVERRIDES(f_1, f_2, ..., f_n)</c> expands to code
    equivalent to:

    @code
    BOOST_CONTRACT_OVERRIDE(f_1)
    BOOST_CONTRACT_OVERRIDE(f_2)
    ...
    BOOST_CONTRACT_OVERRIDE(f_n)
    @endcode

    On compilers that do not support variadic macros,
    the override type traits can be equivalently programmed one-by-one calling
    @RefMacro{BOOST_CONTRACT_OVERRIDE} for each function name as shown above.
    
    @see    @RefSect{tutorial.public_function_overrides__subcontracting_,
            Public Function Overrides}
    
    @param ...  A comma separated list of one or more function names of public
                function overrides.
                (Each function name should never contain commas because it is an
                identifier.)
    */
    #define BOOST_CONTRACT_OVERRIDES(...)
#elif BOOST_PP_VARIADICS
    #include <boost/preprocessor/seq/for_each.hpp>
    #include <boost/preprocessor/variadic/to_seq.hpp>
    
    /* PRIVATE */

    #define BOOST_CONTRACT_OVERRIDES_SEQ_(r, unused, func_name) \
        BOOST_CONTRACT_OVERRIDE(func_name)
    
    /* PUBLIC */

    #define BOOST_CONTRACT_OVERRIDES(...) \
        BOOST_PP_SEQ_FOR_EACH(BOOST_CONTRACT_OVERRIDES_SEQ_, ~, \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#else
    #define BOOST_CONTRACT_OVERRIDES \
BOOST_CONTRACT_ERROR_macro_OVERRIDES_requires_variadic_macros_otherwise_manually_repeat_OVERRIDE_macro
#endif

#endif // #include guard


/* override.hpp
64JnkSfgnSbmCSemeCcWZMGrbxPQ6JPrleObupNT7RMr6xPLDOCuJORh5N/TtirXyAMP3lNPWVMvhANcwN/wmeM3tpNsFlCAbVizbVj9PMEQQeDuNoJ+HBDzCgFDEaiqCGwC+B4QTp9lzcAjyXB9n2JuniLnmyVhnPr0zYeMDGvSu7Z+xk+kZVZIFpGpanYKMj7L+u7HVjXOzjcHhJpjjJ7j05tjmZirJ5sXiJ4VqpoTQZkXq5qXeEfn2sCUiZ6XY1xQeJ8V95lTPZ/TRlmQslvQi16QJ1pU6piTnVgQjV60yF6wmli04Vu0Q1lyQFl0kltytlvUOV/0YFzCNWej3VjavFny6wjI6fcPtOAI6+AIbQh8kuDgh0a6fJbiu/U1k4BKvPPNhPEj4vTL4gsS70uVNBr/WQou6NAullv94FhFcFqtyF4tOV8tY2yvYVyrY5RusFtrqloF9ay2oaxVya11Ra/1VK2tnK11oKwPMa6PyK1P2K4PRK9PVa3PTKwvnq1P8EXMqjVxhDElUoJLIPHIFaRB8XrNopZ0nE+YJEpS0hU2eyjBUbr5qYAFmeVN+zQ8+rjwp8e07zsNd9FqNStpIlFK7koybxtbZgut2K7OCbafgiXD4Do1lDkpIFeCCycrnixhMDPbaB9qkVQhMXTJ+vk785TgIcciAlSDxCE5El9scl8woz54QlHB8iiLml//rPGvQcAO8PpvVx5iLHn9N199jpxSUlRarPxdCHgXyCL3o/67F+6e5zdFzmrsLzlk6ND78VT7ojH7+3x7XMp7uvwN+vZQhsQHuSX7BvYHDKEH0poH1pvGqn9p0yI2HOQd+tYwH6uyXCedXAIABzuzXvp27+JFfHhHbSGuR5DANK5HvxB9exJ0XJvKregYExcn5K7+o0TfI0npI9H0Y4vqVv3WI5eL47aHowz046Jq22Tf48KcE8q247mDg+ocwzDiE3/+02rzE4GAkxamA7Wek/rN08dvR3VMZ87qp+dcBM32Z7Ilp+ppxQmTZ9C/TyALJ7Ooxv36R0vVRsPV/xpkzhkPztpRL7BfCbvlL6CRTldjLhpRT0aYTnomLw6oLqaZLmnEz4mNzh8mDVY2j18nLy8uztM+LjHFL2Ulr+6CL6Fjr0rLLz4mr24Xzkc7r8BTBnBbgdg1+og1l3g116hdSUQ111AC14QkN6eu1zP2Nyt2FwvEl3QOOu+oN18gW3oYaJdf/Qxo/G4Rpm6eL264FXRJLm8FunKwzU+xBO52km8lv9x0bd7IkOizfLlTiC2mcLhV+aIv7XfPNnUrUXPfh32vn6v3DXJutKWrZfBAv3XHF/swDvtgu/WgpvDg8EXXQuDRYOqeyuFRFv/O0+9RDHLxfeuxSe0xEO3W/ct9sJ++d+5TCOQRmPsYhaYdRPIsOoV+KP8saEA0EPNc9e1Bb+o599tznsK9NeS5MHdf85Pyd+TlUgctisWXRjGc2qC4CrTXar+qVEGoR8ah6iu0SsPXIirsVr+tDjSMAbQ384xXG0FAV+xbcTI+B7vfpEMJEP19SOC9jIRgOuI9DrKfsjb1vrHlChMHk4fy4V1MuQ6Gac0NWnL42ICg9UHKLtA0G4AQrNq321zdpXTICxoY8kEG1pzeFvo/sziRwRmNfM+T/v9gXcMpTAgflP9LcshqKq8ItNy9f3KsVvk/LE7FQjBwHaJGwbAVhgvVZmv/tjjlf9BXBAhqt3rcX/yDdW2V1Pan6In4Exj2/zc5JFQHDOX/r8XJVdy3fOXWYjpfLBb1ReFsL1uIK9Z8Y/XeZhlz4NfFeKIbxPYfrOtjHSNFlQBydYDMfblwjQKicNafWHt2Pprpi0HpZZRcaehzguPzXe/uTSkhYU/V33zzuCOGz+ywaTN71NjC+wAL8JA9v8bNXR5ukfwx/ENDc1Y7v3kq3xl4pjJBBfvzSejbCyEGvTCErvGqdxyLAfQtna0ophgHlY2xHZ0EeRSAtcXiJOSsWxZC5GxuYyWGwdJ4LU6IuRslkomD3OsPTXRXRwXaFpH/Bv2EXtbmo657TQT9YJUf7KMbRinB0DA/S49XxRMlkWaKfNJDEjNSyvNJHPmvdMAbAjDg+/ZrqDholNaSxO1PxaAUzDIXqJPgN5aLonB8AYpssvcbpDRYIDZSaThQXwjY6aH6dWgKhkxzti1FGCssV9IXoNwvLPPtfj7tDzKw5Re3tbzIqyxFIpW4PsswrEAbUmMxW7Q3LPQCed19LkG/cC2PmyZQmRRa8A2eX3xI2FXbumIgrCflxFqhcC2E8GY28GaFNIyNIrqGKjDKW2KC1BfhMRflxrs4mOTA4yFXutCHKgxlFR2E4IE3MKUdiMSOm99Xu8ZeyEIh5LROOi7EgpFCye5vjEwul4juG/NKneAW6ILALydAeJ8c0/Yzb85i1xlKK9bhySh3F7f4yjDL+TdOShAs21kh2OYDt1PSkVRb06CD3lJZ/ifNTYs3TMEVPIw3IySV28Ng5BCOQgM18EDjId3ZNnuMXWdswQ3ZCvqTrqYGKUjbn7S35TDlDI72kKU7K4gwJZYf5slo6CJzSLyRFPqXRzE++xDrDGcsPL/X99FHZyntEVM63ZNwdj9LZ4zjyCvRfHqO97t3Qzyl2hPr1woqGkzkiFOPEfF3t3WP2+jiL9gmUnPOQ5TffvyNjGX85Zdgic2SQq50k2s+wH3b0hzd/OE5Xem8z434D/RX0puYRf4SyPnZSkqt39fngXa3488pfplhsAxI01p2jcdzKDjJgbPdBwDH/GUsYIvqL6k/gmI38NEGYW97B32GFgYLWGQIu1XwB90JGieVBgC0qIV0F5WVQNM1GCLI4eJralKBWhyl4OnzugvDyqnucDcR7NxFhgBhDERZ3fAinBRFtCihIpTkhsrD1X4t4JAQxNExSU1RGnEWJlxvEng+UC8unBjh1U4mVsfTQA2hU6i2JClOJAaDYIBStE0/InbDgAgJvpmQPO8kZNldgvdENMqBchdjCjeplGiIxIPSlMzjr3iKZl2oeVBEXEZpy25tn3NIkSmVQv2QKE5ebBRDXJwvuH+AaiihkNJMyuVpkP7DVCh8TuVe+lla0x4mcWnGFI9KuVDqu8y3Rh5UvnVsGUO4BnL7xhjy3ZaE2b0EclbbETgmAAkugkrGnMswA1fLSBikDA54UyY+Un1PJohPq5hVaM41ES6pXfKdV4gF3pvVjRHUQSu/sRNKP+GhYK3dkOJrC8Jvc46KRKbFkNUhxAgpkPX+7JJ0xPaZOhlavtBVArveaCmc1CMLidDEGnGfhvk+XM6UvYZHiQCNcwWv8cJlO5XIzIpZq1nEtXpOKKBdWyAUBgr/ZEQ/K9JQxsdayoc8LhdZCWVPf0fuPQ3L7YR5lv9MajJXfCHOeNZQROQkL+kcgZf/JSAy7z7mgFT1l4kehYymezZnnBIYVQ31OOar/PB6Ul6NIbwQJ4V6/UFTZeCKISzrNEBoeapEiKxMz6yZVDwKzA9HYyB09Utj2HcGwrFcBwiAG8MoFLeRFGCG/xI7h4rMhvMrnoqRbMQY5/dgE1WeaHfgcP/oxTS00OwfGys7r6G5HDHhXx4HOj5Y4ZVEQ7CYwSdBgw/La5+bg1rlzo20/vb7XYlgC3HBqew0xCazw7SO7jPBpnutkOAVNcmf2v2Yv568KElN2No4saYIrokkLoUGLVd7nusIjf3+Fl9GZS0zHgDzE7ccWmP1yAclSgSFeJCbgjXaUB09yFjRH4jf/RddjWct0GWuqThetxL1zWgXNgAbSAaA/TAyRgL7Y7XUCj4yCEao4fbXZz2LefiYxSF17xrH3uAUCb6Z/LUDA8KuhPEizoIVdHeQqCAPwlDtpAGwOCI9SPkZULqAWJwyipYjTMlv3AC0jh1SDBDnYAshkilbJhMscLqffN0W7iuNIAYVXAAOTBxs4zYUjssRtd0XakJnznESorAvL9uFMUwlXD/8zB0L8UzjxsRW+2I+57mbShDJllbNIi+ylXChHMsJvMwm/W4spdKzVvbznC+9aCy0qvjcqW0RzFfiWhUaZB2y/ZekNk8QpxEARKQUIUUgdQP+jguH688HUG4HYNX2HG50YvnWoyJytItGoJACgOqbEqMxFGg1K9pKK7Zh1bDGF8F5BBuISj9akeovghp5li7dHltP39HcKUQ3j0se28/PHby3eLbgVzggba8Tl34UvNsAkhYhROLLnwS8OxgGLb0EvleR1Ly72FMtzax6M7Peq7vkXd9Ght6P4gvb9+gEPH5q6+cmt3kLkSi0jm8dZp5v8NLQYrFMae045zlcHgqj/QkbmMDo/ChEhih2CyRAIRCDvbAGJ4Mw2rfDMboBGKHdImB1oXNilbVVwy2uGWfiqcIl/KVG+WktC77bupaNczKO6PUhvceU8Q5xh0OejefqRwHI+0VgKM/mBLd726ecq2YW763HHPfBL5uXcbnem+gOHgMqH9dpse0H0JceB/6d51k1bztfFV4mMvlvSEujnzwrPy864+oQ/+A7t/A7Xd39eIgY5bv8ARG43YTeojI8TD9LX8Eo1+0Fjmn43jJuex9+9Xueyu28KfbzOZHp8i0CPzpov/3lEySHRxiGfm7+1zrLgQyeFwTHQHytXP8adij0hAJV4AA5+UICWW7mvy/M9QGcdZ1jNi1nNikn8qKJdEPPt8OKdsCp8gFVu6eduxGCumFMuxFd2uHnu5Hn21DuulFtO2YautGweloK/4G7sGB6sNl6Bk16MCl7wHu1OEU9uKo9BEFCC9twypKdhyoscbtCJO1BxGy0ZP0C5JSwFGdClAy9Edy9B869RKa9NKq91EW9h4m91n29lLq9ZPO9Kf69DI29tG/CrHcJiywi9El1xN78EKp//uMCuJJyuZJEeCpFeCsB3PMiPOsiAu0iVJpQsIH8EHpRxGG4LwB2JEVojKdQDPd+8HAQAo2/AiiAkQZKl9R/nyJYmFL0qK/roq6Pk1CMk0FMmVdMRVZMVVeM09YfGwyDAN2L9wpPXJl7oMKivA2HU8+mXDtAciakF5WsLyqsiyyufzdwPjagFxVl1C5mqCseYDlooCpuJDpoHDToFzdoyiZu3jhoUSlu/DZogixhTShhwTBkTylhHyXuICrhpiphOz9oAzPkrDtkayvhlSThJDvkGSXhfSfhXjRkNT7khzVsBzPsyzZszAuST2IOLQKQi4aFeEsijImF2LJAIooAkWxh4UXD0QxhMd7DsVHiUXfDb6ODCVgjichSoYRSSeOS0bojSbZS6UFSkbLMSQyRoZTC6QyReJI/kSV/AhXZ82FG2cJ+FoiOAjlHi2xHi1WlS7ylS2WhObOgQhulEfpGo2SheDABUGE/EXAD/QD+jTfSjDQ/ZcNE04oAVbYyaVkBiJqjeUGjxZVjBY0ybUVjbesy7QzSnHeSAXFNqUWSOUVicVkjEVmsCY1SA4SyiWzjA+PDmbyyg0GyQ6pSY6Yj/eOy/VFSk5WyY7OyU8gTk1njw96yszByo0njg1hyc+2yGW+yi0ly87oTq7xy47ITK/MTa0ETE3sT640TkO1+uYyk+hr6sEHTMFqCP8Ga8kgyoMN5VLyvsgeqYUe28ife8kEj8sei8hf9k31l8kdv8ng/g3N5pvxw67oJp+6z6vdUwwNUstVAI2DSAIyn4B+kAWDcQA4QFPVRkFJYoIg/rCYYrsZmCqaHJ4BzMpEwNy6tnsRQETlj8mA7ZHf9WwVuHWLHNMXs9M9aReCxoi60UgB4BgVlBplICVVuBpNRCed9GltOAVtMCc9OCblKCbdYCS25DndDae9sBs9ViXBfiQhlluB+phtGmeDbDCG2MmWxGJXdLMU35c9UytTFs5+aZmn1Zhnu5d/oZsB6U8cuCn2UKl8ZVdj4RkK7SSG6knBAVwHN7p8i7jC6eQCFsmCobBXgRpMf5yToRWUnDdNmTMy+FlGQb34Xn0Cjln3HUFWUb143a/xrx4ye11TQNt6YLkhWTSVoed66fl4eduHn1XwIqVoIs5octtpPQbVgwwUZtYVAxwXFiXn1YDXm4gWNgQWt/XmlpgXphQV92EW1ezUtFHV9InWjaLWBqCnkBfnAY0X0Jnlttua3gkWfNvWoyBap83m9zGk/QDAwuJYUHIKjA0TiVFTknIZVm8PylB/jHjE5R2BVk2cr1tDJ1riSXWSzA3knL3pVLXlHL/k0aficL12/aQQxavrfawTLaQZ8Wz530fTVW/5ppwmJ/Fa7UquoTBOCcwvzih5isK8SEFfveT9vt6EuJrMC/tqOQx8MK8wRp6aVPlG4YpiPUgBIjUbWe+VeMJpPf9eizYiuMWH5KNAcLfuSJ6fdUVaAwLOEzPW1OHp10HAVu1Y4bAFd0RKufEN7cJtIN6+ym0G9U1C7mnGt2ZCprmW1mAjQYKezpYRS+67Yqhld6RoGZajTPKHTHJffco5U170WDNDtIFrvmMjLvCem6pcKWIgY+qPT67PeMEFaFyYihFU50BFBOq0dNq07fL7ewZjH1kI+8E1bRGo+1HF97l53wQcRqF073UT1xRVx7+966LR2O9XawsQG8UjK0nve2AYSpB12/WxW769aMe5b6JJa3tY5Qo8daNUu7EBu+m+2PtdfvRlYpPnksKNi/YtvSQ3C+vm/KrsMdfxP9G/N8kRP9K47Is4GQOt8Bk9ySVeSm/ffEH9v6Ldhg6rMgmCusx6jDQCoCPWKW/vBeXXpebHdW1ws1QB7wwIalBdGwxD02MN30ORRAcTVEEU8HKpTP0nRMMa9lMnY8HjDEPNzzDOKAUIOCMYcBEZdRwxpxMzZEZA2QCsxIkxBBanvEF4YHR1ti2kbkRAbjy/vsGIYk8v/HQIYb6kZU9ujUKhvUuf8nTb8+1JszNAZRdP5l+HCeKjWmOXemMVXJ9V9owlxl0XeBNK5rXMvp/PNd7cjjgyRxh9ZMfBFyIRzcrdlm3/0LzLloomgfUSOEgwwrVGQf6+mhQ8GAOYVN5XYRMRrxcB435Wo3jtf5hqJU5DZNF00K4nV0pBH3X8dIdXdFiWgCTnGMlPzNSxay2m5X1CL2Ud1Mhn11NDqNPOggkWgRxYYNDPY1JPxSjQgPpjHRQ9MMzWWN0cd3AuYNjXzPUhY7lC4UJEOMbf5TKfMbqYas2FzYR5iZXYxwzh7b/69k0pbnFGHycK1E0S8vi98cOAaY5GJaM6TYOEFh2YSoqzZefhdHQVZe49/3yLAviIi4wCJyDLoIkH5t7+KvFnQgUUWkgV49RAS+vtgBymuQfIwgvjI7SFdf/PIC+ebEZxVXEq8ibliQoqF3+Sev7xV8oMpO5dlqrpF8KJ5aI6VQ8yRxqJG1ueDyGoz9wsrhwtLfVTrfF/z+OrDwt9H3uIHxb8tzeGOcL1ObFIO0qrNf7ntZZgf2dnvVT6YZTNpR3xYy39YubBb13+YFfha1MjbaMlbN3+2SFy0yImxkdE/Nre3aoOzSYPb74A7tT04yfywUUO1cSK26YUzbZi0bJQ/U9Q/jXU7641Jjk85M8qxKf19Vh9jbbF4pvjbuuvhrB71LMTedmbRpC/n6A+/3Tf9s5cB68Uc42H282Vfk5bqc7VB26TBc5FBG0j5gV3VhY01nL3o
*/