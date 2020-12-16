// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_RESULT_OF0_DWA2005511_HPP
#define BOOST_PARAMETER_AUX_RESULT_OF0_DWA2005511_HPP

#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/parameter/config.hpp>
#include <boost/utility/result_of.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A metafunction returning the result of invoking
    // a nullary function object of the given type.
    template <typename F>
    class result_of0
    {
#if defined(BOOST_NO_RESULT_OF)
        typedef typename F::result_type result_of_F;
#else
        typedef typename ::boost::result_of<F()>::type result_of_F;
#endif

     public:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_if<
            ::std::is_void<result_of_F>
#else
        typedef typename ::boost::mpl::if_<
            ::boost::is_void<result_of_F>
#endif
          , ::boost::parameter::aux::use_default_tag
          , result_of_F
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        >::type type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* result_of0.hpp
9TKJQ9apItSeNFMcpr0fhZPUPZVVn6DDiLMKI3u88YaNDudaFU4ry3sFCcfqPsbyPgD3vvcBFvN+c7hSn03ruC2lHSTnGy7mBKcQwllnkO2FwCDbvKAg20NIdHCQrTOix83K6856fewHFc9sTjAL1v1NoAr3vmDt188zlePKby09V/1SmZ8LFl3wp3RRai5f50T3d5bvpyT/glj0ycrd+8rdTaQrzpQH62dFf1Pxhup7kKPKvCPYt7+JkfnjHep6TMjntqnONQET7b79T4zMb+9R7uqEfMoXiVcFTLPrdPh5JnRKuQ/X87qflXlTsNXcPRaGTFTXeUc02NS3V3l+oMO/qVi1Z33fF6rKaR49K/c80t8vUXaOQAfj65Wsyt+FfEGr7WbvabsZOWjvwOl26bZxyAbkCNLKmW67nXnwFmdn24/87hGQbpsf0NX2ZkAHff9TX4V7a7B+rm1+RivpeUSlb5u9s5wDl8gZcCuQpxClO1UnJGPluXmTTGvcW5QuvlY7ApcijyJx2g/LQJX7EV1PklXbvJ7wm6ux7Rh9XNJw99gW5HQubsRwxvgWEDYprE9QujMgqKszzDu2MfAxuAWEXnhsw9r25AT3e58tPc/ElfkHuwO7EvK7hLd+9/I72p7OOX9dbfeja586qO+d7jP8Umo+dU/XjXKl73bOzTI3iMWUUIAd5jBS4LkXelCFM7DKuNfV87xLhfO408UXFa+xXcocoDv33d1ttyOf2tvZUhztbUXII8gJ5H4+Pj7a8KvrUpQzzJaG7wjsW1I2ubbT3IMk26NtGfY2thlwNfwz/Ls9wVbLEWFLZqfcYDgBLocPwz3wC2iMM22lnFJH6HJadNAoJ2dAWD7F1Jpi6qOLqWZlUyxl01bKZoIy93UYZXM58jTls4fyaUjZjEXupXy+qKZ8spX/Pr7lo/WeJ9ct5htK79PV9WZSTz3paU/ZVdZB2kivDtb9mzpoLjpoLzpIVuYblA4ykFuQ79BDFC1U6QD5BD20cfjXQ6ML6KHpBfSQ5qOHZD966D7Kq4cRJj2koYeeF6mHTwvdeugkejiqzK9rPdyIvINcSr+UhS6UHpBmjq62qdXo4mBh9br4W2H1uviq0KQLSZeVLgaP9uqinkkXXdBFp4vUxQOii66ii/uUOdRp1sUuJJL8z0Efd6APpQvGhQL08UQ1+lh3AX2sv4A+Nvvo4z4/+si5Rutj4R5Pf16EQsahmBZBDmfdoMkuV3CN9DFexdHB1lP0kaPMg5wO7PqihxuQ15FQdDAM2YZO/opOEtFHPvIQOjlVjU6yVHj9/OpkpFz3p5PJ6nqC6ETSx5pVbewMnbQXncwd49VJhdaJjHEtnXXCUi5OL1FGPGilj+glQpnvdDqwG4ZuVqGT95H66GQUcj/iYp2nOeuy09HLVuQsuunj9K+bABVmpl/dhMh1f7ppqK63Ed1IGhnPwrAz6+busV7dpP0Kunm1wK2b/qKb7cr8D7dukPvRz1F0k4xOJiAPI6eQMejnOvTzKroJYF7V39nVdls1+tlaUL1+ni2oXj9vFpj0I+m00s/2cVo/Cz7S86Nfrp/pop9BnvU2Ze4aoPWDnEJHHdDJDOQZ5HukD3rZjI5eR0dR6CcLuQMdHalGR7kq7Kv86qhArvvT0RwfHZX66KiT6OhEtldHqzw6KpCBebAzLMjlDFJaqlhpqEnrKbEaPSWquLqxBoBZz+d+j566mfREG2Resgj9/BkJRkcDkduQ8+iqPnP08ehpI/J3dNU+wL+u6qvwB/nVVUO57m/NpJW63tJy/mmuT7G5Xl0N8pnDtHeGmapTzcas/WreiU5ETx8o8z6lp8HI3ejoBNKd+5k=
*/