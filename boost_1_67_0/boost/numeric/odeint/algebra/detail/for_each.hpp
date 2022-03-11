/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/for_each.hpp

 [begin_description]
 Default for_each implementations.
 [end_description]

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {


    template< class Iterator1 , class Operation >
    inline void for_each1( Iterator1 first1 , Iterator1 last1 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ );
    }


    template< class Iterator1 , class Iterator2 , class Operation >
    inline void for_each2( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Operation >
    inline void for_each3( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Operation >
    inline void for_each4( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3, Iterator4 first4, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Operation >
    inline void for_each5( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Operation >
    inline void for_each6( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Operation >
    inline void for_each7( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Operation >
    inline void for_each8( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Operation >
    inline void for_each9( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                           Iterator9 first9 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Operation >
    inline void for_each10( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Operation >
    inline void for_each11( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Operation >
    inline void for_each12( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Operation >
    inline void for_each13( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Iterator14 , class Operation >
    inline void for_each14( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 ,
                            Iterator14 first14 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ , *first14++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Iterator14 , class Iterator15 , class Operation >
    inline void for_each15( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 ,
                            Iterator14 first14 , Iterator15 first15 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ , *first14++ , *first15++ );
    }


} // detail
} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED

/* for_each.hpp
yAqKHRKw+ZHj+x+IUaTVy3A+Waj2CYfZ/tK0SIRci4dt9Z6PEdE7cDOpEcya2tpk+sSvn769XAAAgOFhh83nZnYjMzNTYF3erauq61VwnrsmW1fILGn3xRwvP4rrWANphxHgheBT3O8O91qDWJH9VnNQnJiInpbpI9Rj5iCKW5OSlJRkbmsbAw0N7Q7PQwpPzEV32cPsjRoA+HPDAfv1o7e7B4jCo6Kicst5tW57YSdzEtuVkbHhdpPNfy6HrjCo0Z+2qnjeqE4rSZbqV/ljDWvxyeq4hVffaoX8cuGt9Q982Iq2Je3g3Pfx9G8JYiqJn5l2iQUzj05AACH3NrVE7vlh12ToVLPk7jWuDeHX6MsvhSw7wkikX/GxkvxrLwTdfHptQncKQ2qvx3tCHxNfSxv7a/ib+ziADybj7PPqCwcX4ZX9M9ft912C5dPT5Fqfqlo0Jh8w49g/fLYo//uD7JIPzl5ZpMlsBAaF/wcZJBkRbSBtRZvf1Z1xHGV7o4pmYV3dtcQfNDA1SzYSwt9+3tLgKBPJYuLkAkyEqDOQaLDhLeRkTFV5EGR+QVjizHXtO8Vnu8fhhP/e3x4ysx46559ZWIhFniZLM9I2ruY3jze+MuZ93lzf+3XOnZaY8rGiej0eUv7ywwfYv2At2hG1E5RPU/abRZq4/93jshau6XXa/rrgjtB/4z1Qg7T9zUgVwC8mm8V8yKE0Cu/+9qLwi9Fc/WUmVyh/KJYQ4GD4ggWL/xyJPItm/EUhneX4bvf3Sa3ub+4+7AarQV+Q/C6Peej52fsSTZf3NrWgXJcdei7FdnPEfPp31yIlX71cuGwc7Pc/jtPHLrnL0Ye8ay2Rk9HnSnatKrntZpTM0/nnSgZrmfvTd1Xh7+fKLuA2t80aawqXE7lOfv+7FiaDrrRP4QmFTq0hVIXm4iGSTrMtPp67K8aFBhPuU9UHagLfs9lK3RO2uB4qDM/eN7gJLmGx1+nM0vpHn+eIjCbU64/pP757zO72h6YvSt7UvF1MUBgUtqEtyY7EAAAs/9OuVsQbyUpQ08ZH/f8yPmsGmgi/0tx+7emW+h0GX/eN7VliZfrg+Hwzch7zwtc3/gmqRAhZn+p1Xg+1L76kjCK+DXRcM9ihSSYiacYH/9kd2uJDQfT1yC0uLR0k8+PHjeAc+UobFViTyRj/WkCUjHxCIvighpaBnCz1wbF1aF3m+s6kjkZNY8NPxbGYPwYCxGiYyTN87oV2Cb1dPu8l10+Zblv+DT4uf1u/+VZcb3xeru+6+5/ukIivN6FLKjzlukLzqhC3ystDkQAvYVf97y9GPHgAV3CcFR80GbPd+SOMY09TnoZmPT+47E/Ur9vYSPtbveSPoRBCz4ntiKJ478M+srZJ44eTWY6YwptICQFiUrtWg5OZm/ar9ubpzmeNYmlc/rMkZAUFCLMtO3/+521WE80F/bcPmAaDt7ljrdN7bchlJ3d4qPLzVN1tNuMJYVEg5iYDB+I+kI+EmXnvWcA8cvR122maz22LheK/gKOPf/zfyxkrXteZPG5rG63dGczWbw3bKHz7B99P37CpLMeA75dhGIIUNqulC4AYRNBEJg/wKx8Og1a7wXxWT/C/AMGWd1MJ7EsMD+tHWPC2GVwvekshD9+TmKVvkxWg2PkzRN16VdhNCJ1YGrCTmcf17eFUYOFF919dQpTL3DzDoaQDw6ECmVGp8JBcAJSt+JAqlafUZDGL6UQNg3ZLjcmRUrge/LhF3EjKxZqYyJB9eFTwgloYv1ge3MkWlze5UR1anMcZkP239UXNb343l9uQBESuT+bkScEHf+Eh+TMnsragK/8+XvtvXOzxw4fw8ExxKedg4XkK6vn4WrW+d7gXPvsTuBiv1j6+zkk+Puzm4PftrC0Vi5SsE6ZSRqN4XAxja9cx4F2drmceXGEUm4NtStORRfgJh/R3I7ePfwQwL7TAZr2J6tclax7S5gtFmxy1uCY5so5U3IlO+AlD0/JUsHl32BbQeEkj/ISNCtD9h5qa9l+YbAG/6cMj9/N3fvU/flT8iyzfYY02mJgTjvD/daKgbpmHgnv5ETC7zeoz99YIQPlcF3iwh5mdRpk9rPKxFs6WEraDiztxPk1qhKrme9kJfLq7E4pOTLTj6Or6vpRbOiJ0rKCpcLZ2v6wxMrrdxgtv33Yh69S9XHkYQh4+mtMUO+uN1bxWv7E+X+kuUur+vFitvwwy89Kx6fz8fAY0AJ0XbAGuF0GZK4GuebGXMmZpl5OTxxfHmmsXlZWI7fmfAT5LEPXa6cejOybAk9zQC6ejCWIsq9jo6MZ4sJgd3vcOjzCkdUJfd/7B13tkwlqj7P3L1nY+fDNazf2o27cNm+bNoyOnw89K8/kXnyrfm/5vVGB5x5/lw+sLITqiQSfCQxZipMVcjolpuk5qYCo/ozp0kp799xcETEgwAgEeMjI68sXXxAkV5JfWu9YoFr1w/Rd7gYiXbPRWwfH3MyvfdHvzodf49+PNV5uQr95WN8a36Jdk/vPxc/Mb+5Q0+QuW3XRw2CWXdqDQu83j2aLzp83WP+gwnz14Wu014Rta3to8ZHa7LfhT7NWF69TERCgNHldBW1v6g+Pj+Wukm3aID9uGtjYcUKyZ29VFIJvNj0AnU5zzOM9i//XhYW5nETA9xRHYv5uzjeb99Xr80B5Q3f2V5qt1sx8LEBQTC9WbfetF4mvmd+MTahHB7Ns0bZhyEUEUdeuFjYTuFAW38XQAx/c0AIfqpD1T74T86Sk5NguHAntSifPDHAWZL1u/gtr/ry4FWP41CvppIyrjG70CVadLhYqQZaSmcqquQgh7Z2I+JnNhUbPjQx5kkO5vajEG8T8nKnl3DxGQRugPqsSdWsg6D6pMndRgYnbo8zQee6eVhp7lxQ+q6J2LYVtleWphkmckzn7k6pR8DGUmI39HKNGDRGLxGJk95bu7iP2Z+YYlieQIqfr9Tk7AZvvf952Z5WUAZPJ27nB40ARh1Bwy93llp9HCKrO4EWV5HGgqInaU1GJ2ksoxWwklOg9Hwpd5HBSWmJ1cCiae93ljD0cihTv+JWghqZiPno3+JdgHT+tU07HwQKuJz6//jnxzKXyvmZ/X1ZifaVJfFj2nUTOsDNzu7xf+3PIm+vJ0myJUrP+Fdxh37Ykf1w0+nD7sWXts/dVdBYnBpwIWy+sBvae62BfRyHazMk9BTEwMput9KyK+VRd8tSkjI1O4PWtmZhZIZwZzsOZ40vzg4cEwf30arxRBxNUI+a+pQ3Za3LOy5FeEHo1jZmKDnR3V6yZcoYnd3CeO13OXyHHX4eHhjawJV4dXS8DVdklZWUBbGqkz/cdzG85LTleSrxPw4USB0/UCK4PX45+v3bbo0cDk5KSzbQUbxdXFxYOc6sdOdjEK1m9V1nzt/kF4At/joFIMhw/4/Bds0VvmcDw5j3RikpS10MLGgTDYF3diMEKGHPnB4ZZhlq0Dd7bea2imrYxbpr0XLDXvKE7+IfRqMqwLguqcX0PDN7dMAS9Y/LpHNvJRf4kCCvEvgmDRa17CqPCEpTtJ92JK43JzIXRuFSJeeDb2ioVFwnZMweyi+NZcH92NbjU7at3pttQ7MOywqodxBYOgW/Ze6/ITOmb5JLg7ZmUMee10is4mq5j++CVDnUAF/Zip5GxQCuFZXkjNdHQjrM0MYB+rS7S4+QixVq9rgFS1KQkSy+aGskJFFPD0bPOOkVPFWLFmt3TqeLP074jR1Qb3ck3+c0rgIXfiDwFz8JmTCLldlXP8WvPowgtEnr7ubXTpfHTuvtyBATx0ZDL/scgOcpl8Xt34EgXPp73aNVLZ9Q4iyYj822+RGoEehEtHa/dpX069UabJ6RKspQJXgKFK7mu5Xa23PDhDayd1gAAJHYWHLfgVENh6swv5Fo0XDmTVpncKu+tE+JV4uieiUkSjrWKq1lInjVFFr9RKP69S1PG1p0uOgJlAFdqeHP6LjnKeg89MMnr21bVgHjDxoF40xN/94tK+s8rWvpv68llDfCqzUnMqIy4h4T8wWf3H1JT8YqMV1dqj8Oauiu9vgvd//+YRe6d0QnNKSsJO6gwp6akuuZOvKn3+6t1gXHjs25QtjyERkDmZvnbs9qMfCjer9O32h+ae2dXFeFUX4SCqLPXFkTbe4aVNZQJInI737feEIVjZ2QWtrMrPvbm7r+4DCdu0YoNv0ncz2sUCKJB75LhtyX9dwKdPQLX1tfTom5nGt4PbISSx9DPicIYHyyT1Y5Xisa9ik8NAj6fWMuKsyE3RqtcagPruGy0OxKgUe3p//oRlMAYk003QsZjlRkxkGERMHDCamDqmMLPAK5mFGJxNwEapmYnulP1cVzlBHE/Astfwz7p4Nn0PXOL75pWO8CB0vVwTOaYpLCyUV1UVXQaA4lfE6CekE/WPRTW9WYcXUMr+xbSC5Hvy6EkUtloqMNVLzEtrTeTCWWdm9me5Hk/fgRzRDVr9YOAjWFw8KhnlEe7E7oczf7trIsx7wspoOA3TzTITV/brAKTg64Dp0GYXdYdU+JhPipF5FsPGgZ2Wb4svERtbI/J00rIgL8MyrWedHk7cBCngKRF4cNt+3RXf9fmkdZpu1xUXdilwe3c4/pChykuKjjyt+bvpxyBD94fi214kAxmzXYH76dzvCFD0WxB23EaC4hVCkoVZLsr7jG5ykwg01Jut1/fSDLk66i42OZH9urXezErqxf0S8UF/pWhyjR3fQfjO6xp7ubbA7tjVW1Bjgp827EpiDjO2sLF5TANmccD335fwxfknB44GODJqpOB5Pu7SfVtuMV4UZ/vOJfh/3oGmesflVlbKJAPrfRJvq39D9F8l9YaBRtD7fb9ezXLhL5bVsLHu6hqam8/v7Jqqmb9EmBkflKEVvlXH9ZOA+V1t3q+Op2eL5YLY7lxRxjuHMzj57th4iDCNr96X5VHAOPiztl+jPQc766VZ8PAeXz6n5SNAUJuVDt9Bq8lcci4oBe2y/efrduu/oW6G/5UgSUCH0BJ7wSPSeGYenfe760HloLu+fl4GWiEd5dGKD1vYM33UfrcPiuOr8xS0fl1oBR93EohthgbjP7gxx9vrXREGsFljPbFymq6hSfBh5v23H17ratjfHfCWGg1DFHTYwvvxnhnot9cyeoev3UvMN445CGP31zZ6KvfbOsxhb5AMEGv2vN9bTyrSkbth7jGkWYGlwevNdhzR7hSxBEPDwzQvz03VeVc9PIm/ysvKTjoDHh8ffw7Upwmrq6kd962taUa4x8ppScU/rL6aeiJSfmXZfQmPrdUqabY80PaSn4ajR8+9PZ6vZobsSOnpdHqydQbCvg6z9C58MFaUljoQb3WO1LS1afqry10GAYWfgFLzVFR8pFoRoGBi0EMK52RTpuDiGhtUvsXP92cl7IelHV6BBiq1Sk2TsILPD+ktDZxpoN1JOcmJjI9K7PfWjFrjyzXd/9/B6Jfurfcy7K/q466yxqV5rbeyJU0zu9Nykp6vOdAIbE23Pn9nbjUoxljWr078xgs4P8IDP+avvLlal5rH9zKbuEjsrXv4mLTsJrqHufM10XvSzMHXP7h/CoGRG+PYd3tOgKElfAym+LKw89jxmbCeBn8bm11isrQ7c7En3e5EJoyCeUDf97gWvYzWg2E/Z2Drh0iKbQpR8JpfH9+BQzqhGfA6iV7D7UYcv99FQOIlPKHp5zmPXkvPYthS+ub5pp9ZbnTYFx0t6dytT+qWjIXJd/P3YSQmFmC2tPvgxtkXioWh6y5Pg8GD+ffvH1n+01A1aW1rGgaSaJdeF38N0s6nvOilTCdiwXAg9jbdPsT7H0fHOuOFrQbvVBKChrWgEhtDwp73mqj/bW+OFomkm/QJbO4JYR33DPbxQycWRqEd7RWhFqGouBi3iaMDV8gKQWAgUKHdmFcfQPQUauAlRMDCzMyKfM8o+Mj3mxenkSOjHGdyfvF+9+LCuvRynuXf/oaGJ8XPrywer7SDRBq+O2PUXpa5vEIE1qmSzlVrds2k2TawblO/Q54pDiXj733N3qcKXgsBbdRBESk5A+1iBa/+O/tLMA+2yBZ+A3Ce8bGxNF4LO+9O80o1i8vwXn41RcUAjSm3PbsfW1vzl9E9yhTQYUul1S5epIyT4WB5LkdWm1viCm7ccVljIezmck0citJRqBavJYHVKl7rnV4cpq8lqBZeTns2kKcWDKKXg/BnldFl51oILUenEjpG6f3sguvppj7ZcQR6S3/2Fx4roRWXAfrYLfxj8gNI0xBa3wu6cHxSYwCRc22dbUuiw8645ORniDtLDAVf1JVWt2tdazs3HgX1Lzbe0LDvs6ThWV7qaeJ/y1QE93uqKIZSmcz1orm1iAYcLEhDviE+cJcwF3rmYnn4/k+86Vq1Hk0c994X0yuxs6pMWiEUr/srBk3wcs8H9+/o6tgvVTNbgl5INroN77NXQuvz5tOtbfweQF7cb3UffWxLrhRazmn0SqeS8/jlfkuulXaUUf97ceTvs7eDR7z5R8/riNGAx4pEQLbu5bXyeG83DTtMD3MNovBr+bnSQewCdWAnA/t077OdcjYlkqGmZlpuZ/4SIKVbwccQFOAn/uwMaJIimH2UBt60QX7r3SxQzBk5FJdOL5bwM31HRPw8sxIE4pJsXadIGJv/fmUDzhEVFhRQfnV/70JHmAdiLVLU4nc8wcV5bJ1eVcl1fjKrZ3/D2HHh8glS/L/Hsi3+oKsl8Q+Roa4bnAykNEiY1cpIX6RmFfBkGjPHPzz8yzqdWEo1hRHA0EDTEEmCIaEswVpFN1Fi/IUhAIUOuYq5SgCOJM+OHBDxs05EWvgw3en8VhcWbED8ePrgLHfL53mRy6207fi9bKrSc+U2g47AmH/Iqck99BVr+n2QlPfCfeq37o7BkFPbqyn/sFPbedU9V9b8afb0bUYalpXIxLH7FKHsO/30rOJezd/hbtyvtKrJPKTin4RSk8/t14z4vikRgcrMm48Ppx+dnF9mc1yvBMFhJi2EWYoO1aPcKl1aLpVahUra15ml0+R6MK2Eokq7FAAAYGLBTOl4fJRTqFBp0TdR1oHPuYg/nRtQ5iz71Kr0rpwhxPK4Ku1uwl5BcpSe+mbd9CoXjC7yrrL8HSTbK2d2xnL7GTh0H8ZlUcSP+qhyK9VLbJSX70Fvtd96kTGwTA5kb7YLCRaKf/AArfUMcMQ8ffO6xEnoM7TNx5ap91Xlw66y3f+06vxGUDR9dGZ2vGamNB0eellf6ntl8G7N3v2k82bt6Hlz7NvJJYG3yoXgQ7fteZU8Z7d57XOndKzPBK1UjS3dxd/z1erADiAa0o1qxbJiug5/9XWs6LX+0HDhnSwyon+fLjI6+4pf5310z5IdXnAfGLXJwqOgEg5GLX46lbZRHaSKWFFFvqaYUmCQk2MdoSkwOo3eTgDCAWSr7kFB3XVk68Dty3ftZP2klpPFvfRtjZPNvfNtCdLc0fvu+Xvjq/9RJhfvs6R2h7fwGjVFyuj8RCyFcKp3wffBfv5GGPDD/xXezichBXfsP/rfbyHUSVKNzxB80zUm4eyNHeYDdWlT2FoKkbVsjWkV+a7zCM69C1ltkxklwxvB9BrWebpwbmc65wJqy2PmPd5wOs0Peb40djisz7lgNIQ4dTeFBriAiIiIopUViIS/f8VHR6mcqS+xblskroOppieLzwJQDL/zvGUNPdDZVEZLcwWIO0kb8/Pj6XVQpmU6BC5gLKwvppDA4gAFhHMfwyu+7+Mict6fe2y3nvUikaq8PHGqvPSHeuin6LfHDuQvOJGqX8KpSZUJdzjVpfHM32/3qKcut3/VEKJVzsjupMgPMfmIO9WFOu6FQB9eOe0DEdmDQQ6S7h2z6gr3w8PkLK2aP4H3UlzdhrsB6DS6Ox3Qx8mOr4JfV4PV9zTCvq3M35X8O6+OvW6oKhkX/TvDreRZgWztExn2swtgCAjRTihZ4yp5o/fNps2tLOpIaenTgcfH2MHHNqccFzD2vobfUhhVtPQvG96k7r5Z8Q0pFUa1BvhLaWq0G6wMWi3+PrBGY+P63Yz5Nd1/feebTPE1E7lZV7fN667Bzg06HIxk57qGklwqMLlZq7U8LXW1aCDe6cO1fsAzxdfE/vOdN7CEefIXjDXNXjRd2g22SsqamL+akOCWuez9in+0nrloXuvbi+Yfn0yxOmN2MsZHFIwlf1edxFXl1+fbadtpK/wlV7JG9ia62l0lHx2PZXfItF/CZd6p4jQzhgmByl3QJu6ZYNPGnSv2UG2Z8ZKicLZrZDfimT4D9vSq3+HnxGb2imUB/W4lsRIr5R332aFML6yBKRF7FBadTb4Pzij7d2xlW+qd6Uj+HJUbC7fkOXuBfGtbDxZLT7od6ORCh/YTCkvtf1OLJN7tEsfQ0NnmrrGfvYX0fDQKPYGlduqhnE8EvlU+LT6EB51+3Z+b1xJi037Oj9ES2yspzpMDSwlfHVNZ8JMyEuuudBbrq/+a8tks2lf+xd1zz93VUKCqmc05uZGgyokxczQTsWjRODZpySXhcvzNPPdkfnYlGpZpOjiwFVtCTDcPrMfVsHb9zYOJ5HjrSuyWyuLh5aVUlcwPNcb+90mVY+7umSj/klnz+lp2qmvq4PBaEtfNUz63mgAK2rboAz8pAfvsjwPxlbNpMv+oUHQJ15ifJESlRNfwPxwSOgkC0vw3dUxLgLFE5SjBQuaZ4CZ21UNv0h/Nw8bYrYctKamOvZNYXIhRjSMpW10w49004aV0J4tGL67l2n+CJlqnfN98Dw1yP+k20gQaLtEsrvhF5EIPZsvXUU8uc9DeiMjCVYF7cty5vsYoR1LkXhCnpN/2c3xYskPEcQe/WqIzID5H+gEp0s8X5KEn+o5r53LpT1d5dAoCDfTcEXhIIX+XcvkKEluynecMR0j3//u0cMPTuAynaC9RnpOMJb3cz/5ncGRWkBgvzq1R2nA0YDA3JkW6GQDPTD1Clh7kfCcuTTw+IayZ/UqlcWD2V1aC/DTZOM7VhR07Y5Q480x7rppbxhMBqmD7r1zRIEU4OPVpcKCLcG7lg6Y2QqW0Re4zi2b4kx5pRKdEwsTEIRmh9CtR+6XLAbaypG1v9EPohazjWGk+6JwnjQmMWwpUL/lvqfo9TGPEyQpRYVNLWrg=
*/