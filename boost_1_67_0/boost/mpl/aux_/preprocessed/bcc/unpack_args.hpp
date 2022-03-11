
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply
    {
        typedef typename aux::unpack_args_impl<
              size<Args>::value
            , F
            , Args
            >::type type;

    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
V9h53lI1Mx1Zasji0rJeFhLq/axEHfHbPoKWzEJsCfs6s4l8ESYt5L4I8J8AZ3CZuP47WCSwEyODYfrpqkPI7/mpiyg0jFsp/FazdSfoMJHwbv1yyx3G0cALXMHiEnH2yl5r7Pw8Ef13nnXNuR44FCOONef+Bv9Hf8B/R6+JrVwqRe9V5tkwfunqfCkagMYGi8LzgNK7007Rd7F1IttMlZG/jucYcD/GKb0S6g4WU5YsPQsCTfnRs9WiP9s85p5yyb6wnLN+uitAn/4B/0t+B/8f//Smr7xWuHfOsfdoZiODOXY5Sc3VQ8QwrSEYOOUwcDVrnZR8WGzXeroCrPyQgA0JazlPGYd2ikpCCNKdqiAd9fx00XxI9Noh9qVdsDIfEQb+Ybbz8lxpUSmVtKhUb4tqr/PMw5e019mV/fmbKfr+IPtvlFpwY5HbhyKjYAOy8AAJt7h8pskgn+klnZF9KoAhG3l5ksa77/gPnEU9DqNwb4jtfINLt6/GenvI5Q6urAJxZbFvHuEM3sChRLpnso2b7dzycQgXrEEOuqogU7l6+aDtzUG2f6MkpaJRUf0H1jA0wVxyquV1SdL1I5Y0fhyJIJ/w5G1BBMySCvCIOETSDITKnyU5YEJvmyW5UGNA6nq0JMpSanLMhAvgD0sCXpQbaTxHz73Ws58Uk0m09gYdFsNSZKrIv4nSBaxnjxcVG/Nr5RYl5YU8zVrZxX2UW0f3ab2xfmOqWdJqOBbGYSJ7dQgXgdoA4M6MDehLX6eP1x7DeJWEDCOGnmj2qlZtxB4SI7bBJMINuJEKpTpNd9uUTTPhi3vTFGxCyKY8ZonPtrk/9hxZmW0+1DkSSWHqx8QiW/wWm3KHJd9amYZwAjalyKZI7iJLmXyLxbx/kXyLTRuEyLWGKuDLVKpiElVhVWbEZ1uphrFQQ6ahBmv8FqsyyFCBFSoYViabqHirVjyMKdRAxU8UpaO/3BtYgXumctz9J8/5lWPcX5qXW+UpncPERMyxmhz51pUpZd9idUPhJsPMfId6MBXmQ1Qx18IHSXkDByl+q0UptskBq9tBNX248gqoKYo1ZWl9MRVZ4rdYlDtshgr5aMEwuffDiBH/bZOM5x3cDfIaDEAq//guswqVY3gvrymgx1y/ZpSfbGv7HGPCOhBXPe/oWa9V8iPcAIIEB9Sgm0+YIub4E2me9yNXsvWDkZZ99AFkO3MHC8fQxhq/sB7vvEYZ0oWGd0sp3TxKN2Awt37sJsy2Q2zBI7T+CMEcHiVK7G8eQxHMmveR1qPgjGRMdYhERFyzYBAchq8RkejwIEa0GT8XYMEJiCKsO69Jtdfxck9kuBS+ZA9WW6VYwhQdeKCGpQnBt/HAEZulBRnko6v3UpqImhgNVpVfSH34X1vSVF4qcgX+3mwWtFJaaYOyCWcGrRKQLitNfF566tF/qIc8tG/JqbMbJMN8LTk16vdSEt6BVUUB7eBxd+QlFwjkLj3WlOhM52F9RypPtadxJoQHTwcuGOgy9tY5FKPFrCra1kV7lYwC3mGJzPlwXNxfXV+xwnM+cpkqESvhrr9T1yK3cpdVhFMGnhpRrpdUn4jMNOoT6goiN5Ms4Ep0vfKnCUgTWM2oNCkoo3tJWN2pdvfh9LCIc4biDD6xIsS9OdoNF0SX6oUcFOK6E0bIPfh9EH+XqwwH2d1pYevTedEBKyHfP7sPrhR5sC7SVNasJi+9+QNxfb56P36/fyD1UpVPEBM/DCogmU+KBEe1dwuGVRBsO7Ou4eKp4QNRHgo8bEMKPcLBQK0kY/7pXxCDrguX08osI9JLYw09lISO32r0rxELMXp1bC+uLCkyWF+kKdYF7vWS8Q4gQcvABLGkkOWCLjm5DkbajXQ9XQPKZYi8QQKTpxFBxp9Xn1+Thev2kP2Zej8CeVO3VHtZtJb1b0QJDR6d8jo6oekqkJ+kC+E5PFvl5+mErZlJaegkhB6/YFZVT3Mol4NyOcTbZdpbp1nq5eDe+z6LPqDq0EIcx+DlUYjl8ON03YujMEVoNBHGacRfcV98MyodvRvSVflYtuIoI9sVq5nbrgi5UVA17u0TH88V9/YE/Wzpp4Ml1OLGl1vYfPiuOHDDjSxdmRn3Mj+7BR8hUxqrTyNhiq+jiE3ChwUW/WkK/RXbzZfKSFx4fKk0rtEWytG8+hQBj7Iv771GqeuR7ZI8xyLPcchzbPIcq15qownfwWUMjMXAIvZPc650T0Nvfx6jP9ce6V/6Z/UY9YH9mJ8KkvPnQGarJd+nlpxkdZlkosv5P1SeIYBqBttSiTCQCFe7wTseTp+B7OsPHVLnoDoXvLxuZDq8XAFTd7ZBkuql6IBYZZYUcRLVLXuz5JpuGLk1XyQS30oo3kmKL0cJZAvZuZPLzkuAkILVUf1LUkIPQHo0B6gGZ8gf34trPCQChMBCtVJZOszSSDTZeipL43b3EjBvdFBsbw4paG9QcZxJSEK6SrNdeQ53i6kGk5hJcykTVSI/R7vFaytDlBE8Xf6GpwtHm8U2Gdafai9TFHunm+6rOezPC3uBJQwVYAlP4urptCmZr+Gv5/HXNgcQAXGb5B5SD89i+8wmnmhw4zp1qbERZmKPHtDk7XT4LWQeJ7eryUzjVo9BNhGfsGFp6p6arqwumAKlXcs+XcytZ06ZKO24IPsAn7A/m9S0g5XViy0S1w3BJbCUUwgzDMC4h7kltQGPFNZfzpx/Bw/wHKtI454WAzPqKewjbW+zCBPiiK97xkyBOr67nxwsMGxp3om8M/lbF8PzlX7Ex4n72ljOzzLIs9rb4U8Kzkkq58IghbV4EosKJ0LMPFCPwAd5L2zJkDxvYnkrftfLtIXsjZXLjCq42CwUzKLHXDSd/dLEoxt2qJG5e0zRMaH43o2E/sLDPBS6Qn4e16EMRvqHEnedyMYF69duTGSC/UH29w/I3QHf7TLrNux9jDoKZ+hOMZ7/q+vQG2XwE0gpXCnpSCxXxVa6pMg4bOkOQ0tt+EBSIT9Sw2JkhE0hVsobZJjgXvFI0F6Dpgnx4+1VOLP5FS4e9q7/oCmoz0P/+sRkKX8vzeb3BZYBLy0FacDTU3lXdaLiHg+lrSxSNi3ARLbdwqe53Z+Cn88hdjdhUfgW8Q022HMlnn/FTxepvmyvZgvU8ocuTpaMeNEsL4QBA21KpUPJCptEZEDS2DpJY5slP2HT4gU6KF6gU55rRRVuwBqEPXmbv1iodJxSr/N5usEeydn7hE5kvvA4CkPmQqv8sH5ZGXwRAr0wN9xB/3ekjPwK7Hw4l/zB4iJMuWqoYX13sEmQMfU0tya3h9r7JfYVeIAFRLdxyOBYz8UoiiKPQhkqBaTpi+CKzTvhR5jkHiR/+WKfp8txnvxmMqrsVnyb+87XwE88YkIsjE/YWny9uZy7rRSzAKUWOrvyYYgG7TkfzdCIUSshp41ULg8G/TpSKhKGgQtwYSB6e4nLz4mCJEVRSYr1JpDOybTH7bhDDZq/YxdgyNmEXyMh+kf4zs/BcaRWg9e76PUZIlb28tdKN+7svK8SCaDGHUh3nzQJurt0UQNeF7Ac2NNlGDutIUnXg8w/4l2lNGE+1bF9JzZhodaEJWoTptHrH1ITPBcma1TVTeqZUiLI8MNKG9tympo1HJuFTEKI2oXEI/rXhbBlE6Fli1QEKSQ2WqBQ8gtGFx90CmZvnKfZGxyW2NgpVu4ryN6CZL30yb3xtCkAOl8pHFrwLnFfd6g8i8ledR0eQ7MQ6mwmuW9HndjTO6Faz4HIVP4sYsNnM+hZ1BUelcjc8vhuYQxW4Ofs027k+++v3he9Or8WKfPoZcLJMugKDyheT+Wsr0XinftSzqTv9qq/mqRL2LDMrD2FaGqXcTQ1Y9R4jD32zP71z+F7tGMJnFQ2oR+U0uaurcP/v3bv3UFhe+hXzUYyiMIn8UCr7G0VkQjaRCQC70m3t7VE9jZDWW5vG+IoeFvYC09j4c2E3uRJbwZ2fpVT8baI3y3w275pIRS5ei82A3rj66URiwSMe/Of53AF3fIK4V+dEwuMOwYqDpQAIKGCVsfI6d/fyJlt3WDi8VGawQRHJxYQlYgWqGJUbkL3boSp3JRFX+BJNn3RwCpVKzuhg/3hEJPqmM0fpDlMUu+6vxmp1W24eOvSIrl8KiNXp/JfLxpyv6PnRiBGB9wVGKWWT0KHOgkYQ4TidCPfVWQAxFrEVo5MgZWG/RJk6+YLU6RmK3KxL/VM1tzFh7ShZtPvCnLFpghocLfKMIlD6PKQcrOy7m0acbF5nyeuj2vwyjC5ANlXlXpJKr7Shn7xxjA+n86gheA+Q3Olo/leazSTTCL4yPwiU0OZ7D03xzJMUl5C9p7Mr7Taq14z7JVG4kmJnO+NcDiAbnnd16CJdZydTOUXmCWtF+Wqzhlp6r8DY5zEPZawT7qQWUbyLxGdgC851HUoyPXUmhjqC6fWg9kuuQbFCkiyPkMykMON6+YLkRinqawa/Oko9Qcq6HwM7tSTQTbtuAU9v72MvXxmstB53qaEXMosROPQ0DkwSmYSWMcxoyMAgn6tIWRTcsZPHOscROCx//MVrI9KJwqYZ2278Nmb3KrOLHyplZFhk1yTjc1fW242ylS0cpvYZBjITvJVT04iSMXrjJgiiZbOaVzm5TkccaMkpYl4ED87/CGSime/ouXqaURjIUxWBBW8+zHhjcI5xBd+9Qh1dPvgtwsM6w0Yn7wT+Vt78MD05G/FmY5SIDZVPhCZwFHpo+MUou89/weF509RdTwAgENLtX0LfFTVue9MZggDDMwgAWPlkSpa7DgVjbVJBzUiA6k6dJJxMhwxYKvtSVO9pe1MhUoQnLx2dyYg8vIUIyq22NKW9lALwsHwOCRIDgSkGk2qUbHdmLTGI4V4pMz9/t9ae8+eyYC99/6uv59D9t5rrb32enzre/6//XRnXkG0QMBPCNeF6CULjYkdOU7qFxvuYuWvHfDxQcaOJ2E6cEINutWV6HcFUgMp4S7NQ1+UCBwog0NkZbueb61d9R+A+r6UATo/PE1Lkah8q+/j6K2+s9EbaRJ8K7Fqotdo3+4SGqTO0zj3Yvki8YAgni9yRd/HsVf6hrf5W9mj6esF6pdF3uzM8+M1tQFtigyBZoTd14BkyhtkH/WpaQnnKUKmc06VjPSj/Zx+NDajuBLgFvwQtzvE7auwcKtsemR25wKRxk6O2Wtj5ZiJ3EbwWds/NltC8Uz/x0xlzgQZpc2tLh9rQKfOLQhFLpwTa+jO//PH3jTKQre+RSe51MV2mX0poVnBCiVZ3lICli1YIFFfue0JnC3ZvBl+grZp8Ut7U6e0nlzNJztw/YT1JCKtJy8ihngPVF1WV90LyMnZSnQNAXEDvoC2cL7rqVb5vavcxveGB31hPGvRn0WNZ0ZbkGALW31vR2+W7Z32BXrMdUpM7fX7wj3md001nsnK/b7ASXMBm6nyaV/4pLnhv7jMlb+k1rOZhlWBAgGy8Liv3fXUvoXzF6j7RJXtRhXhocvq2Za9KLFXlFjt+swvxFekdXJBqlV8fVonZ7rSvxBfkTY8nzdV7hdDZzQ8LOML14mk1ac969hUhP779rmeMvf/+BjTgHnC/URR6o6bXvc74zlbi1x1T1mMhRG71VgUg75Ar7mXj5iaHfCFe829XDgmYx7YIlfPClj2gB46D9emmvMPevwDQ+dhZKoEg8/Oh+D699HZ0Naz+OMKPOZu9RNBI83ESd9ocov1G1vsUhAfucWO8hb7woCXT9Pd8hZvsYfLol8RWyuft1asHO5M/kFf+7JSz15ltr1vVnHlxCjHTfr7fe01N9DdXGWBve9LuK+BTfOfptKf0+9PEHa7kfCi9Q/42pfuoLvKZJM16R9O8d35lgvjJaYZV/8CLqu+gD49hMw+N4Pr9+2PDheAKoiyt7FH42gcwmXs1WiziKSu/SDZQ/zZa5y+T6Pu4kntxNjFHMWTgk07LdGpjPSeYrcdYjL7csXmUtgATRLtPYB9DiNLuSKMqIFBhTWOyOfBS/oxoBYqbKVk/gSpc3b+FZQS50iImIQTIjOOWBx/HWXk/jVxCJJvm5IDQbq40hG9ntbBUe17z8Kd6YjW8GchlL9M18yRzDNeUD1MvoGOPHXSKjqWgEHB3FQw+So77Re3YIvERkLMPKr1baV1WeNQR1tguJxdUHi8Lulau4/Y3Zk4bAU6DIY/fjNGjLbZ7RxtimGji5tYLCrlOYgt0r9BplfCyvvVX9OJ+wuWTQwalDa+T5692U6v9+13Nf1cxtOklx8lyp96yWKR9O7UbywiY3Tdv1s4L1Vx8R6kSY1dL6YoIQwpDuDsB+1E/0mGUYLOYMYhNuav3jRfB/G6Mead3+c002OjqzV2dX/fjf83dcVqWqi0oL9t9VNtQiWs42m+OcIE2Sv3wyrdVwz6nJy/pgT3rPGtl0Ox4lZXQ1ouqwBcbyomNr4Ha8ESic6ilm45yahfxVgAAhh6Uw5nGoAnMtv3j0Rtkb4cXW9Zod31cjK5MNXaQhlzm06/8s35jVorIhfNSDtbpnvg/Yo0D+P7vIBjjuKfZhgftPvx52BbwwYpq7AsTCX7PgBVo465qgvUI8SFhDVtJ+6FtXh7CXAlrYISYn2G9Mwp0NaONQSnBx2S02qGo6+ykt1910E0U9Y3Mu1pwt8N+FWbV3GZVVxmFpeZxWVKuUwpl7mLy3AOhHVBLsM+oCxqKytZ4OZEQMp6TgckBOyVnAxoHWRspAtbz39IoPJDw1OcXya/rvqFMbsC6DqRcsXfpQQOJMevAT96S2F3qELxt2o/9wv5Vm2YrqulmSIQ2cxPIcaN1q3AIbPAIi4CXcEyzf22lOSIEE5mutOreS0mEa5guE7cIWrp6ph1yzPOLZ0RHELvrvuHUEZwmi3/iYS/nV3R25XKDtqsSLjcT3y0p1Op7PQdq3Ha9tKSavN38pIID7ICucNjPBo0HnUhr7pVLbmvXKSr5CwNlZ0ABQBVkSDb9GKRGmNCsAzpLaRWXQqgUFBPJBp3Ccmt2uxdgBqk/UP/9tFuOxEMhSLaqjVgAiaKywptxRq20fu7pFeFbHACzVGKvFHngkKAFSGhpid0ojCsnil3CUlANGeeIPhpaTiDoqmX8871pL7gJuMLSPiIDg/JBSF1DiFddAfloZ6aNCRCBtEiw/SJNPxFP4Kz95hekUcudglP/zt/ltMvnLQwz7SOLkstqTG6gkBXehAJUfwObcLtOfCy4jX5mLEmjYRgG3MEMKU0ZWwkEQmj3rmHEU4xMKwdMA9MSnZ+NN3MoudKSV1NFa4NIsnWQsME6DTlR15htn/NuiB4cR6NjOLfrfgPwFT5EW01xd+u1sNGUbr4xj5b4mtwhW38KQKm+a4rsZKzOLL1I29F/McFloRzRSw3/mOnJXpr6ZJjqt+p+DXZhKtxI8fuLq4UtWvCmTWjoubM0iVv9P1QFpqurhPGlccS9sc4SSvyJiFHK5LtBnYj2W64VQ2S6H1ACbf3NWk3vO+V/av5OEvlzlTlXq58kisj6ZM6ehbt27pDse+oo0vFX0VV84AI4njXK+Dgtqfg4C7hpFQvnbTqBo4+t4EL1zdMq6FuPIf22pbruh7RPoKfZiCDDV/U7BY6yiK1plVZbFdrDqhjlcUOtaZdLY8qi50Iy9cLuLlAHj/Ox7P6QfZZDyGIAh4ZbLryYJLOnE8m9Un6AJEvPNQ0xuqIEmVJvni09I/A69XuxHk0DvGYM4si0MfTZz7DI9Eaq8ocifO9ciR2SBR4YyS2vXeBkfjhyQuNxFh15oxkJ78r3Ry9o0cldnbYjhMq0qkE1ZnTZW50wDVLKLMcDqrogNfMe/QG1nfvTvrdit/5TB7xJbbWasvZLiIuzjIlnCeStuiftdD4rOvEZ33B+CzATSP6hr+p510rY7n2jS5s5X+Hac+/909/TYduXB9B/UyO77zmWYuxxO7L7MHzb5t6YDd6cM/QHlz5GT0wLsoXJ/zOIGeoNq0UmxqcHuHoD/82AGXfdQrTr/q3q+VFQdw37HUdFwY1tlsESc2zXFTeM/IrR+JL3JahWZYtNpllGX/8P2RZjiW9ln8mPyXyiAtnK21vBZZPT5meGs5V90eLcHjV7noXDBrQ5F21eyxCXUayxW/f8V7EKsM6pqNaExWCSggyAzJG0mFP57tSeUKp7BKKNfG0o0wPG40tUMO9HkhhPSQI6OYckSr8JNiEmn46DT2v+44ty03Yi4lJwFIneTk8QGel501fF92f6IYEPZkOgjwYGp64T8DZslJa58SD54cMksRLNfTxwklRovSbHBWjX6Fh8dIeIdZaoqfRsekk7hC2di38ZzebMFh9FoxUaHe/6bacYmcWLlFt1W5AkRrO6rtd+gu7an8hchL/DZtvzyBbi+rWSWvRJpYmBiW8rnrk1CPywQa5q1x1Y4eGWjFekDllNfW91Gxsqn/bK/ohnB4ctrREam+95bWcgve+WiqBhiWg6qmkgI/rBt4qiRevn33z8uPxd4eVg1HXfk7VqMWxdd3EdiLTsM3Elhh+FcdFhGVEh9xFtBjDdXe7ajmnQjI6Wa13c76AG5Y62/jPG+A2O7xE4QuYTXfk6GZT9gavTucI+u6B0qOSjg1HGa/lN9sFJKPZuwMQTOZeZBjnLqXPGEdVXcjKaYbxTS92B1zn2KW5xDzAV73F9uBmRgd+K2UPvhyQmVPUJ4I6AxpU46WSUZShKZn+jKbMwR02U+bgzre80olR+E+yi4TuQent91r0DGRP/one34I1lJaEjMQLRF9eOAkZLztiTadg/jbp1qHZKZhdI7/3/CH+C+Av1dvt6FL2hCEPruSgpAdWZiQMOcH3Ex0rq6TXSVrCkFB6whBOT1n8iN1Vt0C665uMjx7dM/mK+COOy2MT9XDWKUEdUFLnEu2ijc8NtdDex1XvoQF1HJDZlkvTw+KXvyxmaTTSlC3fIVCEp4oXgYb8RuT4KBv6zlTneVweQf7a9Zb0z6htdSlx4Yxg8kVo7/bqBtljH/IIfVNd3iPwWebRadl/K2sAAjpywAaU1+pL4JzQ0p1ajNfqicweppu+tthE0W0RlpnZXeio9h/m/FC4bEtUWU4l/v/nZkm9J5WbxchH81ExKz6iE7SvvcqfPFpCawqFh8JPh3qkmv2zprc=
*/