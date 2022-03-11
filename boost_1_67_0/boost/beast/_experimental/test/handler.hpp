//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_HANDLER_HPP
#define BOOST_BEAST_TEST_HANDLER_HPP

#include <boost/beast/_experimental/unit_test/suite.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/core/exchange.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace test {

/** A CompletionHandler used for testing.

    This completion handler is used by tests to ensure correctness
    of behavior. It is designed as a single type to reduce template
    instantiations, with configurable settings through constructor
    arguments. Typically this type will be used in type lists and
    not instantiated directly; instances of this class are returned
    by the helper functions listed below.

    @see success_handler, @ref fail_handler, @ref any_handler
*/
class handler
{
    boost::optional<error_code> ec_;
    bool pass_ = false;

public:
    handler() = default;

    explicit
    handler(error_code ec)
        : ec_(ec)
    {
    }

    explicit
    handler(boost::none_t)
    {
    }

    handler(handler&& other)
        : ec_(other.ec_)
        , pass_(boost::exchange(other.pass_, true))
    {
    }

    ~handler()
    {
        BEAST_EXPECT(pass_);
    }

    template<class... Args>
    void
    operator()(error_code ec, Args&&...)
    {
        BEAST_EXPECT(! pass_); // can't call twice
        BEAST_EXPECTS(! ec_ || ec == *ec_,
            ec.message());
        pass_ = true;
    }

    void
    operator()()
    {
        BEAST_EXPECT(! pass_); // can't call twice
        BEAST_EXPECT(! ec_);
        pass_ = true;
    }

    template<class Arg0, class... Args,
        class = typename std::enable_if<
            ! std::is_convertible<Arg0, error_code>::value>::type>
    void
    operator()(Arg0&&, Args&&...)
    {
        BEAST_EXPECT(! pass_); // can't call twice
        BEAST_EXPECT(! ec_);
        pass_ = true;
    }
};

/** Return a test CompletionHandler which requires success.
    
    The returned handler can be invoked with any signature whose
    first parameter is an `error_code`. The handler fails the test
    if:

    @li The handler is destroyed without being invoked, or

    @li The handler is invoked with a non-successful error code.
*/
inline
handler
success_handler() noexcept
{
    return handler(error_code{});
}

/** Return a test CompletionHandler which requires invocation.

    The returned handler can be invoked with any signature.
    The handler fails the test if:

    @li The handler is destroyed without being invoked.
*/
inline
handler
any_handler() noexcept
{
    return handler(boost::none);
}

/** Return a test CompletionHandler which requires a specific error code.

    This handler can be invoked with any signature whose first
    parameter is an `error_code`. The handler fails the test if:

    @li The handler is destroyed without being invoked.

    @li The handler is invoked with an error code different from
    what is specified.

    @param ec The error code to specify.
*/
inline
handler
fail_handler(error_code ec) noexcept
{
    return handler(ec);
}

/** Run an I/O context.
    
    This function runs and dispatches handlers on the specified
    I/O context, until one of the following conditions is true:
        
    @li The I/O context runs out of work.

    @param ioc The I/O context to run
*/
inline
void
run(net::io_context& ioc)
{
    ioc.run();
    ioc.restart();
}

/** Run an I/O context for a certain amount of time.
    
    This function runs and dispatches handlers on the specified
    I/O context, until one of the following conditions is true:
        
    @li The I/O context runs out of work.

    @li No completions occur and the specified amount of time has elapsed.

    @param ioc The I/O context to run

    @param elapsed The maximum amount of time to run for.
*/
template<class Rep, class Period>
void
run_for(
    net::io_context& ioc,
    std::chrono::duration<Rep, Period> elapsed)
{
    ioc.run_for(elapsed);
    ioc.restart();
}

} // test
} // beast
} // boost

#endif

