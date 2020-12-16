
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   define AUX778076_VECTOR_TAIL(vector, i_, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c)<T \
          BOOST_PP_COMMA_IF(i_) BOOST_PP_ENUM_PARAMS(i_, C) \
        > \
    /**/

#if i_ > 0
template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c)
    : v_item<
          integral_c<T,BOOST_PP_CAT(C,BOOST_PP_DEC(i_))>
        , AUX778076_VECTOR_TAIL(vector,BOOST_PP_DEC(i_),C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c) type;
    typedef T value_type;
};
#endif

#   undef AUX778076_VECTOR_TAIL

#else // "brute force" implementation

#   define AUX778076_VECTOR_C_PARAM_FUNC(unused, i_, param) \
    BOOST_PP_COMMA_IF(i_) \
    integral_c<T,BOOST_PP_CAT(param,i_)> \
    /**/

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c)
    : BOOST_PP_CAT(vector,i_)< BOOST_PP_REPEAT(i_,AUX778076_VECTOR_C_PARAM_FUNC,C) >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c) type;
    typedef T value_type;
};

#   undef AUX778076_VECTOR_C_PARAM_FUNC

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
rjun7l82iXV9N2fFfcIZ1bPU985z9er7oZxVWqBX+nAEZ018xRn+1zPOhzhbOkr9/shP6v4JLzJfN6i/O92B/tCr+231w+55cdbDMU2fMt6cTaiPEJy3hy9hL5yxY5Hq02kbcvAy+ugPzqZ5gXU0APvkpD49zOrvKX60h/kvwD4Ub+ZsR9avcwzr/XXuP5Yzj/ujXw9whtgy5PAx5mcOfgffl53kzI9nODud60LXYYcSGPcZary8h6vf5y9V7bah36HjWWenaOc16IH/cOKCZuxtrLqP17vIj4P6vw9ym4zcFg1Bz7mq70v30P67sEMdnIF4jLOUxqnv3UardgQjD8EnWQfr9UpOsPf7WQcV6LvcV/FbbuQM8fs5u+k+1oGzXvUDean8Wa/m4XPs2w3I6zD1vEOcBeu8Qaee68pZK2+p+/o8Svu3cMZpKGcczqX94eoz2ciZZGcNav1+plf9OYL9vEZdl+XI2erVnE20gLPZBtJ/5KwsXKfWL+vjkBN+RT89z+UM2Ab8rXvRP8i520b6ka5Tf1/OfXajLzk7MPBxzmBr4kzBu5HXW/Evq/VKPzyMfbpaO/sU/28087VL9bPLCv2UwZm0YTo1PvgB+W/olN6bxlnjXdhF5N9vuLpPpwn9YFTXeeCP1T1I+x5CPz7KmVYzsAux6IvDyNuz6v/Rv9I+S3X9VmfOXPsQ+X+TM1TmcCZ1Ln4O45zWpNpRFIoe5qz14BjOxqtXn0n0t8gW+fPk7G/sth/z4cw6PFKN/W7lzMkd6r4tt7P+X1H9aHE0qPvcyxlhu5DjX9F3g9TvrJrVPFUN06vfTeGsJvybzqGcYf8u8+DMGTgf4Y/7cpaZlfq/w2j1mduJP4s+XOXI92fxP5EDO+KRI09yNhTzFIkddH4ef8ONMyE/wT95Q32a9cQx+H/6+zhT/Av0XCT+yQ7syBLkZZJOPbef+qx4BD/gQ/ShmfnmTDxbX8662abak56F/I3Tqf4vUZ/etNurlfX1IWfnnFHP32qDXaOfXf7q/sVp2KkXid9sOKuOv0e2qvsXmLEzCaz7l9G7D3Gm23j8bPxN46fEpYGWajzqud/j+GvEiXWNejWu+L0ON3OG0F7s32Mmdd0N2KUu5s2g2uE0XH0GbMEuvIedzEfPPqDalf4m6+cdC3X/JcSfvyJHiZzVNNGg7kO7XQap6w/dou6fcAL/BXuZfpV6/lZN/vDzQ29H7zPvOe8S167mDF/0oA3zsa4I/+kQZ8V/T/yFH5b8mfq7cbBRPcdIvHdYXbfvT7Oanzziz9mcHfg0ZzA1qesb/VU/fG5S39fgj3UvMaj7DORMSQf6+Q/VL+9b1KfzLvzPggGqfw+wHruMqt/Mu1WR+vSgn3X7WXeug/A3jWqcuzjTKhg9/IpOfZ7l//GcbRmKv/03/Z6p/t74Hn7Di6wns0H93VGn5LMcuUuwVPJuYrx91WexJ/P+Ne3O5uzcYOR5Ev0lnvV5hDMLvbAnV9HeWOwb/mPyt6pd4e16NQ871O878/ETtjHPLcT1xD8ubzNOEdiFQ5zR1Y/fPaWur3xTXR/M2airficeL1HtzhpG/D0S3uZGeB/66bYe+f0Nfb6cuKoT3mC4Jf4UduBH/IGj2LOFPOdb9Rl+bT/195vwQxln5zjO9GvE7sznbMN44tdu9Nc/sGtJ+MnEk+mPMC9DWUf47+nYbw879bw4T+SzTaf+7o7+2K3u1xnE+q1HP2HnEwarvxs7iPd2otcWEEcfYt3sQl/1Q/87oH9C1PgVOBFvT+fM3knqd7b30A6Lfup5zrS3CP24gzPAR8HnzCB+vZvfDcPv+ADeBzutf5C4Ej+9czxn0E1hHvA=
*/