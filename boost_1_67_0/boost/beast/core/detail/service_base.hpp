//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_SERVICE_BASE_HPP
#define BOOST_BEAST_DETAIL_SERVICE_BASE_HPP

#include <boost/asio/execution_context.hpp>

namespace boost {
namespace beast {
namespace detail {

template<class T>
struct service_base : net::execution_context::service
{
    static net::execution_context::id const id;

    explicit
    service_base(net::execution_context& ctx)
        : net::execution_context::service(ctx)
    {
    }
};

template<class T>
net::execution_context::id const service_base<T>::id;

} // detail
} // beast
} // boost

#endif

/* service_base.hpp
oVSPFc2esdkGsmppnTkmnGKUTyiyHCdxgZxgTmRZkbb2cjxB2h1Q0woXtVYh9dwPl51qMxAhbaN34T09gUmEbo2RkAHen0Ig/E7yFWZIUFqCkw8iFQ0YOQuAzRBEXobF/j1Xivw3wdTTy52dsUsVfYf/WoZ6CQxeMWbJVEoDl2uDSU8s9VTF9e4EIK12PISVpn1m/wiY51m3/LR4vjT7eCykt0SLTgkrSkfTDWcYAIh1+taXJHw9+sy3mrT5jxSHyxHm24bfT5k6EATRqYNC4G+6b2n3PR5hB8Mqu3dnKQSQSFx9oMPXj/GxeD3su3pL5AaY33MHzLcozGYv7QK2y9HtQP34ruQkCxgLvIAssopXYmUYJY+PsYOf8ug75UzSl+f1gAlIRAvbLVp0rNOUb+rCyR+uF67KW6oy4f6xAR+/OdMOJ1I4NWDZ4soZuiEYv9DIubavEB+EAtLMdF0Osm1bO4lFChIKac66cBoJYuIDd0EeoYyUlBEJA8QcvDQGx4SEG0YWxAx7xkaeqG92DhvDDMTWt5m14cIqxC6tq722u8bfrQFbH+WhWZfloar1WF6cXrbEUSNv4oDTpTPdgoGvZTah5+mGp+VgVwfONtSGwZ0qechOyG6+1LaNRSmJtk4EbIqYWqySiYFzHwSzJVofXi+2MbGxt9Viv/7Y9T8RLhbOMJDTw26GRWJPHnwiQc+NSWGzYF/jvT4Ef4oJZXMXGJk1aZELlcOhb42981qr3FD28YoAnxq79El5CDoYPuQ9HBwkq62JLYw9GhnPnC6mkYvMvlJzY8PB0w4cQdz5a/dxzChJmYsrTvsP80fM8BHw8uKlAk6Sr19657hSGpCsu4OqnA1Uvl99F8Rm1JCc3/Tl/EbL/aK+x4k0iydqxdGY2XQ/RCp9mzj40vISG3Prsv3+uPFZ0kvHgR0Iufry9aMWkv1srAarx+na10mJzaeeOoORugxbCtaJuvdYBOcOLTeYz2NRJ+NHR7ayUKD+sTgw5/AVWhdvQuoSqkKbUiBduR+Y5yZHvIons833sDk977sNN2pm8/z+veA25AFo24/ukvCN6H1+5OCAnAKT72/NYVuYBYWkj/5ebRZ6HmycnDYdn7sklzspa7LNqv61BH0iv+beOsXXsYPO4Jo31268pXEqQbI2Hg0ol/82m9qWjdjGCH70zPV02o08z/mGfNMWVT9IPLv4zYH1uHs4j3lAxmyLXrtPFy99YzA7eV9uqU24TTMXXDFIFvnKhi459Dq1jxoNWQwPFXs3Hb2CdvKMVhfaB/C0ltpWt65aM9TMPEGkV9O7tr62Nh0RXbl6qo8MjKw1tI9MC/kth/YMDbfViYmWq749rw7PhZudfaOqyYzuExi8PT+q1Fz+hNaXLVwNYmlwY1zUwXtT/CmhLZl85bZxF/j2/ZaRpnC1Z/ilfBns+ZRd5mEmY07DCJppT1hg4hlwlciGDAveWxHlCjwI5z+QJQxdiYrK0YpuNkBmBG9HWi1sypzzkT+OopRIAaxIFwOE0MDED+cgPoNdtQsE1BWyTQIV4sRaHVwnHCfgfPJmAeYlhY9yPPJz+CWRT3dt18R8jrjZgQfM9KVwN+M9d1nC8l4E29GWfWDoAV7RzzBTAVYF6H+ScTmErt2nNIi4XwffvHBYEaEwyuHrIx6h8JW2RbIZKwftHtezvd1BZISVnnf/gSQzIgEQtapIJ4y3/ctf4JUcvmW7C9VYJvQTTimlkb2LyV2xU4vuz5l/cdgTzoAaAK+X97Bw0tX3IzWByHNJ/hp/xwNXRBaWLUKu5LA2He3LSSfkE0TAbeVq+nx7xI4jXL1TvprqQ+zijXQoSpNvI8M+Wdm/1J/g3xjZ/RSTokET6GB1DZtDah2j5214j49l1Z+0Uz5FauR09qA++Lud00Ponv7DwHsDsZEzNRiWC84vu56gEu/FFW03Wk4qrO7vs+gV9SrTQzesG3aGavCF/eDFI004hYDnvzeDtR40MuoyqRbozNnAHCI+TBvAM7/GqWZqbku4U0qrXuBO0ug0M0WgbpjtJz9dAG9yMweYl4MEd3g6Xaz148FoAcu87hSBrZzjEj+lz8YcI17Z2saaP91+YXpLfZdDxBPy+5Zl/mImYX5jFmP+YC5jjmCWYn5gnmR+Yp4dwRm5Xir++/13aAqLdp/WknbgHOUi6chh+W55DJ0RHRLdAV0SPRx8lt2P9oKDP8jl0gfGe9JPRoOmRk4Vr5cgAvdPzYqDtgu2o7YK+Q1d831MZkpmXGZg5hBVuaCMmqOStZKhkrdSgly0XKBcllyDUpVSgVKXkhLxjiVYJ7j7R2p1mka4Ah6iI7PHqN39bEZBXELBbMpG4EbRRigXrRuqm6ZbtlmPWTvqwANIDofZ3bL3dXo/ZkP6AGZi+iDmY/ohJurWgixjrHfm50TXxMGy9rVZDru+HWMqcQZv+fExK6BV5DBHjGJlN9hHEUzGsPE04aYP5kdZo8i0YvUGiVuF6zGj7oly7MYp95r2WufYxhh3h3ZH5zhE9uhU+JTENsT26HR4K+Dulr6rsGENYf81JaYKXQS7V87UmZUWejA8JIOPzlU89vi6yNrQmsqa8ZozFwjXoXPE2ODpYOGH37JW0ib+FvZW6XrhOv0W9VbraiOGLau19YNV4QLhQv4GyDoHafe8HU7B+sqqOpAG4DRgm/8kv1Ur/QP3CB9MBFATwAWArQB3H/Sfa7Q129vvyq2Chxsr2oHcinZ269FVlQ4Zhxzj7f2q1A6aJjzWzkr7CTm6FrzaVGK/RIhmWWWKM+k/JOWvkcHJs7yBf1SGKEI0EQnJhdIzGXgDDVSGKYI0KUnFpSTF8HIZeAIb6I1VDPHN9AcpsqUqNd8ZjhyAruVWttsIPTUjfQucOjwOHcyc3M7SbHz2u2vrZtrseuG76evl2+16YptrbVHMcy12bG/scq3w7fSt9LEuAdFohxmvXKDfZLrorh8y3dRORo+XjzDvab91MY5HN7bQ6elXk+hEgRVF4O0YmqXDkwiThcYhLrw3FZunVJMpyzMVpwz6a7frNlH8CKv5RiaiZw2bxJL/GdoXo9VEvzbN6LGPY1pGN4vC5WrGPNe0BHJ59i53RD/MZBwRbPbOxnLaMeeK5uLzwUOOss/57IXcchvRq+IeEc4wCtux6BqcEwYgjsXPNd5M42R9pw8iv5M1k5hxTDdlzaUnNjmue56yvhEXE6MRlxKPi535EwgAEkDOAoRXzDkqOyS6LHjseyVoT3N+9BfuysxljPIycQixKXEYMjlyBPIl8BQwDXAVfLVrc77wRjcAfvvrCPDkoSHAUYAWAWsB9vsLAXQMA9AiKf/0h7/03CT4mzBOw7fN3veA+lye3/eqsZKwwumWqACqvwsWFEVXFA1VFQFpZ7cX+YjtRg9gjusRWar+0Ul61z6KXsecM/jOVeNUYbbTiK+vcE45oBnLGkynd1GzpbUcRsZX70pvZXMrh9dTLIp/gFg6P6mw00HkpRel3kv/uTOdFi/ctaMD047UyM0WOqnCqH5V4tKA4npZ6MKSlnSUC2gnKF+9jrmcGqIMNYpYBSZ9N86oNFGga5Ow17sZWqb0FwZk55fyqBv9s309tDQWK5yTye90s846FRNP/TQ0Szn5xR6G1MrRqmUaED1+ynMcodIt8KZfSdCQSd4T5lRmjEaVuj1ptERt9Xsrdyt4m133KolYpekwdzzaWXVqZ6+oFvKp5zhwOLV+6+A3LJtVL2kk2NPZIH7Efc++I3yGv1Bt0exM7kxu0WzRVOlo8HhCvPgWdp7o4WZt8nWFeqjcitF8yHqVNYxbrK6GNKvGeyEu8JUYDUQp03rOfCK6tE9oB/XSeJk6wj8kvLLt2uwjF4wIOPNH8Yfwh/E/2EN5XPzIjFaH2cs/I/naArUP3eAIDbRk97HMbS7V/3T6LHIaSYKHAVS7pRzqmbpUpi5EWtkPEmUbAy0VxA7+vU1gudBrWaqI6at44Hl+jjERHlQeTKzxcOuzIvcQ36D7qH++M3kwuFLMFDoYelKLUv3QrgDCd6Zvwpxd7TbGC5XCIwaltcYJLvqjNw3TrbngBkgTOcqBKBnUdY7J1thy82lxmA4y71CUEKmNnD9zrqeHxJPRiVPl4H8eRj3O4xoy5LaBymHTsHmr5YeqXBde4ernTAZxuX1afO0cxHicwF1NY6mZ0hoXtVM94j4DYyc0XyLUrtEoW1TS+5v+oGSkoSa1omXvxpUTHaMnRy7mFkknFHeQuiT1JfUt9CH1KfUkp9Gw5dXsNO00b7DssG90bGdytXN5c/RzCH9azr/evNnS/zGIB5V4oQ0p3OAR+b/TFkbDeI3uYZrKI9/q2og0lf4L6KAx+yN1v3rKuYlM4iXhSv0dHyOeyRw7pNjHrX9yGDb2wgNOqxvjv05o/Lc2htaEjPwg/giYprOuc3566SZ4ip9XtBFC11A69vVyjdgMyI50U3FjwTyiLpZRmyL9H5FZ+PXXtjLXkA+LD4g3ijcJ24R1SWPMmWVCqtiMwg0lL9EGOZZl1fSfG0negY2R7MoV2j19pS5P9+iGSvLUuRmSUjLXt3pwYbeP/LZA3k0Ztj7cK2gVyOSvhoI4kUHYVxJoYbOPq9LlR1frq76/ajiutq5/fNdUQtVCrW47s56FVYiXWSmtkIyfmvT0mwT1hKrdW9rA2hMygIL9ZKXuzRYEu+6KCvUtfjLUAa2b+vX/DrCIl9bKBn6P38CcwVx8cu7KHskew97kgCW3zDcCH/UQ5YAtDBBqO+7eDUE1nZXSDsyQjPF/IATi51x5+cEHewH250syxNEzwIzFQ751heq+jKptnq22kLgv415jPTAeK8OmIppRLE8xrsQo0m7s3M+RymIjqaslmV5lmBqPGjLrFjqPG6pqN2r5capWYyydxnWp7T03bd/bF7GpnidsIY4yR8nD4S4iX/C6j1xsLTUbUdmqiU0ZeaImLmCjxPTb+mYqdXMTZO6vJ7JXUSTu8THzaMfhxI6JiFow5RSPXhb4vGS0AOlxsM+8Z6st3BmbqYW6uVW5Cm34FrwxLJRyKzBpVl67iCe0fMEIqM65Ohoq5pu0+o50kJluGTTp61luvaP981i7TzhyKJ/Da3qbO4Kf0alZOt3awJ5actSlxZ3y6i5N2x4lzT5yuQuuufLoqi24cvFV7+kQ/LPg4DbT3nGGeuXRjJsc4dezL4pr/OMH7i8NfI87z7FKmd7yRzit1G6P0WdMgMsy1lGKW6UUN2Ci6nE0k9Bb+Mqr73wXjvzAK20mbwl8bo5/bz1YbZ8hgzGmE93oPiQcBRIuAmNue9DQ+8+ICQ1k12PXiH9zkNVoR9tm3BSIVbyzJ3OOwLZmW5Z/rZF5r2T4o1Q3hb29bBTqUPVLmw8y1LnPE8BypLSkeUGL8np8OhS2dxLMEzoR9wrrcYzdhOfi82H1315YokoAfP2UGpU+8qsbpkApc2B+DiPQoaDiYmO+gTJ5Ayx9FaKfaIKyrGJKYKbazxJm4Ss4QfQyX8LnbJIJfUA3iS6oGsi7PLlVxL0kLTEuoSpZU1CIb+dmVK/wwnH1pFgVNrietFvekogzLOe0Jh+Iflbs5TjLbnC81Av7SHqyo6gBSP54GwMk9FcLlsrrfxcvSiqrFnVy6k+4m+l1I4QMC07XlbyP2ujRBrznwh30K0IKpgjPU8wONLbu4P5OupihDOn+KoBYMXsLCAg4tZViCCZSj6sLWV60ntDsDAd2lbFtvBqe2U4ryppCMuL1Oc+jJumagmVA5kbipSNTj5F2kBGspo+4ObzJ4eij2A6FJ+zv7J6bTwjjrywllIqcxsyXrfraCuN0hEp4XG/cT0eaDcNfRjF77sAelEgdbFcg6zZ3MvgfZiqBkg5b9CXzQd0mykIGoYwlgbi+W7TPSRqBeLCNRRKeD5wjE2g+nFMMPVoqK3HvqqudmhsmDaa6Z6NASZOeIq5W8UhfZHd5hBmVG4y98cOL3eXlPOHLMXvDTSp2TV2agxcl9YC2mkj39hg3YspmcnOQ99PMw1EtQM0VmcYLjREdynJ2OqFpMafID0+SzHFdSK0W6m7zvah0avYoNVnV14ZUZXYMsW9qscxiANcYPVl0bQuEpcr/3Py1zYkpFGGvUuRTBtHhHDWoVvbS9p/FJ7eVVSUvyp6i/JaCuWuYZidqHbqSrFgroRXCPEnQTl+qGMdNoN4hs31TqFJNcKcIwIR+hoGvyYHsisZ5NeTBsq8fxaE9WXLxcnVHabEDygGysm4xuJLovwFNgdpVoWJz/TBnscPg9u/AE055Z8IKLg9vGQsKwbzuOgTxCWsVoy/8y6uFvG2J7tFGgSUK1Xm9JrHTjmgvxfjxNA1V5BkULALoAAACfwX9Cv4V8iv0V9iv8F8RvyJ/Rf2K/hXz6++v2F9xv+J/JfxK/JX0K/lXyq/UX2m/0n9l/Mr8lfUr+1fOr9xfeb/yfxX8KvxV9Kv4V8mv0l9lv8p/Vfyq/FX1q/pXza/aX3W/6n81/Gr81fSr+VfLr9Zfbb/af3X86vzV9av7V8+v3l99v/p/Dfwa/DX069+v4V8jv0Z/jf0a/zXxa/LX1K/pXzO/Zn/N/Zr/tfBr8dfSr+VfK79Wf639Wv+18Wvz19av7V87v3Z/7f3a/3Xw6/DX0a/jXye/Tn+d/Tr/dfHr8tfVr+tfN79uf939uv/18Ovx19Ov518vv15/vf16//Xx6/PX16/vXz+/AOl/zz0Ms5C5PCVXrqwhQhEsaKHeKy74NdSOoLpsuC9oJfwvRlsBePQrsPW5QnGf26kmSaZCg261WoBFQ4T+1pzaGAOsg2SZYFsDPDCovw8Sb5gOylIG0QxCT2WHB7ye9cn9oHG+QPBQVLo7c/s/Y2gZ36BaE5QyL2zCN1YJb2tf0EZtmu960KVGGrYn7D1gk70r07OQnLAMc+fRcjkC0YyU1Q3cgstbpILHcPt+9HklrRGN8hFfwukMgQpI3yC0YKn0loBTe7ZvRsfQE7w261ZEKKv2Hyb3/mEAPP9V4N7CcUDJblIT+VE5Q/BSMdqgprtONTtKaRiEvu5mvnpVhhCP5q5ilV3yC0C144DP10Qc/DTdK3Qven7ccjt75P3OFus1MmRsS03a8wToywaQqNXrBojC0GKJF0ogxcxOShdLHeV3LZnIJs4EqcthNG+ks2D6ZVJJ189T+4/q3D8GPO54DecgtGGmItXJfCvOXDGQvsnZJn6X2JOTwfwP2BdLwL2r6iDeDXN9YYRsYp7cDj5yyuiplVTLGDLC9w3lg68Tud0duAGxt/GhaKOuuALYdFVpd7LG9YGT0cb380T1xsJarIbEHwTinUUz5japIx4O8fM7tWIgyRCB4m/5H5DjojXuc4qJJgy3FrerLXg74DcDwCAhAdyx5dNq0LpUXw1t2jpi5PILag9WmtCo4HvT6jEy59Wm2klic8PpafObPZaUBRWEAfJx+NSkBmb6GjHGdt4b3MGD2trJHDJIKBYlTPax4rVriLJMwKMsoZ2iypU+pIxj8kUpkgWuKWnxDXfpZ875jYqV5jw9ytX2hNPGLGIZUnh15A8SN2W8YsZ3UEnPt90ag0OdUkxY8C7S/I5NisqPm9Or7BmscdrqKwVYpZS5Tn4EDX+GUQdpqczNQzXTLABoE2osGTy1/3xevUvrvW9u90l4tqfno+hkVDZUXbWu2US2KT75kJVe/vO0MJ8f0jhuius2xiJ+xFTczrq7bBVJMUCzzhziTuH9mkC1iSHJxgp9rUex2cL3GodsSHfyKTTG0rE4FcisiKxs5CnEwQQkxoJkOifHrdR0di4kBXja+5ozfnE+Gl3s/rt0hJZeVSun27zozKNny1HBRQDEQYPMYCW9e2c8ucDQ8xZ1PVp65JBKVY41/KG0VqoGBZfwHLa4ltVGC3oBoCRm1ilc+oCqsl1E2p8s0np4ehm8ZMq8ldq892XJAR2z6gP8OC657mXk3TrDq5rLhXdT2iwFC7XUKS2VftZvGLytUWTmz12lQLVJMyqetjy8yIdKvu1NWuhW4S/JZYmUFHSXQdWsqwPgg6ItpHXzCoPxoHbd9hAtLynHu+RZChSK69mpQeqKYYCAi+kjqzI1QR5FdeYrrPlDyM6qrp0mbyzvIK1odpIp6dVgW0+bkLQtxQD9UCyvMrTjmHS5h2J64mjzZkydhUqLxzyskj2nEXCXFWxRnNC2Ax2a1PzuTphYktaYJbNESnkTSKvliqTjKfzSULatBRh3FpRuWZzD4ttF0fSe0ZPB8TnPXQcfNmWMsmL+dphmr+dCm4H+Msvdn51akkPS6PS3XGF4y/2slOAApBqRig4JH/jtTrYwLdIEZJ2FX7nuq+PP5Sq/r4PGl/2+kTYCdrq6quvb6fgfi6o+bJ0mgozEUelTMkN88IvKXd+lZkOkLUMVZGPJBEJsjAJKdDI7Bxsj3TKU2dO0Xni2BjH4jKSn49haEZWn2Z4bkuZHW6GtF8MGwS7J6Rf0sriCmBxbnahVrtyPd4s8erhGDyNrG/6OdeMICxReQa0UQ8O8WgLv5OZcuicr2YzdCXkPzxCsFGOty/VQFC1rtULMoEWAlcPRyw4KD5O/roNYSIwmcDdty+ATr0nNzp5OmtgGVKBch+mmrYPA7BuWN/nEO8bYrpwTfc/PeCzQ6GYBuGNZxyUCg20UI3guRqTNDe8LdoRHOLY6ag/x+ck0oaGqCub3mCcrAg+YGOP2pmAYLZMmOswxvb42nKzNYwLujXoO56fdizPWWjxBmSPJxS40Nrr0T7yP9K2zFZSYlY1+mcX01LI8n3vLLIDYI+Oa0FqLMw4MubAJPOB30FnyIvrP79S97xLzdxSFLawWkrJqP+FcWbAvL8sdrSMkorBrDl2qNzR0a5dHGSmdLY0HTo9ae5gBrR3hn+ncAqsajrSxe8VDR5DkB1Af7u1SHCeEIE0JQ1kqhvXj2y9SDeXr3w6BotCfK9M7jXunZGWhN9NQW3Qtl2/aWSlFmyMUFb3A4x6KzoBekuUsvtvN82fmRzLlkJVvWNuFRjTbMtI6Ml0xe4vzlPAvpAGlGkjguHqVWXvJOWa4MsiyqbjNyBjXEnhns62x9CFHXZCx6sqcgYk8LXbtrZKBUSf0feB2cNnJtMrU+5n6ibjO7WGhtLuojBVKPRI=
*/