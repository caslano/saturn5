
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
TWyKR9AZE7AZXsQWmIwtMQ1b4X1sjT9jW9SxHdtjBXTFGtgBa2FHeV+wLyHnPnJOlEo4GraPfrrN31XD77A2pmMz/Du2w39gT/wRPTEDx+F9nIH/xHn4k2znn3EL/oLHMQsv4a/4Of4LszEbS5Rgf2M1/AMd8AF6oq4k9WAJDMKSGI6lMBKt8E0sg8fRGhOxLH6A5TAJbfAzrIB38Bn8Dm3l8/6uTs6HcIJsH+W4uyXvY8fk8zEBHfAMPotn0QXfxx6YiEPxAwzA8xiCFzEKL8nx+BFuxSTcgR/jafwEU/Aa3sHraE1bPsVy+Bk2xhRsip+jK97A7ngTPfAWDsMv0Q+/wnGYihtL8n7S3rrIefK8+fH8OfGC8+GZnYqWA5exeSTfnT/X7YKehOS2LeS11Tntwn8zhjy2xfy1N1FQzjqRUOep1Tnqu2zfvHnqaEJy07nHAuqWNxddcB5actCSf1bnnIuXb7aUX84ksmm/hTGFTPlkW1frfLnkFBlv6C5mEU78jTvhTUQQ0cR+IpG4RWQSNnQ6cSI6d9ByzNqkTdqkTX/19Kfk/yc/+v3/xvy/V678vz6/pc//v1eZazvGseIt5P8jj+Tk/ylapLy/Me96pYT5vKutYZ2TA/7D8q4bJQceZ8j3oORdD0p7VXlX4zXPgvKuNu/mzrumx+fkXZfH58+xesfnz6fWy1nW1rgs81D+HOu1nGWtjDnWnaZlrvr5QaZ5lyJvS4s5Vtm26t8Tz86zrdNz5VQlzyrbP4Bj3EKeNV/uqpLkw156lnVRmXHZLak/gGV592W27MuehIzfqc/rxB2WfVnM3xeXfGzuPhP5+xXoc6GRpuOFEcBlnGfrItbhH5Y7F8rvxOfKhcpY3bK9Vdtf9sc02f7qdtrLePq9pJ3dZVsMNm6LR8wTSxty1ZksdR6XOg/Ltln1jtRpyBM/9Gu+sDxxdp78aaaqnZJns/g+EC159Y+k7ZeJdGW/xknbDXnfh267hbzvQ7c7E8NKWsrZ/e/ed2V+HPD//hxfO32O78CFi9uDRo8f1nKN7w9d3isV8ORzfMXNHUtOkO8IOTnBC3lygi0kJ9gSrbEVGnM7tlJuiJRT53YuyLXOi2iHV7A+foiN8SNshh9jG7yG/fBTHICfma6pyue3fJ5fyHNNdZHUs0zqWSn1rMLWuAZ9cC2G4jpcjBtwJW7EdfgaxuEmfBe34DncipdxG17H1/EzjMEvcTvexjfwbxiL93AnPsBdaEVb96Ad7sUGuA+b4X5sjW+jGx7A5zEOJ+A7GIzxOBXfxUV4GJfjEdyMR3ErHsc38AQexJP4Ab6Hl/AUpuBpvIFn8CdMxCw8Zxo3XT5rsafsX2v0MDOudll0l/3QE+thL2yJvbEL9sUe2C9n/TRQjh8z678h6/sSHTBVjpuv5bi5jT0xTY6bb+W4+U61/sHS/l5m1u8i62+PVdAVa2IHrIOdpJ7O+Bx2we7YVdbP/pfPQra5rL8irpX1D5D1D0Q7HIo1cBjWxeHYEkdgV/TC/jgKB+HzOB69cTqOwdnog2vRF1/DcbgbA/AQBuJhlPHVOe7kcw8/knZWwi3SziBp5wvSzhB0xFBsiFOwHU6V7R2OQzACJ+J0nIkzcA7OxPX4IsbiS7gH5+LbGCk5o3l4AefjZYzCtby+ozs8vmu3jJ/+WK7fMr76//w1XMZx/9Ou4xb3N7kf9VpuYddx93DMJRCpRBZh29Fa14hwI7w6atdttUmbtEmbtEmbtEmbtEmbtEmbtEmb/hunJ/77/+RGuSvaMACg7tF+/9/YByDzmroPACvXGfoAJNAHoHUhYwBEHsjpAyCjAhaaN9X3A5D12su98qeI8nI=
*/