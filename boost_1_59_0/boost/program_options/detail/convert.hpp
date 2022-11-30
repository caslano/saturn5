// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONVERT_HPP_VP_2004_04_28
#define BOOST_CONVERT_HPP_VP_2004_04_28

#include <boost/program_options/config.hpp>

#if !defined(BOOST_NO_STD_WSTRING)

#include <boost/detail/workaround.hpp>

#include <string>
#include <vector>
#include <locale>
// for mbstate_t
#include <cwchar>
#include <stdexcept>

#if defined(BOOST_NO_STDC_NAMESPACE)
#include <wchar.h>
namespace std
{
    using ::mbstate_t;
}    
#endif

namespace boost {

    /** Converts from local 8 bit encoding into wchar_t string using
        the specified locale facet. */
    BOOST_PROGRAM_OPTIONS_DECL std::wstring 
    from_8_bit(const std::string& s, 
               const std::codecvt<wchar_t, char, std::mbstate_t>& cvt);

    /** Converts from wchar_t string into local 8 bit encoding into using
        the specified locale facet. */
    BOOST_PROGRAM_OPTIONS_DECL std::string 
    to_8_bit(const std::wstring& s, 
             const std::codecvt<wchar_t, char, std::mbstate_t>& cvt);


    /** Converts 's', which is assumed to be in UTF8 encoding, into wide
        string. */
    BOOST_PROGRAM_OPTIONS_DECL std::wstring
    from_utf8(const std::string& s);
    
    /** Converts wide string 's' into string in UTF8 encoding. */
    BOOST_PROGRAM_OPTIONS_DECL std::string
    to_utf8(const std::wstring& s);

    /** Converts wide string 's' into local 8 bit encoding determined by
        the current locale. */
    BOOST_PROGRAM_OPTIONS_DECL std::string
    to_local_8_bit(const std::wstring& s);

    /** Converts 's', which is assumed to be in local 8 bit encoding, into wide
        string. */
    BOOST_PROGRAM_OPTIONS_DECL std::wstring
    from_local_8_bit(const std::string& s);

    namespace program_options
    {
        /** Convert the input string into internal encoding used by
            program_options. Presence of this function allows to avoid
            specializing all methods which access input on wchar_t.
        */
        BOOST_PROGRAM_OPTIONS_DECL std::string to_internal(const std::string&);
        /** @overload */
        BOOST_PROGRAM_OPTIONS_DECL std::string to_internal(const std::wstring&);

        template<class T>
        std::vector<std::string> to_internal(const std::vector<T>& s)
        {
            std::vector<std::string> result;
            for (unsigned i = 0; i < s.size(); ++i)
                result.push_back(to_internal(s[i]));            
            return result;
        }

    }


  
}

#else
#include <vector>
#include <string>
namespace boost{
   namespace program_options{
        BOOST_PROGRAM_OPTIONS_DECL std::string to_internal(const std::string&);

        template<class T>
        std::vector<std::string> to_internal(const std::vector<T>& s)
        {
            std::vector<std::string> result;
            for (unsigned i = 0; i < s.size(); ++i)
                result.push_back(to_internal(s[i]));            
            return result;
        }
   }
}
#endif
#endif

