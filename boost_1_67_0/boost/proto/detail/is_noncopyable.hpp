///////////////////////////////////////////////////////////////////////////////
/// \file is_noncopyable.hpp
/// Utility for detecting when types are non-copyable
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_IS_NONCOPYABLE_HPP_EAN_19_07_2012
#define BOOST_PROTO_DETAIL_IS_NONCOPYABLE_HPP_EAN_19_07_2012

#include <boost/noncopyable.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace detail
{
    // All classes derived from std::ios_base have these public nested types,
    // and are non-copyable. This is an imperfect test, but it's the best we
    // we can do.
    template<typename T>
    yes_type check_is_iostream(
        typename T::failure *
      , typename T::Init *
      , typename T::fmtflags *
      , typename T::iostate *
      , typename T::openmode *
      , typename T::seekdir *
    );

    template<typename T>
    no_type check_is_iostream(...);

    template<typename T>
    struct is_iostream
    {
        static bool const value = sizeof(yes_type) == sizeof(check_is_iostream<T>(0,0,0,0,0,0));
        typedef mpl::bool_<value> type;
    };

    /// INTERNAL ONLY
    // This should be a customization point. And it serves the same purpose
    // as the is_noncopyable trait in Boost.Foreach. 
    template<typename T>
    struct is_noncopyable
        : mpl::or_<
            is_function<T>
          , is_abstract<T>
          , is_iostream<T>
          , is_base_of<noncopyable, T>
        >
    {};

    template<typename T, std::size_t N>
    struct is_noncopyable<T[N]>
      : mpl::true_
    {};

}}}

#endif

