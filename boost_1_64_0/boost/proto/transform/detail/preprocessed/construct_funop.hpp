    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct_funop.hpp
    /// Overloads of construct_\<\>::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename A0>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0) const
    {
        return Type(a0);
    }
    template<typename A0 , typename A1>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1) const
    {
        return Type(a0 , a1);
    }
    template<typename A0 , typename A1 , typename A2>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2) const
    {
        return Type(a0 , a1 , a2);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3) const
    {
        return Type(a0 , a1 , a2 , a3);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4) const
    {
        return Type(a0 , a1 , a2 , a3 , a4);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8 , A9 &a9) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }

/* construct_funop.hpp
s4ev6DtQu8z3t7Xb39B2f8Px7byv15cyy/gb5pQk/fLywcdXPtK2/HcanpnBkYK9X3KZgQ1lyyMF/e6s99s379IyTeJtV13W5e1WF+57Wu82fLeWdTlHU/z6Hlsn0OKnHVPA6/o4X8fUZYGoy+OsLlcYXqWhFPObFUNTKlTzQyjXzmXez8r9s0pny1yXlOS/L1BVJpb0nxFRyuAqCgwJ10W4nSRniORcTOkPkV6umkZ5Gd9rCDdP5G2g9EcIXxTpxSzN+1NItP8nRH/pbLD9KziWzGZSxQI7vcLS0Axvh17eLrRXfQi1y6eMrvuV/v5pfO9VCeXOWT/D2qG3YXAzbwYvNe5ZkHR5Vz6TOqPgzRksgI1Tn6NxamUNHjvSuQo/UyKgXpzw+Xa7L/+mVntfT6ffQek5SC8aR5+8fk7K8v4i431zuz2X5MTpdm++ju2/47vxGl+m2PmWWnVlv0XP68qhvK5fba91tmPLaDrDubC0+xZhzTWl4cyoPpWWoYtqmoUPZNvvNuKzne5E3mBsJpfHKsVwKVsu6/Z2+/uNZl3EbTdlYAvM72MMVjeDn5ueo9MdFt+g06nR9AgcIXh58BZD5yLsO/XzdNyHUMylvQnlzlelclo3KdF9AbAT1JAP9iXAumEHgCo3faFOb0mlwcuj+a4DG2SyoF+Xs5lStgJKKx/BQGllm1KoVphsX9GyTdk65Nb/a0gvmAL1UPrrSB8xZYunr28gfdQUNIZRoeMzm9FXv8n66rFTcLCsiLXJstv+LK3v9FHfd/YmIQ+VtQiM6nXbKf7mP4Rl6TnAV7KlkWx6e1bX4dX0m3G3++JqxE+priSOgCb7EktSS5y4qLMvhnOGOKgYWmuEmojI2FiwfaMtzak5t342zX2fHOO+rWVk47Ye477jG+PK2ewQ9wI2Lfiive3vBIeU4av09++Jcc4dn7/frvNMPD6760B3Gj5VReMk8g6X9JOtNFp660B3WflhWxmwGhnJpXkdLEzWg49nd5NP+wnT1w8D9HWPLQ+0uaGsryw3XWtddhBzsuqod+DNJimewF03cTfxx+Rjjhz7+2bstyvQ0fA0Pf/N+p/ymOw5xMBVL0a0Ovl5gE5+YcsBbSnTwVVikzXsGaON8wu6lImlkSv4bKm+PDCA49qb7FvACZM5COH56/utLkWfsLpEP9hSKFWMCbsx2a9YHd+gMulyhVeSpVFS3HffOt+HSXFlC/vtI7zNWkxkM1V9e7k7W86UcsVKoWTLx3gQyW/JAt0Lkx8xfqaH4uzf8HXe56ADd+4KXwf/54zbfE3oQRqrfxewHwV7DLbpScSoD7P1zkfa2dk4Jou2tz8Ap78j3vS95fhHpIPLru3rdXmPibVZjCEoc+xZwsf/zd6Vx9ddFPHX9rVN2pTmbF7OpuHGUmiBlsvKS/LahuYiR1sQjWmatoE0CTkqioK3gop434IHCgqKV1VA5RLxVhRERQS8EBEpiAgIOru/7++33990X/okfjz7xy95OzM7e83uzu7OzpZne5vRr/vbe7m07y/rFb4XLWk4W5hHyt33p3K975qXeNTtZap4ih718RjRCw7+jJz9o+h7sXtgj3vo+b+mfxL71J+kdnuKzs++RPC/qf3rRApvC+AsZUYK9mJ0z9viBC7zf8xebFZq6nKJ7hnL5+zU1OXS9HOJHjoreAf7OAWqHvIp79dBNieSjj/nfX4KMqZoWcYWED/RbbAHpdIGv4WOn9D6ZbZI0fjsX0uIBjyELm6fVZbK1r+mWMuj/ctT8T37lIQnSY75DKLC017cBuer+q/y0dN/TV/jyip16y/r4lQgwy8nGV5iy6B87AlMt9/+KZLzBPuKSiQ=
*/