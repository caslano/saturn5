#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_SPARC_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_SPARC_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/sp_counted_base_gcc_sparc.hpp - g++ on Sparc V8+
//
//  Copyright (c) 2006 Piotr Wyderski
//  Copyright (c) 2006 Tomas Puverle
//  Copyright (c) 2006 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  Thanks to Michael van der Westhuizen

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/smart_ptr/detail/sp_obsolete.hpp>
#include <boost/config.hpp>
#include <inttypes.h> // int32_t

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using g++/Sparc sp_counted_base")

#endif

BOOST_SP_OBSOLETE()

namespace boost
{

namespace detail
{

inline int32_t compare_and_swap( int32_t * dest_, int32_t compare_, int32_t swap_ )
{
    __asm__ __volatile__( "cas [%1], %2, %0"
                        : "+r" (swap_)
                        : "r" (dest_), "r" (compare_)
                        : "memory" );

    return swap_;
}

inline int32_t atomic_fetch_and_add( int32_t * pw, int32_t dv )
{
    // long r = *pw;
    // *pw += dv;
    // return r;

    for( ;; )
    {
        int32_t r = *pw;

        if( __builtin_expect((compare_and_swap(pw, r, r + dv) == r), 1) )
        {
            return r;
        }
    }
}

inline void atomic_increment( int32_t * pw )
{
    atomic_fetch_and_add( pw, 1 );
}

inline int32_t atomic_decrement( int32_t * pw )
{
    return atomic_fetch_and_add( pw, -1 );
}

inline int32_t atomic_conditional_increment( int32_t * pw )
{
    // long r = *pw;
    // if( r != 0 ) ++*pw;
    // return r;

    for( ;; )
    {
        int32_t r = *pw;

        if( r == 0 )
        {
            return r;
        }

        if( __builtin_expect( ( compare_and_swap( pw, r, r + 1 ) == r ), 1 ) )
        {
            return r;
        }
    }    
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    int32_t use_count_;        // #shared
    int32_t weak_count_;       // #weak + (#shared != 0)

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }

    virtual ~sp_counted_base() // nothrow
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() // nothrow
    {
        delete this;
    }

    virtual void * get_deleter( sp_typeinfo_ const & ti ) = 0;
    virtual void * get_local_deleter( sp_typeinfo_ const & ti ) = 0;
    virtual void * get_untyped_deleter() = 0;

    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }

    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }

    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 1 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }

    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 1 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        return const_cast< int32_t const volatile & >( use_count_ );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_SPARC_HPP_INCLUDED