/* is_noncopyable.hpp
bzCp+ySSGXEqCuEeZcm2OcjtbnHbcZobuAKiQs361LyOBgtQdHM4AvuCecFgVb+k+1PDvx8QdQiON9yav5ld/lBKf0oAwlnaBY2stC4gC1evBwhM9wVpGfrtWAgi15qsuLKWXoPBpBw7fgPtb5qUfKVd3PR7TMqOSL7+UFI1rRWjRaU5UGwh8mCf+OpvGHirVEtLo6c+/lEvVb80T7+gEA0KeR+E/bg/wjW+sre3eRsUNzyRfeHhUINj2T/rW6YZ8e4tMCLwSraDeI4qGJFMdy1viPlx6QPPlFkhppjAfYTKYxpT+WNm8l1R7VtgSQ5AeLmk4oBSHIOMNYCbrEi93AcafI1KA9gzkHsH+PZpN26fvoVNTmvHL62MxTPC8+mv3VXLLosjLdRVjQVxGoeyKtjp6d/22lC3cY0c1L3bqq/O315IO5VQ7qXQv4S0lfBwY4Dv5GDSJ4vqvn2U0ePbN3+/vhEJxkF42yccCPZq8eIYIj2ouUgLh8RM5SiskPdjcyB5eBEfOlbhbJjuiM/zbo+cz8LbSQEjd1+uL7yePsNSJ17Gn0fFXgS3n9KEvRmYCXtb+5Y1F26hfSrHG78AM6Bc4PHTCiJLIy2jsYY0oguQsZVOlPNPH+2N+MYSSWp90Q60WJ4CAGoxCQPy1mjpdgy5BREQ93m/CAel9JE2h3KO5t8LMYk00lBGyC+gAc4OBY19PfIOGd1oG51w7MTeR5UoY+CLa2HkgIVAnZghPNFGZq9zHALa3+CJNFOf/Y2l2P5LcYHeqtlC8srXCRn0XmI4pWtUzRqKla2bKoFQ863T/Ou9NOJMr78xPAj1ZGhbq6xwOMljp6IGN3r9cZN3AIVflUkZvvxRmmvVn81Mu3c7Pbb0CwnEls6x1E+7hN3MQzBwxYaTevRVOpoIUF+FHpKlKWsdHUxJf3PyXrchEKjSIRIQn9HE4AZ2CzKri1FyVrIIJH1NVrx0fPiHk1Kkm/ROdNd6SnlMJItpj6GKWepi/JMu/2RRVdU1+pD5WN9mkLuz7aojJfRCyiKUSoYp0RbDWxtBaEm6g9frtGVIxpI3MvJVrkmltPL+w1t0FdbRIj/RPP10RQ/NCV5oTlbjn5lJz3D/WZRtqcQdibj50tMlLzDyFb97NE3yIqdGvP/6yaT8pejSU+QvpdF3eAHohA8rcDeLcYeqrtU/rfqBltA/9TZF7FU/iGdwyjVIqbpaa6X07ZR+NaVfo38Kq5sH7ARzNznzd+Q34ewsc3yUqP2YOImp9ipYoFhoIXqC+ia0Zesq16+eqg+pX8PRTKU/XsbMo4ld95wLWRvRexaOCE0nXGg0QZ61nAhG0PVNLybgxdv7bfiCyp7yHLBVnzyQkNK3FMM79kLwXeWVK0fSBHz0gOE78OehIHHBk6p6dC0RZEqxhZ1G/vqXlLt1y500t4hxXTWaiDgiNsWKX2Rboo1OkHTECehz7E2+vaMBpr59WDTCvdB/9rVF223KQLjCHQS0+JBxoqX75CCswxEYGMppTNGrErp4748n4T8WmBASiFBADKKO6BtZJS8hMtGrLn2uXR8yYu0gt+FUhLDy3cFKBBIkXog/uteCO+4hAphfh9PrUV/CobUSL+MIwgPwEItMy6CUDJkCr8KUYgW/k0rRcST2eH1H5r9wu0Yk80xp05UC8dnpIP4TFoFK0A2x/Mp/DeJbEldnrM0ece1sY20eSq7Nc3nIFJJrM3Y21mYWZRlCCLdZ/KGSFodrVBcB7c7c3nGjLcuUdh8uaPAUj6OGiq4kqod9o4evJPALuDZlLkdgdnH39kz082woSEweB+rAjMvBN7iGADvHEn14HNbhBB1n2g/HYU+up89JnzEhiFY81WiqlbIY3gqvNJqhFmmxjm/73qZAjMavpVTvHuofkak5hHERTlBLRHU9PIy+oEkcJ94EceZ4Del1bhZLzuIOnjri0iuSIx7ba8RzZDfyoPaMbuSmurE2Q9IiF/ncxsBzLfUbnjYdnJWW0+lxmPCHZzEUOqsXBGkVXUtep2fvYqhGumIvJ3GTNnyRVpSnFeZRW/0CaWhuUp6UK/t/TlOZOPbFML0kuqUHcE6n1CQ4vKHzj3auhxOVPuats50grRDIixufXzvr9tjiVgsilP7wUSLbF7fx8/hHZfBiuCMl9DhqjY3wIgpYostWYQ8SiIqxo1hqX669iS8FDQUf1x6tvihU+/G8PO+TGEgkV3uHB3H9s9EFY2CzerP30/lfzJq5XXTnJ3WZDB9Gh4lXXQKn1l72oOaKZfKznBBwSnI3aNevoLPIUzIGtwuFHV8hKUuvW2Vlbz70qeBjtWSMd1u4n8Y9Vf2OuD3qdxCFpdzmeQaHKn2akjdVPHdbt17wsfdF5FJKNJ6P+CXebfOvlMsQucRYAuciQruZnjJHpJ+ndEyYmAjHxIc/MyYi3l9cQWPxlPUoNrXC4SlzQ+SDA3sh6LyPqdj8AZ4yp9InuoULhOktR+lDBVy18IqgK4YgAmCob0Qe+Q5hSwdMqgzHuqmTsLZh3kXeRehvZJh3Efd1gKZyX+2L4Nk3Wzx3Oe4v0m8Yy6nUzUap64xSVxilxiwiJF452jPULYbdb1xhOA2zbGiOOLViVDqBKz3l3nLeSKPSPKPSq5Ndic4bY1Fc2BNMyqM/DguIA2dsthvUIo2scGa8Q8QvM6Hhfx/dyLhDvEv5o836KR35b6UcVKr2jKXGG6XGGqVGylLlNClasZMmIpu2nZtPHGf0HqdFLQbgzaTpGHuZnGNDrvW/d8JJhSxGobSFIdCn/Q8xjdyUrtgii4kLImED0WvXL9JK0rvDdo8DeHIt0EQucRKc/9RpiU5x6Noz8Pmh9b9j7lD3LO9H1RnaB9oz8GOhLpMf7qQPRnqWykFUAXG4S4TLxGxx20hjpf+fx3Y9lRox8tSxUaFrjUJXGYUu1J6UhR7Vypxq4HqtzK0GCplGTzZ/4FJZUfq9+n9tfQIVetUo1Kv1y4xCFxiFclKF/E514gTZ3n1GUQfcb1ukr3pbQcN2qmCIUbB/+gbb3uGhEoY0Ux5aWxiXX4eAWfq8m7xbuJDHwFn2emyF8GCiZaINbr0gJUwfXOLlkvN3EmSa4sum+H9E6yXJLfGkRK/ltR9XX0g9usTo0Xnam3LzLtbmjvQqjrCjkJDX51SPvFp8JlXD/zp/Y2gS7rnk1Pljl/1yRlJkNyHbehypu2d2TBpl6HDgBrEcYic1N+RhlF19Ve0B2lr8HBmbQt1T8mp3hvuK56bJi9NBRTLL/I8MdwDwuuJUx2nb413izxenpgCZcHOzt7oY0Va8n1aPpyHd4N0WuS4kD5mY/TFtXO3ReZd7/x25JKg9xy1+qg3/lZp7u/dN7odLW8QkzvV1UmFCzEm2wKdQSOtmTy4wJC/HcfQJ6ngWZb1/ccX+hLfH5JGwgs4V7QnMTO1O15LfI8cHrhi8jkDnS7MvocMo9gTHMiFKxTFVuF6yWYjmk2li26rv9Pgwehf19MRaGfILbLUyXqe5fgKtFjTU7qweRgP1e7dGfqg9y21X9HiHPxo+q9C7df7f5NUWNs7MWayf4H0MfQp/LTUYnuIzZROSZE6cKfEPxCMjoA0zqn4QPPpWK9msEOFzaocrKy8kOmsPS2JaYLTzzd0JlpN8id4c8FS4XTWfWuA5POyq+RDVLoPimXdXOEdMpqwBeYh8ejcOkfiIyko40u93Dr3xHWAPcQN9iNz8Y2GmxfQBrrXG3grYYNjSzjKd6BhoUkZatmARKsNTBqM/Ptj5NflaXZi827hP4eFySLh16bdD9bXJV1y0wKSmgG96tT1VRKG1icumduss5G9HYBfw5s36MyM4QgAkAoqLloBIoyZxJMzqPLiy6QS3yEajdavRJd++2LvgIGMKdxSyOFV2dnu8KcWkgrH8vyGh0RIJ/f3C/+NxMorOtDcvPNOZ9r80OEo2qPxfGxxBhQqNQnZEGAD4NyywF3wct8UC2S8Pf2iouzw2O9P76cxqu7YtboOr5EVdlEtSviB14Mu+LpDRe44MEjI+nDrgNRouMM6JnEejvyQy4pxC74757bhvqj4P4pVkPfGhGJNVuzmPSLHfXICrW2fU0fv04iHFsZFGJ0/5XrW7Jj78FRCewxyb3yGr/LeYcoFB5R4WYwu6WRgzU1/VCBSo98L9Z0vrV5YyAHMOMFH718Bt2zHniXRi7Bpjpq9MEmOyS2MejVbT0c5xzMDc1I2TMvasaLVDVzpMnZlNeUnsyDFgZQBYBweDlWFgJzwz2J0e/1XzgYWimvpwXOG5VIFW5tCm5gbLj30c0hKq3310mzV8GeW49d2ysrJM74k5GdoXuEr49r6jueWwER26IKFbFXf+CeVg/FLKeNH3ZZz6aDKjEXaO+4BpLC5M6K5NlLnQWUonoQB7qu0WF29IyJPLyDgW3LzUSoOGFJAy2NlPobzgVpyBQOUmMyntgsy4ZCNmeFB0QZ6FyNg9In+ydJZ+KbjFLKkmRpiCb+tyoDkE99u4iQvoT+FOCNWZN6gpAo11d5dhybxbiUTDKndblUGGhoikXTrup3+DJht3AZdIkm/LwGfR8TeI4/Q59YdGlouzZ/G5VmUNSGZLrH3+O13nVlLs3BSTnSPkmU1s3B7gqsWrLMzyzKJzdP6waPU8RGTLiuHKiPozPSPJqskOQsMJJOPtrpppkP8mWZRopEd31RTCBmsLQNcSflBbDEELZuynHp8jYp2onQUOKuZ3lPJNJW+7H2nPoJexmwkXz1vO8Cwp1itTbBMVdsG6ZD6zO0vvQyMPEyFELFTPxId3ddxGCeKbcyHiNBvgq2a5s/87Z7QM0toG41qZDQjlcAsONLGsEUPxMCtZfXdIcncTvdtdSxdbkrR1tdFTc21UzkWH2QDPjLxwH16geRWoBiuRWgjvibSFkG0seGGWyS8HxXdP24yeYtZTU61lVelm/+HU5sjwpLJcOiKZRhRkhUFBliUpSCkDuEqbmOf1O8Ie46S9f6bBrp2VYtf4xqkwj+krEwetY/LSoC6Pil8mW+5lVMvxe6AFmk3nKrreVXAA3vG+dS39Ow66bLYJwMEI6dknqST41jUU3f5SwZLCGdDwedNmDr/ZKPMSTvoz+pTl1YbwHNmxN5F9tg0A6rAqgVP9jGuP3YoZ7e94fag739egvQQvlvkVjfAP1t9JiQHVv1dU1/G9XkvEHRQPyue9rqXnJLu1xOiWI5mywco4hWgfU3B2Z38o8XXac9ziJBwssF98xXGBr7XjKJbGBhMAvW5EhiQ8+DpKDlcZLGkSCCeiCaur5mXKI0ms3WL5HUzFOA3lBZ5V+GlRBh71NWeE+xE2QSxC2ipuXEhIuq4P3wB88UPpkcGGOSNaZl85LRcvBlpbK9sep/lbCdm42EWHNSgtBOLjZf82SDDpY1yUxC/ha5fHqN74sFSfWd95MLQSd+lP5WWYDRigzCyjHPU+zdccbc9QfY3h6wuO8oJd41H2ha+WsYI0/z5xAn1OSSP7Obv18vLKn9jSgkuxtjUM6TbB8ppoUDkWzFztKHrwbIKmuKsGFBbfBp2qRSRVwNIAElMtfni79HWudQVhtrR73neseuyAcciHPz2pQ5N9r5wWIH+E0MPIoF2ATV7FMUSghqD5WmGAofSVmYHyseBp68fKa50B8e5a3OnjknfbnJRf3lAllAC+z21sVigkK8JEw7qku0RGghuPGdM/C4jP+iIun+HTC4FZOE5qQLzf1/CHzTHAbs8rOAo9wb28DFdokX3ek+FLPEpjOEfLDmIs8CdOq13hPKHH+xOwWcMIT3HbRI43Ie+2jNsl14R0hzq40Xm9D+UiRLXQgpVgYx7atE7etJC0epvmz/Dy0RSewXot6hZMZNPidqtEyeoWC7A5cybqFqTKFILGIg/nVdyn4npZR/wiWbEyzFCYwRp7m8JOhEHOJq5iBU1YL1WZ3t6WD8Naq2nxRKMjZuiqRTSi2ItAJkGJWQoa2Oab+5Cu55LCD8bZuxgXRYYCbN/XCDPYpOrLLHUx3AhI+/ebk56xeP5+5kCUKfiaSk5c+CJTSC1bkOJp5VKDnDyCoZ+j103kSYIfFtrPCMVI31ZaJbFyphFDCfUwYZD5Hh6O0sspZ2osNO+5YIwMxUUTrCQsSd9kfW6WOnZVefWFYBj9P4WujgNaOm0cJAPwNievYCeC5Wxl2vKcs4gteZeH6aoBmQYC6g0crlFJGoFT1jSDs4jNdpfTTkqZ9tVSuidaiN2+vIF6+EZVWPypHwTdM9TIPnn5liDUtkccTiT0puwjc4lLbOKIUlxKs0luMgb7PWibwC2ipuFTgV4Cz9TtgcqFloUBUfcEIQD+wJqNpm2JPfoK0oikE1/dY4QGatVn28VzRYiKXTmXULhsSVKppVWjsQM/lYlVCJ7H9CqncfXi+AREkmkD0opCj9uEPyuCVjTFnzVWMN2nKV8BcafZ3hpWAA4s8dPpuWhzin1RN2D4wfsWdfehfx/6ibbAEdX7h51RfVj44oKGjmPJ/YNrfoAN0bdDGtYAugs79uPrMu6+jHCGRwTnYn0RGvwy7qD6ItIlCo83UZM0iQ/+ZlH3APr3oecBVb00cE2fV9rkPNnrqgy4+ZHeEyawusShgHniSxWjQ6novwgxAX2kQ0nZWPhc/SGnrEl/yIHLMvOg6LiW6MZFC+zokKvmcnrpuIL+hITzr4nU1fjUG9M0lCUZH4rJ6HCLce9P5HR/+OFm7Jex1rxnH5UBB4RDVr4MrmSPeOI1M0YN84CxZfAIRXDSL/owAquLXauhFk4M2GKWrCalqcQjstdSU2Y224qr5fUWoIxlm+nvzI6MhCk+K3N4nsTZFs4Ba6DKZ4cpE03nlNVF0AwFC+SEq8Y8b3N4ANuiBgKlUoPHtIk6LKx2ZnsUe7+G+BXlwr6IzkECBdsFxWHx7SjaoPV3AsbDrhgbIZarD4wTBz7PpNpnpi5Q07wuFXzMvNVWdagasmtLsJFp16r+NrVMeD9wLYN8DGJA7yeupR9gr9fJvQ5JjrZE8rZPEnR4d7lqHqc3Fu4QQAg1yKTQlbiEQJp4JmhQtROhIBVk+4Fmw+lYLjuhOBS/4nQtRK04L+V4q+IIzt2Kzny4HTykZXtbF2RorVqJXT3f4ztUDV+JWplQS+y0s2/GCMraXEtvJDBib3JaU8GHs4RrvAQhccvAlFnL4eiWFswbsbvh0YTtRtFqyJs8SGdvMXiLm7VnTAHDLaP1QuO67XMACEoD0liGMDev9mjYzUuIC/tyuYiSxd/nTpPgUsMySCCgiUkwLnp+uUlS1Wd066zO1cvvZ5rOAd8bs9McvjUemssUGS2sWcNcqiHJdju0Vn3s9euHumG08Cnup1vDg2lJXPhmfAF6a3oMhzMmpFc0jFMa+93QUxvrc1pjE8zGqBWWfpxDC+HdT63uNFvlLA8wx89ttSQXBeHNunXFVpUxw7OsE2B9NeYaTylO12kJD5OBd3NASAVOOe9SEqNFnaDJejuipdN0cTsAugYHWVDlF40vTwnmCTc/S0+e6XmSLDJYz/khyJFZgmxcZWIJo1tQNu1Gk9nPsIc4zlhty3e6Xh4QJVOA90bKT+Wia/L/j7b/gW+qvv7H8aRJS4BAAhQoWrRKUbQ42QpKDGgRUuqfYEppC8OC29B1UTfUXEAlFUyDXC9B5tThpohvQVHZxAlYB2JrGS3SAWInrRTstOqrptOq2BZaub/zPK+bNEXd5/39PT4f9Kb3vv7/Oa/zOue8zuuchM9IuIkS+fx6kfjCi/M5sKqEIcXLlGm6PEBdvmphL+fJBhKlv3P3VQZMLxkcF2wd1WkXXdVizGN89ecbhxvqHkSJV3VQtc7IBlZDU+wFcUx9vrwOX8AEVptRjHEx3gtQ7UMj0niqq05iSGoca1gnjtqZfYy4Jsn1hT8ynZ0FJg4da1bymG1EzobAUkkVUutYWqGlzIQpsASKUsoNCPpGy5Qq06DqKsSp3NlW7NHoXm+m/06CZutEhMoD43PZ9JhkNBKJ0GFTISNMbHv2fncD0UWhteiyDjsNvKHS1oYAdVUXKsKBPMoN2EBN/qQDjhkVh4sHXulHQZd8qxvzkKhS3tdKrLTM4tqAGQgU85wURPZgtkD6qhyubmAdap4bqbBQHJ9GQ2sV/AHgGUugoMDv7N13L8RUMNlrtFZJUP6ZfAau3XjYpkpfwUhIzKE+KcdAFkeJE5Sc9BNetic8BAE3X0koP8wBMFZXL35+H6F/OB2VxcmCEkpxbQARHxin8l+Dx5RiBjnjg0NrMap6bMwT4hzlHzIUIUJqCLhrHY97jrl5HpRl7urlAXdVYLE2Ql0LuKLpSGBeNvQyL+FKFKtcblSlbmAgkgn4gm2Y3VdzA2QTWz/mznCXJFAl5NEkHOxB+liRxFdzy3+wNNgbH8mXW0/C6n89nHrW0+fX38SkezJb4DdSrCIvDvW1nJUgg1m3yGxw1UyFa1OBGanSAdKNCzjNPj55EC79cRzt5RcOikh3AgV2eFIfoyB9SFswQ7d0M0KRkwHB0x7ApsQvBapHSMBUVyGU6P1MNl6BuzChZrPKeKYX7xjqy0lgTlHc8l+59mAUg/NdewAlSgEbkTnJJmRwhab3Ao2uEJF0Uh/ewvT4XdQoqiYTErTcjEC64e5YETFgOige+ZooTpw7nYWkeNoM1HZo+UACo9iUaSXCtQFvgd+5ypYrgw3MLCfoZveHwVFGq93cKskZfHa6S49eKiOCFxrdOUflQVL3oPtG11KMNu5koD4ovvxKXnf+jP7KJPIiJ1vxxDhLH4UHYwrqjvI3AXXdZgerB7j22DgL2z41ethH+TnGrkpU3CUt7oR03VEO24vEnYNxldRaguyTuVlnUm+ZMYlBIIAQGDWK8deYqRaeKaExL20BpdcSZxjkrAn42xu+Gsj0Z/GuxTulnIf7crqUqYBRpooGhrqTylJUHpI4lF6aHYNSbIV1xFBm7ycSAgNrc63FYAcuZDjLj7ACNuuCc7zKsRLyCjSeX9rulxkgY0y9sZgxH8Uw8MTM1sL5RNNcmsB90Wec+3qeWU+DCTPKeh5NhlJqesWd4MFvKYYJA3DhOTZJWwbgTRe4Da5u168lrkTPPqYGewyhcpb7w+UzjfP4ayThEbGu1ydQavj1W7w=
*/