/* handler.hpp
QO8fzBblW5roPFaU8j36vXWM+RwmWI3B3+RJ3t5To+xWPggiuT2vv/YJGgwOajQ6H+ehk828h2Vt6PBc+2zjOtM9Gw4bUjgarfmm8VNo5TQucBIXIRt4MQjBSO8WHrqOa9Pb1b88sD7tb1QIXVsqW2Gf+3oLxBazVwCNW+1c/GVVV4zI1htL+uPU+fuZUsEwjP7+QUBKAtgTTiD8GPnFNQZDTHxHs3rEx4UtUVXUwzM58N4o+HHE2gYXOScqTuor1TKwF7P59YKb747zG2xbmaDf3/+3NB7UoL0/eDaxPO2Q1+ap2JlW+kgQUpb3B4VzYMjVbzLY2hlulx7eg2RW5mlQSU/myLZ83TrtNe5ObLGX8KmRavrYbHs/z9PRA6oKWL7SYRWy2M8L/W9PzxaWRtAhtGu80xMGf33kz+V78nYFgc7Rao12KK+zvVTl0umx94gX64+4CK5EtPR8/DKNL7ZhdJsyHSuwFFNTPGSfePifXL68bx8NUwp+Lz+rZF6UMcVRukSDJhCLwkkmCqM0XXt2vodZNR/jXVjS02V0EU2eR6zBt2PF/s8LAG8KIRmfMDiniewNsv1cZgjSg3yw4rup4PeZdamTj2Fqqqeuf33549Nathv9gMoalwbjRu0gdLFu9enJdbPKSmHOTJMu0bGU2X+W/VbyJ6GgQwipT8s9Gx//x3rjMUTU4xyRGJWDaw9tPcgQEvVrx8n7Ac+EVVcvOQAkQt0QHYYoKnacOrUdEWmfJo3LgVQwSNWkO1LfIrpE53pIrmDjevNw4jcleJRTmLGXXg5loiKK5akyQ/XVli1nC1WQQcTkI1Qtwy4zkrxuope5L/4psUIsXWKK/22pFqZZHzOnukBarIcG0TxLiNdJZpw951aPXokmhHsvOGPaoaijxUKkv4M+eOHYjN97F+8dHKVp0c1KQAQTO32B/M1aYymGixdBoG9qEjeZkCQT08ksxH6FnAEFnRN9/o2e272WOrEK7Wy/H0SJ9xJ71xrreugjbPVSYo3d/d6f17I8tl/zMRsbm0g1uj9W3l7cv8HYd4o2Gish4n7dBvTLQsY9MsF2SkLNlDvAGaQyVIx2R57VwCpQ1t0bvbaIM+e8XUyxJFOIgZAvXxdx3uTxuE01lF/PleKhxCpUOkhYoQsPHHkyx8J3fG7T29qJdmZScaKzroydi6TfVouCgpeXH7yCBIvl7XkET0ghy4LI05S35C/rYKaYvAxdf3866HJ1i/x4kZ2eXMIWmqKH6UEYOkmLjAwaZWP51fMqFLYRsHCxoeXhl7+JQaogTra/TH0dWs1vO7jscx3be+Wort8Ie+Mt65iqU4cMq0MGK4cLHgn8GZI3vmiGivNuuN72I/tePvdGje+Ryj7yUZLkbyPqasMCDsSg0fttm6wwc4v3Sqdbt6mSOAUVXKWgCzaPrtiW+Gp5mtlSlsuy5kua/uLDSvPaKYkduxKX2UHgfS2Rp3XpRksnmF3FXjZoEhTh5tA4FwzVZZvEjgI3vHCm8qkIDbZYW2OwG7Ki2yVDstouzCLN6jnbxoL6MYfNpTMep333wIN7Y4OgdjTb8BKAQN6Pun/UErS1s3Xg8wr4eV2Y6zX2uas+0wlGv7fQCQl/oJI2fTC6vrSerTnD48HgPyrGc1MV9xUjykS2QPdXK3rHukY9VcRXnAR5tDJx6A80skJaKRPa8W9Vjt9pViHk7d/Po48afIa+0ghDfvwtrkBoWeVXY4poF8KqI/TglAV8viWA4PbnSGX1B0XoWs42KZ/T4r6a4MppRiZz7yifgGAUobZe6vDYr2AomKhbHB5AaRl2aRem2n5h+samqboAHePPtW745Un3wkw7/nLrnnRF7esUhixo08NjgHiJRleuK/nHZcEqjt3meiTEe84vypyizJ6v+TjLFJtKip6ZTDmr9jeeqIGhHodiDLOxw+ZXn1YCuMVOotVYvKDVdTE90p/icQnxi1SpwpqmrN631+2lru0+Xo2CRxkxoSPlOkfVgtz+IM/pkUz8iSglE91t7bpC84GP8Mn+y0LzglcWsGBhOyMPjIL4lJOOD9hXnecm6kOx8oDsO/3r7Yyy1MM152XndIbrizWSsNGfVjXqOCCgAROn/Sqoe4ykzGgcur3IO347g7w6UMvp3mQx3vd4R0vsWepWhbH0nFLkQXBwwqjLqTcsVSP8+fR4eA7vxOt4SDVsx+Lc2NUvXJ4ky2AhLBW/2rA4mzt2th8KmtA2JtGzP0L4jtU6kBBb2KdRZEoCKc4GzpeFbYdCf2CY+ltiAhw3dNfscEdcsAt9mHe4wLVZ6xGlwKTE/YmDyI8fJqD8GavIv3Nvtkkll0MHX+PcrytyY100fqbgzfUrVMruTZm2l/hvVmy1NI9Xe5pxblePTDcbssOiQ+uLo8VScX67JG4ExSGnK2+wTbpPj8Y0+q7m4wtzdeN+UmN6GLtNEQzqevE6KJgojCgNrWguWNk+Qz7y8turyOMKVTkk7HOV7Bf+COVBffhU82+3sdG9voZyO30TVeyXkKEZ3Vw1bDYnEtQpwYA7wsrdOXC15Y8/7w6rrIpnAJlhh1xhN63pbkR+puMoSRoGoJTMTEsUFwC3zlQq7KHBRbkLZhEfxyTXX3GW43KV257zCXDMuXoQMxmcOGlnveY8ehfZ/METNpt5cAcVSBCDKpkAs48o2M+Cd4eElCcIjQm3o+q0lbfbozuZZ3081oPrkCsMYbkxzldg8QYTYnmbvUZhdLMxUfkAmI3sz52HctXZsHrmQEnGaCKBI6/vQV7W8/KzutoFRaDjWMjn0ZzbpkNYtdRPk3SAI7pxQFUTFFoET27bjd9lOX8aWKNhMMc26AE/4MWDX7y6lumYqGxSi9VuBSD/w3ybhHVe2JASgXitoxGBV4ufOh6+yXZK4uAkly+hYwhj7DSOsMDAIKFT04qTo9OGC3lrRW4nN2+wa8a8j0uZBvfDBHTMccT4mQaBGKg02OsL2GFi/JNpsov+7QIIdx+h4QEl6frAn8iVmzxTy9/wB8uXq9dUV3kKWMy8silBhFrIrxz5UYVlCyS7clwW8aEd2rzZG22sFfXum9XXjuq2Yr/TCgPmQCNDK6IauhCl6yXEI0Hv7KwuUo8djaNZgBg6W/NpGal+8joH7Xkh5cAteLFm+dbb3EFFIMHfX5xQjkJyVblo8v81IvTztBPXZe9+FN63eZ7YNXj4kzO8P3+RjE5+YvbUVCZIp2m247O/5sMTDbW7my7eTni1v4Cj2UsDN2ni45NJS+RL+BaS8mDSroxd4gzCeFnFw+OpokJHA4Ux6D7d7Cxj92jaQ+NROyqO7uRUzAV/RvUlEE2cZsYfcxNVl5MeHZDF6yUbNgM5ERRYpn/IFDYGjQotHIv7E3IblpEtCeecpX1mFw3SJFoU//UwH/7AzPmHgQqiLaY9eD4LfHI+4S1KQb3pWByoyUUsh7XDPcbew8n4B9M5J6/fGGRtyu4UCd9LQIjnue4jeQS9UTHzYRIOl/cK5fW7ukCr/rHvsoPqSmwIpZtmYq9+YdSJgEfQgrh/fnxoM6++C4GTOFNgDUgcR7V3DQmZkGxpNUNX6F/tWt+yJVoYYtQIdVQZH9IHvPq2DTDhbv+Dn6af/UCwb1VHJ2UUehCWmuhqqz3I8BbLIOoEv+zKXNDmJopN5r0CqOqh1E7v7SlBxZXzpdAraxvtUMUM4/6yWCUs9d7VJCVzuTC50bM7JxhhBJP4PEFLBFJA/5uoODJqZBAZQ6gN9t915hl62h/bv/YmXkPK6kkbuQZpBt1PJy9wr8w4b83GOOnb59jaXEBBTEN55rZRAENwrS9zjuMkVuNnh+sxa3bzb7tM/uAsWr8/KEFMQND2Eq4WoY0A+ZkmywYPu/EU+4MKHhDXh7Ek+T+AH3eIcH0Bme5dCZx2Lfj7JKpmGxnTEpDLOQGgMDFmfPR5kDECoeuZVegG0822ZPKmU7PUTFkuBVZvMezhcvWYadb7gD0aLxLW/e5Q1B51m/Tp5uieTkROMxMQbOhyFvbke5UYXcELK1gD25pNLb1J85X2Y6IUZ1BQfzBGNrmRRnvWErVS9OEXVl8nekHqHQaBZDrOH8VWU8mLtyVktKvj+6VHrtc2DjHuKo2YuSuSLIuWO0ayTHxTTQ9A9vCq7fYMqAZYa6sVndy0m53gQnV3UemTX5uEI9Asx99UgcyLdcukQa7tbKOSM62ftyILmpTTGJGX1D68aUZVK1v1lUtWz/2K+KFd+GJ5iZktJj2F1xdMn6fgt+O4r02OBK4Nh+HzXEJm8aqAoqHgvugeg8SPDbc9/0ADuAQadR6zv924kP0nwn8advN4jFK6QKDBJRjjYIZfVbF6zKS03o+UQn4p4znIlj+xN0EQISPQcJnx4CV0uM6shm6HStj8cV4ekO2t1uu/Qlj2wvSzlszPFQ/FjCUGRuOLSbKNIxN7T63LUgtY3SozVbTxIMlliBwqQwnmUieEknBuSPsOJcK19xdTC72P8eJq4D24tN3LZ0aJElBMCghuLEQDLVc+230JysGKmi210Rry/eSm8d8KWQKBAW3jz0/ZL1Ot6s9cWLIHM/Fl79PT03zUmUHD9w7+t3ARPhq+Y3DKApLwDkDQ9XUvHWOVVNpUG92YI90HB1aRPGRhNOwsEaAi5yb+IEp+GlibQtdNsOSN5VV6eeHkshkkaonh14n+Ku1un007gHzNMU48q0Z01cO8gvGov5n1QI4ji78+so5FY4hds4XX3QyZdfbtVJrG4sQ25xvcdFeQ7qbmbpDLeF3RzVL/jgIAuYzvOCAJiA3scX1emsm5MjtYmPXFo2jWZyCNf0JAxe3+9wHzu+f+NkjOhExAl6L40Nl33saI3mWZWD/sqkDKik6q8wU2RUIIkoFzRaRDI8Oyjr+dne3EhaFD4AgH1ziMNDzh8Cw+4uX6fvPorXzVHLwW78SHnjOaMwAvFxeL5NUVYnA98almpqtpGO3V9VxjeT+TnYr7qxHoGbe8LyweSelVisyXb6MUYJGzzV5/RLfoP8Z5E1nsmYlRdXKZq1EmqtRJmhO+lhh6g6dLgnozDIPvdUpBsBOcwt7mw6pHu81+6yEcGU8MZTrPV2LlgSWgeBErA3FTgkK62iUcN7mEa8eok2Ur7eGpMA/Ns/lGdYHlC1vB68pKJrFffGvBNmmLru32Jo/5MjxFrWBQmzZr25ESUe7S39i2drebi1WPChWVS9MrDtHEoTD9gboavq9NIKjj0EaB7JxSYyYA3YijUSArh0hx4EgNpcEGuKltDzyr/tBtRpRpFYRn/tidT69k4CajSDoa3U+puhjaKAc+QiW9Uz2Xkf5r+lrtc0Re5wZAwJWY/Wzoa/MUm967YcjZESHWPM40FJCbPyxoHdZg9JBU97yoMSBU3Hdm6MLC6NEUvzpgyJloHBWElLFWlKrcixgSEZZy3D7y6ALKzFxqfMREww6zHyHY0Apas61gYVfNCsTTfaUQcHeUxPiJ673q2OLLPyU3zAmO9bfaTYKIGWz0RtaNvY3ZKu92Y/KjBPw1Rcp+dj4+FOS6BqoFlA0AnYs8gkve+HakvY9cCnWTne1ODjkTnTxhrKj0piaoLw/duC2vlxcZR9yiPnmALUblHCOU1KXn4g9CRHIH4mn3U2qCtcOwqlcrJ4QXfSQV45OSgHOQ3+fkXYXfjuo+IFk8w+Eg9UyhcFVtWc83w/1Lp9YmNWzXgPuCk72jVO0mNejcGpw5RtqAdcUolJ3ApaloqA0+qsB7laMniylwFV0SMWkSGvkPkHU+16Sjs2DvLlaIh1FKU4IR/uNqfe4wsl7BELTAikN/JC1u5FAMgr0DvtX9Dcr4g6Ou4ZQCZECBN/4ufZTOEge6tvtILPh+Ef2hOMsoYu4N61ZA1oClLEosLhqOYpWNz6a3Yv5BQKtpfM4EO0auV4kq7r1gRdLnexP6BfQ5wtlFonXWGRyoEs3vR3YNerPt2zddNeiQLWrgvVZXWmyktHvp43P08NmOfrFg6vk/N3Xv3+LoIjZI+EqofuFOvBm9rQjj7MhIhyQ0YdToIRIECNhaBLpCKHQIWj9qtESZsco3ur86i2vx5JMIF6DKr3T5KNH6paiQhH+BIvWAemik2oNyie8MiTtrvTD6CUOmnqkyHVcbMWY6dbSZi5PGtrZJNszj0plRO74MmbwNqxXBt2mnWHO4ew3NGsGm2PQyK10JPCpwZjsz8z9wg/QM9qYeAR0wiqSA+mA100nrmpD3GuJfoAN7S3FEMr45zm2+04R0HDaLC5bgHibGmQTwM0nJNPJU7oVEqXY1RyaTWHHGa2DsKalkRAj9/TMiCz4vEdnY/K5GD2Uin1yeTAimFFJHlB5N2Ah5Lx3Qgt+J6Yn2I8MHVzygyMvzpHSJN6EF0D7FOh919oYDA/zlmrPY9px2qydaR2Dsh0iuaatsOG+q8rD3BxIbdtlBAUN9/eVLXyOIz4KCo6MaDlmWwiQcbiafhqwJ8U5gMg0MFXUS1j8DBOZnqWnliKZ//AGCcE2Jde8ly8v3mKCDQJNmJPhrd20uJHNRcBy808OTVWMbKD5UU7ZQ1DsXXl3vrJw/XVpjcqzGG4GVyFLLSolnriQw7JzbODLZ2/9eWlu7Yvh+G7R1A0O07Bv1h41qEzq5lwFu/1hMrAdBv0U7ZXjkkHKr7unpSqjBOo/DMUEh0ogWmJaxH4L5gQKEGVFoub09pMRTFVTg2WzKmUGkxjNUiaXRLtRra6bX1WrhfxeXr7To7PTaVK/xHahe8+88vnMg6tmo4S8Y/5M8y8HZFzwvp3CgrrmANBmOWkeM6DsxOS/Bm4t2nwnvjkBHHktMj45KqtJ82GwXk9Z+xOFdnnSr5AYvQEErwzZxXeLiBTScOsTLLpxaL0MngoJM3y3rP0uiH/MgHsTq6Rzgf5JNrOGNrOundvu71jYHyUFsAgp7JrHANDSlCBZSMfka3UEX8ixUNig14ryxTwz1t9593Dy4gAy6ZgM7Qq9oJXjs55qsDYK5kRpX7yxPC7rDzbXZqM0W2yDmgaDO8tq5la3WW6q7/9KkG5hYeDQu+ESJDdQmVu972kZbNRoZVIuz6VVAebL1pYkaBxiIGEZ2YLovuFC/KbZRIELAH+FUekNbBjgASU2CaXYWCdbRnva5bx7Se/qPBsj+xy8AMQAcLOPTv3sF8x9mMB91Xc2fAgYaVoFRvD+11mQ9xGmyVCqr8XCVh18nEmC9cTyrctTYOzlS98BB6SUQNsqNNvT9LqKusXr9+l1cUw14scI+sHYvVB2Vu661mGsVRoVG7HewNX5xyhKBatQZixjF3DvNKYQsOY8DgQ/1Vgtip2S5QZnEBO50cikygCLKMhWyRDFAYDg/fPCs5wuzNOwAFuTBfkkHrJPyYvDPcW3K0ON6Iw7jrbkYuaCvc6asj1iTNV/N41IraVmhWSQCZIPZZibfjRuJl+WXjEd6bPbbq8E/LJunQyREGk72h+Gx0PlDVfi0ZNFK+jyKoPHEPLgnJ7+EENCpQOkwg5JFbFx+Dn+KKPsu99PxwKWD5gu4k9EREOMLwwKQ0400j+id/iD/rmQOjEdtD1zSK1fvQRjYnWORe9/QIXOtqUJ0EFjlWhZSE3Q6sLxvb7mbmqa0U17XOdXA7fWRBcaYoVKlfUl54163cvbu5ri3gJCJ4Qj4BkvE795x0/qQTCQtUf14/hgBMxLDGFg8Z9UME5pEoip4cCiAWRFX7bDSkYTKiY8VPlx7KZl8FwRAl2psVv3pHHdwvyqcrVO8qJ8SJxbF4VKDnDlExgNFa1g56bDP02DuueTRCnVZDfQidDCOMWH4ia7AsnvRllWWB6wLQDbX9R60WpdtwjEnA9OdtPPfY48baL8PoL+Oc7Md8QTLhr62GjMvfp12ah8NUBLVKz46PUiVF5xEHJw/KHfOYOBnuExiARVzpi6qFZj/Jf7HQlyFlSDiFN3KsZvfD0/uSF8pxYw7UFG8LkKlKntqNfYkKIJiBxckl+kT4+hFkrJEk2Br3b5KSMIrtRJ7uLHe1cYOFGnv14ydIgSENrLInh2y5WOj1TI9kfFrWXhJ3pSCobaOwMO+pVRY6MO0BnbttF0NyMB8zdbqoRpf8wL/06Lt82LFZ0cNADtS2mru7y/Sh2SuGpWAfp1IUH3XicBQ2i1kOhAvXLreT7Af0goXo0aaIqj8f34ozh8UCX2S4FBAXzaNe15WpJIemXa+8Mj7aWtnUv/loIiOI+alNgCDhtE4yMgsuPYoUaB2uWg/IMliFdxheYA4+0FoZqduHrcRgGQ+/1OTybeJpMAhyHji8GfxYcEK4uZ9OaIaYcnL8VuTz3fAMUOrrwxa7Jb10HignO0WxQsngT9TW0qfJ4pKaQFqFwy2d0EMUU8SFw6zpNRR0q/YcdkMTVgE0wxCcx1TSGk2JEsIYhIskLM6ulxCkN3SFq5jJJ7zvmxYfxOWZVtnGMSO6urqLeGtViZ9fGLU1fn5P/fQIqQ/z97oud4k2q6dbKobQqbKUDg3OA5+2qVva8wthwfMkgwyDc3DbxcrWsL8IejU3opM7hRKQhA3rtFDeEjNZV5t0M2FJI7hR7iqMRS0e/kdw2Fjl2AXIPQ+t7rqgpqKhLU8UAtQimfKWenf126QKN4H40HEVNG7y4O19oDiKMDull2oIY/flWt6SBAfwh/TWhd1WaiF8+AYtNfyQ9+DRi0atUo8A+yRdqPw74KzOTOyzBfNJpfnpS9MBqIgSAf2tmC2y9h5R6dthDYa4T2lgWoWCnOK2EVjYcRT+8PQpZTtyKCx6NrG2Y10ffX6PZHfCaOsqUwG+QikR8O/RhR8/cJ0X61DxQOXhih/SK7B5rQ9AJAQGcFgj4+zkfe9LSCAZNVE08mjQhhAL8BCxEzgUVE4zTMNGu37G+soeiOnStPnvCRFvb729PQ0xi3slNyzHoIkprDbV2/JjjK/HQi4KRCt229c6D13POCFgOS7GHxZ0C3yAvmk201LJqV/qFpvV8E+rA+kj2UASApxXiLruZ1TN1ovJdrzmViSZzwrCDIaYggPf4DLHFn8cKbbZBgmsPBFtbaAv8BcjHO5/dCyq04tgqFh3E2iy9cZi6IpcMAYWTPi4o9pLi2JuQgY1zrD7Z4ik86zsnxLkqcEJz8o8E6UWU73lFo=
*/