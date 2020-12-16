#ifndef BOOST_BIND_MAKE_ADAPTABLE_HPP_INCLUDED
#define BOOST_BIND_MAKE_ADAPTABLE_HPP_INCLUDED

//
//  make_adaptable.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

namespace boost
{

namespace _bi
{

template<class R, class F> class af0
{
public:

    typedef R result_type;

    explicit af0(F f): f_(f)
    {
    }

    result_type operator()()
    {
        return f_();
    }

    result_type operator()() const
    {
        return f_();
    }

private:

    F f_;
};

template<class R, class A1, class F> class af1
{
public:

    typedef R result_type;
    typedef A1 argument_type;
    typedef A1 arg1_type;

    explicit af1(F f): f_(f)
    {
    }

    result_type operator()(A1 a1)
    {
        return f_(a1);
    }

    result_type operator()(A1 a1) const
    {
        return f_(a1);
    }

private:

    F f_;
};

template<class R, class A1, class A2, class F> class af2
{
public:

    typedef R result_type;
    typedef A1 first_argument_type;
    typedef A2 second_argument_type;
    typedef A1 arg1_type;
    typedef A2 arg2_type;

    explicit af2(F f): f_(f)
    {
    }

    result_type operator()(A1 a1, A2 a2)
    {
        return f_(a1, a2);
    }

    result_type operator()(A1 a1, A2 a2) const
    {
        return f_(a1, a2);
    }

private:

    F f_;
};

template<class R, class A1, class A2, class A3, class F> class af3
{
public:

    typedef R result_type;
    typedef A1 arg1_type;
    typedef A2 arg2_type;
    typedef A3 arg3_type;

    explicit af3(F f): f_(f)
    {
    }

    result_type operator()(A1 a1, A2 a2, A3 a3)
    {
        return f_(a1, a2, a3);
    }

    result_type operator()(A1 a1, A2 a2, A3 a3) const
    {
        return f_(a1, a2, a3);
    }

private:

    F f_;
};

template<class R, class A1, class A2, class A3, class A4, class F> class af4
{
public:

    typedef R result_type;
    typedef A1 arg1_type;
    typedef A2 arg2_type;
    typedef A3 arg3_type;
    typedef A4 arg4_type;

    explicit af4(F f): f_(f)
    {
    }

    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4)
    {
        return f_(a1, a2, a3, a4);
    }

    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        return f_(a1, a2, a3, a4);
    }

private:

    F f_;
};

} // namespace _bi

template<class R, class F> _bi::af0<R, F> make_adaptable(F f)
{
    return _bi::af0<R, F>(f);
}

template<class R, class A1, class F> _bi::af1<R, A1, F> make_adaptable(F f)
{
    return _bi::af1<R, A1, F>(f);
}

template<class R, class A1, class A2, class F> _bi::af2<R, A1, A2, F> make_adaptable(F f)
{
    return _bi::af2<R, A1, A2, F>(f);
}

template<class R, class A1, class A2, class A3, class F> _bi::af3<R, A1, A2, A3, F> make_adaptable(F f)
{
    return _bi::af3<R, A1, A2, A3, F>(f);
}

template<class R, class A1, class A2, class A3, class A4, class F> _bi::af4<R, A1, A2, A3, A4, F> make_adaptable(F f)
{
    return _bi::af4<R, A1, A2, A3, A4, F>(f);
}

} // namespace boost

#endif // #ifndef BOOST_BIND_MAKE_ADAPTABLE_HPP_INCLUDED

