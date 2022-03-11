// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUINTIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUINTIC_B_SPLINE_HPP
#include <memory>
#include <limits>
#include <boost/math/interpolators/detail/cardinal_quintic_b_spline_detail.hpp>


namespace boost{ namespace math{ namespace interpolators {

template <class Real>
class cardinal_quintic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n - 1] = y(b), step_size = (b - a)/(n -1).
    cardinal_quintic_b_spline(const Real* const y,
                                size_t n,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                std::pair<Real, Real> left_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()},
                                std::pair<Real, Real> right_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()})
     : impl_(std::make_shared<detail::cardinal_quintic_b_spline_detail<Real>>(y, n, t0, h, left_endpoint_derivatives, right_endpoint_derivatives))
    {}

    // Oh the bizarre error messages if we template this on a RandomAccessContainer:
    cardinal_quintic_b_spline(std::vector<Real> const & y,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                std::pair<Real, Real> left_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()},
                                std::pair<Real, Real> right_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()})
     : impl_(std::make_shared<detail::cardinal_quintic_b_spline_detail<Real>>(y.data(), y.size(), t0, h, left_endpoint_derivatives, right_endpoint_derivatives))
    {}


    Real operator()(Real t) const {
        return impl_->operator()(t);
    }

    Real prime(Real t) const {
       return impl_->prime(t);
    }

    Real double_prime(Real t) const {
        return impl_->double_prime(t);
    }

    Real t_max() const {
        return impl_->t_max();
    }

private:
    std::shared_ptr<detail::cardinal_quintic_b_spline_detail<Real>> impl_;
};

}}}
#endif