/* sp_counted_base_gcc_sparc.hpp
3rPWBhW2oVj8639RZ9jV3OeIc6DKbGWeRxGbX6bg8FaQGTmQREEe3DiUGsUynYJIPC+PJ09sPJWiMM/oo2xQGKbYGwdSFOYJ/XsCYaAap3h0dgYf5uKvfZnpOVEUsZ24gkR1r0+t3pl4cK0cxFbFJ1kI8cT/cEfFjgEA6nYqNXo4/HNRgadAhJ7+MdPjIE65jnt7dZyMtVzWPhoC3Js/oyRcnyYNhDZTXE0MO3u4imnx50NpUX+FqFznJk2uOQxt1qR7qNhAPBw14n3nZyBJm1V7bcCPFRa4gPLHvTt0hwSGR5paDIh2gMEnUb0DdmGlepeIYz8CsPaCn9gZcvmMNs3lNgHi4HPaHg8/qR+8I/N4Enm41RnAkPFwr3qTJEO9nronnQlYDaYglAIBpTSXXjdkOnywn00B2ZljjxfHQppCYcbAb1CYmoc5HNxI40ZNqLMTpavNp2oO8ex+VHwJLED1EXZc8iJxP2qv6n30XzJPCuchey67xyu3ttFsvhnMrJcF0CNmaKW3jgayPUMpIIuOYTsS8EHtHB7tUKdgq1foqwZeeo8SNml6Kj5hYz+ao72hfwNhsZuoYdX2uPeIRBmsvswhwg9n4bOoX0RwORDFLAfHU3xATbLrvTs+q35Lz67fSM3e+oyavfWv16zq/6pmIEdn1uzLRs0OfEbNDvzrNWOSlV4z1Cl9CmD0pTMhY+HNdl5t/E4Z4bzr4d5tkh8mZpm4w23qYN/vP9XnZjrmtoNASMbC4EbT9zc6H1iNzXnGHscRZrP4uKZtnfYulja8uzFLeAk75SIpVqUBTYWK1MRcDTrC2K7Vl6qPANXrCD0yPWIKZ5V7Old+khyj2iJJu/xMUTvUfmf0FxQnmaNHxnrH2TifUA9VOEcdDl2jzrPHdoUL1EqH+jsucN+JgVmeA6vGqbYfUDUs6s5ZsV2hD9SPAolqu1jRTW26D0f9XKJm0WenIt78PM0srgAb7/94mr5sYv/sZZPYgDP2JTRKUrH/3olHxscPs+h2HLs0zmkmQOKprVG1N1K1LmiECq3R83JoXKNaZYl0WCg0/GFJx5n+fNvt0V2hCe0UWdVueTmU015lxqLcccRcfxTmMFDE4PgGkrz5oA+HL1gO0QV28KyH+tsNbFhkb69w26MdYXewFJ9FzY0w4mrK8otZ9LS1IpPPkUCObAI/8pyqD/urDagzsHjn195obS7WFodJXHyju6JYM53tT2jEV0VugO1jvCbsesfpW/eUaCUHab6NqRNvl8h+70X4GL94TX8f9Lwd9nGS0AX6ee7XhSa3e81eHL2q50dBtukFYas3+TEfz+qggAnG8aztmfrn71Qmj+me+XljapE8YUmeh1HLlvGO9JPTqafgPpTP0ZUnoITHBeePZdU+oYz9ySsT2Gee2kjkaJ9v125v/XRxyCEPwOXzP97AsYhmCPkm9dXQxarWbp7+7ZB9egvV6dqwtdvc0D7TPJMq+nd486aZ+UZwbqqMN7gE4h4a4AAKLPXTSkueqkEIBodFaJMeJfTu3DLXnePcQoDh3GJz+2p+9Nwy6qITJ51bKtw5WBeqwccJNUpwwVjGc9IGa2q6P34CCGx+YDcOfsUn3ryeIcWtXqDUiG75kiVPGOnCxvXHKAj+PMPXQxl6tv+oCpmXw6+I+2VqBxxqG1mcmQTlUxxzl67gtPt44yyfgZzHoHsz5TLiAUzG59pKZwZhy5IupHAoYjrFnGHCdobMsO4HTC91pDwfn9bz8nWsuMoNqP04redxvMIjRgWfmmr3BfxwUp8nxl2PuTUo2hChBw63U+cN2hR/E07R0U9YMN1t4dPmCK1MxkFSofHQxuKgUJjds5fu5xZTzMZp40J5jdPmWUIT0MzGuL0xXmXxY80jic0rLn9NylIfmcGp0xFoTXQ/32i/xB/YSepvREdQhp5XQxMb4zmEQ0p20efIdsYlorHHgiKLl4St9Anpfehn2QacEsEUkQ/ogtZuKh/+CFcA2qRSyKHsOQ1nGqZ8jANW2tkZnr3N1e7LalPM7b7MNsXS7stoU6ztPlubQhGsbUpGu8/SpmS2+8xtSla7b2ybYm/3OdqU7HbfmDYlp92X06aMafdNaFMc7b7xbcrYdp+rTRnX7nO2Kc5236Q2hfLPbVPGt/smtykT2n0XtCkT230XtSm57b4L25RJ7b78NuWCdt/Fbcrkdt8lbUpeu29Km3Jhu6+gTbmo3Xdpm3Jxu+/yNiW/3XdZmzKl3eduUy5pv/2KtqpLu8sLJGycCb/rjwKP1gKhQnddclDtDsQXux1YMUwo5o3tdhzzipOQcRojVhvkEmqdupm39SXHUUosWuokrN32+bYKd37bYvcU9ZMEPP272l++5YJw/i2vhHLbqfNevsVvDo+j0Yl0WyjnwyUdyYyLOyK9lDtXMGxDIdOkNWl4/jR6Cc+TWTH++9ezC00GxLVjuXgTa53bHC4+zxlgj9McYzM1XkDNrQ/fQK3A1klVblZUu4sOGOcjtTks6IKBkWMd0WNwB+lQN3DshrbFdvPor6n+BdTKnc6jz1vqTsy1aDhBJ3QJEToHwJr3o9+yPZwBXwWO9pna7ThfBwgkMdNszGmCRwfNBWCddRMB1kX97a5bcjPDY8vBZR+T1ehaYlDV9UdX2OVorbXjzIwSrY5tRsXnTHwUDHEgNGXUqDtqx+aRDe5W2LHuTEefDkbLiSh/Uvzivz8nzU3vQcK5cM0hvstBmGqh/BrxDeTNGKr8cxKP1K/fgWqwP39fjVio53CxhSPyyomTnmupkGYz1pTTDuyAJ8cmU3AHyMQmXiKukcd2UIE3sT/8KRuYZoFyhSuMLLCsRCSFyFopdfK1bJ3KPkJLzyZcZTXa/uAzKAD7dIjrRZnagcigbV1e8GmEcxykLov0Wa2dRLf0IyP0A3mxsu2M4sxLdQbOuQU2B1e9kS1u2dR0gztKAb4mc43Yew0TiksBiLGO1S6FKo2PivTSm8eu+kI79GNouTbUdMQIPjqW1yQwMjRoD9l1k8eQM9iGeur5aPtLOp4bD45yGy9YHcOanRuZoIo1itJUoCgo9VHEJrwuj0CrYNT+KJuph75CY+smiRlrexp/eBgtne92qzfBmKeG/Y0WKtwtBVxBK3YMr6B61IllhdzEXIANBSvi6Of0Be7wuDpxMwnj2OkHBkx2Nh9kwWb/YkwhE6v8RRKGCgolmPnEx1ePhibAt09nZYKD4yxMRHkfpMiAENDMOy9yaZbkk1wa8PnFBbJW2epkIvZvXi3BVJ2CkxHlsFM+AP1UPs+f5HzcqBnyqPGLfUiGQ5nGKGqWIn7Ar1xBYlzY0186jl1/FKtrfGie5Q+XIMtbkWCzO9+CaTnYZA6IDQiJugswvZosAdGM9w18EHOgKcsnGq/G9naRgeBNbrgYrSE6bvaLWpmwUCb0i9kyITZe+5qsflFC7wHxh6tMsIXgbdda5rqciDa2JeMPURNeHXidQK8wvqttsvnFjyh2IvfFhO3BOhOyzfCL71BQ07KmTL9oxpMT/PNKPFmb7H4RpKe6pmy/eOkqbB1xMjeXqzMCqnSVCmKLjQ1l8uASl68pxy8evIrbk2sBRc6qEfddJZmPMQjvkdYW6LxRJMvnD26gIoKtTl4oZw+O2qTNPID61sDYQGgcMyzapCc5HHBq00m6PIu5Vn3Y7bBji/c2/iURqdJPfNJ/XonBDG52MipAlkAqtVxlbRLQDONC8FANV/KRziYTiVH8LGrpviSyjY8Ft6ybGMSqbPBhyoodygy+y+dDL0o/zJn+gktdxgbIWMfjyxssLuIN/epNaEpwvguamgOPt1LwY/gWrJAh6lh+K6U33+MbGlhDM4mDCiio5vFmDno8mkrnGpXOxOlC6en6nUi3UaZrS6U75ExPt9uJdJvS023jdGtluhX0cwYHytnofB3va8pAAEZNEqqtpS7wvIVgrok2T6LrQrqm0HUZXVfSdQ1d1+JkKPq9CWdD0WXnGUpJu4FoieP4vPjNsFStqmbGKTQdJ6HfMMMTfHhyk4WGECFyEwS77nYAMsuVptPBPS4meWicuify7nBjbF8op3HGl03OGBwNS8rAwo/nJThNXXcvDqBqA0iE3FW1hr1E+yXBHZRTYt6grzvTBMultktCcPvs8lZ6RPPh5G3tFVPnRl6CSFSaCE29kxJsQwL/yZqRBDntlZ9WTm8Jv5uUu3x4tV4C46IGnOKcR7yZ9O9k2KuCsQkvkUyufqzkJtcZx0qGb1Vgc5HHIkdusJWBwtiWNBlH8GWF9QKx+0gWCA5mZC+WnbsR8MUor8ksX84/zISfptMDFxtcjhLFJZdjtAmLY+zP2FGgwuHK+JKOyKdW57/9Fya3+8HgcRNbC9pynLEfIEuag5pFM3dBoWBrjHxaEFpL9+zQSrrPCR2m+1dCf6Z7ThhEzNFjZlAzYt8VeoHu3wxt5Rhe5NZjQQwtOy3HqzjHArqPDV3EMS9GTNUi45brmSJ/TUpzkD1Mph4EE1wfM7n+SNcpui6l+hvtM/yJLM6EP5GDft72BY4bFnZlcLEPG0J4XQcHztYaIbbcKMDpBLC+E7tOsfnMRWyi61KCm8fDBPmKU7x43LeSqO1jAHxigLMT2EOv7UmOTWATFhuW0xfnix0/h41w6CK1Oletc/mCG8bDHuLwpzILPmSNiD94bsVnTBvni3tObNeT6SUHueSf68kGwc1V23FO9oIa8AlSrxh1h5g+nfbVEhhF08p3Rr9HjS/ZFZ/rntlIN2/bXPccupaWdLDZUNBMCZ9rxexrdn+VeJgKdxCQCxvP6TCdUGr8BI5soBSXJ17M1Sa1cQk7T3SiCNYALSU+2hWsGs983LIaHay9aDrYxGXEkf7tpGwDiKTqddTqrmpqGcO3pu/hoWEoC6c6rpg77r/11AMsSmmTtvG5CLWYe/ZaddCPM9aIUYTDeohQ00fGzs49KP0fOvqeRXpsG6ACnzFi51LsulzV66oJCp4+0/TYYIUb15dpw2FQQvYwA9Mx3pMQchfAc3rkPYvnBEx/1LecEb+Zpw7OYs5NOC4glDGXvQ3PTUJ3glOj56qwuyogzJfZqNrsyYxG5ws2bJrVjYIUUY8drcZRkGBVPSRFO+9/h8qkCVplCWFLFHx/5UtWv8mq41x5IAWQRi7x7d2h3KKuvaKop1yxvgmwAOFJuoq6RkJCaYASvi6ZleYvhXpnhfwaGVwWypaw/F7SUqKDtZfKVnwMPVTtYA1XByenJbCRmRhw1ApgMhoG3jnB/Qp+12KUhJiM7BZzB+FEtzzrTmu/J+Seiu5z3g8wKzn4GCLRjLsCWijPK6EcTJs9RiifDUChGcCX7DYaZkLUjKfltrHpni7JU4esklspo+9w2ynfqx06f8xYVk96SOLjwoYl8SkI1q3Qpb6D2R80QHqZxtlerGBCD6aIwYXsKHOsvtdVP7KM6Ed83BLdWfVuqf90SAPKLJhOoTNd/ngF92geRAd2g6aaa0YoyVSUHBk0hzIig5awKzaAFocmtM8t1qK7QjkNW6EnXkJFxLNgVTvKA7zEj1sd4AoKClhTWXKwpKON+v85zWoacbqkzuBNyBgkpne1wScmwNhGbkPGyX2UBU3WAuBT7Q1PV/hWCNkJ3eoqvyb48ARmVfNgHSbgNoviXMStUncG2yZgYuZczvJV3+fMDEouud+5Nlg1QaesqczvKunwHOONDuhMGk8qC6cehG82jMXyfakSxX8N66WBKqrbuTRFPHyZLG2biTkYlyTktcGCs0qbe77SSniMGHGPlFYmS5uMF5+6l0urEdfJ0pKylODx8XohnOR3p5nG3HCuyvfJb5NGV/7tAs4O4IL9LygqKBg7Xn+RyZRW2zSHTrsN/6HsFDdy0rxujFpug+HbTd/XND5I1ceupuHEr9rE3mF4vdBwoT/8bxo7UY7tI2H6tsiHroD4j+/x2ka6/+56ds6eVQv/wYl8O83et1bdUVMrNt9kMll7seXtLegAV90MREHhN94MQobzzAuBSCmC9RWFgMZs9quvxetMYstjGvyKL2rgnHu8vJVS9zY64qVzCdchd1FaJaS8ChfG7IDc8D+vqTeoS457TjVfwi7IezeONCG3gZIvidsXjfJBXnTCeoz9kBdQXy38ScrFvN3E/g4/73wBDnxv0iXuUJ5fxG6CZON8YZxP/JDDoYUWapanP6SoVceL+mvVt9QVIx6VDxR1wikxvG6++RNu3IrjRccS88y+RC7xj2LH1VLzMLCoeZJ0kjlulHNx3Q9j/XfOcOiqr6ec/CxXnMGfwPXi6HwbkPHI4Y0ZRr40qG+qJe2ZgRIsZd6C86kV8Uyp0XI70alMdZhog+YX60vRB+043ZI4gj/hJIsiT0B9RXyFho8Po+iS5wNIhJcAt8vLpoFaA3mKDZONvdJfADfsJ9kBCuRcbdJ8Kds6fGq/P1ArvkwRYwPhC0AQSjoUv9j+uKbxMc4Mjd2j908jFrZDi4fTY+1O8+f5xJskym4tvx/bcdkiU5gv1s3Ba8+2ipWWh5p0F7XNPf9+uI817MXTbEii/MmcSulOW3/UP1pSCfPPSmhNJSw4O6EtlbD0rIQZqYRT1Wfci+83EN6KiRbXbzOxb3sphYlvwF6bWcFeDYe2LsE7u1BaPlHXMwA5EX/lFvtgPwG8Q0UsuB8uVVb8XGNrcbmNG8We36PHmVmKiJ6dW8/OLi7732RXqmdXqGeXLfY9+b/I7m+fyuwK9OxyROR/k90P9ezK9OzGiNJ/NTtwdEwlfH7x4hAnKkjw2Wh+8Wu8z+etRm5fjV/8FO9zmXXIR/wHdP8ofBxzrbj9cgMxFQETqwDHuTT49JKn+KCBXmyBk4WJoDffvIh3MiRvCJZORGJHKvGlSASqwEnmI8lxJlHTOYmrTvzbB6BgOEvOGb1Lqgumj6gLpjPEpdQFgQQ2eqnYcmQqN2FT1OJZ0HPyS9S9jPJXcKg5JJvI4eFGqkEBRVIQqc4vbpiI/QJHJmD5+Up67vsDzd1Anf8PQHxi4kRWLZQqQWi6EtisRyWVsWyTwKa7Wpa/wKw2zlhmckZbKFVj5JQ57OI4esa7J2BdW/yVfvgQpKmUVlGgW9xKQcG898xwUyCemoC6UA42v3wWP52gK2Bl+brkVsbJuTaza2vSKxCOqLzrYUQHMD2lAxCuD3g44dquWDojACxlnA8OvUaM0dYf9WlRZvfr+GK0/UfDkkWjnBroTnuqgK3O7/pAd5CAWOfdHkoofSTWZ7hRsEk3CogF2n9+NwpA2CnTiPU75t5/hsYjhd//APye2m8CqILXnBVKEAcEyaWQkvfhG+4y+jQDgc4IjipMbOBjr+FlBlMajsKM5RFn9BMzVMi54seTdfsCnNQ0qVAq+PPq6vjVJLl24p1UGa2ko6+P8vfXYbXUxk6+ChS5kb0Dyxgorkc/zRvHqmHjkoNrCSk5oPaLWUZGvCwCxZhcjaDIx55SZ3RQ9Zrgs7wMKw70u2w9ZNn4cndQe6NpgKjCWuJmQ9ob6iZedGLXtxS6QvzlV0wA3HJ5Rx7abm8y10nfS5vZJ5N48hPCZnVyIaMJe1qwAWd/jJjg02Hj+G5QauH8DgxxljTU00Chx1PDtIJe
*/