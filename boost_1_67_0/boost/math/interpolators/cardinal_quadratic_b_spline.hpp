// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_HPP
#include <memory>
#include <boost/math/interpolators/detail/cardinal_quadratic_b_spline_detail.hpp>


namespace boost{ namespace math{ namespace interpolators {

template <class Real>
class cardinal_quadratic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n - 1] = y(b), step_size = (b - a)/(n -1).
    cardinal_quadratic_b_spline(const Real* const y,
                                size_t n,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                                Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
     : impl_(std::make_shared<detail::cardinal_quadratic_b_spline_detail<Real>>(y, n, t0, h, left_endpoint_derivative, right_endpoint_derivative))
    {}

    // Oh the bizarre error messages if we template this on a RandomAccessContainer:
    cardinal_quadratic_b_spline(std::vector<Real> const & y,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                                Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
     : impl_(std::make_shared<detail::cardinal_quadratic_b_spline_detail<Real>>(y.data(), y.size(), t0, h, left_endpoint_derivative, right_endpoint_derivative))
    {}


    Real operator()(Real t) const {
        return impl_->operator()(t);
    }

    Real prime(Real t) const {
       return impl_->prime(t);
    }

    Real t_max() const {
        return impl_->t_max();
    }

private:
    std::shared_ptr<detail::cardinal_quadratic_b_spline_detail<Real>> impl_;
};

}}}
#endif