/* cardinal_quintic_b_spline.hpp
+AbpWulm5KlznVH6PKwQch/rZ/XqmKSj0Fy7r7NQGGlt0V2RKilVRZsEssjPEc9snscOdzNIIj+tcskJLzHEAaIpjoAR0c6vIhMQCg5plv0s9DXQLYpSTljZASkvP9FxL2UxJ4fct2qT9f428Jdgk/JP4aYNlue9dVs3GXo5yLhzCTZrMKS00c1r659ttO21WZpQJrd+WZGg+nii8BrqIzPlHK63rLqzUrMIxJU+7XS+w0S+xsIt93bWVQCdWSxrnIT+cXvgwCfSHQp1O84F9MHlerG08eR6Rpno8oNrym/zj2ihb+jgECJ75Jvv7EvC2VU49/fWU/C967jXoPjcWfPpDh4KjvRhgdR52HtrKhLdWf3Yj+C09aVrDom19ls85eP152Of2hxTodrkt+zImqUmttTm6NJa9CJ18Ngaw/EB8Nd8eLbYKvTn9VvWuV09fO7lvlv67D2rEX23Wt0aFvph1iqZaQzbMLS1JxKnQwAAwAeQEYp++x39ue372AdWyo/dHe8vLVY+9o7aHMxXvO76DuD4xlolrJcdets9zietgNgV24zsXRJ6KNf9fU7i+XxvR8cu2EXxUbHta2Fvzse2/bTWcm5yJJsRXYl7Gj/fM32Cr+qTHfJLD/y7N+6tfg87sWKN549JyFzOHhqHFWCrsjzUsvGjLOh0tirlUQkvzihMdKW5h5K1dQUHS9mr2I3VVU3TuUcEJPIk3CTecFD38JyEMk4pevA4ombStJHCSVNwEghTpHwFRuGiH4jNsrXsfquVVbhcAQHlSu3VfX4XeqxMIkbdtWU4Rx4Io46Id3F52wWFkaVc72f8La9IFNvrMEbMXZMhwTLKZEamDeQiIqQaBMhBOBNtzI4OlHEFrb4GwtyIlE7If25fnrE2wWH0PSS9YB8wtfsWrxV/VnnRBWhPQ4ZvUCWNtxOSZp8qYMtprpvs8D1HRVAx78p8zzlnB9ETaMNI70Y56KaTEL+NuzAS1dbqVBS4mS1EbU38SfqIxmbAPxf/ZmSTRq1xnXY8Tdog8Gl0+53TwRSifMPSb5DH9Ga6jpEN5EnijNX3Lb2w7FCyV2qgezmWBrFYil8BaCGZAcpKu5BzHmeWzeZdX8/YOHW1yKWfYVWxPXPPtYjuGe0DsPbut/OnW5kudKChmPbIcnpjpYu3qdSVtGpL5mWy8faDyb09erh2XNTXt1vHrvfIsNnpAXp7Le32eg4K8Jf4t7jqKnVR1EPG6VUG6ulLLve5O4oW3Zqlz+mKV5HgqVvIJHP5/rw78thzi+kAsALF1rUOYuM3HYJ19lvWxdp4jozVAO52/RCiEt9sGO3rBR1KQfC28H5L99aQ3MnroU+j2Tik3PXhZY/+GNX4FMvntFT/xczlPjb1fdcza5OnBQcY3L4+9anCKatBa4zTiiTbkxm2d2ZMje1irLC2BA7tC6e/dd0uB26QmKklHT+PTZUwPafrzEtuTn/WA3zNJg8IfS+7/W6HQxwOCp1QRlAgfrFbm8+bbA0DZgoSGkqNotJ1wEMwuM/2mED4Tkx66W18uCxDTq1TBXd+UX8u3UA6VG5SkSA4VNjelD+B/Cqc0lnZEu7xk8bAAmhcc3Qs3Kcti5BCzFjWmGy5LydeCa8/naVmdXSnoKNiva6q4ALKZUdmS6H5WmiKgrBeHVS6v6vhpC2TT7ZmF1fyUrMDLQQYxgFp0DUCod3fGfCbFL6KZr0NXrSNa/0iuj0ALoA4EpBmlhvs+AFD68I1f6Gq1nR+rpysoBW8AMEZorD6X62v5b8acVuMZzDm2zrnrtuMQyKIUZ4H3jPQsQG+D7hKKp6Zzwd65+uI++pU6YzjQp9DOlOKTLfPhigWmoBMJ0zTEJ+ah8d0yUWkK3/RUE2qELPcJuUyjqW/7ShyxtkiQJopY1TNqGVFQQXBU4nTt4G0KQnwQjzoEiCZfmcfx2zprZOeZkAWojelRX5erC7nD5ZTRvNaN0i3+Ehk1ORo9zclO9Ota5f8oSNkq4Tc4bfYZtmTMyRne+Y5VZD964EKvQPxwVzMrl9zdza/TEXQ1lpeBjfRG3dQxtxbMRGlPIA39jbAq8IG+2Y4NiRQ8kMs4Hb5cwZFtzuIGLU7pkCR8nDQFxs9ApXps2AhLhXSeITaeCzt4fdpxXXl1ajNv/RSfFCp2fGMfPvxJOK1Ooy26R1mqi/Hr/atmuin969LPcTp+On+tO/iTX1sC9p8UPjctyx8WU0E05FsToizo+Qd2LHvVBeds97NbT1v8HjgKvXY99eArrJn1Rwi1PNbQKywhdew4bD1/TnH5ilC7dEku9vpGoq497SuPQPScMxgqlQxn7VhS59HFvfyRsHW97eh13Ax9oHZzokfuB11ct8XDlwvb7lDf6ZH298EbxRa1dq7YSzNzrbZOyNIVgVqsjCIiGFuZ1Mlf+uTt8nlTOb5Xx6sAM5qiTlRcqfOY/HSw2qTgURGksAmSrQLphb+53Y/b/BXTzWjX0eWZVd15Ppq21JAdwllLYVFdGUP0HNaTDHoo9nGMCpbL5+Ta3je/qgRrwD5EYH9Md3OQEHQJeOpPtbQmqZpN4iO4oJjgnk11+uU6zHrlbkxMg5dNi++n559Q+uFqE2YxmKWnIGaQBnm9YNsaJU6eYt7ZhbryGOGESJRKBgofXLTdxkJn1s7mBQ2Zmw8ikrXDpEOKoMrxCywtYzbqWRFLsUrP/bXu+TCQiozJrh+vMmhzj6dJk9GLhzByZ/740kFd9AlxACZO4VevjtWlkqW+4vn2gL2joQSq+bGpqvq+CVsrZFortSZ3Un3yr8MCigWuAGFLy7l23uxS+r48aG3LgX3clqf7tR4WkiwvSO2I4X9sB5J2XdbN3o32I1e8ta4yMW69u4e7JkOX+Abei4w9grPiETEjM+wnfKZROXZr3DUZ6ESAcg+8heYffIkU/HyPnch/cyv2n23TE+/tWAZkDskkS63HTy298vScwF8XfRJrhdk/0Qt8T7XxHA1JtrQ8uXP8U6cy23Vvz4yQ1fT7JTJ2LSGQ60A6x8bn1Sb67NDRmab96VDyJLjdl0XIK4eIwUaxB5OdMbOA6gGYccyxCDD+akCWyq/3RAWxUA3rmfDpA07Ri9DpiL9XRaDKhCS4mpepygH7PUJyMh2dmUxEAP4jniqV6YwSmpSP0TzG/XnyS0IyJiJqizSWrUGfx8iiAwhEt1GKdgU/RAesoxmX/5pcw42MgLq6wi9b7ASLjnL8/y8OVIoxUj5nsgbMoBEFLPnhQagfVDOJ9pdLiIFPA9gO3LllhoVGSGZD/YqKaTzqsBqya3GYERVK11/fcQ+QOy+RcYlEzoZ1jncFXPW4kcbA3TCYJ1tD/nl5WeuvF1CSeAU74/+XjroaoQmGx6hGZucdrR1R1FXpSKH+itdJw57pTxa8cB9+KFZ6k0qhCo6T1I9Z4TToFIObpNXjcV3Uj/TXY7UGC83J5NBbbRvUaVzKPXkb1StU2oK1G5LZrw2M4NSvv199O3T2vMuBJKegDDuG/mvLi+fCM2OSwjpVLxwT1NPeQtPEqMvbqsrfY5e8Ua+CB4+2AdaURSXMTzcIaarBtBC4lQjB6iv2fwTm/kk5DGIOcmpsnyMqXfdRkeTm9GrkQtICE7QvqQihZvxrUrWw+Cj9+acKPLuenEFvlPj0q8tSwXlntbLaVhOOsycrU1fzHbfRAf8nq4u+bOYmu5LsMPKb+dZGLITze20UnkqAdpLjOcPMpt57/4tn+VA4giZ97d/y7RpWVLAyDcd+bev3O3FbCsAVgyB48e09TqXG4hXLYGT+VmkdUgqeB8t6HV84qzee/Qx+G9z8c4x/8KB6rl+oyntLJZEOvCkx9q4EQp47WHVeevgXYPimCdUB/bfCGlOIrCorjVPtnP3qcV9WGkZwkkmM19cZUzSitoSeudua0biId0y+cIRIOM7IkpUmgHsOkhDzUdCTeEm/fpwU6UsUc4S+4tzObBV5PsZa9oF1lYAnlqG4xOqGXgBgo44J/It+MAl07ldw10WTu/5j+KmB5mAKEeQsLJP5yJCOhAoWXahbdsK11XfQhCbREdXYlsfzM2krUW0OF4ULW4zWi24hqoWyHVmSFNgodAdLqKToa6o/kpocuST1pFN2iQSXKPCcEDkHykGZX1/3lzZy59GPq/baVWrft/6azWlIHRDpH/o+cnEOoWNwC9LkJwLjNLkB9PjyoWSluGkZiYm6r28WG0w6fSUv/DHeqsQWeKckVhjjJFsYMn3qfGhlRJDZvFD1gpTB8VwP05J8gbbhaZuWiGe7g0BqTjEVmoBDvj/6BxbPTDgZXq60d0AeBDRtBJ53+udbJI49Damwan5Q8gpwOlm9+j/9jz6E03tk+nG7sEz/6n+BMptWOJW7X8gaKQM1QAT8rT+9lCJX9+S+HL3jozmpWI5jZ59vMdUIHf27UikRz4su+qrR8govR2etZNSNhcdxBwVnA7ZvXZ9tvvtX8CvHlvzRLsH2QWpf4OEyCz4KhqD3MHoeWj6sebiaEWT3mr+J2rYsdAmINWUitYfyJGKuL0y8OAun3icBG4mpPavaKR9pBoWkgYHTcTEEYE0JFQiGE0xWaKjW8pBoHunQXRAKFL2sNIY6Y6BQDuj0/EJoChFZfXyPkMTFvUKkQVPPtiDD4+hVN/aoOnPivCv3d6k+BKS/HXlfTpWPsx09Xzsj9x/ii3Nd77wi+gBciJPGbVw/E6JZ1PzNoEJqWBbQQPFghmHUU4vlEAGYK+mH5+MtJe6822PhQa2BRt4bKpwz1kjfYsM66vWH7tvkVFRC8NF03HV4AUd5gCWmcej17qOHA8IT0ezsXEU/AtADoF3nFxziLHmkjB3BqYNNUozEWG6og1B1GgRJygJ0NMM9x1EfePMVlnI84NhEAyBUwMnJ+idU2UThn+hcH7/Ij4V0aUSYd9buQlkjb/IFPLIL2q84+/UIJ3LVUPm8wmwOQTJ3po5iLSFm0Ss6eK3htR99CTBlTJzqjj3eJkP/fYsDlpk8o8WqJn5e9zi6X8AGM2he+1lx6jDctmhYvOQ398HXWnybi2W8WbPb3/NFNe/GcMetp283/r6/xJaBpzf6+W615Olvwsv2mT7HeuWf+9HH3TroDPcjt+BfttYulszl2Wp1TgocXa2Q/egzr5YG0yg39c0ygRfIsVWkMdG0ZW3wZSR7fWW1wvWN8Ld43JdVwfwg/giFbV3dXF9qua7+Z5642FY8HyS2yHoKF5VTJdSWykWSoPShQR0Usb8o0bNimMEVJD004Wpw9MKfPnvmlx+ujdxUMPI8B8GZJTQ74KYsg2I0BdI2SseR0LNrSPXDsImrTViB6hBDML7r736dwLnlTrktEpSDfPDz/MmQmJv8KUjza0IV+28mnZH5lPkyrZ1qh4YvPydaOu2HEk0rRlxH89YE75kQRxvC4Vcg0Ro0I9AjHn9AAUUx2hGaIeEZHnCzuSogGzXlrzlyYReMt8rPSv0sJ6iO6O+D8A8sr5NB9GIpUQFY6ueNgPqi3NrWFVVoDXhjoQSLGOJuP746m+H8mMGYXtO7YgBGmZ+evtCDB3PucIBFXq/6SArSeR1BrJZSuQJ4rtEgAp5rFCq8H1UvwdrPy7+22hKwa9glSpxWxkNiNMEb2Gi1Ve4NO2/v05Gr5GL7wqS5VHg0Do9/uB2J3bEDMz4p6g7xK7LQIhm8t+mEC88lvhPzWhptvDNZjwag+Ts+9j7hJMROh5aeo905gp5W4A9+0j72Dxse38fNcjnaWaU3qBcqw7i7aDqbHsenw5jQS4NiNfcaJfaWsjY4/UgYbtfTdPyaS0kBtntWIq0aPHrXMFvsa9dTDLLzVUnqY1gm/zR/f3fVgMEXb+N0eF+vWWqCBd1mE3PXM9bCI74qo+NQP2MzoRKJrvhGN6RrnqIPgW8DSVli6uuoPxEfGgHVtn1k+QduKhq2gwiKIe/JwQid4wUmQ7dmj5HSavBdFMX6RsQRPJI8wzFhAOFSyb1EKpefv96IMPw3ZGyDDkWNgFWkAxBQmCPRZhTgneC9NLtu+f3Fm2ghJLHV3E5X5XUMSv8L1tTQqD+SAt8Usy+BKSNwKaik++PYD0tLDesLbLNp8NQBGXGkn1NB8TyjgS9yejQKgqKUMFCGdDz+ZDdLpMxQ2TOVRJiNqOoGqXNqAqOY1zVPra0GIueNX0auVrCN43iS85wujqNIxhyaH1UFDCiITkoFQczCymv0rNOWtmvAMT0cvjMzAk/Evp155u3dYwH55mdzav7l+gyyUzGbdDG+IS36oL7PAx1Win0Rs7bEVesaWTJTyMvk+xR0WaWu0xzRsLlKHH9ypmW6PN00NNciMohFjKb/MtJxL6K9e6fdJsf1SuaZUl0dj0kX6ypfa0djKG+c29NU0qCid+ymlz0C5/k+5JrxeXtLWVa9ebtBvEtuZgjnTqoB+l/FlbKVhziOZMqIocPwFuP2wOP+acH4x1diW/NGE2G5cfVPfXOhj7sjmsqKE5d38sbqNHH9/jwdcQ6VwOEs1+jEqv74sfjrz09f7ecW5N3fvPALRVk7yWJYpvq0f7nUn/e42t9hB46fKVuUuslM2vPVUu+/zwK+BwS1C2YuHoOfn33dhKYpTIr2tnJU1UIhb+cHvWgk+Il5VLYQpcvNP/T+ngZJ8hHW+g7AvnPAQVx7ll+79ke73nVIko8N5G1DmEipcvPRbRDLP5eYwsEuyLF8eQyw31k48o8YhiBM+kGTWMn9pUlI6FNPb78urLIYeSYmS894UgH9NTNkN/+werg5ktRsJB/ySwtz88FA6OgvxeN7hE5pRpea6DbCVNgvqI1+ilara+8ohgLvG9W8VQfbsIjUosO2fOdqRHH1CdMtDdGuOLWMsiIs/BuXboPlT1UlE5AcT4Do8L5qvSJ4bMunPxq1Wr/jYKk9EPAkxtKEpsFU873uhdvGbtmt8JYAT86OhBHhlkZaGdC63U4QvqyOg1dF3zqOCLRn8SkHX728pQq3eGrImFTjq955gbrNdrjk75uf9My6TWHE+GGhDLl1vTd3pKuTMFSnDvh6bFaZaMdwBMDeNlxUzPN169h93KH5eUtcaHE6WB52fOyoEcc14Fx5JDfFgP5m6vi/kjE8Plj72/XqLts6LSv5yjo77Rdufnr4ORwVeD34dUl3cJx/xPziuU6CY/4LMvrursx/9+JFmrrtGHW2G/vPSeSBWPfzkaXz+7rwbXU3+v7wG7Ao7l//idTMdx33+YzO3gcV9ou38spXiFzYsJl80HcDhX/bXdeU58d1blrmu9WTGl6SxHTFTKG1CUBOUcJSpxTNidfaO2gO8SeqS7ptaGtnut5nclPwG3CjiWCh7JHool1xKhmwqA7OZSwYbHOAGHKz/DfYMZdZ8E1Th7hIQEFayxwOLBNB9LeaiM95/ugZ1xgS3BG9x33hTJfT0HLQvkdvoIVUUWIDgogIFANpQHrMJBWSgoalq9Zb5XN8o39MEET3/PXYwMwBEpaQHbIEEzJyCxv39DsS9IjrS0LXgiYrBGTS5edJ3InrUA2EAhnvVdf9w7VH8HEi4P73VBTBMXn8d3O/Id0ShIRG8TyVl06R1VZCNiywR/hUlsASEXTj8REb+D3tOl2YcYTCFehExBVksQXg3SpcAWyI+HLckh+3/+PIpfi11Avg/qmDl77yqzPiEThuKBoEnfqhKX+goyaRUYWE3OeL09L0mfmrh55O1MWG736LgzbOO9uemCEvpUQxaLfqcgvgt9ui/eEu7uHDS1g/YbKQrIrf+1cJ2p8nUWeR2uOlQ6NuxD2XQ9u8UB+TP0O7nZPOz8xKO3d6+LjN45rY9dN3yDhS62+bU8R5lpgu8LH1qD5gLHeq6m+iKyHzeJPV08ifliyh44vY9M73Xc6CrwPfL0WxYarcblmbebHbl8Yvw6C+o2n5c7LPmU50rt3bg24jouuArJuX5AmfYi3cffL07flzrvaa9EvHlv3ZlAegj7jvRjHb47RPg4rjS0B+98UGuvVi3kfsIP+rY0o7LjCfk/vHFyXWIPHHsGVdP78v2WqjFLUKZnU5DTGc+29HIb3tjkdwzoM8cbiCHNKQ1trEk29TPR+TqTPnTHgh4HzaXCOKFbRe0WgjEC7Av+eAo4UzzsC6cRPsPOEtWpHYmwD6LsWCzfHROikhURGXnlizNBg/g4rCZmpOBhMfehEeRK4Cv/RKqCniHI5ulk64T6bFC7EWyiiP/avH8vEgXvDS5TeDWhThCVLaKWUJOdY8DLkdomeLYBV7UVLMP0RgorPyt4VBc8pMdeqkUzPJMNH8ARxFJ1Znz2Ce/qzidY7T31wGlbwq8k3q+zTj3l0ql2rJxkX7k/S3e7DQKGGUgo+WUAUywCD+mYExcyWGTHJvhCmN0KYorIxOqz3TdtT/Vnm6nlNGJxL1W9gGRkCsvWPjpz6Wpj9u+3g/OxwaaK6W/iUAz+PrShWHqFZPpoUO89/ZL4bfc57bmod/ta7H2L82pV19j7wX70O4LMJ/wxrLfnXsPrY6vgk1/d17orlgP+JdFD54g96DF32lf6PB7r59Vih3Pq7ya9vD5u4QlxwfhX6RDQthfY2vaOic8Nbe82i3Mt4elz6q3Tuinvk//46j5u7bj5argfL0D123oFWU4r+Ef6TD0VYf7yq6NLD/uNuMvcRXYy+w7G/z5ZPlNHpus3rclyI5s97c8nl0zkH/HlNDol6ui+joExBq2AIOmwbbh5V+FLcqX52ier/JWCxfHbAj/J4AVbShdOAcEjpi35hx7KltW1f5RKZ1ifG0hwDMrpcKTxOctQIRVQAavgzCGXj5hulaZa8pLBhBqFhzimXg/woISnfmTFcwipDqZiWQwxjntKHKTHsFTTz9oCCtvMiYekAe1DyO7VX54QZUz2GW3myWFsCCMfwkSrUw7lVeFNIkX+QLFVx7mkkq9Fwh2vdlJgMkJQBnSMv61OF4X5DJzYdRZc2sTzDl7oj3scA0/6cQJJQtTPue+ciDiPRBrusJ4ZmCpn5L6EAEDgXyEdNmnlfjrKy1GMQU15jJfz9o6dX6ATFb3wCdYCIf+rhAeX5OBA+sPVt+0SSi+SLlHPc8btoejnjZhV86bpHsjV9/+892Kf6srvOfC3i6I80KcXBbXhEdTEsYkCSJzFn89M=
*/