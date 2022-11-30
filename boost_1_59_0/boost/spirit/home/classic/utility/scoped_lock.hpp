/*=============================================================================
    Copyright (c) 2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/
#ifndef BOOST_SPIRIT_UTILITY_SCOPED_LOCK_HPP
#define BOOST_SPIRIT_UTILITY_SCOPED_LOCK_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/thread/lock_types.hpp>
#if !defined(BOOST_SPIRIT_COMPOSITE_HPP)
#include <boost/spirit/home/classic/core/composite.hpp>
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    // scoped_lock_parser class
    //
    //      implements locking of a mutex during execution of
    //      the parse method of an embedded parser
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename MutexT, typename ParserT>
    struct scoped_lock_parser
        : public unary< ParserT, parser< scoped_lock_parser<MutexT, ParserT> > >
    {
        typedef scoped_lock_parser<MutexT, ParserT> self_t;
        typedef MutexT      mutex_t;
        typedef ParserT     parser_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<parser_t, ScannerT>::type type;
        };

        scoped_lock_parser(mutex_t &m, parser_t const &p)
            : unary< ParserT, parser< scoped_lock_parser<MutexT, ParserT> > >(p)
            , mutex(m)
        {}


        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const &scan) const
        {
            typedef boost::unique_lock<mutex_t> scoped_lock_t;
            scoped_lock_t lock(mutex);
            return this->subject().parse(scan);
        }

        mutex_t &mutex;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // scoped_lock_parser_gen
    //
    //      generator for scoped_lock_parser objects
    //      operator[] returns scoped_lock_parser according to its argument
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename MutexT>
    struct scoped_lock_parser_gen
    {
        typedef MutexT mutex_t;
        explicit scoped_lock_parser_gen(mutex_t &m) : mutex(m) {}

        template<typename ParserT>
        scoped_lock_parser
        <
            MutexT,
            typename as_parser<ParserT>::type
        >
        operator[](ParserT const &p) const
        {
            typedef ::BOOST_SPIRIT_CLASSIC_NS::as_parser<ParserT> as_parser_t;
            typedef typename as_parser_t::type parser_t;

            return scoped_lock_parser<mutex_t, parser_t>
                (mutex, as_parser_t::convert(p));
        }

        mutex_t &mutex;
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    // scoped_lock_d parser directive
    //
    //      constructs a scoped_lock_parser generator from its argument
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename MutexT>
    scoped_lock_parser_gen<MutexT>
    scoped_lock_d(MutexT &mutex)
    {
        return scoped_lock_parser_gen<MutexT>(mutex);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS
#endif // BOOST_SPIRIT_UTILITY_SCOPED_LOCK_HPP

/* scoped_lock.hpp
rRW5w8J9w0Nf6TVuPd0octKL6BIHdWOI+Om7vQY29AmFNOI/oubKMIrwNodYZXblmoIKx+KLg9RVfeqTsRHRYmgsF+gOKLu8OINm4TqavI4ZngrHA4fzD8+HWc0/3u415mkVdn1Wplbh1Crc4gfUMK0is+L2RlHV1Au/jpiLjicwvCZD1ZSGV6LW6Fdujrx9hnJzaWkgKKOT92Bw9JNiFs7LYHY8taDYDvVzYwnce62FuG2v+IBPrxx6l+7toxkCnLzhpSZjY+/RnbXaULrVJtXOjxY5TdEKGPFLDsFeADpRlqa0NmpV4kSgX7f5NXxmne657GImzhky3MQNGKT5pCmmjZ8omB6K7OK5L/vgoahyNzvkSEoEBZ2j/Qbs/zgsJeIJLRutaKnM4DYbHEWDoWh24ZmKZpkhS7ByIo5aN3CDpalov5mtFR6uaNSYhe/nUd+SSqeDKcWlTAWkigkb+/pjium1bolNhupSgz2cC5WcGXKPJ4rj4hTYspquWRopqzSWCm+B2byFiP09wnOsT0qpVUf+8YihpJx79fzEZKNXzx1MTEP4Bc7XlPb8Jd85G5iHW5Pnobzjv2/2w5a4YgO1wOIpymXDNGbxTb0fkfVBchQ1sIrcN6x1DpiboLhLSxNmaAFaHlfBtBFowvggdl0JwJF4OGk/yULC8UHjA+j79kUaanKgIA7ry2kTPybyJX3adfSzOHOGp7xv6RECRRrIt3m/oK43xb6WzQ5ZqOGrTvPcDwdYueGMFHo62OjPkUrP8EhFGPBbUxwfRhoZ/SrIs4wP/PRfODdAVVl8goWHI7lnIXVIYPeTYic+0Oi00pK6vEAl8lFuHgMdzkGeyKvOqW9EnfkNni7C0hzAPlO3BUAuoJX+ADcsNpI+Z8CwJI1IyKWx//r9lZPQ4NeTYbLfLJe6pruNB3L94m+bkjW5ea+4mpi5qlMyZCjYj73GyCQjNsqav+/SK2h4lXNKlMwSJZ3+04xdnL/v+voL0RZn/UV8CFc/PgUmKrP95lKOh4RPNjq0KqmieVtvfxPCb0mPdmlwsQUfV7dsgGKB1KT0Ep3IbiHE4/Xf1qR8BkqN31CSxvo12JriuVzIBXpG3PEdub7qo1zbOVd9/4bmdcAqN7fyPAxiUvPZqgPGmePO+CAVUpOEm/Y34A6EXlRC/pEgi0wV96SEh1+PJzzvzIQSaAhMTwroC9GOvwVUHIHJKBBgAUrsF2//XQrxQBBOgkRtb5n470Y2Du8ERJxTDyGXvuv85rs9zQR46SFLGXwispuz2E7sopIiMT2EtA+Do3qCAaVXYn7lmiB8dtz3JlB9Jk6YTIU6J5Y43ITQZ2rBYBF+U9pk5kD6KFQzw95+RLuYoE0Eh7NuYxxdmy6RssR5a6VufbJLJHaoEvuGl+jZQP3SgQP6/fft/f2+mneFveLXG2S/4Q9BvNVOG24VXGGJv9Atq+EluVCK7RjgPwnbcUNB0VIiv9OChv8+vcdYEjfzFil+fpCm21sGnzLm6yN5f9xjPF5vNU/adu82sRhhNqZH8w2IBAL6Iak22QO1STvkULT6CnP/ZrFMtJy/rcnbh/NPxRUan7E1OJuPYjZ8TsP3zUe90nVOT6mfTb4IRKAwXhasXDhhhJvVdcXYZ+BPZ6Knab62AsBYcTujz8GmY7Zkogc7I9EYNNpn+KmcLJ6ugLPcveLFVf18IyKmhN8BbcxuBHAjtRhnw1fjP3liZp80T5KleqPJv2ylWso2QeblaXzgFunKsUR/BKgeiQPyFMF043gJFfPGep61cSD2iE6fBrVvdWTA2CiX182cUk40OJ6E7Rh15fgjvP8rbi7TTynDL0p7UZx8n9iBHUri+RfYH5SaMiBGt7avnxZ66I1v0ULhh3ItxENhSHc20pQKJ5yidOkVuaGuMulrUZ8GK9AL4NDXj5cHiVmhKRbEJhtlCb4t01B75NckO0u4hSlMCnP8fbNjKZezMyiaBPCUVvrKzJMDPE7uIqavzJEBQtui4iRUrPrH2gT4hOjgVri5yo4vv/8eYROIVDGFiEJ9US6toe4BhqheR/iuVgtEQbRze1sQwMy7GyrADt1v1+fCFVzetrxDmq9Zm8O2LN7NelFu+K43KE+9yPsng7PmXa97c6K+VzTvK3o6B0leSLUOk82XiscdMPXXvQc0OCtoYanOesT59TZDyOzdrnk7IefxEtG5GSJe7+4LqKNf8Mp6JQg34OcfIGpkDMd98Lb5CV3n9u/e+zVvtjj3VT7OGNxfbbg626KET3hh6+BWvIaaLZeQfENkTSgl5pIPVnqwxVJoaPaKy2J9bNT495Nwtkw1TUqqSQprdm7LTpCdbpCdjApvAWzuEX87ATpBkh0Ain5CqdSMdit+iyRdHA5OtHNoEuIrJwQrWyH/LjrVK21vztaXT7FjySnDyvRm8f8w9zfgUVRn/zi+m90kCyzsAgGivEVARYOKBpTtgoK4IVYWNyxkRQzQ+tJ0H2tRZxArCdBNItNxKVV8axGxgsWWtlhQ4gNiApQEQYiKGoTWqKgnbqpBEQKJzO/+3Gdmd4P4fH/P9/pfv+vPxWxm5pw57+d+O/fLP/t8l1wsGQilrHTzw5k0fK3APTBiO0ZbLYIGK5mGj3JdQutXDGoB4QhByvl4/EZIOpL4aL28fenn7H6tG24PIJOvvF0pLltKGcJhq8D1L8BMOlk+9kjZNXbkCKcywejFV+pSwN5Z7yAaTZr1S3pNLtZ0c2LaK+yoWz+l/jRccBgS03Q5qtgmaboAzc81ybZfQ0+T6SmEeLt5uJHHOzUspmnVZx7Xg235jVqhC2bAddo0t1aCcJGzKfvv/sLHICxoefdTS9AiAcvNYJD2z2mJvkm4rewvpj0tyyNuxWftMcOh5McMp3IRTeAb3xpyl739agfchTWInscNnKDjHOsjzDQiy6e75Dgl7v+803SbwNb7ohqLgMBFU+yMoV4GXhbe5b5hhmzK59I1lNqHe632eJFXbzat3oyoYw7gyOhdnJNjBrObpNS63ciT8B78K31m1ekPdCr3sD/Bm4uLme0wqcr3/FPy1BlUdeKEufbTE/Wb8+iTsZBtDkt7Xf8w6Dc78O95vt/iXulNsLtrpvSZX9o6xpnuSAhgu+q45Dq91q6hsZv2WafUjJNBaLrqwEkXcJGo8TrcHUN7WRpucDD0ULyqEfYoIZHrgqFW7EqCVIULY7tyiLGIhC09vqZo75B4sxsRR4Oh8B3bhXc4xo3j62Ktah/9Md7R4/jraJjtP3D/+ciRLP2Nvij9wivZmlS+hdxUvBHuJHoC5x9zxMJPzpbiHTM5MyLIPgVBtl9UvcikIPFAh9XecGCmZxNVYHmXlfIv06NbX90eNkK3QepoBlRKnEfAoEnNJMqQvQgSHQMiBoNYdVjJp+IulkajIXH9i6ZmSP9voK2swo1tBEDPdGML/3PDTK0mSQkyS0It/PRrE/EAIZ/lYl0E1stje0jFIK6Gt0DjgVEELEATA1Ik1fQgJSHyV3zRZrD7SOUyGUSdPf+BBRysPzBSzwpzIXAWOlDvH7VH0KPpSqJXlFZlWbdjRCZdeLID4sKdNQtHIXS27XLJHtz0LtG7bVlsI0R4rNS1NOimMZqord4liZWhhLHoT67OPjS15cy3LmEztmrQM8yHsJXptMuleqpYIt+4xHh6Aws7uxizhY2KhoSlPeoV/OSVJkZt2L7i3i0dTCpf28VciIY0DBuVn//NgATJeBKkJnHytWqeaS20DEtVmp+W43a3OJ3FxHVh4l+WDZQX/TslLv8kuT8+tsFQ1vcsForSz6LtTPVRT9VOPBJeLDghR5oQLaD0JMDNeV8BF/m/UQpomg9/bMJW9UJfaRvh8OSeYxNxogsDbbQM6LMRBwlj3EMAWvxkizk8gy/rQEhTKmoSFbUiWVSBef61qeA7zsgj2JyPfsISBxrEj46GzqzLN+e44tLUNpy1uhBs7YDY9o7BGrTzKYf4KjMVjSL2IGH3gfokd/4kpz7TpV2fp13v0id58yfR/QjteneK6mOx3xjDU7nODgcP9x/sgJ56Wc66vl7R9G2HUcAhGzv99Z7KX2M5TMuBB/MVYAiJznfohTmmFSylIFqH5WOelle4rO1LQrQVOVpFrnjk2w4uici+UfmFI6LOkF44Mr8wT99LUGEEiH1xO80ZbTnp04r1PIi4fBUGLPCP0dNYMB6UhNfjtCUGh8tyviV64Gou1V+vuCmVsoeEh5Jp26aVUlaFnkX4GYjaVzFIvYdWFLX2Yv1pWEb5P1TmYa+Hxdap3xly00HhnpFq0JXwm7U1HJd9QIiXyfpTjXb+1MefEmqrOPvjoSAn9n4MZIravL5Xiy5jbUS7sQKhRPTC0bOpqMv0JTADpbvhDEaknwmlvz5ttL4UKb6aHAc0G8SN90GmDohZb8+5Ah4dxsdavC3zae8lAQ5EMRaRv3J9isgnADALCj9fZZi6hPVZKKLA0CqcWoVLq3BrFTRZeVrFCK1ipFYxSqzdjMU7bbyYdynM4VyxaWMMrXA0wauyzXf081IKlIR4erXCQYjJ8qfRvCvvcPBSjE2wbRjgJaoqNmFlHt0ovV8d9eQArzAGsdtyqJcm1Ulplfp+d5DAkdJLt2t8Z6xodkhH1tT0D4to/MdYTRf/PczJQD++fKQdYrxR1BOxtTKTyfYXVmQwyAKdC+K9egRudos3M6RlulnaZ/bkQODzVHGimgoyNSLLqSKxMiM94vEAByz407a0AS74U2qAa0YPGmAKVDigIJsg+iY0LhjgVbK0CaNfJJReW3B4ckTbvr4X2oe6tO04etOqR/P9GP4twu/qPP7dwDnH8fvxnLMJb7Yf4d9d9Cv2/uo7Fl7Flud5aNRiyxvorTFRqxb0N17dTr8hbXsrf9DGv8f5t5Z/t/HvPv49iA/ZqDle7fKwwBUPYn/Wd1K69yiiTjggTELUF7HiD2cgZ3AEOrXtuR40bhB+VzejtNVH6dc3YVUetBV8E254fIBX7R+b0EnD4aroKX6FMpdAMRXEb0SrrsWn20fQrzj14HdGrN2h9jOzL3bL4dNWo0v6YNnCZg93rIm/O4KuEweiVa/wotdrvJy4lvs1godvI9/X8O9GLxT0a7ym2v72zV4eC/6t5d9GzvcI36/0MiO1fQk/VfLvMv5dxb+b5eh52OekVv2UF5KJPTst1fLPjO6WavmXk2B+QOPn49lRc32ZPDDelHa5oMYm0rTNj4L4MLXNHfC1e77NMgiP8VLheI24kYD4lhj3g13j40ZOHLtgIrL9tWcIoy1FbrBLxvy7E+fHXpX5r9aXpvLDdiFU9tSltF3f/gpQj7L3CwltENwgYKGLrV+BsnOzG0izQNW+k0osE/0oeRV/tROgDsfaBB7fXUYoruyG4ZS42EzknW/lYA/pf7zBYcqPz3pfhPfWqyUHe1iO7VMVlLYsrzADBJz17dT0b1lKHUp7U7DHtwzwxvNsnV53bndOp+BCjL9uI5hwrJKZzUmYyJQKXVgfYuLytyi9CBTMY3DrIsmEGXTneBj7laoLtM/myiwe694mIoOTQ8X80h83dNAMb9xH/UzksGu6Vr3IpV9NVO4n0AS8peqEKhA/wMdj73ncdMZ59lnPNy8wA3aej4EgrZTlDAztc0qNeW7Ym6UOfpIcmLEFecpum5PjFe9CssPPelPZoNvozc7/MEWPg4jDKo4MIIHzSU94Lt+EMbRP1f8Q8erVdwMqDa8Hu/b4TBfO1OE8+OS/B54YfrJE3F7skhYqzPw8BwzBHObzq16jFfJawE4bFNsUK9yUYfFhCm/SopRYXf8dBgAa45Gqt4kFuB6eo6+O3zeDyO119C8xKv4SvoldC+XKXhhlLO4qBDK5OrY7N17ehmxxoqzelO64CeIfsZsQ74+AeOaa6Oox/ZA42tRpXAiF/fgmgJsSLSCMfp0sfPJUaTYEqS9vRdlz9b2+GODS4iuwRMQLP4I5upvuaYrgSkki/Fl6DFBF+kX9LlbrScwgkjI/0O7AAmvlT//r3J8OiW3Fp4TuhNKNC6jtlegvb3pLD/Z7sRxKz3diHlj1p+PdNOUzfabb9GboqnpbWiLS5GhLAQBBvhfUVp3wrK4tijU7YrXdHI3aS+iP9juAxjTDC5yWUO+f3aEtXcnp+L7gbe13yJ1umSIiREFaWPQ/z54li+yy/6CJRv3Vj4V0RulddMhAL7HSuUTyDb7VQP5KxslDIVOlHDpk4XBU+hQAPcg3oLFYN3pyJOoUEag2SG9oXtMb2usNvxvgDYHOJl6vNSJ2I8ty1B8NxxqMEP2LiJfo5dzEIPPTHPNTfEXfhMWjlBxmWtSquwxhkcJhfgYtas3FLw8CAkRtNVvfI4Qx9RQQBp/WbzGSGuZQSCowIltdIyeGxHv3MQzqZyLWnj5G8GomUidKkMPwql2vBt6jKXi4nWCcvhyb5XrahxfHXt1oA9gfoj1p60mj+mQD0iUiWVILrPiwsydYo+mxvaPlEUqeA4vBU/l3RiZiMzwkHibOx60vAc2hVeNX51/t4WYq7rmJwNoPHwU1lzoCanqaLekz9Yl5wP3alBm+1cD+FTf6VmOnKpPKVkLav+oZHPsH4MuIsnuNV5BJbygRrQhcbMYd1KqBdzUuQKIu7jePQKtd7qaTTUWisb17kj1a2gp1+667WXdE5JARn6CPhSBbb9deg9dYOM/2VP6OxgLO9TX6a3rU9lQu6smx2beU9YBC2T0YLh0D6N9PDD8BmjYJaPrUV91N5QCS+cZivogefBlv4lWKAUl6hrGJyUD1iLGJqUK1WVOPaqqo5wwjbSwrhCmD0e8WueO98cCyEMS9psO8XiV4KImONvrNwNpmPgTiH1oCe7XXyqgYUQA5sQ4qRlePMuTSquZDH2SPMkd/DGRL3H1dFYJvxNCK/Lr8wJFEd3033fALf2N5hr5Df4ypnhjy67G19JsfQ+vp2/zYBjwSYhOOBv9blPsNTV/F+fC93uDfvShD3+8LHqnI1KnsLH7eHdvKdIzGmdSLdS5Onyko/w5Kf8MXbEb+ZsqP5x2azBDjnujcjk3cpiCsUGhTX+yLgUpTh+pxzCB40vjMXdONFWsxIC4dmprIWvC27zEUol7re4w/uDruvM7RpsdACcfdD8pcVOmQWLu9wks06eIcxyYmltX2RDeHzrfB4/qERTTmvsduAI7tHy0w3o9mOdqM9+M3FGYSadACXt/3OGbcUwlRtF6F+dCDx2OB9u7xHFv+G44GKHIG9mmBxnhRdy3YFN8K+jau7gMCifEut6nR+KY2ekvUQBasG9VbIY9ih9jzMCATTPGmvczuZPEidcl4/7mcBwZ44WfZi6OB3LQUGpUYU9Flq66F2uR+cegTh9U4HdxE7JShzPUF2ytupWW+iYfqBt8mHqrx+svI5ziRv5/oI3OcJaGjN+j1T588VR8DYYyZzf86fsO1GTix4LILTtTH2swk2sdUMtCEMo+mYxOjlcA+z+od8a3Aqj+OfeyI7ejm2wT8pgygMYuPseXvp/EKNDp28KA1Jc7X1eNxty3/mB5sz29wtGnBRscbmnqQxtE+s90cRKrnZax2tZf28h3017cJvIDSvb4KT2iLHuPN
*/