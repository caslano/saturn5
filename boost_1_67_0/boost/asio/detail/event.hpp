//
// detail/event.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EVENT_HPP
#define BOOST_ASIO_DETAIL_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_event.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_event.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_event.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_event.hpp>
#else
# error Only Windows, POSIX and std::condition_variable are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_event event;
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_event event;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_event event;
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_event event;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_EVENT_HPP

/* event.hpp
6LrrrgvCcbIxsIctxmz0QA1g9nQs6BaAyelZs2ZVMK6Fm90K4JoldXWSgoA1r10DQfR3hNAT8x7fqhMWePwnrZBue/wpvF7rPzuxRlce+wx17V4BPArwzwBGVDyHHsvKLWB+KZdHKajZi6awaD94+5+lY+9uqZh3LD4vV6k9L3tjaq5NqNghUBkv3LprwBD9uPmYnVmxXCwfwaCA4CLcH/0O/OEW2fWVz4ls2oAR0xs5+ZyDz4jYUYALrIjXGCSmdmWg7+eHqRft7CA0ohfXt2pk+gdhDIDyImf4W3odOQgOpOFbEuyC2KF2oy4dOHM192e/lOJRtSCR2SmZm+1gIKFJoDz88MN47bwxUVFR8Sts7f5Jy4AfhudSeY8gzNxHH9cj34NOY7usFcjUtUh4tLDChs0pf/MpHEuejgU7nhyj0tStGzdL+4t8qQocidDeCIJqMIwqitl+kBvH1hm98UnfT+/SUntvGEFCYHCByulGLc7LjwYju++6Qza9922y68Z/li6AhcLG3pijCk3rmaOeoYT54Lq1Tnn8uGmy2QkK5s+yccSwEY9lo3/Dg/fJxg9dLQdRh0q8q89RshqaLz8RHHp8nUwyPqndd7OM5JWFhfgW8NviqemnMbvRDseBP0TBow2E8MwVt3I5gug3TVAvbvJMufYzUjb1GBQjOzhcWaTMYu2RwCmQNgCF06vvMpt8VdazWFEEDI0YorZD/waNcNXatWubzj///LEslPWk7LWyqaLqapl5wz/JpquulLIisBRMYL998Pb7ZOq0qVJUOyojqd4Uj/dJXMFXLrKRopgNX/ZA2cL60PGj0nDTkEQcAsOXreJonGJ0NHy1tDOJadYffysb/3iLVOOA3LjLr5SqRSfqcwQ2Gnlk2hqK/rRbo2pWzg/9C1XGa5qcPtG0EY1ugsFGN5oN994pB379S0liA4JgqEE5eZqAJ5z1RhIUQHtL0CFb9YcS6x2q8piq/vAkg2nPiOul41kpptFkVi+NB3+j58fx3PT30pIoX7AjOJIYPnDiT8HBTrQDdSpesEAmffjjykeWMEoZr8lvtgPN1atXN9EfZ+04enC+nrfKGyDWiByucMCLe+b/gh7q4vXr18vixYurx40bV8ZcGY+aDWaNGC7NaLwWOubKt0vz738rVdgdi6GriKEXPvDHO2Tiu98qvLHQVA92sEDQcwYmnWwIP5bjr72YHxwZJyrMpaXhfm8GOzCC7DEnh51fUSpFY5XHvft4Ox+6V3Y8eK8UY9o1euWF0OdLCb6sa8AwULiNZX7kjfHUeMass6kwP+l2AWF2179r53ZpuOt2acAzjVhDvZ7CLQdvSyGAvMuK4CcLFRioG0iysh5b6VD+4kf9+QMVFm71Y1wnHuJoNCbUtAxjHDc9HOq2tN7hRLYf16bcuepBP8upFT7aoS+VLfrOjVIEecmmjI/GfwKEd7vxJDpk9hWMHtdnS5vNP2+AGAFmiowIkr0Aya/QU33swQcfbMSuwESLQ5MNlkvNwC7E8488JJ04QhIvAdLB0fYdu6Tx/kel7oIVQdJkCy/RgXJAoJwlc6kcfwWH+ZP7ZnfiBJ7hMJ8W21OVhnuRmJyQJUzQIelXlMoQsQINx8Mv3VtelsbNG+XAz2+UkjnzZdSZ58go3LZYgRvvqQwUZtLPwOGGu370N2XgMJ7STeX6m73thWdxHeiT0rLmEelev04fhHLLthRDYBmAwUsseNG0PhUHmaAr8CSaVHMARRMgChiirIGbRSGDWCb6aRg96cXOMkccJy3XiiSR4i4n0io4CBJ4dmA0nPLxazFSZ55y1kycH/LPBQfdq1ataqDMYsbzJ4we+LpsYaoggFgD+hky028DJGfv3bt3MVE6e/bsSms8FsMaLapIJXVjZM53b5SXrrpCSlK899djZAO2fStmTZfyOTM1mR5sZANQqYEf36kNA2+2iXqG/IP4fnBGHAY68dlWqowWHRbux6VTgYLel9MSfm6sFH7cemQvx925bhzsa96ySer/8+eSrqqWiuNPlEqMMBVz50np5GOkfNYcxO5V5Knx1czeUM9mPA3zM7F/n3QAnB0AZ8cmfNn3edyT24J7ckGT9xJXAhScQnmg4AjIaR6rha6EFWaF+KN2nwOO8FNgmUCj0cHEfeLCw4/nWYwm48PHB4yXn3qofwAkJgfdNGYRnF55DwLJU/ATfWwHToCXnniiTPvMZwM+MYewMj4aQGhidtOKEYSvaDz5/ve//9vhNPm4CwKIEbRRBDsCXAzeAr2Yo8jMmTMrEKb8ZIHDPZ6lN7MOT9in4CzN/p/8AJXHFz20AdKy94+3y7QPvRs7Ffi8dHA5HFOBtFKn1bN4u1ReUFS4F99PpAZ+fCdNHXV80kGAhTNCYO/Nk17MnnXkgp7fIynDtEu3rrGuoqlTg64O6XnyMWl54jFpQE626IzXjZUS3DxePmOWXs1ThE9Ll+JDqLlUAtcW9WCa1PXKLjw0bZUurCViPQmdAnKqRK7XoDwlAAVvclHt+3N01qmiSjJyCUBAuyfIWlFYo9YcvUBhBCpkYHEDWvAwexhM8NegwB9xQYKe9gIUw3F+0NvSRTyOINy1SpSXysIbfyJF+DpWNmUdiwsOzGxSCYYx6QAAIABJREFU2Llqoqxi7fHLbGn78y8YIFYYP2OZ+okP/deWf/zXC/Fl3JVYDDWeddZZdcy0P3BYwWZ+4cvS/Ngj0v7cszjawKYG77Ao3/f7/5Up73279GCKpcz1AaERvB/4MzYT+D++08CT1V+jsx910gZ23xLQygjozYtJEcey5vSLl0MQBJxNc1ShnVME3a5EJfSJMDPtbpd4w34pSmD6iAbUcmBzwpuFMz9HIVB53tomJVioxnGiIIZetQKAjAMMFHyCA7jUbWm62ajs92kncR2dlSQ8mBn9aVG7Ojw3vRmo/vyBUuarRUcDZbkKOv2Y1o0Hu6YlDVg0GD/+7IDtpR/B8YiQgNJPxzCtwkqcPOsB00x3YWo1+x+/K5X+m5UaP+KH/KF2AfLoo482Yo2cxOhx1/ve975+DyVGkFWvggHCVCwMAUJNhUJ8CzsnK5966qnW+fPnV06YMKGM0wEWmEBhfJsmaALnJ1ZaJgtwh9TTF66QLjxv4EjCRXsbzmkduPUubBvxzg9PgQwUGc528Ew/RP3U7kXy3U4cx7/PqIFofenQxw9wwx1vTWN01eEt6vEgBXBBaqzVysbVSUndaCmrw+331VW4kqdGpxLkh94bRpmCnXXMyiPkwSKoEMDC9QM1nyklcP9xAg9aE3jHpmv/IcFHXbxSU0CptOx+BejnW13B13gOENTNiCShcyOYGu6uTxCo4Yzn0/XjZPUnGdDVrglxWWvrNLx1B8ABWgRIBx5cjrvqapl01bu84mT5JU9MG0BwoLYTJz3asATgG4PXM3ygCoBmLT119904G5WnYjrdXnzLJZpix3d/9E2cz7q6rq6uFK8wcsEeIzioLQ8zo7JowGe8XnzHW3CyFme+0DPy3YMSdI0lpbjYEjS4OOZuEuuaAQ6rvPIAP2YyE7OrSXe2UcPS+SXLoOkTMhoaxYsfcE7DvAgEQtUxk6RqykQpG+NdGu1TVcPYTeGg3UyLQ7erPGho0dWbbhbPTDcu7Z34BHf73gPawXThAaynNCO1aik1Cycf123eVlCmsnALowf+PVq+pxqef2aejp/RZFzYtYMIRgxMp/BUMIGRpAPPcErxisRJt90jMXz0J5sywadp4IC8pW+++ea9eKU2UVlZ+S/XXHNNzuce1slnzcMV2kIAQoJM2/Om1wW0N33re7dg0X7a6aefXrt8+fJaFyCM6+YVJHIsu278nuz4h+ukoqRUwVEMVBAkxdBF/vEH9s4mv4HFPLTFVHo8quYPV7/TMaaw+EpHPXwpoB3KD1dZcNwERfWMKVI9bbIU41bJkaK66hulccNWad25RwVSy+ULaVBF3+2F8devnVUyI9wNg913Bt8O1OTRcbQ38MNJUp93KDjwrAMdIIHR44MjNWqULFn1iPDW/FzKRg4XIJxa4dlcM9YdD370ox99d670DOsPIAOaYmXLFIv272BU+e1jjz3WPG3atLLJkyfrygA2LMnTikChYkVygWTa33xSOndsk/3/8e+Ii54Dw7uO8JzEY86dTmPqovNZ9J86wVaiSjtqtNAA5kmLSoQvFmb3nTnDNK0XMUynGiNF7bwZUo5pVKBwQmCkqLLRNTLxVFwVdOKx0rhpuzRv3okpGO90oWyjNvhnm3gedNCGH1ZU+UyTnl5ctQdh8Nf4pMTxjNFIAzY16WYcN60Xl1u5BAinU3zm4T3vwLMOrDmSFeWy+Ld/lPIpU0kxq7Jyc+QwgOBt1441a9a0+M/q/ilr4gICOFUesLJCGgEs2B8Hcm9GodO33nprPY434HZNb/izuGZamrA594Z/ljFvfou0Yy4d9CzoabiFqg+QyG+/DbzGAwVtHTaGT80aHSaiZ4YzDsMz4vpuTRcK82kwT6aL8RDj3Gn4YuzZEL4TpHwMnvwTFCNYF5UWy9iFc2TmJStk/CkLpbSWt8qwnuAPDI9HnhsBPm98NwyLS5vyjXyifxDm0NA4GtAnnEDSaRXi2FojAdYl0L5d2HjgLZLH//LXUnPiyaSSVZkM0TSNTaLkbbfdVo8RIQ0ZvAHbus9mJVBAwIDXIJZH4rKLzBqYmGr9BFOti6dPn15x+eWXj+eoYWuRfKZaaYDjubdfjnu0HpUKzEGLcFZIp1roLYph5zkpHgPRP4W432BsMb9ttPFZInVn+mtBzT9HnAxwIV71tIkyZuFsKUYv96pWaI+mra9Iw0tbJEUJVcWep5d9OgrQX5nghbnxvCQamBFH2Qr6Xjh/OfLjF6MG/rWTS2KtoTtVXHNgdtGNMnQmumUBrmkdf/kVXtocvwYKmv+/vWsBj7I602cymcwkmVzIhaQEyk0QlLs+QhVQqKiF2mXFVnd9rEpTal2glVVbaet22ad2pVSUp63rqlS6aikXK7CwqbYK262Fqq3rjSIqLAqSkAuBkMxMJsm+7/n/b+bMMDOZZHLD5CRnzvU///+f873/933nKhxk69atVdjc0Adw7IBotTTB5RFJPSpiyZ0han0bgBiLxfGj0bN1atq0abl8GdMkErWomPFL8sb1X1BN6P71YGNmdHfga4eaRoW2QQ9xIqw70SB2IQgTCQLdRAKCCJdZ7WeJjrfLiLgW2V05map40vkWt+Ct0N16rpu84Z9S2SWFquat99SZ49WsXF2FEaIXK4J1HvrqwG/ns8QoXCN5dLwFBt3WRAWTEa/7quByblUL9Q4kaemAkgFAEsB4DiWHjoJDgAKR/iTEKz9mePyVtNeVbZOSiBXvQSBq1aF77fucPYkBxHp2uwnSBSjixisjHYraxF9iG/9hw5RPi1tU4vjFsfrKKW4hqLsJ9RdKEzvbT8QqRsDqeHEZpSNixrON2d5WHuua3OGlauhlk5UnPws3Q0/9J8im42iokmljVdGE0dj4AF32umr43lYdsj4S1RerKnyNHQhdizJQmQQcD9aU9rLE5nA7+qETDb3zbjXktnJdXKIfoRkBBmmKXGPfvn3UO9pAc/dizMOem5SopOTTugUgvP2n7/z6HiA6pI9g0AbbYoVlRuaRF6Y/luFo88RNz6k0uD4/1jKgwsmSaUWxQ8cHmQsaAw1B4pdG1S4SQnGm306kwwvsRrXyMow+AcwPGzzlPFU4fhjyYLYsZvF+Um1OWYEaMn2ccmVBdGSdaMt6iPexYRrziXu2nx8a9q1Q57AUcU4dEWDABRf2YTp+6a2L9alcyJ7QCK2YNGTrHTXUeTHm8SN06erTmRMW1MHEbgMIn2PU3ctWAiQVXL9eUVFRY74c00XMEr0klusZMVJN2fVblY6t7fWaBrJooMICiVX5ZNtc586vlTX3h6XDsAFDrt2YbFlGa4tr4LIxw3kxBdybqcpAMNlFOcAGuEY/sBlZGWrIJWMhRuKdpY7semH9hLiJ1F0oDyKMetZ5kR9NYgEDblicstrNj6+bHx+8If+wTI3+4RpNB7HaXuL4GPTTmDREmmJHEGhs5+233/4TnaGLf7q0mzfWs0Em/A70kXHY6GEkxK262bNnD+JLkj2K4s6wVECsMtxDh6mpu36n3rzxb1XTm28oN6bbazBoAQuNQcWdGmArZ9uiItGayXQD6ypng4caG7MC8rLV4ImfxjQOPBNk4/5kWBUlE4apE+98pBqrMfFV6x+sAabw42MRqOVhFMHB+mYWqw3pZVvqEXI0idY58EGjYq45SACHF0EhH/nPP1BlS+5A7sSGtEEjNEOXFmN2NYbegYNRusd0Sy9W9KNilP18rGx7HhPIHJirlXfxxRfn6lF4ViSVbvvrIG709RJu9TWpd26+UZ16+X/0mhT2brFXSw8kovuV8yStHi5rMNHBPnJeLD+Gy4Zko2pjx2cWAhzjysLgslL73y8qp/rgx6qhCnsF6IrCj3ZRFWgrXV0R8QAPWAajWgEELVbBtcABcRh+zfWhSwYgWo19+BE1eNEX263XaHDwo0oLnaOeY23QO05htHxheXn5e+0WFidDe71YPQIQPtuhNT+ZBT3kKYLkqquuGnTBBRd4CQ6xAg5x47yPasPX593ld6jaHc8pN2YTExC665dAgZ+gEZDormC0JqeomCDRbRsFjuwiryocU6y/TvHu3a/iUUlVB46rpjps/hEBBtSCARK2l1jOxtUzcgkItK3uzrXBEYC+0Ypux/E/f1rlXz6n3aqMBw7sTHJq9+7d9bZSfv2SJUvinu3R7k2QAeUkzNatOoh555F3Lf09FKnlHMgBe6zD/kSNwi6lMgQcUuGxXJXuUmN/9pgqufUryofJegEMMOk5PHTRQPprZbN2a2DRmkUrukkscGQOylSFowZh8hi6b/uBvpHUO6K3rvi8QuXJxdQZm8NaLloVHxfWI3kGmb/mGKj7FoDC6mmEOAU9g9NHaP2YcKqwNmbClu0qb/YVIUDFal+TBkz6oJ9rjggO0hBo6bbF/7sxJXCY9BnP32McRB7g/dXr7gcnuQkvnLZo0aIiTkehuCWiFl0aqSi5LpZ7fMN6deh79+IrgIVBbgwogv1a3MTiKmTHFLvo6srWn4PIcZOMLJcqGVs4IFbFqmDEtYLAK9+tUc1Ntj4GQJiEzXSG2YZ6yjpFK1r7YxXAR8yNLULHYca2Z+SoOHcJR0eDwmpDJ8/JbNq+fXsNHwng+E756888xatcj/4+fHEnfH2Gg8izj75n+Uq84EZUaitfmIeYsBJoaVhBYsyGiOXnoSkXPrtDOfLylR+nT4X62NFAAXzBGLbWFqDB0IjEnnz1+DV0YgFH8Ygc6JnsqQIBDNiz6iANqzSKhnuxTwA35bDqD7Rv6xkc9COnEG4hfo6OB9EmTWoQzlGciFm57hEjI4AVqz2l3cUVusBe0IEdO3bUkGbQY7Wx/LUNT4XaSjJ3k9vjHETe4+C/PrQO01EWopcrDZsIl+Tm5qYLJxFuIpUo18Rzm6uq1MGlS1TDK/uUC6Pu6TgjkZyD3CSNOolW3i0lnvoI9HkNxNLRXuXOSiyDxrtnd8QHApoCsUoTu6igF43fCj4r/b1tGuub1YkjOCoTXxk9nwqcg37RM8g9JNyMYyqCEHmHf/f7qrT8a0k9usk5BBhUoLmX1ebNm6vQnduKaSSbyl954i6zQNf6V81gh/0AXMJreg0gfCqA5BGAZAFBsnDhwuLCwsLQ8W4mSJiXYGnPHF33oDq6dg04A0QuAIXgoKKejoq2QEKwWHEFpW41qDj+WoP27pVKOqQRDJJhvbUPMjoYlz3Btt0iIUViHwB0Rbux6zrH9HoYN9XH/OpkDc+XZ+eKpe9pcUqLVLZYhdWgLnTLj3l0vcqyj5RL9GIiMQhACA4Cgy53JNm2bVs1wQGpY/tX9z561hwr1y9Sm5PYHkB69fOJLrplJHx0AS/YsmVLFUBSVFJS4mEcK0w4iIBD3HgV/qml31S56CH5YPnXlf+jD/WkQlY2hxFbMGcLXpWOstMznConD+VTIe9B04TD4xsaHaqJJ95TxhMKT5LQ/QATxtfU6QbWDzZl8LSpXG8r1qH3zEs4sfie4lQEKGzO0ewDcNBTVYxj94at/CeVhrEqfuQSGWljAQdd4R6cuo4Z4TWQKqiQby//w0+Xtv+JTHS3zqX1KgfhI18+f4R6bNY31mLjh0WoHMf8+fMLhg8fniXiFl0CQyq7PZCwzFb0mhx7cLWqfPzfsNgfIpfmJhwjsTgI3QzMQyoqTld5+RZweF13mSZ/mqpvdEEvStBpmAgk7VCG1xNUedlBvF87GTv5gg0AZM2JFoUZ5Vr5Zpvo2QvkJLDN5BqDS9SI1WtVzqUzk7qLCQr6hWtQaebpsxglr2VBAMem8v9+KEKsMm/g+uUBM9hhP8pPeE3vA+TqofoBH59zF7cQupEAuPLKKweNGzfOqxsCjUFwmCJXMiBhoY04f/zwimXKf+gDgMSDTcfIuq2xEouVY0kv4gblO1Qh1jyRw3Sl4e6AdY0erG0xPvEhIIQ8nbilDQQDD+QouR6/yssEi+kic6rBoapryeEtkYqHsMo4hwYIPkQtkBUHQ88Ycuc9mmskc2sTHMIxCBCCA+d3nEZX7knmAfE+Xf7SmnsTlena9H6i5HbT+jxAZl8Z3m9u/byVtwAkqwAGx2WXXZY7derUPAwsgqWHQSJA4ZsnAxSeO37iycfV8XVr9SCjKztLg0QAwikpbBzqKIX5baogrxU6i0F57VZx7Az+YLqqbsQGDeHBg8iMXYCPcIFhwGS7/Kogi2etds7g+6ROnXGq6ro0zKIG59b6BV0LHOzWDWJEnOdFZk29SA393iqVecGFSd2MRE9DV4BBl8BgG3BXnFdffZXHo1GsumfxC/f/qr2CM7YeaS9LwvS+D5A5kYe/r7/mvs8DJD8lSCZPnuzlNkLCSUygEBxiE9aAndhy8qT6eO1qVbvxaZVGsQszVwkOaSgCxGosbFQNuT7fG8RiLWjTnTANzZmqLmBP+pPrIwBhBAyvZI3rRuDWCBhedsRmOgOq0IMdYuBP1gRx+F99Y7qqPZ2ObWXR20uurcFBFwBBd24L5lFRfE0vKFJDVt6n8q5ZkGw=
*/