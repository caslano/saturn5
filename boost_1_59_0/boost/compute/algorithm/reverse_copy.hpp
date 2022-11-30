//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class OutputIterator>
struct reverse_copy_kernel : public meta_kernel
{
    reverse_copy_kernel(Iterator first, Iterator last, OutputIterator result)
        : meta_kernel("reverse_copy")
    {
        // store size of the range
        m_size = detail::iterator_range_size(first, last);
        add_set_arg<const cl_uint>("size", static_cast<const cl_uint>(m_size));

        *this <<
            decl<cl_uint>("i") << " = get_global_id(0);\n" <<
            decl<cl_uint>("j") << " = size - get_global_id(0) - 1;\n" <<
            result[var<cl_uint>("j")] << "=" << first[var<cl_uint>("i")] << ";\n";
    }

    void exec(command_queue &queue)
    {
        exec_1d(queue, 0, m_size);
    }

    size_t m_size;
};

} // end detail namespace

/// Copies the elements in the range [\p first, \p last) in reversed
/// order to the range beginning at \p result.
///
/// Space complexity: \Omega(1)
///
/// \see reverse()
template<class InputIterator, class OutputIterator>
inline OutputIterator
reverse_copy(InputIterator first,
             InputIterator last,
             OutputIterator result,
             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    difference_type count = std::distance(first, last);

    detail::reverse_copy_kernel<InputIterator, OutputIterator>
        kernel(first, last, result);

    // run kernel
    kernel.exec(queue);

    // return iterator to the end of result
    return result + count;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP

/* reverse_copy.hpp
REfj9K+hqK/HuCXGiLl5OymVKGVtrA75QwUuqbqtM3FSzFsgZnmjPDmVayYLRGSffP18v3CMS5TPbKde7LOcZH30zHy9/XxTZKb9rYAORy7j0jBq3GKMB2ukUXVTo9GXe5OMfJNV2ONfscEVsN/OjkrmQE51bN0qsa3NqWq89zhGK0M8y7TDYIRd7I1lXGUZ8jfAfc6wCKduy6+cOmDDmqBeWU5CQHOgIQvzVXXf6uiSZ4tWxcdLNH0zv1CJ8NFJUOyIo9LVSVesyKJOtlLWxMCz0DFGb+WwaV03auVEHqzmaMPE7FzKivpnLuONpPizgaZaUWn6aHUsWmLGwuRdJlrQLVteQK9jDhVifyU5xuPkHKfOG83e31iwWB9WuI7c9MXJdeuFS/MWlMYnkagIYv8MRzaGaOKLYstBlWrn5yKMSLvpyhOi54PX/yXqcd93+q2M47HjN+pKlgWOTPhcoteQhjcsiXtMsMMEiQKTZBpyU5SoVwN6jfZnIU4sjDa19kS/EDo/sjUce7VGx3bMeobI89WwzZP8X99fInGM6len9ZJ4QKnoblkluPORO3+L133Ap2oFC8cQjfSSrv79xAL8HugeOLnkBZVOrHndgUPif8B3GyUVZggY9fSMw0rJcvL1TlgCw/OYux9wCDtqfBFG9JDFiZbMtoHttn0wLEfHADP2iG0R1lRS+NYCjnAFYM+R8eHa753Y8VYM82m9CxhUD+WD3FaXNeuy2UXjs97YOBmtFcRehSC1sZKNHRrvLZCxTxRv/ADdtjtnQyBgAqVIRo+h3ra5UFX8cbWeHbX/Cp2qsWVrk5YeKzmxg3uk4mTlECiTXPy+ydvx97QRUHTCrTuCoiaDwBTXuLp35KE24qQroqqjPP7xe+IuJ20rj2XSxxG3L6isCKGcMA2K2C05HzNwH3PzWMj7Jgh4/wSrL2M8i+tCF0RB1XVn4zxG6isQCqO3juvGSLwwlXI3JoqVJYIJMvHfQcJ3qLAnDQezQBodVeoVe2OzApnqYJyPlZ47ybHb2ar0JDhfX93rG6Z9M6vntKwZelfLoUaiV+Rb/OjhZp8xUuKCgUrgRVHR9yVa9zmsWvdUxpBxqo0mDNzAxAIWveQGxEb3riyjPeRKRBXgGj+4Dm6M7ISKSQxYcY/O6KVfe9wO1ICDO+ukW9F4t8MVRMqR0RkQ8JB2xOSN4ATICzdqwoojtNAR7H66Tic78F/hx/MekAZOPq2xJcM70TjI0woWjfLyymFaLfZs5ZVPNqWcc8LjcXkXeQIBRNE6ViJQZcM9Z7dlJ44N3mhVW1eClfCtBAkZWAlfxlW6VKmo0dcyDlHr5WnC6VsVSTRNiIaf+PkXtvljfWmHuKJeXPqxeM/mlg441FnAtlbBxKo0I4bekec35fej084TbKCYneRRUCLivvZtwt74rSJPYLpsyl86Vxtw3pQuV+cv3eOpiS41I8U9udZ+wG3tHgG1Okg2kaCdPRGVKjkVsM1r8ejN9vDVRJ2ISbas7Kh5/9m6EMm6Fq81l4Fx/ehEZrUONo1DtH5DmU1ifWqFCCpkUSi9yPkYEH7wNovZhD0vnn7soOsicEWbvxzwMe1nKbhNLlEviqbo5iqWGhYQ9EAnEz5A5bV+VlXqTShC/e7omdJp1odZGZRPG8SG1CMXmMGDm7vesONlGSqoRobTvUjz7bVob+SBvtxbw7y4jMaB0RMdnCYgbK3cbs8IkQseXSR6T58P8qr4SBbzqFng1wjhY5nOCchblxbU9LYJR+bsfk+3/BeoIMe16wHIdqgf6Ap2iQuyekeTgjztokSbObVSsoPuoWUFNSUwmNh46OSpValiuM/bNnsjYrlaAso4k80yDlre8WF2dtheC20JEUN3OluvkQppD/+wuFrsn42e9kz+jjelTgRcXh0r7xk66PpA+WeqfZ0dXSNaDnSScDfpounDzNKoF/R+BF47SnrrGKd2Ywn3qy77dHakxivFEQndKtx6yZWW8S6eTm0rmoGOX9HceaXu0ZbZs1UNLdfYTITB1UI+b5pPSislLKWCjtPrwAlGgkXs1WefpI7CYOC5Ogi1543UaRJoGottFYKdWxpHlavcNdygHHMOexTICPs0rXPm/IIo4KReWFmGc5U3DS1bdeTqguq7krOYPTAwLe2sRu4QJgCxDCGFVyZSATLlhuU6J1GqLWLte4HsL/Om0hGBev0mnq494Ke0f8aGZBghSq61W66G5Gi7aSD8EU8mrW7xtafXeYfEX++FneMzuMzV9iHmEaqwLe6rCiGkOxOIq1RiSXJNjkVi2HjKYBG9RCMl2pjHBFQ4omugoGOvCg9olh542UBXD9LE5J2T+jkHnHHupodQiEe7qH/6aA9pOZxCQXKGGEoK4wBjhCqm9UXDbkQiU5/nWN2xridwkEMTkXKqum2Vk41Uc3FUvIHK10UqU1YMm48kPNuiYkjUz8RpV/pf6/ajDU7ATM2Z6RwzTJwB2/3q5rZL47ckRoFH9ZVwLJgYemw/lySTu2+k0iBJilRVSbwqDR0MO8eOWMl0GXDv7bRe0eYlJsbER446qpYF5h21yPROK5uLmbJeCy3150VzAxjEOeZiEU1jZl7+xDbyaK10xtgkRHQp0rKI6O2BpwWFFh1hbrsiYPBR5roruH9tbGI+nlP9xfhZ6NNwTaSDFXyKLuFgEQv/TlyNu7JkuahtDQZVKfYM+75XBPlZsnNNWeSE8bIrkcnpRqmbJA/xVYH91HmIMtj/yQlLYYCJ7ZUcEqL76k6ACD0NdFJf4UwqgLk3YInnEHOCR12XpnuHyF/sgbbgxgBFyS0utDFFmaQL3kYj3SlkX6iCQUQtN06lRLot49xDlmFmRJTN0pX35kS2x5IG4QPZKg0kWvprt2PfTFgDeJGDMUOyKaJPX20Y0+Le7QSMIxDoUdtmsQb4BMb1jzUVNj5LCd6RIbH0jrMe4guXSYEcGC8buN0FiXE60glyHDMYTiQhOi21vLCWNUqwXC+xTS+RX3VKw6L5gvdPCCH307XN+cZCC0rnjKDy4UlOxbf3sDsto2pTPeSUTMypLmsOIqnLfkhmEjzSSsVOo33blLX9T5NwSpoEfof0hNb2YPkj13BW3vsxH1jTKTWNJwlTZI/ZmI7FjfK8bv58o3FxekJeFnPayFjsz6M9ayqTCz0rlLXqorAq1u7kWJocEEZQX/6cB+D+M4FqrdQYOVcPjDNzjSb1oI2UhI39wnPajTLVUW2OL2t3ONPtw8obXXbZXy7p+I3FEMgfuypDlnkT+yUVBDp1n9SehEgzfVKVj9lBkpqcAzQzJo7zlFgIWJo0USeweNvWi9OaP9p/SCr+PXObw8vtzAYQXuTpkUls1eCHyE7iXPkCmVKNtSxMTJt49B+5BoudmnPK6Rj8uazBpK8MSsV3yATiN87R0/zYF0oWeCB7YV3IfzqYpevL1+kLdSnVhmI44Z4f3Fiy803bX+IPiIo8f9Snh4gPl47LkkDBkIO0dzYCEWYYO8jPaacSmuR0FReQEJtcmQ5ICE4PSBhUEYKS7FCXVzSZAyXVwZnISHuYzl+jv6UbswMSkFjpRUwyTkgpDlrJacYg3DOSzKRru1VtDpU6Ml0sJsYriILl9cIZBUq8cBfNLdSdjPeSrMxcPCmz49Tu4YqEd89cgX14fUgW2T623E+4H3wQFhltxz4CY9Tmbgm9MvEXTiF8Nn0TL5IBi9ymI8J1ECMuNoxQbfN9T5XgjSNtBEKDZTsD0jE0P+CbUc6MUo99NdU4IYiVOMRkA8RsFL7pO+FcEcgUomub+pTAsIj6JrApujssHZ9UNkGv0yugyk2k9RJk5wik99iQP8JU0lWiE3KRZmGYLAhGZ4csdaDEVch9BUfphlYQg42+WYHp67H+JPAe1s32tSFzwrVA/wcVvtak4kzeQ28JJaISSuswobOUqq7gNY9MSQB0EPbu2Abh5L5TM14vQ+VOmrz0Nvq6OwuLLmwVUVVQwObzhWGpR1lH+5u31yreX+1l8g0bl6SjRNfDpqutUp4LJ1VxUQq16f/cfd6QMx3YojnhHLphNLIUSyg9p4LD3o7cS5a/3uIru+qa7Af0upuEsJtdy0+v979OKVFbDFZG3nDXDpPAj5i+ctj7eq5JygTe0d11KkpDAT9nllY4buPOGtexzwQy6zT/DJka0oaHssd2MuK2EFSKI8A8z9xOnz7UuHTs+wr1Z6KHVCUfnZulzgtoXV1amC6n9VJjgmfJ6H+k9TIjZy3PQt63BK0MfZVOhDwjvbjq9t016/0BGWWT0qp29DJ1kVPidD6C8R/sDodJqa1Wv/eQ6ruIBq9deXdXNMKd9CdKxDgv/MfsVhLQ78E7REoJHwB1qjmRYstCQR5VWbC1RpCd012Vy5xxF0FHIl8OU4jLCgNZO4LMomQbX5RNXH2TETLaeKTKEij8tAX/igNBzeVgsz2hMvFPCGtUtDRjJVPjdS3VDCCun5B6N0skqSkcgwU5XBijBPN9SFln/exCHZ+yLkjMTUu7eWc0RdNaDmZ0iq2aMx/hwdWtEkqnma1BIh6SCHl480zDJLU+AkwBnF/tnK/UIgNxdlRdVW3LHWxbJz2DVXNyTk1QXtA7XXGjSLp998lMra7N2HZmpow3GUNMj03fq6WEHZmviFRi01Og27the6tkX8mgkQ08HP2d5BymbOH0Ooary3uJ/nzMCaq5JGb5H0A8mHKnwjHiwXhpJs5QnvOWf96NEwLCfXel9pdSLE6Y1/n6OgiDQg1d3hSUu1toZQ3ecXClfpu9iC+TyNYk7uVqdPephqjZi10IzjBNmts1j7s5DMJlxUdgsCt8i3opWhuXJvOCZLfj0tf6gA8rx/6yxT4gOLddnJ5iVOwH1z92pPsYlkiWIGkt8Clw0WJz24DhSKgtCIvzC54V0OXyWAZEvgvYtNm5XpPt+fcdyntxDz74zl0uLTjPYIUfPxVkhUZh7AODsYjS3IVHop74jmOl1eJ/oaN8wahKMrpjWH1XZjcSyI8bZ/Yc01m1Olvjw925K9zCcVVZULG8L6wOw0r1gTcGPBD6IBCLZcig1Y2dfwh2DDJ4VHRq3PiNlMgYdnjfIecTxHNvqTgZObG3SWOYEGT7B02e/5aPDbMQ474rQObYa8niWyq58hzW7Yoofk0JrWqW29WAKt82u3vj1vyWQZm0h2tFLI/1ejNensxPveFdM+pijC6l7lOXILRO/uqiyP5+sAz/4HO31JI900qU6Ahgg9KXm5r1DftLcpL728wrr2ssyWdaQH9ov90jFvB6Ha+QMlO07nGM6GZSbizeNj194AFbOrQzyaj+RF3TWpwhwsE9Wo5TYJXsIRjKISFq+jm7650ApAMlGWl8HTEtaRI2L4DD7TLilxSGOTuZCxSF+KqFJAVn2iYKVPCVLeBQKI8zIZT44yFDok3hXLpJpn/d4ddWpXIlh9uo3ktqc1/67a7D/UGwYIi1DlHmbXQV6AKW6ksKXikl1dcvpuUv8OQXASAvfNEmm7PQH7v9ATdyp5+mAlcoSi0jXpmG8WI6mT2jaFGaeQC80pkV1nVTVOTCqJMoFMUq2OmCpdGW1wkPNFOPNiHr/SGPF74jI6k13hDqdOmv2Ibf65PRn6h7lU/veLB6Of1xVhMlLEGuDDXb4p99EEBsMx4VrB2WuYdKuv+Ctj2V/GrY9lw3X9gFGkeNVORGKnLCVXhSI55cikstDd0ibvkygA6vaET5lIosHMOV0iTzfCvkW87jxlT+KWxqIG0wh/hUZOeSGtTZS762llhTsAr8ezth8M52jYCHhUVPUdf5A3fPII5zfos2A110OTNyc3gwZNNRFHbzqKmL4hKGtF5zMRfErNqqameYlIS57nVx1BgklUp7h5u8klTwGmkeGUqBGbKe9w7Pvk6h1YxeTzSHturwdTvkJ8pv2cgeEOK4BL+D46f+EZEI/Io0T0ahpaPljf3HhJime5sXtq+eQ7VZD4tguGLdUIXrdxmpdBqpeM6GIANcOl+KQ+Navn+hf9IZjNIIRwNqe7KoxLXWCKF5QfUq9V3PQRvHKIwofiwURLTZgY8Vx0b4lbmMsfOCObuCX6avs37Gvk1Go9AbWm5x/2EpnfB4iUxjvNlbLCfByayzkMzvKIkhIBu52ZE0cn1RAVvCPnp0r8BzXupPZVAgMjmiCA6KdGKwWpK40YdHO8PEsFra6c3s8E3CH5+kzVwSm5kQ0toUHm05pHO+AcnaCBeq1FkY47zEn3yuWNdKgJG8k1QDFMpVrP1MU023f7QwycDkE6MzJWmp+gfCWpMZJxjnHoXDdyNHLBYO7PnuPNRGEy8axffNDsy4/k5i+EgGM7RaDca3jHgw6BQzH1afGeE8X5nTjMRYUVG9zB/l1npiRDCyUPOq2Bdrwoy0Y0CciPAMvhemfareyTwsxUswqGQyzxQVT3jXwOL1xKagL6jiVN4bxUTG3dfNsx165bV+oaTTnMuEpyyiwlYw9NwFLV3mY+03yxTTw7eApKtQbnthInXeAn82g6WeuZgNO0NrRpkpd25+bDzWLXm1B6SejkOrhlx7QBySPK5xRO8ajJA5cAfa+spsidEOvaiCX8p4S4v+F94MEisCmb8mfgvz9alb4l2UH4qKmTcljoWvJivgSqUom5T3amOYW14B8Cr6lAecVsFQCxtw+lw1lf/vHkkKTgB0QJuNswyjXuJFfUl0D89ld+Wl/1+b1necD4AOyzXm7AodCa8yzhvyNKuKer2vdbm0gqer2L4gBFhd0eEkqbxmXLGboHnlcIdBpSProeB5LZc4Xgx++Q7B/MsS4kG59du1wDBVBPlScaX19JByfhvbdWX9OpLbsDVz47pobQlCF59++U1N+0SDDMYgSbGsMeVzL5VDD69uRONbEnVdr7IqGj/jk8b6lmK42BvpKSAf5xA90hq0YpfYWjn6HTF44LDuclNH99LR1Kr+yn0hkLMntZ/X1LO+kRGzW8sSbueObQAd1yXbkPyGaAbOZUpLs2Uuc4gvWdCWyjsc4dhUHBWwBa+TcOm6/QotfblxRkhwytKtCcxWh4mQ6hZwUZw44I7867PAOwv8tHb1Qw7aOiDCD5g/jwEWNJSwISPBOg7d5sWynV+lSMRFcmOpGO5/+0r0GVDrK05EZqk6MI+3GHds7ayehnPEeyqvIcNQl1KX53LuX13UYg/b0j6PgaHFPhqCQwczWoZbA83ZOzR54reWimtSk3CHZXLGciRXkGWcaOBHK2kz3o8/6q5/6LCQv7euWVcexKj/3ap+vYIQfOAt9cJJZ2mteYdevDkOZ6gzABtG3bGiCbw//53t8Vxws4GfvmJOF3zFBmzNoa6UTrydmbt1nc0DOhf7A6c5UfTuIxMR5BvS870vERAzYat2hV/G7c2NtWakwPrih6NYK9ATCl46nLQVphXlZ1VV/7krxZLywj8ZCH89gu3Fd+wZkmLNu5QuBkJBeInr9KEtOdJt9Be6EEEevuVusVHyaT9RvFzEcYPKa0b6RWHFRcsSZzGZEzROe83oMj8eaP9HtyXNhLjSlrVB8SzKQGOpMY81gUldzw7AsKgYOCiA4Y38LJkNc1psVIBBEGcXt881m+Uwd/BZ
*/