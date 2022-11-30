
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
8LYe3nbCW4MwpfUWPDJog7+9NCBlIw1oh799GPDcJvyW5xngrjm43RDD37Ewp4s6FJ1V5DuvWzkYg9DohK5pIOa/IzgNgokORyzin9HjBtjh/EPeSfVi0RSqLhmmz2Fz1zMSPbHGiQMRSkkLsBMolf+SiffzjVfjfq5R9vM878X3cycCBHgXAJqM8LBFAdwdQuSyhmpCh/PF24vE3GL0APkZu0gj1aMunsQ1JsKMVWBcUjd+PcmTf5bM8rbDJqPnhamU0YMI73/X141dL9ADjToRj/40jbpIF7CSVe1fo273pjlR7bZ7Jmg35AcSSi/O7/WN3Lkm1fhq+9L78PZgcxn8iPMP1HaK839b23kbbNTtpRCUB08BPMXwRP4plwf038QXA3H0Xwx671rV/WpHxrUcJ91rWciF99HTUfsoshZi3wk6KYU9J/Gl1iA8fQRf7CbB3wsv1iHhlVPwK24+/VEoVCHdAYvD1mXcmAWrTvRjDC+KGOWUHkU0jhuhd3IHIs8BFP8itALpUxMkZ0XIIacTWUGfoN/73bQk38hVxsff0qA/53+k90l6Y6uDviQb/c+hY0s/liBzIsBfPN0PuYY6YV/Ge0l0aDlyMCTswbKEVyT4KzthRbbCJYoYIpnPh4MHbyJi9wkUgpAZEwzs+LQRGRNatHWI0MKIH7Paury3KO6JxdMQkENL9CTJJd+9Usd14GYxcBVSIjW8NHLtQhQnt51oyWsn5w/+t3YPJjTu3uhlPdZ9DntMR973/YVytK8hAHPfPnRSn1hk+3xdT6R+Ojici9CanI3aGrIZh0mZwmREAcxPAaPwGluXoetJBtye+3XcAA/fjRp5vCqBAA2iC+mRgWzkJV85yToMCShxMza/oqYm3OP9RbAzihhKM76AbrrDlYqYVWqEj4G/Qe48xJpG/2dceMzZiPkCcWxYAMmizS5ehm3DVzQI2FGxRz0cOEc7mpejUa4hZQg8jeSMuAcLbfDRH85zB5lDd9DQYeNuo+/sUm8KkC5ZXiOyBFN9XXHopHlkcBL78AXjGnw/5LwHrYeE6XJ3yn1JWDMW0D6xDg3GvzU1Qp+rOzY84u4VOs523pPkkm6dgSypDggzsZcWySZ5Yjzev8E0f3rfwuv3jSUWTgOxMGsOIxZi8W8dOiCYpOfSVQt4lDq3hhbkkc+833VJ/0adHjfdBJiJTMEFMorDBV8ii5hK9U/YexzuLqP11nfrpO1prNbo+5lKtjPRKt488venkKZi29MMX5duw3kdkI7o0IbuQYw/qrMGIvyRjJJ/GE2PzHOfjKJHbkV6JJXSI7HoD7OK/khV0R/mGPQHkBVhEsSk3Hwc8FxFjXfZ9S5Kb/wY6Y1p8Ck6Rp0uhvax4MugKSL2s+dG+L8NpzNgmU+AWvG8ZoicFfx95xAXnaR/T9G/0jk628kiHZmx4cA1XBzscxWwhCCY3Vf12U54blDIBT+GozMBngHJyiKdA4dxdfl7z+Fw00Q1sFrFfnhxwqI7h6uXD/rxm2NSFazJVYMJjF4GLEDTsoqvliv2PiJuxjIryGalTFoGLyevqRhfpudlBgCZgwCiQydYcTKctP08eY81XipGVmFkbNtU6YMsYayVcmZm1Jyl4+/QN3Lq/3Dg2ZszLMpiYkACX85yw3qsHp0dGO4bJ79CpqIvJ8/0qPkgHxrXdQJ/rKYoKHPNzpZjpVath+9Hr4c73ab/VK+HG3E9GOh6oK2pcNJ1oFetA71qHeijzyvp5UUy3jRO5yukR6BbKUWyPm8F0Iuc96boupPdGZG6n/NAkq54TKh5Ft9hEWIaUq5DaKbKgCC9g2sGgVBReUTzGmNV9d4ZMucl864mTwIFtnOs/FQlOSb9px4V1IFBtR5qsPXKlAJFIejtg5bgErx6iDP6f4sLSWGmgYvTQmWeVUSr1OPFc/0wFHerIuKRg9USm4sBhm68tHODB0fEsqK4Dfs4QKu2t42+/6DsZsu0uefFUq6BGL7PtogS7+fkKlavNdBgixskJAmhTfY8BN9CAkkCcOoFrYL7ZP7TZtyd6AsM+0ZmrJkK1N+WVZT6a4efC0Gxai5AYJp7vn1M/bRm779bD9RDoFIToN5wd62Ggm2rkHbUaDjNuH9c2H/4IyqVq457r4MdxTlL2VH2C62WZRBUGeXzvem6sM93IMnR2aNQZjELhZYMYaklNexVfKtlPSQEHs8lVFkWS7ORuz5j+xwwcSuNwTU+cA8sC9iumo2t2fAAGCzn0zY4SdxuoQWH3OZ9T3GuYKElX0OXKe48w32zh9zZEF7kEjyWzPC5nN72ubHVhrgD4HBJL51jNRk3norH03CTsfVqpGCWWjLhyYLn9i4GggYoAhJssL3juZax2Q1AH+CSpSy27R3vfw/q0U/432DVRnY8pdrvRXa9T6DmDOiFTBe6Icca4MmWPjkLuFxVbc5Si4UdYzBIE8OQImnHwq4fUcJ+DWFtrBexAOimtd55LplWAo7oNuTaqiyplU7ImVbhkjLOK1kHw8VtH1XCjurkrvZvg3QD3dGluy3Y30rbvKk0N0TkSveES9gMWdy8Op3Rf73c7eImy3LY7yokazh5QxiIa8JhFQyIPFi9Wjo2nh9BJSXwlKFPd3lc4ghMJpe40YIaLbR1YpWFR4/zVeg2Hp6l0tzPsUx1Ziy/RatuVdlAEJqaU2v2roCuz/Y0KrnhWSbXpcW63Amwz1byMHj3SvuGYdeBQV+C7InHshjAwJY5gVVOxw2s0zPJNxJn9NsiVdk+9yTVyBuwXANreM0Q9HTzeSTq5Yl2ozzD6UxLljGjPNsG2Wx7PE6etX6OQpDhRirAVUO9vVsodJ4s98xImImFpVVW0pSVlTT8dqnpU9aS38YpA/HLL5WBOBCnDMR2nIQYWwmdnF4hHfosPAEhzYD/HOtBnvYTrZWntf4LtA1GxAI1JwbtaMCAawzh/F/uRnMwsEvuDIvLGR/JRj7u1fa+Byna64YfWNsWevmzj8H25Vml3u+E4Z3+dyVsJoN3rXeBagV8H0X0yiypPF0C6S7pxq9kJDMJQDa2ngrjhKfDhfcix7gOqoalUyVUQ6pPYHbiyvSk2Q4b/cdwrgJovPRAEiXayZmBrShkedhjh3C6MHjp6WF6PGrFGYN1p0rHv2DHjk+y0rKNrY/DG3TpvRWQKE06Dk0ZWMcKlwtZPMx60BqADKkeI5bjDE8jiklx+P4LD5VpiXkypEY/rjJcnfDkw1MoT2YdNCpDLLTci0OUD3iXRuIikQaHo3PQicGFpzCkz5WKIc1AH/RhJDBTug0CVShbxMZeDWGMif91VBGZg/8U+SiRhofGZ/14CCVBBlfw0szJcv9Gsiwe/C4vaZTwwc5QChWrpEJZvCRNGpchV/pFdB3Yu2iUmY/0I+nCniQb2calohs30s3N2iO9bGS0o4lrz20q4Gpgdi6Vn29LZhO4KHYE/ZlyPg1IwLd32Hd2xpoU46vCirVUttS9FuWFjwoJgyfq6zqBDlkCAfesnXhfV/OHZuQPfdPU/CGeMQNd6BLFL5DJB1Yw6Mc3Kguz5a/I2vpDxrZDCBGNAD44AUgmY+suylCMyPyjY0hJugXPSUPtxHBODzshMBcjjKOXN8kpxb7Q1JV/fosel/8TSTtngFT+455PI2Vp5LKa+NfWUgJNxBhvD1AXjVjEEqBdK8PJhc1n4EXKHWaZHqghNIBq40cSTZdmYwLWSvngPojsbZ313SXS/inKETxmotU5ARBJASRIQurxmGl89eeGZoq4dM1UfptdJAx+YD0ApKXRfwow/OAT7YPrCrihdRcfm8h5XNe6TRF+8XYdd4GjOKThmw3oe+6QsLkbj0SqRwWxF18299C/J+Ev9f4Xh/T4ejwDOyO8gsvZP+Q1SA8mInM1gMcusEGEUrYrPvMmS/UQNYByUxi+Qz48O4IZj0PsfIx9SY7dSXMJe/ohVizW2IKrJlPb6wNPyO6CgRVEQKSv/kyPi3BbGJxLxP1fqU5uMLDj+y14kEbhI7QyQgsFtu8relmfSMsdzHPxrkoYXS30OqNNEqUXkVa8znqA0DY3CIYC2Ah4QisGlrWH1k+PoADipftlb8WbT0F4Ds2CRzQUyj/U6cJH78FYbOWTSQpq+Ab35/LlOeq/ydfn587R3pnw+lwu/5HfqeYHP1k1P85EHSc49MRrtoZE/07YZQTxDfgb9O+AvyhbJPi3Y+geGrdnF/378t9p/bj/2oY9BSTBFvTkAmcHPzfY3vNcK+zBPCjD4YQBxZxS44c0IE7GV0V6X5feFvS+TWh1JJlUmEVaJ5oyO2MbNm58BKnuPW+wgnTkjqaf7eQobSD68ZSDh8FZ9wcUZYJJ1g+Tf8AOcXmYwDuX1kRLlr4nhftKFLEC6ZkPYPt5EGddNjvCZMcaAYhz6ykVOuc4Hp0aoG3TXYy9tZ2BQfdjkoH1FJXhK7TtEFAGr8M2wLmTkMprEDb3nkX8wgpoDUSB8m+fjAXFjKDQU93/oOeZmFk+z3ztOipe3yBstGNog7DJjpWJfvzi3T1400oLcUonPqTkyfC6EtaKCnc/xrLulAJK7C3EYXB/wdAstpklqOBzmk2eROnmE4CF4qV7KFOhAvqzv44Fuv7YeNF9ejf5vF6Z7Yp+jJ6U6kWdBW/d3PtQMlpPzBYgVHSCSSjRRc5IYqRffpH0X0u+dfTS5Vth/zDurtajbELVR5u5cfbJIvpCqCB770ebZX0h3ZgQ1XrMePAS7KuqQJRSfnsRuxqKMMcl9AcVFlQX3rFjYqsa/gNerTWAblw7Lxd+lQixVL3jCsOvLnzkNxPDr4xPy+SIQt5Ye7Lj9HN2Ruvn7G+lNNTLrRPo57wEEc/A82t4nm/9dvVzwgqGqvaMl5fUu/Ay1I0CXNIPqKlCg//AA3LAzRjQbMIdmwWgw2WKufNsDnPL7MY4vBHdRfsAZRKz3biBSv/DUTtEL7/NdADm+eZx9XXea1jkn3ADgMwSZA6ldDBZFaRsYq6nsf0diO7v2x+m/W15eIL+vhYijPCkwDP74W9dHwqgzMNGolYHQoN020eKCC/VT3hjoSL+1dOV79aQ/DLUIqMqMmw+36eWDxi/Xrx61Lf0fLiZQ4HBUTwO+2MwoersU5xQdK9QVyLUFQp1VcGiDCR4hLrlDUKdW1qJu2Ld4phC8RHRQXZ+WyPhYcGly+fnXFieAQBm4FFxY1LEkzluugF7EvCMvYUnRWXhjzJSVBL+KCFFheGPQlJUBR9oYGcZKtu0VJGixRAwhQ+DKLQsVhnGWfHhZm4Cu4zR90uL8X4Jl0G7hLsxFEtvhMqXkpZl2m7b2VXXkRnao0LNstBhUn6vMF/ve0gX5+2Dd2oh2xXqHXxnfYub8wTqu4ru4+jBqBr/6SP94zttiS3BLjp6pXkP5LIhde8YeYpr1FRi4KQHczmSV4XSeaGj7m6IqMRwoahE+hTSY+AXkcAy6RgLJHlupviUU1fi+QfgTe/PqSvz3ONOh3HAAxsjKpnSFMCTAyX0fwCKARTBc3P5QKqzJNCzPE1TBQUokqkI1BdNudwEQh+QEsXAhDo6rMoHHVblgw6r8kGHtTMyrDBzI/VshHpiiZ+E9X2K+ErrcRdr7DevuX7JGPwDBUHhZRDrbruKo/1aXoKqa0cB03lIS5U/BIwiGvutFoqWsomTHJmPwaLFdHRnVDABZFJTJRQtJkanb5+ugpdu0S7EyQa4TChaxmxjkfIqOgCAJkqQ56kpIXmIGiqg5iIe6q/vHL/+CtXy6RPJa5NjKOWzhvcPeVJRH7CnlIus7WAxz+6lqE5bvs5F8gt56R9/XUoRczGPR0wLtGFVbLKIl370bCkn2CV5sDDBdSgdOwRcdmoN/IMGICV2pjEeuF34KoQvYc3iRlhpi6pQuhXVZhkv4HtoMVoGLq5Ch+RQNi9Z/rUUK7Eeyq42GTfvq5CeYwHIykg3Pcfeqw0V0vPwLkvXJ5L3iCl0SJaYQBBbfgUgekcbV6h00fBGNoHpok1y8RL5EqjXOOSYzArm6BNqTV3592nk6zsN785vg60lpelDPBNCXCEUo4HYRLmWHVBL2HAFjbabrUPMp9ckOc2RraXIQ1716IL7gLY3yMkHiuiFJeaZazfn9UKJxodRzNA/ZPS34VrcxkUp0hmAvp6M2iQ1pFvaVbcAuheAH4LQSVCf25SEHrq20DzbYM9xJ9OAreEAktDIuWfXoGYHaXdTnXfqsD5lPUyDRq1yYfnscmgqj+GjqI5Xa5JhLNbnmW7iuNV6bNL8X9FRkM4+RZuWSDqlW8+yExF66enogUF+eSGVzk1mdgyYDYN7AV0eQz2pj88Ds/Mman9yxtb38RYBinsQi+2UPh6B7tl3nsr80E2ypMzJNklFKYB7jIrq69ExPe1rg9zXI0+Fx2NwupL61qjU5Cpo9jvUuQEsh0lkOjpKc4d6yQyYQ+hUDbJNlYub9EykOJNSXLNcnO8hnvN8B0JRF58trmRYXH/ojrG4YslUL2Fsj1LsEVpsjATAZ3cVQS+UK72geHeLuGfoSH58gsxKgtsulqDyYgl+h/CNxz9JavyTqzpMGiN7cDyYkE+pFLNQniq25FdWCt4O4RqhXifU64V6A2OZ+Ur6zw2Z1le6t+DeFkppK0ah+iqgYGB7PCaR8tQPa7JEe8+HddmA74W6NKEuXaizCHUZUurMZI5U98CaTiT2XizcBSjMQN3mGVvbkXotSc15Eqkjz+05T2bh7wzyc7zxE2rS0DFPG30vTx9MIRvwlXQPH3MO9+El3Ba0hFCTShbqoTzCp5InOiiP0Zdz9xeeUgjIudvtmU/2idVHKsTqQIXYjvEVTl9gqVDbL9SeFGpPCbUSL1a/ITq6xdp+aWArgIu6NAFNebqmKI04+qzHlcLTULEGSr4LS/6XHtQaylcK74PCMb7CGY8qi2OK7xYdb2Dxj2Lx9j6oAcqGGljZ2AHUdmVZzpNlePJRSASUw7q53IL1PlpF3zPoO4ZrjPR1MQ0uCSfRlBfS96U0vAzefa+jub44TyZx9MIgOCtEx34nVLdhL4ZLyz+exx237//ACwOXddze/YG3F0Ywplq/fBL2+EgpN5Z/P553UfuwOM+UzSq85936hwssy+IqnpHmF1J6kP1rXq06fyu8wOEpcLbdpFYv1AYo6fsUKecl4WncN19+Sq4XCNjv+Dphdpp4Um5wwlTfDjAMrgzaX1ZB1/HpE7g0vd1YTo/Q3Cs0HxGa+3JaFnu0QIUoSFfec/vQQGw7zFSxuqcCSlwPgfCzE+NqA1ibvXcYlZh6YF7LNVpDlaieHko5Ax85LanGVrwPE4vyedHR7yQHIWYTNT1ibEUDeziNUnOaSloKbB+tM9oWlzRPBpJB1G0hetiRDpBkWJs8eYLuX4dEez/P9oOtdD8w+g/ChFkAJUDGdW+SOgtpSSPV/aLuKsHeDdOivzxL+tHZUk4bFOz9WpzSSuhdcugp0pJB6tJJ9UlRN0PJlC1lYnSnYD+pbZaEZiV0uhwqNS5Wbab7ZeoD9qc5pFqqII5TTigPfvudjRwvZf0+GQaqezAxaO9WDYXo6AAWlCkbU6lExxvsm5421gbI2jRfZ7o/1HIDUOT7Qyn9
*/