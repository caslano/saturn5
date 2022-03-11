//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_RANDOM_SHUFFLE_HPP
#define BOOST_COMPUTE_ALGORITHM_RANDOM_SHUFFLE_HPP

#include <vector>
#include <algorithm>

#ifdef BOOST_COMPUTE_USE_CPP11
#include <random>
#endif

#include <boost/static_assert.hpp>
#include <boost/range/algorithm_ext/iota.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/scatter.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Randomly shuffles the elements in the range [\p first, \p last).
///
/// Space complexity: \Omega(2n)
///
/// \see scatter()
template<class Iterator>
inline void random_shuffle(Iterator first,
                           Iterator last,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    // generate shuffled indices on the host
    std::vector<cl_uint> random_indices(count);
    boost::iota(random_indices, 0);
#ifdef BOOST_COMPUTE_USE_CPP11
    std::random_device nondeterministic_randomness;
    std::default_random_engine random_engine(nondeterministic_randomness());
    std::shuffle(random_indices.begin(), random_indices.end(), random_engine);
#else
    std::random_shuffle(random_indices.begin(), random_indices.end());
#endif

    // copy random indices to the device
    const context &context = queue.get_context();
    vector<cl_uint> indices(count, context);
    ::boost::compute::copy(random_indices.begin(),
                           random_indices.end(),
                           indices.begin(),
                           queue);

    // make a copy of the values on the device
    vector<value_type> tmp(count, context);
    ::boost::compute::copy(first,
                           last,
                           tmp.begin(),
                           queue);

    // write values to their new locations
    ::boost::compute::scatter(tmp.begin(),
                              tmp.end(),
                              indices.begin(),
                              first,
                              queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_RANDOM_SHUFFLE_HPP

/* random_shuffle.hpp
T27GVkkkzq19+W5FEgL0yn2mIXLo4LHpaRtnMDTAUKKZMPKeBTrFIPqsrfTnNYDM3tSMrYu0F63LF9gFEeJR+nvgogk46K8ZvnihGHqgJ9M9Qzi9fynHvYgvKLvE7WjL2ppCHF5qgWMCvhiyy2ejeukzGLvwVn1hdZXRqr1DOjpahe6KLQ/Kk+grv7MuWVCWujMZtfg8NOX5Uirb02bcR6Qd2WKTzlMqndwWj1CHdxaCFVR6htQxYHvQFkEMG6OH0CTdmtIE4D/gRif5cnpLGFcaMn29kpsWsXA+OKupUAe09302H4h9xbMY7C90416pcqFOYRspeHJdpMiujiFL07MHsnerS51hvXpyOXbYdMFTbM4Bp7mXKq2ZkGF8Hhv3uJXTePr+NJ6+j4HVByfwjHGu/kl2rt61HTsg6EYypQkl6BsU09nv6fr0RkMfpZmYb5AHI6uZE+2QHTnLQMFBuus3Vr64BJwyLDYtkTRdhIGVt644Z1cIGFhx87CBfakXDGyC2XcqQt1ZDoUthE/i0w70jKLgBjXDshtiTCqj9wOTFZoLuFMT9HXp+jq+jP4JrEVFgBY8ZvBU6MS5HLxBEwYdxqQOlEioC3PsloIH5eIy+sAeU1Vzyugv95h9Zha46z/bc26nefMe1mlWGL3mSlNuDfnOrAfzHpQTa5e6uUyOq61Ox+k9eQKWh5fG/AGnFOTElkJ2FQh0BoXOIWGbDRcVx2gT2SRij0eJepIMpWGiG703zF2ufKSzGxV+WUY/2j1k3qjgaznnQoWO2FnjQoXnzrlQ4SJA+9/dpyCdR996abg60r4B69JiDFCCvO9T6YTh0/B10fu+3GKXP7d8mcF38LqTBF8hLyexPrstH6phjNlbJ81JlxIBoL1ej12zXugc7plRK7AFPRNyr25HI6O8xO71Ed3Ck+CZgXZcMsIOGmIwuNrlqOEnHjTvdjHNVQebk1bFoz80GOteYle1uKlXMSzGP7kEC3dyjhrLFHiEbeDXrXWThKJyNYJrX9LNRVJBkTSrSLqoSCosKpLGFwnhzbjgGd6oG0drtdyWBHaG+tFh8DgETzPCYzE80Qjj9aR4MHmjedlpcaQ6vVx/E19p+p+te7cWkwJeGfBI0Pgmgv4PTAY/YFV0SANXNtpd6FGOfN4d3Kq0OVR/tDyyFO0boxAJI8PG7VxbtjJDbtwL9ibCqfctAF2HJzbTrJu6Usqo4/cnmcHh9Wvo/f/BLrAxpsDflX548xZedDXYHRwYuWCLwYyLprTpOEDY8ri8ZBj0IbvbjK/4OF7B7qu7/yqM6krN3zPeU2zQQbTfMrSBETSc+caRXj7+tA1fslW2Ha/y6jzi3e/texuv8MoV0+S5uaUe+f5O2rHPuFdPwFuCjTsc3GNsJl8XAPCntu12a9u2bdu2bdve2m63brdut7Zt2+3b/zvJL7lzkrmZZC7OmQ/3MWNIgGNrnJXgTZfoQx3+muaKB38E7UzHPysnfsyXeEyZgXPwG2iP/9SkzVlQiHOo+IWk1J0XXtBe3/DDUAxuQS0v0D1S1RX/muqRgQtYsHfQRxh6DppQusW03a9NJ2o00G7WWAJK3soVvw5wAD1n5cC4RBXktEamv7JaJNsqMQYcNGzwgc5TeyLS6KFrwmWJv+rNdryBpdir/XiN1IpGmp4wtUZ88QvWn5pSSsHQQAV0C1H9nVOOcMHq7dEjM6tM5zFfaShwram1vHYi3QNBeF0HPwyeSh/LwYYHzO9OWU5nNF7lsedOavRrvNGDV8+2vjKaOnq0O7GyKJvdnuyeSWDALoqmkbfGh21xFtKMRcmu6tOGamRx5wmnYZ9vGW68Ng8MiXIDJ+ssVs3kepx/puhtfQDKzJ3KjaLzAST/8RphG/lqUWd82IGe/D4mPHmNt/jwdGYh6vQd83SNPvHKtzY7Jd4LnYh4lcDzmZ7jRtNE8k/6AddUQKeQk3OV15LMBO3lLB1AnQenQeNhZfSTzcV8qtqRssPW1ih6JTS2PSLlqdw4sve8x7eyN/plvR8S7wSKk4pOBjB159tQeQDpkLJ5FpvnI1pxtkei3R99qmA2l5UbZfrsqlaSxeQVGktgEPGiAc3TNBSM9EphGVo+GebAJhwOG2rwd9VmXFRzEejX5W7fU7IuRA9obYH1Lh3t5dk3DtSTSBr/snSXyfVDfB952Mt+n0XURqFXpM9NH0bHSpHKI4dKu/E+kE5prK9h/AuEX1L38nJPIrl6xVwyxfR6/sVhyp/7sPc9EzamLhYljsrG8epx5HXZOIGN1U7YhiA2gZ7dW6HN4JXCr3urSpLJoqpTmKKsNCpvb+iGgK3PVe8aqw6qJPZZ9ubhU+5g15l+ttaDvyei2dCLrEPVlaxsdVfcQKysJtrnN2fRC1Wj4qLPvsBFIGq8GFwRK3Ga6iVCsrELCJKTIcBiR9mH0ajrYYef/gIbRJ3PN40eUF48MfTbBywvaPivIOwblXoVj/tk79jIzBz4JYTf5A/Gd7AGM/0rg4suPPM7BvVrqt0cMa/09e0Yqx9GqNnhDvsrwxL0rxZvesFj9oAkYGMnUDU80DgEH0tHrcWGhs/evxXsHcCLKZGPfceD22vbnoI4KzwGFCXJxWZAHKQrVTlT6cqR/giUvCVqHIsNWo1OXMpuQCK5Ji7+bXPPV/is75/bfwum3r4LBScZ4c6qv9uwFjS/9dnLnb+ysRc4/xXofW1vFhwxB3u9coKzfvc2CObe74OzXvfaKVzr8NooGKq8027xUsoX3+c1m7XkXRqeO3t8a3jaJejz5+lx4KoP7LGsrqfhPCzII+XFTE4/3p8nn8yg2DSeM0w5DoalzM8vtSV2exSaRj07CDr//TeqpO0PwXm5uU3fmcosea7DGnuYVVTKWOZ38QH8QRJOP1rHGcRfewQq512zOkxrx1HXr8bv5ui792v7lJU8pqVDrK09tYKKFssLwMmJ201PZAJDak1nrYupYZB9Ftbt0NZW888de1zjNkQ17jK/kYmtcTbcfHO7kOCmbBmG4WJyGo1XIY865g6X0CgLGU8JvLQmHmk2tgqu0j/hAaSVpef75kXDee/fqBdOjJetDUoBVVmVHzsOahmY1MmYeLgLK4cAl0SREzYM3oDQiNPZiIAp6tSIN97vRmYfjT1fv+ksNcBWVGDzkUhcz9v5rujMCzIFfIQpJSwDNg+c8Rk5Xc3xvSrj5nLXESaFmLZxFhFazi1uprQJ8T0Q5mI17NdoGN+HlaB2Zps82nmhSehh5YtHMXRHhbjKK+Xid9jZ9u83fbVP+vIvc9VvtcVvkVp+ab54uZfHm5i+NXmHVsK8dMBk90JRWs+awfREyoanJHJ+Og3nvZLpCLAstSdvWX+PAGfuL56cwORnTaTPHsc8iVlx1rLXRyiDf3YzfKRfNEkiKvsPAzrZF9DtVM1shuIqhatzJpjnZY3vLWy/DVerbOFWqbUGxes7l/XU1Hj/9nc+wSqoHNIKuGxS85OEL4v0pqXTyk5kU8pmrpN0Z6sT8niRIk6gVCXT9/JOk/H4EOG7S88s4AhRauX259zMSLFZusPTFsLXweatm1woE5bUDd8WkJhU5+and576lJzFSlonu97GTmQJ2LKG09mF/p22rXy7IDipDnvomy/qUwbh9gC3TEyg6qXRryY98SMuWSgrATnsZRqnRDelbj0rf7oylU0goZf0eMEnRHYa1u8fe8AJU/muKk1AEZa89cf7q72YwcMsmIdPJp+TAnvruLHw+yX/rzXL/pCwR65ZFzZ+5UfQEYMHh++rqudHxyW7BQYOyfKno13yU6BS6phkNGxlIo7LqMIaVPM24XtKJe3OIU+tV0gHPA9vag+Nuo9xbllp5XbLLCPJ0zaok+IQe/3gX+HNgELVkCRqOwU5cpjd+JukMryE9jbZbFDS6a4mWs2VWRxNJ1Xvy1MB7BFbKaaor/Yjr04OON0e85aULp3dBkI9wfHfPbEY+2bY3zgJ07Ksy85zFRF/mAsm7OsndqlHihCeqt17G+dztd9UUrt7B4jsJml9Bd04Bh825tJNxVszGBHukfE7Ef9kt6kOeEuZC91c/srZitsujap7ww7lgsbWTV3bvn1K85d9BsAaOUnPH4DaNyuhuR+l9VAt+EaogwSB1Q50furHqnafKRi1UfBGVvbCU/LAzLqLbSbCAAIs/dNmOyZ71BpPYjoxKbXg6chufsuR/MlNuRqSvhU0ONGpNEqvryHMfPA67LYvcub23X7QuMTISLvki/jDW/nxp76mZu6ZXXCsed9JOrogByIQoecbsM2HjC9WZjsCsYwjzVgh0Y22Elu2dosCkdojfLfw+rmHf/F9ANXuVHUxluo+Tlmt4L2vv8qg2+Sz+/EFnLebk965RBk/8ThurOIZT9VWeTf1IrdEkxel4toc4QFCJvFBqdQxhKQqnQ93XdfD2TjTooymH4d6U/kCHPgtrY/eGguSrqsJJnWrRUxJEPOvMVj84OHx9/oDOLbGksgSglScFK8ikn4rtXuvwfLnNJXqtFP2lqrWRcdLytV20Frb6e1aBi90TNh6ZR2pqq6hrzBbIneEh8N2ZTAjVyqu00PJw3BPFrajXv6cBo6xNq1JCl3xSjOG/wc4atAzLWHDF7yhdp2xfb7HTBg1pfYt1VklvNJaw/VVrcb0gu/2Tio+hHG+7Ka4Mnb6XlSph8JWOrV9qk5q1HeBaude/6Ox5Gn/2vRN1J81Zp3Y2GRzStVwF6yPJ2GFvnhXTmHNR8Zn+AnutgcUTqTirzEfW5kSOr/ftx0vjFmpwuuu+2IfrPPdivY4iH64VIoev8Af/6w4wFgZ68T2QIFLZNUlRYQrfcQXySGrFJrt6KG5q1Z+da+hli855N+IqGgujqPphlDqZihotiQrD/FKLVbh/uQKW2R/FSZ6k0cni13UY7yaqbUHyVd4zlDtCYwh6AVqbluBMnyTpAMA3JZzYeu/unyLK/lEfYqV0KgWRWc8+Qtr26oOodq07nMg1LLYy3173HLMW1mmlEH8/cN6+V46hfCPNQH+033bwjfHGuxTzIDp7YmjWKtxRstie5TWSHxD7YpjW9S3B0yXdawC08RXr9WHJ6mSM7BaHTi+9V+t+2ap6LcFtycrTccXjzN19ThLyFkwF8ys5B9me+TulS/jN36vWgnKmPxt6EuhDjD3ltTOn/QqlfAOuGFaTUq5mY9gT+NpwOG0Ze19Q2xdZTtxKvqdiMMlCA6yAPCXP+IFw8tU5Jjvt+/GN3n08fqTm2yzRaka3ta/wwuCNxGkboJS1LyxFX434hzTmNfia0B5GAf0sfjkd3VgbBGDTc0MAj7TQa2fvLydAwdKdOuz4kS2mHBfYUWCMqO2I59X7dZFufxnj25BwicZs/DnXyKadqbK+ZVGOnv9rjVsAMWRWqVv3iEIXDQ4K/6YNh4lWm+pVP6Far6lb/lM/zRfbnz/urFEQJtyyO/SWkPnRaDkd4RexOW6Uogjh3Zwz9y1tON9lUnIPPY+t84KvLAaQ8U0u9ttwZLh0Bg0UfWET8yuG8rEF7l/A+Kex/jsT9W5V1a+mNku6DeFpHqz/CzetkarG/62FuKJnXOQUPSaozvUFXyg2+YZAoWHhBMQNAQIn/PugI2ppMZXOsn79NquQNKdYVSYgsb/RrpgjN1Rv1XPRNqgjtdfyLfH7C/e8M5tZGYX99oXel2M8KkUjWFqOvZPTRHDs7U6VWPwLkkkreCVQs2RsKiVF8CgtNkvJA1YJTYN/mtdM16Z3h7BvLoMaUYfZnZtOnDR/a8i9N8FKcXevsFTHqCpTbViDdosPuKactLgVW/xU7GEatw2aqEVM02+7ukx2gNLJJYnOaIsotd9u1Jv7ipieE9Z2eiCmQrEAAhPkSFgWI/ZEaBkuxbK7wcCKljvR2vx+TsukK8hXbP38oLwnRLT9KLTm9DN5Kxnn3Ib2LPZ7zZFV7QS9nEBZkl+Y6pa/7r+8Rzs/Pi6hvdv9bblxFuuwdI1aEpTvGYv35XtwNvrNMO5uxlSk5/5zNtj4SO3oVYv0G7/dpPZKM0OuirPOI3BNAINoal6SnjVim8sC/pzV/C9IFms7t/g6f3bmJ2RHR3PZ2HeipJuqph8KQiJ05GtqdOa+XVrfvEv4qakRcIHpQLcmqDGQTsWmxIA8Drc0Bkafl6sfZjRY21vou8kOGbU8dqq2yYKpao21SpcaJnKLTOPOrWfYoWa7xCblwDjG5XzIa1BtPiqoWrxbf4eXKrix9fYgZA0+chxlPghY7tRfM4gy51xaeKlE5eBCwNsBA+kFWUrjOtLO4+D/C/VASvKHqkPxZPYz/XC8C7GvWtAOMHbAf7e9i+b4KO84movhLdd3RUEc5J3PvDQC5FQn2mF0WcO15JVhO3uoVoRQYI2atX1dlmCejsPDSx/5XUbCmMCtwGQapwvRlXcq8jscLQGhM5dPoVBM2GkdwGkbDjRixZUR2oqo0UK0Q+ywwcL0epGVMfzb94ojRd51Ab3Pzh+r/lUROdh8sWj9N9FwKP6WJs3hktwBLxtOFf93tTvgy44lL5pEfYJlc1Si3SHPIcAS7sO1MvETapFmFRamIJrrNNY9JVsjD9/XrR40H/Ll7uFkFWTMMXiPS/gE3TkPeoXcClU8ChH4iPzSH2IP9ecASGMOXKAbZBa0FoQGnV88/JU0Cq1g1DtnX3JW/X2leyfYQUYlXZk/yYoNqzEr4bOQtYen3sQoHUTQV/9xe9YKWiBaB9S9LfI3iiuhDC8CKk9fPV9MoG+4qx/QxBrQ2ecTklK0v6C4yqcV8QoUVOyT22QNy7lKsaXmbUE7U7yNP5g1RfExo6WV8ni/iqcqEEaq4+z+RNGwt6j1yRbfnBJQitO6y3vGpGwta5l0v3luWDXWnoVLdOVF9P3V2/Zb0MJ94f+k5xmAT7K7kdKMIYgBjFT8WxROHAQ9kZ78bMos+lsXTDjl/LW+uF0anJWbie7B7Aia/m+euD8qSCpXBwnnSXFIs4QvM7zdM4sjLUcwl3xsGfqz27Y7lxs/biLDiQtNYLSC513jJMr1XhHUOyOzyOfcFmPRkcL9UnzCtbYzEcgb2YP9FeFIvqnItET6zuJ1o8eso8gnaqmOih+2uXxZ9bd9EMtXl9ZNh+zJ3ZHXA8sxObkzet6YtvOcbf6ZPl5wedbwgWRbT3KoTZp/PzxHtZjM4LMeZ0LTKLV2KiLHRL2N8IZBWSlLFZvqX3o4vMDkr47Bx0Uh/mTRJ31QNfa4uoP3eLt5VHpp5TSHrEyk5kz62bjiJGESZlXoM6YjsRbC3lLok43BvRnKWVfAiDjzsCG7tEVW3DjV3DjTAb0gbGO1Pnnmj8t6G0jq8WRF5bpSb7vJkRooSvFzUfsJUfLMRtCCeBdu+wpVJIOM535kRQHr5FEHbpdROO6cqg0PJe+spkvzYUSKFbuRPF/WzdJWoN982tfQQ5Uxpn4lNzzbhO58MPE9pW+SmOBXHDfDJkodh7iSRBGEZ6LDGADNGABIbay/gKcmFgBaSq7y7kF07b5WxyfxM1xdrgUX1A4MhCyg4E8fpeWBfdXQBSjACj4D336kQczy7D+T7ClZezsw8iAAOM7ghRAM0D6XV4KaJyhEtaqIpvF693JfB/jdwjXR5rGZboyXpdwDRfZB+WK9OBWx4lv3y30Pmie8OpE0yUnptNXYAMwUScRJuRqDIg3VIt3ovvcG13lwMPmnGkfXHlQCtC0z/C33Y5/3di3XvJ3d8YLiErwKS30ZDqTmVi/zX61Et9AWBCDzQx5GBzY3zr1FnmM16/PeYSS5mD2DIms/QunmFsPY1YXzYcXlA49oJLAq4sUd39dnLRj8p1xHLC1IeEZilk6ctDYX5eNOG0dTWsrgTahz1qswIuzIeMplirhijlknjmaeGNmrivK8LLfEpHH0snW+2aMe6/VczFGF0zRDdFoRYnNXp9XqLObBCCvTUvQuhOjS8I8v038dE/2D4V3CDy7wgXD9qc/fyt8oOVQwt3dDbHYzt+A7mTpDgsSwdhzd+DdYoedpX1ptYJs+3ovxxblqyGQZ0FENp8Xfk/oDu/TmGo1cCq/3oO6/ZXrFOtdjmR42Y9l9nruiHWmgSVCmT6Mn0plsQ5CxsP2bTzNiU1dShtfcHZLxMBIT/F8v3HB3tKlQUgS0W9qjpIZti0zvaEvhhgffwDx2JVvcoHZyrh/3EFc32eBDADmmWRDhDx9a4lAi5NaFhnsbwTkZkd02v+dfR8+Gg9OwqmLQBq/He3kKW/mYER5Fb3/Qt2QWQyHHJm4CSrQw30Mxb35tsKFrT0ypCiXL+ibkv5T0ji2pkHZ7oiBtfXhALsX81claY7xAsWzuMXpje8B2Bze/stzx1GX/m+3mGhS5+gHm/Fo7arwlGk/mVuVfz0U/555df4eg3vjYySPsQsXODm/g/3GPnQNFFtD3UUmQQ9Jw/umGC6sVQAdN2PMAJGb/thNtTMXEu+FXii6owNleUtWLZ1z5YQHD9ITol1SGJDeTPAAXxRM9fsvT8l/YH8AuoD4xvGBxORi5Rrseh8gz77ZMLo+8QMWWMhMaQE8X0Zbq3G7ESJW8c0dlWiPk0vdHqUouaoRBy3enLNEusAFCSYl23s4uLqYOAMbB6mp14Sc0RFMreGWHvl+25cDnWpTsrSB7ehlxuSmODanoIYQHnxwOv5ADTaDIYT+SnwJoos/VHs92GJZPboCDvTIuAyQ8A5U9KaiUjYMCpwAnlzB75K6BJ8Yc/+3YpMbe4zyEnzWvn3xSinel8BKKnYnIMLdXbGNRl/M9XlTkh0SnxqOlaqmaS4fmFq9C2b5Cxz58cIVJIQ84T1f8xK6D61b8J5esCqdKSJRuST4yBWkKPsxIJogOw4J4R3wq6A3KqdK9B6XgiRPxlQrxbsItHafh/Gg8E30BHDX4Z4rcOLZ8zHxi2QYnveDoLkwbagm4zggtPoDF0w8HbGnpGEC4VPVQxfb6t/nquF98LsHRUzF9jxDaduVTByZ5PD7Wzf1dLuG+wz4XU9wYx5Ov77oqJZ3gbfHzkTmUEfsq96n1JropRqpvQ9gz8fxT0kNnEqVRC+t4xZU8I5/7TlWFBEZVK3TXxJ/1YYVt39gH2/onn/hhXF5FM4rXuIZeKFL169K3VQn7kjuXRtCvbQ=
*/