/* make_adaptable.hpp
bhs6UPMnRx0o5lk5x3pMTTbtUOAv4utbNJ0U+zuIAuKa6+qQhG90Fetz8L44RDQ9l03nm79qyS13jZfrT9tX5SinaZ+vJL07XF1pn4a29hmM/Frc6UmeZ9QSfdaaG8Y1Y61nv/pVs54dedrI1H1w2bVf0nYwefTrl5anuOQ3Xcf2SbiHrHp/1dS7PmZKVTv13ciHHNvNc9m7Ev4jV0tGphTqpL7vmZ16sD+31/6N0mHMN2ueR3Fcntm0r52JW2G9q37NWyZ9fvZ9L8vJ1w9mAeUzfcFMiTvFNYB/z/E9O5PmqX529pTBO0hv1DKsx63l2P6AMhRq6+iDZ1D+U7z6LfFW897abcpwuf0dwCkuh7ct9mg5Fmg55uBWc6x6r385ysy3NtMUjm3xlMS9SMqR5SsDaZ7aMnivEW4a+BGmfdNw3PmUIfN1U4bivHJRp5z8uaWS74dlv30Om2tE5W3v9qeKv3/wtwAt5zQJzxD/WBM/yWWzr1EIjb2mEgmPUT+9lPgbm3udFPqcNrhU3C9P4F6QslAvlMX5O4GZo5DY3pNAf23vHrhpVnv76gqzFsUFprZUZzOl/BLEObSdJU5bVwt7G8uxOKfvJxqe7Eog/GzJkZxIEra/J/q9yKXwvFnf6Etb6x7pBL6HZkodSNK1fj8p0s0rd+s9zuO4hdZJ3jD1Is8h1LKnDyWM+1W8Rn9UNsWMRSnif5Bryu1UHxqnlbkPaiX+X8g4p3rKT05j6r2HyKx1TUR3vO/V2+r9pKVD7VSH6Ofl+BzD8K43axy77g0zjpnrjzJTd1Jmp++R5prc3sGT4GZcU+0ny4gf+6ZffZqGj9NxiTrVQ6ZeNU6c+SbcTvw3uvry7yXOdavxko3+ugL0d7aEn8M9QHSt+thVZM9ydUDW+067rdpb2oazuCwMmzcJ3rqUejNl1fp0vm4PdNT3KqqfvXEPWuONpz4LehfnBMz3cck7nQGip3lal175tmbOjnuf7165opm/jZmxRj7F9Infir+9yMfJM6D/t6RvJLy1+ItM/FZ+zz3zw+jbvPOsyL/MszJ7lTfzt8GSKbSOST786mxfJ/9vwpb3l6SXKWWuLO5dELrOGGfsdabySaYOpok/UepgabNg2z9TJTzBNy6o314Hq0+gDsiPXx1wTvycU8s7Rsfy7M7BtmSWc4KqfTZbMiFmIVkz0dj5v6QEefM+KwybMDJnR89dr0vwuf9BvqtrPffCud73OV8F27Ihvr+tmgfCyJe3///K2Krxz+t7IfJ6NfVUU0texfCO5vWzlKC8avwEfRceZHeH8JO3u8P5guzuzDV2d/zLt7NrcPm+QfZgbeW7JK9kYaFjW2j8BLut3ILF0Lz7CSjf+BMoH+cLLJ++r+EcAXqe2S24fNdZY8tbtvKFnB1mNP2k9fxAiHN/R94zwjg3mi51dyy4bol/8np+zEHPX0gPzuu11nNW7Xm1NF3yejBYzzV+gr6/D9Jzwk9ezw+G0HPOoXrurwfV3YPL56Z8pbWXTzXdsT1I47i6TvjJ6/qxMHT9LC1j6x7BZbzd6tNNGbP7ZQzIGTZp3MnrtvdcR0Kc6w7r2SD4XKXzS2WutX4XCqw/jaM2QqMl3BKftXBevu1ZIKAOp4aRX28dck5Thwlah9FyzJzHbnMSOwfBZdto9fkhyobuO5VL5RN0jlSIPv576L4pU9D8JTmHX3kyMoLLc4v1Tt+vPCevE97zRPcKPs8Gq699234ef31oH6LekDf68HRofUDm5PWhfQh9eDqEPvT2vvcIUa71lCsjoFzoglOZVDZBnz+CdIHwk9cFUx6/Z/pgO3v73U726Jzs1znZzTt19tlC299zso/nZKc=
*/