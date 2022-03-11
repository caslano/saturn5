/*
 boost/numeric/odeint/stepper/detail/pid_step_adjuster_coefficients.hpp

 [begin_description]
 Coefficients for the PID stepsize controller.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_COEFFICIENTS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_COEFFICIENTS_HPP_INCLUDED

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

enum adjuster_type{
    BASIC,
    H0211,
    H211b,
    H211PI,
    H0312,
    H312b,
    H312PID,
    H0321,
    H321
};

template<int Type>
class pid_step_adjuster_coefficients;

template<>
class pid_step_adjuster_coefficients<BASIC> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0;
        (*this)[1] = 0.0;
        (*this)[2] = 0.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0211> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 2.0;
        (*this)[1] = 1.0 / 2.0;
        (*this)[2] = 0.0;
        (*this)[3] = 1.0 / 2.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H211b> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 5.0;
        (*this)[1] = 2.0 / 5.0;
        (*this)[2] = 0.0;
        (*this)[3] = 1.0 / 5.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H211PI> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 6.0;
        (*this)[1] = 2.0 / 6.0;
        (*this)[2] = 0.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0312> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 4.0;
        (*this)[1] = 2.0 / 2.0;
        (*this)[2] = 1.0 / 4.0;
        (*this)[3] = 3.0 / 4.0;
        (*this)[4] = 1.0 / 4.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H312b> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 6.0;
        (*this)[1] = 2.0 / 6.0;
        (*this)[2] = 1.0 / 6.0;
        (*this)[3] = 3.0 / 6.0;
        (*this)[4] = 1.0 / 6.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H312PID> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 18.0;
        (*this)[1] = 2.0 / 9.0;
        (*this)[2] = 1.0 / 18.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0321> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] =  5.0 / 4.0;
        (*this)[1] =  1.0 / 2.0;
        (*this)[2] = -3.0 / 4.0;
        (*this)[3] = -1.0 / 4.0;
        (*this)[4] = -3.0 / 4.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H321> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] =  1.0 / 3.0;
        (*this)[1] =  1.0 / 18.0;
        (*this)[2] = -5.0 / 18.0;
        (*this)[3] = -5.0 / 16.0;
        (*this)[4] = -1.0 / 6.0;
    }
};

} // detail
} // odeint
} // numeric
} // boost

#endif
/* pid_step_adjuster_coefficients.hpp
XPh6/jsHX3Z1tyUC++ayhAVtU8BKAh1z7LQn1GqC53kRE50wTB0qBE2835kHAKLYeyJ4wvboeSnbg1pMmtABTl3u4kRZ6wKA5lgywDK1Z2RVxFVpEeIaMk2vgBA/JvmJlMbRMwgWsFzWJd71zfZC0pONRn+Jnulx2DjHbtzycSyibWUYN/iLPoWX5AEUXMx/2O0BNIKjsufEcW3CIMu0+elhRqG964UOSnqnoNlsJGmVZfF38Yk39r+PlQIrOmEdTxW6utTCO8JaZsdBQ3PXLI0wG2FL+YL4VYkvoxcU9czhXjnZYzC3G2c6EUaKJsDIxzKHF4KKrAHgxbfAA+7VAull3cJxWdnRXNnDSSXe6Ks0fqYZbi1pJiNS3IC+Y5mh+2yMiHpllLS1mY0Ym6Is/Y76j4+YsxDmIWDRnO9AAryiZIme3R8sv+equZ4L2ra06ekzCtPEvQpjR8Pd0YNN8i4Bpmi5Vtd3xbxwZVlN54DhinSz9TipQUFfo8Tae6RiWEUzFduuKsb04PD1zz3ULNuNDPTDDI0Z+EbcelagJBQ/+p5HMBu9dYKJwhJGZ8OlTF+igCdRSNgVxPR8RLZRg+jVauTVRqAn3BT3x9XF9fcLRpUIbrh5hxhhlYeFKbvJ2hyWO/EE5IloFh6B5UxUnl/4zki7bKbNUwZQui6+Sjvw6eG3wmozLvKh093yyRw+aYWz+dbFQkjmzZrgt7Ofoxj0CTYwULpwdoBNz+jxJGwZc5VSbVHAwWeaX/fAV4utcG47gBA9vTyngSYd/Jp6mewHmcoRn6yiz51X7k7jWOtQf0SOwFNbDtL6HzhqJOPcudcArmkXY/RSk3hfvhR3yHrys07h3b0npCiPaxleFj09A8BELf7Ja4x1jBPKEQFfFcyu846ugF5JSomPMtvelQprHw8cATWLFvZiFZld17FY0XCGZIwPcSkebIlOP1pYopoP5nSxjaJJ6aXBH8nCtf8yOPuNKXxFC+LcIUjkfuBabdbBbwnd1XENUr1j+2YUdWTw+GyiHGbeR1IPeFfHPSt/tRJYuT9DSE+eE7z4Ig/Bd3SPIobRMm/dpAa3CsACRh453wxfQJAK6KEDpXYDmg/8d6wzqjF2pYvwxzWb9rHYt+bH7vslddbtlPY8bd6Bdx/9PoaMvfYoLOXACWJubCXnURsHGspYqycQUxZs7og3U/XImRdRG4uRtne/f/kUjFqSvmUWm6PwsREP5U2ws/C9RnpCPNcvT9ngumg9v5VI9fMhRnMQtkCIM6rd8tPmORUlx4QrM0hclTBa5F681sRruuLM1Xd503TZvKBzRrixJK56eyVJmlXB679eYOWFaz7dCzjxyZ+bOOlux+J32x8iLN/IOsF15j2zf4IWn4KIhbR6zlfRUcPmBNQlbgEMikgwDYtL6osQI1FFJMpIwAE6TFmiGmpjdwYq5wQWkeXQaDUlaA0JXW/C6+haZLkBLavJcW6aTumHJ3UIPz4vl6XaaoMMU4Rk2Iwp6W6WX05VPcT3qRYzqqdso2fy06M6spDyb3AI11gkZ+1egIJkiR0Vz9rWnjB5nV+Wwca40EXrSyO/LVJjiIPXObSUyLJz7rQhkEtwTomTV3aFCGmUTlQT9jRDDM1IbYZ1NgzIuf0n256WrDDbj98lEYhsTX3D1RuSrgU5TwS4oq7Zl+lY22qdg7GtgKBuhJpYiPMuQQyXS6HrE363uVI0KzJ4RGhDFunT5JIpU66fV/hBY5kD+753coPFvMc6gXO/0xVzIjn4SACReyqdZp42CJ3gqKAf6Lbsy8UNXG/LXxOqjeXf3u1D1B76DpFYJbBFNhn25N4d4JYz4Ea5bpdm0HRJ3Ywjo/RrUC4FhgwOv+DW0CPV6F3Q+lEVORDp0djuqkqeNnu7UO8C2ztTFS+QZuCPVDD0H+SV4j+9G7pUzdjuhutEdchVHpKwn10e5RIAZqbVahaU2P6aNRU2QTeu2kzRmiVHLePSuVaamKvAAKJ+pC3L19ngaU0owGrMwmY4841jvEWFDxou5rjtvjAyTw70m4uwyx53YgSGKBTLNFvkhIQ8IyJ27nSxOJq3jEQVvfns/H9wrOkDUW46/gzTwSo/nYIxjqh3AyAtRKEqNS+QsusrT3Pr3DGotS1MgcwEg+wydKxLzDxccm4a2IfLnSqVK13+2owXjezxD6BEPfg4dAA4cCq1whCTTjJyMwcFZ2uvgRxEWQiaO4RIx1dTXBC0e2Mejf55LNiRZ5KJ5Yh28eq2OYS2m7TTdWxklbmEn9MigHLcY+4mLR3H45rMmg+KYSjNgLEsoi73KrnC6mFeRi2NEwoRaxBcPzDugoTYUAFtV9z9tw1OeDAqSzC01WnfbDTSuTWmEJU5N+diKYsw8zHpZQ6R5N4CDVokMcYBFecTVZRUKr5Ahb0CuRZ0dGw61KtSHBwy6+qIVO+YNKUpbstRxUeFo9wT6sXq5mp3iBrW3b7OlJr1mDhDtQud8gPbbG5RnfcOtlNbIuVL/iOeJvBogVfsfZGOu1j/jMoUcXlCUlSU187ga/JFur+7xDmUkYE8A1pJxl6D+6xZjEcJ4T9XFDLgZT/NURx1hTXp/dNNMmGlB2Q6oBwVn5xNZGXudAB/p3Uqtd+dmMddejjWW4nXhm/XC9iTE2HcHbLZ3EhngdPdUbG6J/jXG/tt1HuwbVQQT8zVqSpeZNgnYzQmcGKEPRW5TsAOFxv8voeGn5gtJYdl3L6dTwx4pQcNG+aDodHDknQCNL3K1YB0wTFa0yKYF+u98a7SOpcmysiSINmjQChoaooj7ZFsYZQMRbB0fcKJ5+R5iQsNYy2uzAsmr4YQRYXt2cHpZLQc3hhL+19Vi/hCwTZAGkFQWvtyRygcUxkIYvlgjg2+PpUbr3MFPfwMIbSg3DTgoLQbsdOjveCAt1vNWmwcxdnOpWacpI1BMEYApZAxPmf6jSjGSkCEYEUZTtxMUKNKM/UIIeN11V4ZYWcHgZysqewAjYDBsQeFKMlt/lv5jf2aWJG8S/a+JqfQwqBkMNYx+tegzcb3WR409HRR4TIYU4FhA+i7WMnfKdL5UI1WiKLa3ChsoAZstKxnX+1D4KCmkZun3y5kC1recFAu8dp0vDSFLilOD88NBk/cK2AGMr9Se8Co46VRdv1QXxRf1BJr3sJaZr3kuJjsNv1CxXuN0eogQbPzH9Pxw1Q38IQNc+VyEaMm8MTqRXIfNXvS+LI07fAck7UJ5aXNcsSx3fPOKNXJOq5b1K4sQ/hw1OHpQT19If2FisbJ9Yg80QlSbZbD/lkqcx7PE2Xze79aRnkmbRqX5Lk8+ZaQKKKaMXll1J4apiEcCfjx6Bh54O75bzH8SZJDRRaKqORJvl6WNtqSmc0hLZrvZmrdUeOnNeUtsfshK0EwDEmIClSLqXjhuFV/Et+EDJp80LeVPDSf6bVSjlvQtsUEe2IRkq1ZBjBVhPYdWUANQ/zNIzOCasGGxTLdFuwH0q83S2QV5aAQYEqhSk4/08lrKpuKoR4FY/06DD6Sk0Od0h52XmLmMhfPPhLsuJM+oSmwTZ8rfOsZ9Rv0+3UFBNxQkYi0JaOwkeTAZyZ7WHfBuMh/kT3UfMqSB1c/jyOknqLQyNRSZGUk2cX1fc9oVxOTyjb+juAXIjgSP+3Off88b/OCJn0BP64kgwfrB+ASCPbWzpZB0TjSaQbkd5f4TDIKzWqKwjLk2DurGalfgU2l0gpSI7tI14rCeesylyi9LlbxK6hmf4pjD2d0wqYpc7wl7LGvNevNFzHJOpvWOs6ZHe4B1h3DZHtRTeDfhcjiDMU46dVXMnWMCLn4QeOUj26yyM4A1Jf2dCNEoHI0vgg44pBW1atmDG18aNVwmjT8BoH3Oanh8L0sdfC9ZPtKjilDWUkUicwAaE4IbdbdhRqhX8GrhefhVVSlkADvBT0H1YhSW0gQ3uCD08KDpuH3RONZIJ5FKkYlNkooe0H3KapcwQerZv7jmdpiD9I8U0Axgj9mlyjpgIg7DIJ+i/AeUkrC2S/sm8dGEXgZ+ieJ3t4Tf1BahvNWJ/KmuA/by2rWcml6YYEvpPw2jprfVoZvgoVOecxEaqySgb1eKRd75pxqvrOJJEzg9W/WB5gRi+3y2r9Iho1QvKyGisNKdhcIq9XL1AJjnTT8cufHq/Ikrhx+PuUWZk9YhCxncA2upUDpwtroZthK18cL4uTODod1pS/RaFZ/ageYuhP+v4jNbJhrlU9lbWRyP3DUXJkkAgV7nhR4AT7klzbAd3rtceTPEnYia5P2pF0IwEFMBlh+fLRi8MaqgBZ8Nwx/W/25EpNP2GosLdeWVxz95Pkz7uqjKAG2afOkwjcMXFxjiWTIkekjhZCTdoeQo3eDcy2hxRhMHPDv7xZi+Q45fWTjSqvI2CviQk0g1oAbvIzrxnR9aU0lXm4dEPNTGfOW1W6n/1zGdfwlMHLp6Vbg5qPp823kYINu30qI9DtfjAEtHyy1Gc4n/HobQUVGBty5BynIJz8asKg+E9XkT34H+k7Fk7LF1ftaYQfKivQpJbpNPukKAAp9kbmnf7/dZcpwbPhfi2GixRS1ioib8egq8vnYtfFOWft0C2vK8Rgrcq0K/gGpWqJZAILbz+WGkOBtZOLjzA/9MC1V1bxBlMqmiYhmRWCAaav6fzDDJbOc/xcvcWXUDTuTOYRinE1gM6/kHTlTW0j9sY2/U2Drwnzvvg27DEAMjkf7DPcf/c84N/HvEc/dKu5PTV9jYamJ5lOZskHRqEYzF24sS6GvAxfSGaAvytsl/lGyho/umpR2UoFbaPwOphhZk/3toAp8pKm4Zx0pyScOHIIko0W7ofm3gMg3vA1xyyZ391oouxwTX6N0YHKhTxP8tWgOCtc5lXkOgE3wFzL9Nd2+c2sf7yw9a8TUgFm4fmx/5tK6nHxtEBM2RVNbMkU3D1Lp14VadzBlyqKah83A+ZpHwrglcKIqlue2TraUTCL2WAOle0BLpkADVShoeWas3hveRao8uJI5hD0t5taD1heQ+DnCxqIwrKDqX3GXx86x7BQ61smB/DJNt7iATENB/LsI6x9y4prSunrWEg2aiWKkNx1Bn8i/AXjjHGhsJo+PmTCGVS+W1i6WCxFCPmoOvetztPGnlJgHMZz35y49Jogjg2FPGun3D0JDV5yylX7FiufupYg0j/b1567DtDSaxZ267+EN/KDHZNuciXqXE32YwDy78iu7PDpzKL05E5gMK/RJHDyQ5IqkJYcNEQFeq+AsM9Y1TWpiZSGOpy+S4f5alUG4Y4DFQxMbFFsQpRYhBKgPn4Bf/jSujDuiU4+6XsR4WUnbxtQPsFa95b95r2yA6Pz+/f0NmAb4L/BP0J/gPyF/Qv+E/Qn/E/En8k/Un+g/MX9i/8T9if+T8CfxT9Kf5D8pf1L/pP1J/5PxJ/NP1p/sPzl/cv/k/cn/U/Cn8E/Rn+I/JX9K/5T9Kf9T8afyT9Wf6j81f2r/1P2p/9Pwp/FP05/mPy1/Wv+0/Wn/0/Gn80/Xn+4/PX96//T96f8z8Gfwz9Cf4T8jf0b/jP0Z/zPxZ/LP1J/pPzN/Zv/M/Zn/s/Bn8c/Sn+U/K39W/6z9Wf+z8Wfzz9af7T87f3b/7P3Z/3Pw5/DP0Z/jPyd/Tv+c/Tn/c/Hn8s/Vn+s/N39u/9z9uf/z8Ofxz9Of5z8vf17/vP15//Px5/PP15/vPz9//pv5W/+d/XB5+euLjaHrMV9BtI1XdcqzCUl1JKGnoQqCuzV2P76C2UvFfi1MYaps3+IDEDi5ICA4kLk3MNdyhrVV2++d5fmgQYjdV+acoPA91kDLHtcGxHU/GQf5LvpyC+Zv8bqHCDOdgi0eACZZfhGUFiautepL0EWJ4LbgIuHlxlMH26F069xgZR0Fi77sKJ1Oqb2nx3y83a1uuIXer2CBP80aH2Z20tJ/OyAk8LixY4fnm+fnw/LJuguUhXa7T7KCZ+d3GzDFCr4lhNvvQFAA3R67ZSAil9B4qbtMqbkwycOD5mvv5xnXn+bxzJ8XzPSR9oo8vBk4l+x4O9v6XwK3AFEAd97y0Fgece3uXLfgX03nXUQlM43Iqj5mfTexFa0RF+6drVgOz+V275ia2j8RN9KbZPe43Nkjs+3BOgAee32OzxVlJCQOiNpPJDKgrWH8pSRwG9UZcr96W0ybs7BCK9LHHdrPHacZJ3CdsM7v7S5O3QcfdNcZ1tJKz7iloqq8i0mSmDeUz2rOadDe56olidNSpKoto3tPuLKNn7KuPk54X7cMjwBvuXvYkL+I3b4hv9rd3nu9w5z/fjS7Ud52oYvcf1+aSHi5BL+NAexmfPayArOXb+8/FQMid5x69woSb1f3Qed0Kn6AIJP1gwMvQt+6kXpvUbymh8VdWKnV465+gMPg37s1zRWIzwBFXHtrEgLqXaEmHHAOFrUd6H8A6js9MdoNzZJ2DrvNVbrBADsOcLMCTXHrFDwAbGWF9l5dFLm0kUjDkKzPcQilNOs6D8JBO0YNrDtEJV1xxsvrk3pEPfz+S+fkrSo57GqOkJ3etdbfTtr16+Ar9ePaiq7AU0JaB8ZlaI1UgEIwyOL+xhWrXoyUN+CO41lN09k6mKoSy91M0YF67pHI/QTFmqlfWyk2Y+8fIhJ2dpl8TL5DvtHMsoYpxlBzZuxgQLp19BtK1PEai9fx6nNFjDNc+6/F2Bnsb9/GrogQEzxRASEexDAzdj6WsKmhl4mbrHsYu1vyARfClWwqQjKbmz5hV289xVsgw1AWjO5iZdQMoQMWFmJgnlxWK2q0FizGsJCxmEAHY5iwD5hOBRR9PxpGNn/ZNvjkAWPAQ1yQXtbBFz+OwQKy1Znfca4Wtb5feyMH3RUFKU3RwCecc73GwzbI9+4r8uvvDdHFL56xEyDIpX7uARZbkKcAAuhdF91auqc4Hpoo3H3OTxsuCs7pd56OEe8cB9Sk5uQsSWh3sMCM0abLnBPvfB+GpGECHW6PgE6fClLtGnhalMlYhxXT+ZYWUNexPnj/x1di7EHFf+kGj0qVbZUDy4cIgL/vpLlDnXYnsbkS698xlDMiaTOJ5zMmXtOSclYStDxZN1Z+8Q5okbEY4HUIPdesHJeMrxxhp6gM82vB1fhsQwt4sP0EAPM6WMHJizu6F8Mtc2Bac9z7mXzdX1c9cY4BHysuGLn2oG5ePmc7Jfnn70zQCBeZDbZt5uK045+orQTaJ5ZdU65Jjub5Lg39QmzzdePZFQfmTZTKMX1mQGFu7MmOnWxA3tMux66hWltVbjKA5Vw1SNjFQnPsmycv9aAIHf3a644MZvmbaxGnbC1Dfm59o2CMc88Imf5Z533/rdzrFdc9YwaTfJaoKfgq4QXsnyqKiebkYeqMccpFGa/MhqM+D178pwlMeD3mEG7HZE221DTy5hG/aOhPEDyEiVViG8RKVPcmIuIBYf4sZmz6HhV14l5c2uXNpDnere/4MRN8WhTHnj3ldUebHB/HvImpuL5JGJzOERC7su4TAOR6bN5iWYq3LNVlysuONnY5p1X+cr0yAlBP446/yTZedAWRmbTu5+AeVNM+IqRHi9LqBt6WhBJq4wGvE4lEoYsWLoFonLiQz568RmP6VLwW9Smh6xWd9oz6owfPw5DuJEQuAY/zFj1VONMe+gpbwtrHBCohTyjtWU34Dbl9IfNYu3MBS8qQlkcSoqUPjEI0ibJ/7f/PYOVcLvdrUKGqFKR0qI2MZ0WhRaQt7qxd96k79oi/8ToI/VG2xq/3GuHk7EH2R4EjOdfAjuxdfIKssrVVu9yOTLeI85VzgftZ5FQ/dD5QfFVxj2viNhKgS8KnAUjd58SGginTIZa5aNw6LF+pIPpfJ4YY1Xo2lf6C8ak8Gum6u9a2HQ79fiQl0qkLKNicgw9CwwWuFTQs33193QCRg/qlB+XvLImTzu3hQs+dM8FuNcIGt0C0MyxzMx+rcmiSoqwqnDXbCzFu8q2FSDjX/Uu9J6oHuQxV+Fw0dM5uhToLawZudv46x+6kR/Kj5vgiZSlETK8VcPYRn4Pc1xGrAO99uJxmPinJPaL3QThrH6K2VfJcNhxLanwXs7lDmro4uurywegif4BIt3Sdnu8NHkiYHDy6nWh11aIfdv53uJi4T3UqKyUdlyT12Clf7oBc3mwbJ+e8jv4u71NFm/4qu7QPQTFHbpZaYIw0TdRAg9CK1FCGrYuI4ac5FIBt4m1PsYeZBC35kVDYD9So5Yz5siAjQUsKKxI5kk4vFV4o64roLzjtwUskc9O03rRLKbBK5c+neEaiJI6kXNbz+YxRYaM/AkoPBjG/DIRkXHQ8glG3ghLuTvauDF4JS3pisdotPvgDRAKefeKjxpZjEushFNQu4lkVmo69kHYa7kumZSnt8GLlvpFDUI9Ts12Z4MeEGjlxWs5d5m+H/Od38j8Pp2Xl2i4Y4A9qJGS7inNmjptYeLYVEwvBfdItkf4CAeKQS8r5oMtJtnGKY6bZ7AWfzcebZyk+FieZCuWH4sgtn+iyM9jo9GC2dQgsliZbvuTWiOoPQSBBKJu28xwhHQ7fb8moouuhmORowny/0Pt03IFS5SQYpWlMKoNogjdcLfTJ37A9Xyjse9IiBcJA0oPLmbVgBCmrlykdBJyZmcQs1ZI29m13tLCbOb6E9eo3eF0ke/CIC/FG/47wwgZTXhNr375iNkyIJI8vntXiLf1nMneT30M6ssHv2Nfkru+vJhDuZxp3tQyDzHpidYYVzijP+nq9CsLu/nTHOfP2bpRIdiNZQpN5p4EkQXNRD15OpFEcfI4VSrb8TXDVyNmH811ReS/nOO0o8XWdW8QmdyfmQ8VeUtF/4UNt9DlnUMNBeHMq+gwNcPBJwCQw1DBXsZ4+BDKHCD/2q24qCxYtoaR1L2lO0bu+o9zgn+Qib/UodbskODHoGdaXbisnJnubTzyV8dgAiu6JurzomXsjvSzBg94cMfuqM2WXrPlcwnrLAxGNj/Yl3Si/igcR4VtkmevtZZI4UHEmnOw55Q9L026yzsdMhY8DYG7lo7cnnIR3MjMwROM4WGnTsBjk5FBI7882IpyG36wxwpP4HdfnigDEkF/RppBfyCZstLcx/zV0/lfeEOg6Uej41iolvWzSauEfCv1GEjucXTHRyDabXcHgwZg=
*/