/* cardinal_quadratic_b_spline.hpp
c2peP+lMQPUgJLYzATA2Q8HnVwps8p/lVyF1YC8+TOomIl1S5fbFIUmDltOjbWMS7X6b8o8gCOTGiFjnNvmtSp4c8I+Stb4+xNYhsQ0nskArR8sXv64hw7qOO8I59OPbh5/uDrfp3rv56urp8/OO33bV3+/OieOlD/wXNsgPNvKF9DqnY3TGLPX0wB7HxO1woj4fDs5YQV78HQHJbCosjzR60+cXypWcnyoWKVs5F+b6EW/DmU6ifKOpH45ofe5amay6tLNbfPyyvdI/v/2T4OQlMQW/SmSr+jPzYH9Iu/bfTcOcwSB7hGXYeNiueDlg7vhWUIJctDFuklqst+P1a7o26ZgV2kizHDmAdOax3pCH0+DFh8NZGOMLk2moob9BxyKk4W47s9sXO97OhAVUHFtvk7BIcWuyLASZmC+F95dkphygTTM5q6P+5RC1wdWmrSqOsDtMCBj1AcdVUGg8MZ6dZQYGO1lf2KOTA6A/CtMCYAxqFyHStMYrPryOAPHBgxB/5jxg1U7xg3DXIXKXT9m9bth2LTDiUMhYHaMUJExp7ziEU5Oye4JHxZx+weMXrEG917y5NvsYsKWf9k2sgM/2TBC2pnjEfBX3r2MnPZNvuRZBes2GTU86xYYwnTa51XDDisbaUz8ksGOPOD0UgShF00KHl//4LnY/zslKPcSTu247Qv65HNBKOOvVFsB/+tAJmU70FS766FGZLlHhEY6mXeymJBV05WzmcCOIqBeLl9AhT8vciEYFJ2MH+O3NqAMmvM7+4/5KjWc0Fesj01JQ/xtdc1kg81XQk2asaYIEPSsI7CEDnLOatOr4k7nFbqOb1uR+5S1Fl2oSdHBiJfxE3zbSY101TTg3httPsYsNwHevKY+d/mDZooF7TJ8PuA83kUftlVQolzNaVbrMqPz8hKjOmJtIqOHMJe/gytrKI6W/B5p25XccpbTgby4p2Os3MbyR38yHPo4P+mVLbGH4n71D+9eHHX/Rtu/TueOPvQ8Nt8HsuOEKJ69xVTCKx91gayW+bElrctxzb933FRzKxLfbp+3O6nQKOeucI2aYe25QWgMPsbeKLfU7MAEtvB74PiTxmH/+uYVEFeAyXZwB4Epd6eFRCARUkdWTSWzLuBLSUsVxGe44F4P0DZ8h9SIpXwZO6F7jN1t51y2ZLtJM9CA0uUruLKbYJDBoAlGt6Y0mD6/VJlnlBBJ7jtxpBhCcfnuPQldtpxdRbD9MwNwjn8GFEbT27KI/RZbF1DHD7216u9PPGnG5nPIQohLwP4GLiv/i9kf69VUX+LLhOAJOm5ByeN/vhKh/0KovNQi68KVAiAHDbDBcQdRhQWgUj0oSN4yPzmCtHNcOnd+eyiKM+YlYrOlKi8enm2wQqBLRRAmV5x563yh3VyZybcPfltSm31SshgE7dQkTlKcbuinGSeH0Rtu1K5yD01eXh20axtMeyV3HTn/t+4NQXDOqXmPJvN72wwEPvb7/7cBs/ODt+9oOecnH5XFdN+Ajp3R08tkgc9t3uysfSiz1XPY/PZx5um+j7jxP3rQyoyJhVw907YODfeaGwtIOcA6SM5U/D4NXOK+M3fp44yofrbW4qQ8YgznI/2JQpdOKxhd9d78+fiBwAe16hgo1pSwAF5HH4jbQrpiSQYM4PZYZC/GdoFGETD4XMfoSICg9maB5RZKb5agozJ1SJCtckIuT4ioC3V1AUMVx0w9Ywo8Yq5DixAHmAROSEIIaFw0jCgtoSbZoOcXbJKERcDzXsgF6gQevQqQre6eUNFrDeS2Gate7qPpmpRTAVW7tf3XQw2s8JtvV1cjbSk+o0m/OA4/VNLmm9g7dvsWpVWNCPVHA08DpLZsO7AxTaT1EMWVRLNZO/3yWlecQ2k7Jbk3sUlpWomihJPQxpF7ayvJqBGlN8+bhpzY7l7+5z+MqWqpO6klBc5urhU5EvlWy1+3D0WD8jFYYCKrEwZGlHW9H2+vL0eZ22wG9t/vFvznYafI0cup4zceb/kH2B4vt/idOHTJq1w2vtVEgfg1u17lf6rZg9g2msrFB3HgJd9n4UFKtoD+rMU8HkAjr3zzaoXjnRNfWnnzw8E3tIL1xrHUmvriZPub8TF302OZlLuq/WP26pvFCgnE+7Gov+2enB6tPL0y5rO8qCdncn9kpnnSUvtJuvdnOFP6FIr7JSJKyNK0yGi8XHp8qCJ+yA1BWHf1sr907PU8kki1J4XvTaRt4b6fBYwHaDjzQTm5DSKKM1qPOt+nFSESYp/InGQBl3+g9J5KOpl4CFAFAVzb69SMgTopekDdAEkAhM+4R0Xh/PWFlnBQIpkCg13+cgwGRx9A4cxp2pznfLAdP6TW1F/lnmXVpLsYdTk94LpKrWF7PcrSGD0eIWsc8V6hnxqsSxrAvbwr12QoHnN3gSjUVjCmZt2FEEF6Ky7+CfTGqSkng7SjgX24PhTEoYnz4pKJ3QV6tgLoKdnPc2/Q6KQj3HXTIMHich21mNb7yDr3+GTY53knSykEaa+0xC7CDhNFtTnq4RSpG+DIRAge40aJrPsxUSN3PhWGwJjiYJ5Lag0r0QkklAFCkJAf08NbF4vDAST+ZsAsYWSbxEiy6q5b9tij98IjfOlfAJH2bNPtXnn7ViosMVXt942CjuB7urHbXffZuTEXOfXLz1+e/QrvtThxYunrcKb9//M/vuVv52ZvYh2oiAmBVtPOVCaWaCm7SsZs8ujmztDS/uHm/XptlF3WVEF5LJRkZQO5k4Lrg+5I4ZX7pjkGDePVydedT5VP+rh1/M9nR5G7ocf/g6ATJ8bPCVbTTL4XsMgEbg/l4sAoSmvbLd/F0lzOOmojTG7qGQA55L170YC4beIml6TB4X5on9mUIjqAnEnVabd7XMfObYCwLCBjM/B07gaoEEg2BfhHSH/6/GwtYlOrNpDHf3I5YcwQD8QV2Y1LJ16SHxbnSmdczyqU50pp0GMcZQ+ACqBpCR1rcXZ4aL35ADekYV3m4CV+3sXK6iX4GXk5DHP2Ck6WcyJqckt7UJFczhmPm63X9Xc/bHhQm2+JLXLibf1IrlRAtKJvKjUT723+EcjyQ68EL5xIBbjv83kZzyGqHv5VK5SPXW0ft35WgBEcMNJ74HUwriX2csSciz9QIceIqrIIRKGiKKp4xcyRfeLVz0WWBmZX3+CbNn+UtQCLqkbSAz9Rfqh5988ohsZucIPeM65Erm+5lUXNtu8/WriXyqxbNA0InN+TgoCMTzprcAJi9ZXRNWt9941+l/ejTGc9qrGb4+1de9T+Kn9squ5ne5Of4VIPbuaXj2C+Nyg5h5tDGJ7dYHhvcjLxo7tKV/KsDzLOfdEUSGtZujvlSU9tgl3J/GH6GFdt2g/xDmV5+GWS8knu87sxIt5/mWtAsXnKdZGwkSG0c8mO3Ehc60XjEA5xg/6t122N9nbeBm7kRu9mTjuk33xl0qd/UrWHGa+Bp19uO34ApuypPuMDOoP8apSAvB4N6ZIzJN17VD+dh79fv07G9xlyXjvPE1C1nhSRgpVgYB9PrZt236dPhxkS3HypX+ErfLrntaKZqDr0fHj8VjpGATKaVnvVrPLomLBGnngleQP+aGViR3aRQKvsiXTw2gID6fZTX+Q1DsgKTwMlg232HhWMYyEUZKBjiCZekIheXSw7srKeZoElC2ymSfjg4tTJSsrEBEcF8CiSfSXuVFxwVpzS+gfiziV1GQBOcWnlX7uPQRyIRdScplGMFySshTfY1ZYZGyvGLi8eG1OKieNRsc3ichm1uO/r2Fjwd0+CkhBejjirkwlkFOl5jrggp47yDO65v3g54fX9yWIjxBXZaUTmI0+ayNcuz0+NGflbhxtHAL/3F/cv3lK6X4N1iu4wNQogjRd5YAJsJEc5bIg3ifFlcFEZrBRLi9zRpLWj5Rny991wO4l1F9XkX8D0oTjptuLBa3y41AvrRKOVdX23qBgf9//WvI42ClG+aG8HUwP8pzeavhVWnaawRNxSdmcK40c4M4NA30OP/oGp5JmXORN7Mn0Epw4Xk5IbKWRHci5ApjTiqrkNZVitRvAEtA7iP7d1YK+87/oV+kWe9eb91NAakHGYu5etojTMIa7O7QtW4Ts7tU66pg8mli4VtmvfWmBzdtWzOWrht3i39V4ltUDE/nS8F7xb24U4WJ8eOsXiRwoKvuTXk5yOzP2Ehy3EzJboOVturd1cQ8bZpxE1N8M85cb8kpTIioTZtr72HzsBxDpkIEvkBKNOJU4Ar3nvpUxQLChZU8knf0xKsI8EUCK8vixQ+oBzs0SQ+NCx4ZoOd0H25I5SVfzK1nvY8qCy8KSzU2DPIK8tduayWCl548mXsieX/0WVEUfvMf194dCUbXy7+x46Zb7o7ZBmpqBaJmfIP30vAPxPz7+AyC1w1Jv76xdk5aRFElNtM3F6FoIEqmWPgkwFmizU1nAT82tpxtBC34gsbQoDAMj5db88dNzCD7Wv7+GJsCxWt+OIphn+cdKjoL4jD9Q3p0UFEk+3Vr+xK64ZUxThdGlinLyVgTczU6QxLyeGzddBYfD4Htry9aWMO2tQW+VY70OUofCSc9rf/+BjKZvH+bEA7NZuMpiA9j2MFVotDrb12B/rdOpNrDleXLXUl0prL4l/lFe9KhyewPzUL1H+Nevqw+mra82McEtaxqiyLQPHSEiXkXtAIjLZ9OldW+6K09l1LkXvV+1vY6LmWxndw+pn5fKz0/HK3BbG0xUdmJEl4VtHsOXhfbn14sBB8tV9c6kI39zn9+14r/ZsqFzsoEzxhY1oKnvbq/ClDa9aOa9Yfs6vIWOoBBw/WuhUzaqF1c1s3hA4P3JnP2K1kqqKCWviTDHwpaOn8jTg7N7L9zJSHVbQyjQgR4ZqzdEqHyCApZzNX1eSw/SDTlW0wsuzxylCZr03CvA8ClNl3mwkCZAcK33XkPvERa7DezY/bTpap8H2V8pNz68pBweSZbnVZ9bmOhLOuInROkA63bPKlRdCpfWRpqsJRQM9cHrIHRMR8oU5vJfgCjUOBfYsFP6pAop+LdPP0tb6gFFFbBFsu1IsUmlpQQi7XD6+mD5fPXcLehDp9OH3+9vtxU/m0KPAz/LEf4XtvIBzvi+yOm+0YMJKvsjDmJ9fLK9wvDrIdOWyH6qm97Xe6/KG4pB1023vEFt46K8eOjYd1+U4fktUtEK9/m9dX4/k/pwNdXK/XeWx9X3+xPT2Ef0+Zd8Vp3ud4hz7vru9Gv7dNPKdvCddH4PaMe099zxccX72TEijLzr4EaGC7c5TNBTbeILfjfm6cSb5uF/jQgX3/B5qy4/vBsTZ+fMzxW3T9byaxYe+qZxwPxiG79lefAGbhI26WTDcl5hth89NPlbSnMAUMdZZOV/G2IOv4X8+H3E2coQ8gH8Suwo/OtkAYLrDvp1whOt8wU4+sFw40/jE51glDI7H8ZefFBzK9aNuJJfJklXmQ4ImDVdDCKmOARC/zmKaFmHya3xrnv+LmdESCCrJ9C1AO3DqHNInEXe481BF94oqCzkFDQPfXzCx02CIT5A3Z1Bju9E0SuWzbaTXtd09wKLYUM0D9FSFHm9DK7yUn7xrBXq3ofLEBfsbTIkG7seyV9Wdk1yNR+RSZtMfu/+WNWP2uUmdEI4ilEb5joTgBgpce6ialdII/6bqc9DjngZnQvdaOgDJ2SbTeBBy33cIHwHm94V8yhwMZF3FoKfdS7IHYXfyggbRGZAqUpW5tI5RUjeGj+RoF8QUPHZ2BN1jNPsPf7bTDQWD0+qESnlRHTSmPKAIaH5eBb+14YcBGKd8IRt2x+GNAUXiEhpOuQxQXwT+2CWEP2CY+H4+bmmGco0bZWONXoM/d4MXcxzDkeYEo7qUpXPwRrwrdlMUKwhKykQxxdpKWfsUbWsk2G0EWkOl6P/gDTyOeR5TmVYbbSdm95vfrwnoZU118TMTWYu/MRuxQHj1x67x/F4tgXPLKvHdF6VZAmND4jewuDD5kQlm/ZppjSwOmLvn/r+GZvGRp6Dhn/U52fx6jfsdLnS7/OTdqfn77AvnT0ai70/EhfHfWn0gpXqxz21ygbl5/JY+bpgNbhEBoFYG6s7frvv+jTyMRXI/eewtOfF0fP1LhYH7JdNCju2nhZNsPZ7Hm3A9jcWO70+pmszfdr13K8/JsEo5pkXhnkdRBuv1OJ7y88jE9WoAen+6Rpk9Fzovu7NRW7rdhEV6anQ62mr3WoEj1HL7Bskugwq2m7sF6obgvZ0kmxr0Wm2yoVhqkW7f3NcDdhRrCVi6tx1xC2Q1CHJxw6j8shBdKyHORaP+4tpo3ccvGm1ru9Qc6AxJz+MuDKTzNRSJrKvjS+35JKU5K4hjEyDNQ8Eck9gHWKmily1LMrGhsmAM7NicaoEsE7oVIMQpa25mLtVi8ib4qMAfsOw6sMJo2jFalhEMAM1QfZUvaFQPFgykK2nghRJE3/C9xsjQLfWxok8FU2D/JeqYCBPYqYHurqHE0bnv16eWlBSR0O0S2Hie6+ArSCufxQzB0MTQnzniPZ07fK6i2PrxqijhjNnWPOP/0Ar83MpSQoxcj0TJjTQqGwbk3oEnYlEBu0iO5uTGB4/nzkGCL6L+3WiGoSKpp/fUoXlm7KHu9kPF/xMMgXQDDGYMi2wUgbQu9kdc0j/LdpqHd0hglShR7tnNZNDTQkqRyfvgAq7vm/4GWPQ64M84Av2WfuzqbpHy/vlvfH1IuN9c5Y9PWnL/XmtpBk8+mH9sZH7yi+P8+V4yvCYvX/nzVX7YqBo1X53PLYu6q3U3XnWaMbkTPU3HN2+tPH9m1lvvp0vjLzy4iSx/Tr4+35VPv7g13P2qn1RTH8Yr3MK1K8znmzlF316ImJbjkRlznTMdezaog1Of3coNjZUsqzDsh4yzy2bCKxqIlM2GnlHZeXvowbPLf6iAqUvZ8rWSku/401ld8woG4um0Wt72KRQXVlqGXrVt+y3RiKOaDTE9rjTVdGdlaMmVnh+F20Gpn9+in2vqE2+17VeAPfXZyYYvlhGj6gE2ll0TplUs8igXA8RQKhVEUJIuJ1oqP+XGz61ZZezmPiSQfOZ2PI1WRKgLMM3ZgcKFKRwDlQXmYGTHvC+3Aw/H4qT+xxr2RSynG9CtDJK4WRkACH5WHhK13AwOsJ+uYBAhtL0QBdCk6rXzgMPEKCmxqCiDK/AqCLCVB0RdEU5ycUGmZTQX44cXTxmVIRFqSdBedfFph+lHPn32CUZcAHSzi07/SouunRdZeQTB+HeI590AgrgugggHymKmab1U6bsRHMHUAdBAQAAAAAAIAABAAACIA7u7u7u7ucVd3d3d3d3fuYt3Fd8F3d3d3d3dMYFXRgFkAABAA3QLSFANhRbOi23TL0h1Icrcd20EddEPJwNac++yBD7o0sy4fM4P+RUFkWN7mHvZAHkqQ5ZJ37KE9kKCZ0e1kXi6cSZKToHRJQJMAIAAAAAAAACEA///A//w8bM5ZSrR+q4AlyPCedFCz5ncOKQLiubb5FPTBdRj0ecv39RBymcoQUyC//MJlwA7XI7KMg6le2Md7Od0eazj6Vkf48WNrzwY1pnP40R4cEaHy9i8NBvdIlPAKas5vp1pl1FHK8knuM5PkYGNaPc/fPLfc2SPhINR9HlOEd4tE6aZya4z47Pi44LKZd8hZmnvg5HQBqUvxe3tM9t3+zR0N1tU17rHw17bFt3uCJpIwp9CR4N9vO7v2ahfjPIi0s5bOh3np8eGJ7c6D/UeXlOFmSG/aQ6MogMmb8drPFnmfsmcznOfqpauv9WwGtF1F3He374o2+1igd14o8Wpo8LPkFdglRb5oyN97WuF7CdpbV522F+5U0W5lxfdpfoX2ECVtF/0+cNr8LI2cDpz9cvZrKcyWnDnnss6GuFgsofWQ/w1cZ5HnTltCB2gMismD33bn0rEnzI8dlwcNr056DHu2YKAqvyG4kAIEYhIGwAkRXEaLbQIh1vlGmQnyi4vudprk6dZtH+RYXD8WKQKm2pYCBllpjIQWaW9UJBEpYvFkgAiLjeBcLTzX73LtIhe5MOEjaWevx/vp4HnipHHj4McAxJJ/3QGZMWhDbM/J4y3fr+f7++3hke3OMM8H/+oL72stLZHar69LZZpltOuzvTaKppPV9uugKRcuuNPge7dd7uidaAHounoshMhPsu38FBR0sMWJGTJgkhyfsyeKtu6JilR5JmcQJIDjB6JEp9a1erDsyGp+lKJP98X+RLPh7OIw7WY4yMF6R0SIabWZ7MEkxobe8S5YcSbNiBkJcam/QOfr2q9Q6MkTa1NBgwT0n1v/22afbSKtqoxriPFs/Dy0EQGWe5aOXpSI+nSMjlGYOOmASmx196OF64YeI0gFNjtzJ3W4Yje6BQVLYltiPSOYWlxeKLNunHTPeR9gkld8ThZKYwk/H6GQezkRPZCHDc8LlMw0GG9vbSZvAFVXvHl67b6cVJl9nY4q0mT7FxI2KDxnm0wAPHEe1Q67/C6vhrmWhvAcU46ODoWqNWHHfL4or28IB+yFD5fCr7GlpzKZ09nvlKN8RceZYmO3NjwLs4cWz7L8O2/YvY4pig8n2gPBfQdv+dCv02cWW9P14nSUxu2QC3s0IWe2ZdISaSpSWTTh4lUc8oO7XK7f2RVC0j6Jv9OrlC6/NWhbALDodGrbcqPThVXXe4NZv+99Em+rL4xmgcvlxU4o67CjR1n7IZo3cp5frSGv/+5XX+0u3sMud51gwfh+pUURvWjs4Hay1q9Fd0yrPu3wTug9uOZ7Lu/2VYe/dHit23gLC+9nX5vUPn+SNiXr4EO3wUyduo4/iJ04EQkNnEyPtcAuVys0BwpSFbRXnt1PHX8XTd3ulkdppL1WMcfe9JBVDiQvDt2Q23Z9Ndw2NVXhzD74WmYwSzq8OjUa+mtrrs1hGbe1LRbYrd83I6sCH+7tM6z4L9yWYyJhGEk3+Alx6rIiTXK1jD1TY8wIOKmqDFhCYc0QsLNpkvzafEZHHYJ5g3zBddEj6Q22xLwRGawrkkZQFt+oQmWmLri+BMSwj1GSobJgnhXewpYeOS3zJA9I3KlZrCoSOyauZu1BF2evUiN9vfWgtKOIIpwqSC+COT8+k5Jf8rpG+CHqPX3itL2wbRkoXBUXcLvZ/KX1Qt4=
*/