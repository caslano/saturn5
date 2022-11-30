/*

@Copyright Barrett Adair 2015-2018
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_RVALUE_REFERENCE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_RVALUE_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_rvalue_reference_hpp
/*`
[section:ref_add_member_rvalue_reference add_member_rvalue_reference]
[heading Header]
``#include <boost/callable_traits/add_member_rvalue_reference.hpp>``
[heading Definition]
*/
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

template<typename T>
struct add_member_rvalue_reference_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Reference member qualifiers are not supported by this configuration.");
};

#else
//->
template<typename T>
using add_member_rvalue_reference_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_rvalue_reference,

        detail::fail_when_same<typename detail::traits<T>::add_member_rvalue_reference,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_rvalue_reference,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_rvalue_reference,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_rvalue_reference_impl {};

    template<typename T>
    struct add_member_rvalue_reference_impl <T, typename std::is_same<
        add_member_rvalue_reference_t<T>, detail::dummy>::type>
    {
        using type = add_member_rvalue_reference_t<T>;
    };
}
//->


template<typename T>
struct add_member_rvalue_reference
  : detail::add_member_rvalue_reference_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member rvalue reference qualifier (`&&`) to `T`, if not already present.
* If an lvalue reference qualifier is present, the lvalue reference qualifier remains (in accordance with reference collapsing rules).

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_rvalue_reference_t<T>`]]
    [[`int()`]                          [`int() &&`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() &&`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const &&`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() && transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_rvalue_reference.cpp]
[add_member_rvalue_reference]
[endsect][/section:ref_add_member_rvalue_reference]
*/
//]

#endif

/* add_member_rvalue_reference.hpp
VdHgDSEd792Z99EQQd89Zv9vXBEE/mfi2k83spWtPFC41o329X8/4rpdZDnLMIU+2FeU8JWJCf7gS3oy0fmyN2JoStm7hxkfKggEXf9DdarWa3EnFY3fL9bgZrdbQBrKMtQo+OYGnynmAUSy9ajRDj0dpmeV6pmSFf1cnI/LQdvMFpBALJxBQkMc1wJOCcR+yIafuNuZrR3lsEYhkcW2RDC07YFKSaVSgBE9kwjD7UfsBbACU3wYp4mFCASxGfgeF45pSKOjs5T+TwsQehvkXBC/JaVfwKOr7+tLBjEXve8RdyPSVS/zkJ83ol4NEdhUJmL/2DgLCqh3tNrg/4nn+HPcaCpDdtLpjUxQRneGOad+flzPK7y+l7a9YMwmRJkTqqDFQ2qfva2Pe8piBKRNQyK3qJrsLVvaPJ+GJ4cKoBLmYgwQc1D3VSwqXXjwWinehFmaEal+Kzj38Ertky9DwXwbPHCvHEQwUlkbAcVA/u/EYJHLF6lX5bDY7ed43e/0cRKVuMIsciUQ/OeyhuIVSW43W2u3Q4nS/kWJNmIcXCOZlFUlus7pB9XPgYY/RD/jCE7Pi6BFZBb+3Z6ChAvfQOuPuQaz0PntevFdmZMd8HwRy9hbTzba+OQH9AfbF5YYskeqa6SHneeHsM29mgk5LhMhCeEotBrABTenWibcn2ZTDBd1U5x/gMCq/ZMMK5K4/MC46y9uk69tAxqoAEOrO6gX1jQLfZ+IgqT3UClIZsUmIzwhU9T8ClDu1PDmgHXtA8WzaBAp7XIJ/D2mqF6K3TpaYNPBajkezOXzomxIfoew6KiAEJT0B+3PXmZE6XS9tnSL+DBAD7tXdn7P2qnqxoSZDHTbn4jAxwZvbtp42Zbdm6aal9PqFte3SU5WmB0bSPKzHjJMrj+OaAYSZI3Y1W86LZLdgyVlpeg9zFFm/oW0EPHNMWeqEeNMvBNonMFO5yKavCYt8a9jIRa8H4GLQEObzK7kLycJ3cQ6Uhl9agOH3zpOOjHLXZgPwlMACjOjponT0G5NUTsk6jvlmayef0dZOz/txMqbiLtdXxap1tUcw/SIIVXXkUYFxshjlZKO00glTiIv+j/r4wI1r6GkXioAERF1JmEdEhT7QVSeThvJ7uHcHLMcx6QC/9/CLteBgcL+tU4X3rhNmpFgIEYevR3RGffmOWavY/ZSC9M7Q8RVwmHzsRYXqxIYAlwTBnM+P8/1RwevjE8xwbKGo8vdVPkuLoJbuUR4VvTTf9DI6JFg5wVIQDs+i/jd+kf+jWhX+blO06fFvINwK94XpyMmdFDID9XvBRBNg/urQxpf+bqWZZu0pq/bG/JNIuXbetpm0bdiciOv2/Lel7icnv+yA27R7B5WdG3fdXiEhG0ABdaH72W2Ex8hGLr/EKS4uMpsH5n9h6IhrxQEKbYsUuVaaeU7xi1Uh8uzTR3moZ2D6m1mD1+g8YOe20axXxTcavyGKQq2pBNJdJh3uwxOXUl7zxUxr+NP2OJoBCGRqY2yuR/eCurS2ev+EvhET/0smZVgOWfO62cvecK42ZHCjTVaa4rTWP2Qr3LiFnTGI0jEmEpKskzN2/lGTbU9BWX+9ZNASOM4woCfJ91QjKN6bIRGlNfCGnXHW4poH9T6/wCisxV6y38AgENLrV0Dc6ZNsI1t27bNzca27Y1t28nGtm3btp03to273626/+D+gOeZqanu0+dMnenebirTjTp8m5dFHwL2A+Glw6ixBA1LXQHZr16kJXMWHtiunGDdxRmz67BekDVIg1uUWzdzQEpp8BIVrEhCHnq49/UxqhwPxud1bcKef5SJSajR9HhuXwgYoGkQrsGt3T3bqqPeM/Q7JA3gdBl1RTkVeFjqk5cwZg5XpmOgkkbacZ/NBhaSqeveeL7ixCdr/HmjSfdYLlXRyCTqoqfp29Lc/1zTpq0z9KLyfCoQlipVCnaFi5WzIHhhITz/QzeR6vsz2nHb4NhOUfAsmQAB/Gsb6Bu9UDFKUY0fUjHSvu6ypMrhbIXnLA417C4brAdf9dZ/4LcvCnn549Lx4u0CCpYMIIaAII6U1Vzq7G+hsIDLhrxbxxaOQov1+sJ5WO2zkySzJ1BwQvoa5ZjLmNw1sojL/C7b4CDMr95IzhyqiHJlVSYu2zoUmwv3byP2m87yQkgceiJTuOY/xD9C/RP3SHgdCB63AhEHFDQnC0sqamFEsrEY6q9VrSXcN6jqk39xfemukpcXwiMJjRARt0GmFZM76bauFpxQk2Djas9AMqOs5cYtlB74Bp3RFvq2qUvITzOEKpGjbfaSIK+Y8K1iTQW/ydXT+1XGJpKMXVjESJnGaDPCrj8Tk4SMuEyPMHgiT6GaTxCgmLeStL7sH54XrdBiLsAVbrtHZHHOERaY5bn6IHnlTsUKOOxr3z+jAp+bXF1kJ6rGGXm9J5x9fPgJL9Y87oYxa1cair4egaAGJZeIW2Jt6Va0F8WROR/QeAXQtGKyk1zRtHAJns7WeqQ7nq9ezmcmnhXdbIfegyzfRMTKdWGv2r+I4EWICuuYpfOjHGCb958FweDliKWoOQ8OL8xcVSji2Sh7nggPi3oFyAC7XulsgGrfJ5opaKgmyi3ZNfA/wrCobDY9xyrUuk78g1zT4TcBIH3++HE+IO4O5TwP1pp3YZ2mO6O1KwlBR0x7CzMdaeny3WvPSyoQ8SvmuSlrk4yS1J/tNcoLO3GQKNMwgo8PDU9XPUGhhIJQpeThVvsCpw3Doio13M4xkyy/3DAwJZcFsypdZlTUK1MDwFhJ8fn3ruu7Yf9W/AIeQDI7AD2Q2+C029kyC7bUMmMbhFGJyca3hgciKQOajxWz8Ynm1EhS9mFp90LfnBYPwR8ZOGLekXh/NNSwUwkniOPXp/48t3sPcQZ0RmYpN5o7C/9SeqOCIU2GJrdMZxhZtI76/qJ1hNHTaz3V5pRYXrdLjZ03LkKeMriZnRdlt1DYK8cVqlFkvwJLqt0v3RsIo5pU69Y08z2GdVzwiRuv3/2JUAFgNB9JGpZs06sLPBnqWEkv1CWksF18v1AqQXBTCeNdGzDn0JhyYm7teAplqm9CAvsm5fmkCX191vXZImNfryc3CrcdF0Wsl1DhHE5sApFwrSGrG0RqBm8uq/muOpsmN1jhf5XIZsIR+TXgLUzXQZawIUAn7BONWK5EQSLgaQTiV1toampGbCKZ6KXR5HBJVsy4RzVte8WpGJYPclvh5mDWCnyhUVeVw0gvVOqfpFztIRR48MGllUPHpNu79xnwMZJ4BZBsTdIw9mmCC8B676Xojwe/+AqB96WZw9sOFLM5vRp6l7gsJlAWSfcebDCznGW5lVG0p8BfHPUVIkpfYEQHK+B7uUqjmRb88T0TLU/jloahpQlB5F3e84BYaYUrHShMJaA13gkHZZKBL5PYdJdPtF3EqEF+eGUmYIK2bEDNt/V9lzwTSrf6ioUIfWHKmNU3uWyNmIWEVc8jktmcsooiquH4m8sA5XbQIEAXvgADRcK96khHeB4HBSYBeSDnfVO8gSDzt0aDsSVss//Bg3ILLUI4J9fjpXP3y8ATxykMZAjrCMkHZCjO+yhZXSuW/3mNmUFIIhweteTPz5lPw8msmzQ4zZBiEdBLiRaBt45YtpOYxqPeV4F2yxt8QNkKVx6++8B1MhjGkzlW4f0EtBjSqWNe8feJYMJGa06Qm5vsAlNl6fC0CmFoWPnjK0XZ1Crb4rxes339ORNP91tCTUCgg67BnM0RU6KvjyIEgg7w6MNndsML7qokuIIiTAzmgmfVcEDWrLVadLqXZjm+XLAVKhJUznCUncMyoqAMxpyRTm6NfBhyEpiv9xiZOOKhpD0aPb8Yjf1zgmS9T3UMt6dC7+f9JH38GZjz6XXyvNFJhmK5QQDWzqIXKyuQom1WfFnBPEuJZeBexhGV8909oAnFXTd7Blc71wOYMR1AmulBUxTnCEYMKCtfur00KeCICPXqt9V59hzGEqXJk+bdND1JFWB0kKm3rhDNb2gwr4gLMWf50lkm4l+kGGObtjVsz7DVWr0+tnyWOZo8trORxDmMCARlDfcR/ALOiV8Lji0W4uQ1eL2EFGG91doEN7RGbIkqxdqt8tXiWZ5FdLrCOG5tbmY8oV26tHfxDGnWoF/xTD83s7FkkUb9jFJOwRZbN1NLVxHzZxJBeYiwDv4iZmLocTqZMZhcPXYc2WJyuvwQ9B8ubdVYlQo4m37WUmAhE8ff7JQ/+GwKpDbNGtWoRebrhGCdMq8Sz+0mOA/acKRXiqh7Vb4weWmtWbXEcGVVIaJyL9H46aFCdS8pzmabLsrOIK2LGThOHXcG4OCvFm07609YBQ430QUFBF3EHTfHSQJkBVNhmGrgvAHXyaOYuasTJLmrIzXOO0E3GwK2OrRld2sDp3ausMqCgdOgEKWqO0sTnRuo6fzaYoY0hBRex+Z7dfPGH89XNmW0vO8fDO2Hf+mnSBInoJAomOLjmeJdIVm9z4pTudjOmEzBmRbTrjKWudbp+O4lCMnWlMXBtXN1GXXdUeYAENwLnbH75EgVbBWOitiEPH+YjJAQMZqNIyGloc8VYgcTpNhcJwltk0F/3CphwOWUl4vi0+6D+3Xe0imazkqAA77NZs20PKOMbVenak3G12y/JOIKIXhhA4tsFicbPn58xF6XfMCDm4f8WsS4CQe0TRsCB0vtQK5HZbFlG4YWlzKgrQXgA0UWAamQRXjcUH+ff7dGf8wldzA4mc5cUqQmqW/AUzH2vJK4jro8tsk+TN4nohPJjE55C23B5HWFe9Fma9RdwOLDJagB0Sp0cCNvxuNjYbmACQ/f2opbdtwYVvfewyRfT19udKtvCvkh9a4qiij2w1jQs4Ee98M01tP25dH4H/a99BCHEfhQYUlS4aGJGTekFy2oH8E0rqeHrTemp/vPrzZo8KxMoj3Y98/XO3Vetr3TUFvZiYoHlqO/Ds2vGpP70tPzL8kJFh6vYR+PiBYtzQ/JGzucypSehCGTeYr9fgvItoqDqmmOG3H41dHVbgsKbprsmpXltvdsC4f/3RHF0EEFuEaP+pWMTgSBgAIhHIvzQvww5DTLv2qC3RnCbCjFWale8/evcWyyKxsY7eiTBG1N1G/qxwlNR87O2Ot7+VnkmKmFV5lfpnBqKAL4uxJxpS6/NLBxsonKh0b6K3O/ivC6rl76JYy6qcBX0RbhmyYg4GBxT/m2W4ht5PbXqNegNu4P/hVW0lRJyy/gcgaqoQE8Xv899LdTXcCL9G9fLPkkdmcrthvxwey2pve7pEpbHHhjzye4A2YBgOPjnI0uF5engi+XTa790WgRUODNynhzZ4OkB7lEjt/3G8UE0+UL6+aOipq/hpHZb/+kpKRPMDOji5XqK+/xWlOpRIcpZ1iz5/FV751Ms3zHFdSl3TvMJQHq4BT9jvXtOao7NW84Pexj1oUTU8QSlvpQ01hxivvb+IdzGpnWtrMuQl52L99bXXQskCHdVAvvpdnzA46B3ajtCblE0+Mywwv4wCAh7se9P+tvd4iSHg/E/oMr+GWcWBUNsCmeyuT3K3bk8Lcetgl00QlTORizhSI40cYJp49Xf9Y2BlOxD+Xsmwx9VZvsE6JHAqq0GVdtGyxYpOxvq8k3W2wu/OFu/L+x3+Yyz9GJyAZkyoDjxUweed/5Py4beSLbQgr8KHRdtmDKfTe52xwmyjFoo0VXcngsfdHC0ujMMfA3GxlbqZPnFUo+VClRy/L/Ag3OQTPmxNiTlUNI/DHg2P3sbbhyyk2xWCTOdlSw53qqw8dfkKgl/BKrgKGtjMG6BNIQPGeIJvJyQHo9b/6hQddVBBfnflWckgNOVn72EBTmJQffitt70Nicf621pvzxQWCW0+Kzq7Bmy3Kv87wyjXIKDFq1c0es1i75/khtjCWo6hwvGb9hneVbhPMC2WtD5HS7IqYWXLQvVPdnwmY1pvhNLORIyqrZ6+tDm7YpKviHFkyWVqOD+2jxp0J9wGM9llMROmkkzH6Q4zUFkntdefR51eObobDZQIuLcsrO3z84FyhUDrFqf+mQ6iAbBgA+BCQZEFh0kfBhuujF+DcU8nrRBVqvv+KXCSmMm5tMCHReCHxquh5FR7mOQZ3cUgfWboMmh8+hEvfjIm4xhCJ3NQkXV/V9H7C8etmynKASfKZreWsuBba8pQVO6EeKP4SloqZ3bTdXex29rmO21SpHtDO7hptKLRdxYVb6f3OVWylst9rqkw3j9wlxctk26QRDVvW8bJCiM2MC+LeNokfmtoDMZoVqO6Dg5KZy+LUFf9nsy5inl2YONzejiA+y7a/DPcvhxObn3NxV8/1JuM/ik16ttsoZADR/r0viOAWNITh1Q9ymZYPAochFnSTPd2ZP0KItBZ6I4ajt0k6nxaVOp1OCF4rRalCZ6ODOsQ0/qqipr9oa4hgi+dLNOi82NIALCMsyYY2h07V19JyE7Sb7rPppSiGsWEIqlpNWtB6fPvF03jHvlQvCK/vFUTZBfLpenW+zxo5K2RHX7gmhCZAL2zaKxPxS23A4+bMT50ssyl4IklO6movfGBBMEXB/O4gIqH8Y0fDweKutb/4QxwiI3F9XOZX09ASxsiD00Ynzxn33tk69M+kuqaioGNNV6Xh21lKueQ9m2/IJa7rZiiDogoqzO3gfnswsvh+GV6o3UfR0dvEiharqYSphymGe2m0Oas+CcHdgJ7JcbZknfFrk5hjPmzTxiERZaxeGbRZsF2vx3dtW6vh0T7+9ftmXJR6l5hpDNO5ih/iyHnqM3J/n3EmgBC2PZrDEsclgCIdGCgzybWLtMh7lKP+4qi1+Y3QD3JuVRg9IKIZGPuTgyI+3cwAMW15EDqDmKvqUv87qOvquh47YkfgEkqJHeay0Rh6upBjJED49lGpkIzrJIqBmo7uQg0kh2Tk9SrwvcaizeeBNodQPozYxrCmr+I3awBciE4IWK+1CSuFepqGJUpaCQbBtwr7hPYvdqrVbr+fOSnMFUgYM4YdHxopgKitMVtR/pDm6L35R04OJJNmBO+7VfJicP5YrcdE86cpB91ATzCaCETGFlqaNyXJfHE1wzKUosrLThZs7ZJWBwSAOKtB1ZyiB/NoaPnP3zL70/lONNpNDC9h5s8V2maChrqhY0VsXEt5pc0U1sGJaNUnxUT1kbo5BKAJ0nNn5Mykwdb2NNzvuxbVKfRgjXoQM/gEBjQM/LwTKEzY4TYJxSPwVAyQKywo8mGQOxeklpcOILzzAljG18RvQT6jI1hcHaD/LnUpM1fKQLcYlAq5Cx+IjsIAci8Kg/ytJ+F0GApT0S5WHa40iTvD7lfg9NSXF8XHPm988mVUoDRg9jFbn9mDgqZfZJLfZcBCC+/20sHIkBne0Uk7LfaQ5tEi/Aydm1HFU5zVu4bFTu/hvbuZIzW8w5Voene2c1xy3Eu/XYlheDcn85wkktrwbmdBGeM+IwQELtE8NTy1vym4SJIJv9HzDSOF6OPiJk2xeV+tk0N1XxPWP6VqJN1y5eJwuL8slydJzeqXnJWs4KyJAasDIJ33sJOo9jQw2fCi2oOwpPNGxPCs5XNQtxhaGRdcP40Ig6l1gipm/sAnaihYePRScgMRIeRJI
*/