/* convert.hpp
O5f9nIdtfyf+mPVIyR7Mj6STT4X+k6aYwFQj9vn56wvmQwaiNveZcwHjkxone+pG6culA5GWLV/DWzM4b0/7FnzvmVuIP/Kh0wiT+AMsEBvUV/dqLtxLa1gLjcYIaKLM4qdb+qgjEGhZyXHJLND5Ap0mAQNhYewqqS5dduCfXhNSKCq7BwuZ04I2ndu7OrW1btMsYPjmIEcs3k9EOv5/P9HYC0sY8b8B5eDrVFahjgWUCuIVdcsOedn2z+83VjUzKqytV3HVHmy+ZbRZ/WyJECsdCN6SOS+1TniUTPk2ZcX28wZcAfS3TSTHJ0dD8lx9qldb9GYiQHdiw9idHIwqxtzXR02LdSgpJkj45yUHf6eq0wRGmT90DfrwLnZl/svncNgaJXpL7usqSO6FUOK/FhcbzhGJGEJMG0cMWOoYL/av/XhRfL2d2x9UeoY3FNXuhO4NQlS4YV9/Ue4ZH/HONwXGSkGPMNpeLfkBr7/RQ7yNenj34r4YiV74m74s0vhgZRZXOs+uAXSl9LkdMGhoSF/C18q2FS2DuocPxTacnUuaHnTaj7WuR6H+7V73Rz8f5tHxgKY8ktk4LS7Jt5D1Ebhi5J0oFWS1ZoznSOywKtDoHA/d0B08jeUrtuZ8L+dYKNkh6AAjnwP/Q47+unHoGnNzm+0q0tDDCXsxbo3FkIkFuvErhSO84Ez7N/uGQXck5gD7mkw+imUBVBJKzpQPAwwviLPKZ0RkRLVuRX1eWzO4zZ9wwz4awv9tmLEUC3M/zvLpjijvT351Fv9Hd4mfJ2iFRQ2BkUMMawZBg0jRkm7asGZThOrU70350uhxm/89oTqnxNpb9w2qc49eZ9mLORunD16zK4R9COOrbb8IszXx6UvQ2jiVGPxTg6j3kXA0Lp5cl+DAKHbIp4punWKog/biX2ZWQfbXpfI/fmZ9fzgbpI+vWyobG+W0maGOiA2GSh3PrB62A5K3yY1mkM7osYId3DjDpjHPI0ALg0RfOmHzMu2BGuewXXgvvd8vih4A+TfaOA3ZLs6dkjvtg/1m3/+WhK59jvTLCAUZzEc6fB7J/87bzdn54cCKOXOkRfnbf78Bb8B3Bpxw2bjOw8FY2MEfeFb/ZVRkp+29vwrMDR/RaLz/0VdwbQ5D39WlNtj/zoBW4nwapME4VV7O+quS1adaT39TOk7y19F3NApKCxB0yKhXfzsbul4R291HvWR/JLqWo9MCvLjNyPXfSIggGI0n/nLBznqQNiv/LutrELL36YNW23HLZ9spG5tecQpZMTV0y1jf0LBbOcMxUTpfkW4lmKgIMZ31eVs4vMjB/cxIEc1vUMPYBrmj7qTNwYmSV5UcL5bobvD94kWwzpUYB0EA8XULQ+jOD95PHGnDaGueqELLG9r9vJWn+1F0H/ib3evLN6Nub9xuRTOKdBIWNEla3P8GromHS9SdoFSEf5S8zRMlRHhcE4m5dMd3rP6Jsol/xBiOTZYshTcq+JcF3nyp4bwp23j2UB6kXilGj4i6LBx2UgmVoqKUJv1Nv0Zxl5Z2qRK99mOH22tsxaM1zkNrlyEm4IoE4LDRex9fTTu8DA2vbBchu/yHr7jAvmAUAZgmgbIGYZ2Umhgid1bmwdIdYVa7U7q1E/ObPwss4ICEKIfaGqmX12P4ZgJnTRGJ2knNxPME7St/DT4hKut6oBxeX2f7FlY0+2CMgQ4KcfZPzB30YHxd7HdpczFr56CSyk/W1Hqnv75nM4r/GCPvop49fZQ9JiNnRXVp/fORMf7NeI20byKGmOQdulJCuQFN/J7d0tLa6j5ScSll1ddO8dzlXQzxhUT5xmKbJPhP9EszTu4SH/DeAILEyQJuMOCpbtEsm9eB5pQpWd+NSJbpTn63rh/flmGEI5uk0jZuASnt/RiyofkXkfr66+t2cA+7fU9L/OxgtTUcGIUGjjvESmikjOkQcM3Ad4QimN2qqtDp8t5QkBlzKtXcgRaUPmpzzWVMOwT08sSXFeyClbmDU+b/uObC+HeBHGU8Itr0Nvz0VCQX1wMQ9HwQ+xakLIkqhVG8w1AUVA8k6x2UN3BU7MKrCRvFecEhGKy+1r8MnobpeUkzvxOxwq/d4FWiiTQk5/H44uiPEet59EqJDIMrAeH95hOf/AC6P8G1C4jdneX3E/8jfJQ4nL6Dfdf4qipYcvJnP8SdnbVtT+qlSHPX/lKOTIjp8Ecuxdi1UNRtzXjSVI2WzTaawykVGbRr4h2ABMmi8qKzN7pXYyP0Rb4WDOdVyRrDcKrDK4S40SPfh0O6C/cvYrz3frLAdBs/apjMU0jDtviVG3tpE5aoSb0alhUbtFZMDNXl79BcpEg8QQB0DXPQnROc4u1ndctaMSqGRbalTqEAuXWRoznkLCg+JDw0mw8oqhSkS8P/lABDFTfGSLz4UZqkusdgeMjxiakUe+tmfWdMWrfdZwfRdUXWM1Q+FPe9h4mycQYq8kRR/ta3QWTvIBySUz0LG/9RzZuCexz4k4Yqpb8Q8OnDK+1a3tw62dcN+7/Am5X3Nk73CWDMu1La9VfgxpyY5xB+PpxjVwPZKgAMByeMtw1qgqLUY3chjbACwIlJ98wmaHfClvj65cI3v+TDd+ZalMd51A/0QAHU1MyFgFkWWhLft6mBLtUq7b/n5xx65DhUT2iSJ7PQCAFDwd2xkl6taBTSfBSdoJBAYEoFFDv2wo8YVUGh+rJaTkREDis/Tb3b3IBs3olasZ3sAbCf+e5rqbG+RWx8PVoEYuSmi4MpK/Ku/Oqw+LaZ7AqkriuG+AMmVBGALMg6RCcwVBqlvWc4D1SlEVhEMNxjwLjYHnPN+2RYG9v3cOS67vlGrN578U8pKJA7RyiZN2zhTuwN9sqkitPbN1vw74oq5tYbO94lH1q1vgG1cJbK3oz4wMq1bnGUm1+vvz6bPkTehWfko5Rt1U9AA7p9TyXHuK7LnxJQmklgZsklrYhGAePXySYlU59+P0kPvE/EQ3uRHHMY6GAtjROfHDb+CvAbBc9r3nxVfXwpnd3cCEFLhRv3TwTmdvxtD7X4aRwGm5sBGV7K7fPNxzN+dreb2CbJgRWXRMHJQEivasS4jfnwinyNQ9/jpgmYNPDyoapbkcuYwOQO8PYrgoXLadvhF5vd11VadSoWSDQ2zMrsGDPgnDnNYJM/asqKhCDvy+WLPfiNtPkIi3la9EFn0EbgcT630RFW7l0zgkPfVeM/LDD5wYEvJk1OWJcaNbRw6OD31ugXtruoWG3f6FlBKGKisZifmcOMVjVAVUXF73EceufOV+9kILc28CpZJ0GcBA9/hDYjOXcl8/wY0BhSeMisI5UaJ0psEp9AEEByaRKX2KfR6+ZZ0Ox+kDej88WljhcVDqyb2n0jecOEdWjzlw6JWIKsDXn+N/nD/cEVidWbyjOKvvHiOfXh/VMsmUKLtMyj/9+zH37b2pFwSHKSaXdzTa+gOmBUkDhnLZc0JdK23+OhC27A13y1vlUFLaH3wxftp2y6HbEYqGpdV7kx0xK3JKqcYeijhT/M82/tX4ILH4g/9Hpr44AvV6+try7WP6ETE9R0ddTBQa7zPVAafMibgbskVoC4x/W42DOldj72DtFnEfEcqPPdm9iVXjKcsF/Fn3uaIZ+TSOLP2hL5T5fbHXB4JhxUtd9+9ziXKmX90VytJNh2/AYSpeE8J7kXaqpe60cxjRFCCihdhH7uBLWMQl4eCWW+f6ToBlAA38eNC69pOrp6hz2/2WSDF5lL9kjiDmFi+jtxoeRIjO7ylfLG4IsxKyDWykf+ueZfwx/zyWQ+D441grVJ4HcrLL+Xk1vzbODHx5YRbMRPYYjDg9QAByz406D+zGZzVUAlcj1ZAIfPyNyNzyzcMSGVR9fgxxeIR+n5iZN+dDUw4p3sNdoDTe1Tz9txWdWn/boO7ebC7My/U2xLF0Le4nl7YGAIE/Zu+CjqSWs6evDH8Bs0AtiyIB4Pz32rOowr2ptmHOMtIVYHzoaDpVCRS8cQWAWFlil9CeJYciEw2bJTqiP4Xp4xOfCvZyrjz/6S3qGZ1+9Ggyqh4bi+PUdH/6MiHTqPHZor/wZFLHwq9VHo0J9Wp5EmgKz4Doeygj9tYLx//bLP3L23GZ6ALJOg15LTipFvMD+ocoCdwmOOgOD7RHgDjGJ5TOHnC4T6Bb7KqLH6X4PqJR2a7GtPkfi1V1lCD1edPO8UoZsZx4QwXskwMBpDQLTz9eU76ZQhDrFAULHxGd3nRxScsZvNdNLVIWJso9j6k27bEJDuYkORtNQQ1TquRCfBnF6zjJxuGQxBxQThj/OXyHuHpPW8V87ox3Nf6CsaDHFU9t8osOr7B8273GUSH8ebd28OUPFddrb3HgleDGWf88+77CGFATnPyEAan+T4MPAb7icdp0Bg2JzyPflw/P6o/7Ye66coxnyW95fpqTyAU0Thdujvh11BJBQtQq542N6KJajuHc4zJTQfGSMCnTyAohXiRfxH3a9vaASNkRwrPJnpRB4hIIY4O+74WuoUbcCCkOsBQZ0938rx668od4N3uuSH6rnsX9BorlTVQnQeY+yrSz5KA/S3xOqmuzyxWoDGe9qnm5TyHk76Xo1Zz5moB6hBnq4iEvM/RMCDH54sCht8spS+LLIy0gbxfOhnvZzG/Um6hY+1Ej1g1gUA5A6BsyTX636/68lIszLyz5LKq9sVhJT5QeydwF2j/vkYD3QU1LEJGif3eA/tItkSEqLTxaJhj8pTxlcguTR4ee2sfvJ5oMUCYmNWnWYO8yXIpdReV6tRVO3SnGHpBC67bebpylDQ3Xob4vcOYSnluDqJp4SZyvmf6d1AJAjzhbhQgPicgHeUXGZOG0OINRLSHdONLiTpeNPzSgdOcwb3JFZyn4DHVjB0l12o1SnkQRJUpFXfJGzOxpZT8UP20gfqfbFobju89HQNaIGurFUyLD2B8DX+BmCoryTYHAGP0KzHyYB0tvlC7qbnb2sYb4FuPe0fJ7CjKCk6jpKCj5H3crfTRXVOPFgkKJgT2RTMtTxaQ+XgjV8eWd+SRGGIAxZ94looHRwA3lWFcu/LRpvPvw+iXj86yRno3p/FA9seJ3co8xD9m7aRjeHVTCwzoWMqYeC2XBMaHdC0gLo8xXnJjgDC2pOZ3+Xa7rT5rVfyqBdGiZPMzAzEi4QHj/NnuX6j2bmmrTLcpvjT0/Z2lKgUrHMJMRbiSvL5tiNUWAESYBSBADtWU8vgmpfLreHftn6NUjHMh4ZrsRIs8a0fJ7/iPBybsqcUvjW0KH+VSi4ZN7t61bdAwWHnZtW6OLVj+m/oHPnwCC1gq/W6iDjNiPQLI+Hgt8uPOHKY3CLfM2RleatucfiwiLAC6xxSEPIPuy3vPhSXi2Em7Z8n2Ms9q/7CMOLgBaBwiGM6mvR0A79QQk6xHHlrQNPjxaq6+Psefdx3287Z8aZ3dZuDVJG0AC84xY4P7GEyaLr9A9cSLfXFHtU/fzwwMb5MAmsvTQaQRIwF2c4pAWNP+KnOIx3wEPpyeixAncu7s67GYnH/utf4fZlEzIcfLWs6VyjUzr1hUuqw60XhIOL1K/mBeR9MG8E2sCj+2BBBHZpq1MoyF9fVKe/0Hh0V8sq1jBIQwfV3qeq+Eg7AuYMiDl1egWQ5fTx8+jiwuRj12cqcOHJBlBG5voGsP2waiKflNIh5ovzDoEKlwrjkgkMogh+BLLzUdgZdo56uepSsT2uqYDnE2goaT2Cct3Vm09O3xR7CIJLxaLJx+DMj71SkUtY63Ua7NyofHVdO96aT1IOZKWIUm2CUsAjSBn1fQT/hGFFmtITfQccojLIcjrDJFLDapM+HKPJV4Uh/5i7WDI1HEhJ2ebk6yS2xkMJhKAabAWlG3suDVwNH96/loRYjuYXzxhSB4CAwZWgynD2TWMp0KuY2Iq7GAq7oQKK7hjDUZxM0GZ4V5JdGuHc2NJSC8Dxz7MBqVuNt1GuqjG2WE/2UIISc/Eb3Z0bNF4WMbyE87/3hBG6moxeiQLzULNIFJSQ2ur31dW+5tOHafhALFY5xiY8F++zW5mJyDEdbtdbW/l44j3kXvSy63urwRbw3cqVKqt7ZyJgaYSa+8uwg2vmmAFuHX5lKCewZfrP1Jmi6aXZPuCBKzg9/p2yAmSnXCwDDzxS7pRlyfLGTQ/rNBUtlCBFp9ynwhbmcB/0YPv57vQ2ay8/buLatDRaNcADZBvWnzw7BAIaHk1RLqXfajzMJetMBn9+usPA6ROZXfU21qBZvoE6kQOQfE1bHOEbvZt2flyH50AMuWNrJNznrrNfucouXLuiDzc3zI+YQn8K5CHEQKTF6kT3GhVzaOM+ZsfyKpzBSSUDkq0C4hbht4Dh4mqjSmxYCcM2N0WyPL7tX1R6/9A5jx3qKs5KlLvsEdQcE07N3OIwBwJWPbyVKaWdHLquO/lyIcbC3Cmv3KkGXiGOB9ZhDsCZQkb4XuA2yUwf3LhDmLUqXRgi4fePANaNzrUMvM5f2/n5VXenx1aiZhDtLrQw2zAJO/hcEGHITbkT2V5z1p1PGZZpqN0T7yvfp8JYoa2KmreefdxZHQLyYqCRAWjXpEij8tuTXmy6+fAHs0WH+pPrjpFHHoIr1Wz24/OW+l2r9sSCI45Ub+B3tGdr+hj0PyX8OYyrpALZDbinefQQJypG9fCXIdrk7zY2Cqd0kOdSwYKpxIvL2Z57H5DuTObitDZ4AxtXZQhqGrD+OGjgIolYgvk959acBqM2+Ds00F0Q8dDQx79CN9zKWUQri9aZZbX72RQ46hnx/3dHH4/44teDQ+cOLQ9dmsiX/R98wQTfGc1D7OdhhDrY3I4Bp3g4qRjpIWcmfNWrhgv+iulrBcTJd7FN8ufi6fNXByrGNixJQHXZ6BoCvLIvxbvWp33qRMveAOjx6scdxvCYUfI02BOWwBiitcsRJWYrJc3jBON69K3L47/RRoB02QOUZCBsz7Oi103NTwdDRhNAfwn5PtcfHREeUEog1ScrBAwjxTTegPYjlVrDqbpoZZca2ta8ZlkQ3Vy+4LBxX9xJ+icH6prsrLFWlNdVF+iooZEvwZZOAwdFPGnvXNECN/Rmgn87axcn1Y0Q7c3JSQ6YFmIsBeD1HbPD3F7cWCpzeg3bBMA2CDLfgzXts7sEsj1ExQzHjTXD778Co9f7Pt5KJxvlvm2I1cQmXudFD+Ce2iRBj0hhxgdVr+I2AWNsnQNL4NwvnRiiWdKjhp/c4E9ij10Yc2guHp8CHbPlF6Ow5cn+PBWQwxju4BYodo0qaZ9TxoADGR+i9du23vLckW7u6Yli54keHPZPG+opZG/WavBZJeoHZTR6/d1lBdsGhTBSVtIqqFy5zSfweN7eUZzCI9jGsj4HtOEFmRx1QvAJVn5SQqQOcGdovIFYEW1rLEzrOCsxgSw6dUTpnEm8xNF6n45XmfNvwOfzU9eot0mH1rX87nyz5BfCvp0S9wGDsoOpXO9XT9DXG/q5jOOEO27Sy/G4HFz7MXBWQ5t2KAdkN+q595ovEvr0TLKFd4P+D9AS5hdB/x0u8LP7NFLQAPIG8354cuYm9/RzGnMBsi1RXM7kCBu7lWQq5u8V+ALU+oKqxNVjh+vqmXcIA
*/